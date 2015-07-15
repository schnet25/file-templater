lib_LTLIBRARIES = libfileTemplater.la

bin_PROGRAMS = fileTemplater

libfileTemplater_la_SOURCES = \
    FileTemplater.cpp

fileTemplater_SOURCES = fileTemplaterMain.cpp

AM_CPPFLAGS = -I$(top_srcdir)/src @JSON_CFLAGS@ 
LDADD = @JSON_LIBS@

fileTemplater_LDADD = ./libfileTemplater.la @JSON_LIBS@ -lboost_program_options
