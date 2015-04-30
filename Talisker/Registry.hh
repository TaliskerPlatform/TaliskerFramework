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

#ifndef TALISKER_REGISTRY_HH_
# define TALISKER_REGISTRY_HH_          1

# include <Talisker/Object.hh>
# include <Talisker/IRegistry.h>

namespace Talisker
{
	struct FactoryEntry;

	class Registry: virtual public IRegistry, public Object
	{
	public:
		static Registry *sharedRegistry(void);
	protected:
		static Registry *m_sharedRegistry;
	public:
		virtual ~Registry();
	
		virtual __stdcall int unregisterFactory(const uuid_t clsid, IFactory *factory);	
		virtual __stdcall IFactory *factory(const uuid_t clsid);

		/* IObject */
		virtual __stdcall int queryInterface(const uuid_t riid, void **object);
		
		/* IRegistry */
		virtual __stdcall int registerFactory(const uuid_t clsid, IFactory *factory);
	protected:
		FactoryEntry *m_factories;
		size_t m_fcount;
		size_t m_fsize;

		Registry();
	};
};

#endif /*!TALISKER_REGISTRY_HH_*/
