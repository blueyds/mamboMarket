#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_CONFIG_MACRO_DIRS([m4])
AC_PREREQ([2.69])
AC_INIT([FULL-MAMBO], [0.2], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
 
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AX_CXX_COMPILE_STDCXX_11([ext],[mandatory])

# Checks for libraries.
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

AX_BOOST_BASE([])
AX_BOOST_SYSTEM
AX_BOOST_DATE_TIME
AX_BOOST_ASIO


# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT
