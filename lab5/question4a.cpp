#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
// Each thread locks one resource and then tries to lock another
// that is already held by a different thread which causes a deadlock
mutex resourceA;
mutex resourceB;
mutex resourceC;

void thread1() {
    cout << "Thread 1- locking A" << endl;
    resourceA.lock();
    cout << "Thread 1- A locked" << endl;

    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "Thread 1- trying to lock B" << endl;
    resourceB.lock();
    cout << "Thread 1- B locked" << endl;
    resourceB.unlock();
    resourceA.unlock();
    cout << "Thread 1- released A and B" << endl;
}

void thread2() {
    cout << "Thread 2- locking B" << endl;
    resourceB.lock();
    cout << "Thread 2- B locked" << endl;

    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "Thread 2- trying to lock C" << endl;
    resourceC.lock();
    cout << "Thread 2- C locked" << endl;

    resourceC.unlock();
    resourceB.unlock();
    cout << "Thread 2- released B and C" << endl;
}

void thread3() {
    cout << "Thread 3- locking C" << endl;
    resourceC.lock();
    cout << "Thread 3- C locked" << endl;

    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "Thread 3- trying to lock A" << endl;
    resourceA.lock();
    cout << "Thread 3- A locked" << endl;

    resourceA.unlock();
    resourceC.unlock();
    cout << "Thread 3- released C and A" << endl;
}
int main() {
    thread t1(thread1);
    thread t2(thread2);
    thread t3(thread3);

    t1.join();
    t2.join();
    t3.join();

    cout << "Done." << endl;
    return 0;
}
