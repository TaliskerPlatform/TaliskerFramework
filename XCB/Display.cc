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

Display::Display():
	Object::Object(),
	m_connection(NULL),
	m_screenid(0),
	m_setup(NULL),
	m_screen(NULL),
	m_map(NULL),
	m_maplen(0),
	m_mapsize(0)
{
	int c;
	xcb_screen_iterator_t iter;

	m_connection = xcb_connect(NULL, &m_screenid);
	if(!m_connection)
	{
		return;
	}
	if(xcb_connection_has_error(m_connection))
	{
		xcb_disconnect(m_connection);
		m_connection = NULL;
		return;
	}
	m_setup = xcb_get_setup(m_connection);
	iter = xcb_setup_roots_iterator(m_setup);
	for(c = 0; c < m_screenid; c++)
	{
		xcb_screen_next(&iter);
	}
	m_screen = iter.data;
	Talisker::debug("[XCB::Display] connected to display, screen DPI is %d\n", dpi());
}

Display::~Display()
{
	if(m_connection)
	{
		xcb_disconnect(m_connection);
	}
}

bool
Display::connected()
{
	return (m_connection == NULL ? false : true);
}

uint32_t
Display::generateId(void)
{
	return xcb_generate_id(m_connection);
}

void
Display::flush(void)
{
	xcb_flush(m_connection);
}

int
Display::dpi(void)
{
	return (double) m_screen->height_in_pixels * 25.4 / (double) m_screen->height_in_millimeters;
}

void
Display::registerControl(xcb_window_t window, Control *control)
{
	ControlMap *entry;
	ControlMap **p;
	size_t l;
	
	entry = new ControlMap();
	entry->window = window;
	entry->control = control;
	if(m_maplen + 1 > m_mapsize)
	{
		l = m_mapsize + 16;
		/* TODO: use thread allocator; thread safety */
		p = (ControlMap **) realloc(m_map, l * sizeof(ControlMap *));
		if(!p)
		{
			delete entry;
			return;
		}
		m_map = p;
		m_mapsize = l;
	}
	m_map[m_maplen] = entry;
	m_maplen++;
}

void
Display::unregisterControl(Control *control)
{
	size_t c;
	
	for(c = 0; c < m_maplen; c++)
	{
		if(m_map[c]->control == control)
		{
			m_maplen--;
			if(m_maplen > c)
			{
				delete m_map[c];
				memmove(&(m_map[c]), &(m_map[c + 1]), sizeof(ControlMap *) * (m_maplen - c));
				return;
			}
		}
	}
}

Control *
Display::controlForWindow(xcb_window_t window)
{
	size_t c;
	
	for(c = 0; c < m_maplen; c++)
	{
		if(m_map[c]->window == window)
		{
			return m_map[c]->control;
		}
	}
	Talisker::notice("failed to locate control for window 0x%08x\n", window);
	return NULL;
}
