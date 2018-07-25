# $OpenBSD$

PROGS =		fenv fdump
SRCS_fenv =	fenv.S
SRCS_fdump =	fdump.c
LDADD_fenv =	-nostdlib -nopie
LDADD_fdump =	-lm
WARNINGS =	yes

REGRESS_TARGETS =	run-regress
run-regress: ${PROGS}
	./fenv | ./fdump

.include <bsd.regress.mk>
