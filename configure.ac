#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_INIT([FULL-MAMBO], [0.2], [BUG-REPORT-ADDRESS])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_MACRO_DIRS([m4])
AC_PREREQ([2.69])
AC_CONFIG_SRCDIR([src/main.cpp])
 
#define some macro variables
m4_define([boost_e1],[cannot locate boost developer libraries[,] do you need to install libboost-all-dev?])
m4_define([pthread_e1],[cannot locate pthread libraries[,] do you need to install libpthread-stubs0-dev])
m4_define([ssl_e1],[cannot locate openssl libraries])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_CHECK_PROGS([UNZIP],[unzip],[0])
if test "x$UNZIP" = "x0"; then
	AC_MSG_ERROR([We need unzip])
	fi

# Checks for libraries.
PKG_CHECK_MODULES([TA],[stlta])
AX_CHECK_OPENSSL([],[AC_MSG_ERROR([ssl_e1])])
AX_BOOST_BASE([],[],[AC_MSG_ERROR([boost_e1])])
AX_BOOST_SYSTEM([],[],[AC_MSG_ERROR([boost_e1])])
AX_BOOST_DATE_TIME([],[],[AC_MSG_ERROR([boost_e1])])
AX_BOOST_ASIO([],[],[AC_MSG_ERROR([boost_e1])])
AX_XERCESC()

AX_PTHREAD

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_11([ext],[mandatory])


# Checks for library functions.

# Output
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile intl/Makefile po/Makefile.in])

AC_OUTPUT
