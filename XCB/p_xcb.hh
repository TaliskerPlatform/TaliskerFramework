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

#ifndef P_XCB_HH_
# define P_XCB_HH_                      1

# define TALISKER_INTERNAL_             1

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include <xcb/xcb.h>

# include <Talisker/Talisker.h>

extern Talisker::Internal::XCB::Application *talisker_xcb_curapp_;

#endif /*!P_XCB_HH_*/
