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

#ifndef TALISKER_INTERNAL_XCB_CONTROL_HH_
# define TALISKER_INTERNAL_XCB_CONTROL_HH_ 1

# include <Talisker/Object.hh>
# include <Talisker/Coordinates.hh>
# include <Talisker/IControl.h>
# include <Talisker/Internal/XCB/Display.hh>

namespace Talisker
{
	namespace Internal
	{
		namespace XCB
		{
			class Control: virtual public IControl, public Object
			{
			public:
				Display *m_display;
				xcb_window_t m_window;

				Control(Control *parent);
				virtual ~Control();

				virtual xcb_window_t windowId();
				virtual IControl *outer(void);
				virtual void setOuter(IControl *outer);

				/* IObject */
				virtual int __stdcall queryInterface(const uuid_t riid, void **object);
				/* IControl */
				virtual bool __stdcall visible(void);
				virtual void __stdcall setVisible(bool visible);
				virtual TaliskerEventMask __stdcall eventMask(void);
				virtual void __stdcall setEventMask(TaliskerEventMask mask);
				virtual bool __stdcall dispatchEvent(IEvent *event);
				virtual void __stdcall drawRect(Talisker::Rect rect);
			protected:
				uint8_t m_depth;
				Control *m_parent;
				Rect m_rect;
				uint16_t m_border;
				uint16_t m_class;
				xcb_visualid_t m_visual;
				bool m_visible;
				TaliskerEventMask m_eventMask;
				IControl *m_outer;

				virtual bool createWindow();				
			};
		};
	};
};

#endif /*!TALISKER_INTERNAL_XCB_CONTROL_HH_*/
