AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = 	 mambo
AM_CPPFLAGS = $(BOOST_CPPFLAGS) $(TA_CFLAGS)
AM_LDFLAGS=$(BOOST_LDFLAGS)


mambo_LDADD = $(TA_LIBS) $(BOOST_DATE_TIME_LIB)
mambo_SOURCES = \
	src/url.cpp \
	src/reports.cpp\
	src/XmlDomDocument.cpp\
	src/stock.cpp\
	src/loadASIO.cpp\
	src/save.cpp\
	src/main.cpp



ACLOCAL_AMFLAGS = -I m4

