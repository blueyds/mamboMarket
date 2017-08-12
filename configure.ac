#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_INIT([mambo], [0.3], [BUG-REPORT-ADDRESS])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_MACRO_DIRS([m4])

#define some macro variables
m4_define([boost_e1],[cannot locate boost developer libraries[,] do you need to install libboost-all-dev?])
m4_define([pthread_e1],[cannot locate pthread libraries[,] do you need to install libpthread-stubs0-dev])
m4_define([ssl_e1],[cannot locate openssl libraries])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AX_WITH_PROG([WGET],[wget],[Please install wget])
AX_WITH_PROG([RM],[rm])


# Checks for libraries.
AX_BOOST_BASE([],[],[AC_MSG_ERROR([boost_e1])])
#AX_BOOST_DATE_TIME([],[],[AC_MSG_ERROR([boost_e1])])


# Checks for header files.
AX_ABSOLUTE_HEADER([report.hpp])
AX_ABSOLUTE_HEADER([xml/xml_report.hpp])
AX_ABSOLUTE_HEADER([sec/sec_report.hpp])
AX_ABSOLUTE_HEADER([xml/rapidxml_ns.hpp]) 


# Checks for typedefs, structures, and compiler characteristics.
#AX_CXX_COMPILE_STDCXX_11([ext],[mandatory])


# Checks for library functions.

# Output

AC_OUTPUT
