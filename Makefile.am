AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = 	mambo
AM_CPPFLAGS = $(BOOST_CPPFLAGS) $(TA_CFLAGS) $(XERCES_CFLAGS) $(PTHREAD_CFLAGS)
AM_LDFLAGS=$(BOOST_LDFLAGS) $(OPENSSL_LDFLAGS) $(XERCES_LDFLAGS) $(PTHREAD_CFLAGS)

bin_PROGRAMS = 	xbrl
xbrl_LDADD = $(BOOST_DATE_TIME_LIB) $(BOOST_SYSTEM_LIB) $(OPENSSL_LIBS) $(LIBXERCES)
xbrl_SOURCES = \
	src/xbrl/url.cpp \
	src/xbrl/reports.cpp\
	src/xbrl/url.cpp\
	src/xbrl/XmlDomDocument.cpp\
	src/xbrl/main.cpp

mambo_LDADD = $(BOOST_DATE_TIME_LIB) $(BOOST_SYSTEM_LIB) $(LIBXERCES)$(TA_LIBS) $(PTHREAD_CFLAGS)
mambo_SOURCES = \
	src/xbrl/url.cpp \
	src/xbrl/reports.cpp\
	src/xbrl/url.cpp\
	src/xbrl/XmlDomDocument.cpp\
	src/stock.cpp\
	src/loadASIO.cpp\
	src/save.cpp\
	src/main.cpp
