AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = 	 xbrl mambo
AM_CPPFLAGS = $(BOOST_CPPFLAGS) $(TA_CFLAGS) $(OPENSSL_INCLUDES) $(XERCES_CFLAGS) $(PTHREAD_CFLAGS)
AM_LDFLAGS=$(BOOST_LDFLAGS) $(OPENSSL_LDFLAGS) $(XERCES_LDFLAGS) $(PTHREAD_CFLAGS)

xbrl_LDADD = $(BOOST_DATE_TIME_LIB) $(BOOST_SYSTEM_LIB) $(OPENSSL_LIBS) $(LIBXERCES) $(PTHREAD_CFLAGS)
xbrl_SOURCES = \
	src/xbrl/url.cpp \
	src/xbrl/reports.cpp\
	src/xbrl/XmlDomDocument.cpp\
	src/xbrl/main.cpp

mambo_LDADD = $(TA_LIBS) $(BOOST_DATE_TIME_LIB) $(BOOST_SYSTEM_LIB) $(OPENSSL_LIBS) $(LIBXERCES) $(PTHREAD_CFLAGS)
mambo_SOURCES = \
	src/xbrl/url.cpp \
	src/xbrl/reports.cpp\
	src/xbrl/XmlDomDocument.cpp\
	src/stock.cpp\
	src/loadASIO.cpp\
	src/save.cpp\
	src/main.cpp
