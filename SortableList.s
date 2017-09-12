	.text
	.file	"SortableList.bc"
	.globl	"SortableList.setValue(Self)$$2"
	.align	16, 0x90
	.type	"SortableList.setValue(Self)$$2",@function
"SortableList.setValue(Self)$$2":       # @"SortableList.setValue(Self)$$2"
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
	movl	%r9d, %r14d
	movq	%r8, %r13
	movq	%rcx, %rbx
	movq	%rdx, %r12
	movq	(%rbx), %r15
	movq	$0, 8(%rsp)
	movq	%r15, 8(%rsp)
	movq	8(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %r9d
	movl	$0, (%rsp)
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%r15d, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB0_1
# BB#4:                                 # %entry_ifend5
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#5:                                 # %entry_ifend10
	movq	(%rax), %rax
	movl	%eax, %r9d
	movl	$1, (%rsp)
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%r15d, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB0_1
# BB#6:                                 # %entry_ifend13
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#7:                                 # %entry_ifend18
	movq	(%rax), %rax
	movl	%eax, %r9d
	movl	$2, (%rsp)
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%r15d, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB0_1
# BB#8:                                 # %entry_ifend21
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB0_2
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
.Lfunc_end0:
	.size	"SortableList.setValue(Self)$$2", .Lfunc_end0-"SortableList.setValue(Self)$$2"
	.cfi_endproc

	.globl	"SortableList.length()$$3"
	.align	16, 0x90
	.type	"SortableList.length()$$3",@function
"SortableList.length()$$3":             # @"SortableList.length()$$3"
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
	movl	$2, %r9d
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
	.size	"SortableList.length()$$3", .Lfunc_end1-"SortableList.length()$$3"
	.cfi_endproc

	.globl	"SortableList.toString()$$4"
	.align	16, 0x90
	.type	"SortableList.toString()$$4",@function
"SortableList.toString()$$4":           # @"SortableList.toString()$$4"
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
	je	.LBB2_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	testl	%eax, %eax
	je	.LBB2_4
# BB#6:                                 # %label_elsezzzzzzzzzo
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movq	$0, 32(%rsp)
	movl	%ebp, %ebp
	movq	%rbp, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rbx, %rdi
	movq	%r12, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#7:                                 # %entry_ifend6
	movq	(%rax), %rdi
	movq	%rdi, (%rsp)            # 8-byte Spill
	callq	run_int_to_string_cast
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$5056, %esi             # imm = 0x13C0
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#8:                                 # %entry_ifend9
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movl	%edx, %edx
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
	jne	.LBB2_9
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
	movl	$.Lglobal_string.3, %edi
	callq	create_string_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$5084, %esi             # imm = 0x13DC
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
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
	jne	.LBB2_9
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
	je	.LBB2_1
# BB#13:                                # %entry_ifend58
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%r12d, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#14:                                # %entry_ifend61
	movq	(%rax), %rdi
	testl	%edi, %edi
	je	.LBB2_15
# BB#16:                                # %entry_ifend64
	callq	get_string_object_of_object_name
	movl	%eax, (%rsp)            # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$5092, %esi             # imm = 0x13E4
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#17:                                # %entry_ifend67
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
	movl	(%rsp), %edx            # 4-byte Reload
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
	je	.LBB2_18
.LBB2_9:                                # %then_block19
	movq	%r14, %rdi
	callq	get_try_catch_label_name
.LBB2_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB2_2
.LBB2_4:                                # %entry_condend
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%r12)
	movl	$1, %eax
.LBB2_2:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB2_15:                               # %then_block63
	movl	$.Lglobal_string.4, %r8d
	movl	$.Lglobal_string.5, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%r12d, %edx
	movq	%r14, %rcx
	callq	entry_exception_object_with_class_name2
	jmp	.LBB2_1
.LBB2_18:                               # %entry_ifend81
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
	jmp	.LBB2_2
.Lfunc_end2:
	.size	"SortableList.toString()$$4", .Lfunc_end2-"SortableList.toString()$$4"
	.cfi_endproc

	.globl	"SortableList.items(int)$$5"
	.align	16, 0x90
	.type	"SortableList.items(int)$$5",@function
"SortableList.items(int)$$5":           # @"SortableList.items(int)$$5"
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
	movl	%r9d, %r14d
	movq	%r8, %r15
	movq	%rcx, %r12
	movq	%rdx, %r13
	movq	(%r12), %rbx
	movq	$0, 8(%rsp)
	movq	%rbx, 8(%rsp)
	movq	8(%r12), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%ebp, %ebp
	jns	.LBB3_3
# BB#1:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_4
# BB#2:                                 # %entry_ifend
	movq	(%rax), %rax
	addl	%eax, %ebp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
.LBB3_3:                                # %label_if_endzzzzzzzzzp
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_4
# BB#6:                                 # %entry_ifend8
	movq	(%rax), %rax
	movq	$0, 24(%rsp)
	movl	%eax, %r8d
	movq	%r8, 24(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%ebx, %ebx
	jmp	.LBB3_7
	.align	16, 0x90
.LBB3_14:                               # %entry_ifend29
                                        #   in Loop: Header=BB3_7 Depth=1
	movq	(%rax), %rax
	movq	$0, 24(%rsp)
	movl	%eax, %r8d
	movq	%r8, 24(%rsp)
.LBB3_7:                                # %while_start_pointzzzzzzzzzq
                                        # =>This Inner Loop Header: Depth=1
	testl	%r8d, %r8d
	movl	$0, gSigInt(%rip)
	je	.LBB3_11
# BB#8:                                 # %entry_condend12
                                        #   in Loop: Header=BB3_7 Depth=1
	cmpl	%ebp, %ebx
	movl	$0, gSigInt(%rip)
	je	.LBB3_9
# BB#13:                                # %label_if_endzzzzzzzzzr
                                        #   in Loop: Header=BB3_7 Depth=1
	incl	%ebx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB3_14
	jmp	.LBB3_4
.LBB3_11:                               # %label_whilezzzzzzzzzq
	movq	$0, (%r12)
	movl	$1, %eax
	jmp	.LBB3_5
.LBB3_9:                                # %entry_condend18
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_4
# BB#10:                                # %entry_ifend22
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%r12)
	movl	$1, %eax
	jmp	.LBB3_5
.LBB3_4:                                # %then_block
	xorl	%eax, %eax
.LBB3_5:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end3:
	.size	"SortableList.items(int)$$5", .Lfunc_end3-"SortableList.items(int)$$5"
	.cfi_endproc

	.globl	"SortableList.clear()$$6"
	.align	16, 0x90
	.type	"SortableList.clear()$$6",@function
"SortableList.clear()$$6":              # @"SortableList.clear()$$6"
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
	pushq	%r12
.Ltmp45:
	.cfi_def_cfa_offset 40
	pushq	%rbx
.Ltmp46:
	.cfi_def_cfa_offset 48
	subq	$16, %rsp
.Ltmp47:
	.cfi_def_cfa_offset 64
.Ltmp48:
	.cfi_offset %rbx, -48
.Ltmp49:
	.cfi_offset %r12, -40
.Ltmp50:
	.cfi_offset %r14, -32
.Ltmp51:
	.cfi_offset %r15, -24
.Ltmp52:
	.cfi_offset %rbp, -16
	movl	%r9d, %r15d
	movq	%r8, %r12
	movq	%rcx, %r14
	movq	%rdx, %rbp
	movq	(%r14), %rbx
	movq	$0, 8(%rsp)
	movq	%rbx, 8(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$0, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%rbp, %rcx
	movl	%ebx, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB4_1
# BB#3:                                 # %entry_ifend
	movl	$0, gSigInt(%rip)
	movl	$1, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%rbp, %rcx
	movl	%ebx, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB4_1
# BB#4:                                 # %entry_ifend4
	movl	$0, gSigInt(%rip)
	movl	$2, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%rbp, %rcx
	movl	%ebx, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB4_1
# BB#5:                                 # %entry_ifend8
	movl	$0, gSigInt(%rip)
	movl	%ebx, %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB4_2
.LBB4_1:                                # %then_block
	xorl	%eax, %eax
.LBB4_2:                                # %then_block
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end4:
	.size	"SortableList.clear()$$6", .Lfunc_end4-"SortableList.clear()$$6"
	.cfi_endproc

	.globl	"SortableList.add(GenericsParametorClass0)$$7"
	.align	16, 0x90
	.type	"SortableList.add(GenericsParametorClass0)$$7",@function
"SortableList.add(GenericsParametorClass0)$$7": # @"SortableList.add(GenericsParametorClass0)$$7"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp53:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp54:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp55:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp56:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp57:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp58:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp59:
	.cfi_def_cfa_offset 112
.Ltmp60:
	.cfi_offset %rbx, -56
.Ltmp61:
	.cfi_offset %r12, -48
.Ltmp62:
	.cfi_offset %r13, -40
.Ltmp63:
	.cfi_offset %r14, -32
.Ltmp64:
	.cfi_offset %r15, -24
.Ltmp65:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebx
	movl	%ebx, 28(%rsp)          # 4-byte Spill
	movq	%r8, %r12
	movq	%rcx, %r13
	movq	%rdx, %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	%rsi, %r14
	movq	(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	8(%r13), %r15
	movq	$0, 40(%rsp)
	movq	%r15, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	%ebx, %edx
	movq	%rax, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#3:                                 # %entry_ifend
	movq	112(%rsp), %rdi
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	testl	%eax, %eax
	je	.LBB5_4
# BB#15:                                # %label_elsezzzzzzzzzs
	movl	$5492, %esi             # imm = 0x1574
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#16:                                # %entry_ifend51
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	16(%rsp), %rcx          # 8-byte Reload
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#17:                                # %entry_ifend56
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$5504, %esi             # imm = 0x1580
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#18:                                # %entry_ifend59
	movq	$0, (%r14)
	movq	%rbp, (%r14)
	movq	$0, 8(%r14)
	movq	%r15, 8(%r14)
	movq	$0, 16(%r14)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	addq	$8, (%r12)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	28(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r12, %r8
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB5_7
# BB#19:                                # %entry_ifend81
	movq	(%r13), %r14
	movq	$0, 32(%rsp)
	movq	%r14, 32(%rsp)
	movq	8(%r13), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 48(%rsp)
	movq	%r15, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#20:                                # %entry_ifend97
	movq	(%rax), %r8
	movl	%r15d, %ebp
	movl	$1, (%rsp)
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movq	%rbp, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB5_1
# BB#21:                                # %entry_ifend101
	movl	$0, gSigInt(%rip)
	movl	$1, (%rsp)
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r14d, %r8d
	movq	%rbp, %r9
	jmp	.LBB5_11
.LBB5_4:                                # %entry_condend
	movl	$5420, %esi             # imm = 0x152C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#5:                                 # %entry_ifend5
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$5432, %esi             # imm = 0x1538
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#6:                                 # %entry_ifend9
	movq	$0, (%r14)
	movq	%rbp, (%r14)
	movq	$0, 8(%r14)
	movq	%r15, 8(%r14)
	movq	$0, 16(%r14)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	addq	$8, (%r12)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	28(%rsp), %r14d         # 4-byte Reload
	movl	%r14d, %ecx
	movq	%r12, %r8
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB5_8
.LBB5_7:                                # %then_block27
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
.LBB5_8:                                # %entry_ifend28
	movq	(%r13), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r13), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, (%rsp)
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	8(%rsp), %r14           # 8-byte Reload
	movq	%rbx, %rcx
	movl	%ebp, %r8d
	movq	%r15, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB5_1
# BB#9:                                 # %entry_ifend39
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#10:                                # %entry_ifend44
	movq	(%rax), %rax
	movl	%eax, %r9d
	movl	$1, (%rsp)
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r14d, %r8d
.LBB5_11:                               # %entry_ifend44
	callq	store_field
	testl	%eax, %eax
	je	.LBB5_1
# BB#12:                                # %label_if_endzzzzzzzzzs
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#13:                                # %entry_ifend111
	movq	(%rax), %r9
	incl	%r9d
	movl	$2, (%rsp)
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r14d, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB5_1
# BB#14:                                # %entry_ifend115
	movl	$0, gSigInt(%rip)
	movl	%r14d, %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB5_2
.Lfunc_end5:
	.size	"SortableList.add(GenericsParametorClass0)$$7", .Lfunc_end5-"SortableList.add(GenericsParametorClass0)$$7"
	.cfi_endproc

	.globl	"SortableList.push(GenericsParametorClass0)$$8"
	.align	16, 0x90
	.type	"SortableList.push(GenericsParametorClass0)$$8",@function
"SortableList.push(GenericsParametorClass0)$$8": # @"SortableList.push(GenericsParametorClass0)$$8"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp66:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp67:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp68:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp69:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp70:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp71:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp72:
	.cfi_def_cfa_offset 80
.Ltmp73:
	.cfi_offset %rbx, -56
.Ltmp74:
	.cfi_offset %r12, -48
.Ltmp75:
	.cfi_offset %r13, -40
.Ltmp76:
	.cfi_offset %r14, -32
.Ltmp77:
	.cfi_offset %r15, -24
.Ltmp78:
	.cfi_offset %rbp, -16
	movl	%r9d, 4(%rsp)           # 4-byte Spill
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %rbp
	movq	80(%rsp), %rdi
	movq	(%r14), %r12
	movq	$0, 8(%rsp)
	movq	%r12, 8(%rsp)
	movq	8(%r14), %rbx
	movq	$0, 16(%rsp)
	movq	%rbx, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$5564, %esi             # imm = 0x15BC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%r12, (%rbp)
	movq	$0, 8(%rbp)
	movq	%rbx, 8(%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB6_5
# BB#4:                                 # %then_block12
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB6_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB6_2
.LBB6_5:                                # %entry_ifend13
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%rbp, (%r14)
	movl	$1, %eax
.LBB6_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end6:
	.size	"SortableList.push(GenericsParametorClass0)$$8", .Lfunc_end6-"SortableList.push(GenericsParametorClass0)$$8"
	.cfi_endproc

	.globl	"SortableList.pop()$$9"
	.align	16, 0x90
	.type	"SortableList.pop()$$9",@function
"SortableList.pop()$$9":                # @"SortableList.pop()$$9"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp79:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp80:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp81:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp82:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp83:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp84:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp85:
	.cfi_def_cfa_offset 96
.Ltmp86:
	.cfi_offset %rbx, -56
.Ltmp87:
	.cfi_offset %r12, -48
.Ltmp88:
	.cfi_offset %r13, -40
.Ltmp89:
	.cfi_offset %r14, -32
.Ltmp90:
	.cfi_offset %r15, -24
.Ltmp91:
	.cfi_offset %rbp, -16
	movl	%r9d, %r14d
	movq	%r8, %r12
	movq	%rcx, %rbx
	movq	%rdx, %r15
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	testl	%eax, %eax
	je	.LBB7_4
# BB#6:                                 # %label_elsezzzzzzzzzt
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#7:                                 # %entry_ifend5
	movq	(%rax), %r8
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#8:                                 # %entry_ifend8
	movq	(%rax), %rax
	movq	$0, 24(%rsp)
	movl	%eax, %r13d
	movq	%r13, 24(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#9:                                 # %entry_ifend12
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#10:                                # %entry_ifend15
	movq	(%rax), %rax
	movq	$0, 32(%rsp)
	movl	%eax, %eax
	movq	%rax, 32(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%r13d, %r13d
	je	.LBB7_11
# BB#15:                                # %label_elsezzzzzzzzzu
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$1, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB7_1
# BB#16:                                # %entry_ifend39
	movl	$0, gSigInt(%rip)
	movl	%r13d, %r9d
	movl	$1, (%rsp)
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB7_1
# BB#17:                                # %entry_ifend44
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#18:                                # %entry_ifend48
	movq	(%rax), %r9
	decl	%r9d
	movl	$2, (%rsp)
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB7_1
# BB#19:                                # %entry_ifend52
	movl	$0, gSigInt(%rip)
	movq	8(%rsp), %rax           # 8-byte Reload
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB7_2
.LBB7_4:                                # %entry_condend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB7_2
.LBB7_11:                               # %entry_condend20
	movq	%rax, %r13
	movl	$0, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB7_1
# BB#12:                                # %entry_ifend24
	movl	$0, gSigInt(%rip)
	movl	$1, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB7_1
# BB#13:                                # %entry_ifend28
	movl	$0, gSigInt(%rip)
	movl	$2, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB7_1
# BB#14:                                # %entry_ifend32
	movl	$0, gSigInt(%rip)
	movq	%r13, (%rbx)
	movl	$1, %eax
	jmp	.LBB7_2
.LBB7_1:                                # %then_block
	xorl	%eax, %eax
.LBB7_2:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end7:
	.size	"SortableList.pop()$$9", .Lfunc_end7-"SortableList.pop()$$9"
	.cfi_endproc

	.globl	"SortableList.shift()$$10"
	.align	16, 0x90
	.type	"SortableList.shift()$$10",@function
"SortableList.shift()$$10":             # @"SortableList.shift()$$10"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp92:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp93:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp94:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp95:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp96:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp97:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp98:
	.cfi_def_cfa_offset 96
.Ltmp99:
	.cfi_offset %rbx, -56
.Ltmp100:
	.cfi_offset %r12, -48
.Ltmp101:
	.cfi_offset %r13, -40
.Ltmp102:
	.cfi_offset %r14, -32
.Ltmp103:
	.cfi_offset %r15, -24
.Ltmp104:
	.cfi_offset %rbp, -16
	movl	%r9d, %r14d
	movq	%r8, %r12
	movq	%rcx, %rbx
	movq	%rdx, %r15
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	testl	%eax, %eax
	je	.LBB8_4
# BB#6:                                 # %label_elsezzzzzzzzzv
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#7:                                 # %entry_ifend5
	movq	(%rax), %r8
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#8:                                 # %entry_ifend8
	movq	(%rax), %rax
	movq	$0, 24(%rsp)
	movl	%eax, %r13d
	movq	%r13, 24(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#9:                                 # %entry_ifend12
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#10:                                # %entry_ifend15
	movq	(%rax), %rax
	movq	$0, 32(%rsp)
	movl	%eax, %eax
	movq	%rax, 32(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%r13d, %r13d
	je	.LBB8_11
# BB#15:                                # %label_elsezzzzzzzzzw
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$2, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB8_1
# BB#16:                                # %entry_ifend39
	movl	$0, gSigInt(%rip)
	movl	%r13d, %r9d
	movl	$0, (%rsp)
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB8_1
# BB#17:                                # %entry_ifend44
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#18:                                # %entry_ifend48
	movq	(%rax), %r9
	decl	%r9d
	movl	$2, (%rsp)
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB8_1
# BB#19:                                # %entry_ifend52
	movl	$0, gSigInt(%rip)
	movq	8(%rsp), %rax           # 8-byte Reload
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB8_2
.LBB8_4:                                # %entry_condend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB8_2
.LBB8_11:                               # %entry_condend20
	movq	%rax, %r13
	movl	$0, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB8_1
# BB#12:                                # %entry_ifend24
	movl	$0, gSigInt(%rip)
	movl	$1, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB8_1
# BB#13:                                # %entry_ifend28
	movl	$0, gSigInt(%rip)
	movl	$2, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB8_1
# BB#14:                                # %entry_ifend32
	movl	$0, gSigInt(%rip)
	movq	%r13, (%rbx)
	movl	$1, %eax
	jmp	.LBB8_2
.LBB8_1:                                # %then_block
	xorl	%eax, %eax
.LBB8_2:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end8:
	.size	"SortableList.shift()$$10", .Lfunc_end8-"SortableList.shift()$$10"
	.cfi_endproc

	.globl	"SortableList.insert(int,GenericsParametorClass0)$$11"
	.align	16, 0x90
	.type	"SortableList.insert(int,GenericsParametorClass0)$$11",@function
"SortableList.insert(int,GenericsParametorClass0)$$11": # @"SortableList.insert(int,GenericsParametorClass0)$$11"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp105:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp106:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp107:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp108:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp109:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp110:
	.cfi_def_cfa_offset 56
	subq	$120, %rsp
.Ltmp111:
	.cfi_def_cfa_offset 176
.Ltmp112:
	.cfi_offset %rbx, -56
.Ltmp113:
	.cfi_offset %r12, -48
.Ltmp114:
	.cfi_offset %r13, -40
.Ltmp115:
	.cfi_offset %r14, -32
.Ltmp116:
	.cfi_offset %r15, -24
.Ltmp117:
	.cfi_offset %rbp, -16
	movl	%r9d, %eax
	movq	%r8, %rdi
	movq	%rcx, %r14
	movq	%rdx, %rcx
	movq	%rsi, 40(%rsp)          # 8-byte Spill
	movq	(%r14), %r8
	movq	$0, 64(%rsp)
	movq	%r8, 64(%rsp)
	movq	8(%r14), %r12
	movq	$0, 72(%rsp)
	movq	%r12, 72(%rsp)
	movq	16(%r14), %rdx
	movq	%rdx, 48(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rdx, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%r12d, %r12d
	jns	.LBB9_5
# BB#1:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rdi, %r15
	movq	%r14, %rsi
	movl	%eax, %edx
	movl	%eax, %ebx
	movq	%rcx, %rbp
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#4:                                 # %entry_ifend
	movq	(%rax), %rax
	leal	1(%r12,%rax), %r12d
	movq	$0, 72(%rsp)
	movq	%r12, 72(%rsp)
	movq	%rbp, %rcx
	movl	%ebx, %eax
	movq	%r15, %rdi
.LBB9_5:                                # %label_if_endzzzzzzzzzx
	movl	$0, gSigInt(%rip)
	testl	%r12d, %r12d
	jns	.LBB9_7
# BB#6:                                 # %entry_condend12
	movl	$0, gSigInt(%rip)
	movq	$0, 72(%rsp)
	xorl	%r12d, %r12d
.LBB9_7:                                # %label_if_endzzzzzzzzzy
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r8d
	movl	$2, %r9d
	movq	%rdi, %rbx
	movq	%r14, %rsi
	movl	%eax, %edx
	movl	%eax, 60(%rsp)          # 4-byte Spill
	movq	%rcx, %rbp
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#8:                                 # %entry_ifend18
	movq	(%rax), %rax
	cmpl	%eax, %r12d
	jle	.LBB9_11
# BB#9:                                 # %entry_condend21
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r8d
	movl	$2, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#10:                                # %entry_ifend25
	movq	(%rax), %rax
	movq	$0, 72(%rsp)
	movl	%eax, %r12d
	movq	%r12, 72(%rsp)
.LBB9_11:                               # %label_if_endzzzzzzzzzz
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r8d
	movl	$2, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#12:                                # %entry_ifend30
	movq	(%rax), %rax
	testl	%eax, %eax
	sete	%al
	movq	$0, 112(%rsp)
	movzbl	%al, %eax
	movq	%rax, 112(%rsp)
	je	.LBB9_15
# BB#13:                                # %entry_condnotend
	movl	64(%rsp), %r8d
	movl	$2, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#14:                                # %entry_ifend36
	movq	(%rax), %rax
	cmpl	%eax, %r12d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, 112(%rsp)
.LBB9_15:                               # %label_or_endpointzzzzzzzzzzc
	movq	176(%rsp), %rdi
	movl	$0, gSigInt(%rip)
	testq	%rax, %rax
	je	.LBB9_20
# BB#16:                                # %entry_condend40
	movl	64(%rsp), %r15d
	movl	$6364, %esi             # imm = 0x18DC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_2
# BB#17:                                # %entry_ifend45
	movq	64(%rsp), %rcx
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	$0, 8(%rdx)
	movq	%r12, 8(%rdx)
	movq	$0, 16(%rdx)
	movq	48(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	$0, 32(%rdx)
	movq	$0, 40(%rdx)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	60(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB9_18
# BB#19:                                # %entry_ifend64
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	jmp	.LBB9_30
.LBB9_20:                               # %label_if_endzzzzzzzzzzb
	testl	%r12d, %r12d
	movl	$0, gSigInt(%rip)
	movq	%rbp, %rcx
	je	.LBB9_21
# BB#31:                                # %label_elsezzzzzzzzzzd
	movq	%rdi, %rbp
	movl	64(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%rcx, 32(%rsp)          # 8-byte Spill
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#32:                                # %entry_ifend169
	movq	(%rax), %rax
	movq	$0, 88(%rsp)
	movl	%eax, %r8d
	movq	%r8, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r13d, %r13d
	leal	-1(%r12), %r15d
	jmp	.LBB9_33
	.align	16, 0x90
.LBB9_48:                               # %entry_ifend278
                                        #   in Loop: Header=BB9_33 Depth=1
	movq	(%rax), %rax
	movq	$0, 88(%rsp)
	movl	%eax, %r8d
	movq	%r8, 88(%rsp)
	movl	$0, gSigInt(%rip)
	leal	1(%r13), %r13d
	movq	$0, 96(%rsp)
	movq	%r13, 96(%rsp)
.LBB9_33:                               # %while_start_pointzzzzzzzzzze
                                        # =>This Inner Loop Header: Depth=1
	testl	%r8d, %r8d
	je	.LBB9_30
# BB#34:                                # %entry_condend174
                                        #   in Loop: Header=BB9_33 Depth=1
	movl	$0, gSigInt(%rip)
	cmpl	%r15d, %r13d
	je	.LBB9_35
# BB#47:                                # %label_if_endzzzzzzzzzzf
                                        #   in Loop: Header=BB9_33 Depth=1
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB9_48
	jmp	.LBB9_2
.LBB9_21:                               # %entry_condend85
	movq	%rcx, %rbp
	movl	$6452, %esi             # imm = 0x1934
	movq	%rdi, %r15
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_2
# BB#22:                                # %entry_ifend88
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	64(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#23:                                # %entry_ifend93
	movq	(%rax), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movl	$6464, %esi             # imm = 0x1940
	movq	%r15, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_2
# BB#24:                                # %entry_ifend96
	movq	64(%rsp), %rcx
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	$0, 8(%rdx)
	movq	%r12, 8(%rdx)
	movq	$0, 16(%rdx)
	movq	48(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	$0, 32(%rdx)
	movq	$0, 40(%rdx)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	60(%rsp), %r15d         # 4-byte Reload
	movl	%r15d, %ecx
	movq	%rbx, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB9_18
# BB#25:                                # %entry_ifend124
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 88(%rsp)
	movq	%r12, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#26:                                # %entry_ifend146
	movq	(%rax), %r8
	movl	88(%rsp), %r9d
	movl	$2, (%rsp)
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%rbp, %rcx
	callq	store_field
	testl	%eax, %eax
	je	.LBB9_2
# BB#27:                                # %entry_ifend150
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r8d
	movl	88(%rsp), %r9d
	movl	$0, (%rsp)
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%rbp, %rcx
	callq	store_field
	testl	%eax, %eax
	je	.LBB9_2
# BB#28:                                # %entry_ifend155
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r8d
	movl	$2, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#29:                                # %entry_ifend159
	movq	(%rax), %r9
	incl	%r9d
	movl	64(%rsp), %r8d
	movl	$2, (%rsp)
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%rbp, %rcx
	callq	store_field
	testl	%eax, %eax
	jne	.LBB9_30
	jmp	.LBB9_2
.LBB9_35:                               # %entry_condend181
	movl	$6604, %esi             # imm = 0x19CC
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_2
# BB#36:                                # %entry_ifend184
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 28(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	88(%rsp), %r15d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	movl	%r15d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#37:                                # %entry_ifend190
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movl	$6616, %esi             # imm = 0x19D8
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_2
# BB#38:                                # %entry_ifend193
	movq	64(%rsp), %rcx
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	$0, 8(%rdx)
	movq	%r12, 8(%rdx)
	movq	$0, 16(%rdx)
	movq	48(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	$0, 32(%rdx)
	movq	%r13, 32(%rdx)
	movq	$0, 40(%rdx)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	60(%rsp), %r13d         # 4-byte Reload
	movl	%r13d, %ecx
	movq	%rbx, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB9_39
.LBB9_18:                               # %then_block63
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB9_2:                                # %then_block
	xorl	%eax, %eax
.LBB9_3:                                # %then_block
	addq	$120, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB9_39:                               # %entry_ifend221
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 104(%rsp)
	movq	%r12, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%rbx, %r15
	movq	%r14, %rsi
	movl	%r13d, %edx
	movl	%r13d, %ebx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#40:                                # %entry_ifend243
	movq	(%rax), %rax
	testl	%eax, %eax
	je	.LBB9_43
# BB#41:                                # %entry_condend248
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %r8d
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#42:                                # %entry_ifend252
	movq	(%rax), %r8
	movl	%r12d, %r9d
	movl	$2, (%rsp)
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	store_field
	testl	%eax, %eax
	je	.LBB9_2
.LBB9_43:                               # %label_if_endzzzzzzzzzzg
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %r8d
	movl	%r12d, %r9d
	movl	$1, (%rsp)
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	store_field
	testl	%eax, %eax
	je	.LBB9_2
# BB#44:                                # %entry_ifend262
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r8d
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#45:                                # %entry_ifend266
	movq	(%rax), %r9
	incl	%r9d
	movl	64(%rsp), %r8d
	movl	$2, (%rsp)
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	store_field
	testl	%eax, %eax
	je	.LBB9_2
# BB#46:                                # %entry_ifend271
	movl	$0, gSigInt(%rip)
.LBB9_30:                               # %label_if_endzzzzzzzzzzd
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB9_3
.Lfunc_end9:
	.size	"SortableList.insert(int,GenericsParametorClass0)$$11", .Lfunc_end9-"SortableList.insert(int,GenericsParametorClass0)$$11"
	.cfi_endproc

	.globl	"SortableList.deleteAt(int)$$12"
	.align	16, 0x90
	.type	"SortableList.deleteAt(int)$$12",@function
"SortableList.deleteAt(int)$$12":       # @"SortableList.deleteAt(int)$$12"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp118:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp119:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp120:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp121:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp122:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp123:
	.cfi_def_cfa_offset 56
	subq	$88, %rsp
.Ltmp124:
	.cfi_def_cfa_offset 144
.Ltmp125:
	.cfi_offset %rbx, -56
.Ltmp126:
	.cfi_offset %r12, -48
.Ltmp127:
	.cfi_offset %r13, -40
.Ltmp128:
	.cfi_offset %r14, -32
.Ltmp129:
	.cfi_offset %r15, -24
.Ltmp130:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebp
	movl	%ebp, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r12
	movq	%rcx, %r13
	movq	%rdx, %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	(%r13), %r8
	movq	$0, 32(%rsp)
	movq	%r8, 32(%rsp)
	movq	8(%r13), %r14
	movq	$0, 40(%rsp)
	movq	%r14, 40(%rsp)
	movq	$0, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	%ebp, %edx
	movq	%rax, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movl	%eax, %ebx
	movq	%rbx, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#4:                                 # %entry_ifend5
	movq	(%rax), %rax
	movq	$0, 56(%rsp)
	movl	%eax, %ebp
	movq	%rbp, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r15d, %r15d
	jmp	.LBB10_5
	.align	16, 0x90
.LBB10_51:                              # %entry_ifend199
                                        #   in Loop: Header=BB10_5 Depth=1
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movl	%eax, %ebx
	movq	%rbx, 48(%rsp)
.LBB10_5:                               # %while_start_pointzzzzzzzzzzh
                                        # =>This Inner Loop Header: Depth=1
	testl	%ebx, %ebx
	je	.LBB10_17
# BB#6:                                 # %entry_condend
                                        #   in Loop: Header=BB10_5 Depth=1
	movl	$0, gSigInt(%rip)
	cmpl	%r14d, %r15d
	je	.LBB10_7
# BB#50:                                # %label_if_endzzzzzzzzzzi
                                        #   in Loop: Header=BB10_5 Depth=1
	incl	%r15d
	movq	$0, 64(%rsp)
	movq	%r15, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 56(%rsp)
	movl	%ebx, %ebp
	movq	%rbp, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB10_51
	jmp	.LBB10_1
.LBB10_7:                               # %entry_condend12
	movl	32(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#8:                                 # %entry_ifend17
	movq	(%rax), %rax
	cmpl	%eax, %ebx
	sete	%al
	movq	$0, 72(%rsp)
	movzbl	%al, %eax
	movq	%rax, 72(%rsp)
	jne	.LBB10_11
# BB#9:                                 # %entry_condend21
	movl	32(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#10:                                # %entry_ifend26
	movq	(%rax), %rax
	cmpl	%eax, %ebx
	sete	%al
	movzbl	%al, %eax
	movq	%rax, 72(%rsp)
.LBB10_11:                              # %label_and_endpointzzzzzzzzzzk
	testq	%rax, %rax
	je	.LBB10_18
# BB#12:                                # %entry_condend30
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	movl	$0, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB10_1
# BB#13:                                # %entry_ifend34
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	movl	$1, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB10_1
# BB#14:                                # %entry_ifend38
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	movl	$2, (%rsp)
	xorl	%r9d, %r9d
.LBB10_15:                              # %entry_ifend38
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB10_1
# BB#16:                                # %label_if_endzzzzzzzzzzj
	movl	$0, gSigInt(%rip)
.LBB10_17:                              # %label_whilezzzzzzzzzzh
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB10_2
.LBB10_18:                              # %label_elifzzzzzzzzzzj1a
	movl	32(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#19:                                # %entry_ifend48
	movq	(%rax), %rax
	cmpl	%eax, %ebp
	sete	%al
	movq	$0, 80(%rsp)
	movzbl	%al, %eax
	movq	%rax, 80(%rsp)
	jne	.LBB10_22
# BB#20:                                # %entry_condend53
	movl	32(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#21:                                # %entry_ifend58
	movq	(%rax), %rax
	cmpl	%eax, %ebx
	sete	%al
	movzbl	%al, %eax
	movq	%rax, 80(%rsp)
.LBB10_22:                              # %label_and_endpointzzzzzzzzzzl
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	testq	%rax, %rax
	je	.LBB10_28
# BB#23:                                # %entry_condend64
	movl	%ebp, %ebx
	movl	$0, (%rsp)
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	%rbx, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB10_1
# BB#24:                                # %entry_ifend69
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	movl	$1, (%rsp)
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	%rbx, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB10_1
# BB#25:                                # %entry_ifend74
	movl	$0, gSigInt(%rip)
	movl	$2, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB10_1
# BB#26:                                # %entry_ifend78
	movl	$0, gSigInt(%rip)
	movl	$1, (%rsp)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB10_1
# BB#27:                                # %entry_ifend82
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	movl	$2, (%rsp)
	movl	$1, %r9d
	jmp	.LBB10_15
.LBB10_28:                              # %label_if_elifzzzzzzzzzzj0a
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#29:                                # %entry_ifend92
	movq	(%rax), %rax
	cmpl	%eax, %ebx
	jne	.LBB10_39
# BB#30:                                # %entry_condend96
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %ebx
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#31:                                # %entry_ifend101
	movq	(%rax), %r8
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#32:                                # %entry_ifend104
	movq	(%rax), %rax
	movl	%eax, %r9d
	movl	$0, (%rsp)
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%ebx, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB10_1
# BB#33:                                # %entry_ifend107
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#34:                                # %entry_ifend111
	movq	(%rax), %r8
	movl	$2, (%rsp)
	jmp	.LBB10_35
.LBB10_39:                              # %label_elifzzzzzzzzzzm1a
	movl	32(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#40:                                # %entry_ifend128
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %ebx
	jne	.LBB10_46
# BB#41:                                # %entry_condend132
	movl	32(%rsp), %ebx
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#42:                                # %entry_ifend137
	movq	(%rax), %r8
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#43:                                # %entry_ifend140
	movq	(%rax), %rax
	movl	%eax, %r9d
	movl	$1, (%rsp)
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%ebx, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB10_1
# BB#44:                                # %entry_ifend143
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#45:                                # %entry_ifend147
	movq	(%rax), %r8
	movl	$1, (%rsp)
.LBB10_35:                              # %entry_ifend111
	xorl	%r9d, %r9d
	jmp	.LBB10_36
.LBB10_46:                              # %label_if_elifzzzzzzzzzzm0a
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#47:                                # %entry_ifend166
	movq	(%rax), %rax
	movl	%eax, %r9d
	movl	$1, (%rsp)
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB10_1
# BB#48:                                # %entry_ifend169
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#49:                                # %entry_ifend173
	movq	(%rax), %r8
	movl	%ebp, %r9d
	movl	$2, (%rsp)
.LBB10_36:                              # %entry_ifend111
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB10_1
# BB#37:                                # %entry_ifend114
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#38:                                # %entry_ifend118
	movq	(%rax), %r9
	decl	%r9d
	movl	32(%rsp), %r8d
	movl	$2, (%rsp)
	jmp	.LBB10_15
.LBB10_1:                               # %then_block
	xorl	%eax, %eax
.LBB10_2:                               # %then_block
	addq	$88, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end10:
	.size	"SortableList.deleteAt(int)$$12", .Lfunc_end10-"SortableList.deleteAt(int)$$12"
	.cfi_endproc

	.globl	"SortableList.each(lambda)$$13"
	.align	16, 0x90
	.type	"SortableList.each(lambda)$$13",@function
"SortableList.each(lambda)$$13":        # @"SortableList.each(lambda)$$13"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp131:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp132:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp133:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp134:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp135:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp136:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp137:
	.cfi_def_cfa_offset 96
.Ltmp138:
	.cfi_offset %rbx, -56
.Ltmp139:
	.cfi_offset %r12, -48
.Ltmp140:
	.cfi_offset %r13, -40
.Ltmp141:
	.cfi_offset %r14, -32
.Ltmp142:
	.cfi_offset %r15, -24
.Ltmp143:
	.cfi_offset %rbp, -16
	movl	%r9d, %r14d
	movq	%r8, %rbp
	movq	%rcx, %r13
	movq	%rdx, %r12
	movq	(%r13), %r8
	movq	%r8, 8(%rsp)            # 8-byte Spill
	movq	$0, 16(%rsp)
	movq	%r8, 16(%rsp)
	movq	8(%r13), %r15
	movq	$0, 24(%rsp)
	movq	%r15, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	$0, 32(%rsp)
	movl	%eax, %ebx
	movq	%rbx, 32(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB11_4
	.align	16, 0x90
.LBB11_8:                               # %entry_ifend22
                                        #   in Loop: Header=BB11_4 Depth=1
	movq	(%rax), %rax
	movq	$0, 32(%rsp)
	movl	%eax, %ebx
	movq	%rbx, 32(%rsp)
.LBB11_4:                               # %while_start_pointzzzzzzzzzzn
                                        # =>This Inner Loop Header: Depth=1
	testl	%ebx, %ebx
	movl	$0, gSigInt(%rip)
	je	.LBB11_9
# BB#5:                                 # %entry_condend
                                        #   in Loop: Header=BB11_4 Depth=1
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#6:                                 # %entry_ifend7
                                        #   in Loop: Header=BB11_4 Depth=1
	movq	(%rax), %rax
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
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
	movq	%r12, %r8
	callq	invoke_block_in_jit
	testl	%eax, %eax
	je	.LBB11_1
# BB#7:                                 # %entry_ifend14
                                        #   in Loop: Header=BB11_4 Depth=1
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB11_8
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
.LBB11_9:                               # %label_whilezzzzzzzzzzn
	movq	8(%rsp), %rax           # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB11_2
.Lfunc_end11:
	.size	"SortableList.each(lambda)$$13", .Lfunc_end11-"SortableList.each(lambda)$$13"
	.cfi_endproc

	.globl	"SortableList.eachReverse(lambda)$$14"
	.align	16, 0x90
	.type	"SortableList.eachReverse(lambda)$$14",@function
"SortableList.eachReverse(lambda)$$14": # @"SortableList.eachReverse(lambda)$$14"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp144:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp145:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp146:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp147:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp148:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp149:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp150:
	.cfi_def_cfa_offset 96
.Ltmp151:
	.cfi_offset %rbx, -56
.Ltmp152:
	.cfi_offset %r12, -48
.Ltmp153:
	.cfi_offset %r13, -40
.Ltmp154:
	.cfi_offset %r14, -32
.Ltmp155:
	.cfi_offset %r15, -24
.Ltmp156:
	.cfi_offset %rbp, -16
	movl	%r9d, %r14d
	movq	%r8, %rbp
	movq	%rcx, %r13
	movq	%rdx, %r12
	movq	(%r13), %r8
	movq	%r8, 8(%rsp)            # 8-byte Spill
	movq	$0, 16(%rsp)
	movq	%r8, 16(%rsp)
	movq	8(%r13), %r15
	movq	$0, 24(%rsp)
	movq	%r15, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB12_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	$0, 32(%rsp)
	movl	%eax, %ebx
	movq	%rbx, 32(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB12_4
	.align	16, 0x90
.LBB12_8:                               # %entry_ifend22
                                        #   in Loop: Header=BB12_4 Depth=1
	movq	(%rax), %rax
	movq	$0, 32(%rsp)
	movl	%eax, %ebx
	movq	%rbx, 32(%rsp)
.LBB12_4:                               # %while_start_pointzzzzzzzzzzo
                                        # =>This Inner Loop Header: Depth=1
	testl	%ebx, %ebx
	movl	$0, gSigInt(%rip)
	je	.LBB12_9
# BB#5:                                 # %entry_condend
                                        #   in Loop: Header=BB12_4 Depth=1
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB12_1
# BB#6:                                 # %entry_ifend7
                                        #   in Loop: Header=BB12_4 Depth=1
	movq	(%rax), %rax
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
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
	movq	%r12, %r8
	callq	invoke_block_in_jit
	testl	%eax, %eax
	je	.LBB12_1
# BB#7:                                 # %entry_ifend14
                                        #   in Loop: Header=BB12_4 Depth=1
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB12_8
.LBB12_1:                               # %then_block
	xorl	%eax, %eax
.LBB12_2:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB12_9:                               # %label_whilezzzzzzzzzzo
	movq	8(%rsp), %rax           # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB12_2
.Lfunc_end12:
	.size	"SortableList.eachReverse(lambda)$$14", .Lfunc_end12-"SortableList.eachReverse(lambda)$$14"
	.cfi_endproc

	.globl	"SortableList.replace(int,GenericsParametorClass0)$$15"
	.align	16, 0x90
	.type	"SortableList.replace(int,GenericsParametorClass0)$$15",@function
"SortableList.replace(int,GenericsParametorClass0)$$15": # @"SortableList.replace(int,GenericsParametorClass0)$$15"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp157:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp158:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp159:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp160:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp161:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp162:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp163:
	.cfi_def_cfa_offset 128
.Ltmp164:
	.cfi_offset %rbx, -56
.Ltmp165:
	.cfi_offset %r12, -48
.Ltmp166:
	.cfi_offset %r13, -40
.Ltmp167:
	.cfi_offset %r14, -32
.Ltmp168:
	.cfi_offset %r15, -24
.Ltmp169:
	.cfi_offset %rbp, -16
	movl	%r9d, %r15d
	movq	%r8, %rbp
	movq	%rcx, %rbx
	movq	%rdx, %r12
	movq	(%rbx), %r8
	movq	$0, 32(%rsp)
	movq	%r8, 32(%rsp)
	movq	8(%rbx), %r13
	movq	$0, 40(%rsp)
	movq	%r13, 40(%rsp)
	movq	16(%rbx), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%r13d, %r13d
	jns	.LBB13_5
# BB#1:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	%r8, %r14
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB13_2
# BB#4:                                 # %entry_ifend
	movq	(%rax), %rax
	addl	%eax, %r13d
	movq	$0, 40(%rsp)
	movq	%r13, 40(%rsp)
	movq	%r14, %r8
.LBB13_5:                               # %label_if_endzzzzzzzzzzp
	movl	$0, gSigInt(%rip)
	testl	%r13d, %r13d
	jns	.LBB13_7
# BB#6:                                 # %entry_condend11
	movl	$0, gSigInt(%rip)
	movq	$0, 40(%rsp)
	xorl	%r13d, %r13d
.LBB13_7:                               # %label_if_endzzzzzzzzzzq
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	%r8, 24(%rsp)           # 8-byte Spill
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB13_2
# BB#8:                                 # %entry_ifend17
	movq	(%rax), %rax
	cmpl	%eax, %r13d
	jl	.LBB13_11
# BB#9:                                 # %entry_condend20
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB13_2
# BB#10:                                # %entry_ifend24
	movq	(%rax), %r13
	decl	%r13d
	movq	$0, 40(%rsp)
	movq	%r13, 40(%rsp)
.LBB13_11:                              # %label_if_endzzzzzzzzzzr
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB13_2
# BB#12:                                # %entry_ifend29
	movq	(%rax), %rax
	movq	$0, 56(%rsp)
	movl	%eax, %r8d
	movq	%r8, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r14d, %r14d
	jmp	.LBB13_13
	.align	16, 0x90
.LBB13_19:                              # %entry_ifend53
                                        #   in Loop: Header=BB13_13 Depth=1
	movq	(%rax), %rax
	movq	$0, 56(%rsp)
	movl	%eax, %r8d
	movq	%r8, 56(%rsp)
.LBB13_13:                              # %while_start_pointzzzzzzzzzzs
                                        # =>This Inner Loop Header: Depth=1
	testl	%r8d, %r8d
	je	.LBB13_17
# BB#14:                                # %entry_condend33
                                        #   in Loop: Header=BB13_13 Depth=1
	movl	$0, gSigInt(%rip)
	cmpl	%r13d, %r14d
	je	.LBB13_15
# BB#18:                                # %label_if_endzzzzzzzzzzt
                                        #   in Loop: Header=BB13_13 Depth=1
	incl	%r14d
	movq	$0, 64(%rsp)
	movq	%r14, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB13_19
	jmp	.LBB13_2
.LBB13_15:                              # %entry_condend39
	movq	16(%rsp), %rax          # 8-byte Reload
	movl	%eax, %r9d
	movl	$0, (%rsp)
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	callq	store_field
	testl	%eax, %eax
	je	.LBB13_2
# BB#16:                                # %entry_ifend44
	movl	$0, gSigInt(%rip)
.LBB13_17:                              # %label_whilezzzzzzzzzzs
	movl	$0, gSigInt(%rip)
	movq	24(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB13_3
.LBB13_2:                               # %then_block
	xorl	%eax, %eax
.LBB13_3:                               # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end13:
	.size	"SortableList.replace(int,GenericsParametorClass0)$$15", .Lfunc_end13-"SortableList.replace(int,GenericsParametorClass0)$$15"
	.cfi_endproc

	.globl	"SortableList.sample()$$16"
	.align	16, 0x90
	.type	"SortableList.sample()$$16",@function
"SortableList.sample()$$16":            # @"SortableList.sample()$$16"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp170:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp171:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp172:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp173:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp174:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp175:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp176:
	.cfi_def_cfa_offset 96
.Ltmp177:
	.cfi_offset %rbx, -56
.Ltmp178:
	.cfi_offset %r12, -48
.Ltmp179:
	.cfi_offset %r13, -40
.Ltmp180:
	.cfi_offset %r14, -32
.Ltmp181:
	.cfi_offset %r15, -24
.Ltmp182:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebx
	movq	%r8, %r12
	movq	%rcx, %r15
	movq	%rdx, %rbp
	movq	%rsi, %r14
	movq	96(%rsp), %rdi
	movq	(%r15), %r13
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$8308, %esi             # imm = 0x2074
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB14_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r14)
	movq	%r13, (%r14)
	movl	$15, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r12, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbp, %rdi
	je	.LBB14_5
# BB#4:                                 # %then_block4
	callq	get_try_catch_label_name
	jmp	.LBB14_1
.LBB14_5:                               # %entry_ifend5
	movl	%ebx, %ebp
	movl	%ebp, 20(%rsp)          # 4-byte Spill
	movq	%rdi, 24(%rsp)          # 8-byte Spill
	movq	%r12, %rbx
	movq	(%r15), %r12
	movq	$0, 32(%rsp)
	movq	%r12, 32(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	movl	%edi, 16(%rsp)          # 4-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$2, %r9d
	movq	%rbx, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB14_1
# BB#6:                                 # %entry_ifend11
	movq	%rbx, 8(%rsp)           # 8-byte Spill
	movl	20(%rsp), %ebx          # 4-byte Reload
	movq	(%rax), %rcx
	testl	%ecx, %ecx
	je	.LBB14_7
# BB#8:                                 # %entry_ifend14
	movl	16(%rsp), %eax          # 4-byte Reload
	cltd
	idivl	%ecx
	movl	%edx, 16(%rsp)          # 4-byte Spill
	movl	$8316, %esi             # imm = 0x207C
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebx, %ecx
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	8(%rsp), %rbp           # 8-byte Reload
	je	.LBB14_1
# BB#9:                                 # %entry_ifend17
	movq	$0, (%r14)
	movq	%r12, (%r14)
	movq	(%rbp), %rsi
	movq	$0, (%rsi)
	movl	%r13d, %edx
	movq	%rdx, (%rsi)
	movq	(%rbp), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rsi)
	movl	16(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rsi)
	addq	$8, (%rbp)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movq	%rbp, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	movq	%rbp, %rbx
	je	.LBB14_11
# BB#10:                                # %then_block28
	callq	get_try_catch_label_name
	jmp	.LBB14_1
.LBB14_7:                               # %then_block13
	movl	$.Lglobal_string.6, %r8d
	movl	$.Lglobal_string.7, %r9d
	movq	8(%rsp), %rdi           # 8-byte Reload
	movq	%r15, %rsi
	movl	%ebx, %edx
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	entry_exception_object_with_class_name2
.LBB14_1:                               # %then_block
	xorl	%eax, %eax
.LBB14_2:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB14_11:                              # %entry_ifend29
	movq	(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbp, (%r15)
	movl	$1, %eax
	jmp	.LBB14_2
.Lfunc_end14:
	.size	"SortableList.sample()$$16", .Lfunc_end14-"SortableList.sample()$$16"
	.cfi_endproc

	.globl	"SortableList.map(lambda)$$17"
	.align	16, 0x90
	.type	"SortableList.map(lambda)$$17",@function
"SortableList.map(lambda)$$17":         # @"SortableList.map(lambda)$$17"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp183:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp184:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp185:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp186:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp187:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp188:
	.cfi_def_cfa_offset 56
	subq	$88, %rsp
.Ltmp189:
	.cfi_def_cfa_offset 144
.Ltmp190:
	.cfi_offset %rbx, -56
.Ltmp191:
	.cfi_offset %r12, -48
.Ltmp192:
	.cfi_offset %r13, -40
.Ltmp193:
	.cfi_offset %r14, -32
.Ltmp194:
	.cfi_offset %r15, -24
.Ltmp195:
	.cfi_offset %rbp, -16
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r12
	movq	%rcx, %r15
	movq	%rdx, 48(%rsp)          # 8-byte Spill
	movq	%rsi, %rbp
	movq	144(%rsp), %rdi
	movq	(%r15), %r13
	movq	$0, 56(%rsp)
	movq	%r13, 56(%rsp)
	movq	8(%r15), %rbx
	movq	$0, 64(%rsp)
	movq	%rbx, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$8332, %esi             # imm = 0x208C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB15_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movl	$8348, %esi             # imm = 0x209C
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB15_1
# BB#4:                                 # %entry_ifend3
	movq	$0, (%rbp)
	movq	%r13, (%rbp)
	movq	$0, 8(%rbp)
	movq	%rbx, 8(%rbp)
	movq	$0, 16(%rbp)
	movq	$0, 24(%rbp)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	20(%rsp), %r14d         # 4-byte Reload
	movl	%r14d, %ecx
	movq	%r12, %r8
	movq	48(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB15_5
# BB#6:                                 # %entry_ifend15
	movq	%rbp, 8(%rsp)           # 8-byte Spill
	movq	(%r15), %r13
	movq	%r13, 24(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%r13, 56(%rsp)
	movq	8(%r15), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %rbp
	movq	%rbp, 32(%rsp)          # 8-byte Spill
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 72(%rsp)
	movq	%rbp, 72(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%r14d, %edx
	movl	%r14d, %ebp
	movq	%rbx, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB15_1
# BB#7:                                 # %entry_ifend29
	movq	(%rax), %rax
	movq	$0, 80(%rsp)
	movl	%eax, %r14d
	movq	%r14, 80(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB15_8
	.align	16, 0x90
.LBB15_14:                              # %entry_ifend89
                                        #   in Loop: Header=BB15_8 Depth=1
	movq	(%rax), %rax
	movq	$0, 80(%rsp)
	movl	%eax, %r14d
	movq	%r14, 80(%rsp)
.LBB15_8:                               # %while_start_pointzzzzzzzzzzu
                                        # =>This Inner Loop Header: Depth=1
	testl	%r14d, %r14d
	movl	$0, gSigInt(%rip)
	movl	%ebp, %edx
	je	.LBB15_15
# BB#9:                                 # %entry_condend
                                        #   in Loop: Header=BB15_8 Depth=1
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%edx, %ebx
	movq	48(%rsp), %rcx          # 8-byte Reload
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB15_1
# BB#10:                                # %entry_ifend36
                                        #   in Loop: Header=BB15_8 Depth=1
	movq	(%rax), %rax
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	$1, %edi
	movq	%r15, %rsi
	movl	%ebx, %edx
	movq	%r12, %rcx
	movq	48(%rsp), %r8           # 8-byte Reload
	callq	invoke_block_in_jit
	testl	%eax, %eax
	je	.LBB15_1
# BB#11:                                # %entry_ifend45
                                        #   in Loop: Header=BB15_8 Depth=1
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$8420, %esi             # imm = 0x20E4
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB15_1
# BB#12:                                # %entry_ifend53
                                        #   in Loop: Header=BB15_8 Depth=1
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	%r14, 24(%rcx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r12)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ebp
	movl	%ebp, %ecx
	movq	%r12, %r8
	movq	48(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB15_5
# BB#13:                                # %entry_ifend71
                                        #   in Loop: Header=BB15_8 Depth=1
	movq	(%r15), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r15), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%r15), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%r15), %r14
	movq	$0, 80(%rsp)
	movq	%r14, 80(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB15_14
	jmp	.LBB15_1
.LBB15_5:                               # %then_block14
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB15_1:                               # %then_block
	xorl	%eax, %eax
.LBB15_2:                               # %then_block
	addq	$88, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB15_15:                              # %label_whilezzzzzzzzzzu
	movq	32(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%r15)
	movl	$1, %eax
	jmp	.LBB15_2
.Lfunc_end15:
	.size	"SortableList.map(lambda)$$17", .Lfunc_end15-"SortableList.map(lambda)$$17"
	.cfi_endproc

	.globl	"SortableList.append(Self)$$18"
	.align	16, 0x90
	.type	"SortableList.append(Self)$$18",@function
"SortableList.append(Self)$$18":        # @"SortableList.append(Self)$$18"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp196:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp197:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp198:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp199:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp200:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp201:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp202:
	.cfi_def_cfa_offset 128
.Ltmp203:
	.cfi_offset %rbx, -56
.Ltmp204:
	.cfi_offset %r12, -48
.Ltmp205:
	.cfi_offset %r13, -40
.Ltmp206:
	.cfi_offset %r14, -32
.Ltmp207:
	.cfi_offset %r15, -24
.Ltmp208:
	.cfi_offset %rbp, -16
	movl	%r9d, 44(%rsp)          # 4-byte Spill
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, 48(%rsp)          # 8-byte Spill
	movq	%rsi, %rbp
	movq	128(%rsp), %rax
	movq	(%r14), %r15
	movq	$0, 56(%rsp)
	movq	%r15, 56(%rsp)
	movq	8(%r14), %r12
	movq	$0, 64(%rsp)
	movq	%r12, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movq	%rdx, 32(%rsp)
	movl	$0, 24(%rsp)
	movl	$2, 16(%rsp)
	movl	$1, 8(%rsp)
	movl	$13, (%rsp)
	movl	$8492, %ecx             # imm = 0x212C
	movl	$44, %r8d
	movl	$8536, %r9d             # imm = 0x2158
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movq	%rax, %rdx
	callq	run_create_block_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$8552, %esi             # imm = 0x2168
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB16_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%r15, (%rbp)
	movq	$0, 8(%rbp)
	movq	%r12, 8(%rbp)
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
	movl	$13, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	48(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB16_5
# BB#4:                                 # %then_block11
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB16_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB16_2
.LBB16_5:                               # %entry_ifend12
	movq	(%r14), %rbp
	movq	$0, 56(%rsp)
	movq	%rbp, 56(%rsp)
	movq	8(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	%ebp, %eax
	movq	%rax, (%r14)
	movl	$1, %eax
.LBB16_2:                               # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end16:
	.size	"SortableList.append(Self)$$18", .Lfunc_end16-"SortableList.append(Self)$$18"
	.cfi_endproc

	.globl	"SortableList.multiply(int)$$19"
	.align	16, 0x90
	.type	"SortableList.multiply(int)$$19",@function
"SortableList.multiply(int)$$19":       # @"SortableList.multiply(int)$$19"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp209:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp210:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp211:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp212:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp213:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp214:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp215:
	.cfi_def_cfa_offset 112
.Ltmp216:
	.cfi_offset %rbx, -56
.Ltmp217:
	.cfi_offset %r12, -48
.Ltmp218:
	.cfi_offset %r13, -40
.Ltmp219:
	.cfi_offset %r14, -32
.Ltmp220:
	.cfi_offset %r15, -24
.Ltmp221:
	.cfi_offset %rbp, -16
	movl	%r9d, 4(%rsp)           # 4-byte Spill
	movq	%r8, %r12
	movq	%rdx, 8(%rsp)           # 8-byte Spill
	movq	%rsi, %r15
	movq	112(%rsp), %rdi
	movq	(%rcx), %r14
	movq	$0, 24(%rsp)
	movq	%r14, 24(%rsp)
	movq	8(%rcx), %rbp
	movq	%rcx, %rbx
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$8568, %esi             # imm = 0x2178
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB17_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$8584, %esi             # imm = 0x2188
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB17_1
# BB#4:                                 # %entry_ifend3
	movq	$0, (%r15)
	movq	%r14, (%r15)
	movq	$0, 8(%r15)
	movq	%rbp, 8(%r15)
	movq	$0, 16(%r15)
	movq	$0, 24(%r15)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%rbx, %r13
	movq	%r13, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%r12, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB17_6
# BB#5:                                 # %then_block14
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB17_1
.LBB17_6:                               # %entry_ifend15
	movq	%r12, %r14
	movq	(%r13), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	16(%r13), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	24(%r13), %rax
	movq	%r13, %rbx
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 40(%rsp)
	movq	%r13, 40(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 48(%rsp)
	xorl	%r12d, %r12d
	jmp	.LBB17_7
	.align	16, 0x90
.LBB17_11:                              # %entry_ifend50
                                        #   in Loop: Header=BB17_7 Depth=1
	movq	(%rbx), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%rbx), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	16(%rbx), %r13
	movq	$0, 40(%rsp)
	movq	%r13, 40(%rsp)
	movq	24(%rbx), %r12
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	incl	%r12d
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
.LBB17_7:                               # %for_start_pointzzzzzzzzzzv
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	cmpl	%ebp, %r12d
	jge	.LBB17_12
# BB#8:                                 # %entry_condend
                                        #   in Loop: Header=BB17_7 Depth=1
	movl	$8656, %esi             # imm = 0x21D0
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB17_1
# BB#9:                                 # %entry_ifend32
                                        #   in Loop: Header=BB17_7 Depth=1
	movq	$0, (%r15)
	movq	16(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, (%r15)
	movq	$0, 8(%r15)
	movq	%rbp, 8(%r15)
	movq	$0, 16(%r15)
	movq	%r13, 16(%r15)
	movq	$0, 24(%r15)
	movq	%r12, 24(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$18, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %rbp           # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB17_11
# BB#10:                                # %then_block49
	movq	%rbp, %rdi
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
.LBB17_12:                              # %label_for_endzzzzzzzzzzv
	movl	%r13d, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB17_2
.Lfunc_end17:
	.size	"SortableList.multiply(int)$$19", .Lfunc_end17-"SortableList.multiply(int)$$19"
	.cfi_endproc

	.globl	"SortableList.select(lambda)$$20"
	.align	16, 0x90
	.type	"SortableList.select(lambda)$$20",@function
"SortableList.select(lambda)$$20":      # @"SortableList.select(lambda)$$20"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp222:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp223:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp224:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp225:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp226:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp227:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp228:
	.cfi_def_cfa_offset 128
.Ltmp229:
	.cfi_offset %rbx, -56
.Ltmp230:
	.cfi_offset %r12, -48
.Ltmp231:
	.cfi_offset %r13, -40
.Ltmp232:
	.cfi_offset %r14, -32
.Ltmp233:
	.cfi_offset %r15, -24
.Ltmp234:
	.cfi_offset %rbp, -16
	movl	%r9d, 36(%rsp)          # 4-byte Spill
	movq	%r8, %rbp
	movq	%rcx, %r15
	movq	%rdx, 16(%rsp)          # 8-byte Spill
	movq	%rsi, %r12
	movq	128(%rsp), %rdi
	movq	(%r15), %rbx
	movq	$0, 40(%rsp)
	movq	%rbx, 40(%rsp)
	movq	8(%r15), %r14
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$8728, %esi             # imm = 0x2218
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$8744, %esi             # imm = 0x2228
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#4:                                 # %entry_ifend3
	movq	$0, (%r12)
	movq	%rbx, (%r12)
	movq	$0, 8(%r12)
	movq	%r14, 8(%r12)
	movq	$0, 16(%r12)
	movq	$0, 24(%r12)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbp)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	36(%rsp), %r14d         # 4-byte Reload
	movl	%r14d, %ecx
	movq	%rbp, %r8
	movq	16(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB18_6
# BB#5:                                 # %then_block14
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB18_1
.LBB18_6:                               # %entry_ifend15
	movq	(%r15), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r15), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movq	%rbx, (%rsp)            # 8-byte Spill
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 56(%rsp)
	movq	%rbx, 56(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r15, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movq	%r13, %rbx
	movq	8(%rsp), %r8            # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#7:                                 # %entry_ifend29
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movl	%eax, %r13d
	movq	%r13, 64(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB18_8
	.align	16, 0x90
.LBB18_14:                              # %entry_ifend97
                                        #   in Loop: Header=BB18_8 Depth=1
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movl	%eax, %r13d
	movq	%r13, 64(%rsp)
.LBB18_8:                               # %while_start_pointzzzzzzzzzzw
                                        # =>This Inner Loop Header: Depth=1
	movq	%rbx, %rcx
	testl	%r13d, %r13d
	movl	$0, gSigInt(%rip)
	je	.LBB18_20
# BB#9:                                 # %entry_condend
                                        #   in Loop: Header=BB18_8 Depth=1
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r15, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	%rcx, %r14
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#10:                                # %entry_ifend35
                                        #   in Loop: Header=BB18_8 Depth=1
	movq	(%rax), %rax
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
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
	movq	%r15, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movq	%r14, %r8
	callq	invoke_block_in_jit
	testl	%eax, %eax
	je	.LBB18_1
# BB#11:                                # %entry_ifend44
                                        #   in Loop: Header=BB18_8 Depth=1
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	testb	$1, %bl
	je	.LBB18_12
# BB#15:                                # %entry_condend52
                                        #   in Loop: Header=BB18_8 Depth=1
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r15, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	%r14, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#16:                                # %entry_ifend57
                                        #   in Loop: Header=BB18_8 Depth=1
	movq	(%rax), %rbx
	movl	$8840, %esi             # imm = 0x2288
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#17:                                # %entry_ifend60
                                        #   in Loop: Header=BB18_8 Depth=1
	movq	$0, (%r12)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, (%r12)
	movq	$0, 8(%r12)
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%r12)
	movq	$0, 16(%r12)
	movq	(%rsp), %rdx            # 8-byte Reload
	movq	%rdx, 16(%r12)
	movq	$0, 24(%r12)
	movq	%r13, 24(%r12)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	%r14, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_18
# BB#19:                                # %entry_ifend78
                                        #   in Loop: Header=BB18_8 Depth=1
	movq	(%r15), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r15), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r15), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r15), %r13
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	jmp	.LBB18_13
	.align	16, 0x90
.LBB18_12:                              #   in Loop: Header=BB18_8 Depth=1
	movq	%r14, %rbx
.LBB18_13:                              # %label_if_endzzzzzzzzzzx
                                        #   in Loop: Header=BB18_8 Depth=1
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%r15, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB18_14
	jmp	.LBB18_1
.LBB18_20:                              # %label_whilezzzzzzzzzzw
	movq	(%rsp), %rax            # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%r15)
	movl	$1, %eax
	jmp	.LBB18_2
.LBB18_18:                              # %then_block77
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB18_1:                               # %then_block
	xorl	%eax, %eax
.LBB18_2:                               # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end18:
	.size	"SortableList.select(lambda)$$20", .Lfunc_end18-"SortableList.select(lambda)$$20"
	.cfi_endproc

	.globl	"SortableList.clone()$$21"
	.align	16, 0x90
	.type	"SortableList.clone()$$21",@function
"SortableList.clone()$$21":             # @"SortableList.clone()$$21"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp235:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp236:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp237:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp238:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp239:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp240:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp241:
	.cfi_def_cfa_offset 112
.Ltmp242:
	.cfi_offset %rbx, -56
.Ltmp243:
	.cfi_offset %r12, -48
.Ltmp244:
	.cfi_offset %r13, -40
.Ltmp245:
	.cfi_offset %r14, -32
.Ltmp246:
	.cfi_offset %r15, -24
.Ltmp247:
	.cfi_offset %rbp, -16
	movl	%r9d, 12(%rsp)          # 4-byte Spill
	movq	%r8, %r13
	movq	%rcx, %r12
	movq	%rdx, %r15
	movq	%rsi, %rbp
	movq	112(%rsp), %rdi
	movq	(%r12), %rbx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$8960, %esi             # imm = 0x2300
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB19_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movl	$8976, %esi             # imm = 0x2310
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB19_1
# BB#4:                                 # %entry_ifend2
	movq	%rbp, (%rsp)            # 8-byte Spill
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	$0, 8(%rbp)
	movq	$0, 16(%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	12(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r13, %r8
	movq	%r15, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB19_6
# BB#5:                                 # %then_block11
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB19_1
.LBB19_6:                               # %entry_ifend12
	movq	(%r12), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 40(%rsp)
	movq	%r15, 40(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%r12, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movq	%rbx, 16(%rsp)          # 8-byte Spill
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB19_1
# BB#7:                                 # %entry_ifend23
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movl	%eax, %r14d
	movq	%r14, 48(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB19_8
	.align	16, 0x90
.LBB19_14:                              # %entry_ifend64
                                        #   in Loop: Header=BB19_8 Depth=1
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movl	%eax, %r14d
	movq	%r14, 48(%rsp)
.LBB19_8:                               # %while_start_pointzzzzzzzzzzy
                                        # =>This Inner Loop Header: Depth=1
	testl	%r14d, %r14d
	movl	$0, gSigInt(%rip)
	je	.LBB19_15
# BB#9:                                 # %entry_condend
                                        #   in Loop: Header=BB19_8 Depth=1
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%r12, %rsi
	movl	%ebp, %edx
	movq	16(%rsp), %rcx          # 8-byte Reload
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB19_1
# BB#10:                                # %entry_ifend29
                                        #   in Loop: Header=BB19_8 Depth=1
	movq	(%rax), %rbx
	movl	$9048, %esi             # imm = 0x2358
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB19_1
# BB#11:                                # %entry_ifend32
                                        #   in Loop: Header=BB19_8 Depth=1
	movq	(%rsp), %rcx            # 8-byte Reload
	movq	$0, (%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r15, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r14, 16(%rcx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebp, %ecx
	movq	%r13, %r8
	movq	%r12, %rbx
	movq	16(%rsp), %r12          # 8-byte Reload
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB19_12
# BB#13:                                # %entry_ifend48
                                        #   in Loop: Header=BB19_8 Depth=1
	movq	(%rbx), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbx), %r15
	movq	$0, 40(%rsp)
	movq	%r15, 40(%rsp)
	movq	16(%rbx), %r14
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%rbx, %r12
	jne	.LBB19_14
	jmp	.LBB19_1
.LBB19_15:                              # %label_whilezzzzzzzzzzy
	movl	%r15d, %eax
	movq	%rax, (%r12)
	movl	$1, %eax
	jmp	.LBB19_2
.LBB19_12:                              # %then_block47
	movq	%r12, %rdi
	callq	get_try_catch_label_name
.LBB19_1:                               # %then_block
	xorl	%eax, %eax
.LBB19_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end19:
	.size	"SortableList.clone()$$21", .Lfunc_end19-"SortableList.clone()$$21"
	.cfi_endproc

	.globl	"SortableList.subList(int,int)$$22"
	.align	16, 0x90
	.type	"SortableList.subList(int,int)$$22",@function
"SortableList.subList(int,int)$$22":    # @"SortableList.subList(int,int)$$22"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp248:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp249:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp250:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp251:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp252:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp253:
	.cfi_def_cfa_offset 56
	subq	$136, %rsp
.Ltmp254:
	.cfi_def_cfa_offset 192
.Ltmp255:
	.cfi_offset %rbx, -56
.Ltmp256:
	.cfi_offset %r12, -48
.Ltmp257:
	.cfi_offset %r13, -40
.Ltmp258:
	.cfi_offset %r14, -32
.Ltmp259:
	.cfi_offset %r15, -24
.Ltmp260:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebp
	movq	%r8, %rdi
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	%rsi, 48(%rsp)          # 8-byte Spill
	movq	(%rbx), %r13
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 72(%rsp)
	movq	%r12, 72(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%r12d, %r12d
	jns	.LBB20_5
# BB#1:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rdi, %r14
	movq	%rbx, %rsi
	movq	%rbx, %r15
	movl	%ebp, %edx
	movl	%ebp, %ebx
	movq	%rcx, %rbp
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_2
# BB#4:                                 # %entry_ifend
	movq	(%rax), %rax
	addl	%eax, %r12d
	movq	$0, 72(%rsp)
	movq	%r12, 72(%rsp)
	movq	%rbp, %rcx
	movl	%ebx, %ebp
	movq	%r14, %rdi
	movq	%r15, %rbx
.LBB20_5:                               # %label_if_endzzzzzzzzzzz
	movl	$0, gSigInt(%rip)
	movq	80(%rsp), %r15
	testl	%r15d, %r15d
	jns	.LBB20_8
# BB#6:                                 # %entry_condend11
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rdi, 56(%rsp)          # 8-byte Spill
	movq	%rbx, %rsi
	movq	%rbx, %r14
	movl	%ebp, %edx
	movl	%ebp, %ebx
	movq	%rcx, %rbp
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_2
# BB#7:                                 # %entry_ifend16
	movq	(%rax), %rax
	leal	1(%r15,%rax), %r15d
	movq	$0, 80(%rsp)
	movq	%r15, 80(%rsp)
	movq	%rbp, %rcx
	movl	%ebx, %ebp
	movq	56(%rsp), %rdi          # 8-byte Reload
	movq	%r14, %rbx
.LBB20_8:                               # %label_if_endzzzzzzzzzzzb
	movl	$0, gSigInt(%rip)
	testl	%r12d, %r12d
	jns	.LBB20_10
# BB#9:                                 # %entry_condend24
	movl	$0, gSigInt(%rip)
	movq	$0, 72(%rsp)
	xorl	%r12d, %r12d
.LBB20_10:                              # %label_if_endzzzzzzzzzzzc
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rdi, %r14
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movl	%ebp, 56(%rsp)          # 4-byte Spill
	movq	%rcx, %rbp
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_2
# BB#11:                                # %entry_ifend30
	movq	(%rax), %rax
	cmpl	%eax, %r15d
	jle	.LBB20_14
# BB#12:                                # %entry_condend33
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_2
# BB#13:                                # %entry_ifend37
	movq	(%rax), %rax
	movq	$0, 80(%rsp)
	movl	%eax, %r15d
	movq	%r15, 80(%rsp)
.LBB20_14:                              # %label_if_endzzzzzzzzzzzd
	movl	$0, gSigInt(%rip)
	cmpl	%r15d, %r12d
	setge	%al
	movq	$0, 112(%rsp)
	movzbl	%al, %eax
	movq	%rax, 112(%rsp)
	movq	%r14, %rdi
	movq	%rbx, %rsi
	jge	.LBB20_19
# BB#15:                                # %entry_condnotend
	movl	$2, %r9d
	movq	%rdi, %rbx
	movq	%rsi, %r14
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_2
# BB#16:                                # %entry_ifend46
	movq	(%rax), %rax
	cmpl	%eax, %r12d
	setge	%al
	movq	$0, 120(%rsp)
	movzbl	%al, %eax
	movq	%rax, 120(%rsp)
	jge	.LBB20_18
# BB#17:                                # %entry_condnotend51
	testl	%r15d, %r15d
	sets	%al
	movzbl	%al, %eax
	movq	%rax, 120(%rsp)
.LBB20_18:                              # %label_or_endpointzzzzzzzzzzzg
	movq	%rax, 112(%rsp)
	movq	%rbx, %rdi
	movq	%r14, %rsi
.LBB20_19:                              # %label_or_endpointzzzzzzzzzzzf
	movq	192(%rsp), %rcx
	movl	$0, gSigInt(%rip)
	testq	%rax, %rax
	je	.LBB20_25
# BB#20:                                # %entry_condend58
	movq	%rsi, 40(%rsp)          # 8-byte Spill
	movq	%rdi, %rbx
	movq	%rbp, 32(%rsp)          # 8-byte Spill
	movl	$9600, %esi             # imm = 0x2580
	movq	%rcx, %rdi
	movq	%rcx, %r14
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_2
# BB#21:                                # %entry_ifend61
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$9616, %esi             # imm = 0x2590
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_2
# BB#22:                                # %entry_ifend64
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r15, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	$0, 32(%rcx)
	movq	$0, 40(%rcx)
	movq	%rbx, %r14
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	56(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB20_24
# BB#23:                                # %then_block79
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB20_2
.LBB20_25:                              # %label_if_endzzzzzzzzzzze
	movq	%rsi, 40(%rsp)          # 8-byte Spill
	movq	%rdi, %rbx
	movl	$9688, %esi             # imm = 0x25D8
	movq	%rcx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_2
# BB#26:                                # %entry_ifend98
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movl	$9704, %esi             # imm = 0x25E8
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_2
# BB#27:                                # %entry_ifend101
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r15, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	$0, 32(%rcx)
	movq	$0, 40(%rcx)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbx)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %r14          # 8-byte Reload
	movq	%r14, %rdx
	movl	56(%rsp), %r12d         # 4-byte Reload
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%rbp, %r15
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB20_29
# BB#28:                                # %then_block119
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB20_2
.LBB20_24:                              # %entry_ifend80
	movq	(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%rbx)
	movl	$1, %eax
	jmp	.LBB20_3
.LBB20_29:                              # %entry_ifend120
	movq	(%r14), %r13
	movq	%r13, (%rsp)            # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movq	8(%r14), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r14), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movq	%rbp, 8(%rsp)           # 8-byte Spill
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 88(%rsp)
	movq	%rbp, 88(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	movl	%r12d, %r14d
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_2
# BB#30:                                # %entry_ifend142
	movq	(%rax), %rax
	movq	$0, 96(%rsp)
	movl	%eax, %r8d
	movq	%r8, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 104(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r12d, %r12d
	movq	%r15, %rcx
	movq	%rcx, 32(%rsp)          # 8-byte Spill
	movl	%r14d, %ebp
	movq	%rbx, %r14
	movq	40(%rsp), %r13          # 8-byte Reload
	jmp	.LBB20_31
.LBB20_43:                              # %entry_ifend215
                                        #   in Loop: Header=BB20_31 Depth=1
	movq	(%rax), %rax
	movq	$0, 96(%rsp)
	movl	%eax, %r8d
	movq	%r8, 96(%rsp)
	movq	%rbp, %rcx
	movl	%ebx, %ebp
	movq	%r15, %r14
.LBB20_31:                              # %while_start_pointzzzzzzzzzzzh
                                        # =>This Inner Loop Header: Depth=1
	testl	%r8d, %r8d
	movl	$0, gSigInt(%rip)
	je	.LBB20_39
# BB#32:                                # %entry_condend146
                                        #   in Loop: Header=BB20_31 Depth=1
	movq	24(%rsp), %rax          # 8-byte Reload
	cmpl	%eax, %r12d
	setge	%al
	movq	$0, 128(%rsp)
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
	jl	.LBB20_34
# BB#33:                                # %entry_condend153
                                        #   in Loop: Header=BB20_31 Depth=1
	movq	16(%rsp), %rax          # 8-byte Reload
	cmpl	%eax, %r12d
	setl	%al
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
.LBB20_34:                              # %label_and_endpointzzzzzzzzzzzj
                                        #   in Loop: Header=BB20_31 Depth=1
	testq	%rax, %rax
	je	.LBB20_42
# BB#35:                                # %entry_condend160
                                        #   in Loop: Header=BB20_31 Depth=1
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r13, %rsi
	movl	%ebp, %edx
	movq	%r8, %rbx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_2
# BB#36:                                # %entry_ifend165
                                        #   in Loop: Header=BB20_31 Depth=1
	movq	(%rax), %r15
	movl	$9868, %esi             # imm = 0x268C
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_2
# BB#37:                                # %entry_ifend168
                                        #   in Loop: Header=BB20_31 Depth=1
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movq	%rdx, 24(%rcx)
	movq	$0, 32(%rcx)
	movq	%rbx, 32(%rcx)
	movq	$0, 40(%rcx)
	movq	%r12, 40(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %r13          # 8-byte Reload
	movq	%r13, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	32(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_38
# BB#41:                                # %entry_ifend190
                                        #   in Loop: Header=BB20_31 Depth=1
	movq	(%r13), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r13), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r13), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r13), %r15
	movq	$0, 96(%rsp)
	movq	%r15, 96(%rsp)
	movq	40(%r13), %r12
	movq	$0, 104(%rsp)
	movq	%r12, 104(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	movq	%r15, %r8
	addq	$-8, (%r14)
	movq	32(%rsp), %rcx          # 8-byte Reload
.LBB20_42:                              # %label_if_endzzzzzzzzzzzi
                                        #   in Loop: Header=BB20_31 Depth=1
	movl	$0, gSigInt(%rip)
	incl	%r12d
	movq	$0, 104(%rsp)
	movq	%r12, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%r14, %r15
	movq	%r13, %rsi
	movl	%ebp, %edx
	movl	%ebp, %ebx
	movq	%rcx, %rbp
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB20_43
	jmp	.LBB20_2
.LBB20_39:                              # %label_whilezzzzzzzzzzzh
	movq	8(%rsp), %rax           # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB20_3
.LBB20_38:                              # %then_block189
	movq	32(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
.LBB20_2:                               # %then_block
	xorl	%eax, %eax
.LBB20_3:                               # %then_block
	addq	$136, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end20:
	.size	"SortableList.subList(int,int)$$22", .Lfunc_end20-"SortableList.subList(int,int)$$22"
	.cfi_endproc

	.globl	"SortableList.deleteWithRange(int,int)$$23"
	.align	16, 0x90
	.type	"SortableList.deleteWithRange(int,int)$$23",@function
"SortableList.deleteWithRange(int,int)$$23": # @"SortableList.deleteWithRange(int,int)$$23"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp261:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp262:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp263:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp264:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp265:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp266:
	.cfi_def_cfa_offset 56
	subq	$136, %rsp
.Ltmp267:
	.cfi_def_cfa_offset 192
.Ltmp268:
	.cfi_offset %rbx, -56
.Ltmp269:
	.cfi_offset %r12, -48
.Ltmp270:
	.cfi_offset %r13, -40
.Ltmp271:
	.cfi_offset %r14, -32
.Ltmp272:
	.cfi_offset %r15, -24
.Ltmp273:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebp
	movq	%r8, %rdi
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	%rsi, 48(%rsp)          # 8-byte Spill
	movq	(%rbx), %r13
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 72(%rsp)
	movq	%r12, 72(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%r12d, %r12d
	jns	.LBB21_5
# BB#1:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rdi, %r14
	movq	%rbx, %rsi
	movq	%rbx, %r15
	movl	%ebp, %edx
	movl	%ebp, %ebx
	movq	%rcx, %rbp
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB21_2
# BB#4:                                 # %entry_ifend
	movq	(%rax), %rax
	addl	%eax, %r12d
	movq	$0, 72(%rsp)
	movq	%r12, 72(%rsp)
	movq	%rbp, %rcx
	movl	%ebx, %ebp
	movq	%r14, %rdi
	movq	%r15, %rbx
.LBB21_5:                               # %label_if_endzzzzzzzzzzzk
	movl	$0, gSigInt(%rip)
	movq	80(%rsp), %r15
	testl	%r15d, %r15d
	jns	.LBB21_8
# BB#6:                                 # %entry_condend11
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rdi, 56(%rsp)          # 8-byte Spill
	movq	%rbx, %rsi
	movq	%rbx, %r14
	movl	%ebp, %edx
	movl	%ebp, %ebx
	movq	%rcx, %rbp
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB21_2
# BB#7:                                 # %entry_ifend16
	movq	(%rax), %rax
	leal	1(%r15,%rax), %r15d
	movq	$0, 80(%rsp)
	movq	%r15, 80(%rsp)
	movq	%rbp, %rcx
	movl	%ebx, %ebp
	movq	56(%rsp), %rdi          # 8-byte Reload
	movq	%r14, %rbx
.LBB21_8:                               # %label_if_endzzzzzzzzzzzl
	movl	$0, gSigInt(%rip)
	testl	%r12d, %r12d
	jns	.LBB21_10
# BB#9:                                 # %entry_condend24
	movl	$0, gSigInt(%rip)
	movq	$0, 72(%rsp)
	xorl	%r12d, %r12d
.LBB21_10:                              # %label_if_endzzzzzzzzzzzm
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rdi, %r14
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movl	%ebp, 56(%rsp)          # 4-byte Spill
	movq	%rcx, %rbp
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB21_2
# BB#11:                                # %entry_ifend30
	movq	(%rax), %rax
	cmpl	%eax, %r15d
	jle	.LBB21_14
# BB#12:                                # %entry_condend33
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB21_2
# BB#13:                                # %entry_ifend37
	movq	(%rax), %rax
	movq	$0, 80(%rsp)
	movl	%eax, %r15d
	movq	%r15, 80(%rsp)
.LBB21_14:                              # %label_if_endzzzzzzzzzzzn
	movl	$0, gSigInt(%rip)
	cmpl	%r15d, %r12d
	setge	%al
	movq	$0, 112(%rsp)
	movzbl	%al, %eax
	movq	%rax, 112(%rsp)
	movq	%r14, %rdi
	movq	%rbx, %rsi
	jge	.LBB21_19
# BB#15:                                # %entry_condnotend
	movl	$2, %r9d
	movq	%rdi, %rbx
	movq	%rsi, %r14
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB21_2
# BB#16:                                # %entry_ifend46
	movq	(%rax), %rax
	cmpl	%eax, %r12d
	setge	%al
	movq	$0, 120(%rsp)
	movzbl	%al, %eax
	movq	%rax, 120(%rsp)
	jge	.LBB21_18
# BB#17:                                # %entry_condnotend51
	testl	%r15d, %r15d
	sets	%al
	movzbl	%al, %eax
	movq	%rax, 120(%rsp)
.LBB21_18:                              # %label_or_endpointzzzzzzzzzzzq
	movq	%rax, 112(%rsp)
	movq	%rbx, %rdi
	movq	%r14, %rsi
.LBB21_19:                              # %label_or_endpointzzzzzzzzzzzp
	movq	192(%rsp), %rcx
	movl	$0, gSigInt(%rip)
	testq	%rax, %rax
	je	.LBB21_25
# BB#20:                                # %entry_condend58
	movq	%rsi, 40(%rsp)          # 8-byte Spill
	movq	%rdi, %rbx
	movq	%rbp, 32(%rsp)          # 8-byte Spill
	movl	$10488, %esi            # imm = 0x28F8
	movq	%rcx, %rdi
	movq	%rcx, %r14
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB21_2
# BB#21:                                # %entry_ifend61
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$10504, %esi            # imm = 0x2908
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB21_2
# BB#22:                                # %entry_ifend64
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r15, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	$0, 32(%rcx)
	movq	$0, 40(%rcx)
	movq	%rbx, %r14
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	56(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB21_24
# BB#23:                                # %then_block79
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB21_2
.LBB21_25:                              # %label_if_endzzzzzzzzzzzo
	movq	%rsi, 40(%rsp)          # 8-byte Spill
	movq	%rdi, %rbx
	movl	$10576, %esi            # imm = 0x2950
	movq	%rcx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB21_2
# BB#26:                                # %entry_ifend98
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movl	$10592, %esi            # imm = 0x2960
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB21_2
# BB#27:                                # %entry_ifend101
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r15, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	$0, 32(%rcx)
	movq	$0, 40(%rcx)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbx)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %r14          # 8-byte Reload
	movq	%r14, %rdx
	movl	56(%rsp), %r12d         # 4-byte Reload
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%rbp, %r15
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB21_29
# BB#28:                                # %then_block119
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB21_2
.LBB21_24:                              # %entry_ifend80
	movq	(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%rbx)
	movl	$1, %eax
	jmp	.LBB21_3
.LBB21_29:                              # %entry_ifend120
	movq	(%r14), %r13
	movq	%r13, (%rsp)            # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movq	8(%r14), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r14), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movq	%rbp, 8(%rsp)           # 8-byte Spill
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 88(%rsp)
	movq	%rbp, 88(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	movl	%r12d, %r14d
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB21_2
# BB#30:                                # %entry_ifend142
	movq	(%rax), %rax
	movq	$0, 96(%rsp)
	movl	%eax, %r8d
	movq	%r8, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 104(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r12d, %r12d
	movq	%r15, %rcx
	movq	%rcx, 32(%rsp)          # 8-byte Spill
	movl	%r14d, %ebp
	movq	%rbx, %r14
	movq	40(%rsp), %r13          # 8-byte Reload
	jmp	.LBB21_31
.LBB21_43:                              # %entry_ifend216
                                        #   in Loop: Header=BB21_31 Depth=1
	movq	(%rax), %rax
	movq	$0, 96(%rsp)
	movl	%eax, %r8d
	movq	%r8, 96(%rsp)
	movq	%rbp, %rcx
	movl	%ebx, %ebp
	movq	%r15, %r14
.LBB21_31:                              # %while_start_pointzzzzzzzzzzzr
                                        # =>This Inner Loop Header: Depth=1
	testl	%r8d, %r8d
	movl	$0, gSigInt(%rip)
	je	.LBB21_39
# BB#32:                                # %entry_condend146
                                        #   in Loop: Header=BB21_31 Depth=1
	movq	24(%rsp), %rax          # 8-byte Reload
	cmpl	%eax, %r12d
	setl	%al
	movq	$0, 128(%rsp)
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
	jl	.LBB21_34
# BB#33:                                # %entry_condnotend153
                                        #   in Loop: Header=BB21_31 Depth=1
	movq	16(%rsp), %rax          # 8-byte Reload
	cmpl	%eax, %r12d
	setge	%al
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
.LBB21_34:                              # %label_or_endpointzzzzzzzzzzzt
                                        #   in Loop: Header=BB21_31 Depth=1
	testq	%rax, %rax
	je	.LBB21_42
# BB#35:                                # %entry_condend161
                                        #   in Loop: Header=BB21_31 Depth=1
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r13, %rsi
	movl	%ebp, %edx
	movq	%r8, %rbx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB21_2
# BB#36:                                # %entry_ifend166
                                        #   in Loop: Header=BB21_31 Depth=1
	movq	(%rax), %r15
	movl	$10756, %esi            # imm = 0x2A04
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB21_2
# BB#37:                                # %entry_ifend169
                                        #   in Loop: Header=BB21_31 Depth=1
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movq	%rdx, 24(%rcx)
	movq	$0, 32(%rcx)
	movq	%rbx, 32(%rcx)
	movq	$0, 40(%rcx)
	movq	%r12, 40(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %r13          # 8-byte Reload
	movq	%r13, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	32(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB21_38
# BB#41:                                # %entry_ifend191
                                        #   in Loop: Header=BB21_31 Depth=1
	movq	(%r13), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r13), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r13), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r13), %r15
	movq	$0, 96(%rsp)
	movq	%r15, 96(%rsp)
	movq	40(%r13), %r12
	movq	$0, 104(%rsp)
	movq	%r12, 104(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	movq	%r15, %r8
	addq	$-8, (%r14)
	movq	32(%rsp), %rcx          # 8-byte Reload
.LBB21_42:                              # %label_if_endzzzzzzzzzzzs
                                        #   in Loop: Header=BB21_31 Depth=1
	movl	$0, gSigInt(%rip)
	incl	%r12d
	movq	$0, 104(%rsp)
	movq	%r12, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%r14, %r15
	movq	%r13, %rsi
	movl	%ebp, %edx
	movl	%ebp, %ebx
	movq	%rcx, %rbp
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB21_43
	jmp	.LBB21_2
.LBB21_39:                              # %label_whilezzzzzzzzzzzr
	movq	8(%rsp), %rax           # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB21_3
.LBB21_38:                              # %then_block190
	movq	32(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
.LBB21_2:                               # %then_block
	xorl	%eax, %eax
.LBB21_3:                               # %then_block
	addq	$136, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end21:
	.size	"SortableList.deleteWithRange(int,int)$$23", .Lfunc_end21-"SortableList.deleteWithRange(int,int)$$23"
	.cfi_endproc

	.globl	"SortableList.fill(int,int,GenericsParametorClass0)$$24"
	.align	16, 0x90
	.type	"SortableList.fill(int,int,GenericsParametorClass0)$$24",@function
"SortableList.fill(int,int,GenericsParametorClass0)$$24": # @"SortableList.fill(int,int,GenericsParametorClass0)$$24"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp274:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp275:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp276:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp277:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp278:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp279:
	.cfi_def_cfa_offset 56
	subq	$136, %rsp
.Ltmp280:
	.cfi_def_cfa_offset 192
.Ltmp281:
	.cfi_offset %rbx, -56
.Ltmp282:
	.cfi_offset %r12, -48
.Ltmp283:
	.cfi_offset %r13, -40
.Ltmp284:
	.cfi_offset %r14, -32
.Ltmp285:
	.cfi_offset %r15, -24
.Ltmp286:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebx
	movq	%r8, %rdi
	movq	%rcx, %r15
	movq	%rdx, %rcx
	movq	%rsi, 40(%rsp)          # 8-byte Spill
	movq	(%r15), %r13
	movq	$0, 56(%rsp)
	movq	%r13, 56(%rsp)
	movq	8(%r15), %rbp
	movq	$0, 64(%rsp)
	movq	%rbp, 64(%rsp)
	movq	16(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%r15), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%ebp, %ebp
	jns	.LBB22_5
# BB#1:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rdi, %r14
	movq	%r15, %rsi
	movl	%ebx, %edx
	movl	%ebx, %r12d
	movq	%rcx, %rbx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_2
# BB#4:                                 # %entry_ifend
	movq	(%rax), %rax
	addl	%ebp, %eax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%r14, %rdi
	movq	%rbx, %rcx
	movl	%r12d, %ebx
.LBB22_5:                               # %label_if_endzzzzzzzzzzzu
	movl	$0, gSigInt(%rip)
	movq	72(%rsp), %r12
	testl	%r12d, %r12d
	jns	.LBB22_8
# BB#6:                                 # %entry_condend13
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rdi, %rbp
	movq	%r15, %rsi
	movl	%ebx, %edx
	movl	%ebx, %r14d
	movq	%rcx, %rbx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_2
# BB#7:                                 # %entry_ifend18
	movq	(%rax), %rax
	leal	1(%r12,%rax), %r12d
	movq	$0, 72(%rsp)
	movq	%r12, 72(%rsp)
	movq	%rbp, %rdi
	movq	%rbx, %rcx
	movl	%r14d, %ebx
.LBB22_8:                               # %label_if_endzzzzzzzzzzzv
	movl	$0, gSigInt(%rip)
	cmpl	$0, 64(%rsp)
	jns	.LBB22_10
# BB#9:                                 # %entry_condend26
	movl	$0, gSigInt(%rip)
	movq	$0, 64(%rsp)
.LBB22_10:                              # %label_if_endzzzzzzzzzzzw
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rdi, %r14
	movq	%r15, %rsi
	movl	%ebx, %edx
	movl	%ebx, 52(%rsp)          # 4-byte Spill
	movq	%rcx, %rbx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_2
# BB#11:                                # %entry_ifend32
	movq	(%rax), %rax
	cmpl	%eax, %r12d
	jle	.LBB22_14
# BB#12:                                # %entry_condend35
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_2
# BB#13:                                # %entry_ifend39
	movq	(%rax), %rax
	movq	$0, 72(%rsp)
	movl	%eax, %eax
	movq	%rax, 72(%rsp)
.LBB22_14:                              # %label_if_endzzzzzzzzzzzx
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %ebp
	cmpl	72(%rsp), %ebp
	setge	%al
	movq	$0, 112(%rsp)
	movzbl	%al, %eax
	movq	%rax, 112(%rsp)
	jge	.LBB22_19
# BB#15:                                # %entry_condnotend
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_2
# BB#16:                                # %entry_ifend48
	movq	(%rax), %rax
	cmpl	%eax, %ebp
	setge	%al
	movq	$0, 120(%rsp)
	movzbl	%al, %eax
	movq	%rax, 120(%rsp)
	jge	.LBB22_18
# BB#17:                                # %entry_condnotend53
	cmpl	$0, 72(%rsp)
	sets	%al
	movzbl	%al, %eax
	movq	%rax, 120(%rsp)
.LBB22_18:                              # %label_or_endpointzzzzzzzzzzzzb
	movq	%rax, 112(%rsp)
.LBB22_19:                              # %label_or_endpointzzzzzzzzzzzz
	movq	192(%rsp), %rcx
	movl	$0, gSigInt(%rip)
	testq	%rax, %rax
	je	.LBB22_25
# BB#20:                                # %entry_condend60
	movq	%r14, %r12
	movl	$11376, %esi            # imm = 0x2C70
	movq	%rcx, %rdi
	movq	%rcx, %r14
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_2
# BB#21:                                # %entry_ifend63
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$11392, %esi            # imm = 0x2C80
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_2
# BB#22:                                # %entry_ifend66
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%r13, (%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	$0, 24(%rdx)
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 24(%rdx)
	movq	$0, 32(%rdx)
	movq	$0, 40(%rdx)
	movq	$0, 48(%rdx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB22_24
# BB#23:                                # %then_block83
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB22_2
.LBB22_25:                              # %label_if_endzzzzzzzzzzzy
	movl	$11464, %esi            # imm = 0x2CC8
	movq	%rcx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_2
# BB#26:                                # %entry_ifend104
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$11480, %esi            # imm = 0x2CD8
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_2
# BB#27:                                # %entry_ifend107
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%r13, (%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	$0, 24(%rdx)
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 24(%rdx)
	movq	$0, 32(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	%r14, %r12
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	52(%rsp), %r14d         # 4-byte Reload
	movl	%r14d, %ecx
	movq	%r12, %r8
	movq	%rbx, %r13
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB22_29
# BB#28:                                # %then_block127
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB22_2
.LBB22_24:                              # %entry_ifend84
	movq	(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	32(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	40(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	48(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	%r14, (%r15)
	movl	$1, %eax
	jmp	.LBB22_3
.LBB22_29:                              # %entry_ifend128
	movq	(%r15), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%r15), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	32(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	40(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	48(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %rbx
	movq	%rbx, 16(%rsp)          # 8-byte Spill
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 88(%rsp)
	movq	%rbx, 88(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movq	%r13, 24(%rsp)          # 8-byte Spill
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_2
# BB#30:                                # %entry_ifend152
	movq	(%rax), %rax
	movq	$0, 96(%rsp)
	movl	%eax, %r13d
	movq	%r13, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 104(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB22_31
.LBB22_43:                              # %entry_ifend280
                                        #   in Loop: Header=BB22_31 Depth=1
	movq	(%rax), %rax
	movq	$0, 96(%rsp)
	movl	%eax, %r13d
	movq	%r13, 96(%rsp)
.LBB22_31:                              # %while_start_pointzzzzzzzzzzzzc
                                        # =>This Inner Loop Header: Depth=1
	testl	%r13d, %r13d
	movl	$0, gSigInt(%rip)
	je	.LBB22_40
# BB#32:                                # %entry_condend156
                                        #   in Loop: Header=BB22_31 Depth=1
	movq	104(%rsp), %rbx
	cmpl	64(%rsp), %ebx
	setl	%al
	movq	$0, 128(%rsp)
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
	jl	.LBB22_34
# BB#33:                                # %entry_condnotend163
                                        #   in Loop: Header=BB22_31 Depth=1
	cmpl	72(%rsp), %ebx
	setge	%al
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
.LBB22_34:                              # %label_or_endpointzzzzzzzzzzzze
                                        #   in Loop: Header=BB22_31 Depth=1
	movl	$0, gSigInt(%rip)
	testq	%rax, %rax
	je	.LBB22_44
# BB#35:                                # %entry_condend171
                                        #   in Loop: Header=BB22_31 Depth=1
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%r14d, %edx
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_2
# BB#36:                                # %entry_ifend176
                                        #   in Loop: Header=BB22_31 Depth=1
	movq	(%rax), %rbp
	movl	$11644, %esi            # imm = 0x2D7C
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_2
# BB#37:                                # %entry_ifend179
                                        #   in Loop: Header=BB22_31 Depth=1
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	$0, 24(%rdx)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, 24(%rdx)
	movq	$0, 32(%rdx)
	movq	16(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 32(%rdx)
	movq	$0, 40(%rdx)
	movq	%r13, 40(%rdx)
	movq	$0, 48(%rdx)
	movq	%rbx, 48(%rdx)
	movq	%r12, %rbx
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%esi, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	jmp	.LBB22_38
.LBB22_44:                              # %label_elsezzzzzzzzzzzzd
                                        #   in Loop: Header=BB22_31 Depth=1
	movl	$11712, %esi            # imm = 0x2DC0
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_2
# BB#45:                                # %entry_ifend229
                                        #   in Loop: Header=BB22_31 Depth=1
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	$0, 24(%rdx)
	movq	8(%rsp), %rsi           # 8-byte Reload
	movq	%rsi, 24(%rdx)
	movq	$0, 32(%rdx)
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%rdi, 32(%rdx)
	movq	$0, 40(%rdx)
	movq	%r13, 40(%rdx)
	movq	$0, 48(%rdx)
	movq	%rbx, 48(%rdx)
	movq	%r12, %rbx
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%edi, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
.LBB22_38:                              # %entry_ifend179
                                        #   in Loop: Header=BB22_31 Depth=1
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r14d, %ecx
	movq	%rbx, %r8
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB22_39
# BB#42:                                # %entry_ifend203
                                        #   in Loop: Header=BB22_31 Depth=1
	movq	(%r15), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%r15), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	32(%r15), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	40(%r15), %r13
	movq	$0, 96(%rsp)
	movq	%r13, 96(%rsp)
	movq	48(%r15), %rbp
	movq	$0, 104(%rsp)
	movq	%rbp, 104(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %rdi
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 24(%rsp)          # 8-byte Spill
	movl	$0, gSigInt(%rip)
	incl	%ebp
	movq	$0, 104(%rsp)
	movq	%rbp, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rdi, %r12
	movq	%r15, %rsi
	movl	%r14d, %edx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB22_43
	jmp	.LBB22_2
.LBB22_40:                              # %label_whilezzzzzzzzzzzzc
	movq	16(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%r15)
	movl	$1, %eax
	jmp	.LBB22_3
.LBB22_39:                              # %then_block202
	movq	24(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
.LBB22_2:                               # %then_block
	xorl	%eax, %eax
.LBB22_3:                               # %then_block
	addq	$136, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end22:
	.size	"SortableList.fill(int,int,GenericsParametorClass0)$$24", .Lfunc_end22-"SortableList.fill(int,int,GenericsParametorClass0)$$24"
	.cfi_endproc

	.globl	"SortableList.fill(GenericsParametorClass0)$$25"
	.align	16, 0x90
	.type	"SortableList.fill(GenericsParametorClass0)$$25",@function
"SortableList.fill(GenericsParametorClass0)$$25": # @"SortableList.fill(GenericsParametorClass0)$$25"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp287:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp288:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp289:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp290:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp291:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp292:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp293:
	.cfi_def_cfa_offset 80
.Ltmp294:
	.cfi_offset %rbx, -56
.Ltmp295:
	.cfi_offset %r12, -48
.Ltmp296:
	.cfi_offset %r13, -40
.Ltmp297:
	.cfi_offset %r14, -32
.Ltmp298:
	.cfi_offset %r15, -24
.Ltmp299:
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
	movl	$11844, %esi            # imm = 0x2E44
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
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
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$24, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB23_5
# BB#4:                                 # %then_block18
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB23_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB23_2
.LBB23_5:                               # %entry_ifend19
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
.LBB23_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end23:
	.size	"SortableList.fill(GenericsParametorClass0)$$25", .Lfunc_end23-"SortableList.fill(GenericsParametorClass0)$$25"
	.cfi_endproc

	.globl	"SortableList.reverse()$$26"
	.align	16, 0x90
	.type	"SortableList.reverse()$$26",@function
"SortableList.reverse()$$26":           # @"SortableList.reverse()$$26"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp300:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp301:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp302:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp303:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp304:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp305:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp306:
	.cfi_def_cfa_offset 112
.Ltmp307:
	.cfi_offset %rbx, -56
.Ltmp308:
	.cfi_offset %r12, -48
.Ltmp309:
	.cfi_offset %r13, -40
.Ltmp310:
	.cfi_offset %r14, -32
.Ltmp311:
	.cfi_offset %r15, -24
.Ltmp312:
	.cfi_offset %rbp, -16
	movl	%r9d, 12(%rsp)          # 4-byte Spill
	movq	%r8, %r13
	movq	%rcx, %r12
	movq	%rdx, %r15
	movq	%rsi, %rbp
	movq	112(%rsp), %rdi
	movq	(%r12), %rbx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$11860, %esi            # imm = 0x2E54
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB24_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movl	$11876, %esi            # imm = 0x2E64
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB24_1
# BB#4:                                 # %entry_ifend2
	movq	%rbp, (%rsp)            # 8-byte Spill
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	$0, 8(%rbp)
	movq	$0, 16(%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	12(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r13, %r8
	movq	%r15, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB24_6
# BB#5:                                 # %then_block11
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB24_1
.LBB24_6:                               # %entry_ifend12
	movq	(%r12), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 40(%rsp)
	movq	%r15, 40(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%r12, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movq	%rbx, 16(%rsp)          # 8-byte Spill
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB24_1
# BB#7:                                 # %entry_ifend23
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movl	%eax, %r14d
	movq	%r14, 48(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB24_8
	.align	16, 0x90
.LBB24_14:                              # %entry_ifend64
                                        #   in Loop: Header=BB24_8 Depth=1
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movl	%eax, %r14d
	movq	%r14, 48(%rsp)
.LBB24_8:                               # %while_start_pointzzzzzzzzzzzzf
                                        # =>This Inner Loop Header: Depth=1
	testl	%r14d, %r14d
	movl	$0, gSigInt(%rip)
	je	.LBB24_15
# BB#9:                                 # %entry_condend
                                        #   in Loop: Header=BB24_8 Depth=1
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%r12, %rsi
	movl	%ebp, %edx
	movq	16(%rsp), %rcx          # 8-byte Reload
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB24_1
# BB#10:                                # %entry_ifend29
                                        #   in Loop: Header=BB24_8 Depth=1
	movq	(%rax), %rbx
	movl	$11952, %esi            # imm = 0x2EB0
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB24_1
# BB#11:                                # %entry_ifend32
                                        #   in Loop: Header=BB24_8 Depth=1
	movq	(%rsp), %rcx            # 8-byte Reload
	movq	$0, (%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r15, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r14, 16(%rcx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebp, %ecx
	movq	%r13, %r8
	movq	%r12, %rbx
	movq	16(%rsp), %r12          # 8-byte Reload
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB24_12
# BB#13:                                # %entry_ifend48
                                        #   in Loop: Header=BB24_8 Depth=1
	movq	(%rbx), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbx), %r15
	movq	$0, 40(%rsp)
	movq	%r15, 40(%rsp)
	movq	16(%rbx), %r14
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%rbx, %r12
	jne	.LBB24_14
	jmp	.LBB24_1
.LBB24_15:                              # %label_whilezzzzzzzzzzzzf
	movl	%r15d, %eax
	movq	%rax, (%r12)
	movl	$1, %eax
	jmp	.LBB24_2
.LBB24_12:                              # %then_block47
	movq	%r12, %rdi
	callq	get_try_catch_label_name
.LBB24_1:                               # %then_block
	xorl	%eax, %eax
.LBB24_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end24:
	.size	"SortableList.reverse()$$26", .Lfunc_end24-"SortableList.reverse()$$26"
	.cfi_endproc

	.globl	"SortableList.shuffle()$$27"
	.align	16, 0x90
	.type	"SortableList.shuffle()$$27",@function
"SortableList.shuffle()$$27":           # @"SortableList.shuffle()$$27"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp313:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp314:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp315:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp316:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp317:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp318:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp319:
	.cfi_def_cfa_offset 128
.Ltmp320:
	.cfi_offset %rbx, -56
.Ltmp321:
	.cfi_offset %r12, -48
.Ltmp322:
	.cfi_offset %r13, -40
.Ltmp323:
	.cfi_offset %r14, -32
.Ltmp324:
	.cfi_offset %r15, -24
.Ltmp325:
	.cfi_offset %rbp, -16
	movl	%r9d, %r13d
	movq	%r8, %r12
	movq	%rcx, %r15
	movq	%rdx, %r14
	movq	%rsi, %rbp
	movq	128(%rsp), %rdi
	movq	(%r15), %rbx
	movq	$0, 16(%rsp)
	movq	%rbx, 16(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$12028, %esi            # imm = 0x2EFC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB25_1
# BB#3:                                 # %entry_ifend
	movq	16(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	32(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	40(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	48(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	56(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	64(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	movl	$21, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r13d, 12(%rsp)         # 4-byte Spill
	movl	%r13d, %ecx
	movq	%r12, %r8
	movq	%r14, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB25_4
# BB#5:                                 # %entry_ifend18
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	24(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	32(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	40(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	48(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 24(%rsp)
	movq	%r14, 24(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 32(%rsp)
	xorl	%eax, %eax
	jmp	.LBB25_6
	.align	16, 0x90
.LBB25_27:                              # %entry_ifend315
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	24(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	32(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	40(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	48(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	32(%rsp), %eax
	incl	%eax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
.LBB25_6:                               # %for_start_pointzzzzzzzzzzzzg
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	cmpl	$49, %eax
	jg	.LBB25_28
# BB#7:                                 # %entry_condend
                                        #   in Loop: Header=BB25_6 Depth=1
	movl	$12104, %esi            # imm = 0x2F48
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB25_1
# BB#8:                                 # %entry_ifend37
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	16(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	32(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	40(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	48(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	56(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	64(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movl	$15, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r13d, %r14d
	movl	%r14d, %ecx
	movq	%r12, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB25_4
# BB#9:                                 # %entry_ifend55
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	24(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	32(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	40(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	48(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	16(%rsp), %r8d
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%r14d, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB25_1
# BB#10:                                # %entry_ifend79
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	(%rax), %rcx
	testl	%ecx, %ecx
	je	.LBB25_11
# BB#13:                                # %entry_ifend82
                                        #   in Loop: Header=BB25_6 Depth=1
	movl	%r13d, %eax
	cltd
	idivl	%ecx
	movq	$0, 40(%rsp)
	movq	%rdx, 40(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$12112, %esi            # imm = 0x2F50
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB25_1
# BB#14:                                # %entry_ifend85
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	16(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	32(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	40(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	48(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	56(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	64(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movl	$15, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r14d, %r13d
	movl	%r13d, %ecx
	movq	%r12, %r8
	movq	%rbx, %r14
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB25_15
# BB#16:                                # %entry_ifend103
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	24(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	32(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	40(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	48(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	16(%rsp), %r8d
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%r13d, %edx
	movq	%r14, %rcx
	movq	%r14, %r13
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB25_1
# BB#17:                                # %entry_ifend127
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	(%rax), %rcx
	testl	%ecx, %ecx
	je	.LBB25_18
# BB#19:                                # %entry_ifend130
                                        #   in Loop: Header=BB25_6 Depth=1
	movl	%ebx, %eax
	cltd
	idivl	%ecx
	movq	$0, 48(%rsp)
	movq	%rdx, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	24(%rsp), %ebx
	movl	40(%rsp), %r14d
	movl	$12120, %esi            # imm = 0x2F58
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB25_1
# BB#20:                                # %entry_ifend136
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	16(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	32(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	40(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	48(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	56(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	64(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	%r13, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB25_4
# BB#21:                                # %entry_ifend160
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	%rbx, %r13
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	24(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	32(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	40(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	48(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 56(%rsp)
	movq	%rbx, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movl	24(%rsp), %ebx
	movl	48(%rsp), %r14d
	movl	$12136, %esi            # imm = 0x2F68
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB25_1
# BB#22:                                # %entry_ifend185
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	16(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	32(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	40(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	48(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	56(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	64(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	%r13, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB25_4
# BB#23:                                # %entry_ifend209
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	%rbx, (%rsp)            # 8-byte Spill
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	24(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	32(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	40(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	48(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 64(%rsp)
	movq	%rbx, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	24(%rsp), %r14d
	movl	48(%rsp), %ebx
	movl	56(%rsp), %r13d
	movl	$12152, %esi            # imm = 0x2F78
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB25_1
# BB#24:                                # %entry_ifend235
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	16(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	32(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	40(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	48(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	56(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	64(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$15, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	(%rsp), %r14            # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB25_15
# BB#25:                                # %entry_ifend262
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	(%r15), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r15), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	24(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	32(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	40(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	48(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, gSigInt(%rip)
	movl	24(%rsp), %ebx
	movl	40(%rsp), %r14d
	movl	64(%rsp), %r13d
	movl	$12168, %esi            # imm = 0x2F88
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB25_1
# BB#26:                                # %entry_ifend288
                                        #   in Loop: Header=BB25_6 Depth=1
	movq	16(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	24(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	32(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	40(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	48(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	56(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	64(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$15, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	12(%rsp), %r13d         # 4-byte Reload
	movl	%r13d, %ecx
	movq	%r12, %r8
	movq	(%rsp), %rbx            # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB25_27
.LBB25_4:                               # %then_block17
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB25_1:                               # %then_block
	xorl	%eax, %eax
.LBB25_2:                               # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB25_15:                              # %then_block102
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB25_1
.LBB25_28:                              # %label_for_endzzzzzzzzzzzzg
	movl	24(%rsp), %eax
	movq	%rax, (%r15)
	movl	$1, %eax
	jmp	.LBB25_2
.LBB25_11:                              # %then_block81
	movl	$.Lglobal_string.8, %r8d
	movl	$.Lglobal_string.9, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%r14d, %edx
	movq	%rbx, %rcx
	callq	entry_exception_object_with_class_name2
	jmp	.LBB25_1
.LBB25_18:                              # %then_block129
	movl	$.Lglobal_string.10, %r8d
	movl	$.Lglobal_string.11, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	entry_exception_object_with_class_name2
	jmp	.LBB25_1
.Lfunc_end25:
	.size	"SortableList.shuffle()$$27", .Lfunc_end25-"SortableList.shuffle()$$27"
	.cfi_endproc

	.globl	"SortableList.equals(Self)$$28"
	.align	16, 0x90
	.type	"SortableList.equals(Self)$$28",@function
"SortableList.equals(Self)$$28":        # @"SortableList.equals(Self)$$28"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp326:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp327:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp328:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp329:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp330:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp331:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp332:
	.cfi_def_cfa_offset 128
.Ltmp333:
	.cfi_offset %rbx, -56
.Ltmp334:
	.cfi_offset %r12, -48
.Ltmp335:
	.cfi_offset %r13, -40
.Ltmp336:
	.cfi_offset %r14, -32
.Ltmp337:
	.cfi_offset %r15, -24
.Ltmp338:
	.cfi_offset %rbp, -16
	movl	%r9d, %r14d
	movq	%r8, %r12
	movq	%rcx, %rbx
	movq	%rdx, %rax
	movq	%rsi, 24(%rsp)          # 8-byte Spill
	movq	(%rbx), %r13
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	movq	8(%rbx), %rcx
	movq	%rcx, 32(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rcx, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rax, %rcx
	movq	%rax, %rbp
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %r15
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#4:                                 # %entry_ifend5
	movq	%r12, %rsi
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r15d
	je	.LBB26_7
# BB#5:                                 # %entry_condend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB26_2
.LBB26_7:                               # %label_if_endzzzzzzzzzzzzh
	movq	$0, 64(%rsp)
	xorl	%r12d, %r12d
	movq	%rbp, %rcx
	movq	%rcx, 40(%rsp)          # 8-byte Spill
	movq	%rbx, %rbp
	movl	%r14d, 20(%rsp)         # 4-byte Spill
	movq	%rsi, %r15
	jmp	.LBB26_8
	.align	16, 0x90
.LBB26_20:                              # %label_if_endzzzzzzzzzzzzj
                                        #   in Loop: Header=BB26_8 Depth=1
	incl	%r12d
	movq	$0, 64(%rsp)
	movq	%r12, 64(%rsp)
	movl	%ebx, %r14d
	movq	40(%rsp), %rcx          # 8-byte Reload
.LBB26_8:                               # %for_start_pointzzzzzzzzzzzzi
                                        # =>This Inner Loop Header: Depth=1
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#9:                                 # %entry_ifend11
                                        #   in Loop: Header=BB26_8 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r12d
	jge	.LBB26_21
# BB#10:                                # %entry_condend14
                                        #   in Loop: Header=BB26_8 Depth=1
	movl	$12388, %esi            # imm = 0x3064
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#11:                                # %entry_ifend19
                                        #   in Loop: Header=BB26_8 Depth=1
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r12, 16(%rcx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	%r14d, %ecx
	movq	%r15, %r8
	movq	40(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB26_12
# BB#13:                                # %entry_ifend32
                                        #   in Loop: Header=BB26_8 Depth=1
	movq	(%rbp), %r12
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movq	8(%rbp), %r14
	movq	$0, 56(%rsp)
	movq	%r14, 56(%rsp)
	movq	16(%rbp), %r13
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$12404, %esi            # imm = 0x3074
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#14:                                # %entry_ifend45
                                        #   in Loop: Header=BB26_8 Depth=1
	movq	%rbx, 32(%rsp)          # 8-byte Spill
	movq	%r12, %rcx
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	$0, 8(%r12)
	movq	%r14, 8(%r12)
	movq	$0, 16(%r12)
	movq	%r13, 16(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbp, %r13
	jne	.LBB26_15
# BB#16:                                # %entry_ifend61
                                        #   in Loop: Header=BB26_8 Depth=1
	movq	(%r13), %rbx
	movq	$0, 48(%rsp)
	movq	%rbx, 48(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 56(%rsp)
	movq	%rbp, 56(%rsp)
	movq	16(%r13), %r14
	movq	$0, 64(%rsp)
	movq	%r14, 64(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, (%r12)
	movq	%rbx, (%r12)
	movl	20(%rsp), %ebx          # 4-byte Reload
	movq	$0, 8(%r12)
	movq	%rbp, 8(%r12)
	movq	%r13, %rbp
	movq	$0, 16(%r12)
	movq	%r14, 16(%r12)
	movq	(%r15), %rax
	movq	$0, (%rax)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rax)
	movq	(%r15), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r15)
	movq	$0, 8(%rax)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, 8(%rax)
	addq	$8, (%r15)
	movl	%edx, (%rsp)
	movl	$12420, %edi            # imm = 0x3084
	movq	%rbp, %rsi
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB26_17
# BB#18:                                # %entry_ifend89
                                        #   in Loop: Header=BB26_8 Depth=1
	movq	(%rbp), %r13
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	movq	8(%rbp), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %r12
	movq	$0, 64(%rsp)
	movq	%r12, 64(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	testl	%r14d, %r14d
	jne	.LBB26_20
# BB#19:                                # %entry_condend104
	movl	$0, gSigInt(%rip)
	movq	$0, (%rbp)
	movl	$1, %eax
	jmp	.LBB26_2
.LBB26_21:                              # %label_for_endzzzzzzzzzzzzi
	movq	$1, (%rbp)
	movl	$1, %eax
	jmp	.LBB26_2
.LBB26_12:                              # %then_block31
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB26_1
.LBB26_15:                              # %then_block60
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB26_1
.LBB26_17:                              # %then_block88
	movq	40(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
.LBB26_1:                               # %then_block
	xorl	%eax, %eax
.LBB26_2:                               # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end26:
	.size	"SortableList.equals(Self)$$28", .Lfunc_end26-"SortableList.equals(Self)$$28"
	.cfi_endproc

	.globl	"SortableList.delete(GenericsParametorClass0)$$29"
	.align	16, 0x90
	.type	"SortableList.delete(GenericsParametorClass0)$$29",@function
"SortableList.delete(GenericsParametorClass0)$$29": # @"SortableList.delete(GenericsParametorClass0)$$29"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp339:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp340:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp341:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp342:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp343:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp344:
	.cfi_def_cfa_offset 56
	subq	$104, %rsp
.Ltmp345:
	.cfi_def_cfa_offset 160
.Ltmp346:
	.cfi_offset %rbx, -56
.Ltmp347:
	.cfi_offset %r12, -48
.Ltmp348:
	.cfi_offset %r13, -40
.Ltmp349:
	.cfi_offset %r14, -32
.Ltmp350:
	.cfi_offset %r15, -24
.Ltmp351:
	.cfi_offset %rbp, -16
	movl	%r9d, %r14d
	movl	%r14d, 20(%rsp)         # 4-byte Spill
	movq	%r8, %rbp
	movq	%rcx, 48(%rsp)          # 8-byte Spill
	movq	%rdx, %r12
	movq	%r12, 24(%rsp)          # 8-byte Spill
	movq	%rsi, 32(%rsp)          # 8-byte Spill
	movq	(%rcx), %r8
	movq	$0, 56(%rsp)
	movq	%r8, 56(%rsp)
	movq	8(%rcx), %r13
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%rcx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	$0, 72(%rsp)
	movl	%eax, %ebx
	movq	%rbx, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%r14d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#4:                                 # %entry_ifend5
	movq	(%rax), %rax
	movq	$0, 80(%rsp)
	movl	%eax, %r15d
	movq	%r15, 80(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB27_5
	.align	16, 0x90
.LBB27_54:                              # %entry_ifend223
                                        #   in Loop: Header=BB27_5 Depth=1
	movq	(%rax), %rax
	movq	$0, 72(%rsp)
	movl	%eax, %ebx
	movq	%rbx, 72(%rsp)
.LBB27_5:                               # %while_start_pointzzzzzzzzzzzzk
                                        # =>This Inner Loop Header: Depth=1
	testl	%ebx, %ebx
	je	.LBB27_20
# BB#6:                                 # %entry_condend
                                        #   in Loop: Header=BB27_5 Depth=1
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#7:                                 # %entry_ifend10
                                        #   in Loop: Header=BB27_5 Depth=1
	movq	(%rax), %rax
	movq	56(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	$0, 8(%rdx)
	movq	%r13, 8(%rdx)
	movq	$0, 16(%rdx)
	movq	%rbx, 16(%rdx)
	movq	$0, 24(%rdx)
	movq	%r15, 24(%rdx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	%eax, (%rsp)
	movl	$12640, %edi            # imm = 0x3160
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%r14d, %edx
	movq	%rbp, %rcx
	movq	%r12, %r8
	movq	160(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB27_8
# BB#9:                                 # %entry_ifend26
                                        #   in Loop: Header=BB27_5 Depth=1
	movq	%rbp, %r13
	movq	48(%rsp), %r12          # 8-byte Reload
	movq	(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r12), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%r12), %rbp
	movq	$0, 72(%rsp)
	movq	%rbp, 72(%rsp)
	movq	24(%r12), %rbx
	movq	$0, 80(%rsp)
	movq	%rbx, 80(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	testb	$1, %r14b
	jne	.LBB27_10
# BB#53:                                # %label_if_endzzzzzzzzzzzzl
                                        #   in Loop: Header=BB27_5 Depth=1
	movq	$0, 80(%rsp)
	movq	%rbp, %r8
	movl	%r8d, %r15d
	movq	%r15, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%r12, %rsi
	movl	20(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %edx
	movq	24(%rsp), %r14          # 8-byte Reload
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r14, %r12
	movl	%ebx, %r14d
	movq	%r13, %rbp
	movq	40(%rsp), %r13          # 8-byte Reload
	jne	.LBB27_54
	jmp	.LBB27_1
.LBB27_8:                               # %then_block25
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB27_1
.LBB27_10:                              # %entry_condend39
	movq	%rbp, %r14
	movq	%rbx, 40(%rsp)          # 8-byte Spill
	movl	56(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%r12, %rsi
	movl	20(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %edx
	movq	24(%rsp), %r15          # 8-byte Reload
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#11:                                # %entry_ifend44
	movq	(%rax), %rax
	cmpl	%eax, %r14d
	sete	%al
	movq	$0, 88(%rsp)
	movzbl	%al, %eax
	movq	%rax, 88(%rsp)
	jne	.LBB27_14
# BB#12:                                # %entry_condend48
	movl	56(%rsp), %r8d
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#13:                                # %entry_ifend53
	movq	(%rax), %rax
	cmpl	%eax, %r14d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, 88(%rsp)
.LBB27_14:                              # %label_and_endpointzzzzzzzzzzzzn
	testq	%rax, %rax
	je	.LBB27_21
# BB#15:                                # %entry_condend57
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r8d
	movl	$0, (%rsp)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	store_field
	testl	%eax, %eax
	je	.LBB27_1
# BB#16:                                # %entry_ifend61
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r8d
	movl	$1, (%rsp)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	store_field
	testl	%eax, %eax
	je	.LBB27_1
# BB#17:                                # %entry_ifend65
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r8d
	movl	$2, (%rsp)
	xorl	%r9d, %r9d
.LBB27_18:                              # %entry_ifend65
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	store_field
	testl	%eax, %eax
	je	.LBB27_1
# BB#19:                                # %label_if_endzzzzzzzzzzzzm
	movl	$0, gSigInt(%rip)
.LBB27_20:                              # %label_whilezzzzzzzzzzzzk
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %eax
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	%rax, (%rcx)
	movl	$1, %eax
	jmp	.LBB27_2
.LBB27_21:                              # %label_elifzzzzzzzzzzzzm1a
	movl	56(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#22:                                # %entry_ifend75
	movq	(%rax), %rax
	movq	40(%rsp), %rcx          # 8-byte Reload
	cmpl	%eax, %ecx
	sete	%al
	movq	$0, 96(%rsp)
	movzbl	%al, %eax
	movq	%rax, 96(%rsp)
	jne	.LBB27_25
# BB#23:                                # %entry_condend80
	movl	56(%rsp), %r8d
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#24:                                # %entry_ifend85
	movq	(%rax), %rax
	cmpl	%eax, %r14d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, 96(%rsp)
.LBB27_25:                              # %label_and_endpointzzzzzzzzzzzzo
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r8d
	testq	%rax, %rax
	je	.LBB27_31
# BB#26:                                # %entry_condend91
	movq	40(%rsp), %rax          # 8-byte Reload
	movl	%eax, %ebp
	movl	$0, (%rsp)
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	%rbp, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB27_1
# BB#27:                                # %entry_ifend96
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r8d
	movl	$1, (%rsp)
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	%rbp, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB27_1
# BB#28:                                # %entry_ifend101
	movl	$0, gSigInt(%rip)
	movl	$2, (%rsp)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB27_1
# BB#29:                                # %entry_ifend105
	movl	$0, gSigInt(%rip)
	movl	$1, (%rsp)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB27_1
# BB#30:                                # %entry_ifend109
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r8d
	movl	$2, (%rsp)
	movl	$1, %r9d
	jmp	.LBB27_18
.LBB27_31:                              # %label_if_elifzzzzzzzzzzzzm0a
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#32:                                # %entry_ifend119
	movq	(%rax), %rax
	cmpl	%eax, %r14d
	jne	.LBB27_42
# BB#33:                                # %entry_condend123
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %ebp
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#34:                                # %entry_ifend128
	movq	(%rax), %r8
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#35:                                # %entry_ifend131
	movq	(%rax), %rax
	movl	%eax, %r9d
	movl	$0, (%rsp)
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB27_1
# BB#36:                                # %entry_ifend134
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#37:                                # %entry_ifend138
	movq	(%rax), %r8
	movl	$2, (%rsp)
	jmp	.LBB27_38
.LBB27_42:                              # %label_elifzzzzzzzzzzzzp1a
	movl	56(%rsp), %r8d
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#43:                                # %entry_ifend155
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r14d
	jne	.LBB27_49
# BB#44:                                # %entry_condend159
	movl	56(%rsp), %ebp
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#45:                                # %entry_ifend164
	movq	(%rax), %r8
	movl	$2, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#46:                                # %entry_ifend167
	movq	(%rax), %rax
	movl	%eax, %r9d
	movl	$1, (%rsp)
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB27_1
# BB#47:                                # %entry_ifend170
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r8d
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#48:                                # %entry_ifend174
	movq	(%rax), %r8
	movl	$1, (%rsp)
.LBB27_38:                              # %entry_ifend138
	xorl	%r9d, %r9d
	jmp	.LBB27_39
.LBB27_49:                              # %label_if_elifzzzzzzzzzzzzp0a
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#50:                                # %entry_ifend193
	movq	(%rax), %rax
	movl	%eax, %r9d
	movl	$1, (%rsp)
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB27_1
# BB#51:                                # %entry_ifend196
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#52:                                # %entry_ifend200
	movq	(%rax), %r8
	movq	40(%rsp), %rax          # 8-byte Reload
	movl	%eax, %r9d
	movl	$2, (%rsp)
.LBB27_39:                              # %entry_ifend138
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	store_field
	testl	%eax, %eax
	je	.LBB27_1
# BB#40:                                # %entry_ifend141
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r8d
	movl	$2, %r9d
	movq	%r13, %rdi
	movq	48(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#41:                                # %entry_ifend145
	movq	(%rax), %r9
	decl	%r9d
	movl	56(%rsp), %r8d
	movl	$2, (%rsp)
	jmp	.LBB27_18
.LBB27_1:                               # %then_block
	xorl	%eax, %eax
.LBB27_2:                               # %then_block
	addq	$104, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end27:
	.size	"SortableList.delete(GenericsParametorClass0)$$29", .Lfunc_end27-"SortableList.delete(GenericsParametorClass0)$$29"
	.cfi_endproc

	.globl	"SortableList.indexOf(GenericsParametorClass0)$$30"
	.align	16, 0x90
	.type	"SortableList.indexOf(GenericsParametorClass0)$$30",@function
"SortableList.indexOf(GenericsParametorClass0)$$30": # @"SortableList.indexOf(GenericsParametorClass0)$$30"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp352:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp353:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp354:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp355:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp356:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp357:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp358:
	.cfi_def_cfa_offset 128
.Ltmp359:
	.cfi_offset %rbx, -56
.Ltmp360:
	.cfi_offset %r12, -48
.Ltmp361:
	.cfi_offset %r13, -40
.Ltmp362:
	.cfi_offset %r14, -32
.Ltmp363:
	.cfi_offset %r15, -24
.Ltmp364:
	.cfi_offset %rbp, -16
	movl	%r9d, %eax
	movl	%eax, 28(%rsp)          # 4-byte Spill
	movq	%r8, %rbx
	movq	%rcx, %rbp
	movq	%rdx, %rcx
	movq	%rcx, 32(%rsp)          # 8-byte Spill
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	(%rbp), %r15
	movq	$0, 40(%rsp)
	movq	%r15, 40(%rsp)
	movq	8(%rbp), %r13
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 56(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%eax, %edx
	movl	%r15d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB28_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movl	%eax, %r14d
	movq	%r14, 64(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r12d, %r12d
	jmp	.LBB28_4
	.align	16, 0x90
.LBB28_13:                              # %entry_ifend42
                                        #   in Loop: Header=BB28_4 Depth=1
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movl	%eax, %r14d
	movq	%r14, 64(%rsp)
.LBB28_4:                               # %while_start_pointzzzzzzzzzzzzq
                                        # =>This Inner Loop Header: Depth=1
	testl	%r14d, %r14d
	movl	$0, gSigInt(%rip)
	je	.LBB28_8
# BB#5:                                 # %entry_condend
                                        #   in Loop: Header=BB28_4 Depth=1
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB28_1
# BB#6:                                 # %entry_ifend6
                                        #   in Loop: Header=BB28_4 Depth=1
	movq	(%rax), %rax
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r12, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	%r14, 24(%rcx)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	%eax, (%rsp)
	movl	$13528, %edi            # imm = 0x34D8
	movq	%rbp, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB28_7
# BB#10:                                # %entry_ifend22
                                        #   in Loop: Header=BB28_4 Depth=1
	movq	%rbx, %r13
	movq	(%rbp), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%rbp), %r15
	movq	$0, 48(%rsp)
	movq	%r15, 48(%rsp)
	movq	16(%rbp), %r12
	movq	$0, 56(%rsp)
	movq	%r12, 56(%rsp)
	movq	24(%rbp), %rbx
	movq	$0, 64(%rsp)
	movq	%rbx, 64(%rsp)
	movq	(%r13), %rax
	movq	%rbp, %r14
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	testb	$1, %bpl
	jne	.LBB28_11
# BB#12:                                # %label_if_endzzzzzzzzzzzzr
                                        #   in Loop: Header=BB28_4 Depth=1
	incl	%r12d
	movq	$0, 56(%rsp)
	movq	%r12, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%r14, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r14, %rbp
	movq	%r13, %rbx
	movq	%r15, %r13
	movq	16(%rsp), %r15          # 8-byte Reload
	jne	.LBB28_13
	jmp	.LBB28_1
.LBB28_8:                               # %label_whilezzzzzzzzzzzzq
	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
	movq	%rax, (%rbp)
	movl	$1, %eax
	jmp	.LBB28_2
.LBB28_7:                               # %then_block21
	movq	32(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
.LBB28_1:                               # %then_block
	xorl	%eax, %eax
.LBB28_2:                               # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB28_11:                              # %entry_condend35
	movl	%r12d, %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB28_2
.Lfunc_end28:
	.size	"SortableList.indexOf(GenericsParametorClass0)$$30", .Lfunc_end28-"SortableList.indexOf(GenericsParametorClass0)$$30"
	.cfi_endproc

	.globl	"SortableList.toString()$$31"
	.align	16, 0x90
	.type	"SortableList.toString()$$31",@function
"SortableList.toString()$$31":          # @"SortableList.toString()$$31"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp365:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp366:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp367:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp368:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp369:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp370:
	.cfi_def_cfa_offset 56
	subq	$88, %rsp
.Ltmp371:
	.cfi_def_cfa_offset 144
.Ltmp372:
	.cfi_offset %rbx, -56
.Ltmp373:
	.cfi_offset %r12, -48
.Ltmp374:
	.cfi_offset %r13, -40
.Ltmp375:
	.cfi_offset %r14, -32
.Ltmp376:
	.cfi_offset %r15, -24
.Ltmp377:
	.cfi_offset %rbp, -16
	movl	%r9d, %eax
	movl	%eax, 52(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	%rcx, 56(%rsp)          # 8-byte Spill
	movq	%rsi, 40(%rsp)          # 8-byte Spill
	movq	(%rbx), %r12
	movq	$0, 64(%rsp)
	movq	%r12, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%eax, %edx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB29_1
# BB#3:                                 # %entry_ifend
	movq	%rbx, %r15
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	testl	%eax, %eax
	je	.LBB29_4
# BB#6:                                 # %label_if_endzzzzzzzzzzzzs
	movl	$.Lglobal_string.13, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movq	$0, 72(%rsp)
	movl	%ebp, %eax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	%rax, 72(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rbx
	movq	%rbx, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	56(%rsp), %rcx          # 8-byte Reload
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB29_1
# BB#7:                                 # %entry_ifend5
	movq	%rbx, 24(%rsp)          # 8-byte Spill
	movq	(%rax), %rax
	movq	$0, 80(%rsp)
	movl	%eax, %r15d
	movq	%r15, 80(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB29_8
	.align	16, 0x90
.LBB29_19:                              # %entry_ifend99
                                        #   in Loop: Header=BB29_8 Depth=1
	movq	(%rax), %rax
	movq	$0, 80(%rsp)
	movl	%eax, %r15d
	movq	%r15, 80(%rsp)
.LBB29_8:                               # %while_start_pointzzzzzzzzzzzzt
                                        # =>This Inner Loop Header: Depth=1
	testl	%r15d, %r15d
	movl	$0, gSigInt(%rip)
	je	.LBB29_20
# BB#9:                                 # %entry_condend10
                                        #   in Loop: Header=BB29_8 Depth=1
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %r13
	movq	%r13, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	56(%rsp), %rcx          # 8-byte Reload
	movl	%r15d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB29_1
# BB#10:                                # %entry_ifend15
                                        #   in Loop: Header=BB29_8 Depth=1
	movq	(%rax), %rax
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r12, (%rcx)
	movq	$0, 8(%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r15, 16(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	%eax, (%rsp)
	movl	$13848, %edi            # imm = 0x3618
	movq	%r13, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%r14, %rcx
	movq	56(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r8
	movq	144(%rsp), %rbx
	movq	%rbx, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%r13, %rax
	jne	.LBB29_11
# BB#12:                                # %entry_ifend25
                                        #   in Loop: Header=BB29_8 Depth=1
	movq	(%rax), %r13
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movq	8(%rax), %rbp
	movq	$0, 72(%rsp)
	movq	%rbp, 72(%rsp)
	movq	%rbx, %r12
	movq	16(%rax), %rbx
	movq	$0, 80(%rsp)
	movq	%rbx, 80(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$13860, %esi            # imm = 0x3624
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB29_1
# BB#13:                                # %entry_ifend35
                                        #   in Loop: Header=BB29_8 Depth=1
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%rbx, 16(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	%r15, 8(%rcx)
	addq	$8, (%r14)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	%r12, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	56(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB29_14
# BB#15:                                # %entry_ifend51
                                        #   in Loop: Header=BB29_8 Depth=1
	movq	(%r12), %r15
	movq	$0, 64(%rsp)
	movq	%r15, 64(%rsp)
	movq	8(%r12), %rbx
	movq	$0, 72(%rsp)
	movq	%rbx, 72(%rsp)
	movq	16(%r12), %r13
	movq	$0, 80(%rsp)
	movq	%r13, 80(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.14, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$13872, %esi            # imm = 0x3630
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB29_1
# BB#16:                                # %entry_ifend67
                                        #   in Loop: Header=BB29_8 Depth=1
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	$0, 8(%rcx)
	movq	%rbx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r13, 16(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	52(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	56(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r12, %rbx
	jne	.LBB29_17
# BB#18:                                # %entry_ifend83
                                        #   in Loop: Header=BB29_8 Depth=1
	movq	(%rbx), %r12
	movq	$0, 64(%rsp)
	movq	%r12, 64(%rsp)
	movq	8(%rbx), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%rbx), %r15
	movq	$0, 80(%rsp)
	movq	%r15, 80(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r13, %rcx
	movl	%r15d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB29_19
	jmp	.LBB29_1
.LBB29_4:                               # %entry_condend
	movl	$.Lglobal_string.12, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	%ebx, %eax
	movq	%rax, (%r15)
	movl	$1, %eax
	jmp	.LBB29_2
.LBB29_20:                              # %label_whilezzzzzzzzzzzzt
	movl	$13940, %esi            # imm = 0x3674
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB29_1
# BB#21:                                # %entry_ifend104
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r12, (%rcx)
	movq	$0, 8(%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r15, 16(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	$125, 8(%rcx)
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	56(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB29_22
.LBB29_11:                              # %then_block24
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB29_1
.LBB29_14:                              # %then_block50
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB29_1
.LBB29_17:                              # %then_block82
	movq	%r13, %rdi
	callq	get_try_catch_label_name
.LBB29_1:                               # %then_block
	xorl	%eax, %eax
.LBB29_2:                               # %then_block
	addq	$88, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB29_22:                              # %entry_ifend123
	movq	(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%rbx), %rbp
	movq	$0, 72(%rsp)
	movq	%rbp, 72(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB29_2
.Lfunc_end29:
	.size	"SortableList.toString()$$31", .Lfunc_end29-"SortableList.toString()$$31"
	.cfi_endproc

	.globl	"SortableList.join(String)$$32"
	.align	16, 0x90
	.type	"SortableList.join(String)$$32",@function
"SortableList.join(String)$$32":        # @"SortableList.join(String)$$32"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp378:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp379:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp380:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp381:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp382:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp383:
	.cfi_def_cfa_offset 56
	subq	$104, %rsp
.Ltmp384:
	.cfi_def_cfa_offset 160
.Ltmp385:
	.cfi_offset %rbx, -56
.Ltmp386:
	.cfi_offset %r12, -48
.Ltmp387:
	.cfi_offset %r13, -40
.Ltmp388:
	.cfi_offset %r14, -32
.Ltmp389:
	.cfi_offset %r15, -24
.Ltmp390:
	.cfi_offset %rbp, -16
	movl	%r9d, 60(%rsp)          # 4-byte Spill
	movq	%r8, %r13
	movq	%rcx, %rbx
	movq	%rdx, 64(%rsp)          # 8-byte Spill
	movq	%rsi, %r12
	movq	160(%rsp), %rdi
	movq	(%rbx), %rbp
	movq	$0, 72(%rsp)
	movq	%rbp, 72(%rsp)
	movq	8(%rbx), %r14
	movq	$0, 80(%rsp)
	movq	%r14, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$13948, %esi            # imm = 0x367C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB30_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 48(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.15, %edi
	callq	create_string_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$13960, %esi            # imm = 0x3688
	movq	160(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB30_1
# BB#4:                                 # %entry_ifend3
	movq	%r12, 32(%rsp)          # 8-byte Spill
	movq	$0, (%r12)
	movq	%rbp, (%r12)
	movq	$0, 8(%r12)
	movq	%r14, 8(%r12)
	movq	$0, 16(%r12)
	movq	$0, 24(%r12)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	48(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	60(%rsp), %r14d         # 4-byte Reload
	movl	%r14d, %ecx
	movq	%r13, %r8
	movq	64(%rsp), %r12          # 8-byte Reload
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB30_6
# BB#5:                                 # %then_block17
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB30_1
.LBB30_6:                               # %entry_ifend18
	movq	(%rbx), %r15
	movq	$0, 72(%rsp)
	movq	%r15, 72(%rsp)
	movq	8(%rbx), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbp
	movq	%rbp, 48(%rsp)          # 8-byte Spill
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 88(%rsp)
	movq	%rbp, 88(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%r15d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB30_1
# BB#7:                                 # %entry_ifend32
	movq	%r13, %r12
	movq	%rbx, %r13
	movq	%r13, 24(%rsp)          # 8-byte Spill
	movq	(%rax), %rax
	movq	$0, 96(%rsp)
	movl	%eax, %r14d
	movq	%r14, 96(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB30_8
	.align	16, 0x90
.LBB30_19:                              # %entry_ifend135
                                        #   in Loop: Header=BB30_8 Depth=1
	movq	(%r13), %r15
	movq	$0, 72(%rsp)
	movq	%r15, 72(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r13), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r13), %r14
	movq	$0, 96(%rsp)
	movq	%r14, 96(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
.LBB30_8:                               # %while_start_pointzzzzzzzzzzzzu
                                        # =>This Inner Loop Header: Depth=1
	testl	%r14d, %r14d
	movl	$0, gSigInt(%rip)
	je	.LBB30_20
# BB#9:                                 # %entry_condend
                                        #   in Loop: Header=BB30_8 Depth=1
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r13, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	64(%rsp), %rcx          # 8-byte Reload
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB30_1
# BB#10:                                # %entry_ifend38
                                        #   in Loop: Header=BB30_8 Depth=1
	movq	(%rax), %rax
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%r15, (%rdx)
	movq	$0, 8(%rdx)
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%rdx)
	movq	$0, 16(%rdx)
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 16(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	movl	%eax, (%rsp)
	movl	$14028, %edi            # imm = 0x36CC
	movq	%r13, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%r12, %rcx
	movq	64(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r8
	movq	160(%rsp), %r14
	movq	%r14, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB30_11
# BB#12:                                # %entry_ifend53
                                        #   in Loop: Header=BB30_8 Depth=1
	movq	(%r13), %r15
	movq	$0, 72(%rsp)
	movq	%r15, 72(%rsp)
	movq	8(%r13), %rbp
	movq	$0, 80(%rsp)
	movq	%rbp, 80(%rsp)
	movq	16(%r13), %rbx
	movq	$0, 88(%rsp)
	movq	%rbx, 88(%rsp)
	movq	24(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r12), %rax
	movq	%r14, %r13
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$14040, %esi            # imm = 0x36D8
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB30_1
# BB#13:                                # %entry_ifend70
                                        #   in Loop: Header=BB30_8 Depth=1
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%r15, (%rdx)
	movq	$0, 8(%rdx)
	movq	%rbp, 8(%rdx)
	movq	$0, 16(%rdx)
	movq	%rbx, 16(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	%r14, 8(%rcx)
	addq	$8, (%r12)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	24(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %rdx
	movl	60(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r12, %r8
	movq	64(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB30_14
# BB#15:                                # %entry_ifend88
                                        #   in Loop: Header=BB30_8 Depth=1
	movq	(%rbp), %r15
	movq	$0, 72(%rsp)
	movq	%r15, 72(%rsp)
	movq	8(%rbp), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%rbp), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB30_1
# BB#16:                                # %entry_ifend106
                                        #   in Loop: Header=BB30_8 Depth=1
	movq	%rbp, %r13
	movq	(%rax), %rax
	movq	$0, 96(%rsp)
	movl	%eax, %r14d
	movq	%r14, 96(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%eax, %eax
	je	.LBB30_8
# BB#17:                                # %entry_condend112
                                        #   in Loop: Header=BB30_8 Depth=1
	movl	$0, gSigInt(%rip)
	movl	$14076, %esi            # imm = 0x36FC
	movq	160(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB30_1
# BB#18:                                # %entry_ifend117
                                        #   in Loop: Header=BB30_8 Depth=1
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	$0, 8(%rcx)
	movq	40(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	%r14, 24(%rcx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	60(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	64(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB30_19
.LBB30_14:                              # %then_block87
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB30_1
.LBB30_20:                              # %label_whilezzzzzzzzzzzzu
	movq	48(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB30_2
.LBB30_11:                              # %then_block52
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB30_1:                               # %then_block
	xorl	%eax, %eax
.LBB30_2:                               # %then_block
	addq	$104, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end30:
	.size	"SortableList.join(String)$$32", .Lfunc_end30-"SortableList.join(String)$$32"
	.cfi_endproc

	.globl	"SortableList.join()$$33"
	.align	16, 0x90
	.type	"SortableList.join()$$33",@function
"SortableList.join()$$33":              # @"SortableList.join()$$33"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp391:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp392:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp393:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp394:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp395:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp396:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp397:
	.cfi_def_cfa_offset 80
.Ltmp398:
	.cfi_offset %rbx, -56
.Ltmp399:
	.cfi_offset %r12, -48
.Ltmp400:
	.cfi_offset %r13, -40
.Ltmp401:
	.cfi_offset %r14, -32
.Ltmp402:
	.cfi_offset %r15, -24
.Ltmp403:
	.cfi_offset %rbp, -16
	movl	%r9d, 12(%rsp)          # 4-byte Spill
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %r13
	movq	(%r14), %r12
	movq	$0, 16(%rsp)
	movq	%r12, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.16, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$14204, %esi            # imm = 0x377C
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB31_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%r12, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$32, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB31_5
# BB#4:                                 # %then_block8
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB31_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB31_2
.LBB31_5:                               # %entry_ifend9
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
.LBB31_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end31:
	.size	"SortableList.join()$$33", .Lfunc_end31-"SortableList.join()$$33"
	.cfi_endproc

	.globl	"SortableList.count(GenericsParametorClass0)$$34"
	.align	16, 0x90
	.type	"SortableList.count(GenericsParametorClass0)$$34",@function
"SortableList.count(GenericsParametorClass0)$$34": # @"SortableList.count(GenericsParametorClass0)$$34"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp404:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp405:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp406:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp407:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp408:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp409:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp410:
	.cfi_def_cfa_offset 128
.Ltmp411:
	.cfi_offset %rbx, -56
.Ltmp412:
	.cfi_offset %r12, -48
.Ltmp413:
	.cfi_offset %r13, -40
.Ltmp414:
	.cfi_offset %r14, -32
.Ltmp415:
	.cfi_offset %r15, -24
.Ltmp416:
	.cfi_offset %rbp, -16
	movl	%r9d, %eax
	movl	%eax, 36(%rsp)          # 4-byte Spill
	movq	%r8, %rbp
	movq	%rcx, %r12
	movq	%rdx, %rbx
	movq	%rsi, %r15
	movq	(%r12), %r8
	movq	%r8, 16(%rsp)           # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%r8, 40(%rsp)
	movq	8(%r12), %rcx
	movq	%rcx, 24(%rsp)          # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rcx, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 56(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	%eax, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB32_1
# BB#3:                                 # %entry_ifend
	movq	%rbx, 8(%rsp)           # 8-byte Spill
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movl	%eax, %r14d
	movq	%r14, 64(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r13d, %r13d
	jmp	.LBB32_4
	.align	16, 0x90
.LBB32_11:                              # %entry_ifend41
                                        #   in Loop: Header=BB32_4 Depth=1
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movl	%eax, %r14d
	movq	%r14, 64(%rsp)
.LBB32_4:                               # %while_start_pointzzzzzzzzzzzzw
                                        # =>This Inner Loop Header: Depth=1
	testl	%r14d, %r14d
	movl	$0, gSigInt(%rip)
	je	.LBB32_12
# BB#5:                                 # %entry_condend
                                        #   in Loop: Header=BB32_4 Depth=1
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB32_1
# BB#6:                                 # %entry_ifend6
                                        #   in Loop: Header=BB32_4 Depth=1
	movq	(%rax), %rax
	movq	$0, (%r15)
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r15)
	movq	$0, 8(%r15)
	movq	24(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 8(%r15)
	movq	$0, 16(%r15)
	movq	%r13, 16(%r15)
	movq	$0, 24(%r15)
	movq	%r14, 24(%r15)
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
	movl	$14280, %edi            # imm = 0x37C8
	movq	%r12, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movq	%rbx, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB32_7
# BB#8:                                 # %entry_ifend22
                                        #   in Loop: Header=BB32_4 Depth=1
	movq	(%r12), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r12), %r13
	movq	$0, 56(%rsp)
	movq	%r13, 56(%rsp)
	movq	24(%r12), %r14
	movq	$0, 64(%rsp)
	movq	%r14, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	testb	$1, %bl
	je	.LBB32_10
# BB#9:                                 # %entry_condend35
                                        #   in Loop: Header=BB32_4 Depth=1
	movl	$0, gSigInt(%rip)
	incl	%r13d
	movq	$0, 56(%rsp)
	movq	%r13, 56(%rsp)
.LBB32_10:                              # %label_if_endzzzzzzzzzzzzx
                                        #   in Loop: Header=BB32_4 Depth=1
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB32_11
	jmp	.LBB32_1
.LBB32_12:                              # %label_whilezzzzzzzzzzzzw
	movl	%r13d, %eax
	movq	%rax, (%r12)
	movl	$1, %eax
	jmp	.LBB32_2
.LBB32_7:                               # %then_block21
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB32_1:                               # %then_block
	xorl	%eax, %eax
.LBB32_2:                               # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end32:
	.size	"SortableList.count(GenericsParametorClass0)$$34", .Lfunc_end32-"SortableList.count(GenericsParametorClass0)$$34"
	.cfi_endproc

	.globl	"SortableList.indexOf(GenericsParametorClass0)$$35"
	.align	16, 0x90
	.type	"SortableList.indexOf(GenericsParametorClass0)$$35",@function
"SortableList.indexOf(GenericsParametorClass0)$$35": # @"SortableList.indexOf(GenericsParametorClass0)$$35"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp417:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp418:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp419:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp420:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp421:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp422:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp423:
	.cfi_def_cfa_offset 128
.Ltmp424:
	.cfi_offset %rbx, -56
.Ltmp425:
	.cfi_offset %r12, -48
.Ltmp426:
	.cfi_offset %r13, -40
.Ltmp427:
	.cfi_offset %r14, -32
.Ltmp428:
	.cfi_offset %r15, -24
.Ltmp429:
	.cfi_offset %rbp, -16
	movl	%r9d, %eax
	movl	%eax, 28(%rsp)          # 4-byte Spill
	movq	%r8, %rbx
	movq	%rcx, %rbp
	movq	%rdx, %rcx
	movq	%rcx, 32(%rsp)          # 8-byte Spill
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	(%rbp), %r15
	movq	$0, 40(%rsp)
	movq	%r15, 40(%rsp)
	movq	8(%rbp), %r13
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 56(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%eax, %edx
	movl	%r15d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB33_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movl	%eax, %r14d
	movq	%r14, 64(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r12d, %r12d
	jmp	.LBB33_4
	.align	16, 0x90
.LBB33_13:                              # %entry_ifend42
                                        #   in Loop: Header=BB33_4 Depth=1
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movl	%eax, %r14d
	movq	%r14, 64(%rsp)
.LBB33_4:                               # %while_start_pointzzzzzzzzzzzzy
                                        # =>This Inner Loop Header: Depth=1
	testl	%r14d, %r14d
	movl	$0, gSigInt(%rip)
	je	.LBB33_8
# BB#5:                                 # %entry_condend
                                        #   in Loop: Header=BB33_4 Depth=1
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB33_1
# BB#6:                                 # %entry_ifend6
                                        #   in Loop: Header=BB33_4 Depth=1
	movq	(%rax), %rax
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r12, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	%r14, 24(%rcx)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	%eax, (%rsp)
	movl	$14500, %edi            # imm = 0x38A4
	movq	%rbp, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB33_7
# BB#10:                                # %entry_ifend22
                                        #   in Loop: Header=BB33_4 Depth=1
	movq	%rbx, %r13
	movq	(%rbp), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%rbp), %r15
	movq	$0, 48(%rsp)
	movq	%r15, 48(%rsp)
	movq	16(%rbp), %r12
	movq	$0, 56(%rsp)
	movq	%r12, 56(%rsp)
	movq	24(%rbp), %rbx
	movq	$0, 64(%rsp)
	movq	%rbx, 64(%rsp)
	movq	(%r13), %rax
	movq	%rbp, %r14
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	testb	$1, %bpl
	jne	.LBB33_11
# BB#12:                                # %label_if_endzzzzzzzzzzzzz
                                        #   in Loop: Header=BB33_4 Depth=1
	incl	%r12d
	movq	$0, 56(%rsp)
	movq	%r12, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%r14, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r14, %rbp
	movq	%r13, %rbx
	movq	%r15, %r13
	movq	16(%rsp), %r15          # 8-byte Reload
	jne	.LBB33_13
	jmp	.LBB33_1
.LBB33_8:                               # %label_whilezzzzzzzzzzzzy
	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
	movq	%rax, (%rbp)
	movl	$1, %eax
	jmp	.LBB33_2
.LBB33_7:                               # %then_block21
	movq	32(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
.LBB33_1:                               # %then_block
	xorl	%eax, %eax
.LBB33_2:                               # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB33_11:                              # %entry_condend35
	movl	%r12d, %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB33_2
.Lfunc_end33:
	.size	"SortableList.indexOf(GenericsParametorClass0)$$35", .Lfunc_end33-"SortableList.indexOf(GenericsParametorClass0)$$35"
	.cfi_endproc

	.globl	"SortableList.quickSort(Self,int,int)$$36"
	.align	16, 0x90
	.type	"SortableList.quickSort(Self,int,int)$$36",@function
"SortableList.quickSort(Self,int,int)$$36": # @"SortableList.quickSort(Self,int,int)$$36"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp430:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp431:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp432:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp433:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp434:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp435:
	.cfi_def_cfa_offset 56
	subq	$120, %rsp
.Ltmp436:
	.cfi_def_cfa_offset 176
.Ltmp437:
	.cfi_offset %rbx, -56
.Ltmp438:
	.cfi_offset %r12, -48
.Ltmp439:
	.cfi_offset %r13, -40
.Ltmp440:
	.cfi_offset %r14, -32
.Ltmp441:
	.cfi_offset %r15, -24
.Ltmp442:
	.cfi_offset %rbp, -16
	movl	%r9d, 36(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r12
	movq	%rdx, %rbp
	movq	%rsi, %r15
	movq	176(%rsp), %rdi
	movq	(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %r13
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	movq	16(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r12), %rcx
	movq	$0, 64(%rsp)
	movq	%rcx, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 72(%rsp)
	movl	%eax, %ebx
	movq	%rbx, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 80(%rsp)
	movl	%ecx, %eax
	movq	%rax, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$14660, %esi            # imm = 0x3944
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB34_1
# BB#3:                                 # %entry_ifend
	movq	40(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	%rbx, 8(%rcx)
	addq	$8, (%r14)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB34_4
# BB#5:                                 # %entry_ifend31
	movq	(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 88(%rsp)
	movq	%r13, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movq	56(%rsp), %rcx
	movq	$0, 96(%rsp)
	movl	%ecx, %eax
	movq	%rax, 96(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB34_6
.LBB34_38:                              # %label_if_endzzzzzzzzzzzzzh
                                        #   in Loop: Header=BB34_6 Depth=1
	movq	56(%rsp), %rcx
	.align	16, 0x90
.LBB34_6:                               # %while_start_pointzzzzzzzzzzzzzb
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB34_10 Depth 2
                                        #     Child Loop BB34_24 Depth 2
	movq	%rbp, %r13
	movq	64(%rsp), %rbx
	cmpl	%ebx, %ecx
	movl	$0, gSigInt(%rip)
	jl	.LBB34_10
	jmp	.LBB34_7
	.align	16, 0x90
.LBB34_16:                              # %entry_condend163
                                        #   in Loop: Header=BB34_10 Depth=2
	movq	%rbp, %r13
	movl	64(%rsp), %ebx
	decl	%ebx
	movq	$0, 64(%rsp)
	movq	%rbx, 64(%rsp)
.LBB34_10:                              # %while_start_pointzzzzzzzzzzzzzc
                                        #   Parent Loop BB34_6 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	48(%rsp), %ebp
	movl	$14768, %esi            # imm = 0x39B0
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB34_1
# BB#11:                                # %entry_ifend57
                                        #   in Loop: Header=BB34_10 Depth=2
	movq	40(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r13, %rbp
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB34_4
# BB#12:                                # %entry_ifend83
                                        #   in Loop: Header=BB34_10 Depth=2
	movq	(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	88(%rsp), %rax
	movq	40(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	$0, 48(%r15)
	movq	%rax, 48(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r14)
	movl	%r13d, (%rsp)
	movl	$14784, %edi            # imm = 0x39C0
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	movq	%rbp, %r8
	movq	176(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB34_4
# BB#13:                                # %entry_ifend132
                                        #   in Loop: Header=BB34_10 Depth=2
	movq	(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	testl	%ebx, %ebx
	setns	%al
	movq	$0, 104(%rsp)
	movzbl	%al, %eax
	movq	%rax, 104(%rsp)
	js	.LBB34_15
# BB#14:                                # %entry_condend157
                                        #   in Loop: Header=BB34_10 Depth=2
	movl	56(%rsp), %eax
	cmpl	64(%rsp), %eax
	setl	%al
	movzbl	%al, %eax
	movq	%rax, 104(%rsp)
.LBB34_15:                              # %label_and_endpointzzzzzzzzzzzzzd
                                        #   in Loop: Header=BB34_10 Depth=2
	movl	$0, gSigInt(%rip)
	testq	%rax, %rax
	jne	.LBB34_16
# BB#17:                                # %label_whilezzzzzzzzzzzzzc
                                        #   in Loop: Header=BB34_6 Depth=1
	movq	56(%rsp), %rbx
	movl	64(%rsp), %r13d
	cmpl	%r13d, %ebx
	je	.LBB34_23
# BB#18:                                # %entry_condend170
                                        #   in Loop: Header=BB34_6 Depth=1
	movq	%rbp, 24(%rsp)          # 8-byte Spill
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %ebp
	movl	$14988, %esi            # imm = 0x3A8C
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB34_1
# BB#19:                                # %entry_ifend177
                                        #   in Loop: Header=BB34_6 Depth=1
	movq	40(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, 16(%rsp)          # 8-byte Spill
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	24(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB34_4
# BB#20:                                # %entry_ifend203
                                        #   in Loop: Header=BB34_6 Depth=1
	movq	(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$15004, %esi            # imm = 0x3A9C
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB34_1
# BB#21:                                # %entry_ifend228
                                        #   in Loop: Header=BB34_6 Depth=1
	movq	40(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r14)
	movl	$15, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB34_4
# BB#22:                                # %entry_ifend257
                                        #   in Loop: Header=BB34_6 Depth=1
	movq	(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %ebx
	incl	%ebx
	movq	$0, 56(%rsp)
	movq	%rbx, 56(%rsp)
.LBB34_23:                              # %label_if_endzzzzzzzzzzzzze
                                        #   in Loop: Header=BB34_6 Depth=1
	movq	%rbp, %r13
	movl	$0, gSigInt(%rip)
	jmp	.LBB34_24
	.align	16, 0x90
.LBB34_30:                              # %entry_condend397
                                        #   in Loop: Header=BB34_24 Depth=2
	movq	%rbp, %r13
	incl	%ebx
	movq	$0, 56(%rsp)
	movq	%rbx, 56(%rsp)
.LBB34_24:                              # %while_start_pointzzzzzzzzzzzzzf
                                        #   Parent Loop BB34_6 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	48(%rsp), %ebp
	movl	$15108, %esi            # imm = 0x3B04
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB34_1
# BB#25:                                # %entry_ifend288
                                        #   in Loop: Header=BB34_24 Depth=2
	movq	40(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r13, %rbp
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB34_4
# BB#26:                                # %entry_ifend314
                                        #   in Loop: Header=BB34_24 Depth=2
	movq	(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	88(%rsp), %rax
	movq	40(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	$0, 48(%r15)
	movq	%rax, 48(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r14)
	movl	%r13d, (%rsp)
	movl	$15124, %edi            # imm = 0x3B14
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	movq	%rbp, %r8
	movq	176(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB34_4
# BB#27:                                # %entry_ifend363
                                        #   in Loop: Header=BB34_24 Depth=2
	movq	(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	testl	%ebx, %ebx
	setle	%al
	movq	$0, 112(%rsp)
	movzbl	%al, %eax
	movq	%rax, 112(%rsp)
	jg	.LBB34_29
# BB#28:                                # %entry_condend389
                                        #   in Loop: Header=BB34_24 Depth=2
	movl	56(%rsp), %eax
	cmpl	64(%rsp), %eax
	setl	%al
	movzbl	%al, %eax
	movq	%rax, 112(%rsp)
.LBB34_29:                              # %label_and_endpointzzzzzzzzzzzzzg
                                        #   in Loop: Header=BB34_24 Depth=2
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %ebx
	testq	%rax, %rax
	jne	.LBB34_30
# BB#31:                                # %label_whilezzzzzzzzzzzzzf
                                        #   in Loop: Header=BB34_6 Depth=1
	movl	64(%rsp), %eax
	cmpl	%eax, %ebx
	je	.LBB34_38
# BB#32:                                # %entry_condend407
                                        #   in Loop: Header=BB34_6 Depth=1
	movl	%eax, 24(%rsp)          # 4-byte Spill
	movq	%rbp, %r13
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %ebp
	movl	$15328, %esi            # imm = 0x3BE0
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB34_1
# BB#33:                                # %entry_ifend414
                                        #   in Loop: Header=BB34_6 Depth=1
	movq	40(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %ebp
	movq	%rbp, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r13, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB34_34
# BB#35:                                # %entry_ifend440
                                        #   in Loop: Header=BB34_6 Depth=1
	movq	%rbp, %r13
	movq	(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$15344, %esi            # imm = 0x3BF0
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB34_1
# BB#36:                                # %entry_ifend465
                                        #   in Loop: Header=BB34_6 Depth=1
	movq	40(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	24(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	addq	$8, (%r14)
	movl	$15, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%rbx, %rbp
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB34_4
# BB#37:                                # %entry_ifend494
                                        #   in Loop: Header=BB34_6 Depth=1
	movq	(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %eax
	decl	%eax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	jmp	.LBB34_38
.LBB34_4:                               # %then_block30
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB34_1:                               # %then_block
	xorl	%eax, %eax
.LBB34_2:                               # %then_block
	addq	$120, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB34_7:                               # %label_whilezzzzzzzzzzzzzb
	movq	%rcx, %rbp
	movl	48(%rsp), %ebx
	movl	88(%rsp), %eax
	movl	%eax, 24(%rsp)          # 4-byte Spill
	movl	$15476, %esi            # imm = 0x3C74
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB34_1
# BB#8:                                 # %entry_ifend527
	movq	40(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
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
	movl	$15, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB34_39
# BB#9:                                 # %then_block555
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB34_1
.LBB34_39:                              # %entry_ifend556
	movq	%r13, 24(%rsp)          # 8-byte Spill
	movq	(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %ebp
	movq	$0, 96(%rsp)
	movq	%rbp, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movl	72(%rsp), %ebx
	movq	$0, 56(%rsp)
	movq	%rbx, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %eax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movl	$0, gSigInt(%rip)
	cmpl	%ebp, %ebx
	jge	.LBB34_43
# BB#40:                                # %entry_condend587
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r13d
	movl	48(%rsp), %eax
	movl	%eax, 16(%rsp)          # 4-byte Spill
	movl	$15520, %esi            # imm = 0x3CA0
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB34_1
# BB#41:                                # %entry_ifend595
	leal	-1(%rbp), %ecx
	movq	40(%rsp), %rdx
	movq	$0, (%r15)
	movq	%rdx, (%r15)
	movq	48(%rsp), %rdx
	movq	$0, 8(%r15)
	movq	%rdx, 8(%r15)
	movq	56(%rsp), %rdx
	movq	$0, 16(%r15)
	movq	%rdx, 16(%r15)
	movq	64(%rsp), %rdx
	movq	$0, 24(%r15)
	movq	%rdx, 24(%r15)
	movq	72(%rsp), %rdx
	movq	$0, 32(%r15)
	movq	%rdx, 32(%r15)
	movq	80(%rsp), %rdx
	movq	$0, 40(%r15)
	movq	%rdx, 40(%r15)
	movq	88(%rsp), %rdx
	movq	$0, 48(%r15)
	movq	%rdx, 48(%r15)
	movq	96(%rsp), %rdx
	movq	$0, 56(%r15)
	movq	%rdx, 56(%r15)
	movq	(%r14), %rdx
	movq	$0, (%rdx)
	movl	%r13d, %esi
	movq	%rsi, (%rdx)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movl	16(%rsp), %esi          # 4-byte Reload
	movq	%rsi, 8(%rdx)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movl	%ebx, %esi
	movq	%rsi, 8(%rdx)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movl	%ecx, %ecx
	movq	%rcx, 8(%rdx)
	addq	$8, (%r14)
	movl	$36, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB34_34
# BB#42:                                # %entry_ifend627
	movq	(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
.LBB34_43:                              # %label_if_endzzzzzzzzzzzzzi
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r13d
	movl	96(%rsp), %ebx
	cmpl	%ebx, %r13d
	jle	.LBB34_47
# BB#44:                                # %entry_condend655
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %eax
	movl	%eax, 16(%rsp)          # 4-byte Spill
	movl	48(%rsp), %ebp
	movl	$15620, %esi            # imm = 0x3D04
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB34_1
# BB#45:                                # %entry_ifend663
	incl	%ebx
	movq	40(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	16(%rsp), %edx          # 4-byte Reload
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
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$36, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB34_46
.LBB34_34:                              # %then_block439
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB34_1
.LBB34_46:                              # %entry_ifend695
	movq	(%r12), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
.LBB34_47:                              # %label_if_endzzzzzzzzzzzzzj
	movq	$0, (%r12)
	movl	$1, %eax
	jmp	.LBB34_2
.Lfunc_end34:
	.size	"SortableList.quickSort(Self,int,int)$$36", .Lfunc_end34-"SortableList.quickSort(Self,int,int)$$36"
	.cfi_endproc

	.globl	"SortableList.mergeList(Self,Self)$$37"
	.align	16, 0x90
	.type	"SortableList.mergeList(Self,Self)$$37",@function
"SortableList.mergeList(Self,Self)$$37": # @"SortableList.mergeList(Self,Self)$$37"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp443:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp444:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp445:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp446:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp447:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp448:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp449:
	.cfi_def_cfa_offset 128
.Ltmp450:
	.cfi_offset %rbx, -56
.Ltmp451:
	.cfi_offset %r12, -48
.Ltmp452:
	.cfi_offset %r13, -40
.Ltmp453:
	.cfi_offset %r14, -32
.Ltmp454:
	.cfi_offset %r15, -24
.Ltmp455:
	.cfi_offset %rbp, -16
	movl	%r9d, 28(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %r12
	movq	%rsi, %rbx
	movq	128(%rsp), %rdi
	movq	(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	$0, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$15692, %esi            # imm = 0x3D4C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB35_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$15708, %esi            # imm = 0x3D5C
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB35_1
# BB#4:                                 # %entry_ifend3
	movq	32(%rsp), %rcx
	movq	%rbx, 16(%rsp)          # 8-byte Spill
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	48(%rsp), %rcx
	movq	$0, 16(%rbx)
	movq	%rcx, 16(%rbx)
	movq	56(%rsp), %rcx
	movq	$0, 24(%rbx)
	movq	%rcx, 24(%rbx)
	movq	64(%rsp), %rcx
	movq	$0, 32(%rbx)
	movq	%rcx, 32(%rbx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rbx
	movq	%rbx, %rdx
	movl	28(%rsp), %r13d         # 4-byte Reload
	movl	%r13d, %ecx
	movq	%r15, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB35_6
# BB#5:                                 # %then_block16
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB35_1
.LBB35_6:                               # %entry_ifend17
	movq	(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movq	%rbx, %r14
	movl	%r13d, %edx
	movl	%r13d, %ebx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB35_1
# BB#7:                                 # %entry_ifend33
	movq	(%rax), %rax
	movq	$0, 56(%rsp)
	movl	%eax, %eax
	movq	%rax, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB35_1
# BB#8:                                 # %entry_ifend37
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movl	%eax, %eax
	movq	%rax, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	%ebx, %edx
	movq	%r12, %rcx
	movq	%r15, %rdi
.LBB35_9:                               # %entry_condend
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rdi, %r13
	movq	%r14, %rsi
	movl	%edx, %r15d
	movq	%rcx, %r12
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB35_1
# BB#10:                                # %entry_ifend41
                                        #   in Loop: Header=BB35_9 Depth=1
	movq	(%rax), %rbx
	movl	64(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB35_1
# BB#11:                                # %entry_ifend45
                                        #   in Loop: Header=BB35_9 Depth=1
	movq	(%rax), %rax
	movq	32(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r13)
	movl	%ebx, (%rsp)
	movl	$15784, %edi            # imm = 0x3DA8
	movq	%r14, %rsi
	movl	%r15d, %ebx
	movl	%ebx, %edx
	movq	%r13, %rcx
	movq	%r12, %r15
	movq	%r15, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB35_12
# BB#13:                                # %entry_ifend65
                                        #   in Loop: Header=BB35_9 Depth=1
	movl	%ebx, %r12d
	movq	(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	24(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	32(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %ebp
	testl	%ebx, %ebx
	jg	.LBB35_28
# BB#14:                                # %entry_condend84
                                        #   in Loop: Header=BB35_9 Depth=1
	movl	56(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB35_1
# BB#15:                                # %entry_ifend89
                                        #   in Loop: Header=BB35_9 Depth=1
	movq	(%rax), %rbx
	movl	$15828, %esi            # imm = 0x3DD4
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB35_1
# BB#16:                                # %entry_ifend92
                                        #   in Loop: Header=BB35_9 Depth=1
	movq	32(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %rbx
	movq	%rbx, %rdx
	movl	%r12d, %r14d
	movl	%r14d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB35_12
# BB#17:                                # %entry_ifend112
                                        #   in Loop: Header=BB35_9 Depth=1
	movq	(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r8d
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%r13, %r12
	movq	%rbx, %rsi
	movq	%rbx, %r13
	movl	%r14d, %edx
	movl	%r14d, %ebx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB35_1
# BB#18:                                # %entry_ifend132
                                        #   in Loop: Header=BB35_9 Depth=1
	movq	(%rax), %rax
	movq	$0, 56(%rsp)
	movl	%eax, %eax
	movq	%rax, 56(%rsp)
	jmp	.LBB35_19
.LBB35_28:                              # %label_elsezzzzzzzzzzzzzl
                                        #   in Loop: Header=BB35_9 Depth=1
	movl	64(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB35_1
# BB#29:                                # %entry_ifend138
                                        #   in Loop: Header=BB35_9 Depth=1
	movq	(%rax), %rbx
	movl	$15900, %esi            # imm = 0x3E1C
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB35_1
# BB#30:                                # %entry_ifend141
                                        #   in Loop: Header=BB35_9 Depth=1
	movq	32(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %rbx
	movq	%rbx, %rdx
	movl	%r12d, %r14d
	movl	%r14d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB35_12
# BB#31:                                # %entry_ifend161
                                        #   in Loop: Header=BB35_9 Depth=1
	movq	(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r8d
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%r13, %r12
	movq	%rbx, %rsi
	movq	%rbx, %r13
	movl	%r14d, %edx
	movl	%r14d, %ebx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB35_1
# BB#32:                                # %entry_ifend181
                                        #   in Loop: Header=BB35_9 Depth=1
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movl	%eax, %eax
	movq	%rax, 64(%rsp)
.LBB35_19:                              # %label_if_endzzzzzzzzzzzzzl
                                        #   in Loop: Header=BB35_9 Depth=1
	movl	$0, gSigInt(%rip)
	movq	56(%rsp), %r8
	testl	%r8d, %r8d
	movl	%ebx, %edx
	movq	%r15, %rcx
	movq	%r12, %rdi
	movq	%r13, %r14
	je	.LBB35_20
# BB#35:                                # %label_elifzzzzzzzzzzzzzm1a
                                        #   in Loop: Header=BB35_9 Depth=1
	cmpl	$0, 64(%rsp)
	jne	.LBB35_9
# BB#36:                                # %entry_condend254
	movq	%r14, 8(%rsp)           # 8-byte Spill
	movq	%rcx, %r12
	movl	%edx, 28(%rsp)          # 4-byte Spill
	movl	$0, gSigInt(%rip)
	movl	28(%rsp), %r14d         # 4-byte Reload
	jmp	.LBB35_37
.LBB35_42:                              # %entry_ifend314
                                        #   in Loop: Header=BB35_37 Depth=1
	movq	(%rax), %rax
	movq	$0, 56(%rsp)
	movl	%eax, %r8d
	movq	%r8, 56(%rsp)
	movq	%rbp, %rdi
.LBB35_37:                              # %while_start_pointzzzzzzzzzzzzzq
                                        # =>This Inner Loop Header: Depth=1
	testl	%r8d, %r8d
	movl	$0, gSigInt(%rip)
	je	.LBB35_34
# BB#38:                                # %entry_condend266
                                        #   in Loop: Header=BB35_37 Depth=1
	movl	48(%rsp), %r13d
	xorl	%r9d, %r9d
	movq	%rdi, %rbp
	movq	8(%rsp), %rsi           # 8-byte Reload
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB35_1
# BB#39:                                # %entry_ifend271
                                        #   in Loop: Header=BB35_37 Depth=1
	movq	(%rax), %rbx
	movl	$16424, %esi            # imm = 0x4028
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB35_1
# BB#40:                                # %entry_ifend274
                                        #   in Loop: Header=BB35_37 Depth=1
	movq	32(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %rdx
	movl	%r14d, %ecx
	movq	%rbp, %r8
	movq	%r12, %r15
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB35_12
# BB#41:                                # %entry_ifend294
                                        #   in Loop: Header=BB35_37 Depth=1
	movq	(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movq	%r15, %r12
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB35_42
	jmp	.LBB35_1
.LBB35_20:                              # %entry_condend186
	movq	%r14, 8(%rsp)           # 8-byte Spill
	movq	%rcx, %r12
	movl	%edx, 28(%rsp)          # 4-byte Spill
	movl	$0, gSigInt(%rip)
	movq	64(%rsp), %r8
	testl	%r8d, %r8d
	je	.LBB35_33
# BB#21:                                # %entry_condend191
	movl	$0, gSigInt(%rip)
	movl	28(%rsp), %r14d         # 4-byte Reload
	jmp	.LBB35_22
.LBB35_27:                              # %entry_ifend245
                                        #   in Loop: Header=BB35_22 Depth=1
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movl	%eax, %r8d
	movq	%r8, 64(%rsp)
	movq	%rbp, %rdi
.LBB35_22:                              # %while_start_pointzzzzzzzzzzzzzo
                                        # =>This Inner Loop Header: Depth=1
	testl	%r8d, %r8d
	je	.LBB35_33
# BB#23:                                # %entry_condend197
                                        #   in Loop: Header=BB35_22 Depth=1
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r13d
	xorl	%r9d, %r9d
	movq	%rdi, %rbp
	movq	8(%rsp), %rsi           # 8-byte Reload
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB35_1
# BB#24:                                # %entry_ifend202
                                        #   in Loop: Header=BB35_22 Depth=1
	movq	(%rax), %rbx
	movl	$16088, %esi            # imm = 0x3ED8
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB35_1
# BB#25:                                # %entry_ifend205
                                        #   in Loop: Header=BB35_22 Depth=1
	movq	32(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %rdx
	movl	%r14d, %ecx
	movq	%rbp, %r8
	movq	%r12, %r15
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB35_12
# BB#26:                                # %entry_ifend225
                                        #   in Loop: Header=BB35_22 Depth=1
	movq	(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movq	%r15, %r12
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	jne	.LBB35_27
	jmp	.LBB35_1
.LBB35_12:                              # %then_block64
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB35_1:                               # %then_block
	xorl	%eax, %eax
.LBB35_2:                               # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB35_33:                              # %label_if_endzzzzzzzzzzzzzn
	movl	$0, gSigInt(%rip)
.LBB35_34:                              # %label_whilezzzzzzzzzzzzzk
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %eax
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rax, (%rcx)
	movl	$1, %eax
	jmp	.LBB35_2
.Lfunc_end35:
	.size	"SortableList.mergeList(Self,Self)$$37", .Lfunc_end35-"SortableList.mergeList(Self,Self)$$37"
	.cfi_endproc

	.globl	"SortableList.mergeSort()$$38"
	.align	16, 0x90
	.type	"SortableList.mergeSort()$$38",@function
"SortableList.mergeSort()$$38":         # @"SortableList.mergeSort()$$38"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp456:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp457:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp458:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp459:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp460:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp461:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp462:
	.cfi_def_cfa_offset 112
.Ltmp463:
	.cfi_offset %rbx, -56
.Ltmp464:
	.cfi_offset %r12, -48
.Ltmp465:
	.cfi_offset %r13, -40
.Ltmp466:
	.cfi_offset %r14, -32
.Ltmp467:
	.cfi_offset %r15, -24
.Ltmp468:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebp
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %r15
	movq	%rsi, %r13
	movq	(%rbx), %r8
	movq	$0, 24(%rsp)
	movq	%r8, 24(%rsp)
	movq	$0, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB36_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	movl	24(%rsp), %r8d
	testl	%eax, %eax
	je	.LBB36_4
# BB#7:                                 # %label_if_endzzzzzzzzzzzzzr
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB36_1
# BB#8:                                 # %entry_ifend6
	movq	(%rax), %r8
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB36_1
# BB#9:                                 # %entry_ifend9
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	testl	%eax, %eax
	je	.LBB36_10
# BB#11:                                # %label_if_endzzzzzzzzzzzzzs
	movq	112(%rsp), %rdi
	movl	$16900, %esi            # imm = 0x4204
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB36_1
# BB#12:                                # %entry_ifend19
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$16916, %esi            # imm = 0x4214
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB36_1
# BB#13:                                # %entry_ifend22
	movq	24(%rsp), %rcx
	movq	%r13, 16(%rsp)          # 8-byte Spill
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	32(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	40(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	48(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB36_14
# BB#15:                                # %entry_ifend34
	movq	(%rbx), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$16932, %esi            # imm = 0x4224
	movq	112(%rsp), %r12
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB36_1
# BB#16:                                # %entry_ifend46
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$16948, %esi            # imm = 0x4234
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB36_1
# BB#17:                                # %entry_ifend49
	movq	24(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	32(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB36_14
# BB#18:                                # %entry_ifend64
	movq	(%rbx), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 40(%rsp)
	movq	%r13, 40(%rsp)
	movl	$0, gSigInt(%rip)
	movl	24(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB36_1
# BB#19:                                # %entry_ifend82
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movl	%eax, %eax
	movq	%rax, 48(%rsp)
	movl	$0, gSigInt(%rip)
.LBB36_20:                              # %entry_condend85
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %eax
	movl	%eax, 8(%rsp)           # 4-byte Spill
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB36_1
# BB#21:                                # %entry_ifend90
                                        #   in Loop: Header=BB36_20 Depth=1
	movq	(%rax), %r13
	movl	$17024, %esi            # imm = 0x4280
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB36_1
# BB#22:                                # %entry_ifend93
                                        #   in Loop: Header=BB36_20 Depth=1
	movq	24(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	32(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB36_14
# BB#23:                                # %entry_ifend111
                                        #   in Loop: Header=BB36_20 Depth=1
	movq	(%rbx), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %eax
	movl	%eax, 8(%rsp)           # 4-byte Spill
	movl	48(%rsp), %r8d
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB36_1
# BB#24:                                # %entry_ifend130
                                        #   in Loop: Header=BB36_20 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB36_1
# BB#25:                                # %entry_ifend133
                                        #   in Loop: Header=BB36_20 Depth=1
	movq	(%rax), %r13
	movl	$17040, %esi            # imm = 0x4290
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB36_1
# BB#26:                                # %entry_ifend136
                                        #   in Loop: Header=BB36_20 Depth=1
	movq	24(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	32(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB36_14
# BB#27:                                # %entry_ifend154
                                        #   in Loop: Header=BB36_20 Depth=1
	movq	(%rbx), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r8d
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB36_1
# BB#28:                                # %entry_ifend172
                                        #   in Loop: Header=BB36_20 Depth=1
	movq	(%rax), %r8
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB36_1
# BB#29:                                # %entry_ifend175
                                        #   in Loop: Header=BB36_20 Depth=1
	movq	(%rax), %rax
	testl	%eax, %eax
	movl	$0, gSigInt(%rip)
	je	.LBB36_38
# BB#30:                                # %label_if_endzzzzzzzzzzzzzu
                                        #   in Loop: Header=BB36_20 Depth=1
	movl	48(%rsp), %r8d
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB36_1
# BB#31:                                # %entry_ifend185
                                        #   in Loop: Header=BB36_20 Depth=1
	movq	(%rax), %r8
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB36_1
# BB#32:                                # %entry_ifend188
                                        #   in Loop: Header=BB36_20 Depth=1
	movq	(%rax), %r8
	movq	$0, 48(%rsp)
	movl	%r8d, %eax
	movq	%rax, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB36_1
# BB#33:                                # %entry_ifend192
                                        #   in Loop: Header=BB36_20 Depth=1
	movq	(%rax), %rax
	testl	%eax, %eax
	jne	.LBB36_20
# BB#34:                                # %entry_condend196
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r13d
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB36_1
# BB#35:                                # %entry_ifend201
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$17196, %esi            # imm = 0x432C
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB36_1
# BB#36:                                # %entry_ifend204
	movq	24(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	32(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB36_14
# BB#37:                                # %entry_ifend222
	movq	(%rbx), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
.LBB36_38:                              # %label_whilezzzzzzzzzzzzzt
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r13d
	movl	$17356, %esi            # imm = 0x43CC
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB36_1
# BB#39:                                # %entry_ifend243
	movq	24(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	32(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$38, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB36_14
# BB#40:                                # %entry_ifend258
	movq	(%rbx), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 8(%rsp)           # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	40(%rsp), %r13d
	movl	$17372, %esi            # imm = 0x43DC
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB36_1
# BB#41:                                # %entry_ifend276
	movq	24(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	32(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	%rdx, %r12
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$38, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB36_14
# BB#42:                                # %entry_ifend291
	movq	(%rbx), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$17388, %esi            # imm = 0x43EC
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB36_1
# BB#43:                                # %entry_ifend308
	movq	24(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	32(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	40(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	48(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r14)
	movl	$37, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB36_44
.LBB36_14:                              # %then_block33
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB36_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB36_2
.LBB36_4:                               # %entry_condend
	movl	%r8d, %eax
	jmp	.LBB36_5
.LBB36_10:                              # %entry_condend13
	movl	24(%rsp), %eax
.LBB36_5:                               # %entry_condend
	movq	%rax, (%rbx)
	movl	$1, %eax
.LBB36_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB36_44:                              # %entry_ifend326
	movq	(%rbx), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%rbx)
	movl	$1, %eax
	jmp	.LBB36_2
.Lfunc_end36:
	.size	"SortableList.mergeSort()$$38", .Lfunc_end36-"SortableList.mergeSort()$$38"
	.cfi_endproc

	.globl	"SortableList.sort()$$39"
	.align	16, 0x90
	.type	"SortableList.sort()$$39",@function
"SortableList.sort()$$39":              # @"SortableList.sort()$$39"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp469:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp470:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp471:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp472:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp473:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp474:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp475:
	.cfi_def_cfa_offset 80
.Ltmp476:
	.cfi_offset %rbx, -56
.Ltmp477:
	.cfi_offset %r12, -48
.Ltmp478:
	.cfi_offset %r13, -40
.Ltmp479:
	.cfi_offset %r14, -32
.Ltmp480:
	.cfi_offset %r15, -24
.Ltmp481:
	.cfi_offset %rbp, -16
	movl	%r9d, %r13d
	movq	%r8, %r12
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %rbp
	movq	80(%rsp), %rdi
	movq	(%r14), %rbx
	movq	$0, 8(%rsp)
	movq	%rbx, 8(%rsp)
	movq	$0, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$17404, %esi            # imm = 0x43FC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB37_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	$0, 8(%rbp)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	movl	$38, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r13d, %ecx
	movq	%r12, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB37_4
# BB#5:                                 # %entry_ifend8
	movl	%r13d, 4(%rsp)          # 4-byte Spill
	movq	(%r14), %rbx
	movq	$0, 8(%rsp)
	movq	%rbx, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 16(%rsp)
	movq	%r13, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$17420, %esi            # imm = 0x440C
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB37_1
# BB#6:                                 # %entry_ifend18
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	$0, 8(%rbp)
	movq	%r13, 8(%rbp)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$2, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%r12, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB37_7
.LBB37_4:                               # %then_block7
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB37_1:                               # %then_block
	xorl	%eax, %eax
.LBB37_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB37_7:                               # %entry_ifend32
	movq	(%r14), %rbx
	movq	$0, 8(%rsp)
	movq	%rbx, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, gSigInt(%rip)
	movl	%ebx, %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB37_2
.Lfunc_end37:
	.size	"SortableList.sort()$$39", .Lfunc_end37-"SortableList.sort()$$39"
	.cfi_endproc

	.globl	"SortableList.grep(regex)$$40"
	.align	16, 0x90
	.type	"SortableList.grep(regex)$$40",@function
"SortableList.grep(regex)$$40":         # @"SortableList.grep(regex)$$40"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp482:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp483:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp484:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp485:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp486:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp487:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp488:
	.cfi_def_cfa_offset 128
.Ltmp489:
	.cfi_offset %rbx, -56
.Ltmp490:
	.cfi_offset %r12, -48
.Ltmp491:
	.cfi_offset %r13, -40
.Ltmp492:
	.cfi_offset %r14, -32
.Ltmp493:
	.cfi_offset %r15, -24
.Ltmp494:
	.cfi_offset %rbp, -16
	movl	%r9d, 44(%rsp)          # 4-byte Spill
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, 48(%rsp)          # 8-byte Spill
	movq	%rsi, %rbp
	movq	128(%rsp), %rax
	movq	(%r14), %r12
	movq	$0, 56(%rsp)
	movq	%r12, 56(%rsp)
	movq	8(%r14), %r15
	movq	$0, 64(%rsp)
	movq	%r15, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movq	%rdx, 32(%rsp)
	movl	$0, 24(%rsp)
	movl	$2, 16(%rsp)
	movl	$3, 8(%rsp)
	movl	$569, (%rsp)            # imm = 0x239
	movl	$17436, %ecx            # imm = 0x441C
	movl	$260, %r8d              # imm = 0x104
	movl	$17696, %r9d            # imm = 0x4520
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movq	%rax, %rdx
	callq	run_create_block_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$18268, %esi            # imm = 0x475C
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB38_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%r12, (%rbp)
	movq	$0, 8(%rbp)
	movq	%r15, 8(%rbp)
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
	movl	$13, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	48(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB38_5
# BB#4:                                 # %then_block11
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB38_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB38_2
.LBB38_5:                               # %entry_ifend12
	movq	(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, (%r14)
	movl	$1, %eax
.LBB38_2:                               # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end38:
	.size	"SortableList.grep(regex)$$40", .Lfunc_end38-"SortableList.grep(regex)$$40"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"Null list"
	.size	.Lglobal_string, 10

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.zero	1
	.size	.Lglobal_string.2, 1

	.type	.Lglobal_string.3,@object # @global_string.3
.Lglobal_string.3:
	.asciz	" length list of "
	.size	.Lglobal_string.3, 17

	.type	.Lglobal_string.4,@object # @global_string.4
.Lglobal_string.4:
	.asciz	"Exception"
	.size	.Lglobal_string.4, 10

	.type	.Lglobal_string.5,@object # @global_string.5
.Lglobal_string.5:
	.asciz	"Null pointer exception(1)"
	.size	.Lglobal_string.5, 26

	.type	.Lglobal_string.6,@object # @global_string.6
.Lglobal_string.6:
	.asciz	"Exception"
	.size	.Lglobal_string.6, 10

	.type	.Lglobal_string.7,@object # @global_string.7
.Lglobal_string.7:
	.asciz	"division by zero"
	.size	.Lglobal_string.7, 17

	.type	.Lglobal_string.8,@object # @global_string.8
.Lglobal_string.8:
	.asciz	"Exception"
	.size	.Lglobal_string.8, 10

	.type	.Lglobal_string.9,@object # @global_string.9
.Lglobal_string.9:
	.asciz	"division by zero"
	.size	.Lglobal_string.9, 17

	.type	.Lglobal_string.10,@object # @global_string.10
.Lglobal_string.10:
	.asciz	"Exception"
	.size	.Lglobal_string.10, 10

	.type	.Lglobal_string.11,@object # @global_string.11
.Lglobal_string.11:
	.asciz	"division by zero"
	.size	.Lglobal_string.11, 17

	.type	.Lglobal_string.12,@object # @global_string.12
.Lglobal_string.12:
	.asciz	"list {}"
	.size	.Lglobal_string.12, 8

	.type	.Lglobal_string.13,@object # @global_string.13
.Lglobal_string.13:
	.asciz	"list {"
	.size	.Lglobal_string.13, 7

	.type	.Lglobal_string.14,@object # @global_string.14
.Lglobal_string.14:
	.asciz	","
	.size	.Lglobal_string.14, 2

	.type	.Lglobal_string.15,@object # @global_string.15
.Lglobal_string.15:
	.zero	1
	.size	.Lglobal_string.15, 1

	.type	.Lglobal_string.16,@object # @global_string.16
.Lglobal_string.16:
	.zero	1
	.size	.Lglobal_string.16, 1


	.section	".note.GNU-stack","",@progbits
