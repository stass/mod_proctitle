# Makefile.am script for mod_proctitle
# Author: Stanislav Sedov <stas@FreeBSD.org>

lib_LTLIBRARIES=mod_proctitle.la
libdir= @APACHE_MODULEDIR@
mod_proctitle_la_LDFLAGS=-module -avoid-version

LIBS=@APR_LDFLAGS@ @APU_LDFLAGS@ @APR_LIBS@ @APU_LIBS@
AM_CFLAGS=@APR_INCLUDES@ @APU_INCLUDES@ -I@APACHE_INCLUDEDIR@

mod_proctitle_la_SOURCES = mod_proctitle.c
