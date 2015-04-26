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

#ifndef TALISKER_INTERNAL_XCB_APPLICATION_HH_
# define TALISKER_INTERNAL_XCB_APPLICATION_HH_ 1

# include <Talisker/Object.hh>
# include <Talisker/Process.hh>
# include <Talisker/IApplication.h>
# include <Talisker/IEvent.h>
# include <Talisker/Internal/XCB/Display.hh>
# include <Talisker/Internal/XCB/Event.hh>

namespace Talisker
{
	namespace Internal
	{
		namespace XCB
		{
			class Application: virtual public IApplication, public Object
			{
			public:
				static Application *sharedApplication();
			protected:
				static Application *m_sharedApp;
			public:
				Display *m_display;

				Application();
				virtual ~Application();

				Talisker::Application *outer(void);
				void setOuter(Talisker::Application *outer);
				
				/* IObject */
				virtual int __stdcall queryInterface(const uuid_t riid, void **object);

				/* IApplication */
				virtual IApplicationDelegate *__stdcall delegate(void);
				virtual void __stdcall setDelegate(IApplicationDelegate *delegate);
				virtual void __stdcall run(void);
				virtual void __stdcall stop(void);
				virtual void __stdcall terminate(void);
				virtual bool __stdcall running(void);				
				virtual void __stdcall finishLaunching(void);
				virtual IEvent *__stdcall nextEvent(void);
				virtual bool __stdcall dispatchEvent(IEvent *event);
			protected:
				bool connectToDisplay(void);

				Talisker::Application *m_outer;
				IApplicationDelegate *m_delegate;
				Process *m_process;
				bool m_running;
				bool m_terminated;
			};
		};
	};
};

#endif /*!TALISKER_INTERNAL_XCB_APPLICATION_HH_*/
