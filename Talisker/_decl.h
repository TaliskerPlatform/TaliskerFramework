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

#ifndef TALISKER__DECL_H_
# define TALISKER__DECL_H_              1

# if defined(__cplusplus)
#  define DECLARE_INTERFACE(name) \
	struct name
#  define DECLARE_INTERFACE_(name, parent) \
	struct name: virtual public parent
#  define BEGIN_INTERFACE
#  define END_INTERFACE
#  define THIS
#  define THIS_
#  define PURE = 0
#  define STDMETHOD_(type, name) \
	virtual type __stdcall name
#  define STDMETHOD(name) \
	STDMETHOD(int, name)
# else /*__cplusplus*/
#  define DECLARE_INTERFACE(name) \
	struct name { \
		struct name##_vtable_ *lpVtbl; \
	}; \
	struct name##_vtable_
#  define DECLARE_INTERFACE_(name, parent) \
	DECLARE_INTERFACE(name)
#  define BEGIN_INTERFACE
#  define END_INTERFACE
#  define THIS \
	struct INTERFACE *self
#  define THIS_ \
	struct INTERFACE *self,
#  define PURE
#  define STDMETHOD_(type, name) \
	type __stdcall (*name)
#  define STDMETHOD(name) \
	STDMETHOD(int, name)
# endif /*__cplusplus*/

# undef TALISKER_EXPORT_
# if defined(_WIN32) || defined(__CYGWIN__)
#  ifdef TALISKER_INTERNAL_
#   define TALISKER_EXPORT_             __declspec(dllexport)
#  else
#   define TALISKER_EXPORT_             __declspec(dllimport)
#  endif
# else /*_WIN32 || __CYGWIN*/
#  if defined(TALISKER_INTERNAL_) && __GNUC__ >= 4
#   define TALISKER_EXPORT_             __attribute__((visibility("default")))
#  else
#   define TALISKER_EXPORT_
#  endif
# endif

#endif /*!TALKISKER__DECL_H_*/
