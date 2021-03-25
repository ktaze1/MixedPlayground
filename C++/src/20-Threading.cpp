#include <algorithm>
#include <bits/c++config.h>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <shared_mutex>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <vector>

void foo(int a) { // free function
  std::cout << a << '\n';
}

void fooReference(int &b) { b = 10; }

class Bar {
public:
  void fooBar(int a) { std::cout << "member Function fooBar " << a << '\n'; }

  void operator()(int a) { std::cout << "functor object " << a << '\n'; }
};

unsigned int square(unsigned int i) { return i * i; }

int main() {

  // free function ------------------

  std::thread thread(foo, 10); // funcName, argument

  // thread is executing seperately

  thread.join(); // when finished join

  // member function ----------------

  Bar bar;
  std::thread memFuncThread(&Bar::fooBar, &bar, 10); // 10 as arg

  // execute
  memFuncThread.join(); // join

  // functor object -----------------

  std::thread functorThread(bar, 10); // 10 as arg

  // executed in seperated thread
  functorThread.join(); // join back

  // lambda ---------------------------

  auto lambda = [](int a) { std::cout << "lambda " << a << '\n'; };

  std::thread lambdaThread(lambda, 10);

  lambdaThread.join();

  // passing a reference
  int a = 1;
  std::thread referenceThread{fooReference,
                              std::ref(a)}; // a passed as reference

  referenceThread.join();
  std::cout << a << "\n"; // a is 10 now

  // std::async
  auto f = std::async(std::launch::async, square, 8);
  std::cout << "square currently running \n";
  std::cout << "result is: " << f.get() << '\n';
}

// basic sync

std::mutex m;
void basicWorker() {
  std::unique_lock<std::mutex> guard(m, std::defer_lock); // not locked yet!

  guard.lock(); // it's locked!

  // critical section

  guard.unlock(); // released
}

// simple thread pool

struct tasks {

  std::mutex m;
  std::condition_variable v;

  std::deque<std::packaged_task<void()>> work;

  std::vector<std::future<void>> finished; // list of finished works

  template <class F, class R = std::result_of_t<F &()>>
  std::future<R>
  queue(F &&f) { // this will enqueue the lambda into the task for the threads
    // future of the type the lambda returns is given to let you get the result
    // out

    std::packaged_task<R()> p(std::forward<F>(f));

    auto r = p.get_future();
    {
      std::unique_lock<std::mutex> l(m);
      work.emplace_back(std::move(p)); // store the task as void()
    }
    v.notify_one(); // wake a thread to work on the task

    return r;
  }

  // start N thread in the pool
  void start(std::size_t N = 1) {
    for (std::size_t i{0}; i < N; ++i) {
      finished.push_back(
          std::async(std::launch::async, [this] { thread_task(); }));
    }
  }

  void abort() {
    cancel_pending();
    finish();
  }

  void cancel_pending() {
    std::unique_lock<std::mutex> l(m);
    work.clear();
  }

  void finish() {
    {
      std::unique_lock<std::mutex> l(m);
      for (auto &&unused : finished) {
        work.push_back({});
      }
    }
    v.notify_all();
    finished.clear();
  }

  ~tasks() { finish(); }

private:
  void thread_task() {
    std::packaged_task<void()> f;
    {
      std::unique_lock<std::mutex> l(m);

      if (work.empty()) {
        v.wait(l, [&] { return !work.empty(); });
      }

      f = std::move(work.front());
      work.pop_front();
    }

    // if task is invalid, we should abort
    if (!f.valid())
      return;

    // otherwise run the task

    f();
  }
};

// Ensure thread is always joined

class thread_joiner {
public:
  thread_joiner(std::thread t) : t_(std::move(t)) {}

  ~thread_joiner() {
    if (t_.joinable())
      t_.join();
  } // RAII
private:
  std::thread t_;
};

void perform_work() {
  // do something
}

void t() {
  thread_joiner joiner{std::thread(perform_work)};
  // do some calculation while thread is running
} // thread joined automatically

// ops on the current thread

void foo_current() { std::cout << std::this_thread::get_id() << '\n'; }

std::thread someThread{foo_current};
// someThread.join(); prints something like 123456
// foo_current(); prints different id

// std::this_thread::sleep_for(std::chrono::seconds(3)); sleep for 3 sec

// Using condition vars: Producer-consumer

void consumer_producer_problem() {
  std::condition_variable cond;
  std::mutex mtx;
  std::queue<int> intq;

  bool stopped = false;

  std::thread producer{[&]() {
    // generate random numbers, producer will push this random ints
    std::default_random_engine gen{};
    std::uniform_int_distribution<int> dist{};

    std::size_t count = 4006;
    while (count--) {
      // lock before doing any operation
      std::lock_guard<std::mutex> L{mtx};

      // critical region, do some work
      intq.push(dist(gen));

      // notify consumer
      cond.notify_one();
    }

    // acquire lock
    std::lock_guard<std::mutex> L{mtx};

    std::cout << "producer produced! " << '\n';

    stopped = true;
    cond.notify_one();
  }};

  std::thread consumer{[&]() {
    do {
      std::unique_lock<std::mutex> L{mtx};
      cond.wait(L, [&]() {
        // Acquire the lock only if
        // we've stopped or the queue
        // isn't empty
        return stopped || !intq.empty();
      });
      // We own the mutex here; pop the queue
      // until it empties out.
      while (!intq.empty()) {
        const auto val = intq.front();
        intq.pop();
        std::cout << "Consumer popped: " << val << '\n';
      }
      if (stopped) {
        // producer has signaled a stop
        std::cout << "Consumer is done! " << '\n';
        break;
      }
    } while (true);
  }};
  consumer.join();
  producer.join();
  std::cout << "Example Completed!" << '\n';
}

// thread operations

void calculateSomething(int n = 0);

void thread_ops() {
  int n;
  std::thread thread{calculateSomething, std::ref(n)};

  // do some other stuff

  // wait for thread to finish
  thread.join();

  // n calculated in another thread
  std::cout << n << '\n';

  // you can detach thread for whatever reason
  std::thread needlessThread{calculateSomething};

  needlessThread.detach(); // will terminate when done or main thread returns
}

// Thread sync structures

class PhoneBook {
public:
  std::string getPhoneNumber(const std::string &name) {
    std::shared_lock<std::shared_timed_mutex> read(_protect);
    auto it = _phonebook.find(name);

    if (it == _phonebook.end())
      return (*it).second;
    return "";
  }

  void addPhoneNo(const std::string &name, const std::string &phone) {
    std::unique_lock<std::shared_timed_mutex> write(_protect);
    _phonebook[name] = phone;
  }

  std::shared_timed_mutex _protect;
  std::unordered_map<std::string, std::string> _phonebook;
};

// object locking for efficiency

class text_buffer_example {
public:
  [[nodiscard]] std::shared_lock<std::shared_timed_mutex>
  lock_for_reading() const {
    return std::shared_lock<std::shared_timed_mutex>(mtx);
  };
  // this returns a scoped lock that can be shared
  // by multiple readers

  [[nodiscard]] std::unique_lock<std::shared_timed_mutex> lock_for_updates() {
    return std::unique_lock<std::shared_timed_mutex>(mtx);
  };

  char *data() { return buffer; }
  char const *data() const { return buffer; }

  char *begin() { return buffer; }
  char const *begin() const { return buffer; }

  char *end() { return buffer + sizeof(buffer); }
  char const *end() const { return buffer + sizeof(buffer); }

  std::size_t size() const { return sizeof(buffer); }

private:
  char buffer[1024];
  mutable std::shared_timed_mutex mtx;
};