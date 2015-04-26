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

#ifndef TALISKER_APPLICATION_HH_
# define TALISKER_APPLICATION_HH_       1

# include <Talisker/Object.hh>
# include <Talisker/IApplication.h>

namespace Talisker
{

	int ApplicationMain(int argc, char **argv);

	class Application: virtual public IApplication, virtual public IApplicationDelegate, public Object
	{
	public:
		static Application *sharedApplication(void);
	protected:
		static Application *m_sharedApp;
	public:
		Application();
		virtual ~Application();

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

		/* IApplicationDelegate */
		virtual void __stdcall finishedLaunching(IApplication *app);
	protected:
		IApplication *m_aggregate;
		
		Application(IApplication *aggregate);
	};
	
};

#endif /*!TALISKER_APPLICATION_HH_*/
