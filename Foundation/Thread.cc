/* Copyright 2015 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "p_foundation.hh"

using namespace Talisker;

static pthread_once_t init_control = PTHREAD_ONCE_INIT;
static pthread_key_t thread_key;
static pthread_key_t allocator_key;

static void
talisker_thread_init(void)
{
	pthread_key_create(&thread_key, NULL);
	pthread_key_create(&allocator_key, NULL);
}

void *
operator new(size_t nbytes)
{
	IAllocator *allocator;

	allocator = Thread::allocator();
	return allocator->alloc(nbytes);
}

void
operator delete(void *ptr)
{
	IAllocator *allocator;

	allocator = Thread::allocator();
	allocator->free(ptr);
}

/* Obtain the Thread object for the current thread; the object must be
 * retained before it may be accessed by any other threads.
 */
Thread *
Thread::currentThread(void)
{
	pthread_t curthread;
	void *ptr;
	Thread *t;

	pthread_once(&init_control, talisker_thread_init);
	curthread = pthread_self();
	ptr = pthread_getspecific(thread_key);
	if(ptr)
	{
		return static_cast<Thread *>(ptr);
	}
	t = new Thread((unsigned long) curthread);
	pthread_setspecific(thread_key, (void *) t);
	return t;
}

/* Return true if the current thread is the main thread */
bool
Thread::currentIsMainThread(void)
{
#if defined(__linux__)
	if(syscall(SYS_gettid) == getpid())
	{
		return true;
	}
#endif
	return false;
}

/* Terminate the current thread */
void
Thread::exit(void)
{
	pthread_exit(NULL);
}

/* Return the allocator for this thread */
IAllocator *
Thread::allocator(void)
{
	IAllocator *allocator;

	pthread_once(&init_control, talisker_thread_init);

	allocator = static_cast<IAllocator *>(pthread_getspecific(allocator_key));
	if(!allocator)
	{
		allocator = DefaultAllocator::defaultAllocator();
		pthread_setspecific(allocator_key, (void *) allocator);
	}
	return allocator;
}

/* Create a new, dormant, thread object */
Thread::Thread():
	Object::Object(),
	m_running(false),
	m_id(0),
	m_isMainThread(false),
	m_allocator(NULL)
{
}

/* Create a new dormant thread object with a different allocator */
Thread::Thread(IAllocator *threadAllocator):
	Object::Object(),
	m_running(false),
	m_id(0),
	m_isMainThread(false),
	m_allocator(threadAllocator)
{
}

/* Internal: Create a new thread object for an existing thread */
Thread::Thread(unsigned long tid):
	Object::Object(),
	m_running(true),
	m_id(tid)
{
	m_isMainThread = currentIsMainThread();
}

/* Thread object destructor */
Thread::~Thread()
{
}

/* Start running a new thread */
void
Thread::start(void)
{
	if(m_running)
	{
		return;
	}
	pthread_once(&init_control, talisker_thread_init);
	/* TODO */
}

/* The implementation of a thread, invoked when the thread is started */
void
Thread::main(void)
{
	/* TODO */
}

/* Determine whether this is the main thread or not */
bool
Thread::isMainThread(void)
{
	return m_isMainThread;
}

/* Determine whether this is the same thread as the caller */
bool
Thread::isSelf(void)
{
	return ((pthread_t) m_id == pthread_self());
}

/* Determine whether this thread is running */
bool
Thread::running(void)
{
	return m_running;
}

