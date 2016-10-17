AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = 	mambo
AM_CPPFLAGS = $(BOOST_CPPFLAGS)\
		$(TA_CPPFLAGS)
AM_LDFLAGS=$(BOOST_LDFLAGS)
mambo_LDADD = $(BOOST_SYSTEM_LIB) \
		$(BOOST_DATE_TIME_LIB) \
		$(BOOST_THREAD_LIB) \
		$(PTHREAD_LIBS) \
		$(TA_LIBS)
mambo_SOURCES = src/stock.cpp\
		src/loadASIO.cpp\
		src/save.cpp\
		src/main.cpp