/* DO NOT EDIT: Automatically generated from IEvent.idl by idl */

#ifndef IEvent_FWD_DEFINED
# define IEvent_FWD_DEFINED
typedef struct IEvent IEvent;
#endif

#ifndef IEVENT_H_IDL_
# define IEVENT_H_IDL_

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
# include <Talisker/IObject.h>

/* IEvent version 0.0 */

# ifndef __IEvent_INTERFACE_DEFINED__
#  define __IEvent_INTERFACE_DEFINED__
#if defined(__cplusplus)
# include <Talisker/Coordinates.hh>
typedef Talisker::Rect TaliskerRect;
#else
typedef struct 
{
	float x;
	float y;
}  TaliskerPoint;
typedef struct 
{
	float width;
	float height;
}  TaliskerBounds;
typedef struct 
{
	TaliskerPoint origin;
	TaliskerBounds bounds;
}  TaliskerRect;
#endif /*!__cplusplus*/
typedef enum 
{
	 	EVM_DRAW = (1<<0)
}  TaliskerEventMask;
typedef enum 
{
	 	EVT_NOOP,
	 	EVT_DRAW
}  TaliskerEventType;
#include <Talisker/IControl.h>
#  undef INTEFACE
#  define INTERFACE IEvent


DECLARE_INTERFACE_(IEvent, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IEvent */
	STDMETHOD_(TaliskerEventType, eventType)(THIS) PURE;
	STDMETHOD_(IControl*, control)(THIS) PURE;
	STDMETHOD_(TaliskerRect, rect)(THIS) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IEvent_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IEvent_retain(__this) __this->lpVtbl->retain(__this)
#   define IEvent_release(__this) __this->lpVtbl->release(__this)
#   define IEvent_eventType(__this) __this->lpVtbl->eventType(__this)
#   define IEvent_control(__this) __this->lpVtbl->control(__this)
#   define IEvent_rect(__this) __this->lpVtbl->rect(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IEvent_INTERFACE_DEFINED__*/


/* IID_IEvent = {7d36bed4-bcc6-45a9-bc65-49db7b35a42c} */
UUID_DEFINE(IID_IEvent, 0x7d, 0x36, 0xbe, 0xd4,  0xbc, 0xc6, 0x45, 0xa9, 0xbc, 0x65, 0x49, 0xdb, 0x7b, 0x35, 0xa4, 0x2c);

#endif /*!IEVENT_H_IDL_*/
