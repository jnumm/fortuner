applicationsdir = $(datarootdir)/applications
applications_in_files = fortuner.desktop.in
applications_DATA = $(applications_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST = $(applications_in_files)
DISTCLEANFILES = $(applications_DATA)
