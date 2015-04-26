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

#ifndef TALISKER_INTERNAL_INTERNAL_H_
# define TALISKER_INTERNAL_INTERNAL_H_ 1

# if !defined(TALISKER_INTERNAL_)
#  error This header should only be included by the Talisker framework itself.
# endif

# if defined(TALISKER_WITH_XCB)
#  include <Talisker/Internal/XCB/XCB.h>
# endif

#endif /*!TALISKER_INTERNAL_INTERNAL_H_*/
