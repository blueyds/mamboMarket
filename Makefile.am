AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = 	mambo
AM_CPPFLAGS = $(BOOST_CPPFLAGS) $(TA_CFLAGS) $(PTHREAD_CFLAGS)
AM_LDFLAGS=$(BOOST_LDFLAGS)
mambo_LDADD = $(BOOST_DATE_TIME_LIB) $(BOOST_SYSTEM_LIB) $(TA_LIBS) $(PTHREAD_CFLAGS)
mambo_SOURCES = src/stock.cpp\
		src/loadASIO.cpp\
		src/save.cpp\
		src/main.cpp