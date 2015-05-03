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

static uint32_t
get_xcb_event_mask(TaliskerEventMask mask)
{
	uint32_t xmask;

	xmask = 0;
	if(mask & EVM_DRAW)
	{
		xmask |= XCB_EVENT_MASK_EXPOSURE;
	}
	return xmask;
}

Control::Control(Control *parent):
	Object::Object(),
	m_display(NULL),
	m_window(0),
	m_depth(XCB_COPY_FROM_PARENT),
	m_parent(parent),
	m_border(0),
	m_class(XCB_WINDOW_CLASS_INPUT_OUTPUT),
	m_visual(XCB_COPY_FROM_PARENT),
	m_visible(false),
	m_eventMask(EVM_DRAW),
	m_outer(NULL)
{
	if(parent)
	{
		m_display = parent->m_display;
	}
	else
	{
		m_display = Application::sharedApplication()->m_display;
	}
	m_display->retain();
	m_rect = Rect(0, 0, 100, 100, m_display->dpi());
}

Control::~Control()
{
	if(m_window)
	{
		m_display->unregisterControl(this);
		xcb_destroy_window(m_display->m_connection, m_window);
	}
	m_display->release();
}

bool
Control::createWindow(void)
{
	xcb_window_t parent;
	uint32_t values[16];
	uint32_t mask;

	if(m_parent)
	{
		parent = m_parent->windowId();
	}
	else
	{
		parent = m_display->m_screen->root;
	}
	m_window = m_display->generateId();
	mask = XCB_CW_EVENT_MASK;
	values[0] = get_xcb_event_mask(m_eventMask);
	xcb_create_window(m_display->m_connection,
					  m_depth,
					  m_window,
					  parent,
					  m_rect.origin.x, m_rect.origin.y,
					  m_rect.bounds.width, m_rect.bounds.height,
					  m_border,
					  m_class,
					  m_visual,
					  mask,
					  values);
	m_display->registerControl(m_window, this);
	return true;
}

xcb_window_t
Control::windowId(void)
{
	if(!m_window)
	{
		createWindow();
	}
	return m_window;
}

IControl *
Control::outer(void)
{
	return m_outer;
}

void
Control::setOuter(IControl *outer)
{
	m_outer = outer;
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
	return m_visible;
}

void
Control::setVisible(bool visible)
{
	if(!m_window)
	{
		if(!createWindow())
		{
			Talisker::err("[XCB::Control] failed to create window\n");
			return;
		}
	}
	if(m_visible == visible)
	{
		return;
	}
	if(visible)
	{
		xcb_map_window(m_display->m_connection, m_window);		
	}
	else
	{
		xcb_unmap_window(m_display->m_connection, m_window);
	}
	m_visible = visible;
}

TaliskerEventMask __stdcall
Control::eventMask(void)
{
	return m_eventMask;
}

void __stdcall
Control::setEventMask(TaliskerEventMask eventMask)
{
	uint32_t values[1];
	
	m_eventMask = eventMask;
	if(m_window)
	{
		values[0] = get_xcb_event_mask(eventMask);
		xcb_change_window_attributes(m_display->m_connection, m_window, XCB_CW_EVENT_MASK, values);
	}
}

bool __stdcall
Control::dispatchEvent(IEvent *ev)
{
	TaliskerEventType type;

	type = ev->eventType();
	switch(type)
	{
	case EVT_NOOP:
		return true;
	case EVT_DRAW:
		m_outer->drawRect(ev->rect());
		return true;
	default:
		Talisker::debug("Control received an event which was not handled (%d)\n", (int) type);
	}
	return true;
}

void __stdcall
Control::drawRect(Talisker::Rect rect)
{
	Talisker::debug("will redraw (%f, %f)-(%f, %f)\n", rect.origin.x, rect.origin.y, rect.bounds.width, rect.bounds.height);
}
