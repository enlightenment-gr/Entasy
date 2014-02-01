AUTOMAKE_OPTIONS = subdir-objects
MAINTAINERCLEANFILES = Makefile.in

bin_PROGRAMS = entasy

entasy_CPPFLAGS = -I. \
-DPACKAGE_BIN_DIR=\"$(bindir)\" -DPACKAGE_LIB_DIR=\"$(libdir)\" \
-DPACKAGE_DATA_DIR=\"$(pkgdatadir)\" @ENTASY_CFLAGS@

entasy_LDADD = @ENTASY_LIBS@

entasy_SOURCES = \
entasy.h \
entasy_cb.c entasy_cb.h \
entasy_control_buttons.c entasy_control_buttons.h \
entasy_flipper.c entasy_flipper.h \
entasy_main.c \
entasy_sliders.c entasy_sliders.h \
entasy_tracklist.c entasy_tracklist.h

