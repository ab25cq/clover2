	.text
	.file	"Tuple1.bc"
	.globl	"Tuple1.equals(Self)$$1"
	.align	16, 0x90
	.type	"Tuple1.equals(Self)$$1",@function
"Tuple1.equals(Self)$$1":               # @"Tuple1.equals(Self)$$1"
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
	subq	$40, %rsp
.Ltmp6:
	.cfi_def_cfa_offset 96
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
	movl	%r9d, %r12d
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	%rsi, %r13
	movq	(%rbx), %rbp
	movq	$0, 24(%rsp)
	movq	%rbp, 24(%rsp)
	movq	8(%rbx), %r15
	movq	$0, 32(%rsp)
	movq	%r15, 32(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r12d, %edx
	movq	%rax, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r12d, %edx
	movq	16(%rsp), %rcx          # 8-byte Reload
	movl	%r15d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#4:                                 # %entry_ifend5
	movq	96(%rsp), %r9
	movq	(%rax), %rax
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	$0, 8(%r13)
	movq	%r15, 8(%r13)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	8(%rsp), %rsi           # 8-byte Reload
	movl	%esi, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r14)
	movl	%esi, (%rsp)
	movl	$332, %edi              # imm = 0x14C
	movq	%rbx, %rsi
	movl	%r12d, %edx
	movq	%r14, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	je	.LBB0_6
# BB#5:                                 # %then_block15
	movq	16(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
.LBB0_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB0_2
.LBB0_6:                                # %entry_ifend16
	movq	(%rbx), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%rbx)
	movl	$1, %eax
.LBB0_2:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end0:
	.size	"Tuple1.equals(Self)$$1", .Lfunc_end0-"Tuple1.equals(Self)$$1"
	.cfi_endproc

	.globl	"Tuple1.toString()$$2"
	.align	16, 0x90
	.type	"Tuple1.toString()$$2",@function
"Tuple1.toString()$$2":                 # @"Tuple1.toString()$$2"
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
	movl	%r9d, %ebp
	movq	%r8, %r13
	movq	%rcx, %rbx
	movq	%rdx, %r14
	movq	%rsi, %r15
	movq	(%rbx), %r12
	movq	$0, 32(%rsp)
	movq	%r12, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, 24(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	96(%rsp), %rcx
	movq	(%rax), %rax
	movq	$0, (%r15)
	movq	%r12, (%r15)
	movq	%rcx, %r12
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	%eax, (%rsp)
	movl	$356, %edi              # imm = 0x164
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r13, %rcx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	je	.LBB1_5
# BB#4:                                 # %then_block5
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_5:                                # %entry_ifend6
	movl	%ebp, 20(%rsp)          # 4-byte Spill
	movq	%r14, 8(%rsp)           # 8-byte Spill
	movq	%r12, %r14
	movq	(%rbx), %r12
	movq	$0, 32(%rsp)
	movq	%r12, 32(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$368, %esi              # imm = 0x170
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#6:                                 # %entry_ifend13
	movq	$0, (%r15)
	movq	%r12, (%r15)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	24(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	addq	$8, (%r13)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%rbx, %r14
	movq	%r14, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %rcx
	movq	%rbx, %rdi
	je	.LBB1_8
# BB#7:                                 # %then_block24
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_8:                                # %entry_ifend25
	movq	(%r14), %r15
	movq	%r14, 24(%rsp)          # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%r15, 32(%rsp)
	movq	(%r13), %rax
	movq	%rcx, %rbp
	movq	%rdi, %r14
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$380, %esi              # imm = 0x17C
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#9:                                 # %entry_ifend36
	movq	$0, (%rbp)
	movq	%r15, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movq	%r12, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	24(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r14, %rdi
	je	.LBB1_11
# BB#10:                                # %then_block47
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
.LBB1_11:                               # %entry_ifend48
	movq	(%rbp), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%rbx, (%rbp)
	movl	$1, %eax
	jmp	.LBB1_2
.Lfunc_end1:
	.size	"Tuple1.toString()$$2", .Lfunc_end1-"Tuple1.toString()$$2"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"tuple {"
	.size	.Lglobal_string, 8

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.asciz	"}"
	.size	.Lglobal_string.2, 2


	.section	".note.GNU-stack","",@progbits
