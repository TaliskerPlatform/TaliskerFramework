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

#ifndef TALISKER_TALISKER_H_
# define TALISKER_TALISKER_H_           1

/* Foundation interfaces */
# include <Talisker/IObject.h>
# include <Talisker/IAllocator.h>
# include <Talisker/IFactory.h>

/* UI interfaces */
# include <Talisker/IApplication.h>
# include <Talisker/IApplicationDelegate.h>
# include <Talisker/IEvent.h>
# include <Talisker/IControl.h>

# if defined(__cplusplus)

/* Foundation */
#  include <Talisker/Object.hh>
#  include <Talisker/Factory.hh>
#  include <Talisker/DefaultAllocator.hh>
#  include <Talisker/Process.hh>
#  include <Talisker/Thread.hh>
#  include <Talisker/String.hh>
#  include <Talisker/URI.hh>

/* UI */
#  include <Talisker/Coordinates.hh>
#  include <Talisker/Application.hh>
#  include <Talisker/Control.hh>
#  include <Talisker/Window.hh>

# endif /*__cplusplus*/

# if defined(TALISKER_INTERNAL_)
#  include <Talisker/Internal/Internal.h>
# endif

#endif /*!TALISKER_TALISKER_H_*/
