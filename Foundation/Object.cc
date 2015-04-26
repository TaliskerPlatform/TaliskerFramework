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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "p_foundation.hh"

using namespace Talisker;

Object::Object():
	m_refcount(1)
{
}

Object::~Object()
{
	if(m_refcount > 1)
	{
		Talisker::notice("[Object::~Object]: destroying object while dangling references exist\n");
	}
}

int __stdcall
Object::queryInterface(const uuid_t riid, void **object)
{
	if(!uuid_compare(riid, IID_IObject))
	{
		*object = static_cast<void *>(this);
		return 0;
	}
	return -1;
}

int32_t __stdcall
Object::retain(void)
{
	if(m_refcount < 0)
	{
		return 2;
	}
	m_refcount++;
	return m_refcount;
}

int32_t __stdcall
Object::release(void)
{
	if(m_refcount < 0)
	{
		return 1;
	}
	if(m_refcount < 2)
	{
		delete this;
		return 0;
	}
	m_refcount--;
	return m_refcount;
}
