# $OpenBSD$

PROGS =		fenv fdump fproc
SRCS_fenv =	fenv.S
LDADD_fenv =	-nostdlib -nopie
LDADD_fdump =	-lm
LDADD_fproc =	-lkvm
WARNINGS =	yes

REGRESS_TARGETS +=	run-regress-fenv
run-regress-fenv: ${PROGS}
	./fenv | ./fdump

REGRESS_TARGETS +=	run-regress-fproc
run-regress-fproc: ${PROGS}
	${SUDO} ./fproc

.include <bsd.regress.mk>
