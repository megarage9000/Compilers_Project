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
	.globl	add_recur                       # -- Begin function add_recur
	.p2align	4, 0x90
	.type	add_recur,@function
add_recur:                              # @add_recur
	.cfi_startproc
# %bb.0:                                # %entry
	testl	%edi, %edi
	je	.LBB1_1
# %bb.2:                                # %repeat
	pushq	%rax
	.cfi_def_cfa_offset 16
	decl	%edi
	incl	%esi
	callq	add_recur@PLT
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.LBB1_1:                                # %done
	movl	%esi, %eax
	retq
.Lfunc_end1:
	.size	add_recur, .Lfunc_end1-add_recur
	.cfi_endproc
                                        # -- End function
	.globl	fact                            # -- Begin function fact
	.p2align	4, 0x90
	.type	fact,@function
fact:                                   # @fact
	.cfi_startproc
# %bb.0:                                # %entry
	cmpl	$1, %edi
	jne	.LBB2_2
# %bb.1:                                # %isOne
	movl	$1, %eax
	retq
.LBB2_2:                                # %notOne
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movl	%edi, %ebx
	leal	-1(%rbx), %edi
	callq	fact@PLT
	imull	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	fact, .Lfunc_end2-fact
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
	callq	fact@PLT
	movl	%eax, %edi
	callq	print_int@PLT
	movq	.nl@GOTPCREL(%rip), %rdi
	callq	print_string@PLT
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end3:
	.size	main, .Lfunc_end3-main
	.cfi_endproc
                                        # -- End function
	.type	.nl,@object                     # @.nl
	.section	.rodata,"a",@progbits
	.globl	.nl
.nl:
	.asciz	"\n"
	.size	.nl, 2

	.section	".note.GNU-stack","",@progbits
