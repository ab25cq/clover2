	.text
	.file	"Tuple3.bc"
	.globl	"Tuple3.equals(Self)$$1"
	.align	16, 0x90
	.type	"Tuple3.equals(Self)$$1",@function
"Tuple3.equals(Self)$$1":               # @"Tuple3.equals(Self)$$1"
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
	subq	$88, %rsp
.Ltmp6:
	.cfi_def_cfa_offset 144
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
	movq	%rsi, 48(%rsp)          # 8-byte Spill
	movq	(%r13), %rbp
	movq	$0, 56(%rsp)
	movq	%rbp, 56(%rsp)
	movq	8(%r13), %rbx
	movq	$0, 64(%rsp)
	movq	%rbx, 64(%rsp)
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
	movq	%rax, 40(%rsp)          # 8-byte Spill
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
	movq	144(%rsp), %r9
	movq	(%rax), %rax
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	$0, 8(%rcx)
	movq	%rbx, 8(%rcx)
	movq	(%r12), %rsi
	movq	$0, (%rsi)
	movq	40(%rsp), %rdi          # 8-byte Reload
	movl	%edi, %edx
	movq	%rdx, (%rsi)
	movq	(%r12), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rsi)
	movl	%eax, %eax
	movq	%rax, 8(%rsi)
	addq	$8, (%r12)
	movl	%edi, (%rsp)
	movl	$628, %edi              # imm = 0x274
	movq	%r13, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	%r12, %rbx
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
	addq	$88, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB0_6:                                # %entry_ifend16
	movq	(%r13), %r14
	movq	$0, 56(%rsp)
	movq	%r14, 56(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbx), %rax
	movq	%r13, 32(%rsp)          # 8-byte Spill
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r15
	movq	$0, 72(%rsp)
	movq	%r13, 72(%rsp)
	testb	$1, %r13b
	je	.LBB0_18
# BB#7:                                 # %entry_condend
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	%r12d, %edx
	movq	%rbp, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%rbp, %r13
	movl	%r12d, %ebp
	je	.LBB0_1
# BB#8:                                 # %entry_ifend26
	movq	(%rax), %rbx
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	%r13, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#9:                                 # %entry_ifend30
	movq	(%rax), %rax
	movq	48(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%r14, (%r12)
	movq	$0, 8(%r12)
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%r12)
	movq	%r15, %rcx
	movq	(%rcx), %rsi
	movq	$0, (%rsi)
	movl	%ebx, %edx
	movq	%rdx, (%rsi)
	movq	(%rcx), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rcx)
	movq	$0, 8(%rsi)
	movl	%eax, %eax
	movq	%rax, 8(%rsi)
	addq	$8, (%rcx)
	movl	%ebx, (%rsp)
	movl	$680, %edi              # imm = 0x2A8
	movq	32(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r13, %r8
	movq	144(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%rbx, %rcx
	je	.LBB0_11
# BB#10:                                # %then_block43
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB0_1
.LBB0_11:                               # %entry_ifend44
	movl	%ebp, 28(%rsp)          # 4-byte Spill
	movq	%r13, 40(%rsp)          # 8-byte Spill
	movq	(%rcx), %r14
	movq	$0, 56(%rsp)
	movq	%r14, 56(%rsp)
	movq	8(%rcx), %rbp
	movq	$0, 64(%rsp)
	movq	%rbp, 64(%rsp)
	movq	%r15, %rbx
	movq	(%rbx), %rax
	movq	%rcx, %r15
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 80(%rsp)
	movq	%r13, 80(%rsp)
	testb	$1, %r13b
	je	.LBB0_17
# BB#12:                                # %entry_condend58
	movq	%rbp, %r13
	movl	$2, %r9d
	movq	%rbx, %rdi
	movq	%r15, %rsi
	movl	28(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %edx
	movq	40(%rsp), %r15          # 8-byte Reload
	movq	%r15, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#13:                                # %entry_ifend62
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movl	$2, %r9d
	movq	%rbx, %rdi
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#14:                                # %entry_ifend66
	movq	(%rax), %rax
	movq	$0, (%r12)
	movq	%r14, (%r12)
	movq	$0, 8(%r12)
	movq	%r13, 8(%r12)
	movq	%rbx, %rcx
	movq	(%rcx), %rsi
	movq	$0, (%rsi)
	movq	16(%rsp), %rdi          # 8-byte Reload
	movl	%edi, %edx
	movq	%rdx, (%rsi)
	movq	(%rcx), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rcx)
	movq	$0, 8(%rsi)
	movl	%eax, %eax
	movq	%rax, 8(%rsi)
	addq	$8, (%rcx)
	movl	%edi, (%rsp)
	movl	$732, %edi              # imm = 0x2DC
	movq	32(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%rcx, %rbp
	movq	%r15, %r8
	movq	144(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%r15, %rdi
	movq	%rbx, %rcx
	je	.LBB0_16
# BB#15:                                # %then_block79
	callq	get_try_catch_label_name
	jmp	.LBB0_1
.LBB0_16:                               # %entry_ifend80
	movq	(%rcx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%rcx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%rbp, %rbx
	movq	(%rbx), %rax
	movq	%rcx, %r15
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	andl	$1, %r13d
	movq	%r13, 80(%rsp)
.LBB0_17:                               # %label_and_endpointzzzzzzzzzzzzzzv
	movq	%r15, 32(%rsp)          # 8-byte Spill
	andl	$1, %r13d
	movq	%r13, 72(%rsp)
.LBB0_18:                               # %label_and_endpointzzzzzzzzzzzzzzu
	movq	32(%rsp), %rax          # 8-byte Reload
	movq	%r13, (%rax)
	movl	$1, %eax
	jmp	.LBB0_2
.Lfunc_end0:
	.size	"Tuple3.equals(Self)$$1", .Lfunc_end0-"Tuple3.equals(Self)$$1"
	.cfi_endproc

	.globl	"Tuple3.toString()$$2"
	.align	16, 0x90
	.type	"Tuple3.toString()$$2",@function
"Tuple3.toString()$$2":                 # @"Tuple3.toString()$$2"
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
	movl	%r9d, %r15d
	movq	%r8, %rbx
	movq	%rcx, %rbp
	movq	%rbp, 40(%rsp)          # 8-byte Spill
	movq	%rdx, %r12
	movq	%rsi, %r14
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
	movl	%r15d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movl	%r13d, 32(%rsp)         # 4-byte Spill
	movq	112(%rsp), %r9
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%r14)
	movq	%rcx, (%r14)
	movq	%rbx, %r13
	movq	(%r13), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r13)
	movl	%eax, (%rsp)
	movl	$828, %edi              # imm = 0x33C
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%r15d, %edx
	movq	%r13, %rcx
	movq	%r12, %r8
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movl	%r15d, %ebx
	movq	%r12, %r15
	jne	.LBB1_4
# BB#5:                                 # %entry_ifend6
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r13), %rax
	movq	%r14, %rbp
	movl	%ebx, %r14d
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$840, %esi              # imm = 0x348
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	32(%rsp), %edx          # 4-byte Reload
	je	.LBB1_1
# BB#6:                                 # %entry_ifend13
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	addq	$8, (%r13)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r14d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %rbx
	jne	.LBB1_7
# BB#8:                                 # %entry_ifend25
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	%r13, %r12
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	%r12, %r15
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$852, %esi              # imm = 0x354
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#9:                                 # %entry_ifend36
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	%r15, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r14d, %ecx
	movq	%rbx, %r13
	movq	%r8, %rbx
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%r14d, %r12d
	jne	.LBB1_10
# BB#11:                                # %entry_ifend48
	movq	40(%rsp), %r14          # 8-byte Reload
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 32(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	48(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movl	%r12d, %r15d
	je	.LBB1_1
# BB#12:                                # %entry_ifend60
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	(%rbx), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%rbx)
	movl	%eax, (%rsp)
	movl	$860, %edi              # imm = 0x35C
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	movq	%rbx, %r12
	movq	%r13, %r8
	movq	112(%rsp), %rbx
	movq	%rbx, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%r13, %rdi
	je	.LBB1_14
# BB#13:                                # %then_block68
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_14:                               # %entry_ifend69
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	%rbx, %r13
	movq	%r12, %rbx
	movq	(%rbx), %rax
	movl	%r15d, 28(%rsp)         # 4-byte Spill
	movq	%rdi, %r15
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$872, %esi              # imm = 0x368
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#15:                                # %entry_ifend80
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	%rbx, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	28(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r8, %r13
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%ebx, %r12d
	jne	.LBB1_4
# BB#16:                                # %entry_ifend92
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	%r13, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 32(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r13
	movl	$.Lglobal_string.3, %edi
	callq	create_string_object
	movl	%r12d, %ebx
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$884, %esi              # imm = 0x374
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#17:                                # %entry_ifend103
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	%rbp, 16(%rsp)          # 8-byte Spill
	movq	%r13, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r8, %r12
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%ebx, %ecx
	movq	%r15, %r13
	je	.LBB1_18
.LBB1_10:                               # %then_block47
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_18:                               # %entry_ifend115
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 32(%rsp)          # 8-byte Spill
	movl	%ecx, %r15d
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	48(%rsp), %r8d
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	16(%rsp), %r14          # 8-byte Reload
	je	.LBB1_1
# BB#19:                                # %entry_ifend127
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	$0, (%r14)
	movq	%rcx, (%r14)
	movq	(%r12), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r12)
	movl	%eax, (%rsp)
	movl	$892, %edi              # imm = 0x37C
	movq	40(%rsp), %rsi          # 8-byte Reload
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	%r13, %r8
	movq	112(%rsp), %rbx
	movq	%rbx, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%r14, %rbp
	movq	%r13, %rdi
	je	.LBB1_21
# BB#20:                                # %then_block135
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_21:                               # %entry_ifend136
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	%rbx, %r14
	movq	%r12, %rbx
	movq	(%rbx), %rax
	movl	%r15d, %r13d
	movq	%rdi, %r15
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$904, %esi              # imm = 0x388
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#22:                                # %entry_ifend147
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	%rbx, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
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
	movl	%r13d, %ecx
	movl	%r13d, %r14d
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_23
.LBB1_4:                                # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_23:                               # %entry_ifend159
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 32(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r13
	movl	$.Lglobal_string.4, %edi
	callq	create_string_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$916, %esi              # imm = 0x394
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r14d, %ecx
	je	.LBB1_1
# BB#24:                                # %entry_ifend170
	movq	48(%rsp), %rdx
	movq	$0, (%rbp)
	movq	%rdx, (%rbp)
	movq	%r13, %r8
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	32(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movl	%r12d, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%r8, %rbp
	movq	%r15, %r9
	movq	%r15, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_25
.LBB1_7:                                # %then_block24
	movq	%rbx, %rdi
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
.LBB1_25:                               # %entry_ifend182
	movq	40(%rsp), %r13          # 8-byte Reload
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	%rbp, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbp, (%r13)
	movl	$1, %eax
	jmp	.LBB1_2
.Lfunc_end1:
	.size	"Tuple3.toString()$$2", .Lfunc_end1-"Tuple3.toString()$$2"
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
	.asciz	"}"
	.size	.Lglobal_string.4, 2


	.section	".note.GNU-stack","",@progbits
