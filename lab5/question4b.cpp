#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex resourceA;
mutex resourceB;
mutex resourceC;

// Every thread tries to lock A, then B, then C in that order
// since we make them follow the same order for everyone there will no cycle and no deadlock yay
void safeWork(const string& name) {
    cout <<name <<" - trying to lock A"<< endl;
    resourceA.lock();
    cout << name << " - locked A" << endl;

    this_thread::sleep_for(chrono::milliseconds(100));

    cout << name<< " - trying to lock B" << endl;
    resourceB.lock();
    cout << name << " - locked B" << endl;

    this_thread::sleep_for(chrono::milliseconds(100));

    cout << name << " - trying to lock C" << endl;
    resourceC.lock();
    cout << name << " - locked C" << endl;

    cout << name << " - got all resources and is doing work" << endl;
    this_thread::sleep_for(chrono::milliseconds(200));

    resourceC.unlock();
    resourceB.unlock();
    resourceA.unlock();
    cout << name << " - released A B C" << endl;
}

int main() {
    // we are making the 3 thread but they follow same patern each.
    thread t1(safeWork, "Thread 1");
    thread t2(safeWork, "Thread 2");
    thread t3(safeWork, "Thread 3");

    t1.join();
    t2.join();
    t3.join();

    cout << "Program finished without deadlock yes maam" << endl;
    return 0;
}
