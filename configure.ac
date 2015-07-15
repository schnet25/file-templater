#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([file-templater], [0.5], [schnet25@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/main/fileTemplaterMain.cpp])

LT_INIT

AC_PROG_CC
AC_PROG_CXX
AC_LANG(C++)

AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS(iostream)
AC_CHECK_LIB(m, cos)

AC_CONFIG_MACRO_DIR([m4])

PKG_CHECK_MODULES(JSON, jsoncpp >= 1.6.2)
AC_SUBST(JSON_CFLAGS)
AC_SUBST(JSON_LIBS)

#PKG_CHECK_MODULES(BOOST, boost >= 1.54)
#AC_SUBST(BOOST_CFLAGS)
#AC_SUBST(BOOST_LIBS)

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/main/Makefile
    file-templater.pc
])
AC_OUTPUT
