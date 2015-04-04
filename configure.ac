#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-MAMBO], [0.1], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/stock.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
                 src/Makefile])
 
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

AC_ARG_WITH(pgsql-host,
             [  --with-pgsql-host=HOST               server is running on HOST @<:@local socket@:>@],
             [pg_host=$withval], 
             [pg_host=])
AC_ARG_WITH(pgsql-db,
             [  --with-pgsql-db=DATABASE             use DATABASE @<:@tarantoola@:>@],
             [pg_db=$withval], 
             [pg_db=mambo])
AC_ARG_WITH(pgsql-user,
             [  --with-pgsql-user=USER               use USER @<:@postgres@:>@],
             [pg_user=$withval], 
             [pg_user=mambo])
AC_ARG_WITH(pgsql-password,
             [  --with-pgsql-password=PASSWORD       use PASSWORD @<:@none@:>@],
             [pg_password=$withval], 
             [pg_password=""])
AX_CHECK_PGSQL_DB([$pg_db], 
                  [$pg_user], 
                  [$pg_host], 
                  [$pg_password], 
                  [AC_MSG_ERROR([We need a database connection!])])
AC_DEFINE([PG_HOST],
           
AC_DEFINE([PG_DB],
           [$pg_db],
           [name of the postgres database])
# Checks for libraries.
AX_BOOST_BASE([1.34.1])
AX_BOOST_SYSTEM
AX_BOOST_THREAD
AX_BOOST_DATE_TIME
AX_BOOST_ASIO
AX_PTHREAD([])
AX_CHECK_LIBRARY([LIBTALIB],
                  [ta-lib/ta_func.h],
                  [ta_lib],
                  [],
                  [AC_MSG_ERROR(could not find ta_lib)])
AX_LIB_POSTGRESQL([])

# Checks for header files.
AC_CHECK_HEADER([stdio.h],
                     [AC_DEFINE([HAVE_STDIO_H], [1],
                        [define to 1 if you have <stdio.h>.])],
                     [AC_MSG_ERROR([sorry, can't do anything for you])])
# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.

AC_OUTPUT
