# $OpenBSD$

PROGS =		fenv fdump fdfl feget fxproc0
SRCS_fenv =	fenv.S
LDADD_fenv =	-nostdlib -nopie
LDADD_fdfl =	-lm
LDADD_feget =	-lm
LDADD_fxproc0 =	-lkvm
CFLAGS =	-O2 ${PIPE} ${DEBUG}
CFLAGS +=	-Wformat -Wno-compare-distinct-pointer-types
WARNINGS =	yes

REGRESS_TARGETS +=	run-regress-fenv
run-regress-fenv: fenv fdump
	./fenv | ./fdump >fenv.out
	diff ${.CURDIR}/fenv_t.ok fenv.out

REGRESS_TARGETS +=	run-regress-fdfl
run-regress-fdfl: fdfl
	./fdfl >fdfl.out
	diff ${.CURDIR}/fenv_t.ok fdfl.out

REGRESS_TARGETS +=	run-regress-feget
run-regress-feget: feget
	./feget >feget.out
	diff ${.CURDIR}/fenv_t.ok feget.out

REGRESS_TARGETS +=	run-regress-fxproc0
run-regress-fxproc0: fxproc0
	${SUDO} ./fxproc0 >fxproc0.out
	diff ${.CURDIR}/fxsave64.ok fxproc0.out

.include <bsd.regress.mk>
