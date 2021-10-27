	.text
	.file	"add.ll"
	.globl	add1                            # -- Begin function add1
	.p2align	4, 0x90
	.type	add1,@function
add1:                                   # @add1
	.cfi_startproc
# %bb.0:                                # %entry
                                        # kill: def $esi killed $esi def $rsi
                                        # kill: def $edi killed $edi def $rdi
	leal	(%rdi,%rsi), %eax
	retq
.Lfunc_end0:
	.size	add1, .Lfunc_end0-add1
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$3, %edi
	movl	$4, %esi
	callq	add1@PLT
	movl	%eax, %edi
	callq	print_int@PLT
	movq	.nl@GOTPCREL(%rip), %rdi
	callq	print_string@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	.nl,@object                     # @.nl
	.section	.rodata,"a",@progbits
	.globl	.nl
.nl:
	.asciz	"\n"
	.size	.nl, 2

	.section	".note.GNU-stack","",@progbits
