/*
Copyright (c) 2013, Mhd Adel G. Al Qodamni
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:


Redistributions of source code must retain the above copyright notice, 
this list of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation 
and/or other materials provided with the distribution.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGE.
*/

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
