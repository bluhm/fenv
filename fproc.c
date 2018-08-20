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

/* Read fpu storage area from proc0 via /dev/kmem. */

#include <err.h>
#include <fcntl.h>
#include <kvm.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

void __dead usage(void);

void __dead
usage(void)
{
	fprintf(stderr, "usage: %s [-M core] [-N system]\n", getprogname());
	exit(1);
}

int
main(int argc, char *argv[])
{
	char errbuf[_POSIX2_LINE_MAX];
	char *memf, *nlistf;
	kvm_t *kd;
	int ch;
	struct nlist nl[] = { { .n_name = "_proc0" }, { .n_name = NULL } };


	memf = nlistf = NULL;
	while ((ch = getopt(argc, argv, "M:N:")) != -1) {
		switch(ch) {
		case 'M':
			memf = optarg;
			break;
		case 'N':
			nlistf = optarg;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	kd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY, errbuf);
	if (kd == NULL)
		errx(1, "kvm_openfiles: %s", errbuf);
	if (kvm_nlist(kd, nl) == -1)
		errx(1, "kvm_nlist: %s", kvm_geterr(kd));
	if (nl[0].n_type == 0)
		errx(1, "name '%s' has type %d", nl[0].n_name, nl[0].n_type);

	if (kvm_close(kd) == -1)
		errx(1, "kvm_close: %s", kvm_geterr(kd));
	return 0;
}
