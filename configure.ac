#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([file-templater], [0.1], [schnet25@gmail.com])
AM_INIT_AUTOMAKE

AC_PROG_CC
AC_PROG_CXX

AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

AC_CONFIG_MACRO_DIR([m4])

PKG_CHECK_MODULES(JSON, jsoncpp = 1.6.2)
AC_SUBST(JSON_CFLAGS)
AC_SUBST(JSON_LIBS)

PKG_CHECK_MODULES(BOOST, boost = 1.58)
AC_SUBST(BOOST_CFLAGS)
AC_SUBST(BOOST_LIBS)

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/main/Makefile
                 file-templater.pc
])
AC_OUTPUT
