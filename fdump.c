/*	$OpenBSD$	*/
/*
 * Copyright (c) 2018 Alexander Bluhm <bluhm@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>

#include <err.h>
#include <fenv.h>
#include <stdio.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	struct {
		fenv_t	env;
		char	pad[4];
	} buf; 
	fenv_t *env = &buf.env;
	ssize_t len;

	len = read(0, &buf, sizeof(buf));
	if (len < 0 )
		err(1, "read");
	if (len != sizeof(fenv_t))
		errx(1, "read len %zd is not size %zu",
		    len, sizeof(fenv_t));

	printf("control\tdfl %08x, env %08x\n",
	    FE_DFL_ENV->__x87.__control, env->__x87.__control);
	printf("status\tdfl %08x, env %08x\n",
	    FE_DFL_ENV->__x87.__status, env->__x87.__status);
	printf("tag\tdfl %08x, env %08x\n",
	    FE_DFL_ENV->__x87.__tag, env->__x87.__tag);
	printf("others0\tdfl %08x, env %08x\n",
	    FE_DFL_ENV->__x87.__others[0], env->__x87.__others[0]);
	printf("others1\tdfl %08x, env %08x\n",
	    FE_DFL_ENV->__x87.__others[1], env->__x87.__others[1]);
	printf("others2\tdfl %08x, env %08x\n",
	    FE_DFL_ENV->__x87.__others[2], env->__x87.__others[2]);
	printf("others3\tdfl %08x, env %08x\n",
	    FE_DFL_ENV->__x87.__others[3], env->__x87.__others[3]);
	printf("mxcsr\tdfl %08x, env %08x\n",
	    FE_DFL_ENV->__mxcsr, env->__mxcsr);

	return 0;
}
