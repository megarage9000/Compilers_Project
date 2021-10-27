	.text
	.file	"factorial.ll"
	.globl	factorial                       # -- Begin function factorial
	.p2align	4, 0x90
	.type	factorial,@function
factorial:                              # @factorial
	.cfi_startproc
# %bb.0:                                # %entry
	testl	%edi, %edi
	je	.LBB0_2
# %bb.1:                                # %recurse
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movl	%edi, %ebx
	leal	-1(%rbx), %edi
	callq	factorial@PLT
	imull	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.LBB0_2:                                # %done
	.cfi_restore %rbx
	movl	$1, %eax
	retq
.Lfunc_end0:
	.size	factorial, .Lfunc_end0-factorial
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
	movl	$11, %edi
	callq	factorial@PLT
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
