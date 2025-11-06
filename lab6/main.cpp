#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>
using namespace std;
const int max_Size = 3;
counting_semaphore<max_Size> emptySlots(max_Size);
counting_semaphore<max_Size> fullSlots(0);
binary_semaphore basketLock(1);
int basket[max_Size];
int inIndex = 0;
int outIndex = 0;
void snackProducer(int id) {
    int snackID = 1;
    while (true) {
        emptySlots.acquire();
        basketLock.acquire();
        basket[inIndex] = snackID;
        cout<<"Producer " << id << "added snack "<< snackID<< "inIndex=" << inIndex<<endl;
        inIndex = (inIndex + 1) % max_Size;
        snackID++;
        basketLock.release();
        fullSlots.release();
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

void snackConsumer(int id) {
    while (true) {
        fullSlots.acquire();
        basketLock.acquire();
        int snack = basket[outIndex];
        cout << "Consumer "<< id << "took snack "<< snack<< " outIndex=" << outIndex<<endl;
        outIndex = (outIndex + 1) % max_Size;
        basketLock.release();
        emptySlots.release();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}
int main() {
    thread p1(snackProducer, 1);
    thread p2(snackProducer, 2);
    thread c1(snackConsumer, 1);
    thread c2(snackConsumer, 2);
    p1.join();
    p2.join();
    c1.join();
    c2.join();
}
