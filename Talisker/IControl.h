/* DO NOT EDIT: Automatically generated from IControl.idl by idl */

#ifndef IControl_FWD_DEFINED
# define IControl_FWD_DEFINED
typedef struct IControl IControl;
#endif

#ifndef ICONTROL_H_IDL_
# define ICONTROL_H_IDL_

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
# include <Talisker/IEvent.h>

/* IControl version 0.0 */

# ifndef __IControl_INTERFACE_DEFINED__
#  define __IControl_INTERFACE_DEFINED__
#  undef INTEFACE
#  define INTERFACE IControl


DECLARE_INTERFACE_(IControl, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IControl */
	STDMETHOD_(bool, visible)(THIS) PURE;
	STDMETHOD_(void, setVisible)(THIS_ bool visible) PURE;
	STDMETHOD_(TaliskerEventMask, eventMask)(THIS) PURE;
	STDMETHOD_(void, setEventMask)(THIS_ TaliskerEventMask mask) PURE;
	STDMETHOD_(bool, dispatchEvent)(THIS_ IEvent *event) PURE;
	STDMETHOD_(void, drawRect)(THIS_ TaliskerRect rect) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IControl_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IControl_retain(__this) __this->lpVtbl->retain(__this)
#   define IControl_release(__this) __this->lpVtbl->release(__this)
#   define IControl_visible(__this) __this->lpVtbl->visible(__this)
#   define IControl_setVisible(__this, visible) __this->lpVtbl->setVisible(__this, visible)
#   define IControl_eventMask(__this) __this->lpVtbl->eventMask(__this)
#   define IControl_setEventMask(__this, mask) __this->lpVtbl->setEventMask(__this, mask)
#   define IControl_dispatchEvent(__this, event) __this->lpVtbl->dispatchEvent(__this, event)
#   define IControl_drawRect(__this, rect) __this->lpVtbl->drawRect(__this, rect)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IControl_INTERFACE_DEFINED__*/


/* IID_IControl = {bb522490-f8f6-4200-9f6b-ceb9d30014c5} */
UUID_DEFINE(IID_IControl, 0xbb, 0x52, 0x24, 0x90,  0xf8, 0xf6, 0x42, 0x00, 0x9f, 0x6b, 0xce, 0xb9, 0xd3, 0x00, 0x14, 0xc5);

#endif /*!ICONTROL_H_IDL_*/
