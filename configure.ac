
AC_PREREQ([2.69])
AC_INIT([teiq], [0.4.0], [https://github.com/sramsay/teiq/issues])
AC_DEFINE([COPYRIGHT_DATES], ["2020-2022"], [current copyright dates])
AC_CONFIG_SRCDIR([src/teiq.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])

AC_CHECK_PROG(PKG_CONFIG_EXISTS,[pkg-config],[pkg-config],[no])
if test "$PKG_CONFIG_EXISTS" = "no"
then
    # Notify user that pkg-tools are required
    AC_MSG_NOTICE(['pkg-config' is required for building this software])
    AC_MSG_ERROR(['Please install 'pkg-config' and run ./configure again.])
fi

if pkg-config --atleast-version=2.9.0 libxml-2.0; then
	LIBXML2_CFLAGS=$(pkg-config --cflags libxml-2.0)
	LIBXML2_LIBS=$(pkg-config --libs libxml-2.0)
else
	AC_MSG_ERROR([Requires libxml2 v2.9.0 or higher])
fi

CFLAGS="${CFLAGS} ${LIBXML2_CFLAGS}"
LIBS="${LIBS} ${LIBXML2_LIBS}"

# Checks for programs
AC_PROG_CC

# Checks for header files
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for header signatures
AC_CHECK_HEADER_STDBOOL

AM_INIT_AUTOMAKE([-Wall subdir-objects foreign])

# Output files
AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT
