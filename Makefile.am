AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = 	mambo
mambo_SOURCES = src/stock.cpp\
		src/loadASIO.cpp\
		src/save.cpp\
		src/main.cpp
mambo_CPPFLAGS = $(BOOST_CPPFLAGS)\
		$(LIBXMLXX_CPPFLAGS)
mambo_LDFLAGS=$(BOOST_LDFLAGS)
mambo_LDADD =  ./STL_TA/libstlta.a \
		$(BOOST_DATE_TIME_LIB)\
		$(BOOST_SYSTEM_LIB) \
		$(LIBXMLXX_LIBS)\
		-lmlpack
