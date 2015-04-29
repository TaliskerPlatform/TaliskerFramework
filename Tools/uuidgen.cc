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
#include <unistd.h>
#include <string.h>
#include <Talisker/Talisker.h>

using namespace Talisker;

const char *short_program_name = "uuidgen";

static size_t gen_count = 1;
static int gen_sequential;
static int out_idl, out_upper, out_define, out_compact;

static void
usage(void)
{
	printf("Usage: %s [OPTIONS]\n"
		   "\n"
		   "OPTIONS is one or more of:\n"
		   "-h                  Print this usage message and exit\n"
		   "-x                  Generate time-based UUID\n"
		   "-i                  Generate an IDL interface template\n"
		   "-s                  Write a C UUID_DEFINE() statement\n"
		   "-n COUNT            Generate COUNT UUIDs\n"
		   "-c                  Output in upper-case\n"
		   "-z                  Output in compact form (no dashes)\n",
		   short_program_name);
}

int
main(int argc, char **argv)
{
	int c;
	size_t n;
	const char *t;
	int flags;
	UUID *uu;
	String *s;
	const char *p;

	t = strrchr(argv[0], '/');
	if(t)
	{
		short_program_name = t + 1;
	}
	else
	{
		short_program_name = argv[0];
	}
	while((c = getopt(argc, argv, "hxisczn:")) != -1)
	{
		switch(c)
		{
		case 'h':
			usage();
			return 0;
		case 'x':
			gen_sequential = 1;
			break;
		case 'i':
			out_idl = 1;
			break;
		case 'c':
			out_upper = 1;
			break;
		case 's':
			out_define = 1;
			break;
		case 'z':
			out_compact = 1;
			break;
		case 'n':
			gen_count = strtoul(optarg, NULL, 10);
			if(!gen_count)
			{
				fprintf(stderr, "%s: invalid integer '%s'\n", short_program_name, optarg);
				return 1;
			}
			break;
		default:
			return 1;
		}
	}
	if(out_idl || out_define)
	{
		out_compact = 0;
	}
	if(out_idl && out_define)
	{
		fprintf(stderr, "%s: '-i' and '-s' options cannot both be specified\n", short_program_name);
		return 1;
	}
	flags = (out_upper ? UUID::upper : UUID::lower);
	if(out_compact)
	{
		flags |= UUID::compact;
	}
	for(n = 0; n < gen_count; n++)
	{
		uu = new UUID();
		s = uu->string(flags);
		if(out_idl)
		{
			printf("[uuid(%s)]\ninterface INTERFACE\n{\n}\n\n", s->c_str());
		}
		else if(out_define)
		{
			printf("/* %s */\nUUID_DEFINE(NAME, ", s->c_str());
			n = false;
			for(p = s->c_str(); *p; p += 2)
			{
				if(*p == '-')
				{
					p++;
				}
				if(n)
				{
					fputs(", 0x", stdout);
				}
				else
				{
					fputs("0x", stdout);
					n = true;
				}
				putchar(p[0]);
				putchar(p[1]);
			}
			puts(");\n");
		}
		else
		{
			printf("%s\n", s->c_str());
		}
		s->release();
		uu->release();
	}

	return 0;
}
