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

#include "p_ui.hh"

using namespace Talisker;

/* Initialise a point at (0, 0) */
Point::Point():
	x(0),
	y(0)
{
}

/* Initialise a point at (nx, ny) */
Point::Point(float nx, float ny):
	x(nx),
	y(ny)
{
}

/* Initialise a point, converting pixel-coordinate values nx, ny */
Point::Point(long nx, long ny, int dpi)
{
	x = (float) (nx * dpi) / 72;
	y = (float) (ny * dpi) / 72;
}

/* Initialise bounds as (0, 0) */
Bounds::Bounds():
	width(0),
	height(0)
{
}

/* Initialise bounds as (nx, ny) */
Bounds::Bounds(float nx, float ny):
	width(nx),
	height(ny)
{
}

/* Initialise bounds, converting pixel-coordinate values nx, ny */
Bounds::Bounds(long nx, long ny, int dpi)
{
	width = (float) (nx * dpi) / 72;
	height = (float) (ny * dpi) / 72;
}

/* Initialise a rectangle as (0, 0)-(0, 0) */
Rect::Rect():
	origin(),
	bounds()
{
}

/* Initialise a rectangle as (o)-(b) */
Rect::Rect(Point &o, Bounds &b):
	origin(o),
	bounds(b)
{
}

/* Initialise a rectangle as (nx, ny)-(nw, nh) */
Rect::Rect(float nx, float ny, float nw, float nh):
	origin(nx, ny),
	bounds(nw, nh)
{
}

/* Initialise a rectangle, converting pixel coordinates */
Rect::Rect(long nx, long ny, long nw, long nh, int dpi):
	origin(nx, ny, dpi),
	bounds(nw, nh, dpi)
{
}
