	.text
	.file	"Tuple4.bc"
	.globl	"Tuple4.equals(Self)$$1"
	.align	16, 0x90
	.type	"Tuple4.equals(Self)$$1",@function
"Tuple4.equals(Self)$$1":               # @"Tuple4.equals(Self)$$1"
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
	subq	$72, %rsp
.Ltmp6:
	.cfi_def_cfa_offset 128
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
	movl	%r9d, %r15d
	movq	%r8, %r12
	movq	%rcx, %r13
	movq	%rdx, %r14
	movq	%rsi, 24(%rsp)          # 8-byte Spill
	movq	(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	8(%r13), %rbx
	movq	$0, 40(%rsp)
	movq	%rbx, 40(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#4:                                 # %entry_ifend5
	movq	128(%rsp), %r9
	movq	(%rax), %rax
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	$0, 8(%rcx)
	movq	%rbx, 8(%rcx)
	movq	%r12, %rbx
	movq	(%rbx), %rsi
	movq	$0, (%rsi)
	movq	16(%rsp), %rdi          # 8-byte Reload
	movl	%edi, %edx
	movq	%rdx, (%rsi)
	movq	(%rbx), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rsi)
	movl	%eax, %eax
	movq	%rax, 8(%rsi)
	addq	$8, (%rbx)
	movl	%edi, (%rsp)
	movl	$776, %edi              # imm = 0x308
	movq	%r13, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	movq	%r14, %r8
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movl	%r15d, %r12d
	movq	%r14, %rbp
	je	.LBB0_6
# BB#5:                                 # %then_block15
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB0_1:                                # %then_block
	xorl	%eax, %eax
.LBB0_2:                                # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB0_6:                                # %entry_ifend16
	movq	(%r13), %r15
	movq	$0, 32(%rsp)
	movq	%r15, 32(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%rbx), %rax
	movq	%r13, %r14
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	testb	$1, %r13b
	je	.LBB0_17
# BB#7:                                 # %entry_condend
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	movq	%rbp, %rcx
	movl	%r15d, %r8d
	movq	%r15, %r13
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r14, %r15
	movq	%rbp, %r14
	movl	%r12d, %ebp
	je	.LBB0_1
# BB#8:                                 # %entry_ifend26
	movq	(%rax), %r12
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#9:                                 # %entry_ifend30
	movq	(%rax), %rax
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rsi
	movq	$0, (%rsi)
	movl	%r12d, %edx
	movq	%rdx, (%rsi)
	movq	(%rbx), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rsi)
	movl	%eax, %eax
	movq	%rax, 8(%rsi)
	addq	$8, (%rbx)
	movl	%r12d, (%rsp)
	movl	$828, %edi              # imm = 0x33C
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movq	%r14, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	je	.LBB0_11
# BB#10:                                # %then_block43
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB0_1
.LBB0_11:                               # %entry_ifend44
	movq	(%r15), %r12
	movq	$0, 32(%rsp)
	movq	%r12, 32(%rsp)
	movq	8(%r15), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 56(%rsp)
	movq	%r13, 56(%rsp)
	testb	$1, %r13b
	je	.LBB0_16
# BB#12:                                # %entry_condend58
	movl	$2, %r9d
	movq	%rbx, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %r13
	movq	%r13, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#13:                                # %entry_ifend62
	movq	(%rax), %r14
	movl	$2, %r9d
	movq	%rbx, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r13, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#14:                                # %entry_ifend66
	movq	(%rax), %rax
	movq	%r12, %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	$0, 8(%rdx)
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%rdx)
	movq	(%rbx), %rsi
	movq	$0, (%rsi)
	movl	%r14d, %edx
	movq	%rdx, (%rsi)
	movq	(%rbx), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rsi)
	movl	%eax, %eax
	movq	%rax, 8(%rsi)
	addq	$8, (%rbx)
	movl	%r14d, (%rsp)
	movl	$880, %edi              # imm = 0x370
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movq	%r13, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%r15, %rcx
	jne	.LBB0_15
# BB#18:                                # %entry_ifend80
	movq	%r13, %r12
	movq	(%rcx), %r15
	movq	$0, 32(%rsp)
	movq	%r15, 32(%rsp)
	movq	8(%rcx), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%rbx), %rax
	movq	%rcx, %r14
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	testb	$1, %r13b
	je	.LBB0_23
# BB#19:                                # %entry_condend94
	movl	$3, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r12, %r13
	movq	%r13, %rcx
	movl	%r15d, %r8d
	movq	%r15, 8(%rsp)           # 8-byte Spill
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movl	%ebp, %r15d
	movq	%r14, %rbp
	je	.LBB0_1
# BB#20:                                # %entry_ifend98
	movq	(%rax), %r14
	movl	$3, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#21:                                # %entry_ifend102
	movq	(%rax), %rax
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, (%r12)
	movq	$0, 8(%r12)
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%r12)
	movq	(%rbx), %rsi
	movq	$0, (%rsi)
	movl	%r14d, %edx
	movq	%rdx, (%rsi)
	movq	(%rbx), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rsi)
	movl	%eax, %eax
	movq	%rax, 8(%rsi)
	addq	$8, (%rbx)
	movl	%r14d, (%rsp)
	movl	$932, %edi              # imm = 0x3A4
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	movq	%r13, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%rbp, %rcx
	je	.LBB0_22
.LBB0_15:                               # %then_block79
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB0_1
.LBB0_22:                               # %entry_ifend116
	movq	(%rcx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rcx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%rbx), %rax
	movq	%rcx, %r14
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	andl	$1, %r13d
	movq	%r13, 64(%rsp)
.LBB0_23:                               # %label_and_endpointzzzzzzzzzzzzzzy
	andl	$1, %r13d
	movq	%r13, 56(%rsp)
	movq	%r14, %r15
.LBB0_16:                               # %label_and_endpointzzzzzzzzzzzzzzx
	andl	$1, %r13d
	movq	%r13, 48(%rsp)
	movq	%r15, %r14
.LBB0_17:                               # %label_and_endpointzzzzzzzzzzzzzzw
	movq	%r13, (%r14)
	movl	$1, %eax
	jmp	.LBB0_2
.Lfunc_end0:
	.size	"Tuple4.equals(Self)$$1", .Lfunc_end0-"Tuple4.equals(Self)$$1"
	.cfi_endproc

	.globl	"Tuple4.toString()$$2"
	.align	16, 0x90
	.type	"Tuple4.toString()$$2",@function
"Tuple4.toString()$$2":                 # @"Tuple4.toString()$$2"
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
	subq	$72, %rsp
.Ltmp19:
	.cfi_def_cfa_offset 128
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
	movl	%r9d, %r14d
	movq	%r8, %rbx
	movq	%rcx, %rbp
	movq	%rbp, 56(%rsp)          # 8-byte Spill
	movq	%rdx, %r12
	movq	%rsi, %r15
	movq	(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	64(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movl	%r13d, 48(%rsp)         # 4-byte Spill
	movq	128(%rsp), %r9
	movq	(%rax), %rax
	movq	64(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	%rbx, %r13
	movq	(%r13), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r13)
	movl	%eax, (%rsp)
	movl	$1064, %edi             # imm = 0x428
	movq	56(%rsp), %rsi          # 8-byte Reload
	movl	%r14d, %edx
	movq	%r13, %rcx
	movq	%r12, %r8
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%r15, %rbp
	movq	%r12, %r15
	je	.LBB1_5
# BB#4:                                 # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_5:                                # %entry_ifend6
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r13), %rax
	movq	%rbp, %r12
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$1076, %esi             # imm = 0x434
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	48(%rsp), %edx          # 4-byte Reload
	je	.LBB1_1
# BB#6:                                 # %entry_ifend13
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	%r12, 40(%rsp)          # 8-byte Spill
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	addq	$8, (%r13)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%r14d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%r14d, %r12d
	movq	%r15, %rbp
	jne	.LBB1_7
# BB#8:                                 # %entry_ifend25
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%r13, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r14
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$1088, %esi             # imm = 0x440
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r12d, %ebx
	je	.LBB1_1
# BB#9:                                 # %entry_ifend36
	movq	64(%rsp), %rcx
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	%r14, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%ebx, %ecx
	movq	%r8, %r15
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%ebx, %r12d
	jne	.LBB1_7
# BB#10:                                # %entry_ifend48
	movq	56(%rsp), %r14          # 8-byte Reload
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%r15, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 48(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	64(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	40(%rsp), %r15          # 8-byte Reload
	movl	%r12d, %r13d
	je	.LBB1_1
# BB#11:                                # %entry_ifend60
	movq	(%rax), %rax
	movq	64(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	%rbx, %r12
	movq	(%r12), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r12)
	movl	%eax, (%rsp)
	movl	$1096, %edi             # imm = 0x448
	movq	56(%rsp), %rsi          # 8-byte Reload
	movl	%r13d, %edx
	movq	%r12, %rcx
	movq	%rbp, %r8
	movq	128(%rsp), %r14
	movq	%r14, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movl	%r13d, %ebx
	movq	%rbp, %rdi
	je	.LBB1_13
# BB#12:                                # %then_block68
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_13:                               # %entry_ifend69
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r12), %rax
	movq	%r15, %rbp
	movl	%ebx, 36(%rsp)          # 4-byte Spill
	movq	%rdi, %r15
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$1108, %esi             # imm = 0x454
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#14:                                # %entry_ifend80
	movq	64(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r12)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	36(%rsp), %r13d         # 4-byte Reload
	movl	%r13d, %ecx
	movq	%r12, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %rbp
	jne	.LBB1_7
# BB#15:                                # %entry_ifend92
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%r12, %rbx
	movq	%rbx, 24(%rsp)          # 8-byte Spill
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$.Lglobal_string.3, %edi
	callq	create_string_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$1120, %esi             # imm = 0x460
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	40(%rsp), %rdx          # 8-byte Reload
	je	.LBB1_1
# BB#16:                                # %entry_ifend103
	movq	64(%rsp), %rcx
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	24(%rsp), %r8           # 8-byte Reload
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r12, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%r13d, %ecx
	movq	%r8, %r15
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_7
# BB#17:                                # %entry_ifend115
	movq	56(%rsp), %r14          # 8-byte Reload
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%r15, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 48(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	64(%rsp), %r8d
	movl	$2, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	40(%rsp), %r15          # 8-byte Reload
	je	.LBB1_1
# BB#18:                                # %entry_ifend127
	movq	(%rax), %rax
	movq	64(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	%rbx, %r12
	movq	(%r12), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r12)
	movl	%eax, (%rsp)
	movl	$1128, %edi             # imm = 0x468
	movq	56(%rsp), %rsi          # 8-byte Reload
	movl	%r13d, %edx
	movq	%r12, %rcx
	movq	%rbp, %r8
	movq	128(%rsp), %r14
	movq	%r14, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%rbp, %rdi
	je	.LBB1_20
# BB#19:                                # %then_block135
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_20:                               # %entry_ifend136
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r12), %rax
	movq	%r15, %rbp
	movq	%rdi, 16(%rsp)          # 8-byte Spill
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$1140, %esi             # imm = 0x474
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#21:                                # %entry_ifend147
	movq	64(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	%r15, 8(%rcx)
	addq	$8, (%r12)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%r13d, %ecx
	movq	%r12, %r8
	movq	16(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_7
# BB#22:                                # %entry_ifend159
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%r12, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$.Lglobal_string.4, %edi
	callq	create_string_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$1152, %esi             # imm = 0x480
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rbp, %r9
	je	.LBB1_1
# BB#23:                                # %entry_ifend170
	movq	64(%rsp), %rsi
	movq	$0, (%rdx)
	movq	%rsi, (%rdx)
	movq	%rbx, %r14
	movq	(%r14), %rdx
	movq	$0, (%rdx)
	movq	%r12, (%rdx)
	movq	(%r14), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rsi)
	movl	%r15d, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r14)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	%r9, %r12
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_25
# BB#24:                                # %then_block181
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_25:                               # %entry_ifend182
	movq	56(%rsp), %rbx          # 8-byte Reload
	movq	(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 48(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	64(%rsp), %r8d
	movl	$3, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %ebx
	movl	%ebx, %edx
	movq	%r12, %rbp
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	40(%rsp), %rdx          # 8-byte Reload
	je	.LBB1_1
# BB#26:                                # %entry_ifend194
	movq	(%rax), %rax
	movq	64(%rsp), %rcx
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	%rdx, %r13
	movq	(%r14), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r14)
	movl	%eax, (%rsp)
	movl	$1160, %edi             # imm = 0x488
	movq	56(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r14, %rcx
	movq	%rbp, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	je	.LBB1_27
.LBB1_7:                                # %then_block24
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB1_1:                                # %then_block
	xorl	%eax, %eax
.LBB1_2:                                # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB1_27:                               # %entry_ifend203
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$1172, %esi             # imm = 0x494
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebx, %ecx
	movq	%rbp, %r9
	je	.LBB1_1
# BB#28:                                # %entry_ifend214
	movq	64(%rsp), %rdx
	movq	$0, (%r13)
	movq	%rdx, (%r13)
	movq	(%r14), %rdx
	movq	$0, (%rdx)
	movq	48(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r14), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rsi)
	movq	%r15, 8(%rsi)
	addq	$8, (%r14)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r15d
	movq	%r14, %r8
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_29
# BB#30:                                # %entry_ifend226
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
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
	movl	$1184, %esi             # imm = 0x4A0
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r15d, %ecx
	movq	%rbx, %r9
	je	.LBB1_1
# BB#31:                                # %entry_ifend237
	movq	64(%rsp), %rsi
	movq	$0, (%rdx)
	movq	%rsi, (%rdx)
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
	movq	56(%rsp), %rdx          # 8-byte Reload
	movq	%r14, %r8
	movq	%r14, %rbp
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_32
.LBB1_29:                               # %then_block225
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_32:                               # %entry_ifend249
	movq	56(%rsp), %r14          # 8-byte Reload
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
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
	.size	"Tuple4.toString()$$2", .Lfunc_end1-"Tuple4.toString()$$2"
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
	.asciz	"}"
	.size	.Lglobal_string.5, 2


	.section	".note.GNU-stack","",@progbits
