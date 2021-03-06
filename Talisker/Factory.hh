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

#ifndef TALISKER_FACTORY_HH_
# define TALISKER_FACTORY_HH_           1

# include <Talisker/Object.hh>
# include <Talisker/IFactory.h>

namespace Talisker
{
	class TALISKER_EXPORT_ Factory: virtual public IFactory, public Object
	{
	public:
		virtual ~Factory();
	
		/* IObject */
		virtual __stdcall int queryInterface(const uuid_t riid, void **object);
		
		/* IFactory */
		virtual __stdcall int createInstance(IObject *outer, const uuid_t iid, void **object);
		virtual __stdcall int lock(bool lock);
	protected:
		Factory();
	};
};

#endif /*!TALISKER_FACTORY_HH_*/
