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
# include <Talisker/Factory.hh>
# include <Talisker/IApplication.h>
# include <Talisker/IFactory.h>

namespace Talisker
{

	int TALISKER_EXPORT_ ApplicationMain(int argc, char **argv);

	class TALISKER_EXPORT_ Application: virtual public IApplication, virtual public IApplicationDelegate, public Object
	{
	public:
		static IObject *constructor(void);
		static Application *sharedApplication(void);
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

/* f5235e89-4a83-4f4e-8b93-78ec5d544379 */
UUID_DEFINE(CLSID_Talisker_Application, 0xf5, 0x23, 0x5e, 0x89, 0x4a, 0x83, 0x4f, 0x4e, 0x8b, 0x93, 0x78, 0xec, 0x5d, 0x54, 0x43, 0x79);

#endif /*!TALISKER_APPLICATION_HH_*/
