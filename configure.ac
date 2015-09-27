#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ
AC_INIT([file-templater], [0.5], [ts@basketbit.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/main/fileTemplater.cpp])

LT_INIT

AC_PROG_CC
AC_PROG_CXX
AC_LANG(C++)

AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS(iostream)

AC_CONFIG_MACRO_DIR([m4])

PKG_CHECK_MODULES(JSON, jsoncpp)
AC_SUBST(JSON_CFLAGS)
AC_SUBST(JSON_LIBS)

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/main/Makefile
    file-templater.pc
])
AC_OUTPUT
