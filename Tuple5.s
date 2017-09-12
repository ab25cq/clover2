	.text
	.file	"Tuple5.bc"
	.globl	"Tuple5.equals(Self)$$1"
	.align	16, 0x90
	.type	"Tuple5.equals(Self)$$1",@function
"Tuple5.equals(Self)$$1":               # @"Tuple5.equals(Self)$$1"
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
	subq	$56, %rsp
.Ltmp6:
	.cfi_def_cfa_offset 112
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
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %rbx
	movq	(%r14), %r8
	movq	$0, 8(%rsp)
	movq	%r8, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %r13
	movl	16(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#4:                                 # %entry_ifend5
	movq	112(%rsp), %r9
	movq	(%rax), %rax
	movq	8(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	16(%rsp), %rcx
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
	movl	$924, %edi              # imm = 0x39C
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r15, %r8
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#6:                                 # %entry_ifend16
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 24(%rsp)
	movq	%r13, 24(%rsp)
	testb	$1, %r13b
	je	.LBB0_26
# BB#7:                                 # %entry_condend
	movl	8(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#8:                                 # %entry_ifend26
	movq	(%rax), %r13
	movl	16(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#9:                                 # %entry_ifend30
	movq	(%rax), %rax
	movq	8(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	16(%rsp), %rcx
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
	movl	$976, %edi              # imm = 0x3D0
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r15, %r8
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#10:                                # %entry_ifend44
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	testb	$1, %r13b
	je	.LBB0_25
# BB#11:                                # %entry_condend58
	movl	8(%rsp), %r8d
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#12:                                # %entry_ifend62
	movq	(%rax), %r13
	movl	16(%rsp), %r8d
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#13:                                # %entry_ifend66
	movq	(%rax), %rax
	movq	8(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	16(%rsp), %rcx
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
	movl	$1028, %edi             # imm = 0x404
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r15, %r8
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#14:                                # %entry_ifend80
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 40(%rsp)
	movq	%r13, 40(%rsp)
	testb	$1, %r13b
	je	.LBB0_24
# BB#15:                                # %entry_condend94
	movl	8(%rsp), %r8d
	movl	$3, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#16:                                # %entry_ifend98
	movq	(%rax), %r13
	movl	16(%rsp), %r8d
	movl	$3, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#17:                                # %entry_ifend102
	movq	(%rax), %rax
	movq	8(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	16(%rsp), %rcx
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
	movl	$1080, %edi             # imm = 0x438
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r15, %r8
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#18:                                # %entry_ifend116
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	testb	$1, %r13b
	je	.LBB0_23
# BB#19:                                # %entry_condend130
	movl	8(%rsp), %r8d
	movl	$4, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#20:                                # %entry_ifend134
	movq	(%rax), %r13
	movl	16(%rsp), %r8d
	movl	$4, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#21:                                # %entry_ifend138
	movq	(%rax), %rax
	movq	8(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	16(%rsp), %rcx
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
	movl	$1132, %edi             # imm = 0x46C
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r15, %r8
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	je	.LBB0_22
.LBB0_5:                                # %then_block15
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB0_1:                                # %then_block
	xorl	%eax, %eax
.LBB0_2:                                # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB0_22:                               # %entry_ifend152
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	andl	$1, %r13d
	movq	%r13, 48(%rsp)
.LBB0_23:                               # %label_and_endpointzzzzzzzzzzzzzzzd
	andl	$1, %r13d
	movq	%r13, 40(%rsp)
.LBB0_24:                               # %label_and_endpointzzzzzzzzzzzzzzzc
	andl	$1, %r13d
	movq	%r13, 32(%rsp)
.LBB0_25:                               # %label_and_endpointzzzzzzzzzzzzzzzb
	andl	$1, %r13d
	movq	%r13, 24(%rsp)
.LBB0_26:                               # %label_and_endpointzzzzzzzzzzzzzzz
	movq	%r13, (%r14)
	movl	$1, %eax
	jmp	.LBB0_2
.Lfunc_end0:
	.size	"Tuple5.equals(Self)$$1", .Lfunc_end0-"Tuple5.equals(Self)$$1"
	.cfi_endproc

	.globl	"Tuple5.toString()$$2"
	.align	16, 0x90
	.type	"Tuple5.toString()$$2",@function
"Tuple5.toString()$$2":                 # @"Tuple5.toString()$$2"
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
	movl	%r9d, %r12d
	movq	%r8, %rbx
	movq	%rcx, %rbp
	movq	%rbp, 40(%rsp)          # 8-byte Spill
	movq	%rdx, %r14
	movq	%rsi, %r15
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%r12d, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	112(%rsp), %r9
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	%rbx, %rcx
	movq	(%rcx), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%rcx)
	movl	%eax, (%rsp)
	movl	$1300, %edi             # imm = 0x514
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%r12d, %edx
	movq	%r14, %r8
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%r15, %rbp
	je	.LBB1_5
# BB#4:                                 # %then_block5
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_5:                                # %entry_ifend6
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movl	%r12d, %r15d
	movq	%r14, 32(%rsp)          # 8-byte Spill
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r14
	movl	$1312, %esi             # imm = 0x520
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#6:                                 # %entry_ifend13
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	%rbp, 24(%rsp)          # 8-byte Spill
	movq	%r14, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r15d, %ecx
	movq	%r8, %rbx
	movq	32(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_7
# BB#8:                                 # %entry_ifend25
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1324, %esi             # imm = 0x52C
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	24(%rsp), %r12          # 8-byte Reload
	je	.LBB1_1
# BB#9:                                 # %entry_ifend36
	movq	48(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	%rbx, %r8
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	%r14, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movl	%ebp, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r15d, %ecx
	movl	%r15d, %ebx
	movq	%r8, %rbp
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_7
# BB#10:                                # %entry_ifend48
	movq	40(%rsp), %r14          # 8-byte Reload
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	48(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	movl	%ebx, %edx
	cmpl	$0, 8(%rax)
	movq	%r13, %rbx
	je	.LBB1_1
# BB#11:                                # %entry_ifend60
	movq	%r15, 16(%rsp)          # 8-byte Spill
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	(%rbp), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edi
	movq	%rdi, (%rsi)
	addq	$8, (%rbp)
	movl	%eax, (%rsp)
	movl	$1332, %edi             # imm = 0x534
	movq	%r14, %rsi
	movl	%edx, %r13d
	movq	%rbp, %rcx
	movq	%rbx, %r8
	movq	112(%rsp), %r15
	movq	%r15, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB1_13
# BB#12:                                # %then_block68
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_13:                               # %entry_ifend69
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbp), %rax
	movq	%r12, %rbx
	movq	%r15, %r12
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$1344, %esi             # imm = 0x540
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	16(%rsp), %rsi          # 8-byte Reload
	je	.LBB1_1
# BB#14:                                # %entry_ifend80
	movq	48(%rsp), %rdx
	movq	$0, (%rbx)
	movq	%rdx, (%rbx)
	movq	(%rbp), %rdx
	movq	$0, (%rdx)
	movq	%rsi, (%rdx)
	movq	(%rbp), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rsi)
	movq	%r15, 8(%rsi)
	addq	$8, (%rbp)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r13d, %ecx
	movl	%r13d, %r15d
	movq	%rbp, %r8
	movq	32(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_7
# BB#15:                                # %entry_ifend92
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	%rbp, 8(%rsp)           # 8-byte Spill
	movq	(%rbp), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 16(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$.Lglobal_string.3, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1356, %esi             # imm = 0x54C
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	24(%rsp), %r12          # 8-byte Reload
	movl	%r15d, %ecx
	je	.LBB1_1
# BB#16:                                # %entry_ifend103
	movq	48(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	8(%rsp), %r8            # 8-byte Reload
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	16(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movl	%ebp, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ecx, %ebx
	movq	%r8, %rbp
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_7
# BB#17:                                # %entry_ifend115
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	48(%rsp), %r8d
	movl	$2, %r9d
	movq	%rbp, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	movl	%ebx, %edx
	cmpl	$0, 8(%rax)
	movq	%r13, %rbx
	je	.LBB1_1
# BB#18:                                # %entry_ifend127
	movq	%r15, 16(%rsp)          # 8-byte Spill
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	(%rbp), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edi
	movq	%rdi, (%rsi)
	addq	$8, (%rbp)
	movl	%eax, (%rsp)
	movl	$1364, %edi             # imm = 0x554
	movq	%r14, %rsi
	movl	%edx, %r13d
	movq	%rbp, %rcx
	movq	%rbx, %r8
	movq	112(%rsp), %r15
	movq	%r15, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB1_20
# BB#19:                                # %then_block135
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_20:                               # %entry_ifend136
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbp), %rax
	movq	%r12, %rbx
	movq	%r15, %r12
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$1376, %esi             # imm = 0x560
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	16(%rsp), %rsi          # 8-byte Reload
	je	.LBB1_1
# BB#21:                                # %entry_ifend147
	movq	48(%rsp), %rdx
	movq	$0, (%rbx)
	movq	%rdx, (%rbx)
	movq	(%rbp), %rdx
	movq	$0, (%rdx)
	movq	%rsi, (%rdx)
	movq	(%rbp), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rsi)
	movq	%r15, 8(%rsi)
	addq	$8, (%rbp)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r13d, %ecx
	movl	%r13d, %r15d
	movq	%rbp, %r8
	movq	32(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_7
# BB#22:                                # %entry_ifend159
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 16(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$.Lglobal_string.4, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1388, %esi             # imm = 0x56C
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	24(%rsp), %r12          # 8-byte Reload
	movl	%r15d, %ecx
	je	.LBB1_1
# BB#23:                                # %entry_ifend170
	movq	48(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	8(%rsp), %r8            # 8-byte Reload
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	16(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movl	%ebp, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ecx, %r15d
	movq	%r8, %rbx
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_7
# BB#24:                                # %entry_ifend182
	movq	%r14, %rbp
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	%rbx, %r14
	movq	(%r14), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 16(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	48(%rsp), %r8d
	movl	$3, %r9d
	movq	%r14, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %ebp
	movl	%ebp, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#25:                                # %entry_ifend194
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	(%r14), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r14)
	movl	%eax, (%rsp)
	movl	$1396, %edi             # imm = 0x574
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	%r14, %rcx
	movq	%r13, %r8
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB1_7
# BB#26:                                # %entry_ifend203
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$1408, %esi             # imm = 0x580
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebp, %ecx
	je	.LBB1_1
# BB#27:                                # %entry_ifend214
	movq	48(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	(%r14), %rdx
	movq	$0, (%rdx)
	movq	16(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r14), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rsi)
	movq	%r15, 8(%rsi)
	addq	$8, (%r14)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r15d
	movq	%r14, %r8
	movq	%r13, %r9
	movq	%r13, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_28
# BB#29:                                # %entry_ifend226
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$.Lglobal_string.5, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1420, %esi             # imm = 0x58C
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	movl	%r15d, %ecx
	je	.LBB1_1
# BB#30:                                # %entry_ifend237
	movq	48(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	8(%rsp), %r14           # 8-byte Reload
	movq	(%r14), %rdx
	movq	$0, (%rdx)
	movq	%r13, (%rdx)
	movq	(%r14), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rsi)
	movl	%ebp, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r14)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r15d
	movq	%r14, %r8
	movq	%r9, %r13
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_31
.LBB1_7:                                # %then_block24
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
.LBB1_31:                               # %entry_ifend249
	movq	40(%rsp), %rbp          # 8-byte Reload
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 16(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	48(%rsp), %r8d
	movl	$4, %r9d
	movq	%r14, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %ebp
	movl	%ebp, %edx
	movq	%r13, %rbx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#32:                                # %entry_ifend261
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	(%r14), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r14)
	movl	%eax, (%rsp)
	movl	$1428, %edi             # imm = 0x594
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	%r14, %rcx
	movq	%rbx, %r8
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB1_28
# BB#33:                                # %entry_ifend270
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$1440, %esi             # imm = 0x5A0
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	movl	%ebp, %ecx
	je	.LBB1_1
# BB#34:                                # %entry_ifend281
	movq	48(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	(%r14), %rdx
	movq	$0, (%rdx)
	movq	16(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r14), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rsi)
	movq	%r15, 8(%rsi)
	addq	$8, (%r14)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r15d
	movq	%r14, %r8
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_28
# BB#35:                                # %entry_ifend293
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$.Lglobal_string.6, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1452, %esi             # imm = 0x5AC
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	movl	%r15d, %ecx
	je	.LBB1_1
# BB#36:                                # %entry_ifend304
	movq	48(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	8(%rsp), %r8            # 8-byte Reload
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	%r13, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movl	%ebp, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%r8, %rbp
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_37
.LBB1_28:                               # %then_block225
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_37:                               # %entry_ifend316
	movq	40(%rsp), %r14          # 8-byte Reload
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	%rbp, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbp, (%r14)
	movl	$1, %eax
	jmp	.LBB1_2
.Lfunc_end1:
	.size	"Tuple5.toString()$$2", .Lfunc_end1-"Tuple5.toString()$$2"
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
	.asciz	"}"
	.size	.Lglobal_string.6, 2


	.section	".note.GNU-stack","",@progbits
