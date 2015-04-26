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

#ifndef TALISKER_COORDINATES_HH_
# define TALISKER_COORDINATES_HH_       1

namespace Talisker {

	struct Point
	{
		float x;
		float y;
		
		Point();
		Point(float nx, float ny);
		Point(long nx, long ny, int dpi);
	};

	struct Bounds
	{
		float width;
		float height;

		Bounds();
		Bounds(float nx, float ny);
		Bounds(long nx, long ny, int dpi);
	};

	struct Rect
	{
		Point origin;
		Bounds bounds;

		Rect();
		Rect(Point &o, Bounds &b);
		Rect(float nx, float ny, float nw, float nh);
		Rect(long nx, long ny, long nw, long nh, int dpi);
	};
};

#endif /*!TALISKER_COORDINATES_HH_*/
