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

#include <stdio.h>
#include <stdlib.h>

#define TALISKER_INTERNAL_              1

#include <Talisker/Talisker.h>

/* It's important that certain things are initialised before anything else
 * gets the opportunity to do so. In particular, the default allocator
 * really needs to be up and running before we attempt to use new or
 * delete.
 *
 * Once absolutely critical aspects of the framework have been initialised,
 * we also take the opportunity to register constructors and factories
 * in the process-local registry.
 */

using namespace Talisker;

extern "C" void __attribute__((constructor))
talisker_init_(int argc, char **argv, char **envp)
{
	IRegistry *registry;
	IAllocator *allocator;
	Thread *thread;

	talisker_init_thread_pre_();
	talisker_init_process_(argc, argv, envp);
	talisker_init_allocator_();
	allocator = DefaultAllocator::defaultAllocator();	
	talisker_init_thread_();
	thread = Thread::currentThread();
	if(!thread->isMainThread())
	{
		Talisker::warn("Talisker framework was not initialised on the main thread; some functionality may not behave as expected\n");
	}
	/* Register any constructors or factories */
	registry = Registry::sharedRegistry();
	registry->registerConstructor(CLSID_Talisker_Application, Application::constructor);
}

extern "C" void __attribute__((destructor))
talisker_fini_(void)
{
	IRegistry *registry;

	registry = Registry::sharedRegistry();
	registry->unregisterConstructor(CLSID_Talisker_Application, Application::constructor);

	talisker_fini_app_();
	talisker_fini_registry_();
	talisker_fini_process_();
	/* Any destructors from this point on use the failsafe new/delete */
	talisker_fini_thread_pre_();	
	talisker_fini_allocator_();
	talisker_fini_thread_();
}
