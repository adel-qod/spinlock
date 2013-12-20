#include <iostream>
#include <thread>
#include <mutex>

#include "Spinlock.h"

unsigned int counter;
Spinlock spin;
std::mutex mutex;
const int T_COUNT = 2;

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
	//spin.lock();
	std::cout<<"Hello!\n";
	// Since I won't lock it, only one thread should print the msg
}

int main()
{
	std::thread t[T_COUNT];
	for(int i = 0; i < T_COUNT; i++)
		t[i] = std::thread(count);
	for(int i = 0; i < T_COUNT; i++)
		t[i].join();
	std::cout<<counter<<std::endl;
	std::thread t1(lock_test);
	std::thread t2(lock_test);
	t1.join();
	t2.join();
	return 0;
}
