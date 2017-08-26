#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_INIT([mambo], [0.3.1], [BUG-REPORT-ADDRESS])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_MACRO_DIRS([m4])

#define some macro variables
AX_IS_RELEASE([micro-version])
AX_CHECK_ENABLE_DEBUG()

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AX_WITH_PROG([WGET],[wget],[Please install wget])
AX_WITH_PROG([RM],[rm])


# Checks for libraries.


# Checks for header files.


# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_11


# Checks for library functions.

# Output

AC_OUTPUT
