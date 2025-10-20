#include <iostream>
#include <csignal>
#include <unistd.h>
#include <cstdlib>
using namespace std;
void signalHandler(int signalNum) {
    cout <<"Interupt signal recieved exciting safely: "<< endl;
    exit(0);
}
int main() {
    signal(SIGINT, signalHandler);
    cout << "Waiting for user intterupt (Ctlr + C ): " << endl;
    while (true) {
        pause(); //did not work on windows but i did see on stack overflow it works on everything else. such as mac linux and ubuntu/unix.
    }
    return 0;
}
