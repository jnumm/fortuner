AC_INIT([Fortuner], [0.4.0])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/main.cpp])

AM_INIT_AUTOMAKE([foreign dist-xz no-dist-gzip -Wall])

IT_PROG_INTLTOOL([0.35.0])

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.18.3])

GETTEXT_PACKAGE=AC_PACKAGE_TARNAME
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"],
    [The domain to use with gettext])
AM_GLIB_GNU_GETTEXT

LOCALEDIR=[${datadir}/locale]
AC_SUBST(LOCALEDIR)

AC_PROG_CXX
AC_PROG_INSTALL
PKG_PROG_PKG_CONFIG

PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0])
PKG_CHECK_MODULES([LIBNOTIFY], [libnotify])

AC_CONFIG_FILES([Makefile doc/Makefile icons/Makefile misc/Makefile
    po/Makefile.in src/Makefile])
AC_OUTPUT
