AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = 	 mambo
AM_CPPFLAGS = -I $(TRAVIS_BUILD_DIR)/src


mambo_SOURCES = \
   src/xml/xml_report.cpp \
   src/report.cpp \
   src/sec/sec.cpp \
   src/sec/sec_archives.cpp \
   src/main.cpp

TESTS = mambo_test
check_PROGRAMS = mambo_test
mambo_test_SOURCES = \
   test/sec_test.cpp \
   src/report.cpp \
   src/sec/sec.cpp \
   src/sec/sec_archives.cpp \
   src/xml/xml_report.cpp