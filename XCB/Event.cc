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

Event::Event(Display *display, xcb_generic_event_t *xev):
	m_xev(xev),
	m_eventType(EVT_NOOP),
	m_rect(),
	m_control(NULL)
{
	xcb_expose_event_t *expose;

	switch(xev->response_type & ~0x80)
	{
	case XCB_EXPOSE:
		expose = (xcb_expose_event_t *) xev;
		m_control = display->controlForWindow(expose->window);
		m_eventType = EVT_DRAW;
		m_rect = Rect(expose->x, expose->y, expose->width, expose->height, display->dpi());
		break;
	}
}

Event::~Event()
{
	free(m_xev);
}

/* IObject */
int __stdcall
Event::queryInterface(const uuid_t riid, void **object)
{
	if(!uuid_compare(riid, IID_IEvent))
	{
		IEvent *obj = static_cast<IEvent *>(this);

		obj->retain();
		*object = (void *) obj;
		return 0;
	}
	return Object::queryInterface(riid, object);
}

/* IEvent */
TaliskerEventType __stdcall
Event::eventType(void)
{
	return m_eventType;
}

IControl *__stdcall
Event::control(void)
{
	IControl *outer;

	if(m_control)
	{
		outer = m_control->outer();
		if(outer)
		{
			return outer;
		}
	}
	return m_control;
}
	   
Talisker::Rect __stdcall
Event::rect(void)
{
	return m_rect;
}
