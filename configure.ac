#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_INIT([FULL-MAMBO], [0.2], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_MACRO_DIRS([m4])
AC_PREREQ([2.69])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
 
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([LIBXMLXX], [libxml++-3.0])
PKG_CHECK_MODULES([LIBSTLTA], [STL_TA])
AX_BOOST_BASE([])
AX_BOOST_THREAD
AX_BOOST_SYSTEM
AX_BOOST_DATE_TIME
AX_BOOST_ASIO


# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_11([ext],[mandatory])


# Checks for library functions.

AC_OUTPUT
