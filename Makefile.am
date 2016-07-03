AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = 	mambo
mambo_SOURCES = src/stock.cpp\
		src/loadASIO.cpp\
		src/save.cpp\
		src/main.cpp
mambo_LDADD = 	$(BOOST_DATE_TIME_LIB)\
		$(BOOST_SYSTEM_LIB) -lmlpack -l/usr/local/lib/libstlta.a
AM_CXXFLAGS = 	$(BOOST_CPPFLAGS) 
AM_LDFLAGS = 	$(BOOST_LDFLAGS)
