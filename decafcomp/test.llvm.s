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
	callq	if_test@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.globl	if_test                         # -- Begin function if_test
	.p2align	4, 0x90
	.type	if_test,@function
if_test:                                # @if_test
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movb	$1, 15(%rsp)
	xorl	%eax, %eax
	testb	%al, %al
	jne	.LBB1_4
# %bb.1:                                # %true
	movl	$5, 8(%rsp)
	movl	$2, 4(%rsp)
	movl	$3, 16(%rsp)
	movb	$1, %al
	testb	%al, %al
	je	.LBB1_3
# %bb.2:                                # %true5
	addl	$2, 4(%rsp)
	jmp	.LBB1_5
.LBB1_4:                                # %else9
	movl	$3, 8(%rsp)
	movl	$2, 4(%rsp)
	movl	$4, 16(%rsp)
	jmp	.LBB1_5
.LBB1_3:                                # %else
	addl	$2, 8(%rsp)
.LBB1_5:                                # %end
	movl	16(%rsp), %edi
	imull	8(%rsp), %edi
	addl	4(%rsp), %edi
	movl	%edi, 20(%rsp)
	callq	print_int@PLT
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	if_test, .Lfunc_end1-if_test
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
