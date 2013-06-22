# Makefile for fortuner
# Copyright (C) 2013 Juhani Numminen <juhaninumminen0@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# GTKMM version to use. Can be set to either 2.4 or 3.0.
GTKMMVER = 2.4

# Compiler and linker flags.
CXX = g++
CXXFLAGS = -g -std=c++11 -pedantic -Wall -Wextra
CPPFLAGS = $(shell pkg-config --cflags libnotify gtkmm-$(GTKMMVER))
LDFLAGS = -g -Wl,--as-needed
LDLIBS = $(shell pkg-config --libs libnotify gtkmm-$(GTKMMVER))

# Install directories.
DESTDIR =
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
DATADIR = $(PREFIX)/share
LOCALEDIR = $(DATADIR)/locale
MANDIR = $(DATADIR)/man
XDG_DESKTOP_DIR = $(DATADIR)/applications
ICONDIR = $(DATADIR)/icons

# Available icon sizes.
ICONS = $(subst icons/,,$(wildcard icons/*))

# Object files to compile.
OBJS = $(subst .cpp,.o,$(wildcard src/*.cpp))

# Newline character.
define \n


endef

all: fortuner

fortuner: $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o fortuner

src/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

src/main.o: src/main.cpp src/config.h src/fortuner.h src/settings.h \
		src/gettext.h src/statusicon.h src/aboutdialog.h

src/settings.o: src/settings.cpp src/gettext.h src/settings.h

src/fortuner.o: src/fortuner.cpp src/fortuner.h src/settings.h \
		src/gettext.h

src/statusicon.o: src/statusicon.cpp src/gettext.h src/statusicon.h \
		src/aboutdialog.h src/fortuner.h src/settings.h

src/aboutdialog.o: src/aboutdialog.cpp src/aboutdialog.h src/config.h \
		src/gettext.h

src/config.h:
	sed -e "s/@PROJECT_NAME@/fortuner/" \
			-e "s/@VERSION_STRING@/0.4.0/" \
			-e "s/@LOCALEDIR@/\/usr\/share\/locale/" \
			src/config.h.in >src/config.h

install: fortuner
	install -d "$(DESTDIR)$(BINDIR)"
	install fortuner "$(DESTDIR)$(BINDIR)"

	desktop-file-install --dir="$(abspath $(DESTDIR)$(XDG_DESKTOP_DIR))" \
			misc/fortuner.desktop

	install -d "$(DESTDIR)$(MANDIR)/man6"
	install -m644 "doc/fortuner.6" "$(DESTDIR)$(MANDIR)/man6"
	gzip -9 "$(DESTDIR)$(MANDIR)/man6/fortuner.6"

ifneq ($(strip $(ICONS)),)
	# Create an icon directory for each size.
	install -d $(addprefix "$(DESTDIR)$(ICONDIR)/hicolor/,\
			$(addsuffix /apps",$(ICONS)))

	# Then install the actual icon.
	$(foreach size,$(ICONS),\
			install -m644 $(wildcard icons/$(size)/apps/*) \
			"$(DESTDIR)$(ICONDIR)/hicolor/$(size)/apps"$(\n))
endif

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f fortuner src/config.h
