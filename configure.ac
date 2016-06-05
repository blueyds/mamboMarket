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

# Checks for libraries.
AX_BOOST_BASE([])
AX_BOOST_SYSTEM
AX_BOOST_THREAD
AX_BOOST_DATE_TIME
AX_BOOST_ASIO
AX_PTHREAD([])
AX_CHECK_LIBRARY([LIBTALIB],
                  [ta-lib/ta_func.h],
                  [ta_lib],
                  [],
                  [AC_MSG_ERROR([could not find ta_lib])])

# Checks for header files.
AC_CHECK_HEADER([stdio.h],
                     [AC_DEFINE([HAVE_STDIO_H], [1],
                        [define to 1 if you have <stdio.h>.])],
                     [AC_MSG_ERROR([sorry, can't do anything for you])])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.

AC_OUTPUT
