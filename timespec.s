	.text
	.file	"timespec.bc"
	.globl	"timespec.minus(Self)$$1"
	.align	16, 0x90
	.type	"timespec.minus(Self)$$1",@function
"timespec.minus(Self)$$1":              # @"timespec.minus(Self)$$1"
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
	movl	%r9d, 36(%rsp)          # 4-byte Spill
	movq	%r8, 24(%rsp)           # 8-byte Spill
	movq	%rcx, %r13
	movq	%rdx, 40(%rsp)          # 8-byte Spill
	movq	%rsi, %rbp
	movq	128(%rsp), %rbx
	movq	(%r13), %r14
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movq	8(%r13), %r12
	movq	$0, 56(%rsp)
	movq	%r12, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$236, %esi
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$248, %esi
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#4:                                 # %entry_ifend3
	movq	$0, (%rbp)
	movq	%r14, (%rbp)
	movq	$0, 8(%rbp)
	movq	%r12, 8(%rbp)
	movq	$0, 16(%rbp)
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbx)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	36(%rsp), %r15d         # 4-byte Reload
	movl	%r15d, %ecx
	movq	%rbx, %r8
	movq	40(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB0_6
# BB#5:                                 # %then_block12
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB0_1
.LBB0_6:                                # %entry_ifend13
	movq	(%r13), %r12
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movq	%rbp, 8(%rsp)           # 8-byte Spill
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 64(%rsp)
	movq	%rbp, 64(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r13, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#7:                                 # %entry_ifend26
	movq	(%rax), %rbp
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r13, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#8:                                 # %entry_ifend30
	subq	(%rax), %rbp
	movl	$0, (%rsp)
	movq	%rbx, %rdi
	movq	%r13, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	movq	%rbp, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB0_1
# BB#9:                                 # %entry_ifend33
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r13, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#10:                                # %entry_ifend38
	movq	(%rax), %rbp
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r13, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#11:                                # %entry_ifend42
	subq	(%rax), %rbp
	movl	$1, (%rsp)
	movq	%rbx, %rdi
	movq	%r13, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	movq	%rbp, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB0_1
# BB#12:                                # %entry_ifend46
	movl	$0, gSigInt(%rip)
	movq	8(%rsp), %rax           # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB0_2
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
.Lfunc_end0:
	.size	"timespec.minus(Self)$$1", .Lfunc_end0-"timespec.minus(Self)$$1"
	.cfi_endproc

	.globl	"timespec.toString()$$2"
	.align	16, 0x90
	.type	"timespec.toString()$$2",@function
"timespec.toString()$$2":               # @"timespec.toString()$$2"
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
	subq	$40, %rsp
.Ltmp19:
	.cfi_def_cfa_offset 96
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
	movl	%r9d, %ebx
	movl	%ebx, 28(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %rbp
	movq	%rdx, %r15
	movq	%rsi, 16(%rsp)          # 8-byte Spill
	movq	(%rbp), %r13
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbp, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rbx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	create_ulong
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#4:                                 # %entry_ifend4
	movq	(%rax), %rdi
	callq	create_ulong
	movq	%r15, %rbp
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movq	(%r14), %rax
	movq	$0, (%rax)
	movl	%r12d, %ecx
	movq	%rcx, (%rax)
	movq	(%r14), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r14)
	movq	$0, 8(%rax)
	movl	%r15d, %ecx
	movq	%rbp, %r15
	movq	96(%rsp), %rbp
	movq	%rcx, 8(%rax)
	addq	$8, (%r14)
	movq	%rbp, (%rsp)
	movl	$2, %r8d
	movl	$276, %r9d              # imm = 0x114
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%r15, %rcx
	callq	run_create_carray
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#5:                                 # %entry_ifend11
	movq	(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$284, %esi              # imm = 0x11C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#6:                                 # %entry_ifend14
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	addq	$8, (%r14)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_8
# BB#7:                                 # %then_block24
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB1_1:                                # %then_block
	xorl	%eax, %eax
.LBB1_2:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB1_8:                                # %entry_ifend25
	movq	(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%rbx)
	movl	$1, %eax
	jmp	.LBB1_2
.Lfunc_end1:
	.size	"timespec.toString()$$2", .Lfunc_end1-"timespec.toString()$$2"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"%lu.%09lu sec"
	.size	.Lglobal_string, 14


	.section	".note.GNU-stack","",@progbits
