/* Copyright 2012-2015 Mo McRoberts.
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

#include "p_foundation.hh"

using namespace Talisker;

Registry *Registry::m_sharedRegistry = NULL;

/* TODO: thread safety; allocator */

struct Talisker::FactoryEntry
{
	uuid_t clsid;
	IFactory *factory;
};

Registry *
Registry::sharedRegistry(void)
{
	if(!m_sharedRegistry)
	{
		m_sharedRegistry = new Registry();
	}
	return m_sharedRegistry;
}

Registry::Registry():
	Object::Object(),
	m_factories(NULL),
	m_fcount(0),
	m_fsize(0)
{
	m_refcount = -1;
}

Registry::~Registry()
{
	size_t c;
	
	for(c = 0; c < m_fcount; c++)
	{
		m_factories[c].factory->release();
	}
	free(m_factories);
}

int __stdcall
Registry::queryInterface(const uuid_t riid, void **object)
{
	if(!uuid_compare(riid, IID_IRegistry))
	{
		*object = static_cast<IRegistry *>(this);
		return 0;
	}
	return Object::queryInterface(riid, object);
}

int __stdcall
Registry::registerFactory(const uuid_t clsid, IFactory *factory)
{
	size_t c;
	UUID uu(clsid);
	String *s;
	FactoryEntry *p;

	for(c = 0; c < m_fcount; c++)
	{
		if(!uuid_compare(m_factories[c].clsid, clsid))
		{
			s = uu.string();
			Talisker::notice("Registry: ignored attempt to register a factory for {%s} more than once\n", s->c_str());
			s->release();
			return -1;
		}
	}
	if(m_fcount + 1 > m_fsize)
	{
		p = (FactoryEntry *) realloc(m_factories, sizeof(FactoryEntry) * (m_fsize + 8));
		if(!p)
		{
			return -1;
		}
		m_factories = p;
		m_fsize += 8;
	}
	factory->retain();
	memcpy(m_factories[m_fcount].clsid, clsid, sizeof(uuid_t));
	m_factories[m_fcount].factory = factory;
	m_fcount++;
	return 0;
}

int __stdcall
Registry::unregisterFactory(const uuid_t clsid, IFactory *factory)
{
	size_t c;
	UUID uu(clsid);
	String *s;
	
	for(c = 0; c < m_fcount; c++)
	{
		if(!uuid_compare(m_factories[c].clsid, clsid))
		{
			if(m_factories[c].factory != factory)
			{
				s = uu.string();
				Talisker::notice("Registry: ignored attempt to unregister a factory for {%s} which was registered with a different factory\n", s->c_str());
				s->release();
				return -1;
			}
			m_factories[c].factory->release();
			if(c + 1 < m_fcount)
			{
				memmove(&(m_factories[c]), &(m_factories[c + 1]), sizeof(FactoryEntry) * (m_fcount - c - 1));
			}
			return 0;
		}
	}
	s = uu.string();
	Talisker::notice("Registry: ignored attempt to unregister a factory for {%s} which is not registered\n", s->c_str());
	s->release();
	return -1;
}

IFactory *__stdcall
Registry::factory(const uuid_t clsid)
{
	size_t c;

	for(c = 0; c < m_fcount; c++)
	{
		if(!uuid_compare(m_factories[c].clsid, clsid))
		{
			m_factories[c].factory->retain();
			return m_factories[c].factory;
		}
	}
	return NULL;
}
