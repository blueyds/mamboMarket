AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = 	 mambo
AM_CPPFLAGS = $(BOOST_CPPFLAGS)
AM_LDFLAGS=$(BOOST_LDFLAGS)


mambo_LDADD = $(BOOST_DATE_TIME_LIB)
mambo_SOURCES = \
   src/xml/xml_report.cpp \
   src/report.cpp \
   src/sec.cpp \


ACLOCAL_AMFLAGS = -I m4

TESTS = sec_test
check_PROGRAMS = sec_test
sec_test_SOURCES = \
   test/sec_test.cpp \
   src/report.cpp \
   src/sec/sec.cpp \
   src/xml/xml_report.cpp