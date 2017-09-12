	.text
	.file	"Array.bc"
	.globl	"Array.length()$$2"
	.align	16, 0x90
	.type	"Array.length()$$2",@function
"Array.length()$$2":                    # @"Array.length()$$2"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp0:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp1:
	.cfi_def_cfa_offset 32
.Ltmp2:
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
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	get_array_length
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB0_2
.LBB0_1:                                # %then_block
	xorl	%eax, %eax
.LBB0_2:                                # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end0:
	.size	"Array.length()$$2", .Lfunc_end0-"Array.length()$$2"
	.cfi_endproc

	.globl	"Array.items(int)$$3"
	.align	16, 0x90
	.type	"Array.items(int)$$3",@function
"Array.items(int)$$3":                  # @"Array.items(int)$$3"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp3:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp4:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp5:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp6:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp7:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp8:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp9:
	.cfi_def_cfa_offset 80
.Ltmp10:
	.cfi_offset %rbx, -56
.Ltmp11:
	.cfi_offset %r12, -48
.Ltmp12:
	.cfi_offset %r13, -40
.Ltmp13:
	.cfi_offset %r14, -32
.Ltmp14:
	.cfi_offset %r15, -24
.Ltmp15:
	.cfi_offset %rbp, -16
	movl	%r9d, %r14d
	movq	%r8, %r12
	movq	%rcx, %rbx
	movq	%rdx, %r15
	movq	(%rbx), %r13
	movq	$0, 8(%rsp)
	movq	%r13, 8(%rsp)
	movq	8(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%ebp, %ebp
	jns	.LBB1_3
# BB#1:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_4
# BB#2:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	get_array_length
	addl	%eax, %ebp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
.LBB1_3:                                # %label_if_endzg
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_4
# BB#6:                                 # %entry_ifend8
	movq	(%rax), %r8
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB1_4
# BB#7:                                 # %entry_ifend12
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB1_5
.LBB1_4:                                # %then_block
	xorl	%eax, %eax
.LBB1_5:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end1:
	.size	"Array.items(int)$$3", .Lfunc_end1-"Array.items(int)$$3"
	.cfi_endproc

	.globl	"Array.each(lambda)$$4"
	.align	16, 0x90
	.type	"Array.each(lambda)$$4",@function
"Array.each(lambda)$$4":                # @"Array.each(lambda)$$4"
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
	subq	$40, %rsp
.Ltmp22:
	.cfi_def_cfa_offset 96
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
	movl	%r9d, %r14d
	movq	%r8, %rbp
	movq	%rcx, %r13
	movq	%rdx, %r15
	movq	(%r13), %r12
	movq	$0, 16(%rsp)
	movq	%r12, 16(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 32(%rsp)
	xorl	%ebx, %ebx
	jmp	.LBB2_1
	.align	16, 0x90
.LBB2_8:                                # %entry_ifend18
                                        #   in Loop: Header=BB2_1 Depth=1
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	incl	%ebx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
.LBB2_1:                                # %for_start_pointzh
                                        # =>This Inner Loop Header: Depth=1
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_2
# BB#4:                                 # %entry_ifend
                                        #   in Loop: Header=BB2_1 Depth=1
	movq	(%rax), %rdi
	callq	get_array_length
	cmpl	%eax, %ebx
	jge	.LBB2_9
# BB#5:                                 # %entry_condend
                                        #   in Loop: Header=BB2_1 Depth=1
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_2
# BB#6:                                 # %entry_ifend7
                                        #   in Loop: Header=BB2_1 Depth=1
	movq	(%rax), %r8
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebx, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB2_2
# BB#7:                                 # %entry_ifend11
                                        #   in Loop: Header=BB2_1 Depth=1
	movq	(%rax), %rax
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%rbp)
	movl	$1, %edi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	movq	%r15, %r8
	callq	invoke_block_in_jit
	testl	%eax, %eax
	jne	.LBB2_8
.LBB2_2:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB2_3
.LBB2_9:                                # %label_for_endzh
	movq	$0, (%r13)
	movl	$1, %eax
.LBB2_3:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end2:
	.size	"Array.each(lambda)$$4", .Lfunc_end2-"Array.each(lambda)$$4"
	.cfi_endproc

	.globl	"Array.toEqualableArray()$$5"
	.align	16, 0x90
	.type	"Array.toEqualableArray()$$5",@function
"Array.toEqualableArray()$$5":          # @"Array.toEqualableArray()$$5"
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
	subq	$56, %rsp
.Ltmp35:
	.cfi_def_cfa_offset 112
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
	movl	%r9d, 28(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %r13
	movq	%rsi, %r12
	movq	112(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$880, %esi              # imm = 0x370
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movl	$896, %esi              # imm = 0x380
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#5:                                 # %entry_ifend6
	movq	%r12, 8(%rsp)           # 8-byte Spill
	movq	$0, (%r12)
	movq	%rbp, (%r12)
	movq	$0, 8(%r12)
	movq	$0, 16(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%r13, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB3_7
# BB#6:                                 # %then_block18
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB3_1:                                # %then_block
	xorl	%eax, %eax
.LBB3_2:                                # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB3_7:                                # %entry_ifend19
	movq	(%r14), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
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
	movq	$0, 40(%rsp)
	movq	%r13, 40(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 48(%rsp)
	xorl	%r12d, %r12d
	jmp	.LBB3_8
	.align	16, 0x90
.LBB3_22:                               # %label_if_endzj
                                        #   in Loop: Header=BB3_8 Depth=1
	leal	1(%r12), %r12d
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movq	%rbp, %rbx
.LBB3_8:                                # %for_start_pointzi
                                        # =>This Inner Loop Header: Depth=1
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movq	%rbx, %rbp
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#9:                                 # %entry_ifend31
                                        #   in Loop: Header=BB3_8 Depth=1
	movq	(%rax), %rdi
	callq	get_array_length
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r12d
	jge	.LBB3_21
# BB#10:                                # %entry_condend
                                        #   in Loop: Header=BB3_8 Depth=1
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#11:                                # %entry_ifend35
                                        #   in Loop: Header=BB3_8 Depth=1
	movq	(%rax), %r8
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movl	%r12d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#12:                                # %entry_ifend39
                                        #   in Loop: Header=BB3_8 Depth=1
	movq	(%rax), %rbx
	movl	$948, %esi              # imm = 0x3B4
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#13:                                # %entry_ifend42
                                        #   in Loop: Header=BB3_8 Depth=1
	testl	%ebx, %ebx
	je	.LBB3_14
# BB#15:                                # %entry_ifend45
                                        #   in Loop: Header=BB3_8 Depth=1
	movl	%ebx, %edi
	movq	%rax, %rsi
	callq	object_implements_interface
	testl	%eax, %eax
	jne	.LBB3_22
# BB#16:                                # %entry_condend48
	movl	$0, gSigInt(%rip)
	movl	$976, %esi              # imm = 0x3D0
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#17:                                # %entry_ifend51
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 4(%rsp)           # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.3, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$1032, %esi             # imm = 0x408
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#18:                                # %entry_ifend54
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r12, 16(%rcx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	4(%rsp), %edx           # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB3_20
# BB#19:                                # %then_block69
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_21:                               # %label_for_endzi
	movl	%r13d, %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB3_2
.LBB3_14:                               # %then_block44
	movl	$.Lglobal_string, %r8d
	movl	$.Lglobal_string.2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	callq	entry_exception_object_with_class_name2
	jmp	.LBB3_1
.LBB3_20:                               # %entry_ifend70
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
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbx, (%r14)
	movl	%ebx, %edi
	movq	%rbp, %rsi
	callq	entry_exception_object
	jmp	.LBB3_1
.Lfunc_end3:
	.size	"Array.toEqualableArray()$$5", .Lfunc_end3-"Array.toEqualableArray()$$5"
	.cfi_endproc

	.globl	"Array.toSortableArray()$$6"
	.align	16, 0x90
	.type	"Array.toSortableArray()$$6",@function
"Array.toSortableArray()$$6":           # @"Array.toSortableArray()$$6"
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
	subq	$56, %rsp
.Ltmp48:
	.cfi_def_cfa_offset 112
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
	movl	%r9d, 28(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %r13
	movq	%rsi, %r12
	movq	112(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1112, %esi             # imm = 0x458
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movl	$1128, %esi             # imm = 0x468
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#5:                                 # %entry_ifend6
	movq	%r12, 8(%rsp)           # 8-byte Spill
	movq	$0, (%r12)
	movq	%rbp, (%r12)
	movq	$0, 8(%r12)
	movq	$0, 16(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%r13, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB4_7
# BB#6:                                 # %then_block18
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB4_1:                                # %then_block
	xorl	%eax, %eax
.LBB4_2:                                # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB4_7:                                # %entry_ifend19
	movq	(%r14), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
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
	movq	$0, 40(%rsp)
	movq	%r13, 40(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 48(%rsp)
	xorl	%r12d, %r12d
	jmp	.LBB4_8
	.align	16, 0x90
.LBB4_22:                               # %label_if_endzl
                                        #   in Loop: Header=BB4_8 Depth=1
	leal	1(%r12), %r12d
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movq	%rbp, %rbx
.LBB4_8:                                # %for_start_pointzk
                                        # =>This Inner Loop Header: Depth=1
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movq	%rbx, %rbp
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#9:                                 # %entry_ifend31
                                        #   in Loop: Header=BB4_8 Depth=1
	movq	(%rax), %rdi
	callq	get_array_length
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r12d
	jge	.LBB4_21
# BB#10:                                # %entry_condend
                                        #   in Loop: Header=BB4_8 Depth=1
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#11:                                # %entry_ifend35
                                        #   in Loop: Header=BB4_8 Depth=1
	movq	(%rax), %r8
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movl	%r12d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#12:                                # %entry_ifend39
                                        #   in Loop: Header=BB4_8 Depth=1
	movq	(%rax), %rbx
	movl	$1180, %esi             # imm = 0x49C
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#13:                                # %entry_ifend42
                                        #   in Loop: Header=BB4_8 Depth=1
	testl	%ebx, %ebx
	je	.LBB4_14
# BB#15:                                # %entry_ifend45
                                        #   in Loop: Header=BB4_8 Depth=1
	movl	%ebx, %edi
	movq	%rax, %rsi
	callq	object_implements_interface
	testl	%eax, %eax
	jne	.LBB4_22
# BB#16:                                # %entry_condend48
	movl	$0, gSigInt(%rip)
	movl	$1208, %esi             # imm = 0x4B8
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#17:                                # %entry_ifend51
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 4(%rsp)           # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.6, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$1260, %esi             # imm = 0x4EC
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#18:                                # %entry_ifend54
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r12, 16(%rcx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	4(%rsp), %edx           # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB4_20
# BB#19:                                # %then_block69
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB4_1
.LBB4_21:                               # %label_for_endzk
	movl	%r13d, %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB4_2
.LBB4_14:                               # %then_block44
	movl	$.Lglobal_string.4, %r8d
	movl	$.Lglobal_string.5, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	callq	entry_exception_object_with_class_name2
	jmp	.LBB4_1
.LBB4_20:                               # %entry_ifend70
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
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbx, (%r14)
	movl	%ebx, %edi
	movq	%rbp, %rsi
	callq	entry_exception_object
	jmp	.LBB4_1
.Lfunc_end4:
	.size	"Array.toSortableArray()$$6", .Lfunc_end4-"Array.toSortableArray()$$6"
	.cfi_endproc

	.globl	"Array.toList()$$7"
	.align	16, 0x90
	.type	"Array.toList()$$7",@function
"Array.toList()$$7":                    # @"Array.toList()$$7"
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
	subq	$56, %rsp
.Ltmp61:
	.cfi_def_cfa_offset 112
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
	movl	%r9d, 28(%rsp)          # 4-byte Spill
	movq	%r8, %rbp
	movq	%rcx, %r12
	movq	%rdx, %r13
	movq	%rsi, %rbx
	movq	112(%rsp), %rdi
	movq	(%r12), %r15
	movq	$0, 32(%rsp)
	movq	%r15, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1340, %esi             # imm = 0x53C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movl	$1348, %esi             # imm = 0x544
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#4:                                 # %entry_ifend2
	movq	%rbx, 8(%rsp)           # 8-byte Spill
	movq	$0, (%rbx)
	movq	%r15, (%rbx)
	movq	$0, 8(%rbx)
	movq	$0, 16(%rbx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbp)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	%r13, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB5_5
# BB#6:                                 # %entry_ifend12
	movq	(%r12), %r13
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	movq	8(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r14
	movq	%r14, 16(%rsp)          # 8-byte Spill
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 40(%rsp)
	movq	%r14, 40(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 48(%rsp)
	xorl	%r14d, %r14d
	jmp	.LBB5_7
	.align	16, 0x90
.LBB5_13:                               # %entry_ifend52
                                        #   in Loop: Header=BB5_7 Depth=1
	movq	(%r12), %r13
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	movq	8(%r12), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r12), %r14
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	incl	%r14d
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
.LBB5_7:                                # %for_start_pointzm
                                        # =>This Inner Loop Header: Depth=1
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#8:                                 # %entry_ifend24
                                        #   in Loop: Header=BB5_7 Depth=1
	movq	(%rax), %rdi
	callq	get_array_length
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r14d
	jge	.LBB5_14
# BB#9:                                 # %entry_condend
                                        #   in Loop: Header=BB5_7 Depth=1
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#10:                                # %entry_ifend29
                                        #   in Loop: Header=BB5_7 Depth=1
	movq	(%rax), %r8
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r14d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#11:                                # %entry_ifend33
                                        #   in Loop: Header=BB5_7 Depth=1
	movq	(%rax), %r15
	movl	$1392, %esi             # imm = 0x570
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#12:                                # %entry_ifend36
                                        #   in Loop: Header=BB5_7 Depth=1
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r14, 16(%rcx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB5_13
.LBB5_5:                                # %then_block11
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB5_1:                                # %then_block
	xorl	%eax, %eax
.LBB5_2:                                # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB5_14:                               # %label_for_endzm
	movq	16(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%r12)
	movl	$1, %eax
	jmp	.LBB5_2
.Lfunc_end5:
	.size	"Array.toList()$$7", .Lfunc_end5-"Array.toList()$$7"
	.cfi_endproc

	.globl	"Array.toString()$$8"
	.align	16, 0x90
	.type	"Array.toString()$$8",@function
"Array.toString()$$8":                  # @"Array.toString()$$8"
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
	subq	$40, %rsp
.Ltmp74:
	.cfi_def_cfa_offset 96
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
	movl	%r9d, %r15d
	movq	%r8, %rbx
	movq	%rcx, %r12
	movq	%rdx, %r14
	movq	%rsi, 16(%rsp)          # 8-byte Spill
	movq	(%r12), %r13
	movq	$0, 24(%rsp)
	movq	%r13, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r12, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	testl	%eax, %eax
	je	.LBB6_4
# BB#6:                                 # %label_elsezn
	movl	$.Lglobal_string.8, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movq	$0, 32(%rsp)
	movl	%ebp, %ebp
	movq	%rbp, 32(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r12, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#7:                                 # %entry_ifend6
	movq	(%rax), %rdi
	callq	get_array_length
	movl	%eax, 8(%rsp)           # 4-byte Spill
	movl	%eax, %edi
	callq	run_int_to_string_cast
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$1500, %esi             # imm = 0x5DC
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#8:                                 # %entry_ifend9
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r12, %rbp
	movq	%rbp, %rdx
	movl	%r15d, %ecx
	movq	%rbx, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_9
# BB#10:                                # %entry_ifend20
	movl	%r15d, 12(%rsp)         # 4-byte Spill
	movq	(%rbp), %r15
	movq	$0, 24(%rsp)
	movq	%r15, 24(%rsp)
	movq	8(%rbp), %r12
	movq	$0, 32(%rsp)
	movq	%r12, 32(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.9, %edi
	callq	create_string_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$1528, %esi             # imm = 0x5F8
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#11:                                # %entry_ifend29
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
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
	addq	$8, (%rbx)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	12(%rsp), %r12d         # 4-byte Reload
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_9
# BB#12:                                # %entry_ifend43
	movq	(%rbp), %r13
	movq	$0, 24(%rsp)
	movq	%r13, 24(%rsp)
	movq	8(%rbp), %r15
	movq	$0, 32(%rsp)
	movq	%r15, 32(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%r12d, %edx
	movq	%r14, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#13:                                # %entry_ifend58
	movq	(%rax), %rdi
	testl	%edi, %edi
	je	.LBB6_14
# BB#15:                                # %entry_ifend61
	callq	get_string_object_of_object_name
	movl	%eax, 8(%rsp)           # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$1536, %esi             # imm = 0x600
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#16:                                # %entry_ifend64
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r15, 8(%rcx)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%rbp, %r15
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB6_17
.LBB6_9:                                # %then_block19
	movq	%r14, %rdi
	callq	get_try_catch_label_name
.LBB6_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB6_2
.LBB6_4:                                # %entry_condend
	movl	$.Lglobal_string.7, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%r12)
	movl	$1, %eax
.LBB6_2:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB6_14:                               # %then_block60
	movl	$.Lglobal_string.10, %r8d
	movl	$.Lglobal_string.11, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%r12d, %edx
	movq	%r14, %rcx
	callq	entry_exception_object_with_class_name2
	jmp	.LBB6_1
.LBB6_17:                               # %entry_ifend78
	movq	(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%r15), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	%ebp, %eax
	movq	%rax, (%r15)
	movl	$1, %eax
	jmp	.LBB6_2
.Lfunc_end6:
	.size	"Array.toString()$$8", .Lfunc_end6-"Array.toString()$$8"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"Exception"
	.size	.Lglobal_string, 10

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.asciz	"Null pointer exception(2)"
	.size	.Lglobal_string.2, 26

	.type	.Lglobal_string.3,@object # @global_string.3
.Lglobal_string.3:
	.asciz	"An elements doesn't implement IEqualable"
	.size	.Lglobal_string.3, 41

	.type	.Lglobal_string.4,@object # @global_string.4
.Lglobal_string.4:
	.asciz	"Exception"
	.size	.Lglobal_string.4, 10

	.type	.Lglobal_string.5,@object # @global_string.5
.Lglobal_string.5:
	.asciz	"Null pointer exception(2)"
	.size	.Lglobal_string.5, 26

	.type	.Lglobal_string.6,@object # @global_string.6
.Lglobal_string.6:
	.asciz	"An elements doesn't implement ISortable"
	.size	.Lglobal_string.6, 40

	.type	.Lglobal_string.7,@object # @global_string.7
.Lglobal_string.7:
	.asciz	"Null array"
	.size	.Lglobal_string.7, 11

	.type	.Lglobal_string.8,@object # @global_string.8
.Lglobal_string.8:
	.zero	1
	.size	.Lglobal_string.8, 1

	.type	.Lglobal_string.9,@object # @global_string.9
.Lglobal_string.9:
	.asciz	" length array of "
	.size	.Lglobal_string.9, 18

	.type	.Lglobal_string.10,@object # @global_string.10
.Lglobal_string.10:
	.asciz	"Exception"
	.size	.Lglobal_string.10, 10

	.type	.Lglobal_string.11,@object # @global_string.11
.Lglobal_string.11:
	.asciz	"Null pointer exception(1)"
	.size	.Lglobal_string.11, 26


	.section	".note.GNU-stack","",@progbits
