#include <iostream>
#include <thread>
#include <mutex>

#include "Spinlock.h"

unsigned int counter;
Spinlock spin;
std::mutex mutex;
const int T_COUNT = 10;

void count()
{
    for(int i = 0; i < 5001000; i++) {
        spin.lock();
        counter++;
        spin.unlock();
    }
}

void lock_test()
{
    spin.lock();
    std::cout<<"Hello!\n";
    // Since I won't unlock it, only one thread should print the msg
}

void unlock_test()
{
    // This tests whether a thread can unlock a spinlock it doesn't
    // own. We'll need three threads; one to acquire the spinlock, one to 
    // actually block on it and a third one to try and release it
    spin.lock();
    std::cout<<"You should see this only once\n";
}

int main()
{
    std::thread t[T_COUNT];
    for(int i = 0; i < T_COUNT; i++)
        t[i] = std::thread(count);
    for(int i = 0; i < T_COUNT; i++)
        t[i].join();
    std::cout<<counter<<std::endl;

    // std::thread t1(lock_test);
    // std::thread t2(lock_test);
    // t1.join();
    // t2.join();

    //std::thread t3(unlock_test);
    //std::cout<<spin.unlock();
    //std::thread t4(unlock_test);
    //std::cout<<spin.unlock();
    //t3.join();
    //t4.join();

    return 0;
}
