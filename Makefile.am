AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = 	 mambo
AM_CPPFLAGS = -I$(top_srcdir)/src

mambo_SOURCES = \
   src/xml/xml_report.cpp \
   src/csv/csv_report.cpp \
   src/stlta/stlta.cpp \
   src/report.cpp \
   src/stock.cpp \
   src/date/date.cc \
   src/sec/sec.cpp \
   src/sec/sec_archives.cpp \
   src/sec/10Q.cpp \
   src/main.cpp

TESTS = mambo_test
check_PROGRAMS = mambo_test
mambo_test_SOURCES = \
   src/xml/xml_report.cpp \
   src/csv/csv_report.cpp \
   src/stlta/stlta.cpp \
   src/report.cpp \
   src/stock.cpp \
   src/date/date.cc \
   src/sec/sec.cpp \
   src/sec/sec_archives.cpp \
   src/sec/10Q.cpp \
   src/main.cpp