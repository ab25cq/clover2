	.text
	.file	"Tuple10.bc"
	.globl	"Tuple10.equals(Self)$$1"
	.align	16, 0x90
	.type	"Tuple10.equals(Self)$$1",@function
"Tuple10.equals(Self)$$1":              # @"Tuple10.equals(Self)$$1"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp0:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp1:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp2:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp3:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp4:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp5:
	.cfi_def_cfa_offset 56
	subq	$104, %rsp
.Ltmp6:
	.cfi_def_cfa_offset 160
.Ltmp7:
	.cfi_offset %rbx, -56
.Ltmp8:
	.cfi_offset %r12, -48
.Ltmp9:
	.cfi_offset %r13, -40
.Ltmp10:
	.cfi_offset %r14, -32
.Ltmp11:
	.cfi_offset %r15, -24
.Ltmp12:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebp
	movq	%r8, %r12
	movq	%rcx, %r15
	movq	%rdx, %r14
	movq	%rsi, %rbx
	movq	(%r15), %r8
	movq	$0, 16(%rsp)
	movq	%r8, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %r13
	movl	24(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#4:                                 # %entry_ifend5
	movq	160(%rsp), %r9
	movq	(%rax), %rax
	movq	16(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1664, %edi             # imm = 0x680
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r14, %r8
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#6:                                 # %entry_ifend16
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	testb	$1, %r13b
	je	.LBB0_51
# BB#7:                                 # %entry_condend
	movl	16(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#8:                                 # %entry_ifend26
	movq	(%rax), %r13
	movl	24(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#9:                                 # %entry_ifend30
	movq	(%rax), %rax
	movq	16(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1716, %edi             # imm = 0x6B4
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r14, %r8
	movq	160(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#10:                                # %entry_ifend44
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 40(%rsp)
	movq	%r13, 40(%rsp)
	testb	$1, %r13b
	je	.LBB0_50
# BB#11:                                # %entry_condend58
	movl	16(%rsp), %r8d
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#12:                                # %entry_ifend62
	movq	(%rax), %r13
	movl	24(%rsp), %r8d
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#13:                                # %entry_ifend66
	movq	(%rax), %rax
	movq	16(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1768, %edi             # imm = 0x6E8
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r14, %r8
	movq	160(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#14:                                # %entry_ifend80
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	testb	$1, %r13b
	je	.LBB0_49
# BB#15:                                # %entry_condend94
	movl	16(%rsp), %r8d
	movl	$3, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#16:                                # %entry_ifend98
	movq	(%rax), %r13
	movl	24(%rsp), %r8d
	movl	$3, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#17:                                # %entry_ifend102
	movq	(%rax), %rax
	movq	16(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1820, %edi             # imm = 0x71C
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r14, %r8
	movq	160(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#18:                                # %entry_ifend116
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 56(%rsp)
	movq	%r13, 56(%rsp)
	testb	$1, %r13b
	je	.LBB0_48
# BB#19:                                # %entry_condend130
	movl	16(%rsp), %r8d
	movl	$4, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#20:                                # %entry_ifend134
	movq	(%rax), %r13
	movl	24(%rsp), %r8d
	movl	$4, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#21:                                # %entry_ifend138
	movq	(%rax), %rax
	movq	16(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1872, %edi             # imm = 0x750
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r14, %r8
	movq	160(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#22:                                # %entry_ifend152
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	testb	$1, %r13b
	je	.LBB0_47
# BB#23:                                # %entry_condend166
	movl	16(%rsp), %r8d
	movl	$5, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#24:                                # %entry_ifend170
	movq	(%rax), %r13
	movl	24(%rsp), %r8d
	movl	$5, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#25:                                # %entry_ifend174
	movq	(%rax), %rax
	movq	16(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1924, %edi             # imm = 0x784
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r14, %r8
	movq	160(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#26:                                # %entry_ifend188
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 72(%rsp)
	movq	%r13, 72(%rsp)
	testb	$1, %r13b
	je	.LBB0_46
# BB#27:                                # %entry_condend202
	movl	16(%rsp), %r8d
	movl	$6, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#28:                                # %entry_ifend206
	movq	(%rax), %r13
	movl	24(%rsp), %r8d
	movl	$6, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#29:                                # %entry_ifend210
	movq	(%rax), %rax
	movq	16(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1976, %edi             # imm = 0x7B8
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r14, %r8
	movq	160(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#30:                                # %entry_ifend224
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 80(%rsp)
	movq	%r13, 80(%rsp)
	testb	$1, %r13b
	je	.LBB0_45
# BB#31:                                # %entry_condend238
	movl	16(%rsp), %r8d
	movl	$7, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#32:                                # %entry_ifend242
	movq	(%rax), %r13
	movl	24(%rsp), %r8d
	movl	$7, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#33:                                # %entry_ifend246
	movq	(%rax), %rax
	movq	16(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$2028, %edi             # imm = 0x7EC
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r14, %r8
	movq	160(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#34:                                # %entry_ifend260
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 88(%rsp)
	movq	%r13, 88(%rsp)
	testb	$1, %r13b
	je	.LBB0_44
# BB#35:                                # %entry_condend274
	movl	16(%rsp), %r8d
	movl	$8, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#36:                                # %entry_ifend278
	movq	(%rax), %r13
	movl	24(%rsp), %r8d
	movl	$8, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#37:                                # %entry_ifend282
	movq	(%rax), %rax
	movq	16(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$2080, %edi             # imm = 0x820
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r14, %r8
	movq	160(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#38:                                # %entry_ifend296
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 96(%rsp)
	movq	%r13, 96(%rsp)
	testb	$1, %r13b
	je	.LBB0_43
# BB#39:                                # %entry_condend310
	movl	16(%rsp), %r8d
	movl	$9, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#40:                                # %entry_ifend314
	movq	(%rax), %r13
	movl	24(%rsp), %r8d
	movl	$9, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#41:                                # %entry_ifend318
	movq	(%rax), %rax
	movq	16(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$2132, %edi             # imm = 0x854
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r14, %r8
	movq	160(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	je	.LBB0_42
.LBB0_5:                                # %then_block15
	movq	%r14, %rdi
	callq	get_try_catch_label_name
.LBB0_1:                                # %then_block
	xorl	%eax, %eax
.LBB0_2:                                # %then_block
	addq	$104, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB0_42:                               # %entry_ifend332
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	andl	$1, %r13d
	movq	%r13, 96(%rsp)
.LBB0_43:                               # %label_and_endpointzzzzzzzzzzzzzzzzn
	andl	$1, %r13d
	movq	%r13, 88(%rsp)
.LBB0_44:                               # %label_and_endpointzzzzzzzzzzzzzzzzm
	andl	$1, %r13d
	movq	%r13, 80(%rsp)
.LBB0_45:                               # %label_and_endpointzzzzzzzzzzzzzzzzl
	andl	$1, %r13d
	movq	%r13, 72(%rsp)
.LBB0_46:                               # %label_and_endpointzzzzzzzzzzzzzzzzk
	andl	$1, %r13d
	movq	%r13, 64(%rsp)
.LBB0_47:                               # %label_and_endpointzzzzzzzzzzzzzzzzj
	andl	$1, %r13d
	movq	%r13, 56(%rsp)
.LBB0_48:                               # %label_and_endpointzzzzzzzzzzzzzzzzi
	andl	$1, %r13d
	movq	%r13, 48(%rsp)
.LBB0_49:                               # %label_and_endpointzzzzzzzzzzzzzzzzh
	andl	$1, %r13d
	movq	%r13, 40(%rsp)
.LBB0_50:                               # %label_and_endpointzzzzzzzzzzzzzzzzg
	andl	$1, %r13d
	movq	%r13, 32(%rsp)
.LBB0_51:                               # %label_and_endpointzzzzzzzzzzzzzzzzf
	movq	%r13, (%r15)
	movl	$1, %eax
	jmp	.LBB0_2
.Lfunc_end0:
	.size	"Tuple10.equals(Self)$$1", .Lfunc_end0-"Tuple10.equals(Self)$$1"
	.cfi_endproc

	.globl	"Tuple10.toString()$$2"
	.align	16, 0x90
	.type	"Tuple10.toString()$$2",@function
"Tuple10.toString()$$2":                # @"Tuple10.toString()$$2"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp13:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp14:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp15:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp16:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp17:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp18:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp19:
	.cfi_def_cfa_offset 112
.Ltmp20:
	.cfi_offset %rbx, -56
.Ltmp21:
	.cfi_offset %r12, -48
.Ltmp22:
	.cfi_offset %r13, -40
.Ltmp23:
	.cfi_offset %r14, -32
.Ltmp24:
	.cfi_offset %r15, -24
.Ltmp25:
	.cfi_offset %rbp, -16
	movl	%r9d, %r13d
	movq	%r8, %rbx
	movq	%rcx, %rbp
	movq	%rbp, 40(%rsp)          # 8-byte Spill
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	112(%rsp), %r9
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	(%rbx), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%rbx)
	movl	%eax, (%rsp)
	movl	$2480, %edi             # imm = 0x9B0
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%r13d, %edx
	movq	%rbx, %rcx
	movq	%r15, %r8
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%r12, %rbp
	movq	%r15, %rdi
	je	.LBB1_5
# BB#4:                                 # %then_block5
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_5:                                # %entry_ifend6
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	%rdi, 32(%rsp)          # 8-byte Spill
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$2492, %esi             # imm = 0x9BC
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#6:                                 # %entry_ifend13
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	%rbp, 24(%rsp)          # 8-byte Spill
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	addq	$8, (%rbx)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r13d, %ecx
	movq	%rbx, %r8
	movq	%rbx, %r14
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%r13d, %ebx
	movq	%rbp, %rdi
	je	.LBB1_8
# BB#7:                                 # %then_block24
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_8:                                # %entry_ifend25
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	%r14, %rbp
	movq	(%rbp), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbp, %r13
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%ebx, %r12d
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2504, %esi             # imm = 0x9C8
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	24(%rsp), %r15          # 8-byte Reload
	je	.LBB1_1
# BB#9:                                 # %entry_ifend36
	movq	48(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	%r13, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r14, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r12d, %ecx
	movq	%r8, %rbx
	movq	32(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%r12d, %r14d
	je	.LBB1_11
# BB#10:                                # %then_block47
	movq	32(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_11:                               # %entry_ifend48
	movq	40(%rsp), %rbp          # 8-byte Reload
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	48(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movl	%r14d, %ebp
	je	.LBB1_1
# BB#12:                                # %entry_ifend60
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	(%rbx), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%rbx)
	movl	%eax, (%rsp)
	movl	$2512, %edi             # imm = 0x9D0
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movq	32(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r8
	movq	112(%rsp), %r14
	movq	%r14, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB1_13
# BB#14:                                # %entry_ifend69
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	%rbx, 16(%rsp)          # 8-byte Spill
	movq	(%rbx), %rax
	movq	%r15, %r14
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$2524, %esi             # imm = 0x9DC
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#15:                                # %entry_ifend80
	movq	48(%rsp), %rcx
	movq	$0, (%r14)
	movq	%rcx, (%r14)
	movq	16(%rsp), %r8           # 8-byte Reload
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r12, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movq	%r15, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ebp, %ecx
	movq	%r8, %r15
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%ebp, %ebx
	jne	.LBB1_13
# BB#16:                                # %entry_ifend92
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	%r15, %rbp
	movq	(%rbp), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$.Lglobal_string.3, %edi
	callq	create_string_object
	movl	%ebx, %r12d
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2536, %esi             # imm = 0x9E8
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#17:                                # %entry_ifend103
	movq	48(%rsp), %rcx
	movq	$0, (%r14)
	movq	%rcx, (%r14)
	movq	16(%rsp), %r8           # 8-byte Reload
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r12d, %ecx
	movq	%r8, %rbx
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_13
# BB#18:                                # %entry_ifend115
	movq	40(%rsp), %rbp          # 8-byte Reload
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	48(%rsp), %r8d
	movl	$2, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%r12d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movl	%r12d, %ebp
	je	.LBB1_1
# BB#19:                                # %entry_ifend127
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%r14)
	movq	%rcx, (%r14)
	movq	(%rbx), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%rbx)
	movl	%eax, (%rsp)
	movl	$2544, %edi             # imm = 0x9F0
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movq	%rbx, %r12
	movq	%r13, %r8
	movq	%r13, %rbx
	movq	112(%rsp), %r13
	movq	%r13, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB1_21
# BB#20:                                # %then_block135
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_21:                               # %entry_ifend136
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	%r12, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$2556, %esi             # imm = 0x9FC
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#22:                                # %entry_ifend147
	movq	48(%rsp), %rdx
	movq	$0, (%r14)
	movq	%rdx, (%r14)
	movq	(%rbx), %rdx
	movq	$0, (%rdx)
	movq	%r15, (%rdx)
	movq	(%rbx), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rsi)
	movq	%r12, 8(%rsi)
	addq	$8, (%rbx)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ebp, %ecx
	movl	%ebp, %r15d
	movq	%rbx, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbp, %rdi
	je	.LBB1_24
# BB#23:                                # %then_block158
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_24:                               # %entry_ifend159
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	%rdi, %r13
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %rbp
	movl	$.Lglobal_string.4, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2568, %esi             # imm = 0xA08
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#25:                                # %entry_ifend170
	movq	48(%rsp), %rdx
	movq	$0, (%r14)
	movq	%rdx, (%r14)
	movq	(%rbp), %rdx
	movq	$0, (%rdx)
	movq	%r12, (%rdx)
	movq	(%rbp), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rsi)
	movl	%ebx, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%rbp)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r15d, %ecx
	movl	%r15d, %r12d
	movq	%rbp, %r8
	movq	%r13, %r9
	movq	%r13, %r15
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_27
# BB#26:                                # %then_block181
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_27:                               # %entry_ifend182
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	%rbp, %r13
	movq	(%r13), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	48(%rsp), %r8d
	movl	$3, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r12d, %ebx
	movl	%ebx, %edx
	movq	%r15, %r12
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r14, %rbp
	je	.LBB1_1
# BB#28:                                # %entry_ifend194
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	(%r13), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r13)
	movl	%eax, (%rsp)
	movl	$2576, %edi             # imm = 0xA10
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r13, %rcx
	movq	%r12, %r8
	movq	%r12, %r14
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB1_29
# BB#30:                                # %entry_ifend203
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$2588, %esi             # imm = 0xA1C
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebx, %ecx
	movq	%r14, %r9
	je	.LBB1_1
# BB#31:                                # %entry_ifend214
	movq	48(%rsp), %rdx
	movq	$0, (%rbp)
	movq	%rdx, (%rbp)
	movq	%rbp, %r14
	movq	(%r13), %rdx
	movq	$0, (%rdx)
	movq	8(%rsp), %rsi           # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r13), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rsi)
	movq	%r12, 8(%rsi)
	addq	$8, (%r13)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r15d
	movq	%r13, %r8
	movq	%r9, %rbp
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_32
# BB#33:                                # %entry_ifend226
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$.Lglobal_string.5, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2600, %esi             # imm = 0xA28
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r15d, %ecx
	movq	%rbp, %r9
	je	.LBB1_1
# BB#34:                                # %entry_ifend237
	movq	48(%rsp), %rdx
	movq	$0, (%r14)
	movq	%rdx, (%r14)
	movq	%r13, %r15
	movq	(%r15), %rdx
	movq	$0, (%rdx)
	movq	%r12, (%rdx)
	movq	(%r15), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rsi)
	movl	%ebx, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r12d
	movq	%r15, %r8
	movq	%r9, %r13
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_13
# BB#35:                                # %entry_ifend249
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	48(%rsp), %r8d
	movl	$4, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r12d, %ebx
	movl	%ebx, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r14, %rbp
	je	.LBB1_1
# BB#36:                                # %entry_ifend261
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	(%r15), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r15)
	movl	%eax, (%rsp)
	movl	$2608, %edi             # imm = 0xA30
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	%r13, %r8
	movq	%r13, %r14
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB1_29
# BB#37:                                # %entry_ifend270
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$2620, %esi             # imm = 0xA3C
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebx, %ecx
	movq	%r14, %r9
	je	.LBB1_1
# BB#38:                                # %entry_ifend281
	movq	48(%rsp), %rdx
	movq	$0, (%rbp)
	movq	%rdx, (%rbp)
	movq	%rbp, %r14
	movq	%r15, %r8
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	8(%rsp), %rsi           # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movq	%r12, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r15d
	movq	%r8, %rbx
	movq	%r9, %rbp
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_32
# BB#39:                                # %entry_ifend293
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r13
	movl	$.Lglobal_string.6, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2632, %esi             # imm = 0xA48
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r15d, %ecx
	movq	%rbp, %r9
	je	.LBB1_1
# BB#40:                                # %entry_ifend304
	movq	48(%rsp), %rdx
	movq	$0, (%r14)
	movq	%rdx, (%r14)
	movq	%r13, %r15
	movq	(%r15), %rdx
	movq	$0, (%rdx)
	movq	%r12, (%rdx)
	movq	(%r15), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rsi)
	movl	%ebx, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r12d
	movq	%r15, %r8
	movq	%r9, %r13
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_13
# BB#41:                                # %entry_ifend316
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	48(%rsp), %r8d
	movl	$5, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r12d, %ebx
	movl	%ebx, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r14, %rbp
	je	.LBB1_1
# BB#42:                                # %entry_ifend328
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	(%r15), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r15)
	movl	%eax, (%rsp)
	movl	$2640, %edi             # imm = 0xA50
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	%r13, %r8
	movq	%r13, %r14
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB1_29
# BB#43:                                # %entry_ifend337
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$2652, %esi             # imm = 0xA5C
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebx, %ecx
	movq	%r14, %r9
	je	.LBB1_1
# BB#44:                                # %entry_ifend348
	movq	48(%rsp), %rdx
	movq	$0, (%rbp)
	movq	%rdx, (%rbp)
	movq	%rbp, %r14
	movq	%r15, %r8
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	8(%rsp), %rsi           # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movq	%r12, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r15d
	movq	%r8, %rbx
	movq	%r9, %rbp
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_32
# BB#45:                                # %entry_ifend360
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r13
	movl	$.Lglobal_string.7, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2664, %esi             # imm = 0xA68
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r15d, %ecx
	movq	%rbp, %r9
	je	.LBB1_1
# BB#46:                                # %entry_ifend371
	movq	48(%rsp), %rdx
	movq	$0, (%r14)
	movq	%rdx, (%r14)
	movq	%r13, %r15
	movq	(%r15), %rdx
	movq	$0, (%rdx)
	movq	%r12, (%rdx)
	movq	(%r15), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rsi)
	movl	%ebx, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r12d
	movq	%r15, %r8
	movq	%r9, %r13
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_13
# BB#47:                                # %entry_ifend383
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	48(%rsp), %r8d
	movl	$6, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r12d, %ebx
	movl	%ebx, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r14, %rbp
	je	.LBB1_1
# BB#48:                                # %entry_ifend395
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	(%r15), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r15)
	movl	%eax, (%rsp)
	movl	$2672, %edi             # imm = 0xA70
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	%r13, %r8
	movq	%r13, %r14
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB1_29
# BB#49:                                # %entry_ifend404
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$2684, %esi             # imm = 0xA7C
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebx, %ecx
	movq	%r14, %r9
	je	.LBB1_1
# BB#50:                                # %entry_ifend415
	movq	48(%rsp), %rdx
	movq	$0, (%rbp)
	movq	%rdx, (%rbp)
	movq	%rbp, %r14
	movq	%r15, %r8
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	8(%rsp), %rsi           # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movq	%r12, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r15d
	movq	%r8, %rbx
	movq	%r9, %rbp
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_32
# BB#51:                                # %entry_ifend427
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r13
	movl	$.Lglobal_string.8, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2696, %esi             # imm = 0xA88
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r15d, %ecx
	movq	%rbp, %r9
	je	.LBB1_1
# BB#52:                                # %entry_ifend438
	movq	48(%rsp), %rdx
	movq	$0, (%r14)
	movq	%rdx, (%r14)
	movq	%r13, %r15
	movq	(%r15), %rdx
	movq	$0, (%rdx)
	movq	%r12, (%rdx)
	movq	(%r15), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rsi)
	movl	%ebx, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r12d
	movq	%r15, %r8
	movq	%r9, %r13
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_13
# BB#53:                                # %entry_ifend450
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	48(%rsp), %r8d
	movl	$7, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r12d, %ebx
	movl	%ebx, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r14, %rbp
	je	.LBB1_1
# BB#54:                                # %entry_ifend462
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	(%r15), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r15)
	movl	%eax, (%rsp)
	movl	$2704, %edi             # imm = 0xA90
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	%r13, %r8
	movq	%r13, %r14
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB1_29
# BB#55:                                # %entry_ifend471
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$2716, %esi             # imm = 0xA9C
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebx, %ecx
	movq	%r14, %r9
	je	.LBB1_1
# BB#56:                                # %entry_ifend482
	movq	48(%rsp), %rdx
	movq	$0, (%rbp)
	movq	%rdx, (%rbp)
	movq	%rbp, %r14
	movq	%r15, %r8
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	8(%rsp), %rsi           # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movq	%r12, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r15d
	movq	%r8, %rbx
	movq	%r9, %rbp
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_32
# BB#57:                                # %entry_ifend494
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r13
	movl	$.Lglobal_string.9, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2728, %esi             # imm = 0xAA8
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r15d, %ecx
	movq	%rbp, %r9
	je	.LBB1_1
# BB#58:                                # %entry_ifend505
	movq	48(%rsp), %rdx
	movq	$0, (%r14)
	movq	%rdx, (%r14)
	movq	%r13, %r15
	movq	(%r15), %rdx
	movq	$0, (%rdx)
	movq	%r12, (%rdx)
	movq	(%r15), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rsi)
	movl	%ebx, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r12d
	movq	%r15, %r8
	movq	%r9, %r13
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_13
# BB#59:                                # %entry_ifend517
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	48(%rsp), %r8d
	movl	$8, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r12d, %ebx
	movl	%ebx, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r14, %rbp
	je	.LBB1_1
# BB#60:                                # %entry_ifend529
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	(%r15), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r15)
	movl	%eax, (%rsp)
	movl	$2736, %edi             # imm = 0xAB0
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	%r13, %r8
	movq	%r13, %r14
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB1_29
# BB#61:                                # %entry_ifend538
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$2748, %esi             # imm = 0xABC
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebx, %ecx
	movq	%r14, %r9
	je	.LBB1_1
# BB#62:                                # %entry_ifend549
	movq	48(%rsp), %rdx
	movq	$0, (%rbp)
	movq	%rdx, (%rbp)
	movq	%rbp, %r14
	movq	%r15, %r8
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	8(%rsp), %rsi           # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movq	%r12, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r15d
	movq	%r8, %rbx
	movq	%r9, %rbp
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_32
# BB#63:                                # %entry_ifend561
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r13
	movl	$.Lglobal_string.10, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2760, %esi             # imm = 0xAC8
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r15d, %ecx
	movq	%rbp, %r9
	je	.LBB1_1
# BB#64:                                # %entry_ifend572
	movq	48(%rsp), %rdx
	movq	$0, (%r14)
	movq	%rdx, (%r14)
	movq	%r13, %r15
	movq	(%r15), %rdx
	movq	$0, (%rdx)
	movq	%r12, (%rdx)
	movq	(%r15), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rsi)
	movl	%ebx, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r12d
	movq	%r15, %r8
	movq	%r9, %r13
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_65
.LBB1_13:                               # %then_block68
	movq	%r13, %rdi
	callq	get_try_catch_label_name
.LBB1_1:                                # %then_block
	xorl	%eax, %eax
.LBB1_2:                                # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB1_65:                               # %entry_ifend584
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	48(%rsp), %r8d
	movl	$9, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r12d, %ebx
	movl	%ebx, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r14, %rbp
	je	.LBB1_1
# BB#66:                                # %entry_ifend596
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	(%r15), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r15)
	movl	%eax, (%rsp)
	movl	$2768, %edi             # imm = 0xAD0
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	%r13, %r8
	movq	%r13, %r14
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	je	.LBB1_67
.LBB1_29:                               # %then_block202
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_67:                               # %entry_ifend605
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$2780, %esi             # imm = 0xADC
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebx, %ecx
	movq	%r14, %r9
	je	.LBB1_1
# BB#68:                                # %entry_ifend616
	movq	48(%rsp), %rdx
	movq	$0, (%rbp)
	movq	%rdx, (%rbp)
	movq	%rbp, %r14
	movq	%r15, %r8
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	8(%rsp), %rsi           # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movq	%r12, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r15d
	movq	%r8, %rbx
	movq	%r9, %rbp
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_69
.LBB1_32:                               # %then_block225
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_69:                               # %entry_ifend628
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r13
	movl	$.Lglobal_string.11, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2792, %esi             # imm = 0xAE8
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r15d, %ecx
	movq	%rbp, %r9
	je	.LBB1_1
# BB#70:                                # %entry_ifend639
	movq	48(%rsp), %rdx
	movq	$0, (%r14)
	movq	%rdx, (%r14)
	movq	%r13, %r8
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	%r12, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movl	%ebx, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%r8, %rbp
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_72
# BB#71:                                # %then_block650
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_72:                               # %entry_ifend651
	movq	40(%rsp), %r13          # 8-byte Reload
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbx, (%r13)
	movl	$1, %eax
	jmp	.LBB1_2
.Lfunc_end1:
	.size	"Tuple10.toString()$$2", .Lfunc_end1-"Tuple10.toString()$$2"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"tuple {"
	.size	.Lglobal_string, 8

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.asciz	","
	.size	.Lglobal_string.2, 2

	.type	.Lglobal_string.3,@object # @global_string.3
.Lglobal_string.3:
	.asciz	","
	.size	.Lglobal_string.3, 2

	.type	.Lglobal_string.4,@object # @global_string.4
.Lglobal_string.4:
	.asciz	","
	.size	.Lglobal_string.4, 2

	.type	.Lglobal_string.5,@object # @global_string.5
.Lglobal_string.5:
	.asciz	","
	.size	.Lglobal_string.5, 2

	.type	.Lglobal_string.6,@object # @global_string.6
.Lglobal_string.6:
	.asciz	","
	.size	.Lglobal_string.6, 2

	.type	.Lglobal_string.7,@object # @global_string.7
.Lglobal_string.7:
	.asciz	","
	.size	.Lglobal_string.7, 2

	.type	.Lglobal_string.8,@object # @global_string.8
.Lglobal_string.8:
	.asciz	","
	.size	.Lglobal_string.8, 2

	.type	.Lglobal_string.9,@object # @global_string.9
.Lglobal_string.9:
	.asciz	","
	.size	.Lglobal_string.9, 2

	.type	.Lglobal_string.10,@object # @global_string.10
.Lglobal_string.10:
	.asciz	","
	.size	.Lglobal_string.10, 2

	.type	.Lglobal_string.11,@object # @global_string.11
.Lglobal_string.11:
	.asciz	"}"
	.size	.Lglobal_string.11, 2


	.section	".note.GNU-stack","",@progbits
