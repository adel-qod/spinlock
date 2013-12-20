// Copyright (c) 2013, Mhd Adel G. Al Qodamni
// All rights reserved - under BSD 2-clause license.
// Check the LICENSE file for the full text


#ifndef HOME_ARAL_SPINLOCK_H
#define HOME_ARAL_SPINLOCK_H

#include <atomic>
#include <thread>

class Spinlock
{
public:
	Spinlock();
	Spinlock(const Spinlock &) = delete; 
	void lock();
	bool unlock();// Returns true only if called by the owner of lock
	Spinlock & operator=(const Spinlock &) = delete;
	~Spinlock();
private:
	std::atomic<bool> lock_variable;// true only if Spinlock's locked
	std::atomic<std::thread::id> owner;// valid only when lock_cond is true
};
#endif
