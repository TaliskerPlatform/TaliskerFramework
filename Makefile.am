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

ACLOCAL_AMFLAGS = -I m4

dist_noinst_DATA = LICENSE-2.0 README.md

frameworkdir = $(prefix)/Library/Frameworks/Talisker.framework
fwlibdir = $(frameworkdir)/Versions/$(VERSION)/Libraries

DIST_SUBDIRS = Talisker IDL Foundation UI XCB uriparser m4 \
	Tools Samples

SUBDIRS = Talisker IDL Foundation UI uriparser

if WITH_XCB
SUBDIRS += XCB
endif

SUBDIRS += . Tools Samples

fwlib_LTLIBRARIES = libTalisker.la

libTalisker_la_SOURCES = stub.c

libTalisker_la_LIBADD = Foundation/libTaliskerFoundation.la \
	UI/libTaliskerUI.la

if WITH_XCB
libTalisker_la_LIBADD += XCB/libTaliskerXCB.la
endif

libTalisker_la_LIBADD += uriparser/liburiparser.la -luuid

libTalisker_la_LDFLAGS = -avoid-version

install-data-hook:
	$(MKDIR_P) '$(DESTDIR)$(frameworkdir)/Versions'
	cd $(DESTDIR)$(frameworkdir)/Versions && $(LN_S) $(VERSION) Current
	cd $(DESTDIR)$(frameworkdir) && $(LN_S) Versions/Current/Headers/Talisker Headers
	cd ($DESTDIR)$(frameworkdir) && $(LN_S) Versions/Current/Libraries/libTalisker.@shrext_cmds@ Talisker
