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

Control::Control(Control *parent):
	Object::Object()
{
#ifdef TALISKER_WITH_XCB
	Talisker::Internal::XCB::Control *control, *p;

	if(parent)
	{
		p = dynamic_cast<Talisker::Internal::XCB::Control *>(parent->m_aggregate);
		if(!p)
		{
			Talisker::err("Invalid instance passed as parent to Control constructor\n");
			abort();
		}
	}
	else
	{
		p = NULL;
	}
	control = new Talisker::Internal::XCB::Control(p);
#else
# error No GUI implementation available
#endif
	m_aggregate = control;
	control->setOuter(this);
}

Control::~Control()
{
	m_aggregate->release();
}

/* IObject */

int __stdcall
Control::queryInterface(const uuid_t riid, void **object)
{
	if(!uuid_compare(riid, IID_IControl))
	{
		IControl *obj = static_cast<IControl *>(this);
		
		obj->retain();
		*object = (void *) obj;
		return 0;
	}
	return Object::queryInterface(riid, object);
}

/* IControl */

bool __stdcall
Control::visible(void)
{
	return m_aggregate->visible();
}

void __stdcall
Control::setVisible(bool visible)
{
	m_aggregate->setVisible(visible);
}

TaliskerEventMask __stdcall
Control::eventMask(void)
{
	return m_aggregate->eventMask();
}

void __stdcall
Control::setEventMask(TaliskerEventMask mask)
{
	m_aggregate->setEventMask(mask);
}

bool __stdcall
Control::dispatchEvent(IEvent *event)
{
	return m_aggregate->dispatchEvent(event);
}

void __stdcall
Control::drawRect(Rect rect)
{
	m_aggregate->drawRect(rect);
}
