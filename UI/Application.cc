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

#include "p_ui.hh"

using namespace Talisker;

static Application *app = NULL;
static Control *test_control;

extern "C" void
talisker_fini_app_(void)
{
	if(app)
	{
		delete app;
		app = NULL;
	}
}

int
Talisker::ApplicationMain(int argc, char **argv)
{
	IApplication *app;
	Thread *thread;

	(void) argc;
	(void) argv;

	/* While we could invoke Thread::currentIsMainThread(), calling
	 * Thread::currentThread() ensures that the thread object has been
	 * constructed for the main thread if this is indeed the main
	 * thread.
	 */
	thread = Thread::currentThread();
	if(!thread->isMainThread())
	{
		Talisker::err("ApplicationMain not invoked on main thread\n");
		exit(EXIT_FAILURE);
	}
	/* TODO: allow application class to be overridden */
	if(Registry::sharedRegistry()->construct(CLSID_Talisker_Application, IID_IApplication, (void **) &app))
	{
		Talisker::err("Application factory failed to construct an IApplication instance\n");
		return 1;
	}
	/* TODO: now the application has been initialised, load UI resources */
	app->run();
	return 0;
}

IObject *
Application::constructor(void)
{
	return sharedApplication();
}

Application *
Application::sharedApplication(void)
{
#ifdef TALISKER_WITH_XCB
	Talisker::Internal::XCB::Application *aggregate;
#endif

	if(app)
	{
		return app;
	}
#ifdef TALISKER_WITH_XCB
	aggregate = new Talisker::Internal::XCB::Application();
#else
# error No GUI implementation available
#endif
	app = new Application(aggregate);
	app->m_refcount = -1;
	aggregate->setOuter(app);
	aggregate->release();
	return app;
}

Application::Application():
	Object::Object(),
	m_aggregate(NULL)
{
}

Application::Application(IApplication *aggregate):
	Object::Object(),
	m_aggregate(aggregate)
{
	m_aggregate->retain();
}

Application::~Application()
{
	if(app == this)
	{
		app = NULL;
	}
	if(m_aggregate)
	{
		m_aggregate->release();
	}
}

/* IObject */
int __stdcall
Application::queryInterface(const uuid_t riid, void **object)
{
	if(!uuid_compare(riid, IID_IApplication))
	{
		IApplication *obj = static_cast<IApplication *>(this);
		
		obj->retain();
		*object = (void *) obj;	  
		return 0;
	}
	return Object::queryInterface(riid, object);
}

/* IApplication */
IApplicationDelegate *__stdcall
Application::delegate(void)
{
	IApplicationDelegate *p;

	p = m_aggregate->delegate();
	if(p == this)
	{
		return NULL;
	}
	return p;
}

void __stdcall
Application::setDelegate(IApplicationDelegate *delegate)
{
	m_aggregate->setDelegate(delegate);
}

void __stdcall
Application::run(void)
{
	m_aggregate->run();
}

void __stdcall
Application::stop(void)
{
	m_aggregate->stop();
}

void __stdcall
Application::terminate(void)
{
	m_aggregate->terminate();
}

bool __stdcall
Application::running(void)
{
	return m_aggregate->running();
}

void __stdcall
Application::finishLaunching(void)
{
	m_aggregate->finishLaunching();
}

IEvent *__stdcall
Application::nextEvent(void)
{
	return m_aggregate->nextEvent();
}

bool
Application::dispatchEvent(IEvent *event)
{
	return m_aggregate->dispatchEvent(event);
}

/* IApplicationDelegate */
void __stdcall
Application::finishedLaunching(IApplication *app)
{
	(void) app;

	Talisker::debug("[Application::finishedLaunching]\n");
	test_control = new Control();
	test_control->setVisible(true);
}
