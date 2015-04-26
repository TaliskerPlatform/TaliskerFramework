/* DO NOT EDIT: Automatically generated from IApplicationDelegate.idl by idl */

#ifndef IApplicationDelegate_FWD_DEFINED
# define IApplicationDelegate_FWD_DEFINED
typedef struct IApplicationDelegate IApplicationDelegate;
#endif

#ifndef IAPPLICATIONDELEGATE_H_IDL_
# define IAPPLICATIONDELEGATE_H_IDL_

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
# include <Talisker/IApplication.h>

/* IApplicationDelegate version 0.0 */

# ifndef __IApplicationDelegate_INTERFACE_DEFINED__
#  define __IApplicationDelegate_INTERFACE_DEFINED__
#  undef INTEFACE
#  define INTERFACE IApplicationDelegate


DECLARE_INTERFACE_(IApplicationDelegate, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IApplicationDelegate */
	STDMETHOD_(void, finishedLaunching)(THIS_ IApplication *app) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IApplicationDelegate_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IApplicationDelegate_retain(__this) __this->lpVtbl->retain(__this)
#   define IApplicationDelegate_release(__this) __this->lpVtbl->release(__this)
#   define IApplicationDelegate_finishedLaunching(__this, app) __this->lpVtbl->finishedLaunching(__this, app)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IApplicationDelegate_INTERFACE_DEFINED__*/


/* IID_IApplicationDelegate = {a6ee6d41-c3f6-49ad-b4ab-43cc36ffaaff} */
UUID_DEFINE(IID_IApplicationDelegate, 0xa6, 0xee, 0x6d, 0x41,  0xc3, 0xf6, 0x49, 0xad, 0xb4, 0xab, 0x43, 0xcc, 0x36, 0xff, 0xaa, 0xff);

#endif /*!IAPPLICATIONDELEGATE_H_IDL_*/
