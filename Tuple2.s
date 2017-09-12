	.text
	.file	"Tuple2.bc"
	.globl	"Tuple2.equals(Self)$$1"
	.align	16, 0x90
	.type	"Tuple2.equals(Self)$$1",@function
"Tuple2.equals(Self)$$1":               # @"Tuple2.equals(Self)$$1"
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
	movl	%r9d, %r15d
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %r13
	movq	%rsi, 24(%rsp)          # 8-byte Spill
	movq	(%rbx), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 40(%rsp)
	movq	%r12, 40(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#4:                                 # %entry_ifend5
	movq	112(%rsp), %r9
	movq	(%rax), %rax
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	16(%rsp), %rsi          # 8-byte Reload
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
	movl	$480, %edi              # imm = 0x1E0
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movq	%r13, %r8
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#6:                                 # %entry_ifend16
	movl	%r15d, 16(%rsp)         # 4-byte Spill
	movq	(%rbx), %r15
	movq	$0, 32(%rsp)
	movq	%r15, 32(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 40(%rsp)
	movq	%r12, 40(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 48(%rsp)
	movq	%rbp, 48(%rsp)
	testb	$1, %bpl
	je	.LBB0_11
# BB#7:                                 # %entry_condend
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	16(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %edx
	movq	%r13, %rcx
	movl	%r15d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#8:                                 # %entry_ifend26
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r13, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#9:                                 # %entry_ifend30
	movq	(%rax), %rax
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
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
	movl	$532, %edi              # imm = 0x214
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	movq	%r13, %r8
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	je	.LBB0_10
.LBB0_5:                                # %then_block15
	movq	%r13, %rdi
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
.LBB0_10:                               # %entry_ifend44
	movq	(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	andl	$1, %ebp
	movq	%rbp, 48(%rsp)
.LBB0_11:                               # %label_and_endpointzzzzzzzzzzzzzzt
	movq	%rbp, (%rbx)
	movl	$1, %eax
	jmp	.LBB0_2
.Lfunc_end0:
	.size	"Tuple2.equals(Self)$$1", .Lfunc_end0-"Tuple2.equals(Self)$$1"
	.cfi_endproc

	.globl	"Tuple2.toString()$$2"
	.align	16, 0x90
	.type	"Tuple2.toString()$$2",@function
"Tuple2.toString()$$2":                 # @"Tuple2.toString()$$2"
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
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rbx, 24(%rsp)          # 8-byte Spill
	movq	%rdx, %r12
	movq	%rsi, %r14
	movq	(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	32(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	96(%rsp), %r9
	movq	(%rax), %rax
	movq	32(%rsp), %rcx
	movq	$0, (%r14)
	movq	%rcx, (%r14)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	%eax, (%rsp)
	movl	$592, %edi              # imm = 0x250
	movq	24(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	%r15, %rcx
	movq	%r12, %r8
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%r14, %rbx
	movq	%r12, %rdi
	je	.LBB1_5
# BB#4:                                 # %then_block5
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_5:                                # %entry_ifend6
	movq	24(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r15), %rax
	movl	%ebp, %r14d
	movq	%rdi, %rbp
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$604, %esi              # imm = 0x25C
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#6:                                 # %entry_ifend13
	movq	32(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	24(%rsp), %rdx          # 8-byte Reload
	movl	%r14d, %ecx
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%r14d, %r12d
	jne	.LBB1_7
# BB#8:                                 # %entry_ifend25
	movq	24(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%r12d, %r14d
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$616, %esi              # imm = 0x268
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#9:                                 # %entry_ifend36
	movq	32(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	24(%rsp), %rdx          # 8-byte Reload
	movl	%r14d, %ecx
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%r14d, %r12d
	jne	.LBB1_7
# BB#10:                                # %entry_ifend48
	movq	24(%rsp), %r13          # 8-byte Reload
	movq	(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 16(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	32(%rsp), %r8d
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%r13, %rsi
	movl	%r12d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#11:                                # %entry_ifend60
	movq	(%rax), %rax
	movq	32(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	%eax, (%rsp)
	movl	$624, %edi              # imm = 0x270
	movq	%r13, %rsi
	movl	%r12d, %edx
	movq	%r15, %rcx
	movq	%rbp, %r8
	movq	96(%rsp), %r14
	movq	%r14, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%rbp, %rdi
	je	.LBB1_13
# BB#12:                                # %then_block68
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_13:                               # %entry_ifend69
	movq	(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r15), %rax
	movl	%r12d, 12(%rsp)         # 4-byte Spill
	movq	%r14, %rbp
	movq	%rdi, %r14
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$636, %esi              # imm = 0x27C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#14:                                # %entry_ifend80
	movq	32(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r14, %rbp
	jne	.LBB1_7
# BB#15:                                # %entry_ifend92
	movq	(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$.Lglobal_string.3, %edi
	callq	create_string_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$648, %esi              # imm = 0x288
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#16:                                # %entry_ifend103
	movq	32(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r14, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_17
.LBB1_7:                                # %then_block24
	movq	%rbp, %rdi
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
.LBB1_17:                               # %entry_ifend115
	movq	(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbp, (%r13)
	movl	$1, %eax
	jmp	.LBB1_2
.Lfunc_end1:
	.size	"Tuple2.toString()$$2", .Lfunc_end1-"Tuple2.toString()$$2"
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
	.asciz	"}"
	.size	.Lglobal_string.3, 2


	.section	".note.GNU-stack","",@progbits
