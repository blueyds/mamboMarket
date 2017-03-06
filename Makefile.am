AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = 	 xbrl mambo
AM_CPPFLAGS = $(BOOST_CPPFLAGS) $(TA_CFLAGS) $(OPENSSL_INCLUDES) $(XERCES_CFLAGS) $(PTHREAD_CFLAGS)
AM_LDFLAGS=$(BOOST_LDFLAGS) $(OPENSSL_LDFLAGS) $(XERCES_LDFLAGS) $(PTHREAD_CFLAGS)

xbrl_LDADD = $(BOOST_DATE_TIME_LIB) $(BOOST_SYSTEM_LIB) -lxerces $(OPENSSL_LIBS) $(LIBXERCES)
xbrl_SOURCES = \
	src/xbrl/url.cpp \
	src/xbrl/reports.cpp\
	src/xbrl/url.cpp\
	src/xbrl/XmlDomDocument.cpp\
	src/xbrl/main.cpp

mambo_LDADD = $(BOOST_DATE_TIME_LIB) $(BOOST_SYSTEM_LIB) -lxerces $(OPENSSL_LIBS) $(LIBXERCES)$(TA_LIBS) $(PTHREAD_CFLAGS)
mambo_SOURCES = \
	src/xbrl/url.cpp \
	src/xbrl/reports.cpp\
	src/xbrl/url.cpp\
	src/xbrl/XmlDomDocument.cpp\
	src/stock.cpp\
	src/loadASIO.cpp\
	src/save.cpp\
	src/main.cpp
