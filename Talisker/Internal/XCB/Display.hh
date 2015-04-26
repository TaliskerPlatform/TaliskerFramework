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

#ifndef TALISKER_INTERNAL_XCB_DISPLAY_HH_
# define TALISKER_INTERNAL_XCB_DISPLAY_HH_ 1

# include <xcb/xcb.h>

# include <Talisker/Object.hh>

namespace Talisker
{
	namespace Internal
	{
		namespace XCB
		{
			class Control;

			struct ControlMap
			{
				xcb_window_t window;
				Control *control;
			};

			class Display: public Object
			{
			public:
				xcb_connection_t *m_connection;
				int m_screenid;
				const xcb_setup_t *m_setup;
				xcb_screen_t *m_screen;
				
				Display();
				virtual ~Display();

				bool connected();
			    uint32_t generateId(void);
				void flush(void);
				int dpi(void);
				void registerControl(xcb_window_t window, Control *control);
				void unregisterControl(Control *control);
				Control *controlForWindow(xcb_window_t window);
			protected:
				ControlMap **m_map;
				size_t m_maplen, m_mapsize;
			};			
		};
	};
};

#endif /*!TALISKER_INTERNAL_XCB_DISPLAY_HH_*/
