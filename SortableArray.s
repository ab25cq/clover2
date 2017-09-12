	.text
	.file	"SortableArray.bc"
	.globl	"SortableArray.length()$$2"
	.align	16, 0x90
	.type	"SortableArray.length()$$2",@function
"SortableArray.length()$$2":            # @"SortableArray.length()$$2"
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
	.size	"SortableArray.length()$$2", .Lfunc_end0-"SortableArray.length()$$2"
	.cfi_endproc

	.globl	"SortableArray.items(int)$$3"
	.align	16, 0x90
	.type	"SortableArray.items(int)$$3",@function
"SortableArray.items(int)$$3":          # @"SortableArray.items(int)$$3"
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
.LBB1_3:                                # %label_if_endzzc
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
	.size	"SortableArray.items(int)$$3", .Lfunc_end1-"SortableArray.items(int)$$3"
	.cfi_endproc

	.globl	"SortableArray.each(lambda)$$4"
	.align	16, 0x90
	.type	"SortableArray.each(lambda)$$4",@function
"SortableArray.each(lambda)$$4":        # @"SortableArray.each(lambda)$$4"
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
.LBB2_1:                                # %for_start_pointzzd
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
.LBB2_9:                                # %label_for_endzzd
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
	.size	"SortableArray.each(lambda)$$4", .Lfunc_end2-"SortableArray.each(lambda)$$4"
	.cfi_endproc

	.globl	"SortableArray.toString()$$5"
	.align	16, 0x90
	.type	"SortableArray.toString()$$5",@function
"SortableArray.toString()$$5":          # @"SortableArray.toString()$$5"
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
	subq	$88, %rsp
.Ltmp35:
	.cfi_def_cfa_offset 144
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
	movq	%rcx, %rbp
	movq	%rdx, %rbx
	movq	%rsi, 48(%rsp)          # 8-byte Spill
	movq	(%rbp), %r12
	movq	$0, 64(%rsp)
	movq	%r12, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbp, %rsi
	movl	%r13d, %edx
	movq	%rbx, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#3:                                 # %entry_ifend
	movl	%r13d, 36(%rsp)         # 4-byte Spill
	movq	%r14, 24(%rsp)          # 8-byte Spill
	movq	%rbp, %r14
	movq	(%rax), %rdi
	callq	get_array_length
	movl	$0, gSigInt(%rip)
	testl	%eax, %eax
	je	.LBB3_4
# BB#6:                                 # %label_if_endzze
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movq	$0, 72(%rsp)
	movl	%ebp, %eax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	%rax, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 80(%rsp)
	xorl	%eax, %eax
	movq	%rax, 56(%rsp)          # 8-byte Spill
	movq	%r14, %rbp
	movq	%rbx, %r15
	movq	%r15, 16(%rsp)          # 8-byte Spill
	movq	24(%rsp), %r14          # 8-byte Reload
	jmp	.LBB3_7
	.align	16, 0x90
.LBB3_19:                               # %entry_ifend86
                                        #   in Loop: Header=BB3_7 Depth=1
	movl	%r12d, %r13d
	movq	(%rbp), %r12
	movq	$0, 64(%rsp)
	movq	%r12, 64(%rsp)
	movq	8(%rbp), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%rbp), %rbx
	movq	$0, 80(%rsp)
	movq	%rbx, 80(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	incl	%ebx
	movq	%rbx, 56(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rbx, 80(%rsp)
.LBB3_7:                                # %for_start_pointzzf
                                        # =>This Inner Loop Header: Depth=1
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbp, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r15, %rbx
	je	.LBB3_1
# BB#8:                                 # %entry_ifend6
                                        #   in Loop: Header=BB3_7 Depth=1
	movq	%r12, 24(%rsp)          # 8-byte Spill
	movl	%r13d, %r12d
	movq	%r14, %r13
	movq	(%rax), %rdi
	callq	get_array_length
	movl	$0, gSigInt(%rip)
	movq	56(%rsp), %rcx          # 8-byte Reload
	cmpl	%eax, %ecx
	jge	.LBB3_20
# BB#9:                                 # %entry_condend9
                                        #   in Loop: Header=BB3_7 Depth=1
	xorl	%r9d, %r9d
	movq	%r13, %r14
	movq	%r14, %rdi
	movq	%rbp, %r15
	movq	%r15, %rsi
	movl	%r12d, %edx
	movq	%rbx, %rcx
	movq	24(%rsp), %rbp          # 8-byte Reload
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#10:                                # %entry_ifend14
                                        #   in Loop: Header=BB3_7 Depth=1
	movq	(%rax), %r8
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r12d, %edx
	movq	%rbx, %rcx
	movq	56(%rsp), %r9           # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#11:                                # %entry_ifend18
                                        #   in Loop: Header=BB3_7 Depth=1
	movq	(%rax), %rax
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	$0, 8(%rcx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	56(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 16(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	%eax, (%rsp)
	movl	$1792, %edi             # imm = 0x700
	movq	%r15, %rsi
	movl	%r12d, %edx
	movq	%r14, %rcx
	movq	%rbx, %r8
	movq	144(%rsp), %rbp
	movq	%rbp, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%r15, %rcx
	movq	%rbx, %rdi
	jne	.LBB3_12
# BB#13:                                # %entry_ifend28
                                        #   in Loop: Header=BB3_7 Depth=1
	movq	(%rcx), %r15
	movq	$0, 64(%rsp)
	movq	%r15, 64(%rsp)
	movq	8(%rcx), %rbp
	movq	$0, 72(%rsp)
	movq	%rbp, 72(%rsp)
	movq	16(%rcx), %rbx
	movq	$0, 80(%rsp)
	movq	%rbx, 80(%rsp)
	movq	(%r14), %rax
	movq	%rcx, %r12
	movq	%r14, %r13
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$1804, %esi             # imm = 0x70C
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#14:                                # %entry_ifend38
                                        #   in Loop: Header=BB3_7 Depth=1
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%rbx, 16(%rcx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	%r14, 8(%rcx)
	addq	$8, (%r13)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	jne	.LBB3_15
# BB#16:                                # %entry_ifend54
                                        #   in Loop: Header=BB3_7 Depth=1
	movq	(%r12), %r15
	movq	$0, 64(%rsp)
	movq	%r15, 64(%rsp)
	movq	8(%r12), %rbx
	movq	$0, 72(%rsp)
	movq	%rbx, 72(%rsp)
	movq	16(%r12), %r14
	movq	$0, 80(%rsp)
	movq	%r14, 80(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.3, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1816, %esi             # imm = 0x718
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#17:                                # %entry_ifend70
                                        #   in Loop: Header=BB3_7 Depth=1
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	$0, 8(%rcx)
	movq	%rbx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r14, 16(%rcx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movq	%r12, %rbp
	movl	36(%rsp), %r12d         # 4-byte Reload
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %r15
	movq	%r13, %r14
	je	.LBB3_19
# BB#18:                                # %then_block85
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_4:                                # %entry_condend
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	%ebx, %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB3_2
.LBB3_20:                               # %label_for_endzzf
	movl	$1864, %esi             # imm = 0x748
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r14
	movq	%r13, %rbx
	movq	24(%rsp), %rsi          # 8-byte Reload
	je	.LBB3_1
# BB#21:                                # %entry_ifend104
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rsi, (%rdx)
	movq	$0, 8(%rdx)
	movq	40(%rsp), %rdi          # 8-byte Reload
	movq	%rdi, 8(%rdx)
	movq	$0, 16(%rdx)
	movq	56(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 16(%rdx)
	movq	(%rbx), %rsi
	movq	$0, (%rsi)
	movl	%edi, %edx
	movq	%rdx, (%rsi)
	movq	(%rbx), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rsi)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rsi)
	movq	(%rbx), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rsi)
	movq	$125, 8(%rsi)
	addq	$8, (%rbx)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r14, %rdi
	je	.LBB3_23
# BB#22:                                # %then_block122
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_12:                               # %then_block27
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_15:                               # %then_block53
	callq	get_try_catch_label_name
.LBB3_1:                                # %then_block
	xorl	%eax, %eax
.LBB3_2:                                # %then_block
	addq	$88, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB3_23:                               # %entry_ifend123
	movq	(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%rbp), %r14
	movq	$0, 72(%rsp)
	movq	%r14, 72(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	%r14d, %eax
	movq	%rax, (%rbp)
	movl	$1, %eax
	jmp	.LBB3_2
.Lfunc_end3:
	.size	"SortableArray.toString()$$5", .Lfunc_end3-"SortableArray.toString()$$5"
	.cfi_endproc

	.globl	"SortableArray.equals(GenericsParametorClass0[])$$6"
	.align	16, 0x90
	.type	"SortableArray.equals(GenericsParametorClass0[])$$6",@function
"SortableArray.equals(GenericsParametorClass0[])$$6": # @"SortableArray.equals(GenericsParametorClass0[])$$6"
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
	subq	$40, %rsp
.Ltmp48:
	.cfi_def_cfa_offset 96
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
	movl	%r9d, %r12d
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	%rsi, %r13
	movq	(%rbx), %r15
	movq	$0, 24(%rsp)
	movq	%r15, 24(%rsp)
	movq	8(%rbx), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.4, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r12d, %edx
	movq	%rax, %rcx
	movl	%ebp, %r8d
	callq	run_array_to_carray_cast
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#3:                                 # %entry_ifend
	movq	96(%rsp), %rdi
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$1884, %esi             # imm = 0x75C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#4:                                 # %entry_ifend5
	movq	$0, (%r13)
	movq	%r15, (%r13)
	movq	$0, 8(%r13)
	movq	%rbp, 8(%r13)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
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
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	16(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB4_6
# BB#5:                                 # %then_block15
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB4_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB4_2
.LBB4_6:                                # %entry_ifend16
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
.LBB4_2:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end4:
	.size	"SortableArray.equals(GenericsParametorClass0[])$$6", .Lfunc_end4-"SortableArray.equals(GenericsParametorClass0[])$$6"
	.cfi_endproc

	.globl	"SortableArray.equals(Array)$$7"
	.align	16, 0x90
	.type	"SortableArray.equals(Array)$$7",@function
"SortableArray.equals(Array)$$7":       # @"SortableArray.equals(Array)$$7"
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
	movl	%r9d, %r15d
	movq	%r8, %r12
	movq	%rcx, %rbp
	movq	%rdx, %rbx
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	(%rbp), %r8
	movq	%r8, 24(%rsp)           # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%r8, 32(%rsp)
	movq	8(%rbp), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	get_array_length
	movl	%eax, %r14d
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#4:                                 # %entry_ifend5
	movq	(%rax), %rdi
	callq	get_array_length
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r14d
	jne	.LBB5_5
# BB#7:                                 # %label_if_endzzg
	movq	$0, 48(%rsp)
	xorl	%r14d, %r14d
	jmp	.LBB5_8
	.align	16, 0x90
.LBB5_18:                               # %label_if_endzzi
                                        #   in Loop: Header=BB5_8 Depth=1
	incl	%r14d
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movl	%ebx, %r15d
	movq	%r13, %rbx
.LBB5_8:                                # %for_start_pointzzh
                                        # =>This Inner Loop Header: Depth=1
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#9:                                 # %entry_ifend11
                                        #   in Loop: Header=BB5_8 Depth=1
	movq	(%rax), %rdi
	callq	get_array_length
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r14d
	jge	.LBB5_19
# BB#10:                                # %entry_condend14
                                        #   in Loop: Header=BB5_8 Depth=1
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%rbx, %r13
	movq	%r13, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#11:                                # %entry_ifend18
                                        #   in Loop: Header=BB5_8 Depth=1
	movq	(%rax), %r8
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	movl	%r14d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#12:                                # %entry_ifend22
                                        #   in Loop: Header=BB5_8 Depth=1
	movq	(%rax), %rbx
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#13:                                # %entry_ifend26
                                        #   in Loop: Header=BB5_8 Depth=1
	movq	(%rax), %r8
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	movl	%r14d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#14:                                # %entry_ifend31
                                        #   in Loop: Header=BB5_8 Depth=1
	movq	(%rax), %rax
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r14, 16(%rcx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%ebx, (%rsp)
	movl	$1988, %edi             # imm = 0x7C4
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	%r13, %r8
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB5_15
# BB#16:                                # %entry_ifend44
                                        #   in Loop: Header=BB5_8 Depth=1
	movl	%r15d, %ebx
	movq	(%rbp), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbp), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%rbp), %r14
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	testl	%r15d, %r15d
	jne	.LBB5_18
# BB#17:                                # %entry_condend55
	movl	$0, gSigInt(%rip)
.LBB5_5:                                # %entry_condend
	movq	$0, (%rbp)
	movl	$1, %eax
	jmp	.LBB5_2
.LBB5_19:                               # %label_for_endzzh
	movq	$1, (%rbp)
	movl	$1, %eax
	jmp	.LBB5_2
.LBB5_15:                               # %then_block43
	movq	%r13, %rdi
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
.Lfunc_end5:
	.size	"SortableArray.equals(Array)$$7", .Lfunc_end5-"SortableArray.equals(Array)$$7"
	.cfi_endproc

	.globl	"SortableArray.equals(EqualableArray)$$8"
	.align	16, 0x90
	.type	"SortableArray.equals(EqualableArray)$$8",@function
"SortableArray.equals(EqualableArray)$$8": # @"SortableArray.equals(EqualableArray)$$8"
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
	movl	%r9d, %r15d
	movq	%r8, %r12
	movq	%rcx, %rbp
	movq	%rdx, %rbx
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	(%rbp), %r8
	movq	%r8, 24(%rsp)           # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%r8, 32(%rsp)
	movq	8(%rbp), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	get_array_length
	movl	%eax, %r14d
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#4:                                 # %entry_ifend5
	movq	(%rax), %rdi
	callq	get_array_length
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r14d
	jne	.LBB6_5
# BB#7:                                 # %label_if_endzzj
	movq	$0, 48(%rsp)
	xorl	%r14d, %r14d
	jmp	.LBB6_8
	.align	16, 0x90
.LBB6_18:                               # %label_if_endzzl
                                        #   in Loop: Header=BB6_8 Depth=1
	incl	%r14d
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movl	%ebx, %r15d
	movq	%r13, %rbx
.LBB6_8:                                # %for_start_pointzzk
                                        # =>This Inner Loop Header: Depth=1
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#9:                                 # %entry_ifend11
                                        #   in Loop: Header=BB6_8 Depth=1
	movq	(%rax), %rdi
	callq	get_array_length
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r14d
	jge	.LBB6_19
# BB#10:                                # %entry_condend14
                                        #   in Loop: Header=BB6_8 Depth=1
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%rbx, %r13
	movq	%r13, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#11:                                # %entry_ifend18
                                        #   in Loop: Header=BB6_8 Depth=1
	movq	(%rax), %r8
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	movl	%r14d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#12:                                # %entry_ifend22
                                        #   in Loop: Header=BB6_8 Depth=1
	movq	(%rax), %rbx
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#13:                                # %entry_ifend26
                                        #   in Loop: Header=BB6_8 Depth=1
	movq	(%rax), %r8
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	movl	%r14d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#14:                                # %entry_ifend31
                                        #   in Loop: Header=BB6_8 Depth=1
	movq	(%rax), %rax
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r14, 16(%rcx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%ebx, (%rsp)
	movl	$2180, %edi             # imm = 0x884
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	%r13, %r8
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB6_15
# BB#16:                                # %entry_ifend44
                                        #   in Loop: Header=BB6_8 Depth=1
	movl	%r15d, %ebx
	movq	(%rbp), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbp), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%rbp), %r14
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	testl	%r15d, %r15d
	jne	.LBB6_18
# BB#17:                                # %entry_condend55
	movl	$0, gSigInt(%rip)
.LBB6_5:                                # %entry_condend
	movq	$0, (%rbp)
	movl	$1, %eax
	jmp	.LBB6_2
.LBB6_19:                               # %label_for_endzzk
	movq	$1, (%rbp)
	movl	$1, %eax
	jmp	.LBB6_2
.LBB6_15:                               # %then_block43
	movq	%r13, %rdi
	callq	get_try_catch_label_name
.LBB6_1:                                # %then_block
	xorl	%eax, %eax
.LBB6_2:                                # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end6:
	.size	"SortableArray.equals(EqualableArray)$$8", .Lfunc_end6-"SortableArray.equals(EqualableArray)$$8"
	.cfi_endproc

	.globl	"SortableArray.equals(Self)$$9"
	.align	16, 0x90
	.type	"SortableArray.equals(Self)$$9",@function
"SortableArray.equals(Self)$$9":        # @"SortableArray.equals(Self)$$9"
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
	movl	%r9d, %r15d
	movq	%r8, %r12
	movq	%rcx, %rbp
	movq	%rdx, %rbx
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	(%rbp), %r8
	movq	%r8, 24(%rsp)           # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%r8, 32(%rsp)
	movq	8(%rbp), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	get_array_length
	movl	%eax, %r14d
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#4:                                 # %entry_ifend5
	movq	(%rax), %rdi
	callq	get_array_length
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r14d
	jne	.LBB7_5
# BB#7:                                 # %label_if_endzzm
	movq	$0, 48(%rsp)
	xorl	%r14d, %r14d
	jmp	.LBB7_8
	.align	16, 0x90
.LBB7_18:                               # %label_if_endzzo
                                        #   in Loop: Header=BB7_8 Depth=1
	incl	%r14d
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movl	%ebx, %r15d
	movq	%r13, %rbx
.LBB7_8:                                # %for_start_pointzzn
                                        # =>This Inner Loop Header: Depth=1
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#9:                                 # %entry_ifend11
                                        #   in Loop: Header=BB7_8 Depth=1
	movq	(%rax), %rdi
	callq	get_array_length
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r14d
	jge	.LBB7_19
# BB#10:                                # %entry_condend14
                                        #   in Loop: Header=BB7_8 Depth=1
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%rbx, %r13
	movq	%r13, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#11:                                # %entry_ifend18
                                        #   in Loop: Header=BB7_8 Depth=1
	movq	(%rax), %r8
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	movl	%r14d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#12:                                # %entry_ifend22
                                        #   in Loop: Header=BB7_8 Depth=1
	movq	(%rax), %rbx
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#13:                                # %entry_ifend26
                                        #   in Loop: Header=BB7_8 Depth=1
	movq	(%rax), %r8
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	movl	%r14d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#14:                                # %entry_ifend31
                                        #   in Loop: Header=BB7_8 Depth=1
	movq	(%rax), %rax
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r14, 16(%rcx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%ebx, (%rsp)
	movl	$2372, %edi             # imm = 0x944
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	%r13, %r8
	movq	112(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB7_15
# BB#16:                                # %entry_ifend44
                                        #   in Loop: Header=BB7_8 Depth=1
	movl	%r15d, %ebx
	movq	(%rbp), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbp), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%rbp), %r14
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	testl	%r15d, %r15d
	jne	.LBB7_18
# BB#17:                                # %entry_condend55
	movl	$0, gSigInt(%rip)
.LBB7_5:                                # %entry_condend
	movq	$0, (%rbp)
	movl	$1, %eax
	jmp	.LBB7_2
.LBB7_19:                               # %label_for_endzzn
	movq	$1, (%rbp)
	movl	$1, %eax
	jmp	.LBB7_2
.LBB7_15:                               # %then_block43
	movq	%r13, %rdi
	callq	get_try_catch_label_name
.LBB7_1:                                # %then_block
	xorl	%eax, %eax
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
	.size	"SortableArray.equals(Self)$$9", .Lfunc_end7-"SortableArray.equals(Self)$$9"
	.cfi_endproc

	.globl	"SortableArray.toArray()$$10"
	.align	16, 0x90
	.type	"SortableArray.toArray()$$10",@function
"SortableArray.toArray()$$10":          # @"SortableArray.toArray()$$10"
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
	movl	$2476, %esi             # imm = 0x9AC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB8_1
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
	je	.LBB8_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movl	$2484, %esi             # imm = 0x9B4
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB8_1
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
	je	.LBB8_7
# BB#6:                                 # %then_block14
	movq	%r12, %rdi
	callq	get_try_catch_label_name
.LBB8_1:                                # %then_block
	xorl	%eax, %eax
.LBB8_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB8_7:                                # %entry_ifend15
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
	jmp	.LBB8_2
.Lfunc_end8:
	.size	"SortableArray.toArray()$$10", .Lfunc_end8-"SortableArray.toArray()$$10"
	.cfi_endproc

	.globl	"SortableArray.toEqualableArray()$$11"
	.align	16, 0x90
	.type	"SortableArray.toEqualableArray()$$11",@function
"SortableArray.toEqualableArray()$$11": # @"SortableArray.toEqualableArray()$$11"
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
	subq	$24, %rsp
.Ltmp113:
	.cfi_def_cfa_offset 80
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
	movl	$2492, %esi             # imm = 0x9BC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_1
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
	je	.LBB9_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movl	$2508, %esi             # imm = 0x9CC
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_1
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
	je	.LBB9_7
# BB#6:                                 # %then_block14
	movq	%r12, %rdi
	callq	get_try_catch_label_name
.LBB9_1:                                # %then_block
	xorl	%eax, %eax
.LBB9_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB9_7:                                # %entry_ifend15
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
	jmp	.LBB9_2
.Lfunc_end9:
	.size	"SortableArray.toEqualableArray()$$11", .Lfunc_end9-"SortableArray.toEqualableArray()$$11"
	.cfi_endproc

	.globl	"SortableArray.toSortableList()$$12"
	.align	16, 0x90
	.type	"SortableArray.toSortableList()$$12",@function
"SortableArray.toSortableList()$$12":   # @"SortableArray.toSortableList()$$12"
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
	subq	$56, %rsp
.Ltmp126:
	.cfi_def_cfa_offset 112
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
	movl	$2524, %esi             # imm = 0x9DC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB10_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movl	$2540, %esi             # imm = 0x9EC
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB10_1
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
	jne	.LBB10_5
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
	jmp	.LBB10_7
	.align	16, 0x90
.LBB10_13:                              # %entry_ifend52
                                        #   in Loop: Header=BB10_7 Depth=1
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
.LBB10_7:                               # %for_start_pointzzp
                                        # =>This Inner Loop Header: Depth=1
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#8:                                 # %entry_ifend24
                                        #   in Loop: Header=BB10_7 Depth=1
	movq	(%rax), %rdi
	callq	get_array_length
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r14d
	jge	.LBB10_14
# BB#9:                                 # %entry_condend
                                        #   in Loop: Header=BB10_7 Depth=1
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#10:                                # %entry_ifend29
                                        #   in Loop: Header=BB10_7 Depth=1
	movq	(%rax), %r8
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r14d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#11:                                # %entry_ifend33
                                        #   in Loop: Header=BB10_7 Depth=1
	movq	(%rax), %r15
	movl	$2596, %esi             # imm = 0xA24
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB10_1
# BB#12:                                # %entry_ifend36
                                        #   in Loop: Header=BB10_7 Depth=1
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
	je	.LBB10_13
.LBB10_5:                               # %then_block11
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB10_1:                               # %then_block
	xorl	%eax, %eax
.LBB10_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB10_14:                              # %label_for_endzzp
	movq	16(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%r12)
	movl	$1, %eax
	jmp	.LBB10_2
.Lfunc_end10:
	.size	"SortableArray.toSortableList()$$12", .Lfunc_end10-"SortableArray.toSortableList()$$12"
	.cfi_endproc

	.globl	"SortableArray.quickSort(int,int)$$13"
	.align	16, 0x90
	.type	"SortableArray.quickSort(int,int)$$13",@function
"SortableArray.quickSort(int,int)$$13": # @"SortableArray.quickSort(int,int)$$13"
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
	subq	$120, %rsp
.Ltmp139:
	.cfi_def_cfa_offset 176
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
	movl	%r9d, %ebp
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, %rbx
	movq	%rsi, 16(%rsp)          # 8-byte Spill
	movq	(%r15), %r8
	movq	$0, 48(%rsp)
	movq	%r8, 48(%rsp)
	movq	8(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r15), %rcx
	movq	$0, 64(%rsp)
	movq	%rcx, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 72(%rsp)
	movl	%eax, %eax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	%rax, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 80(%rsp)
	movl	%ecx, %eax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	%rax, 80(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %r8
	movl	56(%rsp), %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#4:                                 # %entry_ifend9
	movq	(%rax), %rax
	movq	$0, 88(%rsp)
	movl	%eax, %eax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	%rax, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movq	56(%rsp), %rax
	movq	$0, 96(%rsp)
	movl	%eax, %r13d
	movq	%r13, 96(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB11_5
.LBB11_41:                              # %label_if_endzzw
                                        #   in Loop: Header=BB11_5 Depth=1
	movq	56(%rsp), %rax
	movq	%rdx, %r14
	.align	16, 0x90
.LBB11_5:                               # %while_start_pointzzq
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB11_12 Depth 2
                                        #     Child Loop BB11_27 Depth 2
	cmpl	64(%rsp), %eax
	movl	$0, gSigInt(%rip)
	jl	.LBB11_12
	jmp	.LBB11_6
	.align	16, 0x90
.LBB11_19:                              # %entry_condend68
                                        #   in Loop: Header=BB11_12 Depth=2
	movl	64(%rsp), %eax
	decl	%eax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%r15, %r13
	movq	%r12, %r15
.LBB11_12:                              # %while_start_pointzzr
                                        #   Parent Loop BB11_5 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#13:                                # %entry_ifend16
                                        #   in Loop: Header=BB11_12 Depth=2
	movq	(%rax), %r8
	movl	64(%rsp), %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#14:                                # %entry_ifend21
                                        #   in Loop: Header=BB11_12 Depth=2
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	$0, 24(%rdx)
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 24(%rdx)
	movq	$0, 32(%rdx)
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 32(%rdx)
	movq	$0, 40(%rdx)
	movq	24(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 40(%rdx)
	movq	$0, 48(%rdx)
	movq	%r13, 48(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	%eax, (%rsp)
	movl	$2716, %edi             # imm = 0xA9C
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	movq	%rbx, %r8
	movq	176(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB11_15
# BB#16:                                # %entry_ifend43
                                        #   in Loop: Header=BB11_12 Depth=2
	movq	(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r15), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r15), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r15), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	%r15, %r12
	movq	48(%r12), %r15
	movq	$0, 96(%rsp)
	movq	%r15, 96(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	testl	%r13d, %r13d
	setns	%al
	movq	$0, 104(%rsp)
	movzbl	%al, %eax
	movq	%rax, 104(%rsp)
	js	.LBB11_18
# BB#17:                                # %entry_condend62
                                        #   in Loop: Header=BB11_12 Depth=2
	movl	56(%rsp), %eax
	cmpl	64(%rsp), %eax
	setl	%al
	movzbl	%al, %eax
	movq	%rax, 104(%rsp)
.LBB11_18:                              # %label_and_endpointzzs
                                        #   in Loop: Header=BB11_12 Depth=2
	movl	$0, gSigInt(%rip)
	testq	%rax, %rax
	jne	.LBB11_19
# BB#20:                                # %label_whilezzr
                                        #   in Loop: Header=BB11_5 Depth=1
	movl	56(%rsp), %eax
	cmpl	64(%rsp), %eax
	movq	%r15, %r13
	movq	%r12, %r15
	je	.LBB11_26
# BB#21:                                # %entry_condend75
                                        #   in Loop: Header=BB11_5 Depth=1
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#22:                                # %entry_ifend79
                                        #   in Loop: Header=BB11_5 Depth=1
	movq	(%rax), %r12
	movl	56(%rsp), %eax
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#23:                                # %entry_ifend84
                                        #   in Loop: Header=BB11_5 Depth=1
	movq	(%rax), %r8
	movl	64(%rsp), %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#24:                                # %entry_ifend89
                                        #   in Loop: Header=BB11_5 Depth=1
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movl	%r12d, %r8d
	movl	12(%rsp), %r9d          # 4-byte Reload
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB11_1
# BB#25:                                # %entry_ifend92
                                        #   in Loop: Header=BB11_5 Depth=1
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %eax
	incl	%eax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
.LBB11_26:                              # %label_if_endzzt
                                        #   in Loop: Header=BB11_5 Depth=1
	movl	$0, gSigInt(%rip)
	jmp	.LBB11_27
	.align	16, 0x90
.LBB11_34:                              # %entry_condend162
                                        #   in Loop: Header=BB11_27 Depth=2
	incl	%ecx
	movq	$0, 56(%rsp)
	movq	%rcx, 56(%rsp)
	movq	%r14, %r13
	movq	%rdx, %r14
	movq	%r12, %r15
.LBB11_27:                              # %while_start_pointzzu
                                        #   Parent Loop BB11_5 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#28:                                # %entry_ifend100
                                        #   in Loop: Header=BB11_27 Depth=2
	movq	(%rax), %r8
	movl	56(%rsp), %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#29:                                # %entry_ifend105
                                        #   in Loop: Header=BB11_27 Depth=2
	movq	(%rax), %rax
	movq	48(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	$0, 24(%rdx)
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 24(%rdx)
	movq	$0, 32(%rdx)
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 32(%rdx)
	movq	$0, 40(%rdx)
	movq	24(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 40(%rdx)
	movq	$0, 48(%rdx)
	movq	%r13, 48(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%eax, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	%eax, (%rsp)
	movl	$2908, %edi             # imm = 0xB5C
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	movq	%rbx, %r8
	movq	176(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	jne	.LBB11_30
# BB#31:                                # %entry_ifend130
                                        #   in Loop: Header=BB11_27 Depth=2
	movq	%rdi, %r13
	movq	(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r15), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r15), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r15), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	%r14, %rbx
	movq	48(%r15), %r14
	movq	%r15, %r12
	movq	$0, 96(%rsp)
	movq	%r14, 96(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %rdx
	testl	%r15d, %r15d
	setle	%al
	movq	$0, 112(%rsp)
	movzbl	%al, %eax
	movq	%rax, 112(%rsp)
	jg	.LBB11_33
# BB#32:                                # %entry_condend154
                                        #   in Loop: Header=BB11_27 Depth=2
	movl	56(%rsp), %eax
	cmpl	64(%rsp), %eax
	setl	%al
	movzbl	%al, %eax
	movq	%rax, 112(%rsp)
.LBB11_33:                              # %label_and_endpointzzv
                                        #   in Loop: Header=BB11_27 Depth=2
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %ecx
	testq	%rax, %rax
	movq	%r13, %rbx
	jne	.LBB11_34
# BB#35:                                # %label_whilezzu
                                        #   in Loop: Header=BB11_5 Depth=1
	cmpl	64(%rsp), %ecx
	movq	%r14, %r13
	movq	%r12, %r15
	je	.LBB11_41
# BB#36:                                # %entry_condend172
                                        #   in Loop: Header=BB11_5 Depth=1
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rdx, %r14
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#37:                                # %entry_ifend176
                                        #   in Loop: Header=BB11_5 Depth=1
	movq	(%rax), %r12
	movl	64(%rsp), %eax
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#38:                                # %entry_ifend181
                                        #   in Loop: Header=BB11_5 Depth=1
	movq	(%rax), %r8
	movl	56(%rsp), %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#39:                                # %entry_ifend186
                                        #   in Loop: Header=BB11_5 Depth=1
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movl	%r12d, %r8d
	movl	12(%rsp), %r9d          # 4-byte Reload
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB11_1
# BB#40:                                # %entry_ifend189
                                        #   in Loop: Header=BB11_5 Depth=1
	movq	%r14, %rdx
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %eax
	decl	%eax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	jmp	.LBB11_41
.LBB11_15:                              # %then_block42
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB11_1
.LBB11_30:                              # %then_block129
	callq	get_try_catch_label_name
	jmp	.LBB11_1
.LBB11_6:                               # %label_whilezzq
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#7:                                 # %entry_ifend198
	movq	(%rax), %r8
	movl	56(%rsp), %r9d
	movq	24(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB11_1
# BB#8:                                 # %entry_ifend203
	movl	%ebp, 12(%rsp)          # 4-byte Spill
	movq	%rbx, %rbp
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %ebx
	movq	$0, 96(%rsp)
	movq	%rbx, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 56(%rsp)
	movq	40(%rsp), %rcx          # 8-byte Reload
	movl	%ecx, %r13d
	movq	%r13, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 64(%rsp)
	movq	32(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, 64(%rsp)
	movl	$0, gSigInt(%rip)
	cmpl	%ebx, %ecx
	jge	.LBB11_43
# BB#9:                                 # %entry_condend212
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r12d
	movl	$3132, %esi             # imm = 0xC3C
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	12(%rsp), %ecx          # 4-byte Reload
	je	.LBB11_1
# BB#10:                                # %entry_ifend219
	movl	%ebx, %edi
	decl	%edi
	movq	48(%rsp), %rdx
	movq	16(%rsp), %rsi          # 8-byte Reload
	movq	$0, (%rsi)
	movq	%rdx, (%rsi)
	movq	56(%rsp), %rdx
	movq	$0, 8(%rsi)
	movq	%rdx, 8(%rsi)
	movq	64(%rsp), %rdx
	movq	$0, 16(%rsi)
	movq	%rdx, 16(%rsi)
	movq	$0, 24(%rsi)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 24(%rsi)
	movq	$0, 32(%rsi)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 32(%rsi)
	movq	$0, 40(%rsi)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 40(%rsi)
	movq	$0, 48(%rsi)
	movq	%rbx, 48(%rsi)
	movq	(%r14), %rdx
	movq	$0, (%rdx)
	movl	%r12d, %esi
	movq	%rsi, (%rdx)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movq	%r13, 8(%rdx)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movl	%edi, %esi
	movq	%rsi, 8(%rdx)
	addq	$8, (%r14)
	movl	$13, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movq	%r14, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB11_11
# BB#42:                                # %entry_ifend246
	movq	(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r15), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r15), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r15), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r15), %rbx
	movq	$0, 96(%rsp)
	movq	%rbx, 96(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
.LBB11_43:                              # %label_if_endzzx
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r13d
	cmpl	%ebx, %r13d
	jle	.LBB11_47
# BB#44:                                # %entry_condend272
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r12d
	movl	$3196, %esi             # imm = 0xC7C
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	12(%rsp), %ecx          # 4-byte Reload
	je	.LBB11_1
# BB#45:                                # %entry_ifend279
	leal	1(%rbx), %edi
	movq	48(%rsp), %rdx
	movq	16(%rsp), %rsi          # 8-byte Reload
	movq	$0, (%rsi)
	movq	%rdx, (%rsi)
	movq	56(%rsp), %rdx
	movq	$0, 8(%rsi)
	movq	%rdx, 8(%rsi)
	movq	64(%rsp), %rdx
	movq	$0, 16(%rsi)
	movq	%rdx, 16(%rsi)
	movq	$0, 24(%rsi)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 24(%rsi)
	movq	$0, 32(%rsi)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 32(%rsi)
	movq	$0, 40(%rsi)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 40(%rsi)
	movq	$0, 48(%rsi)
	movq	%rbx, 48(%rsi)
	movq	(%r14), %rdx
	movq	$0, (%rdx)
	movl	%r12d, %esi
	movq	%rsi, (%rdx)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movl	%edi, %esi
	movq	%rsi, 8(%rdx)
	movq	(%r14), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rsi)
	movl	%r13d, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r14)
	movl	$13, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movq	%r14, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB11_46
.LBB11_11:                              # %then_block245
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB11_1:                               # %then_block
	xorl	%eax, %eax
.LBB11_2:                               # %then_block
	addq	$120, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB11_46:                              # %entry_ifend306
	movq	(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
.LBB11_47:                              # %label_if_endzzy
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %eax
	movq	%rax, (%r15)
	movl	$1, %eax
	jmp	.LBB11_2
.Lfunc_end11:
	.size	"SortableArray.quickSort(int,int)$$13", .Lfunc_end11-"SortableArray.quickSort(int,int)$$13"
	.cfi_endproc

	.globl	"SortableArray.sort()$$14"
	.align	16, 0x90
	.type	"SortableArray.sort()$$14",@function
"SortableArray.sort()$$14":             # @"SortableArray.sort()$$14"
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
	subq	$24, %rsp
.Ltmp152:
	.cfi_def_cfa_offset 80
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
	movl	%r9d, %r12d
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r13
	movq	%rsi, %r15
	movq	80(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3244, %esi             # imm = 0xCAC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB12_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r15)
	movq	%rbp, (%r15)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %ebp
	movq	%rbp, (%rcx)
	addq	$8, (%rbx)
	movl	$2, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r13, %rdi
	je	.LBB12_5
# BB#4:                                 # %then_block6
	callq	get_try_catch_label_name
	jmp	.LBB12_1
.LBB12_5:                               # %entry_ifend7
	movq	(%r14), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movl	%r12d, 12(%rsp)         # 4-byte Spill
	movq	%rdi, %r12
	movl	-8(%rax), %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$3260, %esi             # imm = 0xCBC
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB12_1
# BB#6:                                 # %entry_ifend14
	decl	%r13d
	movq	$0, (%r15)
	movq	(%rsp), %rcx            # 8-byte Reload
	movq	%rcx, (%r15)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
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
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB12_8
# BB#7:                                 # %then_block28
	movq	%r12, %rdi
	callq	get_try_catch_label_name
.LBB12_1:                               # %then_block
	xorl	%eax, %eax
.LBB12_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB12_8:                               # %entry_ifend29
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
	jmp	.LBB12_2
.Lfunc_end12:
	.size	"SortableArray.sort()$$14", .Lfunc_end12-"SortableArray.sort()$$14"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"array {}"
	.size	.Lglobal_string, 9

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.asciz	"array {"
	.size	.Lglobal_string.2, 8

	.type	.Lglobal_string.3,@object # @global_string.3
.Lglobal_string.3:
	.asciz	","
	.size	.Lglobal_string.3, 2

	.type	.Lglobal_string.4,@object # @global_string.4
.Lglobal_string.4:
	.asciz	"ISortable"
	.size	.Lglobal_string.4, 10


	.section	".note.GNU-stack","",@progbits
