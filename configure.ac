#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([src/stock.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
                 src/Makefile])
 
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AX_BOOST_BASE([1.34.1],
  [AC_MSG_ERROR([Boost is installed])],
  [AC_MSG_ERROR([sorry, Boost is not installed])])
AX_BOOST_ASIO

# Checks for header files.
AC_CHECK_HEADER([stdio.h],
                     [AC_DEFINE([HAVE_STDIO_H], [1],
                        [Define to 1 if you have <stdio.h>.])],
                     [AC_MSG_ERROR([sorry, can't do anything for you])])
# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.

AC_OUTPUT
