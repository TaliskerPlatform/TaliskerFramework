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

#include <Talisker/Talisker.h>

int
main(int argc, char **argv)
{
	Talisker::String s("123456789012345"), *s1;
	
	(void) argc;
	(void) argv;

	printf("s = '%s'; s.length = %lu\n", s.c_str(), s.length());
	s1 = s.dup();
	printf("s1 = '%s'; s1.length = %lu\n", s1->c_str(), s1->length());
	*s1 = "hello, this is a test of string assignment.";
	printf("s1 = '%s'; s1.length = %lu\n", s1->c_str(), s1->length());
	s1->append(s);
	printf("s1 = '%s'; s1.length = %lu\n", s1->c_str(), s1->length());
	s1->remove(7, 18);
	printf("s1 = '%s'; s1.length = %lu\n", s1->c_str(), s1->length());
	s1->insert(" test", 24); 
	printf("s1 = '%s'; s1.length = %lu\n", s1->c_str(), s1->length());
	s1->insert(" ", 30);
	s1->insert("Yes, ");
	s1->append(".");
	printf("s1 = '%s'; s1.length = %lu\n", s1->c_str(), s1->length());
	delete s1;
	return 0;
}


