#include <thread>
#include <atomic>
#include <iostream>

void add(int a, int b, int* result) { // add a and b to result
    for(int i{a}; i <= b; i++)
        *result += i;
}

void atomicAdd(int a, int b, std::atomic<int> * result) {
    for(int i{a}; i <= b; i++)
        result->fetch_add(i); // atomically add i;
}

int main() {
    // int shared = 0; // primitive type with no thread safety

    // std::thread adderThread(add, 1, 100, &shared);

    // while (!adderThread.joinable()) {
    //     std::cout << shared << '\n'; // MIGHT CAUSE UB!!
    // }

    // adderThread.join();



    // right way:
    std::atomic<int> atomicShared = 0;

    std::thread atomicAdder(atomicAdd, 1, 1000, &atomicShared);

    while(!atomicAdder.joinable()){
        std::cout << atomicShared.load() << '\n';
    }

    return 0;
}
