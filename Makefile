# $OpenBSD$

PROGS =		fenv fdump fdfl fxproc0
SRCS_fenv =	fenv.S
LDADD_fenv =	-nostdlib -nopie
LDADD_fdump =	-lm
LDADD_fdfl =	-lm
LDADD_fxproc0 =	-lkvm
CFLAGS =	-O2 ${PIPE} ${DEBUG}
CFLAGS +=	-Wformat -Wno-compare-distinct-pointer-types
WARNINGS =	yes

REGRESS_TARGETS +=	run-regress-fenv
run-regress-fenv: fenv fdump
	./fenv | ./fdump

REGRESS_TARGETS +=	run-regress-fdfl
run-regress-fdfl: fdfl
	./fdfl

REGRESS_TARGETS +=	run-regress-fxproc0
run-regress-fxproc0: fxproc0
	${SUDO} ./fxproc0

.include <bsd.regress.mk>
