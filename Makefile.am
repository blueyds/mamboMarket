AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = 	 mambo
AM_CPPFLAGS = $(BOOST_CPPFLAGS) $(TA_CFLAGS) $(OPENSSL_INCLUDES) $(PTHREAD_CFLAGS)
AM_LDFLAGS=$(BOOST_LDFLAGS) $(OPENSSL_LDFLAGS) $(PTHREAD_CFLAGS)


mambo_LDADD = $(TA_LIBS) $(BOOST_DATE_TIME_LIB) $(BOOST_SYSTEM_LIB) $(OPENSSL_LIBS) $(LIBXERCES_C) $(PTHREAD_CFLAGS)
mambo_SOURCES = \
	src/xbrl/url.cpp \
	src/xbrl/reports.cpp\
	src/xbrl/XmlDomDocument.cpp\
	src/stock.cpp\
	src/loadASIO.cpp\
	src/save.cpp\
	src/main.cpp



ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = build-aux/config.rpath m4/ChangeLog
