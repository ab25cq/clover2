	.text
	.file	"Hash.bc"
	.globl	"Hash.equals(Self)$$3"
	.align	16, 0x90
	.type	"Hash.equals(Self)$$3",@function
"Hash.equals(Self)$$3":                 # @"Hash.equals(Self)$$3"
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
	movq	%rcx, %rbx
	movq	%rdx, %r14
	movq	%rsi, 56(%rsp)          # 8-byte Spill
	movq	(%rbx), %rbp
	movq	$0, 64(%rsp)
	movq	%rbp, 64(%rsp)
	movq	8(%rbx), %r13
	movq	$0, 72(%rsp)
	movq	%r13, 72(%rsp)
	movq	$0, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#4:                                 # %entry_ifend5
	movq	%r12, %rdx
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	movq	48(%rsp), %rcx          # 8-byte Reload
	cmpl	%eax, %ecx
	je	.LBB0_7
# BB#5:                                 # %entry_condend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB0_2
.LBB0_7:                                # %label_if_endzzzzzzzzzzzzzx
	movq	144(%rsp), %rax
	movq	$0, 80(%rsp)
	movq	$1, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movq	%r14, %r12
	movq	%r12, 32(%rsp)
	movl	$0, 24(%rsp)
	movl	$3, 16(%rsp)
	movl	$2, 8(%rsp)
	movl	$91, (%rsp)
	movl	$1996, %ecx             # imm = 0x7CC
	movl	$140, %r8d
	movl	$2136, %r9d             # imm = 0x858
	movq	%rdx, %r14
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movq	%rax, %rdx
	callq	run_create_block_object
	movl	%eax, 48(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$2228, %esi             # imm = 0x8B4
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#8:                                 # %entry_ifend10
	movq	56(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rbp, (%rdx)
	movq	$0, 8(%rdx)
	movq	%r13, 8(%rdx)
	movq	$0, 16(%rdx)
	movq	$1, 16(%rdx)
	movq	(%r14), %rsi
	movq	$0, (%rsi)
	movl	%ebp, %edx
	movq	%rdx, (%rsi)
	movq	(%r14), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rsi)
	movl	48(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rsi)
	addq	$8, (%r14)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r15d, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r12, %rdi
	je	.LBB0_10
# BB#9:                                 # %then_block22
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
.LBB0_10:                               # %entry_ifend23
	movq	(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%rbx), %rbp
	movq	$0, 80(%rsp)
	movq	%rbp, 80(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB0_2
.Lfunc_end0:
	.size	"Hash.equals(Self)$$3", .Lfunc_end0-"Hash.equals(Self)$$3"
	.cfi_endproc

	.globl	"Hash.length()$$4"
	.align	16, 0x90
	.type	"Hash.length()$$4",@function
"Hash.length()$$4":                     # @"Hash.length()$$4"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp13:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp14:
	.cfi_def_cfa_offset 32
.Ltmp15:
	.cfi_offset %rbx, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB1_2
.LBB1_1:                                # %then_block
	xorl	%eax, %eax
.LBB1_2:                                # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end1:
	.size	"Hash.length()$$4", .Lfunc_end1-"Hash.length()$$4"
	.cfi_endproc

	.globl	"Hash.clear()$$5"
	.align	16, 0x90
	.type	"Hash.clear()$$5",@function
"Hash.clear()$$5":                      # @"Hash.clear()$$5"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp16:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp17:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp18:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp19:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp20:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp21:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp22:
	.cfi_def_cfa_offset 80
.Ltmp23:
	.cfi_offset %rbx, -56
.Ltmp24:
	.cfi_offset %r12, -48
.Ltmp25:
	.cfi_offset %r13, -40
.Ltmp26:
	.cfi_offset %r14, -32
.Ltmp27:
	.cfi_offset %r15, -24
.Ltmp28:
	.cfi_offset %rbp, -16
	movl	%r9d, %r15d
	movq	%r8, %r12
	movq	%rcx, %rbx
	movq	%rdx, %r14
	movq	80(%rsp), %rax
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movq	%rax, (%rsp)
	xorl	%r8d, %r8d
	movl	$2236, %r9d             # imm = 0x8BC
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %r13
	movl	$2244, %esi             # imm = 0x8C4
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#4:                                 # %entry_ifend3
	movq	%rax, %rdi
	movl	%r13d, %esi
	callq	create_array_object
	movq	%rbp, %r13
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %r9d
	movq	%r13, %rbp
	movl	$0, (%rsp)
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB2_1
# BB#5:                                 # %entry_ifend6
	movl	$0, gSigInt(%rip)
	movq	80(%rsp), %rax
	movq	%rax, (%rsp)
	xorl	%r8d, %r8d
	movl	$2256, %r9d             # imm = 0x8D0
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#6:                                 # %entry_ifend10
	movq	(%rax), %rax
	movl	%eax, %r9d
	movl	$2, (%rsp)
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB2_1
# BB#7:                                 # %entry_ifend13
	movl	$0, gSigInt(%rip)
	movl	$1, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB2_1
# BB#8:                                 # %entry_ifend17
	movl	$0, gSigInt(%rip)
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB2_2
.LBB2_1:                                # %then_block
	xorl	%eax, %eax
.LBB2_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end2:
	.size	"Hash.clear()$$5", .Lfunc_end2-"Hash.clear()$$5"
	.cfi_endproc

	.globl	"Hash.put(GenericsParametorClass0,GenericsParametorClass1)$$6"
	.align	16, 0x90
	.type	"Hash.put(GenericsParametorClass0,GenericsParametorClass1)$$6",@function
"Hash.put(GenericsParametorClass0,GenericsParametorClass1)$$6": # @"Hash.put(GenericsParametorClass0,GenericsParametorClass1)$$6"
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
	subq	$72, %rsp
.Ltmp35:
	.cfi_def_cfa_offset 128
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
	movl	%r9d, %ebx
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, %rbp
	movq	%rsi, %r12
	movq	(%r15), %r8
	movq	$0, 32(%rsp)
	movq	%r8, 32(%rsp)
	movq	8(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %r13
	movl	32(%rsp), %r8d
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#4:                                 # %entry_ifend7
	movq	128(%rsp), %r9
	addl	%r13d, %r13d
	movq	(%rax), %rax
	cmpl	%eax, %r13d
	jb	.LBB3_9
# BB#5:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r13d
	movl	$2292, %esi             # imm = 0x8F4
	movq	%r9, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#6:                                 # %entry_ifend11
	movq	32(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	40(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	48(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	56(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbp, %rdi
	je	.LBB3_8
# BB#7:                                 # %then_block24
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_8:                                # %entry_ifend25
	movq	%rdi, %rbp
	movq	(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	24(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	32(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	128(%rsp), %r9
.LBB3_9:                                # %label_if_endzzzzzzzzzzzzzz
	movl	$0, gSigInt(%rip)
	movq	40(%rsp), %rax
	movq	32(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	$0, 8(%r12)
	movq	%rax, 8(%r12)
	movq	48(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	56(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	%eax, (%rsp)
	movl	$2356, %edi             # imm = 0x934
	movq	%r15, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	movq	%rbp, %r8
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB3_10
# BB#11:                                # %entry_ifend56
	movq	(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	24(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	32(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	32(%rsp), %r8d
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#12:                                # %entry_ifend76
	movq	%rbp, %rcx
	movl	%ebx, %ebp
	movq	(%rax), %rsi
	testl	%esi, %esi
	je	.LBB3_13
# BB#14:                                # %entry_ifend79
	xorl	%edx, %edx
	movl	%r13d, %eax
	divl	%esi
	movq	$0, 56(%rsp)
	movq	%rdx, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 64(%rsp)
	movq	%rdx, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	%ebp, %ebx
	movq	%rcx, %rbp
	jmp	.LBB3_15
.LBB3_38:                               # %entry_condend239
                                        #   in Loop: Header=BB3_15 Depth=1
	movl	$0, gSigInt(%rip)
	movq	$0, 64(%rsp)
	movl	%r13d, %ebx
	movq	%rdx, %rbp
.LBB3_15:                               # %entry_condend83
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#16:                                # %entry_ifend87
                                        #   in Loop: Header=BB3_15 Depth=1
	movq	(%rax), %r8
	movl	64(%rsp), %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#17:                                # %entry_ifend91
                                        #   in Loop: Header=BB3_15 Depth=1
	movq	(%rax), %r13
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	movq	(%rax), %r8
	movl	8(%rax), %eax
	testl	%r13d, %r13d
	je	.LBB3_18
# BB#26:                                # %label_elsezzzzzzzzzzzzzzc
                                        #   in Loop: Header=BB3_15 Depth=1
	testl	%eax, %eax
	movl	%ebx, %r13d
	je	.LBB3_1
# BB#27:                                # %entry_ifend163
                                        #   in Loop: Header=BB3_15 Depth=1
	movl	64(%rsp), %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r13d, %edx
	movq	%rbp, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#28:                                # %entry_ifend168
                                        #   in Loop: Header=BB3_15 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r13d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#29:                                # %entry_ifend171
                                        #   in Loop: Header=BB3_15 Depth=1
	movq	(%rax), %rax
	movq	40(%rsp), %rcx
	movq	32(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	48(%rsp), %rdx
	movq	$0, 16(%r12)
	movq	%rdx, 16(%r12)
	movq	56(%rsp), %rdx
	movq	$0, 24(%r12)
	movq	%rdx, 24(%r12)
	movq	64(%rsp), %rdx
	movq	$0, 32(%r12)
	movq	%rdx, 32(%r12)
	movq	(%r14), %rdx
	movq	$0, (%rdx)
	movl	%eax, %esi
	movq	%rsi, (%rdx)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movl	%ecx, %ecx
	movq	%rcx, 8(%rdx)
	addq	$8, (%r14)
	movl	%eax, (%rsp)
	movl	$2572, %edi             # imm = 0xA0C
	movq	%r15, %rsi
	movl	%r13d, %edx
	movq	%r14, %rcx
	movq	%rbp, %r8
	movq	%rbp, %rbx
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB3_30
# BB#31:                                # %entry_ifend192
                                        #   in Loop: Header=BB3_15 Depth=1
	movq	(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	24(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	32(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	testb	$1, %bpl
	jne	.LBB3_32
# BB#36:                                # %label_if_endzzzzzzzzzzzzzzd
                                        #   in Loop: Header=BB3_15 Depth=1
	movl	64(%rsp), %ebp
	incl	%ebp
	movq	$0, 64(%rsp)
	movq	%rbp, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r13d, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#37:                                # %entry_ifend235
                                        #   in Loop: Header=BB3_15 Depth=1
	movq	%rbx, %rdx
	movq	(%rax), %rax
	cmpl	%eax, %ebp
	je	.LBB3_38
# BB#39:                                # %label_elifzzzzzzzzzzzzzze1a
                                        #   in Loop: Header=BB3_15 Depth=1
	movl	64(%rsp), %eax
	cmpl	56(%rsp), %eax
	movl	%r13d, %ebx
	movq	%rdx, %rbp
	jne	.LBB3_15
# BB#40:                                # %entry_condend246
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r13d
	movl	$2872, %esi             # imm = 0xB38
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#41:                                # %entry_ifend250
	movq	32(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	40(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	48(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	56(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB3_42
.LBB3_10:                               # %then_block55
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_13:                               # %then_block78
	movl	$.Lglobal_string, %r8d
	movl	$.Lglobal_string.2, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	callq	entry_exception_object_with_class_name2
.LBB3_1:                                # %then_block
	xorl	%eax, %eax
.LBB3_2:                                # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB3_18:                               # %entry_condend94
	testl	%eax, %eax
	movl	%ebx, 28(%rsp)          # 4-byte Spill
	movq	%rbp, %rbx
	je	.LBB3_1
# BB#19:                                # %entry_ifend98
	movl	64(%rsp), %eax
	movl	%eax, 24(%rsp)          # 4-byte Spill
	movl	$2464, %esi             # imm = 0x9A0
	movq	128(%rsp), %rdi
	movq	%r8, %r13
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#20:                                # %entry_ifend102
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	40(%rsp), %eax
	movl	%eax, 16(%rsp)          # 4-byte Spill
	movl	48(%rsp), %eax
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movl	$2476, %esi             # imm = 0x9AC
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#21:                                # %entry_ifend107
	movq	%r13, 8(%rsp)           # 8-byte Spill
	movq	32(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	40(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	48(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	56(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	16(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	28(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB3_23
# BB#22:                                # %then_block129
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_30:                               # %then_block191
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_32:                               # %entry_condend211
	movl	32(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r13d, %edx
	movq	%rbx, %rbp
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#33:                                # %entry_ifend215
	movq	(%rax), %r8
	movl	64(%rsp), %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r13d, %edx
	movq	%rbp, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#34:                                # %entry_ifend220
	movq	(%rax), %r8
	movl	48(%rsp), %r9d
	movl	$1, (%rsp)
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r13d, %edx
	movq	%rbp, %rcx
.LBB3_35:                               # %entry_ifend220
	callq	store_field
	testl	%eax, %eax
	je	.LBB3_1
.LBB3_46:                               # %label_whilezzzzzzzzzzzzzzb
	movl	$0, gSigInt(%rip)
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %eax
	movq	%rax, (%r15)
	movl	$1, %eax
	jmp	.LBB3_2
.LBB3_42:                               # %entry_ifend267
	movq	(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	24(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	32(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	%ebx, 28(%rsp)          # 4-byte Spill
	movl	32(%rsp), %r13d
	movq	%rbp, %rbx
	movl	40(%rsp), %ebp
	movl	48(%rsp), %eax
	movl	%eax, 24(%rsp)          # 4-byte Spill
	movl	$2880, %esi             # imm = 0xB40
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#43:                                # %entry_ifend289
	movq	32(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	40(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	48(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	56(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	24(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB3_45
# BB#44:                                # %then_block311
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_23:                               # %entry_ifend130
	movq	(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	24(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	32(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r14), %rax
	movq	%rdi, %r12
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbx, (%rsp)
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	movl	24(%rsp), %r9d          # 4-byte Reload
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB3_1
# BB#24:                                # %entry_ifend149
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#25:                                # %entry_ifend153
	movq	(%rax), %r9
	incl	%r9d
	movl	32(%rsp), %r8d
	movl	$1, (%rsp)
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	jmp	.LBB3_35
.LBB3_45:                               # %entry_ifend312
	movq	(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	24(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	32(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	jmp	.LBB3_46
.Lfunc_end3:
	.size	"Hash.put(GenericsParametorClass0,GenericsParametorClass1)$$6", .Lfunc_end3-"Hash.put(GenericsParametorClass0,GenericsParametorClass1)$$6"
	.cfi_endproc

	.globl	"Hash.rehash()$$7"
	.align	16, 0x90
	.type	"Hash.rehash()$$7",@function
"Hash.rehash()$$7":                     # @"Hash.rehash()$$7"
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
	subq	$88, %rsp
.Ltmp48:
	.cfi_def_cfa_offset 144
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
	movl	%r9d, %r14d
	movq	%r8, %r13
	movq	%rcx, %rbp
	movq	%rdx, %r15
	movq	%rsi, 48(%rsp)          # 8-byte Spill
	movq	(%rbp), %rbx
	movq	$0, 56(%rsp)
	movq	%rbx, 56(%rsp)
	movq	$0, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movl	%eax, %eax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	%rax, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#4:                                 # %entry_ifend4
	movq	(%rax), %rax
	movq	$0, 72(%rsp)
	movl	%eax, %eax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	%rax, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#5:                                 # %entry_ifend9
	movq	(%rax), %r9
	addl	%r9d, %r9d
	movl	$2, (%rsp)
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebx, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB4_1
# BB#6:                                 # %entry_ifend12
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#7:                                 # %entry_ifend17
	movq	144(%rsp), %rdi
	movq	(%rax), %r12
	movl	$3068, %esi             # imm = 0xBFC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#8:                                 # %entry_ifend20
	movq	%rax, %rdi
	movl	%r12d, %esi
	callq	create_array_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	%r12d, %r9d
	movl	$0, (%rsp)
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebx, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB4_1
# BB#9:                                 # %entry_ifend23
	movl	$0, gSigInt(%rip)
	movl	$1, (%rsp)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebx, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB4_1
# BB#10:                                # %entry_ifend27
	movl	$0, gSigInt(%rip)
	movq	$0, 80(%rsp)
	xorl	%r12d, %r12d
	jmp	.LBB4_11
.LBB4_22:                               # %label_if_endzzzzzzzzzzzzzzg
                                        #   in Loop: Header=BB4_11 Depth=1
	incl	%r12d
	movq	$0, 80(%rsp)
	movq	%r12, 80(%rsp)
.LBB4_11:                               # %for_start_pointzzzzzzzzzzzzzzf
                                        # =>This Inner Loop Header: Depth=1
	movq	32(%rsp), %rax          # 8-byte Reload
	cmpl	%eax, %r12d
	jge	.LBB4_23
# BB#12:                                # %entry_condend
                                        #   in Loop: Header=BB4_11 Depth=1
	movl	$0, gSigInt(%rip)
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	movl	%r12d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#13:                                # %entry_ifend34
                                        #   in Loop: Header=BB4_11 Depth=1
	movq	(%rax), %rax
	testl	%eax, %eax
	je	.LBB4_22
# BB#14:                                # %entry_condend37
                                        #   in Loop: Header=BB4_11 Depth=1
	movl	$0, gSigInt(%rip)
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	movl	%r12d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#15:                                # %entry_ifend44
                                        #   in Loop: Header=BB4_11 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#16:                                # %entry_ifend47
                                        #   in Loop: Header=BB4_11 Depth=1
	movq	(%rax), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	movl	%r12d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#17:                                # %entry_ifend53
                                        #   in Loop: Header=BB4_11 Depth=1
	movq	(%rax), %r8
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#18:                                # %entry_ifend56
                                        #   in Loop: Header=BB4_11 Depth=1
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movl	$3172, %esi             # imm = 0xC64
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#19:                                # %entry_ifend59
                                        #   in Loop: Header=BB4_11 Depth=1
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	$0, 8(%rcx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	%r12, 24(%rcx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	%r14d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_20
# BB#21:                                # %entry_ifend77
                                        #   in Loop: Header=BB4_11 Depth=1
	movq	(%rbp), %rbx
	movq	$0, 56(%rsp)
	movq	%rbx, 56(%rsp)
	movq	8(%rbp), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%rbp), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%rbp), %r12
	movq	$0, 80(%rsp)
	movq	%r12, 80(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	jmp	.LBB4_22
.LBB4_23:                               # %label_for_endzzzzzzzzzzzzzzf
	movq	$0, (%rbp)
	movl	$1, %eax
	jmp	.LBB4_2
.LBB4_20:                               # %then_block76
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB4_1:                                # %then_block
	xorl	%eax, %eax
.LBB4_2:                                # %then_block
	addq	$88, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end4:
	.size	"Hash.rehash()$$7", .Lfunc_end4-"Hash.rehash()$$7"
	.cfi_endproc

	.globl	"Hash.get(GenericsParametorClass0)$$8"
	.align	16, 0x90
	.type	"Hash.get(GenericsParametorClass0)$$8",@function
"Hash.get(GenericsParametorClass0)$$8": # @"Hash.get(GenericsParametorClass0)$$8"
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
	subq	$72, %rsp
.Ltmp61:
	.cfi_def_cfa_offset 128
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
	movq	%r8, %rbp
	movq	%rcx, %r13
	movq	%rdx, %r14
	movq	%rsi, %r12
	movq	128(%rsp), %r9
	movq	(%r13), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r13), %rcx
	movq	$0, 48(%rsp)
	movq	%rcx, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, (%r12)
	movq	%rax, (%r12)
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	$0, 16(%r12)
	movq	$0, 24(%r12)
	movq	(%rbp), %rax
	movq	$0, (%rax)
	movl	%ecx, %edx
	movq	%rdx, (%rax)
	addq	$8, (%rbp)
	movl	%ecx, (%rsp)
	movl	$3300, %edi             # imm = 0xCE4
	movq	%r13, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movq	%r14, %r8
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB5_1
# BB#2:                                 # %entry_ifend
	movq	(%r13), %r15
	movq	%r15, 32(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%r15, 40(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	movl	%edi, 24(%rsp)          # 4-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$2, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	movl	%r15d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_3
# BB#5:                                 # %entry_ifend24
	movq	(%rax), %rcx
	testl	%ecx, %ecx
	je	.LBB5_6
# BB#7:                                 # %entry_ifend27
	xorl	%edx, %edx
	movl	24(%rsp), %eax          # 4-byte Reload
	divl	%ecx
	movl	%edx, %r15d
	movq	%r15, 24(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%r15, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 64(%rsp)
	movq	%r15, 64(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB5_8
	.align	16, 0x90
.LBB5_19:                               # %entry_condend111
                                        #   in Loop: Header=BB5_8 Depth=1
	movl	$0, gSigInt(%rip)
	movq	$0, 64(%rsp)
	xorl	%r15d, %r15d
.LBB5_8:                                # %entry_condend
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_3
# BB#9:                                 # %entry_ifend32
                                        #   in Loop: Header=BB5_8 Depth=1
	movq	(%rax), %r8
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	movl	%r15d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB5_3
# BB#10:                                # %entry_ifend36
                                        #   in Loop: Header=BB5_8 Depth=1
	movq	(%rax), %rax
	testl	%eax, %eax
	je	.LBB5_17
# BB#11:                                # %entry_condend39
                                        #   in Loop: Header=BB5_8 Depth=1
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_3
# BB#12:                                # %entry_ifend43
                                        #   in Loop: Header=BB5_8 Depth=1
	movq	(%rax), %r8
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	movl	%r15d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB5_3
# BB#13:                                # %entry_ifend48
                                        #   in Loop: Header=BB5_8 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_3
# BB#14:                                # %entry_ifend51
                                        #   in Loop: Header=BB5_8 Depth=1
	movq	(%rax), %rax
	movq	$0, (%r12)
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r12)
	movq	$0, 8(%r12)
	movq	16(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 8(%r12)
	movq	$0, 16(%r12)
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 16(%r12)
	movq	$0, 24(%r12)
	movq	%r15, 24(%r12)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	%eax, (%rsp)
	movl	$3408, %edi             # imm = 0xD50
	movq	%r13, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movq	%r14, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB5_1
# BB#15:                                # %entry_ifend70
                                        #   in Loop: Header=BB5_8 Depth=1
	movl	%ebx, 8(%rsp)           # 4-byte Spill
	movq	%r14, %rbx
	movq	(%r13), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r13), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r13), %r15
	movq	$0, 64(%rsp)
	movq	%r15, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	testb	$1, %r14b
	jne	.LBB5_20
# BB#16:                                #   in Loop: Header=BB5_8 Depth=1
	movq	%rbx, %r14
	movl	8(%rsp), %ebx           # 4-byte Reload
.LBB5_17:                               # %label_if_endzzzzzzzzzzzzzzi
                                        #   in Loop: Header=BB5_8 Depth=1
	movl	$0, gSigInt(%rip)
	incl	%r15d
	movq	$0, 64(%rsp)
	movq	%r15, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_3
# BB#18:                                # %entry_ifend107
                                        #   in Loop: Header=BB5_8 Depth=1
	movq	(%rax), %rax
	cmpl	%eax, %r15d
	je	.LBB5_19
# BB#24:                                # %label_elifzzzzzzzzzzzzzzk1a
                                        #   in Loop: Header=BB5_8 Depth=1
	movq	24(%rsp), %rax          # 8-byte Reload
	cmpl	%eax, %r15d
	jne	.LBB5_8
# BB#25:                                # %entry_condend118
	movl	$0, gSigInt(%rip)
	movq	$0, (%r13)
	movl	$1, %eax
	jmp	.LBB5_4
.LBB5_1:                                # %then_block
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB5_3
.LBB5_6:                                # %then_block26
	movl	$.Lglobal_string.3, %r8d
	movl	$.Lglobal_string.4, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	callq	entry_exception_object_with_class_name2
.LBB5_3:                                # %then_block_b
	xorl	%eax, %eax
.LBB5_4:                                # %then_block_b
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB5_20:                               # %entry_condend87
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	8(%rsp), %edx           # 4-byte Reload
	movl	%edx, %r12d
	movq	%rbx, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_3
# BB#21:                                # %entry_ifend91
	movq	(%rax), %r8
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r12d, %edx
	movq	%rbx, %rcx
	movl	%r15d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB5_3
# BB#22:                                # %entry_ifend96
	movq	(%rax), %r8
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r12d, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_3
# BB#23:                                # %entry_ifend99
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB5_4
.Lfunc_end5:
	.size	"Hash.get(GenericsParametorClass0)$$8", .Lfunc_end5-"Hash.get(GenericsParametorClass0)$$8"
	.cfi_endproc

	.globl	"Hash.getKey(GenericsParametorClass1)$$9"
	.align	16, 0x90
	.type	"Hash.getKey(GenericsParametorClass1)$$9",@function
"Hash.getKey(GenericsParametorClass1)$$9": # @"Hash.getKey(GenericsParametorClass1)$$9"
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
	subq	$56, %rsp
.Ltmp74:
	.cfi_def_cfa_offset 112
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
	movq	%rdx, %rbp
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	(%r14), %r12
	movq	$0, 32(%rsp)
	movq	%r12, 32(%rsp)
	movq	8(%r14), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 48(%rsp)
	xorl	%r13d, %r13d
	jmp	.LBB6_1
	.align	16, 0x90
.LBB6_17:                               # %label_if_endzzzzzzzzzzzzzzm
                                        #   in Loop: Header=BB6_1 Depth=1
	incl	%r13d
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
.LBB6_1:                                # %for_start_pointzzzzzzzzzzzzzzl
                                        # =>This Inner Loop Header: Depth=1
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_2
# BB#4:                                 # %entry_ifend
                                        #   in Loop: Header=BB6_1 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r13d
	jae	.LBB6_13
# BB#5:                                 # %entry_condend
                                        #   in Loop: Header=BB6_1 Depth=1
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_2
# BB#6:                                 # %entry_ifend6
                                        #   in Loop: Header=BB6_1 Depth=1
	movq	(%rax), %r8
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movl	%r13d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB6_2
# BB#7:                                 # %entry_ifend10
                                        #   in Loop: Header=BB6_1 Depth=1
	movq	(%rax), %rax
	testl	%eax, %eax
	je	.LBB6_17
# BB#8:                                 # %entry_condend13
                                        #   in Loop: Header=BB6_1 Depth=1
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_2
# BB#9:                                 # %entry_ifend17
                                        #   in Loop: Header=BB6_1 Depth=1
	movq	(%rax), %r8
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movl	%r13d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB6_2
# BB#10:                                # %entry_ifend22
                                        #   in Loop: Header=BB6_1 Depth=1
	movq	(%rax), %r8
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_2
# BB#11:                                # %entry_ifend25
                                        #   in Loop: Header=BB6_1 Depth=1
	movq	(%rax), %rax
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r12, (%rcx)
	movq	$0, 8(%rcx)
	movq	24(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r13, 16(%rcx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	%eax, (%rsp)
	movl	$3924, %edi             # imm = 0xF54
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	%rbp, %r8
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB6_12
# BB#15:                                # %entry_ifend39
                                        #   in Loop: Header=BB6_1 Depth=1
	movq	(%r14), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r14), %r13
	movq	%r14, %r12
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	testb	$1, %r14b
	jne	.LBB6_18
# BB#16:                                #   in Loop: Header=BB6_1 Depth=1
	movq	%r12, %r14
	movq	16(%rsp), %r12          # 8-byte Reload
	jmp	.LBB6_17
.LBB6_13:                               # %label_for_endzzzzzzzzzzzzzzl
	movq	$0, (%r14)
	movl	$1, %eax
	jmp	.LBB6_3
.LBB6_12:                               # %then_block38
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB6_2
.LBB6_18:                               # %entry_condend50
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_2
# BB#19:                                # %entry_ifend54
	movq	(%rax), %r8
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movl	%r13d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB6_2
# BB#20:                                # %entry_ifend59
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_2
# BB#21:                                # %entry_ifend62
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%r12)
	movl	$1, %eax
	jmp	.LBB6_3
.LBB6_2:                                # %then_block
	xorl	%eax, %eax
.LBB6_3:                                # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end6:
	.size	"Hash.getKey(GenericsParametorClass1)$$9", .Lfunc_end6-"Hash.getKey(GenericsParametorClass1)$$9"
	.cfi_endproc

	.globl	"Hash.containes(GenericsParametorClass0,GenericsParametorClass1)$$10"
	.align	16, 0x90
	.type	"Hash.containes(GenericsParametorClass0,GenericsParametorClass1)$$10",@function
"Hash.containes(GenericsParametorClass0,GenericsParametorClass1)$$10": # @"Hash.containes(GenericsParametorClass0,GenericsParametorClass1)$$10"
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
	subq	$56, %rsp
.Ltmp87:
	.cfi_def_cfa_offset 112
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
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, 24(%rsp)          # 8-byte Spill
	movq	%rsi, %rbp
	movq	112(%rsp), %rdi
	movq	(%r14), %rbx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movq	8(%r14), %r12
	movq	$0, 40(%rsp)
	movq	%r12, 40(%rsp)
	movq	16(%r14), %r15
	movq	$0, 48(%rsp)
	movq	%r15, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$4144, %esi             # imm = 0x1030
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	$0, 8(%rbp)
	movq	%r12, 8(%rbp)
	movq	$0, 16(%rbp)
	movq	%r15, 16(%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB7_4
# BB#5:                                 # %entry_ifend17
	movq	(%r14), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rbx
	movq	$0, 40(%rsp)
	movq	%rbx, 40(%rsp)
	movq	16(%r14), %r15
	movq	$0, 48(%rsp)
	movq	%r15, 48(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, (%rbp)
	movq	8(%rsp), %rax           # 8-byte Reload
	movq	%rax, (%rbp)
	movq	$0, 8(%rbp)
	movq	%rbx, 8(%rbp)
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	$0, 16(%rbp)
	movq	%r15, 16(%rbp)
	movq	(%r13), %rax
	movq	$0, (%rax)
	movq	%r12, (%rax)
	movq	(%r13), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r13)
	movq	$0, 8(%rax)
	movl	%r15d, %ecx
	movq	%rcx, 8(%rax)
	addq	$8, (%r13)
	movl	%r12d, (%rsp)
	movl	$4152, %edi             # imm = 0x1038
	movq	%r14, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	movq	%rbx, %r8
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	je	.LBB7_6
.LBB7_4:                                # %then_block16
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB7_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB7_2
.LBB7_6:                                # %entry_ifend42
	movq	(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%rbp, (%r14)
	movl	$1, %eax
.LBB7_2:                                # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end7:
	.size	"Hash.containes(GenericsParametorClass0,GenericsParametorClass1)$$10", .Lfunc_end7-"Hash.containes(GenericsParametorClass0,GenericsParametorClass1)$$10"
	.cfi_endproc

	.globl	"Hash.each(lambda)$$11"
	.align	16, 0x90
	.type	"Hash.each(lambda)$$11",@function
"Hash.each(lambda)$$11":                # @"Hash.each(lambda)$$11"
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
	subq	$40, %rsp
.Ltmp100:
	.cfi_def_cfa_offset 96
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
	movl	%r9d, %r14d
	movq	%r8, %rbp
	movq	%rcx, %rbx
	movq	%rdx, %r12
	movq	(%rbx), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%rbx), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 32(%rsp)
	xorl	%r13d, %r13d
	jmp	.LBB8_1
	.align	16, 0x90
.LBB8_16:                               # %label_if_endzzzzzzzzzzzzzzp
                                        #   in Loop: Header=BB8_1 Depth=1
	incl	%r13d
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
.LBB8_1:                                # %for_start_pointzzzzzzzzzzzzzzo
                                        # =>This Inner Loop Header: Depth=1
	movl	$2, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#4:                                 # %entry_ifend
                                        #   in Loop: Header=BB8_1 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r13d
	jae	.LBB8_17
# BB#5:                                 # %entry_condend
                                        #   in Loop: Header=BB8_1 Depth=1
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#6:                                 # %entry_ifend6
                                        #   in Loop: Header=BB8_1 Depth=1
	movq	(%rax), %r8
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%r13d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#7:                                 # %entry_ifend10
                                        #   in Loop: Header=BB8_1 Depth=1
	movq	(%rax), %rax
	testl	%eax, %eax
	je	.LBB8_16
# BB#8:                                 # %entry_condend13
                                        #   in Loop: Header=BB8_1 Depth=1
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#9:                                 # %entry_ifend18
                                        #   in Loop: Header=BB8_1 Depth=1
	movq	(%rax), %r8
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%r13d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#10:                                # %entry_ifend23
                                        #   in Loop: Header=BB8_1 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#11:                                # %entry_ifend26
                                        #   in Loop: Header=BB8_1 Depth=1
	movq	(%rax), %r15
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#12:                                # %entry_ifend30
                                        #   in Loop: Header=BB8_1 Depth=1
	movq	(%rax), %r8
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%r13d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#13:                                # %entry_ifend35
                                        #   in Loop: Header=BB8_1 Depth=1
	movq	(%rax), %r8
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#14:                                # %entry_ifend38
                                        #   in Loop: Header=BB8_1 Depth=1
	movq	(%rax), %rax
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%rbp)
	movl	$2, %edi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	movq	%r12, %r8
	callq	invoke_block_in_jit
	testl	%eax, %eax
	je	.LBB8_2
# BB#15:                                # %entry_ifend48
                                        #   in Loop: Header=BB8_1 Depth=1
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	jmp	.LBB8_16
.LBB8_2:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB8_3
.LBB8_17:                               # %label_for_endzzzzzzzzzzzzzzo
	movq	8(%rsp), %rax           # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
.LBB8_3:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end8:
	.size	"Hash.each(lambda)$$11", .Lfunc_end8-"Hash.each(lambda)$$11"
	.cfi_endproc

	.globl	"Hash.toString()$$12"
	.align	16, 0x90
	.type	"Hash.toString()$$12",@function
"Hash.toString()$$12":                  # @"Hash.toString()$$12"
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
	subq	$56, %rsp
.Ltmp113:
	.cfi_def_cfa_offset 112
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
	movl	%r9d, %ebx
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %rbp
	movq	%rsi, 24(%rsp)          # 8-byte Spill
	movq	(%r14), %r8
	movq	$0, 32(%rsp)
	movq	%r8, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#3:                                 # %entry_ifend
	movl	%ebx, %r13d
	movq	%rbp, %rbx
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	testl	%eax, %eax
	je	.LBB9_4
# BB#6:                                 # %label_if_endzzzzzzzzzzzzzzq
	movl	$.Lglobal_string.6, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movq	$0, 40(%rsp)
	movl	%ebp, %eax
	movq	%rax, 40(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 48(%rsp)
	xorl	%r12d, %r12d
	jmp	.LBB9_7
	.align	16, 0x90
.LBB9_31:                               # %label_if_endzzzzzzzzzzzzzzs
                                        #   in Loop: Header=BB9_7 Depth=1
	movl	48(%rsp), %r12d
	incl	%r12d
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
.LBB9_7:                                # %for_start_pointzzzzzzzzzzzzzzr
                                        # =>This Inner Loop Header: Depth=1
	movl	32(%rsp), %r8d
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r13d, %ebp
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#8:                                 # %entry_ifend6
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r12d
	jae	.LBB9_32
# BB#9:                                 # %entry_condend9
                                        #   in Loop: Header=BB9_7 Depth=1
	movl	32(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %r12d
	movl	%r12d, %edx
	movq	%rbx, %rbp
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#10:                                # %entry_ifend13
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	(%rax), %r8
	movl	48(%rsp), %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	movq	%rbp, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#11:                                # %entry_ifend17
                                        #   in Loop: Header=BB9_7 Depth=1
	movl	%r12d, %r13d
	movq	%rbp, %rbx
	movq	(%rax), %rax
	testl	%eax, %eax
	je	.LBB9_31
# BB#12:                                # %entry_condend21
                                        #   in Loop: Header=BB9_7 Depth=1
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %eax
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movl	32(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%rbx, %rbp
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#13:                                # %entry_ifend26
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	(%rax), %r8
	movl	48(%rsp), %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%rbp, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#14:                                # %entry_ifend31
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#15:                                # %entry_ifend34
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	(%rax), %rax
	movq	32(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	%eax, (%rsp)
	movl	$4572, %edi             # imm = 0x11DC
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movq	%rbp, %r8
	movq	112(%rsp), %r12
	movq	%r12, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movl	%r13d, %ebx
	jne	.LBB9_16
# BB#17:                                # %entry_ifend44
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$4584, %esi             # imm = 0x11E8
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_1
# BB#18:                                # %entry_ifend54
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	32(%rsp), %rcx
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	40(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	48(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB9_16
# BB#19:                                # %entry_ifend70
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r13d
	movl	$.Lglobal_string.7, %edi
	callq	create_string_object
	movq	%rbp, %r12
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$4596, %esi             # imm = 0x11F4
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_1
# BB#20:                                # %entry_ifend86
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	32(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB9_21
# BB#22:                                # %entry_ifend102
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %eax
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movl	32(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#23:                                # %entry_ifend119
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	(%rax), %r8
	movl	48(%rsp), %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%r12, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#24:                                # %entry_ifend124
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	(%rax), %r8
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#25:                                # %entry_ifend127
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	(%rax), %rax
	movq	32(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	%eax, (%rsp)
	movl	$4604, %edi             # imm = 0x11FC
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	%r12, %r8
	movq	112(%rsp), %rbp
	movq	%rbp, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB9_21
# BB#26:                                # %entry_ifend140
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	%rbp, %r13
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$4616, %esi             # imm = 0x1208
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_1
# BB#27:                                # %entry_ifend155
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	32(%rsp), %rcx
	movq	24(%rsp), %r13          # 8-byte Reload
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	40(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	48(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB9_21
# BB#28:                                # %entry_ifend171
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r13d
	movl	$.Lglobal_string.8, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$4628, %esi             # imm = 0x1214
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_1
# BB#29:                                # %entry_ifend187
                                        #   in Loop: Header=BB9_7 Depth=1
	movq	32(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB9_21
# BB#30:                                # %entry_ifend203
                                        #   in Loop: Header=BB9_7 Depth=1
	movl	%ebx, %r13d
	movq	%r12, %rbx
	movq	(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	jmp	.LBB9_31
.LBB9_4:                                # %entry_condend
	movl	$.Lglobal_string.5, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	%ebx, %eax
.LBB9_5:                                # %entry_condend
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB9_2
.LBB9_32:                               # %label_for_endzzzzzzzzzzzzzzr
	movl	40(%rsp), %r12d
	movl	$4756, %esi             # imm = 0x1294
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebp, %ecx
	je	.LBB9_1
# BB#33:                                # %entry_ifend222
	movq	32(%rsp), %rdx
	movq	24(%rsp), %rsi          # 8-byte Reload
	movq	$0, (%rsi)
	movq	%rdx, (%rsi)
	movq	40(%rsp), %rdx
	movq	$0, 8(%rsi)
	movq	%rdx, 8(%rsi)
	movq	48(%rsp), %rdx
	movq	$0, 16(%rsi)
	movq	%rdx, 16(%rsi)
	movq	(%r15), %rsi
	movq	$0, (%rsi)
	movl	%r12d, %edx
	movq	%rdx, (%rsi)
	movq	(%r15), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rsi)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rsi)
	movq	(%r15), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rsi)
	movq	$125, 8(%rsi)
	addq	$8, (%r15)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movq	%r15, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB9_35
# BB#34:                                # %then_block240
	callq	get_try_catch_label_name
	jmp	.LBB9_1
.LBB9_21:                               # %then_block101
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB9_1
.LBB9_16:                               # %then_block43
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB9_1:                                # %then_block
	xorl	%eax, %eax
.LBB9_2:                                # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB9_35:                               # %entry_ifend241
	movq	(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %eax
	jmp	.LBB9_5
.Lfunc_end9:
	.size	"Hash.toString()$$12", .Lfunc_end9-"Hash.toString()$$12"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"Exception"
	.size	.Lglobal_string, 10

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.asciz	"division by zero"
	.size	.Lglobal_string.2, 17

	.type	.Lglobal_string.3,@object # @global_string.3
.Lglobal_string.3:
	.asciz	"Exception"
	.size	.Lglobal_string.3, 10

	.type	.Lglobal_string.4,@object # @global_string.4
.Lglobal_string.4:
	.asciz	"division by zero"
	.size	.Lglobal_string.4, 17

	.type	.Lglobal_string.5,@object # @global_string.5
.Lglobal_string.5:
	.asciz	"hash {}"
	.size	.Lglobal_string.5, 8

	.type	.Lglobal_string.6,@object # @global_string.6
.Lglobal_string.6:
	.asciz	"hash {"
	.size	.Lglobal_string.6, 7

	.type	.Lglobal_string.7,@object # @global_string.7
.Lglobal_string.7:
	.asciz	":"
	.size	.Lglobal_string.7, 2

	.type	.Lglobal_string.8,@object # @global_string.8
.Lglobal_string.8:
	.asciz	","
	.size	.Lglobal_string.8, 2


	.section	".note.GNU-stack","",@progbits
