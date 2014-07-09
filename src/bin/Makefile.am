AUTOMAKE_OPTIONS = subdir-objects
MAINTAINERCLEANFILES = Makefile.in

bin_PROGRAMS = entasy

entasy_CPPFLAGS = -I. \
-DPACKAGE_BIN_DIR=\"$(bindir)\" -DPACKAGE_LIB_DIR=\"$(libdir)\" \
-DPACKAGE_DATA_DIR=\"$(pkgdatadir)\" @Entasy_CFLAGS@

entasy_SOURCES = \
entasy_cb.c entasy_cb.h \
entasy_control_buttons.c entasy_control_buttons.h \
entasy_flipper.c entasy_flipper.h \
entasy_sliders.c entasy_sliders.h \
entasy_tracklist.c entasy_tracklist.h \
entasy.h \
entasy_main.c

entasy_LDADD = @Entasy_LIBS@
