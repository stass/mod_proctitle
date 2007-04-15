/*-
 * Copyright (c) 2007 Hosting Telesystems, JSC
 * All rights reserved.
 *
 * This software was developed by Stanislav Sedov <stas@FreeBSD.org>
 * under contract to Hosting Telesystems, JSC.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $MBSDlabs: mod_proctitle/src/mod_proctitle.c,v 1.2 2007/04/12 17:38:29 stas Exp $
 *
 * $HTSID$
 */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include <assert.h>

#include <sys/param.h>

#include <apr.h>
#include <apr_strings.h>
#include <apr_hooks.h>

#include <httpd.h>
#include <http_config.h>
#include <http_core.h>
#include <http_request.h>

#undef PACKAGE_BUGREPORT /* damn apache */
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#include "config.h"

/*
 * Prototypes
 */
static void register_hooks		__P((apr_pool_t *p));

/* Forward */
module AP_MODULE_DECLARE_DATA proctitle_module;

unsigned int enabled;	/* enable/disable */

/*
 * Set process titles according to urls they're processing
 */
static int
proctitle_fixup(request_rec *r) {
	const char *name;

	name = ap_get_server_name(r);
	if (name != NULL && r->uri != NULL)
		setproctitle("-%s::%s", name, r->uri);

	return OK;
}

/*
 ********************* Standard module stuff ************************
 */

static const char *
proctitle_flag(cmd_parms *cmd __unused, void *mconfig __unused, int flag)
{

	enabled = flag;

	return NULL;
}

static void
register_hooks(apr_pool_t *p __unused) {
	ap_hook_fixups(proctitle_fixup, NULL, NULL, \
		APR_HOOK_MIDDLE);
}

static const command_rec proctitle_commands[] =
{
	AP_INIT_FLAG("ProctitleEnable", proctitle_flag, NULL, RSRC_CONF, \
	    "Enable/disable setting process titles (on by default)"),
	{NULL, {NULL}, NULL, 0, 0, NULL},
};

module AP_MODULE_DECLARE_DATA proctitle_module = {
	STANDARD20_MODULE_STUFF,
	NULL,			/* dir config creater */
	NULL,			/* dir merger --- default is to override */
	NULL,			/* server config */
	NULL,			/* merge server configs */
	proctitle_commands,	/* command apr_table_t */
	register_hooks,		/* register hooks */
};
