	.text
	.file	"Test"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$2147483647, 4(%rsp)            # imm = 0x7FFFFFFF
	movl	$2147483647, %edi               # imm = 0x7FFFFFFF
	callq	print_int@PLT
	movl	$.Lglobalstring, %edi
	callq	print_string@PLT
	movl	4(%rsp), %edi
	incl	%edi
	movl	%edi, 4(%rsp)
	callq	print_int@PLT
	movl	$.Lglobalstring.1, %edi
	callq	print_string@PLT
	movl	$-2147483648, 4(%rsp)           # imm = 0x80000000
	movl	$-2147483648, %edi              # imm = 0x80000000
	callq	print_int@PLT
	movl	$.Lglobalstring.2, %edi
	callq	print_string@PLT
	movl	$-2147483648, 4(%rsp)           # imm = 0x80000000
	movl	$-2147483648, %edi              # imm = 0x80000000
	callq	print_int@PLT
	movl	$.Lglobalstring.3, %edi
	callq	print_string@PLT
	movl	4(%rsp), %edi
	shrl	$31, %edi
	movl	%edi, 4(%rsp)
	callq	print_int@PLT
	movl	$.Lglobalstring.4, %edi
	callq	print_string@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.Lglobalstring,@object          # @globalstring
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lglobalstring:
	.asciz	" "
	.size	.Lglobalstring, 2

	.type	.Lglobalstring.1,@object        # @globalstring.1
.Lglobalstring.1:
	.asciz	" "
	.size	.Lglobalstring.1, 2

	.type	.Lglobalstring.2,@object        # @globalstring.2
.Lglobalstring.2:
	.asciz	" "
	.size	.Lglobalstring.2, 2

	.type	.Lglobalstring.3,@object        # @globalstring.3
.Lglobalstring.3:
	.asciz	" "
	.size	.Lglobalstring.3, 2

	.type	.Lglobalstring.4,@object        # @globalstring.4
.Lglobalstring.4:
	.asciz	" "
	.size	.Lglobalstring.4, 2

	.section	".note.GNU-stack","",@progbits
