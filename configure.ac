dnl configure.in script for mod_proctitle
dnl Author: Stanislav Sedov <stas@FreeBSD.org>

dnl ------------------- Initialization -----------------------------------
dnl autoconf
AC_PREREQ(2.59)
AC_COPYRIGHT([Copyright (c) 2007 Stanislav Sedov <stas@FreeBSD.org>])
AC_INIT([mod_proctitle], [0.3], [stas@FreeBSD.org])
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADER([config.h])

AC_ISC_POSIX

dnl automake
dnl AMU_PACKAGE_NAME($PACKAGE_NAME)
dnl AMU_PACKAGE_VERSION($PACKAGE_VERSION)
dnl AMU_PACKAGE_BUGREPORT($PACKAGE_BUGREPORT)
AM_INIT_AUTOMAKE([mod_proctitle], [0.2])

dnl ------------------ Check for programs --------------------------------
AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_CPP
AC_PROG_CC_C_O                                                                  
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_RANLIB
AC_PROG_LIBTOOL
dnl AC_PROG_PKG_CONFIG

AC_TYPE_SIZE_T                                                                  
AC_TYPE_UID_T

dnl disable mainatiner mode
AM_MAINTAINER_MODE

dnl ------------------- Check for programs --------------------------
AC_PATH_PROG(APXS, apxs, no)
if test "${APXS}" == "no"; then
	AC_MSG_ERROR([Cannot find apxs, check your path.])
fi

AC_PATH_PROGS(APR_CONFIG, [apr-config apr-1-config apr-2-config], no)
if test "${APR_CONFIG}" == "no"; then
	AC_MSG_ERROR([Cannot find apr-config, check your path.])
fi

AC_PATH_PROGS(APU_CONFIG, [apu-config apu-1-config apu-2-config], no)
if test "${APU_CONFIG}" == "no"; then
	AC_MSG_ERROR([Cannot find apu-config, check your path.])
fi

APACHE_INCLUDEDIR=`${APXS} -q INCLUDEDIR`
APACHE_MODULEDIR=`${APXS} -q LIBEXECDIR`
APR_INCLUDES=`${APR_CONFIG} --includes`
APR_CFLAGS=`${APR_CONFIG} --cflags`
APR_CPPFLAGS=`${APR_CONFIG} --cppflags`
APR_LIBS=`${APR_CONFIG} --libs`
APR_LDFLAGS=`${APR_CONFIG} --ldflags`
APU_INCLUDES=`${APU_CONFIG} --includes`
APU_LIBS=`${APU_CONFIG} --libs`
APU_LDFLAGS=`${APU_CONFIG} --ldflags`

AC_SUBST(APACHE_INCLUDEDIR)
AC_SUBST(APACHE_MODULEDIR)
AC_SUBST(APR_INCLUDES)
AC_SUBST(APR_LIBS)
AC_SUBST(APR_LDFLAGS)
AC_SUBST(APU_INCLUDES)
AC_SUBST(APU_LIBS)
AC_SUBST(APU_LDFLAGS)

CFLAGS="${CFLAGS} -I${APACHE_INCLUDEDIR} ${APR_INCLUDES} ${APU_INCLUDES}"
CFLAGS="${CFLAGS} ${APR_CFLAGS}"
CPPFLAGS="${CPPFLAGS} ${APR_CPPFLAGS}"

dnl ------------------- Check for headers --------------------------------
AC_HEADER_STDC
AC_CHECK_HEADERS([unistd.h stdint.h sys/types.h])

AC_CONFIG_FILES([Makefile
		 src/Makefile
])

AC_MSG_RESULT([])
AC_MSG_RESULT([ $PACKAGE version $VERSION configured successfully!])
AC_MSG_RESULT([/******************************************************/])
AC_MSG_RESULT([/* Now type make/gmake                                */])
AC_MSG_RESULT([/******************************************************/])
AC_MSG_RESULT([])

AC_OUTPUT
