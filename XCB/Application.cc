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

#include "p_xcb.hh"

using namespace Talisker::Internal::XCB;

Application *Application::m_sharedApp = NULL;

Application *
Application::sharedApplication()
{
	if(!m_sharedApp)
	{
		m_sharedApp = new Application();
		m_sharedApp->m_process = Process::self();
	}
	return m_sharedApp;
}

Application::Application():
	Object::Object(),
	m_display(NULL),
	m_outer(NULL),
	m_delegate(NULL),
	m_process(NULL),
	m_running(0)
{
	Talisker::debug("[XCB::Application::Application]\n");
}

Application::~Application()
{
	if(this == m_sharedApp)
	{
		m_sharedApp = NULL;
	}
	if(m_process)
	{
		m_process->release();
	}
	if(m_display)
	{
		m_display->release();
	}
	Talisker::debug("[XCB::Application::~Application]\n");
}

Talisker::Application *
Application::outer(void)
{
	return m_outer;
}

void
Application::setOuter(Talisker::Application *outer)
{
	m_outer = outer;
	if(!m_delegate)
	{
		setDelegate(outer);
	}
}

bool
Application::connectToDisplay(void)
{
	if(m_display)
	{
		return true;
	}
	m_display = new Display();
	if(!m_display->connected())
	{
		m_display->release();
		m_display = NULL;
		return false;
	}
	return true;
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
	return m_delegate;
}

void __stdcall
Application::setDelegate(IApplicationDelegate *delegate)
{
	m_delegate = delegate;
}

void __stdcall
Application::run(void)
{
	if(!m_display)
	{
		if(!connectToDisplay())
		{
			Talisker::err("Failed to connect to X server\n");
			exit(EXIT_FAILURE);
		}		
	}
	m_outer->finishLaunching();
	m_running = true;	
	m_terminated = false;
	do
	{
		IEvent *ev;
		
		ev = m_outer->nextEvent();
		if(!ev)
		{			
			break;
		}
		m_outer->dispatchEvent(ev);
		m_display->flush();
		ev->release();
	}
	while(!m_terminated);
	m_running = false;
}

void __stdcall
Application::stop(void)
{
	m_running = false;
}

void __stdcall
Application::terminate(void)
{
	m_terminated = true;
}

bool __stdcall
Application::running(void)
{
	return m_running;
}

void __stdcall
Application::finishLaunching(void)
{
	if(!m_delegate)
	{
		return;
	}
	m_delegate->finishedLaunching(m_outer);
	m_display->flush();
}

IEvent *__stdcall
Application::nextEvent(void)
{
	xcb_generic_event_t *xev;

	xev = xcb_wait_for_event(m_display->m_connection);
	if(!xev)
	{
		return NULL;
	}
	return new Event(m_display, xev);
}

bool __stdcall
Application::dispatchEvent(IEvent *ev)
{
	IControl *control;
	
	(void) ev;

	control = ev->control();
	if(control)
	{
		return control->dispatchEvent(ev);
	}
	return true;
}
