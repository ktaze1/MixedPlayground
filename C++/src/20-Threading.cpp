#include <algorithm>
#include <bits/c++config.h>
#include <cmath>
#include <condition_variable>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <type_traits>
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
void basicWorker(){
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

  template<class F, class R=std::result_of_t<F&()>> 
  std::future<R> queue(F&& f) { // this will enqueue the lambda into the task for the threads
  // future of the type the lambda returns is given to let you get the result out

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
      for(std::size_t i {0}; i < N; ++i) {
          finished.push_back(
              std::async(
                  std::launch::async,
                  [this]{thread_task();}
              )
          );
      }
  }

  void abort(){
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
          for(auto&&unused:finished){
              work.push_back({});
          }
      }
      v.notify_all();
      finished.clear();
  }

  ~tasks() {
      finish();
  }

private:

 void thread_task() {
     std::packaged_task<void()> f;
     {
         std::unique_lock<std::mutex> l(m);

         if(work.empty()){
             v.wait(l, [&]{return !work.empty();});
         }

         f = std::move(work.front());
         work.pop_front();
     }

     //if task is invalid, we should abort
     if(!f.valid()) return;

     // otherwise run the task

     f();
 }
};