#include <sys/syscall.h>

	.section	.note.openbsd.ident, "a"
	.p2align	2
	.long		8
	.long		4
	.long		1
	.ascii		"OpenBSD\0"
	.long		0
	.previous

	.data
env:
	.long	1	/* __control */
	.long	1	/* __status */
	.long	1	/* __tag */
	.long	1	/* __others 0 */
	.long	1	/* __others 1 */
	.long	1	/* __others 2 */
	.long	1	/* __others 3 */
mxcsr:
	.long	1	/* __mxcsr */
env_end:

	.text
	.align	8
	.global	_start
_start:
	fnstenv	env
	stmxcsr	mxcsr
	mov	$SYS_write,	%rax
	mov	$1,		%rdi
	mov	$env,		%rsi
	mov	$(env_end-env),	%rdx
	syscall
	mov	$SYS_exit,	%rax
	mov	$0,		%rdi
	syscall
