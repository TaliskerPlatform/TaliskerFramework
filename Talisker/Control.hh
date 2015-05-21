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

#ifndef TALISKER_CONTROL_HH_
# define TALISKER_CONTROL_HH_           1

# include <Talisker/Object.hh>
# include <Talisker/IControl.h>

namespace Talisker
{
	class TALISKER_EXPORT_ Control: virtual public IControl, public Object
	{
	public:
		Control(Control *parent = NULL);
		virtual ~Control();

		/* IObject */
		virtual int __stdcall queryInterface(const uuid_t riid, void **object);

		/* IControl */
		virtual bool __stdcall visible(void);
		virtual void __stdcall setVisible(bool visible);
		virtual TaliskerEventMask __stdcall eventMask(void);
		virtual void __stdcall setEventMask(TaliskerEventMask mask);
		virtual bool __stdcall dispatchEvent(IEvent *ev);
		virtual void __stdcall drawRect(Rect rect);
	protected:
		IControl *m_aggregate;
	};	
};

#endif /*!TALISKER_CONTROL_HH_*/
