	.text
	.file	"Path.bc"
	.globl	"Path.to_stat()$$1"
	.align	16, 0x90
	.type	"Path.to_stat()$$1",@function
"Path.to_stat()$$1":                    # @"Path.to_stat()$$1"
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
	subq	$24, %rsp
.Ltmp6:
	.cfi_def_cfa_offset 80
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
	movl	%r9d, 12(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %r12
	movq	%rsi, %r13
	movq	80(%rsp), %rdi
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1984, %esi             # imm = 0x7C0
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movl	$1992, %esi             # imm = 0x7C8
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#5:                                 # %entry_ifend6
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB0_7
# BB#6:                                 # %then_block14
	movq	%r12, %rdi
	callq	get_try_catch_label_name
.LBB0_1:                                # %then_block
	xorl	%eax, %eax
.LBB0_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB0_7:                                # %entry_ifend15
	movq	(%rbx), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%rbx)
	movl	$1, %eax
	jmp	.LBB0_2
.Lfunc_end0:
	.size	"Path.to_stat()$$1", .Lfunc_end0-"Path.to_stat()$$1"
	.cfi_endproc

	.globl	"Path.to_lstat()$$2"
	.align	16, 0x90
	.type	"Path.to_lstat()$$2",@function
"Path.to_lstat()$$2":                   # @"Path.to_lstat()$$2"
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
	subq	$24, %rsp
.Ltmp19:
	.cfi_def_cfa_offset 80
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
	movl	%r9d, 12(%rsp)          # 4-byte Spill
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %r13
	movq	80(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2000, %esi             # imm = 0x7D0
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movl	$2008, %esi             # imm = 0x7D8
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#5:                                 # %entry_ifend6
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	$1, 8(%rcx)
	addq	$8, (%rbx)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_7
# BB#6:                                 # %then_block17
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB1_1:                                # %then_block
	xorl	%eax, %eax
.LBB1_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB1_7:                                # %entry_ifend18
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbp, (%r14)
	movl	$1, %eax
	jmp	.LBB1_2
.Lfunc_end1:
	.size	"Path.to_lstat()$$2", .Lfunc_end1-"Path.to_lstat()$$2"
	.cfi_endproc

	.globl	"Path.toString()$$3"
	.align	16, 0x90
	.type	"Path.toString()$$3",@function
"Path.toString()$$3":                   # @"Path.toString()$$3"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp26:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp27:
	.cfi_def_cfa_offset 32
.Ltmp28:
	.cfi_offset %rbx, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB2_2
.LBB2_1:                                # %then_block
	xorl	%eax, %eax
.LBB2_2:                                # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end2:
	.size	"Path.toString()$$3", .Lfunc_end2-"Path.toString()$$3"
	.cfi_endproc

	.globl	"Path.equals(Self)$$4"
	.align	16, 0x90
	.type	"Path.equals(Self)$$4",@function
"Path.equals(Self)$$4":                 # @"Path.equals(Self)$$4"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp29:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp30:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp31:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp32:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp33:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp34:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp35:
	.cfi_def_cfa_offset 96
.Ltmp36:
	.cfi_offset %rbx, -56
.Ltmp37:
	.cfi_offset %r12, -48
.Ltmp38:
	.cfi_offset %r13, -40
.Ltmp39:
	.cfi_offset %r14, -32
.Ltmp40:
	.cfi_offset %r15, -24
.Ltmp41:
	.cfi_offset %rbp, -16
	movl	%r9d, %r13d
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %r15
	movq	%rsi, 16(%rsp)          # 8-byte Spill
	movq	(%rbx), %rbp
	movq	$0, 24(%rsp)
	movq	%rbp, 24(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 32(%rsp)
	movq	%r12, 32(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#4:                                 # %entry_ifend5
	movq	96(%rsp), %rdi
	movq	(%rax), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movl	$2016, %esi             # imm = 0x7E0
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#5:                                 # %entry_ifend8
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$14, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB3_7
# BB#6:                                 # %then_block18
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB3_1:                                # %then_block
	xorl	%eax, %eax
.LBB3_2:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB3_7:                                # %entry_ifend19
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
	jmp	.LBB3_2
.Lfunc_end3:
	.size	"Path.equals(Self)$$4", .Lfunc_end3-"Path.equals(Self)$$4"
	.cfi_endproc

	.globl	"Path.realpath()$$5"
	.align	16, 0x90
	.type	"Path.realpath()$$5",@function
"Path.realpath()$$5":                   # @"Path.realpath()$$5"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp42:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp43:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp44:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp45:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp46:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp47:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp48:
	.cfi_def_cfa_offset 80
.Ltmp49:
	.cfi_offset %rbx, -56
.Ltmp50:
	.cfi_offset %r12, -48
.Ltmp51:
	.cfi_offset %r13, -40
.Ltmp52:
	.cfi_offset %r14, -32
.Ltmp53:
	.cfi_offset %r15, -24
.Ltmp54:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebx
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %rcx
	movq	%rcx, 8(%rsp)           # 8-byte Spill
	movq	%rsi, %rbp
	movq	(%r14), %r13
	movq	$0, 16(%rsp)
	movq	%r13, 16(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %rdi
	movq	(%rax), %r12
	movl	$2024, %esi             # imm = 0x7E8
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#4:                                 # %entry_ifend3
	movq	$0, (%rbp)
	movq	%r13, (%rbp)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %r12d
	movl	%r12d, %ecx
	movq	%r15, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_5
# BB#6:                                 # %entry_ifend9
	movl	%r12d, %ebx
	movq	(%r14), %r12
	movq	$0, 16(%rsp)
	movq	%r12, 16(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$2032, %esi             # imm = 0x7F0
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#7:                                 # %entry_ifend16
	movq	$0, (%rbp)
	movq	%r12, (%rbp)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r15)
	movl	$49, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB4_8
.LBB4_5:                                # %then_block8
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB4_1:                                # %then_block
	xorl	%eax, %eax
.LBB4_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB4_8:                                # %entry_ifend25
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbp, (%r14)
	movl	$1, %eax
	jmp	.LBB4_2
.Lfunc_end4:
	.size	"Path.realpath()$$5", .Lfunc_end4-"Path.realpath()$$5"
	.cfi_endproc

	.globl	"Path.dirname()$$6"
	.align	16, 0x90
	.type	"Path.dirname()$$6",@function
"Path.dirname()$$6":                    # @"Path.dirname()$$6"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp55:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp56:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp57:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp58:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp59:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp60:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp61:
	.cfi_def_cfa_offset 80
.Ltmp62:
	.cfi_offset %rbx, -56
.Ltmp63:
	.cfi_offset %r12, -48
.Ltmp64:
	.cfi_offset %r13, -40
.Ltmp65:
	.cfi_offset %r14, -32
.Ltmp66:
	.cfi_offset %r15, -24
.Ltmp67:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebx
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %rcx
	movq	%rcx, 8(%rsp)           # 8-byte Spill
	movq	%rsi, %rbp
	movq	(%r14), %r13
	movq	$0, 16(%rsp)
	movq	%r13, 16(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %rdi
	movq	(%rax), %r12
	movl	$2040, %esi             # imm = 0x7F8
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#4:                                 # %entry_ifend3
	movq	$0, (%rbp)
	movq	%r13, (%rbp)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$49, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %r12d
	movl	%r12d, %ecx
	movq	%r15, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB5_5
# BB#6:                                 # %entry_ifend9
	movl	%r12d, %ebx
	movq	(%r14), %r12
	movq	$0, 16(%rsp)
	movq	%r12, 16(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$2048, %esi             # imm = 0x800
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#7:                                 # %entry_ifend16
	movq	$0, (%rbp)
	movq	%r12, (%rbp)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r15)
	movl	$49, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB5_8
.LBB5_5:                                # %then_block8
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB5_1:                                # %then_block
	xorl	%eax, %eax
.LBB5_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB5_8:                                # %entry_ifend25
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbp, (%r14)
	movl	$1, %eax
	jmp	.LBB5_2
.Lfunc_end5:
	.size	"Path.dirname()$$6", .Lfunc_end5-"Path.dirname()$$6"
	.cfi_endproc

	.globl	"Path.basename()$$7"
	.align	16, 0x90
	.type	"Path.basename()$$7",@function
"Path.basename()$$7":                   # @"Path.basename()$$7"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp68:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp69:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp70:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp71:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp72:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp73:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp74:
	.cfi_def_cfa_offset 80
.Ltmp75:
	.cfi_offset %rbx, -56
.Ltmp76:
	.cfi_offset %r12, -48
.Ltmp77:
	.cfi_offset %r13, -40
.Ltmp78:
	.cfi_offset %r14, -32
.Ltmp79:
	.cfi_offset %r15, -24
.Ltmp80:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebx
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %rcx
	movq	%rcx, 8(%rsp)           # 8-byte Spill
	movq	%rsi, %rbp
	movq	(%r14), %r13
	movq	$0, 16(%rsp)
	movq	%r13, 16(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %rdi
	movq	(%rax), %r12
	movl	$2056, %esi             # imm = 0x808
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#4:                                 # %entry_ifend3
	movq	$0, (%rbp)
	movq	%r13, (%rbp)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$50, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %r12d
	movl	%r12d, %ecx
	movq	%r15, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_5
# BB#6:                                 # %entry_ifend9
	movl	%r12d, %ebx
	movq	(%r14), %r12
	movq	$0, 16(%rsp)
	movq	%r12, 16(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$2064, %esi             # imm = 0x810
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#7:                                 # %entry_ifend16
	movq	$0, (%rbp)
	movq	%r12, (%rbp)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r15)
	movl	$49, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB6_8
.LBB6_5:                                # %then_block8
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB6_1:                                # %then_block
	xorl	%eax, %eax
.LBB6_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB6_8:                                # %entry_ifend25
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbp, (%r14)
	movl	$1, %eax
	jmp	.LBB6_2
.Lfunc_end6:
	.size	"Path.basename()$$7", .Lfunc_end6-"Path.basename()$$7"
	.cfi_endproc

	.globl	"Path.extname()$$8"
	.align	16, 0x90
	.type	"Path.extname()$$8",@function
"Path.extname()$$8":                    # @"Path.extname()$$8"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp81:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp82:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp83:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp84:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp85:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp86:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp87:
	.cfi_def_cfa_offset 128
.Ltmp88:
	.cfi_offset %rbx, -56
.Ltmp89:
	.cfi_offset %r12, -48
.Ltmp90:
	.cfi_offset %r13, -40
.Ltmp91:
	.cfi_offset %r14, -32
.Ltmp92:
	.cfi_offset %r15, -24
.Ltmp93:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebp
	movl	%ebp, 12(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %rax
	movq	%rsi, %r12
	movl	$4294967295, %ecx       # imm = 0xFFFFFFFF
	movq	(%r14), %r8
	movq	$0, 16(%rsp)
	movq	%r8, 16(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
	movq	$0, 40(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 24(%rsp)
	movq	%rcx, 24(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rax, %rcx
	movq	%rax, %rbx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %r8
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %rax
	jmp	.LBB7_5
	.align	16, 0x90
.LBB7_35:                               # %label_if_endzzzzzzzzzzzzzzzzzzzzzi
                                        #   in Loop: Header=BB7_5 Depth=1
	movl	32(%rsp), %eax
.LBB7_5:                                # %for_start_pointzzzzzzzzzzzzzzzzzzzzzh
                                        # =>This Inner Loop Header: Depth=1
	decl	%eax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	testl	%eax, %eax
	js	.LBB7_12
# BB#6:                                 # %entry_condend
                                        #   in Loop: Header=BB7_5 Depth=1
	movl	$0, gSigInt(%rip)
	movl	16(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movq	%rbx, %r13
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#7:                                 # %entry_ifend8
                                        #   in Loop: Header=BB7_5 Depth=1
	movq	(%rax), %rbp
	movl	32(%rsp), %ebx
	movl	$2148, %esi             # imm = 0x864
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_1
# BB#8:                                 # %entry_ifend12
                                        #   in Loop: Header=BB7_5 Depth=1
	movq	16(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	24(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	32(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	40(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%r13, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB7_9
# BB#10:                                # %entry_ifend27
                                        #   in Loop: Header=BB7_5 Depth=1
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r14), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	24(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	cmpl	$46, %r13d
	jne	.LBB7_35
# BB#11:                                # %entry_condend39
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %eax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movl	$0, gSigInt(%rip)
.LBB7_12:                               # %label_for_endzzzzzzzzzzzzzzzzzzzzzh
	movq	%rbx, %rbp
	movl	$0, gSigInt(%rip)
	movl	16(%rsp), %ebx
	movl	$2376, %esi             # imm = 0x948
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_1
# BB#13:                                # %entry_ifend49
	movq	16(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	24(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	32(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	40(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%rbp, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB7_9
# BB#14:                                # %entry_ifend64
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r14), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	24(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 40(%rsp)
	movq	%r13, 40(%rsp)
	movl	$0, gSigInt(%rip)
	movl	24(%rsp), %ecx
	cmpl	$-1, %ecx
	sete	%al
	movq	$0, 48(%rsp)
	movzbl	%al, %eax
	movq	%rax, 48(%rsp)
	je	.LBB7_26
# BB#15:                                # %entry_condnotend
	testl	%ecx, %ecx
	sete	%al
	movq	$0, 56(%rsp)
	movzbl	%al, %eax
	movq	%rax, 56(%rsp)
	je	.LBB7_25
# BB#16:                                # %entry_condnotend87
	movl	16(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movq	%rbx, %rbp
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#17:                                # %entry_ifend91
	movq	(%rax), %rbx
	movl	24(%rsp), %r13d
	movl	$2464, %esi             # imm = 0x9A0
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_1
# BB#18:                                # %entry_ifend96
	decl	%r13d
	movq	16(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	24(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	32(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	40(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%rbp, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB7_9
# BB#19:                                # %entry_ifend114
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r14), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	24(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	cmpl	$47, %r13d
	sete	%al
	movq	$0, 64(%rsp)
	movzbl	%al, %eax
	movq	%rax, 64(%rsp)
	je	.LBB7_24
# BB#20:                                # %entry_condnotend133
	movl	24(%rsp), %ebp
	movl	40(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#21:                                # %entry_ifend138
	movq	(%rax), %r13
	movl	$2512, %esi             # imm = 0x9D0
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_1
# BB#22:                                # %entry_ifend141
	movl	%ebp, 8(%rsp)           # 4-byte Spill
	movq	16(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	24(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	32(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	40(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB7_9
# BB#23:                                # %entry_ifend156
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r14), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	24(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	cmpl	%r13d, 8(%rsp)          # 4-byte Folded Reload
	setl	%al
	movzbl	%al, %eax
	movq	%rax, 64(%rsp)
.LBB7_24:                               # %label_or_endpointzzzzzzzzzzzzzzzzzzzzzm
	movq	%rax, 56(%rsp)
.LBB7_25:                               # %label_or_endpointzzzzzzzzzzzzzzzzzzzzzl
	movq	%rax, 48(%rsp)
.LBB7_26:                               # %label_or_endpointzzzzzzzzzzzzzzzzzzzzzk
	movl	$0, gSigInt(%rip)
	testq	%rax, %rax
	je	.LBB7_29
# BB#27:                                # %entry_condend177
	movl	$.Lglobal_string, %edi
	callq	create_path_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	%ebx, %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB7_2
.LBB7_29:                               # %label_elsezzzzzzzzzzzzzzzzzzzzzj
	movl	16(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movq	%rbx, %rbp
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#30:                                # %entry_ifend182
	movq	(%rax), %rbx
	movl	24(%rsp), %r13d
	movl	$2752, %esi             # imm = 0xAC0
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_1
# BB#31:                                # %entry_ifend187
	incl	%r13d
	movq	16(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	24(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	32(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	40(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$13, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%rbp, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB7_9
# BB#32:                                # %entry_ifend208
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r14), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	24(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$2760, %esi             # imm = 0xAC8
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_1
# BB#33:                                # %entry_ifend225
	movq	16(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	24(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	32(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	40(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	addq	$8, (%r15)
	movl	$49, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB7_34
.LBB7_9:                                # %then_block26
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB7_1:                                # %then_block
	xorl	%eax, %eax
.LBB7_2:                                # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB7_34:                               # %entry_ifend240
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r14), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	24(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbp, (%r14)
	movl	$1, %eax
	jmp	.LBB7_2
.Lfunc_end7:
	.size	"Path.extname()$$8", .Lfunc_end7-"Path.extname()$$8"
	.cfi_endproc

	.globl	"Path.read()$$9"
	.align	16, 0x90
	.type	"Path.read()$$9",@function
"Path.read()$$9":                       # @"Path.read()$$9"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp94:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp95:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp96:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp97:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp98:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp99:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp100:
	.cfi_def_cfa_offset 80
.Ltmp101:
	.cfi_offset %rbx, -56
.Ltmp102:
	.cfi_offset %r12, -48
.Ltmp103:
	.cfi_offset %r13, -40
.Ltmp104:
	.cfi_offset %r14, -32
.Ltmp105:
	.cfi_offset %r15, -24
.Ltmp106:
	.cfi_offset %rbp, -16
	movl	%r9d, %r13d
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %rdi
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$2840, %esi             # imm = 0xB18
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB8_1
# BB#4:                                 # %entry_ifend3
	movq	$0, (%r12)
	movq	%rbp, (%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB8_6
# BB#5:                                 # %then_block8
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB8_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB8_2
.LBB8_6:                                # %entry_ifend9
	movq	(%rbx), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%rbx)
	movl	$1, %eax
.LBB8_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end8:
	.size	"Path.read()$$9", .Lfunc_end8-"Path.read()$$9"
	.cfi_endproc

	.globl	"Path.write(Buffer)$$10"
	.align	16, 0x90
	.type	"Path.write(Buffer)$$10",@function
"Path.write(Buffer)$$10":               # @"Path.write(Buffer)$$10"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp107:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp108:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp109:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp110:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp111:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp112:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp113:
	.cfi_def_cfa_offset 96
.Ltmp114:
	.cfi_offset %rbx, -56
.Ltmp115:
	.cfi_offset %r12, -48
.Ltmp116:
	.cfi_offset %r13, -40
.Ltmp117:
	.cfi_offset %r14, -32
.Ltmp118:
	.cfi_offset %r15, -24
.Ltmp119:
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
	je	.LBB9_1
# BB#3:                                 # %entry_ifend
	movq	96(%rsp), %rdi
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$2848, %esi             # imm = 0xB20
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_1
# BB#4:                                 # %entry_ifend5
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	$0, 8(%r13)
	movq	%r15, 8(%r13)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$13, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	16(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB9_6
# BB#5:                                 # %then_block15
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB9_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB9_2
.LBB9_6:                                # %entry_ifend16
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
.LBB9_2:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end9:
	.size	"Path.write(Buffer)$$10", .Lfunc_end9-"Path.write(Buffer)$$10"
	.cfi_endproc

	.globl	"Path.chmod(int)$$11"
	.align	16, 0x90
	.type	"Path.chmod(int)$$11",@function
"Path.chmod(int)$$11":                  # @"Path.chmod(int)$$11"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp120:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp121:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp122:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp123:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp124:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp125:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp126:
	.cfi_def_cfa_offset 96
.Ltmp127:
	.cfi_offset %rbx, -56
.Ltmp128:
	.cfi_offset %r12, -48
.Ltmp129:
	.cfi_offset %r13, -40
.Ltmp130:
	.cfi_offset %r14, -32
.Ltmp131:
	.cfi_offset %r15, -24
.Ltmp132:
	.cfi_offset %rbp, -16
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r13
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	96(%rsp), %rdi
	movq	(%r13), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2856, %esi             # imm = 0xB28
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB10_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r12)
	movq	%rbx, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %rdi
	je	.LBB10_5
# BB#4:                                 # %then_block8
	callq	get_try_catch_label_name
	jmp	.LBB10_1
.LBB10_5:                               # %entry_ifend9
	movq	(%r13), %r15
	movq	$0, 24(%rsp)
	movq	%r15, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	(%r14), %rax
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$2864, %esi             # imm = 0xB30
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB10_1
# BB#6:                                 # %entry_ifend19
	movq	$0, (%r12)
	movq	%r15, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$54, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB10_8
# BB#7:                                 # %then_block32
	callq	get_try_catch_label_name
.LBB10_1:                               # %then_block
	xorl	%eax, %eax
.LBB10_2:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB10_8:                               # %entry_ifend33
	movq	(%r13), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, (%r13)
	movl	$1, %eax
	jmp	.LBB10_2
.Lfunc_end10:
	.size	"Path.chmod(int)$$11", .Lfunc_end10-"Path.chmod(int)$$11"
	.cfi_endproc

	.globl	"Path.lchmod(int)$$12"
	.align	16, 0x90
	.type	"Path.lchmod(int)$$12",@function
"Path.lchmod(int)$$12":                 # @"Path.lchmod(int)$$12"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp133:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp134:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp135:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp136:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp137:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp138:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp139:
	.cfi_def_cfa_offset 96
.Ltmp140:
	.cfi_offset %rbx, -56
.Ltmp141:
	.cfi_offset %r12, -48
.Ltmp142:
	.cfi_offset %r13, -40
.Ltmp143:
	.cfi_offset %r14, -32
.Ltmp144:
	.cfi_offset %r15, -24
.Ltmp145:
	.cfi_offset %rbp, -16
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r13
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	96(%rsp), %rdi
	movq	(%r13), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2872, %esi             # imm = 0xB38
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB11_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r12)
	movq	%rbx, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %rdi
	je	.LBB11_5
# BB#4:                                 # %then_block8
	callq	get_try_catch_label_name
	jmp	.LBB11_1
.LBB11_5:                               # %entry_ifend9
	movq	(%r13), %r15
	movq	$0, 24(%rsp)
	movq	%r15, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	(%r14), %rax
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$2880, %esi             # imm = 0xB40
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB11_1
# BB#6:                                 # %entry_ifend19
	movq	$0, (%r12)
	movq	%r15, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$55, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB11_8
# BB#7:                                 # %then_block32
	callq	get_try_catch_label_name
.LBB11_1:                               # %then_block
	xorl	%eax, %eax
.LBB11_2:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB11_8:                               # %entry_ifend33
	movq	(%r13), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, (%r13)
	movl	$1, %eax
	jmp	.LBB11_2
.Lfunc_end11:
	.size	"Path.lchmod(int)$$12", .Lfunc_end11-"Path.lchmod(int)$$12"
	.cfi_endproc

	.globl	"Path.chown(int,int)$$13"
	.align	16, 0x90
	.type	"Path.chown(int,int)$$13",@function
"Path.chown(int,int)$$13":              # @"Path.chown(int,int)$$13"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp146:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp147:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp148:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp149:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp150:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp151:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp152:
	.cfi_def_cfa_offset 112
.Ltmp153:
	.cfi_offset %rbx, -56
.Ltmp154:
	.cfi_offset %r12, -48
.Ltmp155:
	.cfi_offset %r13, -40
.Ltmp156:
	.cfi_offset %r14, -32
.Ltmp157:
	.cfi_offset %r15, -24
.Ltmp158:
	.cfi_offset %rbp, -16
	movl	%r9d, 28(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, 16(%rsp)          # 8-byte Spill
	movq	%rsi, %r13
	movq	112(%rsp), %rdi
	movq	(%r15), %rbx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movq	8(%r15), %r12
	movq	$0, 40(%rsp)
	movq	%r12, 40(%rsp)
	movq	16(%r15), %rbp
	movq	$0, 48(%rsp)
	movq	%rbp, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2888, %esi             # imm = 0xB48
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB12_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%rbx, (%r13)
	movq	$0, 8(%r13)
	movq	%r12, 8(%r13)
	movq	$0, 16(%r13)
	movq	%rbp, 16(%r13)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB12_5
# BB#4:                                 # %then_block12
	callq	get_try_catch_label_name
	jmp	.LBB12_1
.LBB12_5:                               # %entry_ifend13
	movq	(%r15), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r15), %r12
	movq	$0, 40(%rsp)
	movq	%r12, 40(%rsp)
	movq	16(%r15), %rbp
	movq	$0, 48(%rsp)
	movq	%rbp, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$2896, %esi             # imm = 0xB50
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB12_1
# BB#6:                                 # %entry_ifend26
	movq	$0, (%r13)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, (%r13)
	movq	$0, 8(%r13)
	movq	%r12, 8(%r13)
	movq	$0, 16(%r13)
	movq	%rbp, 16(%r13)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$57, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB12_8
# BB#7:                                 # %then_block44
	callq	get_try_catch_label_name
.LBB12_1:                               # %then_block
	xorl	%eax, %eax
.LBB12_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB12_8:                               # %entry_ifend45
	movq	(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, (%r15)
	movl	$1, %eax
	jmp	.LBB12_2
.Lfunc_end12:
	.size	"Path.chown(int,int)$$13", .Lfunc_end12-"Path.chown(int,int)$$13"
	.cfi_endproc

	.globl	"Path.lchown(int,int)$$14"
	.align	16, 0x90
	.type	"Path.lchown(int,int)$$14",@function
"Path.lchown(int,int)$$14":             # @"Path.lchown(int,int)$$14"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp159:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp160:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp161:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp162:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp163:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp164:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp165:
	.cfi_def_cfa_offset 112
.Ltmp166:
	.cfi_offset %rbx, -56
.Ltmp167:
	.cfi_offset %r12, -48
.Ltmp168:
	.cfi_offset %r13, -40
.Ltmp169:
	.cfi_offset %r14, -32
.Ltmp170:
	.cfi_offset %r15, -24
.Ltmp171:
	.cfi_offset %rbp, -16
	movl	%r9d, 28(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, 16(%rsp)          # 8-byte Spill
	movq	%rsi, %r13
	movq	112(%rsp), %rdi
	movq	(%r15), %rbx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movq	8(%r15), %r12
	movq	$0, 40(%rsp)
	movq	%r12, 40(%rsp)
	movq	16(%r15), %rbp
	movq	$0, 48(%rsp)
	movq	%rbp, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2904, %esi             # imm = 0xB58
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB13_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%rbx, (%r13)
	movq	$0, 8(%r13)
	movq	%r12, 8(%r13)
	movq	$0, 16(%r13)
	movq	%rbp, 16(%r13)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB13_5
# BB#4:                                 # %then_block12
	callq	get_try_catch_label_name
	jmp	.LBB13_1
.LBB13_5:                               # %entry_ifend13
	movq	(%r15), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r15), %r12
	movq	$0, 40(%rsp)
	movq	%r12, 40(%rsp)
	movq	16(%r15), %rbp
	movq	$0, 48(%rsp)
	movq	%rbp, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$2912, %esi             # imm = 0xB60
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB13_1
# BB#6:                                 # %entry_ifend26
	movq	$0, (%r13)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, (%r13)
	movq	$0, 8(%r13)
	movq	%r12, 8(%r13)
	movq	$0, 16(%r13)
	movq	%rbp, 16(%r13)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$58, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB13_8
# BB#7:                                 # %then_block44
	callq	get_try_catch_label_name
.LBB13_1:                               # %then_block
	xorl	%eax, %eax
.LBB13_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB13_8:                               # %entry_ifend45
	movq	(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, (%r15)
	movl	$1, %eax
	jmp	.LBB13_2
.Lfunc_end13:
	.size	"Path.lchown(int,int)$$14", .Lfunc_end13-"Path.lchown(int,int)$$14"
	.cfi_endproc

	.globl	"Path.unlink()$$15"
	.align	16, 0x90
	.type	"Path.unlink()$$15",@function
"Path.unlink()$$15":                    # @"Path.unlink()$$15"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp172:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp173:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp174:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp175:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp176:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp177:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp178:
	.cfi_def_cfa_offset 80
.Ltmp179:
	.cfi_offset %rbx, -56
.Ltmp180:
	.cfi_offset %r12, -48
.Ltmp181:
	.cfi_offset %r13, -40
.Ltmp182:
	.cfi_offset %r14, -32
.Ltmp183:
	.cfi_offset %r15, -24
.Ltmp184:
	.cfi_offset %rbp, -16
	movl	%r9d, %r12d
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %r13
	movq	80(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2920, %esi             # imm = 0xB68
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB14_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbx)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB14_4
# BB#5:                                 # %entry_ifend6
	movq	(%r14), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$2928, %esi             # imm = 0xB70
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB14_1
# BB#6:                                 # %entry_ifend13
	movq	$0, (%r13)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	addq	$8, (%rbx)
	movl	$60, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB14_7
.LBB14_4:                               # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB14_1:                               # %then_block
	xorl	%eax, %eax
.LBB14_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB14_7:                               # %entry_ifend22
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, (%r14)
	movl	$1, %eax
	jmp	.LBB14_2
.Lfunc_end14:
	.size	"Path.unlink()$$15", .Lfunc_end14-"Path.unlink()$$15"
	.cfi_endproc

	.globl	"Path.access(int)$$16"
	.align	16, 0x90
	.type	"Path.access(int)$$16",@function
"Path.access(int)$$16":                 # @"Path.access(int)$$16"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp185:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp186:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp187:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp188:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp189:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp190:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp191:
	.cfi_def_cfa_offset 96
.Ltmp192:
	.cfi_offset %rbx, -56
.Ltmp193:
	.cfi_offset %r12, -48
.Ltmp194:
	.cfi_offset %r13, -40
.Ltmp195:
	.cfi_offset %r14, -32
.Ltmp196:
	.cfi_offset %r15, -24
.Ltmp197:
	.cfi_offset %rbp, -16
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %r13
	movq	%rdx, %r14
	movq	%rsi, %r12
	movq	96(%rsp), %rdi
	movq	(%r13), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2936, %esi             # imm = 0xB78
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB15_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r12)
	movq	%rbx, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r14, %rdi
	je	.LBB15_5
# BB#4:                                 # %then_block8
	callq	get_try_catch_label_name
	jmp	.LBB15_1
.LBB15_5:                               # %entry_ifend9
	movq	(%r13), %r14
	movq	$0, 24(%rsp)
	movq	%r14, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	(%r15), %rax
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$2944, %esi             # imm = 0xB80
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB15_1
# BB#6:                                 # %entry_ifend19
	movq	$0, (%r12)
	movq	%r14, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$61, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB15_8
# BB#7:                                 # %then_block32
	callq	get_try_catch_label_name
.LBB15_1:                               # %then_block
	xorl	%eax, %eax
.LBB15_2:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB15_8:                               # %entry_ifend33
	movq	(%r13), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbp, (%r13)
	movl	$1, %eax
	jmp	.LBB15_2
.Lfunc_end15:
	.size	"Path.access(int)$$16", .Lfunc_end15-"Path.access(int)$$16"
	.cfi_endproc

	.globl	"Path.utime(ulong,ulong)$$17"
	.align	16, 0x90
	.type	"Path.utime(ulong,ulong)$$17",@function
"Path.utime(ulong,ulong)$$17":          # @"Path.utime(ulong,ulong)$$17"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp198:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp199:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp200:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp201:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp202:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp203:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp204:
	.cfi_def_cfa_offset 112
.Ltmp205:
	.cfi_offset %rbx, -56
.Ltmp206:
	.cfi_offset %r12, -48
.Ltmp207:
	.cfi_offset %r13, -40
.Ltmp208:
	.cfi_offset %r14, -32
.Ltmp209:
	.cfi_offset %r15, -24
.Ltmp210:
	.cfi_offset %rbp, -16
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, 24(%rsp)          # 8-byte Spill
	movq	%rsi, %r12
	movq	112(%rsp), %rdi
	movq	(%r15), %rbx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movq	8(%r15), %r13
	movq	$0, 40(%rsp)
	movq	%r13, 40(%rsp)
	movq	16(%r15), %rbp
	movq	$0, 48(%rsp)
	movq	%rbp, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2952, %esi             # imm = 0xB88
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB16_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r12)
	movq	%rbx, (%r12)
	movq	$0, 8(%r12)
	movq	%r13, 8(%r12)
	movq	$0, 16(%r12)
	movq	%rbp, 16(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB16_5
# BB#4:                                 # %then_block12
	callq	get_try_catch_label_name
	jmp	.LBB16_1
.LBB16_5:                               # %entry_ifend13
	movq	(%r15), %rbx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movq	8(%r15), %rbp
	movq	$0, 40(%rsp)
	movq	%rbp, 40(%rsp)
	movq	16(%r15), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$2960, %esi             # imm = 0xB90
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB16_1
# BB#6:                                 # %entry_ifend26
	movq	$0, (%r12)
	movq	%rbx, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	$0, 16(%r12)
	movq	8(%rsp), %rsi           # 8-byte Reload
	movq	%rsi, 16(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	%rsi, 8(%rcx)
	addq	$8, (%r14)
	movl	$62, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB16_8
# BB#7:                                 # %then_block44
	callq	get_try_catch_label_name
.LBB16_1:                               # %then_block
	xorl	%eax, %eax
.LBB16_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB16_8:                               # %entry_ifend45
	movq	(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, (%r15)
	movl	$1, %eax
	jmp	.LBB16_2
.Lfunc_end16:
	.size	"Path.utime(ulong,ulong)$$17", .Lfunc_end16-"Path.utime(ulong,ulong)$$17"
	.cfi_endproc

	.globl	"Path.fnmatch(String,int)$$18"
	.align	16, 0x90
	.type	"Path.fnmatch(String,int)$$18",@function
"Path.fnmatch(String,int)$$18":         # @"Path.fnmatch(String,int)$$18"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp211:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp212:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp213:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp214:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp215:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp216:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp217:
	.cfi_def_cfa_offset 112
.Ltmp218:
	.cfi_offset %rbx, -56
.Ltmp219:
	.cfi_offset %r12, -48
.Ltmp220:
	.cfi_offset %r13, -40
.Ltmp221:
	.cfi_offset %r14, -32
.Ltmp222:
	.cfi_offset %r15, -24
.Ltmp223:
	.cfi_offset %rbp, -16
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r13
	movq	%rdx, %r12
	movq	%rsi, %rbp
	movq	112(%rsp), %rdi
	movq	(%r13), %rbx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r13), %r15
	movq	$0, 48(%rsp)
	movq	%r15, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2968, %esi             # imm = 0xB98
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB17_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	$0, 8(%rbp)
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%rbp)
	movq	$0, 16(%rbp)
	movq	%r15, 16(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB17_5
# BB#4:                                 # %then_block13
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB17_1
.LBB17_5:                               # %entry_ifend14
	movq	(%r13), %r15
	movq	$0, 32(%rsp)
	movq	%r15, 32(%rsp)
	movq	%r12, 8(%rsp)           # 8-byte Spill
	movq	8(%r13), %rbx
	movq	$0, 40(%rsp)
	movq	%rbx, 40(%rsp)
	movq	16(%r13), %r12
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, (%rsp)            # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$2976, %esi             # imm = 0xBA0
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB17_1
# BB#6:                                 # %entry_ifend26
	movq	$0, (%rbp)
	movq	%r15, (%rbp)
	movq	$0, 8(%rbp)
	movq	%rbx, 8(%rbp)
	movq	$0, 16(%rbp)
	movq	%r12, 16(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$63, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB17_8
# BB#7:                                 # %then_block44
	callq	get_try_catch_label_name
.LBB17_1:                               # %then_block
	xorl	%eax, %eax
.LBB17_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB17_8:                               # %entry_ifend45
	movq	(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r13), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%r13)
	movl	$1, %eax
	jmp	.LBB17_2
.Lfunc_end17:
	.size	"Path.fnmatch(String,int)$$18", .Lfunc_end17-"Path.fnmatch(String,int)$$18"
	.cfi_endproc

	.globl	"Path.fnmatch(String)$$19"
	.align	16, 0x90
	.type	"Path.fnmatch(String)$$19",@function
"Path.fnmatch(String)$$19":             # @"Path.fnmatch(String)$$19"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp224:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp225:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp226:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp227:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp228:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp229:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp230:
	.cfi_def_cfa_offset 80
.Ltmp231:
	.cfi_offset %rbx, -56
.Ltmp232:
	.cfi_offset %r12, -48
.Ltmp233:
	.cfi_offset %r13, -40
.Ltmp234:
	.cfi_offset %r14, -32
.Ltmp235:
	.cfi_offset %r15, -24
.Ltmp236:
	.cfi_offset %rbp, -16
	movl	%r9d, 4(%rsp)           # 4-byte Spill
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %rbp
	movq	80(%rsp), %rdi
	movq	(%r14), %r12
	movq	$0, 8(%rsp)
	movq	%r12, 8(%rsp)
	movq	8(%r14), %r13
	movq	$0, 16(%rsp)
	movq	%r13, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2984, %esi             # imm = 0xBA8
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%r12, (%rbp)
	movq	$0, 8(%rbp)
	movq	%r13, 8(%rbp)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	addq	$8, (%rbx)
	movl	$18, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB18_5
# BB#4:                                 # %then_block15
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB18_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB18_2
.LBB18_5:                               # %entry_ifend16
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbp, (%r14)
	movl	$1, %eax
.LBB18_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end18:
	.size	"Path.fnmatch(String)$$19", .Lfunc_end18-"Path.fnmatch(String)$$19"
	.cfi_endproc

	.globl	"Path.link(String)$$20"
	.align	16, 0x90
	.type	"Path.link(String)$$20",@function
"Path.link(String)$$20":                # @"Path.link(String)$$20"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp237:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp238:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp239:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp240:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp241:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp242:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp243:
	.cfi_def_cfa_offset 96
.Ltmp244:
	.cfi_offset %rbx, -56
.Ltmp245:
	.cfi_offset %r12, -48
.Ltmp246:
	.cfi_offset %r13, -40
.Ltmp247:
	.cfi_offset %r14, -32
.Ltmp248:
	.cfi_offset %r15, -24
.Ltmp249:
	.cfi_offset %rbp, -16
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r13
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	96(%rsp), %rdi
	movq	(%r13), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2992, %esi             # imm = 0xBB0
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB19_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r12)
	movq	%rbx, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %rdi
	je	.LBB19_5
# BB#4:                                 # %then_block8
	callq	get_try_catch_label_name
	jmp	.LBB19_1
.LBB19_5:                               # %entry_ifend9
	movq	(%r13), %r15
	movq	$0, 24(%rsp)
	movq	%r15, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	(%r14), %rax
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$3000, %esi             # imm = 0xBB8
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB19_1
# BB#6:                                 # %entry_ifend19
	movq	$0, (%r12)
	movq	%r15, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$64, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB19_8
# BB#7:                                 # %then_block32
	callq	get_try_catch_label_name
.LBB19_1:                               # %then_block
	xorl	%eax, %eax
.LBB19_2:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB19_8:                               # %entry_ifend33
	movq	(%r13), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, (%r13)
	movl	$1, %eax
	jmp	.LBB19_2
.Lfunc_end19:
	.size	"Path.link(String)$$20", .Lfunc_end19-"Path.link(String)$$20"
	.cfi_endproc

	.globl	"Path.symlink(String)$$21"
	.align	16, 0x90
	.type	"Path.symlink(String)$$21",@function
"Path.symlink(String)$$21":             # @"Path.symlink(String)$$21"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp250:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp251:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp252:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp253:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp254:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp255:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp256:
	.cfi_def_cfa_offset 96
.Ltmp257:
	.cfi_offset %rbx, -56
.Ltmp258:
	.cfi_offset %r12, -48
.Ltmp259:
	.cfi_offset %r13, -40
.Ltmp260:
	.cfi_offset %r14, -32
.Ltmp261:
	.cfi_offset %r15, -24
.Ltmp262:
	.cfi_offset %rbp, -16
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r13
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	96(%rsp), %rdi
	movq	(%r13), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3008, %esi             # imm = 0xBC0
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r12)
	movq	%rbx, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %rdi
	je	.LBB20_5
# BB#4:                                 # %then_block8
	callq	get_try_catch_label_name
	jmp	.LBB20_1
.LBB20_5:                               # %entry_ifend9
	movq	(%r13), %r15
	movq	$0, 24(%rsp)
	movq	%r15, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	(%r14), %rax
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$3016, %esi             # imm = 0xBC8
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#6:                                 # %entry_ifend19
	movq	$0, (%r12)
	movq	%r15, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$65, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB20_8
# BB#7:                                 # %then_block32
	callq	get_try_catch_label_name
.LBB20_1:                               # %then_block
	xorl	%eax, %eax
.LBB20_2:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB20_8:                               # %entry_ifend33
	movq	(%r13), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, (%r13)
	movl	$1, %eax
	jmp	.LBB20_2
.Lfunc_end20:
	.size	"Path.symlink(String)$$21", .Lfunc_end20-"Path.symlink(String)$$21"
	.cfi_endproc

	.globl	"Path.readlink()$$22"
	.align	16, 0x90
	.type	"Path.readlink()$$22",@function
"Path.readlink()$$22":                  # @"Path.readlink()$$22"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp263:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp264:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp265:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp266:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp267:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp268:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp269:
	.cfi_def_cfa_offset 80
.Ltmp270:
	.cfi_offset %rbx, -56
.Ltmp271:
	.cfi_offset %r12, -48
.Ltmp272:
	.cfi_offset %r13, -40
.Ltmp273:
	.cfi_offset %r14, -32
.Ltmp274:
	.cfi_offset %r15, -24
.Ltmp275:
	.cfi_offset %rbp, -16
	movl	%r9d, %r12d
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %r13
	movq	80(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3024, %esi             # imm = 0xBD0
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB21_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbx)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB21_4
# BB#5:                                 # %entry_ifend6
	movq	(%r14), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$3032, %esi             # imm = 0xBD8
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB21_1
# BB#6:                                 # %entry_ifend13
	movq	$0, (%r13)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	addq	$8, (%rbx)
	movl	$66, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB21_7
.LBB21_4:                               # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB21_1:                               # %then_block
	xorl	%eax, %eax
.LBB21_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB21_7:                               # %entry_ifend22
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbp, (%r14)
	movl	$1, %eax
	jmp	.LBB21_2
.Lfunc_end21:
	.size	"Path.readlink()$$22", .Lfunc_end21-"Path.readlink()$$22"
	.cfi_endproc

	.globl	"Path.rename(String)$$23"
	.align	16, 0x90
	.type	"Path.rename(String)$$23",@function
"Path.rename(String)$$23":              # @"Path.rename(String)$$23"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp276:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp277:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp278:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp279:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp280:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp281:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp282:
	.cfi_def_cfa_offset 96
.Ltmp283:
	.cfi_offset %rbx, -56
.Ltmp284:
	.cfi_offset %r12, -48
.Ltmp285:
	.cfi_offset %r13, -40
.Ltmp286:
	.cfi_offset %r14, -32
.Ltmp287:
	.cfi_offset %r15, -24
.Ltmp288:
	.cfi_offset %rbp, -16
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r13
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	96(%rsp), %rdi
	movq	(%r13), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3040, %esi             # imm = 0xBE0
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r12)
	movq	%rbx, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %rdi
	je	.LBB22_5
# BB#4:                                 # %then_block8
	callq	get_try_catch_label_name
	jmp	.LBB22_1
.LBB22_5:                               # %entry_ifend9
	movq	(%r13), %r15
	movq	$0, 24(%rsp)
	movq	%r15, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	(%r14), %rax
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$3048, %esi             # imm = 0xBE8
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#6:                                 # %entry_ifend19
	movq	$0, (%r12)
	movq	%r15, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$67, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB22_8
# BB#7:                                 # %then_block32
	callq	get_try_catch_label_name
.LBB22_1:                               # %then_block
	xorl	%eax, %eax
.LBB22_2:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB22_8:                               # %entry_ifend33
	movq	(%r13), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, (%r13)
	movl	$1, %eax
	jmp	.LBB22_2
.Lfunc_end22:
	.size	"Path.rename(String)$$23", .Lfunc_end22-"Path.rename(String)$$23"
	.cfi_endproc

	.globl	"Path.truncate(ulong)$$24"
	.align	16, 0x90
	.type	"Path.truncate(ulong)$$24",@function
"Path.truncate(ulong)$$24":             # @"Path.truncate(ulong)$$24"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp289:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp290:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp291:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp292:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp293:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp294:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp295:
	.cfi_def_cfa_offset 96
.Ltmp296:
	.cfi_offset %rbx, -56
.Ltmp297:
	.cfi_offset %r12, -48
.Ltmp298:
	.cfi_offset %r13, -40
.Ltmp299:
	.cfi_offset %r14, -32
.Ltmp300:
	.cfi_offset %r15, -24
.Ltmp301:
	.cfi_offset %rbp, -16
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r13
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	96(%rsp), %rdi
	movq	(%r13), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3056, %esi             # imm = 0xBF0
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r12)
	movq	%rbx, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_4
# BB#5:                                 # %entry_ifend9
	movq	(%r13), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$3064, %esi             # imm = 0xBF8
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#6:                                 # %entry_ifend19
	movq	$0, (%r12)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	addq	$8, (%r14)
	movl	$68, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB23_7
.LBB23_4:                               # %then_block8
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB23_1:                               # %then_block
	xorl	%eax, %eax
.LBB23_2:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB23_7:                               # %entry_ifend33
	movq	(%r13), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, (%r13)
	movl	$1, %eax
	jmp	.LBB23_2
.Lfunc_end23:
	.size	"Path.truncate(ulong)$$24", .Lfunc_end23-"Path.truncate(ulong)$$24"
	.cfi_endproc

	.globl	"Path.chdir()$$25"
	.align	16, 0x90
	.type	"Path.chdir()$$25",@function
"Path.chdir()$$25":                     # @"Path.chdir()$$25"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp302:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp303:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp304:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp305:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp306:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp307:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp308:
	.cfi_def_cfa_offset 80
.Ltmp309:
	.cfi_offset %rbx, -56
.Ltmp310:
	.cfi_offset %r12, -48
.Ltmp311:
	.cfi_offset %r13, -40
.Ltmp312:
	.cfi_offset %r14, -32
.Ltmp313:
	.cfi_offset %r15, -24
.Ltmp314:
	.cfi_offset %rbp, -16
	movl	%r9d, %r12d
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %r13
	movq	80(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3072, %esi             # imm = 0xC00
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB24_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbx)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB24_4
# BB#5:                                 # %entry_ifend6
	movq	(%r14), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$3080, %esi             # imm = 0xC08
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB24_1
# BB#6:                                 # %entry_ifend13
	movq	$0, (%r13)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	addq	$8, (%rbx)
	movl	$70, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB24_7
.LBB24_4:                               # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB24_1:                               # %then_block
	xorl	%eax, %eax
.LBB24_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB24_7:                               # %entry_ifend22
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, (%r14)
	movl	$1, %eax
	jmp	.LBB24_2
.Lfunc_end24:
	.size	"Path.chdir()$$25", .Lfunc_end24-"Path.chdir()$$25"
	.cfi_endproc

	.globl	"Path.rmdir()$$26"
	.align	16, 0x90
	.type	"Path.rmdir()$$26",@function
"Path.rmdir()$$26":                     # @"Path.rmdir()$$26"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp315:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp316:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp317:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp318:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp319:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp320:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp321:
	.cfi_def_cfa_offset 80
.Ltmp322:
	.cfi_offset %rbx, -56
.Ltmp323:
	.cfi_offset %r12, -48
.Ltmp324:
	.cfi_offset %r13, -40
.Ltmp325:
	.cfi_offset %r14, -32
.Ltmp326:
	.cfi_offset %r15, -24
.Ltmp327:
	.cfi_offset %rbp, -16
	movl	%r9d, %r12d
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %r13
	movq	80(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3088, %esi             # imm = 0xC10
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB25_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbx)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB25_4
# BB#5:                                 # %entry_ifend6
	movq	(%r14), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$3096, %esi             # imm = 0xC18
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB25_1
# BB#6:                                 # %entry_ifend13
	movq	$0, (%r13)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	addq	$8, (%rbx)
	movl	$72, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB25_7
.LBB25_4:                               # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB25_1:                               # %then_block
	xorl	%eax, %eax
.LBB25_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB25_7:                               # %entry_ifend22
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, (%r14)
	movl	$1, %eax
	jmp	.LBB25_2
.Lfunc_end25:
	.size	"Path.rmdir()$$26", .Lfunc_end25-"Path.rmdir()$$26"
	.cfi_endproc

	.globl	"Path.mkdir(int)$$27"
	.align	16, 0x90
	.type	"Path.mkdir(int)$$27",@function
"Path.mkdir(int)$$27":                  # @"Path.mkdir(int)$$27"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp328:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp329:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp330:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp331:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp332:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp333:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp334:
	.cfi_def_cfa_offset 96
.Ltmp335:
	.cfi_offset %rbx, -56
.Ltmp336:
	.cfi_offset %r12, -48
.Ltmp337:
	.cfi_offset %r13, -40
.Ltmp338:
	.cfi_offset %r14, -32
.Ltmp339:
	.cfi_offset %r15, -24
.Ltmp340:
	.cfi_offset %rbp, -16
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r13
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	96(%rsp), %rdi
	movq	(%r13), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3104, %esi             # imm = 0xC20
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r12)
	movq	%rbx, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %rdi
	je	.LBB26_5
# BB#4:                                 # %then_block8
	callq	get_try_catch_label_name
	jmp	.LBB26_1
.LBB26_5:                               # %entry_ifend9
	movq	(%r13), %r15
	movq	$0, 24(%rsp)
	movq	%r15, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	(%r14), %rax
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$3112, %esi             # imm = 0xC28
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#6:                                 # %entry_ifend19
	movq	$0, (%r12)
	movq	%r15, (%r12)
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$73, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB26_8
# BB#7:                                 # %then_block32
	callq	get_try_catch_label_name
.LBB26_1:                               # %then_block
	xorl	%eax, %eax
.LBB26_2:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB26_8:                               # %entry_ifend33
	movq	(%r13), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, (%r13)
	movl	$1, %eax
	jmp	.LBB26_2
.Lfunc_end26:
	.size	"Path.mkdir(int)$$27", .Lfunc_end26-"Path.mkdir(int)$$27"
	.cfi_endproc

	.globl	"Path.mkdir()$$28"
	.align	16, 0x90
	.type	"Path.mkdir()$$28",@function
"Path.mkdir()$$28":                     # @"Path.mkdir()$$28"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp341:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp342:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp343:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp344:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp345:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp346:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp347:
	.cfi_def_cfa_offset 80
.Ltmp348:
	.cfi_offset %rbx, -56
.Ltmp349:
	.cfi_offset %r12, -48
.Ltmp350:
	.cfi_offset %r13, -40
.Ltmp351:
	.cfi_offset %r14, -32
.Ltmp352:
	.cfi_offset %r15, -24
.Ltmp353:
	.cfi_offset %rbp, -16
	movl	%r9d, %r13d
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	80(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3120, %esi             # imm = 0xC30
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r12)
	movq	%rbp, (%r12)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbx)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r13d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%r13d, %ebp
	jne	.LBB27_4
# BB#5:                                 # %entry_ifend6
	movq	(%r14), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$3128, %esi             # imm = 0xC38
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebp, %ecx
	je	.LBB27_1
# BB#6:                                 # %entry_ifend13
	movq	$0, (%r12)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movq	%rdx, (%r12)
	movq	(%rbx), %rdx
	movq	$0, (%rdx)
	movq	%r13, (%rdx)
	movq	(%rbx), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rsi)
	movq	$493, 8(%rsi)           # imm = 0x1ED
	addq	$8, (%rbx)
	movl	$73, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB27_7
.LBB27_4:                               # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB27_1:                               # %then_block
	xorl	%eax, %eax
.LBB27_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB27_7:                               # %entry_ifend25
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, (%r14)
	movl	$1, %eax
	jmp	.LBB27_2
.Lfunc_end27:
	.size	"Path.mkdir()$$28", .Lfunc_end27-"Path.mkdir()$$28"
	.cfi_endproc

	.globl	"Path.entries()$$29"
	.align	16, 0x90
	.type	"Path.entries()$$29",@function
"Path.entries()$$29":                   # @"Path.entries()$$29"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp354:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp355:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp356:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp357:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp358:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp359:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp360:
	.cfi_def_cfa_offset 80
.Ltmp361:
	.cfi_offset %rbx, -56
.Ltmp362:
	.cfi_offset %r12, -48
.Ltmp363:
	.cfi_offset %r13, -40
.Ltmp364:
	.cfi_offset %r14, -32
.Ltmp365:
	.cfi_offset %r15, -24
.Ltmp366:
	.cfi_offset %rbp, -16
	movl	%r9d, %r12d
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %r13
	movq	80(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3136, %esi             # imm = 0xC40
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB28_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbx)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB28_4
# BB#5:                                 # %entry_ifend6
	movq	(%r14), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$3144, %esi             # imm = 0xC48
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB28_1
# BB#6:                                 # %entry_ifend13
	movq	$0, (%r13)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	addq	$8, (%rbx)
	movl	$4, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB28_7
.LBB28_4:                               # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB28_1:                               # %then_block
	xorl	%eax, %eax
.LBB28_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB28_7:                               # %entry_ifend22
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbp, (%r14)
	movl	$1, %eax
	jmp	.LBB28_2
.Lfunc_end28:
	.size	"Path.entries()$$29", .Lfunc_end28-"Path.entries()$$29"
	.cfi_endproc

	.globl	"Path.glob(String,int)$$30"
	.align	16, 0x90
	.type	"Path.glob(String,int)$$30",@function
"Path.glob(String,int)$$30":            # @"Path.glob(String,int)$$30"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp367:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp368:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp369:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp370:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp371:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp372:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp373:
	.cfi_def_cfa_offset 112
.Ltmp374:
	.cfi_offset %rbx, -56
.Ltmp375:
	.cfi_offset %r12, -48
.Ltmp376:
	.cfi_offset %r13, -40
.Ltmp377:
	.cfi_offset %r14, -32
.Ltmp378:
	.cfi_offset %r15, -24
.Ltmp379:
	.cfi_offset %rbp, -16
	movl	%r9d, 28(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, 16(%rsp)          # 8-byte Spill
	movq	%rsi, %r13
	movq	112(%rsp), %rdi
	movq	(%r15), %rbx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movq	8(%r15), %r12
	movq	$0, 40(%rsp)
	movq	%r12, 40(%rsp)
	movq	16(%r15), %rbp
	movq	$0, 48(%rsp)
	movq	%rbp, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3156, %esi             # imm = 0xC54
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB29_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%rbx, (%r13)
	movq	$0, 8(%r13)
	movq	%r12, 8(%r13)
	movq	$0, 16(%r13)
	movq	%rbp, 16(%r13)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB29_5
# BB#4:                                 # %then_block12
	callq	get_try_catch_label_name
	jmp	.LBB29_1
.LBB29_5:                               # %entry_ifend13
	movq	(%r15), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r15), %r12
	movq	$0, 40(%rsp)
	movq	%r12, 40(%rsp)
	movq	16(%r15), %rbp
	movq	$0, 48(%rsp)
	movq	%rbp, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$3164, %esi             # imm = 0xC5C
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB29_1
# BB#6:                                 # %entry_ifend26
	movq	$0, (%r13)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, (%r13)
	movq	$0, 8(%r13)
	movq	%r12, 8(%r13)
	movq	$0, 16(%r13)
	movq	%rbp, 16(%r13)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB29_8
# BB#7:                                 # %then_block44
	callq	get_try_catch_label_name
.LBB29_1:                               # %then_block
	xorl	%eax, %eax
.LBB29_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB29_8:                               # %entry_ifend45
	movq	(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%r15)
	movl	$1, %eax
	jmp	.LBB29_2
.Lfunc_end29:
	.size	"Path.glob(String,int)$$30", .Lfunc_end29-"Path.glob(String,int)$$30"
	.cfi_endproc

	.globl	"Path.glob(String)$$31"
	.align	16, 0x90
	.type	"Path.glob(String)$$31",@function
"Path.glob(String)$$31":                # @"Path.glob(String)$$31"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp380:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp381:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp382:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp383:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp384:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp385:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp386:
	.cfi_def_cfa_offset 96
.Ltmp387:
	.cfi_offset %rbx, -56
.Ltmp388:
	.cfi_offset %r12, -48
.Ltmp389:
	.cfi_offset %r13, -40
.Ltmp390:
	.cfi_offset %r14, -32
.Ltmp391:
	.cfi_offset %r15, -24
.Ltmp392:
	.cfi_offset %rbp, -16
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, %r12
	movq	%rsi, %r15
	movq	96(%rsp), %rdi
	movq	(%r14), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	8(%r14), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3176, %esi             # imm = 0xC68
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB30_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r15)
	movq	%rbx, (%r15)
	movq	$0, 8(%r15)
	movq	%rbp, 8(%r15)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r12, %rdi
	je	.LBB30_5
# BB#4:                                 # %then_block8
	callq	get_try_catch_label_name
	jmp	.LBB30_1
.LBB30_5:                               # %entry_ifend9
	movq	(%r14), %rbp
	movq	$0, 24(%rsp)
	movq	%rbp, 24(%rsp)
	movq	8(%r14), %r12
	movq	$0, 32(%rsp)
	movq	%r12, 32(%rsp)
	movq	(%r13), %rax
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$3184, %esi             # imm = 0xC70
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB30_1
# BB#6:                                 # %entry_ifend19
	movq	$0, (%r15)
	movq	%rbp, (%r15)
	movq	$0, 8(%r15)
	movq	%r12, 8(%r15)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	addq	$8, (%r13)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB30_8
# BB#7:                                 # %then_block35
	callq	get_try_catch_label_name
.LBB30_1:                               # %then_block
	xorl	%eax, %eax
.LBB30_2:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB30_8:                               # %entry_ifend36
	movq	(%r14), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%rbp, (%r14)
	movl	$1, %eax
	jmp	.LBB30_2
.Lfunc_end30:
	.size	"Path.glob(String)$$31", .Lfunc_end30-"Path.glob(String)$$31"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.zero	1
	.size	.Lglobal_string, 1


	.section	".note.GNU-stack","",@progbits
