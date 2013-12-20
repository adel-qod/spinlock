// Copyright (c) 2013, Mhd Adel G. Al Qodamni
// All rights reserved - under BSD 2-clause license.
// Check the LICENSE file for the full text
#include <iostream>

#include "Spinlock.h"

Spinlock::Spinlock()
{
	lock_variable.store(false);
	// Since the onwer is not valid unless the Spinlock is locked, there's
	// no point in initializing it here - what would you set it to be?	
}

void Spinlock::lock()
{
	bool expected = false;
	bool desired = true;
	// if lock_variable = expected(false) then set it to desired(true)
	// else, loop again but set expected to false again since
	// compare_exchange_strong does: expected = desired when it fails
	while(!lock_variable.compare_exchange_strong(expected, desired))
		expected = false;
	owner.store(std::this_thread::get_id());
}

bool Spinlock::unlock()
{
	if(lock_variable.load())
		if(owner.load() == std::this_thread::get_id()) {
			lock_variable.store(false);
			return true;
		}
	return false;
}

Spinlock::~Spinlock()
{
	// To be safe
	lock_variable.store(false);
}
