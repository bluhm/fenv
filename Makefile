# $OpenBSD$

PROGS =		fenv fdump fxproc0
SRCS_fenv =	fenv.S
LDADD_fenv =	-nostdlib -nopie
LDADD_fdump =	-lm
LDADD_fxproc0 =	-lkvm
CFLAGS =	-O2 ${PIPE} ${DEBUG}
CFLAGS +=	-Wformat -Wno-compare-distinct-pointer-types
WARNINGS =	yes

REGRESS_TARGETS +=	run-regress-fenv
run-regress-fenv: ${PROGS}
	./fenv | ./fdump

REGRESS_TARGETS +=	run-regress-fxproc0
run-regress-fxproc0: ${PROGS}
	${SUDO} ./fxproc0

.include <bsd.regress.mk>
