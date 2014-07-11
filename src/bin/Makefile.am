AUTOMAKE_OPTIONS = subdir-objects
MAINTAINERCLEANFILES = Makefile.in

bin_PROGRAMS = entasy

entasy_CPPFLAGS = -I. \
-DPACKAGE_BIN_DIR=\"$(bindir)\" -DPACKAGE_LIB_DIR=\"$(libdir)\" \
-DPACKAGE_DATA_DIR=\"$(pkgdatadir)\" @Entasy_CFLAGS@

entasy_SOURCES = \
entasy_cb.c entasy_cb.h \
entasy_ui.c entasy_ui.h \
entasy.h \
entasy_main.c

entasy_LDADD = @Entasy_LIBS@
