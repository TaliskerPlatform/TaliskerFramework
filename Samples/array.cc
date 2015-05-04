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

#include <stdio.h>
#include <stdlib.h>

#include <Talisker/Talisker.h>

static int
dumparray(Talisker::Array *a)
{
	const char *sep = "------------------------------------------------------------------------";
	size_t count, c;
	IObject *o;
	Talisker::String *s;

	count = a->count();
	if(count == 1)
	{
		puts("1 element:");
	}
	else
	{
		printf("%lu elements:\n", (unsigned long) count);
	}
	for(c = 0; c < count; c++)
	{
		o = a->objectAtIndex(c);
		if(!o)
		{
			fprintf(stderr, "index %lu is null\n", (unsigned long) c);
			return -1;
		}		
		s = dynamic_cast<Talisker::String *>(o);
		if(!s)
		{
			fprintf(stderr, "dynamic_cast(%lu) failed\n", (unsigned long) c);
			abort();
			return -1;
		}
		o->release();
		printf("%lu: '%s'\n", (unsigned long) c, s->c_str());
	}
	puts(sep);
	return 0;
}

static int
arraytest(void)
{
	Talisker::String s1("string 1"), s2("string 2"), s3("string 3");
	Talisker::Array a;

	a.addObject(&s1);
	dumparray(&a);

	a.addObject(&s2);
	dumparray(&a);

	a.removeAllObjects();
	return 0;
}	

int
main(int argc, char **argv)
{
	int r;

	(void) argc;
	(void) argv;

	fprintf(stderr, "array test:\n");
	r = arraytest();
	fprintf(stderr, "completed with status %d\n", r);
	return r;
}


