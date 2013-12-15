dnl Process this file with autoconf to produce a configure script.

# get rid of that stupid cache mechanism
rm -f config.cache

AC_INIT([Entasy], [0.0.1], [not-available-yet@example.com])
AC_PREREQ([2.60])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_HEADERS([Entasy_config.h])

AM_INIT_AUTOMAKE([1.6 dist-bzip2])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_USE_SYSTEM_EXTENSIONS
AC_PROG_CC
AM_PROG_CC_C_O
AC_C___ATTRIBUTE__

efl_version="1.8.0"
AC_SUBST(efl_version)

requirements="\
   elementary >= ${efl_version} \
   eina >= ${efl_version} \
   eet >= ${efl_version} \
   evas >= ${efl_version} \
   ecore >= ${efl_version} \
   ecore-evas >= ${efl_version} \
   ecore-file >= ${efl_version} \
   edje >= ${efl_version} \
   emotion >= ${efl_version} \
   ecore-input >= ${efl_version} \
   ecore-imf >= ${efl_version} \
   ecore-imf-evas >= ${efl_version} \
   ecore-ipc >= ${efl_version} \
   efreet >= ${efl_version} \
   ethumb_client >= ${efl_version} \
   "

PKG_CHECK_MODULES([Entasy], [${requirements}])

AC_CONFIG_FILES([
Makefile
src/Makefile
data/Makefile
man/Makefile
])

AC_OUTPUT

#####################################################################
## Info

echo
echo
echo
echo "------------------------------------------------------------------------"
echo "$PACKAGE $VERSION"
echo "------------------------------------------------------------------------"
echo
echo "Compilation................: make (or gmake)"
echo "  CPPFLAGS.................: $CPPFLAGS"
echo "  CFLAGS...................: $CFLAGS"
echo "  LDFLAGS..................: $LDFLAGS"
echo
echo "Installation...............: make install (as root if needed, with 'su' or 'sudo')"
echo "  prefix...................: $prefix"
echo
