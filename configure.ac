#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([biostat], [0.1], [keithw@mit.edu])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([util.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.

# Checks for header files.

AC_LANG_PUSH(C++)
AC_CHECK_HEADERS([boost/math/special_functions/beta.hpp boost/math/special_functions/gamma.hpp], [], [AC_MSG_ERROR([Missing Boost math header files.])])
AC_LANG_POP(C++)

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# Add picky CXXFLAGS
PICKY_CXXFLAGS="-std=c++0x -pedantic -Wall -Wextra -Weffc++ -Werror"
AC_SUBST([PICKY_CXXFLAGS])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
