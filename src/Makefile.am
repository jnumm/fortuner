AM_CPPFLAGS = -DLOCALEDIR=\"$(LOCALEDIR)\" $(GTKMM_CFLAGS) \
    $(LIBNOTIFY_CFLAGS)

bin_PROGRAMS = fortuner

fortuner_SOURCES = aboutdialog.cpp \
    aboutdialog.h \
    fortuner.cpp \
    fortuner.h \
    gettext.h \
    main.cpp \
    settings.cpp \
    settings.h \
    statusicon.cpp \
    statusicon.h

fortuner_LDADD = $(GTKMM_LIBS) $(LIBNOTIFY_LIBS)
