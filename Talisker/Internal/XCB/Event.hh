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

#ifndef TALISKER_INTERNAL_XCB_EVENT_HH_
# define TALISKER_INTERNAL_XCB_EVENT_HH_ 1

# include <Talisker/IEvent.h>

namespace Talisker
{
	namespace Internal
	{
		namespace XCB
		{
			class Event: virtual public IEvent, public Object
			{
			public:
				Event(Display *display, xcb_generic_event_t *xev);
				~Event();
				
				/* IObject */
				virtual int __stdcall queryInterface(const uuid_t riid, void **object);
				/* IEvent */
				virtual TaliskerEventType __stdcall eventType(void);
				virtual IControl *__stdcall control(void);
				virtual Talisker::Rect __stdcall rect(void);
			protected:
				xcb_generic_event_t *m_xev;
				TaliskerEventType m_eventType;
				Rect m_rect;
				Control *m_control;
			};
		};
	};
};

#endif /*!TALISKER_INTERNAL_XCB_EVENT_HH_*/
