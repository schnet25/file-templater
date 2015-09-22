bin_PROGRAMS = fileTemplater

fileTemplater_SOURCES = \
    FileTemplater.cpp \
    fileTemplaterMain.cpp

AM_CPPFLAGS = -I$(top_srcdir)/src @JSON_CFLAGS@ 
LDADD = @JSON_LIBS@ -lboost_program_options -lboost_filesystem

