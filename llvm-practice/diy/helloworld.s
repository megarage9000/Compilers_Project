	.text
	.file	"helloworld.ll"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$LC0, %edi
	callq	puts@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	LC0,@object                     # @LC0
	.section	.rodata,"a",@progbits
LC0:
	.asciz	"hello world\n"
	.size	LC0, 13

	.section	".note.GNU-stack","",@progbits
