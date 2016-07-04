AUTOMAKE_OPTIONS = subdir-objects
SUBDIRS = STL_TA
bin_PROGRAMS = 	mambo
mambo_SOURCES = src/stock.cpp\
		src/loadASIO.cpp\
		src/save.cpp\
		src/main.cpp
mambo_LDADD =  ./STL_TA/libstlta.a \
		$(BOOST_DATE_TIME_LIB)\
		$(BOOST_SYSTEM_LIB) \
		-lmlpack
AM_CXXFLAGS = 	$(BOOST_CPPFLAGS)
AM_LDFLAGS = 	$(BOOST_LDFLAGS)
