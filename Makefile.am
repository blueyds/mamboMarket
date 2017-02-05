AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = 	mambo
AM_CPPFLAGS = $(BOOST_CPPFLAGS) $(TA_CFLAGS)
AM_LDFLAGS=$(BOOST_LDFLAGS)
mambo_LDADD = $(BOOST_DATE_TIME_LIB) $(TA_LIBS)
mambo_SOURCES = src/stock.cpp\
		src/loadASIO.cpp\
		src/save.cpp\
		src/main.cpp