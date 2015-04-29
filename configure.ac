## Copyright 2015 Mo McRoberts.
##
##  Licensed under the Apache License, Version 2.0 (the "License");
##  you may not use this file except in compliance with the License.
##  You may obtain a copy of the License at
##
##      http://www.apache.org/licenses/LICENSE-2.0
##
##  Unless required by applicable law or agreed to in writing, software
##  distributed under the License is distributed on an "AS IS" BASIS,
##  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
##  See the License for the specific language governing permissions and
##  limitations under the License.

AC_INIT([TaliskerFramework],[develop])

test x"$CPPFLAGS" = x"" && empty_cppflags=yes
test x"$CXXFLAGS" = x"" && empty_cxxflags=yes
test x"$CFLAGS" = x"" && empty_cflags=yes

AC_CONFIG_MACRO_DIR([m4])
AC_PREFIX_DEFAULT([/Preview])
AM_INIT_AUTOMAKE([foreign])
AM_MAINTAINER_MODE

AC_CONFIG_HEADER([config.h])

AC_PROG_LN_S
AC_PROG_CXX([clang++ g++ c++])
AC_CHECK_PROG([IDL],[idl],[idl],)
if test x"$IDL" = x"" ; then
	AC_MSG_ERROR([cannot find the Talisker IDL compiler, which is required to build the Talisker framework])
fi
LT_INIT

AM_CPPFLAGS="-I\${top_builddir} -I\${top_srcdir}"
AM_CPPFLAGS="$AM_CPPFLAGS -I\${top_builddir}/uriparser/include/uriparser -I\${top_srcdir}/uriparser/include/uriparser"

AC_SUBST([AM_CPPFLAGS])

if test x"$GCC" = x"yes" ; then
	test x"$empty_cppflags" = x"yes" && CPPFLAGS="$CPPFLAGS -W -Wall"
	test x"$empty_cflags" = x"yes" && CFLAGS="$CFLAGS -ggdb -O0"
	test x"$empty_cxxflags" = x"yes" && CXXFLAGS="$CXXFLAGS -ggdb -O0"
fi

gui_backend=none

PKG_CHECK_MODULES([XCB],[xcb],[gui_backend=xcb])

AC_SUBST([gui_backend])
AM_CONDITIONAL([WITH_XCB],[test x"$gui_backend" = x"xcb"])
if test x"$gui_backend" = x"xcb" ; then
	AC_DEFINE_UNQUOTED([TALISKER_WITH_XCB],[1],[Set if building with the XCB GUI back-end])
else
	AC_MSG_ERROR([no suitable GUI back-end could be determined])
fi

AC_CHECK_FUNC([uuid_generate],,[
	AC_CHECK_LIB([uuid],[uuid_generate],,[
		AC_MSG_ERROR([cannot locate UUID library (-luuid)])
	])
])


AC_CHECK_FUNC([pthread_create],,[
	AC_CHECK_LIB([pthread],[pthread_create],,[
		AC_MSG_ERROR([cannot locate POSIX threads library])
	])
])

PRIVATE_CONFIG_URIPARSER

AC_CONFIG_FILES([
Makefile
m4/Makefile
Talisker/Makefile
Talisker/Internal/Makefile
Talisker/Internal/XCB/Makefile
IDL/Makefile
Foundation/Makefile
UI/Makefile
XCB/Makefile
HelloApp/Makefile
])

AC_OUTPUT
