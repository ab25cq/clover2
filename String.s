	.text
	.file	"String.bc"
	.globl	"String.setValue(Self)$$4"
	.align	16, 0x90
	.type	"String.setValue(Self)$$4",@function
"String.setValue(Self)$$4":             # @"String.setValue(Self)$$4"
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
	subq	$104, %rsp
.Ltmp6:
	.cfi_def_cfa_offset 160
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
	movl	%r9d, 48(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, %r12
	movq	%rsi, %rbp
	movq	160(%rsp), %rdi
	movq	(%r15), %r13
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movq	8(%r15), %rbx
	movq	$0, 72(%rsp)
	movq	%rbx, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3932, %esi             # imm = 0xF5C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%r13, (%rbp)
	movq	$0, 8(%rbp)
	movq	%rbx, 8(%rbp)
	movq	$0, 16(%rbp)
	movq	$0, 24(%rbp)
	movq	$0, 32(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	48(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r12, %r13
	movl	%ebx, %r12d
	movq	%r15, %rbp
	je	.LBB0_5
# BB#4:                                 # %then_block14
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB0_1
.LBB0_5:                                # %entry_ifend15
	movq	(%rbp), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%rbp), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movq	%rbx, 32(%rsp)          # 8-byte Spill
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 80(%rsp)
	movq	%rbx, 80(%rsp)
	movl	$0, gSigInt(%rip)
	leal	1(%rbx,%rbx), %eax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3940, %esi             # imm = 0xF64
	movq	160(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%r13, %r15
	movl	%r12d, %r13d
	movq	%rbp, %rbx
	je	.LBB0_1
# BB#6:                                 # %entry_ifend33
	movq	%rax, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	callq	create_array_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %r9d
	movl	$0, (%rsp)
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB0_1
# BB#7:                                 # %entry_ifend36
	movq	%rbx, 56(%rsp)          # 8-byte Spill
	movq	%r15, %rbx
	movl	$0, gSigInt(%rip)
	movq	$0, 96(%rsp)
	xorl	%r12d, %r12d
	movq	56(%rsp), %rbp          # 8-byte Reload
	jmp	.LBB0_8
	.align	16, 0x90
.LBB0_13:                               # %entry_ifend54
                                        #   in Loop: Header=BB0_8 Depth=1
	movq	%r15, %rbx
	incl	%r12d
	movq	$0, 96(%rsp)
	movq	%r12, 96(%rsp)
.LBB0_8:                                # %for_start_pointa
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	56(%rsp), %rsi          # 8-byte Reload
	movl	%r13d, %edx
	movq	%rbx, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	movq	(%rax), %rcx
	movq	%rcx, 48(%rsp)          # 8-byte Spill
	movl	8(%rax), %eax
	movq	32(%rsp), %rcx          # 8-byte Reload
	cmpl	%ecx, %r12d
	jge	.LBB0_14
# BB#9:                                 # %entry_condend
                                        #   in Loop: Header=BB0_8 Depth=1
	testl	%eax, %eax
	movq	%rbx, %r15
	je	.LBB0_1
# BB#10:                                # %entry_ifend42
                                        #   in Loop: Header=BB0_8 Depth=1
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbp, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#11:                                # %entry_ifend47
                                        #   in Loop: Header=BB0_8 Depth=1
	movq	(%rax), %r8
	movq	%r14, %rdi
	movq	%rbp, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movl	%r12d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#12:                                # %entry_ifend51
                                        #   in Loop: Header=BB0_8 Depth=1
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r14, %rdi
	movq	%rbp, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movq	48(%rsp), %r8           # 8-byte Reload
	movl	%r12d, %r9d
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB0_13
	jmp	.LBB0_1
.LBB0_14:                               # %label_for_enda
	testl	%eax, %eax
	movq	%rbx, %r15
	movq	%r14, %rbx
	movq	56(%rsp), %r14          # 8-byte Reload
	je	.LBB0_1
# BB#15:                                # %entry_ifend61
	movq	$0, (%rsp)
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movq	48(%rsp), %r8           # 8-byte Reload
	movl	%r12d, %r9d
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB0_1
# BB#16:                                # %entry_ifend65
	movl	$0, gSigInt(%rip)
	movq	32(%rsp), %rax          # 8-byte Reload
	movl	%eax, %r9d
	movl	$2, (%rsp)
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB0_1
# BB#17:                                # %entry_ifend70
	movl	$0, gSigInt(%rip)
	movq	16(%rsp), %rax          # 8-byte Reload
	movl	%eax, %r9d
	movl	$1, (%rsp)
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB0_1
# BB#18:                                # %entry_ifend75
	movq	$0, (%r14)
	movl	$1, %eax
	jmp	.LBB0_2
.LBB0_1:                                # %then_block
	xorl	%eax, %eax
.LBB0_2:                                # %then_block
	addq	$104, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end0:
	.size	"String.setValue(Self)$$4", .Lfunc_end0-"String.setValue(Self)$$4"
	.cfi_endproc

	.globl	"String.setValue(char[])$$5"
	.align	16, 0x90
	.type	"String.setValue(char[])$$5",@function
"String.setValue(char[])$$5":           # @"String.setValue(char[])$$5"
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
	movl	%ebp, %r9d
	movl	$0, (%rsp)
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movl	$0, gSigInt(%rip)
	movl	%ebp, %edi
	callq	get_array_length
	leal	-1(%rax), %r9d
	movl	$2, (%rsp)
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB1_1
# BB#4:                                 # %entry_ifend7
	movl	$0, gSigInt(%rip)
	movl	%ebp, %edi
	callq	get_array_length
	movl	%eax, %r9d
	movl	$1, (%rsp)
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB1_1
# BB#5:                                 # %entry_ifend12
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB1_2
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
.Lfunc_end1:
	.size	"String.setValue(char[])$$5", .Lfunc_end1-"String.setValue(char[])$$5"
	.cfi_endproc

	.globl	"String.chars(int)$$6"
	.align	16, 0x90
	.type	"String.chars(int)$$6",@function
"String.chars(int)$$6":                 # @"String.chars(int)$$6"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp26:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp27:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp28:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp29:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp30:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp31:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp32:
	.cfi_def_cfa_offset 80
.Ltmp33:
	.cfi_offset %rbx, -56
.Ltmp34:
	.cfi_offset %r12, -48
.Ltmp35:
	.cfi_offset %r13, -40
.Ltmp36:
	.cfi_offset %r14, -32
.Ltmp37:
	.cfi_offset %r15, -24
.Ltmp38:
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
	jns	.LBB2_5
# BB#1:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_2
# BB#4:                                 # %entry_ifend
	movq	(%rax), %rax
	addl	%eax, %ebp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
.LBB2_5:                                # %label_if_endb
	movl	$0, gSigInt(%rip)
	testl	%ebp, %ebp
	jns	.LBB2_7
# BB#6:                                 # %entry_condend9
	movl	$0, gSigInt(%rip)
	movq	$0, 16(%rsp)
	xorl	%ebp, %ebp
.LBB2_7:                                # %label_if_endc
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_2
# BB#8:                                 # %entry_ifend15
	movq	(%rax), %rax
	cmpl	%eax, %ebp
	jl	.LBB2_11
# BB#9:                                 # %entry_condend18
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_2
# BB#10:                                # %entry_ifend22
	movq	(%rax), %rbp
	decl	%ebp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
.LBB2_11:                               # %label_if_endd
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_2
# BB#12:                                # %entry_ifend27
	movq	(%rax), %r8
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB2_2
# BB#13:                                # %entry_ifend31
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB2_3
.LBB2_2:                                # %then_block
	xorl	%eax, %eax
.LBB2_3:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end2:
	.size	"String.chars(int)$$6", .Lfunc_end2-"String.chars(int)$$6"
	.cfi_endproc

	.globl	"String.length()$$7"
	.align	16, 0x90
	.type	"String.length()$$7",@function
"String.length()$$7":                   # @"String.length()$$7"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp39:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp40:
	.cfi_def_cfa_offset 32
.Ltmp41:
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
	je	.LBB3_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB3_2
.LBB3_1:                                # %then_block
	xorl	%eax, %eax
.LBB3_2:                                # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end3:
	.size	"String.length()$$7", .Lfunc_end3-"String.length()$$7"
	.cfi_endproc

	.globl	"String.append(Self)$$8"
	.align	16, 0x90
	.type	"String.append(Self)$$8",@function
"String.append(Self)$$8":               # @"String.append(Self)$$8"
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
	movl	%r9d, %r13d
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %r12
	movq	%rsi, %rbp
	movq	144(%rsp), %rdi
	movq	(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r14), %rbx
	movq	$0, 48(%rsp)
	movq	%rbx, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$4164, %esi             # imm = 0x1044
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#3:                                 # %entry_ifend
	movq	40(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	$0, 8(%rbp)
	movq	%rbx, 8(%rbp)
	movq	$0, 16(%rbp)
	movq	$0, 24(%rbp)
	movq	$0, 32(%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r13d, %ecx
	movq	%r15, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r12, %rbx
	je	.LBB4_5
# BB#4:                                 # %then_block16
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB4_1
.LBB4_5:                                # %entry_ifend17
	movq	(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r14), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movq	%rbp, 24(%rsp)          # 8-byte Spill
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 56(%rsp)
	movq	%rbp, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r8d
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#6:                                 # %entry_ifend35
	movq	(%rax), %r12
	movl	40(%rsp), %r8d
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#7:                                 # %entry_ifend41
	movq	24(%rsp), %rcx          # 8-byte Reload
	leal	1(%r12,%rcx), %ecx
	movl	%ecx, 32(%rsp)          # 4-byte Spill
	movq	(%rax), %r12
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r8d
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%rbx, %rcx
	movq	%rbx, %rbp
	callq	get_field_from_object
	movq	(%rax), %rcx
	movl	8(%rax), %eax
	cmpl	%r12d, 32(%rsp)         # 4-byte Folded Reload
	jge	.LBB4_24
# BB#8:                                 # %entry_condend
	testl	%eax, %eax
	je	.LBB4_1
# BB#9:                                 # %entry_ifend45
	movq	$0, 64(%rsp)
	movl	%ecx, %ecx
	movq	%rcx, 32(%rsp)          # 8-byte Spill
	jmp	.LBB4_10
.LBB4_17:                               # %entry_ifend76
                                        #   in Loop: Header=BB4_10 Depth=1
	movq	%r12, %rbp
	movq	32(%rsp), %rcx          # 8-byte Reload
	incl	%ecx
	movq	%rcx, 32(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
.LBB4_10:                               # %for_start_pointf
                                        # =>This Inner Loop Header: Depth=1
	movq	%rcx, 64(%rsp)
	movl	40(%rsp), %r8d
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#11:                                # %entry_ifend50
                                        #   in Loop: Header=BB4_10 Depth=1
	movq	(%rax), %r12
	movq	24(%rsp), %rax          # 8-byte Reload
	addl	%eax, %r12d
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movl	%r13d, %ebx
	movq	%rbp, %rcx
	callq	get_field_from_object
	movq	(%rax), %rcx
	movq	%rcx, 8(%rsp)           # 8-byte Spill
	movl	8(%rax), %eax
	movq	32(%rsp), %rcx          # 8-byte Reload
	cmpl	%r12d, %ecx
	jge	.LBB4_18
# BB#12:                                # %entry_condend56
                                        #   in Loop: Header=BB4_10 Depth=1
	testl	%eax, %eax
	movq	%rbp, %r12
	movl	%ebx, %r13d
	je	.LBB4_1
# BB#13:                                # %entry_ifend60
                                        #   in Loop: Header=BB4_10 Depth=1
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%r12, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#14:                                # %entry_ifend65
                                        #   in Loop: Header=BB4_10 Depth=1
	movq	(%rax), %rbp
	movl	40(%rsp), %r8d
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#15:                                # %entry_ifend70
                                        #   in Loop: Header=BB4_10 Depth=1
	movq	(%rax), %rax
	movq	32(%rsp), %rcx          # 8-byte Reload
	movl	%ecx, %r9d
	subl	%eax, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#16:                                # %entry_ifend73
                                        #   in Loop: Header=BB4_10 Depth=1
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r13d, %edx
	movq	%r12, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	movq	32(%rsp), %r9           # 8-byte Reload
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB4_17
	jmp	.LBB4_1
.LBB4_24:                               # %label_elsee
	testl	%eax, %eax
	movq	%rbp, %rbx
	je	.LBB4_1
# BB#25:                                # %entry_ifend103
	movq	24(%rsp), %rax          # 8-byte Reload
	addl	%eax, %ecx
	leal	2(%rcx,%rcx), %eax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$4284, %esi             # imm = 0x10BC
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#26:                                # %entry_ifend110
	movl	%r13d, %ebp
	movq	%rax, %rdi
	movq	8(%rsp), %rsi           # 8-byte Reload
	callq	create_array_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movq	$0, 72(%rsp)
	movl	%r12d, %eax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	%rax, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 80(%rsp)
	xorl	%r13d, %r13d
	jmp	.LBB4_27
.LBB4_32:                               # %entry_ifend133
                                        #   in Loop: Header=BB4_27 Depth=1
	incl	%r13d
	movq	$0, 80(%rsp)
	movq	%r13, 80(%rsp)
.LBB4_27:                               # %for_start_pointg
                                        # =>This Inner Loop Header: Depth=1
	movl	40(%rsp), %r8d
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#28:                                # %entry_ifend115
                                        #   in Loop: Header=BB4_27 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r13d
	jge	.LBB4_33
# BB#29:                                # %entry_condend119
                                        #   in Loop: Header=BB4_27 Depth=1
	movl	40(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#30:                                # %entry_ifend125
                                        #   in Loop: Header=BB4_27 Depth=1
	movq	(%rax), %r8
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movl	%r13d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#31:                                # %entry_ifend130
                                        #   in Loop: Header=BB4_27 Depth=1
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	movl	%r13d, %r9d
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB4_32
	jmp	.LBB4_1
.LBB4_18:                               # %label_for_endf
	testl	%eax, %eax
	movq	%rbp, %r13
	movl	%ebx, %ebp
	je	.LBB4_1
# BB#19:                                # %entry_ifend84
	movq	$0, (%rsp)
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r13, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	movq	32(%rsp), %r9           # 8-byte Reload
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB4_1
# BB#20:                                # %entry_ifend88
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r12d
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r13, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#21:                                # %entry_ifend93
	movq	(%rax), %r9
	movq	24(%rsp), %rax          # 8-byte Reload
	addl	%eax, %r9d
	movl	$2, (%rsp)
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r13, %rcx
	movl	%r12d, %r8d
.LBB4_22:                               # %entry_ifend93
	callq	store_field
	testl	%eax, %eax
	je	.LBB4_1
# BB#23:                                # %label_if_ende
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB4_2
.LBB4_33:                               # %label_for_endg
	movl	40(%rsp), %r8d
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#34:                                # %entry_ifend141
	movq	(%rax), %rax
	movq	$0, 80(%rsp)
	movl	%eax, %r13d
	jmp	.LBB4_35
.LBB4_41:                               # %entry_ifend171
                                        #   in Loop: Header=BB4_35 Depth=1
	incl	%r13d
	movq	$0, 80(%rsp)
.LBB4_35:                               # %for_start_pointh
                                        # =>This Inner Loop Header: Depth=1
	movq	%r13, 80(%rsp)
	movl	40(%rsp), %r8d
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#36:                                # %entry_ifend146
                                        #   in Loop: Header=BB4_35 Depth=1
	movq	(%rax), %rax
	movq	24(%rsp), %rcx          # 8-byte Reload
	addl	%ecx, %eax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r13d
	jge	.LBB4_42
# BB#37:                                # %entry_condend152
                                        #   in Loop: Header=BB4_35 Depth=1
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#38:                                # %entry_ifend158
                                        #   in Loop: Header=BB4_35 Depth=1
	movq	(%rax), %r12
	movl	40(%rsp), %r8d
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#39:                                # %entry_ifend163
                                        #   in Loop: Header=BB4_35 Depth=1
	movq	(%rax), %rax
	movl	%r13d, %r9d
	subl	%eax, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movl	%r12d, %r8d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#40:                                # %entry_ifend168
                                        #   in Loop: Header=BB4_35 Depth=1
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	movl	%r13d, %r9d
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB4_41
	jmp	.LBB4_1
.LBB4_42:                               # %label_for_endh
	movq	$0, (%rsp)
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	movl	%r13d, %r9d
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB4_1
# BB#43:                                # %entry_ifend180
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r8d
	movq	32(%rsp), %rax          # 8-byte Reload
	movl	%eax, %r9d
	movl	$0, (%rsp)
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	store_field
	testl	%eax, %eax
	je	.LBB4_1
# BB#44:                                # %entry_ifend185
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r12d
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#45:                                # %entry_ifend190
	movq	(%rax), %r9
	movq	24(%rsp), %rax          # 8-byte Reload
	addl	%eax, %r9d
	movl	$2, (%rsp)
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movl	%r12d, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB4_1
# BB#46:                                # %entry_ifend195
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r8d
	movq	8(%rsp), %rax           # 8-byte Reload
	movl	%eax, %r9d
	movl	$1, (%rsp)
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	jmp	.LBB4_22
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
	.size	"String.append(Self)$$8", .Lfunc_end4-"String.append(Self)$$8"
	.cfi_endproc

	.globl	"String.append(char)$$9"
	.align	16, 0x90
	.type	"String.append(char)$$9",@function
"String.append(char)$$9":               # @"String.append(char)$$9"
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
	subq	$88, %rsp
.Ltmp61:
	.cfi_def_cfa_offset 144
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
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %r12
	movq	(%rbx), %r8
	movq	%r8, 32(%rsp)           # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%r8, 40(%rsp)
	movq	8(%rbx), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 56(%rsp)
	movq	$1, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rbp
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#4:                                 # %entry_ifend7
	addl	$2, %ebp
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %ebp
	jge	.LBB5_15
# BB#5:                                 # %entry_condend
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#6:                                 # %entry_ifend11
	movq	(%rax), %r13
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#7:                                 # %entry_ifend15
	movq	(%rax), %r9
	movq	24(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movl	%r13d, %r8d
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB5_1
# BB#8:                                 # %entry_ifend19
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#9:                                 # %entry_ifend23
	movq	(%rax), %r13
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#10:                                # %entry_ifend27
	movq	(%rax), %r9
	incl	%r9d
	movq	$0, (%rsp)
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movl	%r13d, %r8d
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB5_1
# BB#11:                                # %entry_ifend31
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#12:                                # %entry_ifend36
	movq	(%rax), %r9
	incl	%r9d
	movl	$2, (%rsp)
	jmp	.LBB5_13
.LBB5_15:                               # %label_elsei
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#16:                                # %entry_ifend46
	movq	144(%rsp), %rdi
	movq	(%rax), %rax
	leal	4(%rax,%rax), %eax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$4508, %esi             # imm = 0x119C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#17:                                # %entry_ifend53
	movq	%rax, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	callq	create_array_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movq	$0, 72(%rsp)
	movl	%r13d, %ebp
	movq	%rbp, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 80(%rsp)
	xorl	%r13d, %r13d
	jmp	.LBB5_18
	.align	16, 0x90
.LBB5_23:                               # %entry_ifend75
                                        #   in Loop: Header=BB5_18 Depth=1
	incl	%r13d
	movq	$0, 80(%rsp)
	movq	%r13, 80(%rsp)
.LBB5_18:                               # %for_start_pointj
                                        # =>This Inner Loop Header: Depth=1
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#19:                                # %entry_ifend58
                                        #   in Loop: Header=BB5_18 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r13d
	jge	.LBB5_24
# BB#20:                                # %entry_condend62
                                        #   in Loop: Header=BB5_18 Depth=1
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#21:                                # %entry_ifend68
                                        #   in Loop: Header=BB5_18 Depth=1
	movq	(%rax), %r8
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movl	%r13d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#22:                                # %entry_ifend72
                                        #   in Loop: Header=BB5_18 Depth=1
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	movl	%r13d, %r9d
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB5_23
	jmp	.LBB5_1
.LBB5_24:                               # %label_for_endj
	movq	24(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	movl	%r13d, %r9d
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB5_1
# BB#25:                                # %entry_ifend84
	movl	$0, gSigInt(%rip)
	incl	%r13d
	movq	$0, (%rsp)
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	movl	%r13d, %r9d
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB5_1
# BB#26:                                # %entry_ifend90
	movl	$0, gSigInt(%rip)
	movl	%ebp, %r9d
	movl	$0, (%rsp)
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB5_1
# BB#27:                                # %entry_ifend95
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#28:                                # %entry_ifend100
	movq	(%rax), %r9
	incl	%r9d
	movl	$2, (%rsp)
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB5_1
# BB#29:                                # %entry_ifend105
	movl	$0, gSigInt(%rip)
	movq	16(%rsp), %rax          # 8-byte Reload
	movl	%eax, %r9d
	movl	$1, (%rsp)
.LBB5_13:                               # %entry_ifend36
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB5_1
# BB#14:                                # %label_if_endi
	movl	$0, gSigInt(%rip)
	movq	32(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB5_2
.LBB5_1:                                # %then_block
	xorl	%eax, %eax
.LBB5_2:                                # %then_block
	addq	$88, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end5:
	.size	"String.append(char)$$9", .Lfunc_end5-"String.append(char)$$9"
	.cfi_endproc

	.globl	"String.replace(int,char)$$10"
	.align	16, 0x90
	.type	"String.replace(int,char)$$10",@function
"String.replace(int,char)$$10":         # @"String.replace(int,char)$$10"
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
	movl	%r9d, %r14d
	movq	%r8, %r12
	movq	%rcx, %rbx
	movq	%rdx, %r15
	movq	(%rbx), %r13
	movq	$0, 16(%rsp)
	movq	%r13, 16(%rsp)
	movq	8(%rbx), %rbp
	movq	$0, 24(%rsp)
	movq	%rbp, 24(%rsp)
	movq	16(%rbx), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%ebp, %ebp
	jns	.LBB6_5
# BB#1:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_2
# BB#4:                                 # %entry_ifend
	movq	(%rax), %rax
	addl	%eax, %ebp
	movq	$0, 24(%rsp)
	movq	%rbp, 24(%rsp)
.LBB6_5:                                # %label_if_endk
	movl	$0, gSigInt(%rip)
	testl	%ebp, %ebp
	jns	.LBB6_7
# BB#6:                                 # %entry_condend11
	movl	$0, gSigInt(%rip)
	movq	$0, 24(%rsp)
	xorl	%ebp, %ebp
.LBB6_7:                                # %label_if_endl
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_2
# BB#8:                                 # %entry_ifend17
	movq	(%rax), %rax
	cmpl	%eax, %ebp
	jl	.LBB6_11
# BB#9:                                 # %entry_condend20
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_2
# BB#10:                                # %entry_ifend24
	movq	(%rax), %rbp
	decl	%ebp
	movq	$0, 24(%rsp)
	movq	%rbp, 24(%rsp)
.LBB6_11:                               # %label_if_endm
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_2
# BB#12:                                # %entry_ifend29
	movq	(%rax), %r8
	movq	8(%rsp), %rax           # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r9d
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB6_2
# BB#13:                                # %entry_ifend34
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB6_3
.LBB6_2:                                # %then_block
	xorl	%eax, %eax
.LBB6_3:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end6:
	.size	"String.replace(int,char)$$10", .Lfunc_end6-"String.replace(int,char)$$10"
	.cfi_endproc

	.globl	"String.printf(Self)$$11"
	.align	16, 0x90
	.type	"String.printf(Self)$$11",@function
"String.printf(Self)$$11":              # @"String.printf(Self)$$11"
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
	movl	%r9d, %ebx
	movl	%ebx, 28(%rsp)          # 4-byte Spill
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, %rbp
	movq	%rbp, 32(%rsp)          # 8-byte Spill
	movq	%rsi, 16(%rsp)          # 8-byte Spill
	movq	112(%rsp), %rdx
	movq	(%r14), %r15
	movq	$0, 40(%rsp)
	movq	%r15, 40(%rsp)
	movq	8(%r14), %r12
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movq	(%r13), %rax
	movq	$0, (%rax)
	movl	%r15d, %ecx
	movq	%rcx, (%rax)
	addq	$8, (%r13)
	movq	%rdx, (%rsp)
	movl	$1, %r8d
	movl	$4764, %r9d             # imm = 0x129C
	movq	%r13, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	run_create_carray
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$4772, %esi             # imm = 0x12A4
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_1
# BB#4:                                 # %entry_ifend6
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	addq	$8, (%r13)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB7_6
# BB#5:                                 # %then_block18
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB7_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB7_2
.LBB7_6:                                # %entry_ifend19
	movq	(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, (%r14)
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
	.size	"String.printf(Self)$$11", .Lfunc_end7-"String.printf(Self)$$11"
	.cfi_endproc

	.globl	"String.insert(int,Self)$$12"
	.align	16, 0x90
	.type	"String.insert(int,Self)$$12",@function
"String.insert(int,Self)$$12":          # @"String.insert(int,Self)$$12"
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
	subq	$104, %rsp
.Ltmp100:
	.cfi_def_cfa_offset 160
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
	movl	%r9d, %eax
	movq	%r8, %rdi
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	%rsi, %r13
	movq	(%rbx), %r8
	movq	$0, 48(%rsp)
	movq	%r8, 48(%rsp)
	movq	8(%rbx), %r15
	movq	$0, 56(%rsp)
	movq	%r15, 56(%rsp)
	movq	16(%rbx), %rdx
	movq	%rdx, 40(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rdx, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%r15d, %r15d
	jns	.LBB8_5
# BB#1:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rbx, %rsi
	movl	%eax, %edx
	movq	%rcx, %r14
	movq	%rdi, %r12
	movl	%eax, %ebp
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#4:                                 # %entry_ifend
	movq	(%rax), %rax
	leal	1(%r15,%rax), %r15d
	movq	$0, 56(%rsp)
	movq	%r15, 56(%rsp)
	movl	%ebp, %eax
	movq	%r14, %rcx
	movq	%r12, %rdi
.LBB8_5:                                # %label_if_endzzzzzzzzzzzzzzzzo
	movl	$0, gSigInt(%rip)
	testl	%r15d, %r15d
	jns	.LBB8_7
# BB#6:                                 # %entry_condend12
	movl	$0, gSigInt(%rip)
	movq	$0, 56(%rsp)
	xorl	%r15d, %r15d
.LBB8_7:                                # %label_if_endzzzzzzzzzzzzzzzzp
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r8d
	movl	$2, %r9d
	movq	%rbx, %rsi
	movl	%eax, %edx
	movq	%rdi, %r12
	movq	%rcx, %rbp
	movl	%eax, %r14d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#8:                                 # %entry_ifend18
	movq	%r12, 32(%rsp)          # 8-byte Spill
	movq	%rbx, %r12
	movq	(%rax), %rax
	cmpl	%eax, %r15d
	jle	.LBB8_11
# BB#9:                                 # %entry_condend21
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r8d
	movl	$2, %r9d
	movq	32(%rsp), %rdi          # 8-byte Reload
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rbx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#10:                                # %entry_ifend25
	movq	%rbx, %rbp
	movq	(%rax), %rax
	movq	$0, 56(%rsp)
	movl	%eax, %r15d
	movq	%r15, 56(%rsp)
.LBB8_11:                               # %label_if_endzzzzzzzzzzzzzzzzq
	movq	160(%rsp), %rdi
	movl	$0, gSigInt(%rip)
	movl	$5068, %esi             # imm = 0x13CC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbp, %rbx
	movq	32(%rsp), %rbp          # 8-byte Reload
	je	.LBB8_2
# BB#12:                                # %entry_ifend30
	movq	48(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	$0, 8(%r13)
	movq	%r15, 8(%r13)
	movq	$0, 16(%r13)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 16(%r13)
	movq	$0, 24(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	$0, 40(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbp)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%r14d, %ecx
	movq	%rbp, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %r15
	je	.LBB8_14
# BB#13:                                # %then_block47
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB8_2
.LBB8_14:                               # %entry_ifend48
	movq	(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r12), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r12), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movq	%rbx, 40(%rsp)          # 8-byte Spill
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 72(%rsp)
	movq	%rbx, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r8d
	movl	$2, %r9d
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r15, %rbx
	je	.LBB8_2
# BB#15:                                # %entry_ifend68
	movq	(%rax), %r15
	movl	48(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#16:                                # %entry_ifend75
	movq	%rbp, %rsi
	movq	%rbx, %rbp
	movq	40(%rsp), %rcx          # 8-byte Reload
	leal	1(%r15,%rcx), %ecx
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %ecx
	jge	.LBB8_38
# BB#17:                                # %entry_condend79
	movq	$0, 80(%rsp)
	movq	24(%rsp), %rax          # 8-byte Reload
	movl	%eax, %r15d
	movq	%r15, 8(%rsp)           # 8-byte Spill
	jmp	.LBB8_18
.LBB8_24:                               # %entry_ifend107
                                        #   in Loop: Header=BB8_18 Depth=1
	movq	%rbx, %rsi
	movq	%r15, %rbp
	movl	80(%rsp), %r15d
	incl	%r15d
	movq	$0, 80(%rsp)
.LBB8_18:                               # %for_start_pointzzzzzzzzzzzzzzzzs
                                        # =>This Inner Loop Header: Depth=1
	movq	%r15, 80(%rsp)
	movl	48(%rsp), %r8d
	movl	$2, %r9d
	movq	%rsi, %rbx
	movq	%rbx, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#19:                                # %entry_ifend85
                                        #   in Loop: Header=BB8_18 Depth=1
	movq	(%rax), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r12, %r13
	movq	%rbx, %r12
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	movq	(%rax), %rcx
	movq	%rcx, 24(%rsp)          # 8-byte Spill
	movl	8(%rax), %eax
	movq	32(%rsp), %rcx          # 8-byte Reload
	cmpl	%ecx, %r15d
	jge	.LBB8_25
# BB#20:                                # %entry_condend89
                                        #   in Loop: Header=BB8_18 Depth=1
	testl	%eax, %eax
	movq	%rbp, %r15
	movq	%r12, %rbx
	movq	%r13, %r12
	je	.LBB8_2
# BB#21:                                # %entry_ifend93
                                        #   in Loop: Header=BB8_18 Depth=1
	movl	80(%rsp), %ebp
	movq	40(%rsp), %rax          # 8-byte Reload
	addl	%eax, %ebp
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#22:                                # %entry_ifend100
                                        #   in Loop: Header=BB8_18 Depth=1
	movq	(%rax), %r8
	movl	80(%rsp), %r9d
	movq	%rbx, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#23:                                # %entry_ifend104
                                        #   in Loop: Header=BB8_18 Depth=1
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%rbx, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	movl	%ebp, %r9d
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB8_24
	jmp	.LBB8_2
.LBB8_38:                               # %label_elsezzzzzzzzzzzzzzzzr
	movl	48(%rsp), %r8d
	movl	$2, %r9d
	movq	%rsi, %r15
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%r14d, %ebx
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#39:                                # %entry_ifend162
	movq	(%rax), %rax
	movq	40(%rsp), %rcx          # 8-byte Reload
	addl	%ecx, %eax
	leal	3(%rax,%rax), %r14d
	movq	$0, 80(%rsp)
	movq	%r14, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$5436, %esi             # imm = 0x153C
	movq	160(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB8_2
# BB#40:                                # %entry_ifend170
	movq	%r15, %r13
	movq	%rax, %rdi
	movl	%r14d, %esi
	callq	create_array_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movq	$0, 88(%rsp)
	movl	%r14d, %eax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	%rax, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 96(%rsp)
	xorl	%r14d, %r14d
	jmp	.LBB8_41
.LBB8_45:                               # %entry_ifend190
                                        #   in Loop: Header=BB8_41 Depth=1
	movq	%rbx, %r13
	movl	%r15d, %ebx
	movl	96(%rsp), %r14d
	incl	%r14d
	movq	$0, 96(%rsp)
	movq	%r14, 96(%rsp)
.LBB8_41:                               # %for_start_pointzzzzzzzzzzzzzzzzu
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	movq	24(%rsp), %rax          # 8-byte Reload
	cmpl	%eax, %r14d
	movl	%ebx, %edx
	jge	.LBB8_46
# BB#42:                                # %entry_condend176
                                        #   in Loop: Header=BB8_41 Depth=1
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r13, %rbx
	movq	%rbx, %rdi
	movq	%r12, %rsi
	movq	%rbp, %rcx
	movl	%edx, %r15d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#43:                                # %entry_ifend182
                                        #   in Loop: Header=BB8_41 Depth=1
	movq	(%rax), %r8
	movl	96(%rsp), %r9d
	movq	%rbx, %rdi
	movq	%r12, %rsi
	movl	%r15d, %edx
	movq	%rbp, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#44:                                # %entry_ifend187
                                        #   in Loop: Header=BB8_41 Depth=1
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%rbx, %rdi
	movq	%r12, %rsi
	movl	%r15d, %edx
	movq	%rbp, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	movl	%r14d, %r9d
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB8_45
	jmp	.LBB8_2
.LBB8_25:                               # %label_for_endzzzzzzzzzzzzzzzzs
	testl	%eax, %eax
	movq	%r12, %rbx
	movq	%r13, %r12
	je	.LBB8_2
# BB#26:                                # %entry_ifend114
	movl	80(%rsp), %r9d
	movq	$0, (%rsp)
	movq	%rbx, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB8_2
# BB#27:                                # %entry_ifend118
	movq	%rbx, %r15
	movl	%r14d, %ebx
	movl	$0, gSigInt(%rip)
	movq	$0, 80(%rsp)
	xorl	%eax, %eax
	jmp	.LBB8_28
.LBB8_33:                               # %entry_ifend143
                                        #   in Loop: Header=BB8_28 Depth=1
	movl	80(%rsp), %eax
	incl	%eax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
.LBB8_28:                               # %for_start_pointzzzzzzzzzzzzzzzzt
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r14d
	movq	40(%rsp), %rcx          # 8-byte Reload
	cmpl	%ecx, %eax
	jge	.LBB8_34
# BB#29:                                # %entry_condend124
                                        #   in Loop: Header=BB8_28 Depth=1
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#30:                                # %entry_ifend128
                                        #   in Loop: Header=BB8_28 Depth=1
	movq	(%rax), %r13
	movl	80(%rsp), %r14d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#31:                                # %entry_ifend135
                                        #   in Loop: Header=BB8_28 Depth=1
	movq	(%rax), %r8
	movl	80(%rsp), %r9d
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#32:                                # %entry_ifend140
                                        #   in Loop: Header=BB8_28 Depth=1
	movq	8(%rsp), %rcx           # 8-byte Reload
	addl	%ecx, %r14d
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movl	%r13d, %r8d
	movl	%r14d, %r9d
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB8_33
	jmp	.LBB8_2
.LBB8_46:                               # %label_for_endzzzzzzzzzzzzzzzzu
	movq	$0, 96(%rsp)
	xorl	%r15d, %r15d
	jmp	.LBB8_47
.LBB8_51:                               # %entry_ifend216
                                        #   in Loop: Header=BB8_47 Depth=1
	movq	%rbp, %r13
	movq	%rbx, %rbp
	movl	96(%rsp), %r15d
	incl	%r15d
	movq	$0, 96(%rsp)
	movq	%r15, 96(%rsp)
	movl	%r14d, %edx
.LBB8_47:                               # %for_start_pointzzzzzzzzzzzzzzzzv
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	movq	40(%rsp), %rax          # 8-byte Reload
	cmpl	%eax, %r15d
	movq	%rbp, %rcx
	jge	.LBB8_52
# BB#48:                                # %entry_condend200
                                        #   in Loop: Header=BB8_47 Depth=1
	xorl	%r9d, %r9d
	movq	%r13, %rbp
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movq	16(%rsp), %r8           # 8-byte Reload
	movq	%rcx, %rbx
	movl	%edx, %r14d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#49:                                # %entry_ifend208
                                        #   in Loop: Header=BB8_47 Depth=1
	movq	(%rax), %r8
	movl	96(%rsp), %r9d
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%rbx, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#50:                                # %entry_ifend213
                                        #   in Loop: Header=BB8_47 Depth=1
	movq	24(%rsp), %rcx          # 8-byte Reload
	addl	%ecx, %r15d
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%rbx, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	movl	%r15d, %r9d
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB8_51
	jmp	.LBB8_2
.LBB8_52:                               # %label_for_endzzzzzzzzzzzzzzzzv
	movq	$0, 96(%rsp)
	movq	24(%rsp), %rax          # 8-byte Reload
	movl	%eax, %r15d
	movq	%r15, 96(%rsp)
	jmp	.LBB8_53
.LBB8_58:                               # %entry_ifend246
                                        #   in Loop: Header=BB8_53 Depth=1
	movl	96(%rsp), %r15d
	incl	%r15d
	movq	$0, 96(%rsp)
	movq	%r15, 96(%rsp)
	movl	%r14d, %edx
	movq	%rbx, %rcx
.LBB8_53:                               # %for_start_pointzzzzzzzzzzzzzzzzw
                                        # =>This Inner Loop Header: Depth=1
	movq	%r13, %rdi
	movl	48(%rsp), %r8d
	movl	$2, %r9d
	movq	%r12, %rsi
	movq	%rdi, %r14
	movq	%rcx, %rbp
	movl	%edx, %ebx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#54:                                # %entry_ifend226
                                        #   in Loop: Header=BB8_53 Depth=1
	movq	%r14, %rdx
	movq	%rbp, %r10
	movl	%ebx, %ecx
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %ebp
	movq	40(%rsp), %rsi          # 8-byte Reload
	addl	%esi, %ebp
	cmpl	%eax, %r15d
	jge	.LBB8_59
# BB#55:                                # %entry_condend230
                                        #   in Loop: Header=BB8_53 Depth=1
	movl	48(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rdx, %r13
	movq	%r13, %rdi
	movq	%r12, %rsi
	movl	%ecx, %r14d
	movl	%r14d, %edx
	movq	%r10, %rbx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#56:                                # %entry_ifend238
                                        #   in Loop: Header=BB8_53 Depth=1
	movq	(%rax), %r8
	movl	96(%rsp), %r9d
	movq	%r13, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%rbx, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#57:                                # %entry_ifend243
                                        #   in Loop: Header=BB8_53 Depth=1
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r13, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%rbx, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	movl	%ebp, %r9d
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB8_58
	jmp	.LBB8_2
.LBB8_34:                               # %label_for_endzzzzzzzzzzzzzzzzt
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#35:                                # %entry_ifend152
	movq	(%rax), %r9
	movq	40(%rsp), %rax          # 8-byte Reload
	addl	%eax, %r9d
	movl	$2, (%rsp)
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movl	%r14d, %r8d
.LBB8_36:                               # %entry_ifend152
	callq	store_field
	testl	%eax, %eax
	je	.LBB8_2
# BB#37:                                # %label_if_endzzzzzzzzzzzzzzzzr
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %eax
	movq	%rax, (%r12)
	movl	$1, %eax
	jmp	.LBB8_3
.LBB8_59:                               # %label_for_endzzzzzzzzzzzzzzzzw
	movq	$0, (%rsp)
	movq	%rdx, %r15
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%ecx, %r14d
	movl	%r14d, %edx
	movq	%r10, %rbx
	movq	%rbx, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	movl	%ebp, %r9d
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB8_2
# BB#60:                                # %entry_ifend257
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r8d
	movq	8(%rsp), %rax           # 8-byte Reload
	movl	%eax, %r9d
	movl	$0, (%rsp)
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%rbx, %rcx
	callq	store_field
	testl	%eax, %eax
	je	.LBB8_2
# BB#61:                                # %entry_ifend262
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r8d
	movl	80(%rsp), %r9d
	movl	$1, (%rsp)
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%rbx, %rcx
	callq	store_field
	testl	%eax, %eax
	je	.LBB8_2
# BB#62:                                # %entry_ifend267
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %ebp
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%rbx, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_2
# BB#63:                                # %entry_ifend272
	movq	(%rax), %r9
	movq	40(%rsp), %rax          # 8-byte Reload
	addl	%eax, %r9d
	movl	$2, (%rsp)
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%rbx, %rcx
	movl	%ebp, %r8d
	jmp	.LBB8_36
.LBB8_2:                                # %then_block
	xorl	%eax, %eax
.LBB8_3:                                # %then_block
	addq	$104, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end8:
	.size	"String.insert(int,Self)$$12", .Lfunc_end8-"String.insert(int,Self)$$12"
	.cfi_endproc

	.globl	"String.subString(int,int)$$13"
	.align	16, 0x90
	.type	"String.subString(int,int)$$13",@function
"String.subString(int,int)$$13":        # @"String.subString(int,int)$$13"
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
	subq	$136, %rsp
.Ltmp113:
	.cfi_def_cfa_offset 192
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
	movq	%r8, %rdi
	movq	%rcx, %r12
	movq	%rdx, %rcx
	movq	%rsi, 64(%rsp)          # 8-byte Spill
	movq	(%r12), %r13
	movq	$0, 80(%rsp)
	movq	%r13, 80(%rsp)
	movq	8(%r12), %rbp
	movq	$0, 88(%rsp)
	movq	%rbp, 88(%rsp)
	movq	16(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%ebp, %ebp
	jns	.LBB9_5
# BB#1:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rdi, %r15
	movq	%r12, %rsi
	movl	%ebx, %edx
	movl	%ebx, %r14d
	movq	%rcx, %rbx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#4:                                 # %entry_ifend
	movq	(%rax), %rax
	addl	%eax, %ebp
	movq	$0, 88(%rsp)
	movq	%rbp, 88(%rsp)
	movq	%rbx, %rcx
	movl	%r14d, %ebx
	movq	%r15, %rdi
.LBB9_5:                                # %label_if_endzzzzzzzzzzzzzzzzx
	movl	$0, gSigInt(%rip)
	movq	96(%rsp), %r14
	testl	%r14d, %r14d
	jns	.LBB9_8
# BB#6:                                 # %entry_condend11
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rdi, 72(%rsp)          # 8-byte Spill
	movq	%r12, %rsi
	movl	%ebx, %edx
	movl	%ebx, %r15d
	movq	%rcx, %rbx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#7:                                 # %entry_ifend16
	movq	(%rax), %rax
	leal	1(%r14,%rax), %r14d
	movq	$0, 96(%rsp)
	movq	%r14, 96(%rsp)
	movq	%rbx, %rcx
	movl	%r15d, %ebx
	movq	72(%rsp), %rdi          # 8-byte Reload
.LBB9_8:                                # %label_if_endzzzzzzzzzzzzzzzzy
	movl	$0, gSigInt(%rip)
	testl	%ebp, %ebp
	jns	.LBB9_10
# BB#9:                                 # %entry_condend24
	movl	$0, gSigInt(%rip)
	movq	$0, 88(%rsp)
	xorl	%ebp, %ebp
.LBB9_10:                               # %label_if_endzzzzzzzzzzzzzzzzz
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%rdi, %r15
	movq	%r12, %rsi
	movl	%ebx, %edx
	movl	%ebx, 72(%rsp)          # 4-byte Spill
	movq	%rcx, %rbx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#11:                                # %entry_ifend30
	movq	(%rax), %rax
	cmpl	%eax, %r14d
	jle	.LBB9_14
# BB#12:                                # %entry_condend33
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	72(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#13:                                # %entry_ifend37
	movq	(%rax), %rax
	movq	$0, 96(%rsp)
	movl	%eax, %r14d
	movq	%r14, 96(%rsp)
.LBB9_14:                               # %label_if_endzzzzzzzzzzzzzzzzzb
	movl	$0, gSigInt(%rip)
	cmpl	%r14d, %ebp
	setge	%al
	movq	$0, 120(%rsp)
	movzbl	%al, %eax
	movq	%rax, 120(%rsp)
	movq	%rbx, %rcx
	movq	%r15, %rdi
	jge	.LBB9_19
# BB#15:                                # %entry_condnotend
	movl	$2, %r9d
	movq	%rdi, %r15
	movq	%r12, %rsi
	movl	72(%rsp), %edx          # 4-byte Reload
	movq	%rcx, %rbx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_2
# BB#16:                                # %entry_ifend46
	movq	(%rax), %rax
	cmpl	%eax, %ebp
	setge	%al
	movq	$0, 128(%rsp)
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
	jge	.LBB9_18
# BB#17:                                # %entry_condnotend51
	testl	%r14d, %r14d
	sets	%al
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
.LBB9_18:                               # %label_or_endpointzzzzzzzzzzzzzzzzze
	movq	%rax, 120(%rsp)
	movq	%rbx, %rcx
	movq	%r15, %rdi
.LBB9_19:                               # %label_or_endpointzzzzzzzzzzzzzzzzzd
	movl	$0, gSigInt(%rip)
	testq	%rax, %rax
	je	.LBB9_21
# BB#20:                                # %entry_condend58
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
.LBB9_37:                               # %entry_ifend183
	movq	%rax, (%r12)
	movl	$1, %eax
	jmp	.LBB9_3
.LBB9_21:                               # %label_if_endzzzzzzzzzzzzzzzzzc
	movq	%rdi, %rbx
	movq	%rcx, 32(%rsp)          # 8-byte Spill
	movq	192(%rsp), %rdi
	movl	$6544, %esi             # imm = 0x1990
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_2
# BB#22:                                # %entry_ifend62
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$6552, %esi             # imm = 0x1998
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_2
# BB#23:                                # %entry_ifend68
	movl	%r14d, %ecx
	subl	%ebp, %ecx
	incl	%ecx
	movq	64(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%r13, (%rdx)
	movq	$0, 8(%rdx)
	movq	%rbp, 8(%rdx)
	movq	$0, 16(%rdx)
	movq	%r14, 16(%rdx)
	movq	$0, 24(%rdx)
	movq	$0, 32(%rdx)
	movq	%rbx, %rbp
	movq	(%rbp), %rdx
	movq	$0, (%rdx)
	movl	%r15d, %esi
	movq	%rsi, (%rdx)
	movq	(%rbp), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%rbp)
	movq	$0, 8(%rdx)
	movl	%ecx, %ecx
	movq	%rcx, 8(%rdx)
	addq	$8, (%rbp)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	72(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	32(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB9_24
# BB#25:                                # %entry_ifend85
	movq	(%r12), %r15
	movq	$0, 80(%rsp)
	movq	%r15, 80(%rsp)
	movq	8(%r12), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	16(%r12), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	24(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	32(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r14
	movq	%r14, 56(%rsp)          # 8-byte Spill
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 104(%rsp)
	movq	%r14, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 112(%rsp)
	xorl	%r14d, %r14d
	jmp	.LBB9_26
.LBB9_31:                               # %entry_ifend156
                                        #   in Loop: Header=BB9_26 Depth=1
	incl	%ebx
	movq	$0, 112(%rsp)
	movq	%rbx, 112(%rsp)
	movq	%rbx, %r14
	movq	%r13, %rbx
.LBB9_26:                               # %for_start_pointzzzzzzzzzzzzzzzzzf
                                        # =>This Inner Loop Header: Depth=1
	movq	40(%rsp), %r13          # 8-byte Reload
	movq	48(%rsp), %rax          # 8-byte Reload
	subl	%eax, %r13d
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	72(%rsp), %edx          # 4-byte Reload
	movq	%rbx, %rcx
	movq	56(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	movq	(%rax), %rcx
	movq	%rcx, 24(%rsp)          # 8-byte Spill
	movl	8(%rax), %eax
	cmpl	%r13d, %r14d
	jge	.LBB9_32
# BB#27:                                # %entry_condend105
                                        #   in Loop: Header=BB9_26 Depth=1
	testl	%eax, %eax
	je	.LBB9_2
# BB#28:                                # %entry_ifend109
                                        #   in Loop: Header=BB9_26 Depth=1
	movl	$6628, %esi             # imm = 0x19E4
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	movq	%r14, %r9
	testq	%rax, %rax
	je	.LBB9_2
# BB#29:                                # %entry_ifend117
                                        #   in Loop: Header=BB9_26 Depth=1
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, %rsi
	leal	(%rsi,%r9), %ecx
	movq	64(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%r15, (%rdx)
	movq	$0, 8(%rdx)
	movq	%rsi, 8(%rdx)
	movq	$0, 16(%rdx)
	movq	40(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 16(%rdx)
	movq	$0, 24(%rdx)
	movq	56(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 24(%rdx)
	movq	$0, 32(%rdx)
	movq	%r9, 32(%rdx)
	movq	(%rbp), %rdx
	movq	$0, (%rdx)
	movl	%r15d, %esi
	movq	%rsi, (%rdx)
	movq	(%rbp), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%rbp)
	movq	$0, 8(%rdx)
	movl	%ecx, %ecx
	movq	%rcx, 8(%rdx)
	addq	$8, (%rbp)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	72(%rsp), %r14d         # 4-byte Reload
	movl	%r14d, %ecx
	movq	%rbp, %r8
	movq	32(%rsp), %rbx          # 8-byte Reload
	movq	%r9, %r15
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB9_24
# BB#30:                                # %entry_ifend137
                                        #   in Loop: Header=BB9_26 Depth=1
	movq	(%r12), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	8(%r12), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	16(%r12), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	24(%r12), %rax
	movq	%rax, 56(%rsp)          # 8-byte Spill
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	%rbx, %r13
	movq	32(%r12), %rbx
	movq	$0, 112(%rsp)
	movq	%rbx, 112(%rsp)
	movq	(%rbp), %rax
	movq	%r15, 8(%rsp)           # 8-byte Spill
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%r15, (%rsp)
	movq	16(%rsp), %r15          # 8-byte Reload
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB9_31
	jmp	.LBB9_2
.LBB9_24:                               # %then_block84
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB9_2:                                # %then_block
	xorl	%eax, %eax
.LBB9_3:                                # %then_block
	addq	$136, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB9_32:                               # %label_for_endzzzzzzzzzzzzzzzzzf
	testl	%eax, %eax
	je	.LBB9_2
# BB#33:                                # %entry_ifend164
	movq	$0, (%rsp)
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	72(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	24(%rsp), %r8           # 8-byte Reload
	movl	%r14d, %r9d
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB9_2
# BB#34:                                # %entry_ifend168
	movl	$0, gSigInt(%rip)
	movl	%r13d, %r9d
	movl	$2, (%rsp)
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	72(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	56(%rsp), %r8           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB9_2
# BB#35:                                # %entry_ifend175
	movl	$0, gSigInt(%rip)
	incl	%r13d
	movl	$1, (%rsp)
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	72(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	56(%rsp), %r8           # 8-byte Reload
	movq	%r13, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB9_2
# BB#36:                                # %entry_ifend183
	movl	$0, gSigInt(%rip)
	movq	56(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	jmp	.LBB9_37
.Lfunc_end9:
	.size	"String.subString(int,int)$$13", .Lfunc_end9-"String.subString(int,int)$$13"
	.cfi_endproc

	.globl	"String.equals(Self)$$14"
	.align	16, 0x90
	.type	"String.equals(Self)$$14",@function
"String.equals(Self)$$14":              # @"String.equals(Self)$$14"
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
	movl	%r9d, %eax
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %r13
	movq	%rdx, %r12
	movq	%rsi, %rbp
	movq	(%r13), %rbx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movq	8(%r13), %r14
	movq	$0, 40(%rsp)
	movq	%r14, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r13, %rsi
	movl	%eax, %edx
	movq	%r12, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#3:                                 # %entry_ifend
	movq	112(%rsp), %rdi
	movq	(%rax), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movl	$6704, %esi             # imm = 0x1A30
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB10_1
# BB#4:                                 # %entry_ifend5
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	$0, 8(%rbp)
	movq	%r14, 8(%rbp)
	movq	$0, 16(%rbp)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %r14
	je	.LBB10_6
# BB#5:                                 # %then_block14
	movq	%r12, %rdi
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
.LBB10_6:                               # %entry_ifend15
	movq	%r12, %rbp
	movq	(%r13), %r12
	movq	%r12, 8(%rsp)           # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%r12, 32(%rsp)
	movq	8(%r13), %r15
	movq	$0, 40(%rsp)
	movq	%r15, 40(%rsp)
	movq	16(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movq	24(%rsp), %rax          # 8-byte Reload
	cmpl	%ebx, %eax
	jne	.LBB10_16
# BB#7:                                 # %entry_condend
	movq	%r15, (%rsp)            # 8-byte Spill
	movq	$0, 48(%rsp)
	xorl	%eax, %eax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	%rbp, %rbx
	movl	20(%rsp), %ebp          # 4-byte Reload
	jmp	.LBB10_8
	.align	16, 0x90
.LBB10_19:                              # %label_if_endzzzzzzzzzzzzzzzzzi
                                        #   in Loop: Header=BB10_8 Depth=1
	movq	24(%rsp), %rax          # 8-byte Reload
	incl	%eax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movl	%r14d, %ebp
	movq	%rcx, %rbx
	movq	%r15, %r14
	movq	8(%rsp), %r12           # 8-byte Reload
.LBB10_8:                               # %for_start_pointzzzzzzzzzzzzzzzzzh
                                        # =>This Inner Loop Header: Depth=1
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%r13, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#9:                                 # %entry_ifend28
                                        #   in Loop: Header=BB10_8 Depth=1
	movq	%r14, %r15
	movl	%ebp, %r14d
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	movq	24(%rsp), %rsi          # 8-byte Reload
	cmpl	%eax, %esi
	jge	.LBB10_18
# BB#10:                                # %entry_condend31
                                        #   in Loop: Header=BB10_8 Depth=1
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%rbx, %rbp
	movq	%rbp, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#11:                                # %entry_ifend35
                                        #   in Loop: Header=BB10_8 Depth=1
	movq	(%rax), %r8
	movq	%r15, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#12:                                # %entry_ifend39
                                        #   in Loop: Header=BB10_8 Depth=1
	movq	(%rax), %r12
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	movq	(%rsp), %r8             # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#13:                                # %entry_ifend43
                                        #   in Loop: Header=BB10_8 Depth=1
	movq	(%rax), %r8
	movq	%r15, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#14:                                # %entry_ifend48
                                        #   in Loop: Header=BB10_8 Depth=1
	movq	%rbp, %rcx
	movq	(%rax), %rax
	cmpl	%eax, %r12d
	je	.LBB10_19
# BB#15:                                # %entry_condend51
	movl	$0, gSigInt(%rip)
.LBB10_16:                              # %label_elsezzzzzzzzzzzzzzzzzg
	movq	$0, (%r13)
	movl	$1, %eax
	jmp	.LBB10_2
.LBB10_18:                              # %label_for_endzzzzzzzzzzzzzzzzzh
	movq	$1, (%r13)
	movl	$1, %eax
	jmp	.LBB10_2
.Lfunc_end10:
	.size	"String.equals(Self)$$14", .Lfunc_end10-"String.equals(Self)$$14"
	.cfi_endproc

	.globl	"String.getHashKey()$$15"
	.align	16, 0x90
	.type	"String.getHashKey()$$15",@function
"String.getHashKey()$$15":              # @"String.getHashKey()$$15"
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
	movl	%r9d, %r14d
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %r13
	movq	(%rbx), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 24(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 32(%rsp)
	movq	$1, 32(%rsp)
	movl	$1, %ebp
	xorl	%r12d, %r12d
	jmp	.LBB11_1
	.align	16, 0x90
.LBB11_7:                               # %entry_ifend10
                                        #   in Loop: Header=BB11_1 Depth=1
	movq	(%rax), %rax
	addl	%eax, %r12d
	movq	$0, 24(%rsp)
	movq	%r12, 24(%rsp)
	incl	%ebp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
.LBB11_1:                               # %for_start_pointzzzzzzzzzzzzzzzzzj
                                        # =>This Inner Loop Header: Depth=1
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_2
# BB#4:                                 # %entry_ifend
                                        #   in Loop: Header=BB11_1 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %ebp
	jge	.LBB11_8
# BB#5:                                 # %entry_condend
                                        #   in Loop: Header=BB11_1 Depth=1
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movq	8(%rsp), %r8            # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_2
# BB#6:                                 # %entry_ifend6
                                        #   in Loop: Header=BB11_1 Depth=1
	movq	(%rax), %r8
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movl	%ebp, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	jne	.LBB11_7
.LBB11_2:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB11_3
.LBB11_8:                               # %label_for_endzzzzzzzzzzzzzzzzzj
	movl	%r12d, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
.LBB11_3:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end11:
	.size	"String.getHashKey()$$15", .Lfunc_end11-"String.getHashKey()$$15"
	.cfi_endproc

	.globl	"String.toString()$$16"
	.align	16, 0x90
	.type	"String.toString()$$16",@function
"String.toString()$$16":                # @"String.toString()$$16"
	.cfi_startproc
# BB#0:                                 # %entry
	movq	(%rcx), %rax
	movq	$0, -8(%rsp)
	movq	%rax, -8(%rsp)
	movl	$0, gSigInt(%rip)
	movl	%eax, %eax
	movq	%rax, (%rcx)
	movl	$1, %eax
	retq
.Lfunc_end12:
	.size	"String.toString()$$16", .Lfunc_end12-"String.toString()$$16"
	.cfi_endproc

	.globl	"String.printf(Self)$$17"
	.align	16, 0x90
	.type	"String.printf(Self)$$17",@function
"String.printf(Self)$$17":              # @"String.printf(Self)$$17"
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
	movl	%r9d, %ebx
	movl	%ebx, 28(%rsp)          # 4-byte Spill
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, %rbp
	movq	%rbp, 32(%rsp)          # 8-byte Spill
	movq	%rsi, 16(%rsp)          # 8-byte Spill
	movq	112(%rsp), %rdx
	movq	(%r14), %r15
	movq	$0, 40(%rsp)
	movq	%r15, 40(%rsp)
	movq	8(%r14), %r12
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movq	(%r13), %rax
	movq	$0, (%rax)
	movl	%r15d, %ecx
	movq	%rcx, (%rax)
	addq	$8, (%r13)
	movq	%rdx, (%rsp)
	movl	$1, %r8d
	movl	$7240, %r9d             # imm = 0x1C48
	movq	%r13, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	run_create_carray
	cmpl	$0, 8(%rax)
	je	.LBB13_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$7248, %esi             # imm = 0x1C50
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB13_1
# BB#4:                                 # %entry_ifend6
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	addq	$8, (%r13)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB13_6
# BB#5:                                 # %then_block18
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB13_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB13_2
.LBB13_6:                               # %entry_ifend19
	movq	(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, (%r14)
	movl	$1, %eax
.LBB13_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end13:
	.size	"String.printf(Self)$$17", .Lfunc_end13-"String.printf(Self)$$17"
	.cfi_endproc

	.globl	"String.print()$$18"
	.align	16, 0x90
	.type	"String.print()$$18",@function
"String.print()$$18":                   # @"String.print()$$18"
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
	pushq	%rax
.Ltmp165:
	.cfi_def_cfa_offset 64
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
	movl	%r9d, %r12d
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %rbp
	movq	64(%rsp), %rdi
	movq	(%r14), %rbx
	movq	$0, (%rsp)
	movq	%rbx, (%rsp)
	movl	$0, gSigInt(%rip)
	movl	$7256, %esi             # imm = 0x1C58
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB14_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB14_5
# BB#4:                                 # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB14_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB14_2
.LBB14_5:                               # %entry_ifend6
	movq	(%r14), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, (%r14)
	movl	$1, %eax
.LBB14_2:                               # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end14:
	.size	"String.print()$$18", .Lfunc_end14-"String.print()$$18"
	.cfi_endproc

	.globl	"String.println()$$19"
	.align	16, 0x90
	.type	"String.println()$$19",@function
"String.println()$$19":                 # @"String.println()$$19"
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
	pushq	%rax
.Ltmp178:
	.cfi_def_cfa_offset 64
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
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %rbp
	movq	64(%rsp), %rdi
	movq	(%r14), %rbx
	movq	$0, (%rsp)
	movq	%rbx, (%rsp)
	movl	$0, gSigInt(%rip)
	movl	$7264, %esi             # imm = 0x1C60
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB15_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB15_5
# BB#4:                                 # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB15_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB15_2
.LBB15_5:                               # %entry_ifend6
	movq	(%r14), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, (%r14)
	movl	$1, %eax
.LBB15_2:                               # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end15:
	.size	"String.println()$$19", .Lfunc_end15-"String.println()$$19"
	.cfi_endproc

	.globl	"String.match(regex)$$20"
	.align	16, 0x90
	.type	"String.match(regex)$$20",@function
"String.match(regex)$$20":              # @"String.match(regex)$$20"
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
	subq	$120, %rsp
.Ltmp191:
	.cfi_def_cfa_offset 176
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
	movl	%r9d, 52(%rsp)          # 4-byte Spill
	movq	%r8, 40(%rsp)           # 8-byte Spill
	movq	%rcx, %r15
	movq	%rdx, 56(%rsp)          # 8-byte Spill
	movq	%rsi, %r13
	movq	176(%rsp), %r14
	movq	(%r15), %rbp
	movq	$0, 64(%rsp)
	movq	%rbp, 64(%rsp)
	movq	8(%r15), %rbx
	movq	$0, 72(%rsp)
	movq	%rbx, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 80(%rsp)
	movq	$16, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$7272, %esi             # imm = 0x1C68
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB16_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$7284, %esi             # imm = 0x1C74
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB16_1
# BB#4:                                 # %entry_ifend4
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	$0, 8(%r13)
	movq	%rbx, 8(%r13)
	movq	$0, 16(%r13)
	movq	$16, 16(%r13)
	movq	$0, 24(%r13)
	movq	$0, 32(%r13)
	movq	$0, 40(%r13)
	movq	$0, 48(%r13)
	movq	40(%rsp), %rbp          # 8-byte Reload
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movq	$16, 8(%rcx)
	addq	$8, (%rbp)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	56(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB16_5
# BB#6:                                 # %entry_ifend25
	movq	(%r15), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r15), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r15), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r15), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r15), %r14
	movq	$0, 104(%rsp)
	movq	%r14, 104(%rsp)
	movq	48(%r15), %rbx
	movq	$0, 112(%rsp)
	movq	%rbx, 112(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 88(%rsp)
	movq	%r12, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$7296, %esi             # imm = 0x1C80
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB16_1
# BB#7:                                 # %entry_ifend45
	movq	$0, (%r13)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%r13)
	movq	$0, 8(%r13)
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%r13)
	movq	$0, 16(%r13)
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 16(%r13)
	movq	$0, 24(%r13)
	movq	%r12, 24(%r13)
	movq	$0, 32(%r13)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, 32(%r13)
	movq	$0, 40(%r13)
	movq	%r14, 40(%r13)
	movq	$0, 48(%r13)
	movq	%rbx, 48(%r13)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbp)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	56(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB16_5
# BB#8:                                 # %entry_ifend66
	movq	(%r15), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r15), %r12
	movq	$0, 72(%rsp)
	movq	%r12, 72(%rsp)
	movq	16(%r15), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r15), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r15), %r14
	movq	$0, 112(%rsp)
	movq	%r14, 112(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 96(%rsp)
	movq	%rbx, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$7304, %esi             # imm = 0x1C88
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB16_1
# BB#9:                                 # %entry_ifend94
	movq	$0, (%r13)
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r13)
	movq	$0, 8(%r13)
	movq	%r12, 8(%r13)
	movq	$0, 16(%r13)
	movq	24(%rsp), %rdi          # 8-byte Reload
	movq	%rdi, 16(%r13)
	movq	$0, 24(%r13)
	movq	32(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 24(%r13)
	movq	$0, 32(%r13)
	movq	%rbx, 32(%r13)
	movq	$0, 40(%r13)
	movq	$0, 48(%r13)
	movq	%r14, 48(%r13)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%edi, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$25, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	56(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB16_10
.LBB16_5:                               # %then_block24
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB16_1:                               # %then_block
	xorl	%eax, %eax
.LBB16_2:                               # %then_block
	addq	$120, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB16_10:                              # %entry_ifend127
	movq	(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 112(%rsp)
	movq	%rbx, 112(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%ebx, %ebx
	setg	%al
	movzbl	%al, %eax
	movq	%rax, (%r15)
	movl	$1, %eax
	jmp	.LBB16_2
.Lfunc_end16:
	.size	"String.match(regex)$$20", .Lfunc_end16-"String.match(regex)$$20"
	.cfi_endproc

	.globl	"String.match(regex,EqualableList)$$21"
	.align	16, 0x90
	.type	"String.match(regex,EqualableList)$$21",@function
"String.match(regex,EqualableList)$$21": # @"String.match(regex,EqualableList)$$21"
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
	subq	$136, %rsp
.Ltmp204:
	.cfi_def_cfa_offset 192
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
	movl	%r9d, 36(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rdx, 24(%rsp)          # 8-byte Spill
	movq	%rsi, %r12
	movq	192(%rsp), %rbp
	movq	(%rcx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%rcx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%rcx), %rax
	movq	%rcx, %r14
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	$0, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 64(%rsp)
	movq	$16, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$7312, %esi             # imm = 0x1C90
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB17_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	64(%rsp), %r13d
	movl	$7324, %esi             # imm = 0x1C9C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB17_1
# BB#4:                                 # %entry_ifend6
	movq	40(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%r15, %r13
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %r15
	movq	%r15, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	24(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB17_5
# BB#6:                                 # %entry_ifend33
	movq	(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	64(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	72(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%r13, %rbp
	movq	$0, 72(%rsp)
	movq	%rbx, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r13d
	movl	$7336, %esi             # imm = 0x1CA8
	movq	192(%rsp), %rbx
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB17_1
# BB#7:                                 # %entry_ifend59
	movq	40(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rbp, %r13
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB17_5
# BB#8:                                 # %entry_ifend86
	movq	(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	64(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	72(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	(%r13), %rax
	movq	%r13, %rbp
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 80(%rsp)
	movq	%r13, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r14d
	movl	64(%rsp), %eax
	movl	%eax, 8(%rsp)           # 4-byte Spill
	movl	72(%rsp), %eax
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movl	$7344, %esi             # imm = 0x1CB0
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB17_1
# BB#9:                                 # %entry_ifend120
	movq	40(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rbp, %r13
	movq	%rdx, 8(%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$25, %esi
	movq	%rax, %rdi
	movq	%r15, %rbp
	movq	%rbp, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	24(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB17_5
# BB#10:                                # %entry_ifend159
	movq	(%rbp), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 96(%rsp)
	movq	%r15, 96(%rsp)
	movl	$0, gSigInt(%rip)
	cmpl	$1, %r15d
	sete	%al
	movq	$0, 120(%rsp)
	movzbl	%al, %eax
	movq	%rax, 120(%rsp)
	je	.LBB17_14
# BB#11:                                # %entry_condnotend
	cmpl	$0, 56(%rsp)
	sete	%al
	movq	$0, 128(%rsp)
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
	jne	.LBB17_13
# BB#12:                                # %entry_condend
	testl	%r15d, %r15d
	setg	%al
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
.LBB17_13:                              # %label_and_endpointzzzzzzzzzzzzzzzzzm
	movq	%rax, 120(%rsp)
.LBB17_14:                              # %label_or_endpointzzzzzzzzzzzzzzzzzl
	testq	%rax, %rax
	je	.LBB17_17
# BB#15:                                # %entry_condend195
	movl	$0, gSigInt(%rip)
.LBB17_16:                              # %label_for_endzzzzzzzzzzzzzzzzzn
	movq	$1, (%rbp)
	movl	$1, %eax
	jmp	.LBB17_2
.LBB17_17:                              # %label_elifzzzzzzzzzzzzzzzzzk1a
	movl	$0, gSigInt(%rip)
	cmpl	$2, %r15d
	jl	.LBB17_31
# BB#18:                                # %entry_condend201
	movq	$0, 104(%rsp)
	movq	$1, 104(%rsp)
	movl	$1, %eax
	jmp	.LBB17_19
.LBB17_30:                              # %entry_ifend377
                                        #   in Loop: Header=BB17_19 Depth=1
	movq	(%rbp), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	104(%rsp), %eax
	incl	%eax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
.LBB17_19:                              # %for_start_pointzzzzzzzzzzzzzzzzzn
                                        # =>This Inner Loop Header: Depth=1
	movl	96(%rsp), %ecx
	movl	$0, gSigInt(%rip)
	cmpl	%ecx, %eax
	jge	.LBB17_16
# BB#20:                                # %entry_condend206
                                        #   in Loop: Header=BB17_19 Depth=1
	movl	80(%rsp), %eax
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movl	72(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movq	%rbp, %r15
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	192(%rsp), %rbx
	je	.LBB17_1
# BB#21:                                # %entry_ifend211
                                        #   in Loop: Header=BB17_19 Depth=1
	movq	(%rax), %r8
	movl	104(%rsp), %r9d
	movq	%r13, %rdi
	movq	%r15, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	%r14, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB17_1
# BB#22:                                # %entry_ifend215
                                        #   in Loop: Header=BB17_19 Depth=1
	movq	(%rax), %rbp
	movl	72(%rsp), %r8d
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%r15, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB17_1
# BB#23:                                # %entry_ifend219
                                        #   in Loop: Header=BB17_19 Depth=1
	movq	(%rax), %r8
	movl	104(%rsp), %r9d
	movq	%r13, %rdi
	movq	%r15, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	%r14, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB17_1
# BB#24:                                # %entry_ifend224
                                        #   in Loop: Header=BB17_19 Depth=1
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$7704, %esi             # imm = 0x1E18
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB17_1
# BB#25:                                # %entry_ifend227
                                        #   in Loop: Header=BB17_19 Depth=1
	movq	40(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	%rbp, %rsi
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB17_5
# BB#26:                                # %entry_ifend260
                                        #   in Loop: Header=BB17_19 Depth=1
	movq	(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	64(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	72(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	(%r13), %rax
	movq	%r13, %rbp
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$7712, %esi             # imm = 0x1E20
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB17_1
# BB#27:                                # %entry_ifend289
                                        #   in Loop: Header=BB17_19 Depth=1
	movq	40(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	%rbp, %r13
	addq	$8, (%r13)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB17_5
# BB#28:                                # %entry_ifend316
                                        #   in Loop: Header=BB17_19 Depth=1
	movq	(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	48(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	56(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	64(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	72(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	(%r13), %rax
	movq	%r13, %rbp
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 112(%rsp)
	movq	%r13, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r14d
	movl	$7720, %esi             # imm = 0x1E28
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB17_1
# BB#29:                                # %entry_ifend347
                                        #   in Loop: Header=BB17_19 Depth=1
	movq	40(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	48(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	56(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rbp, %r13
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r15, %rbp
	movq	%rbp, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	24(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB17_30
.LBB17_5:                               # %then_block32
	movq	%r14, %rdi
	callq	get_try_catch_label_name
.LBB17_1:                               # %then_block
	xorl	%eax, %eax
.LBB17_2:                               # %then_block
	addq	$136, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB17_31:                              # %label_if_elifzzzzzzzzzzzzzzzzzk0a
	movq	$0, (%rbp)
	movl	$1, %eax
	jmp	.LBB17_2
.Lfunc_end17:
	.size	"String.match(regex,EqualableList)$$21", .Lfunc_end17-"String.match(regex,EqualableList)$$21"
	.cfi_endproc

	.globl	"String.sub(regex,Self,EqualableList)$$22"
	.align	16, 0x90
	.type	"String.sub(regex,Self,EqualableList)$$22",@function
"String.sub(regex,Self,EqualableList)$$22": # @"String.sub(regex,Self,EqualableList)$$22"
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
	subq	$168, %rsp
.Ltmp217:
	.cfi_def_cfa_offset 224
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
	movl	%r9d, 44(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %r14
	movq	%rsi, %rbp
	movq	224(%rsp), %r13
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movq	$0, 120(%rsp)
	movq	$0, 128(%rsp)
	movq	$0, 136(%rsp)
	movq	$0, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$7968, %esi             # imm = 0x1F20
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$7976, %esi             # imm = 0x1F28
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#4:                                 # %entry_ifend7
	movq	48(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	%rbp, 32(%rsp)          # 8-byte Spill
	movq	%r15, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbp)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movq	%rbx, %r15
	movl	44(%rsp), %r12d         # 4-byte Reload
	movq	%rbp, %r13
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_5
# BB#6:                                 # %entry_ifend37
	movl	%r12d, %ebp
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 80(%rsp)
	movq	%rbx, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %ebx
	movl	$7984, %esi             # imm = 0x1F30
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	32(%rsp), %r12          # 8-byte Reload
	je	.LBB18_1
# BB#7:                                 # %entry_ifend69
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebp, %ecx
	movq	%r13, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB18_8
.LBB18_5:                               # %then_block36
	movq	%r14, %rdi
	callq	get_try_catch_label_name
.LBB18_1:                               # %then_block
	xorl	%eax, %eax
.LBB18_2:                               # %then_block
	addq	$168, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB18_8:                               # %entry_ifend102
	movq	%r14, 24(%rsp)          # 8-byte Spill
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%r13, %r14
	movq	$0, 96(%rsp)
	movq	%rbx, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 104(%rsp)
	movq	$16, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$7992, %esi             # imm = 0x1F38
	movq	224(%rsp), %rbx
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#9:                                 # %entry_ifend137
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	104(%rsp), %ebp
	movl	$8004, %esi             # imm = 0x1F44
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#10:                                # %entry_ifend141
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
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
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_11
# BB#12:                                # %entry_ifend177
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%r14, 16(%rsp)          # 8-byte Spill
	movq	$0, 112(%rsp)
	movq	%rbx, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movq	224(%rsp), %rbp
.LBB18_13:                              # %entry_condend
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB18_65 Depth 2
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r12d
	movl	96(%rsp), %r13d
	movl	88(%rsp), %r14d
	movl	104(%rsp), %eax
	movl	%eax, 8(%rsp)           # 4-byte Spill
	movl	112(%rsp), %ebx
	movl	$8084, %esi             # imm = 0x1F94
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#14:                                # %entry_ifend217
                                        #   in Loop: Header=BB18_13 Depth=1
	movl	%ebx, %edi
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	16(%rsp), %rsi          # 8-byte Reload
	movq	(%rsi), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%rsi), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rsi)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rsi, %rbp
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%edi, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$25, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %r13
	jne	.LBB18_11
# BB#15:                                # %entry_ifend262
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 120(%rsp)
	movq	%rbx, 120(%rsp)
	movl	$0, gSigInt(%rip)
	cmpl	$1, %ebx
	sete	%al
	movq	$0, 152(%rsp)
	movzbl	%al, %eax
	movq	%rax, 152(%rsp)
	je	.LBB18_19
# BB#16:                                # %entry_condnotend
                                        #   in Loop: Header=BB18_13 Depth=1
	cmpl	$0, 72(%rsp)
	sete	%al
	movq	$0, 160(%rsp)
	movzbl	%al, %eax
	movq	%rax, 160(%rsp)
	jne	.LBB18_18
# BB#17:                                # %entry_condend302
                                        #   in Loop: Header=BB18_13 Depth=1
	testl	%ebx, %ebx
	setg	%al
	movzbl	%al, %eax
	movq	%rax, 160(%rsp)
.LBB18_18:                              # %label_and_endpointzzzzzzzzzzzzzzzzzr
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	%rax, 152(%rsp)
.LBB18_19:                              # %label_or_endpointzzzzzzzzzzzzzzzzzq
                                        #   in Loop: Header=BB18_13 Depth=1
	testq	%rax, %rax
	je	.LBB18_49
# BB#20:                                # %entry_condend307
                                        #   in Loop: Header=BB18_13 Depth=1
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %ebp
	movl	88(%rsp), %r15d
	movl	112(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r13, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %r14
	je	.LBB18_1
# BB#21:                                # %entry_ifend313
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r13, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#22:                                # %entry_ifend316
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%rax), %rbx
	movl	$8276, %esi             # imm = 0x2054
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#23:                                # %entry_ifend319
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	%r14, %r12
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	16(%rsp), %r14          # 8-byte Reload
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	44(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_11
# BB#24:                                # %entry_ifend358
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$8284, %esi             # imm = 0x205C
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#25:                                # %entry_ifend393
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	48(%rsp), %rcx
	movq	32(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%rbx, %r15
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r13, %rbx
	jne	.LBB18_26
# BB#27:                                # %entry_ifend426
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbx, %r15
	movq	$0, 128(%rsp)
	movq	%r13, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %ebx
	movl	$8292, %esi             # imm = 0x2064
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#28:                                # %entry_ifend463
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_11
# BB#29:                                # %entry_ifend499
                                        #   in Loop: Header=BB18_13 Depth=1
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%r14, %r13
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %r12d
	movl	64(%rsp), %r14d
	movl	$8300, %esi             # imm = 0x206C
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#30:                                # %entry_ifend536
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%r13, %rbx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebp, %r12d
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	24(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_31
# BB#32:                                # %entry_ifend572
                                        #   in Loop: Header=BB18_13 Depth=1
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %r14d
	movl	112(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r15, %rsi
	movl	%r12d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %rbx
	je	.LBB18_1
# BB#33:                                # %entry_ifend609
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#34:                                # %entry_ifend613
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r14d
	jne	.LBB18_40
# BB#35:                                # %entry_condend617
                                        #   in Loop: Header=BB18_13 Depth=1
	movl	88(%rsp), %eax
	incl	%eax
	movq	$0, 88(%rsp)
	jmp	.LBB18_36
.LBB18_49:                              # %label_elifzzzzzzzzzzzzzzzzzp1a
                                        #   in Loop: Header=BB18_13 Depth=1
	cmpl	$1, %ebx
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %eax
	movl	%eax, 4(%rsp)           # 4-byte Spill
	movl	88(%rsp), %eax
	movl	%eax, 8(%rsp)           # 4-byte Spill
	jle	.LBB18_87
# BB#50:                                # %entry_condend857
                                        #   in Loop: Header=BB18_13 Depth=1
	movl	112(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r13, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %rbp
	je	.LBB18_1
# BB#51:                                # %entry_ifend863
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r13, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#52:                                # %entry_ifend867
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%rax), %rbx
	movl	$8720, %esi             # imm = 0x2210
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#53:                                # %entry_ifend870
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	%rbp, %r12
	movq	48(%rsp), %rcx
	movq	32(%rsp), %r15          # 8-byte Reload
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	16(%rsp), %r14          # 8-byte Reload
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	4(%rsp), %edx           # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_11
# BB#54:                                # %entry_ifend909
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%r14), %rax
	movq	%r13, %rbp
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$8728, %esi             # imm = 0x2218
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#55:                                # %entry_ifend944
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	%r14, %r13
	addq	$8, (%r13)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_11
# BB#56:                                # %entry_ifend977
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	%rbp, %r14
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 128(%rsp)
	movq	%rbp, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %ebx
	movl	$8736, %esi             # imm = 0x2220
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#57:                                # %entry_ifend1014
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
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
	movq	%r14, %rdx
	movl	44(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r13, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_11
# BB#58:                                # %entry_ifend1050
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %r12d
	movl	64(%rsp), %ebx
	movl	$8744, %esi             # imm = 0x2228
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#59:                                # %entry_ifend1087
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%r13, %rbx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebp, %r15d
	movl	%r15d, %ecx
	movq	%rbx, %r8
	movq	24(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_31
# BB#60:                                # %entry_ifend1123
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movq	%r14, %rbp
	movl	88(%rsp), %r14d
	movl	112(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movl	%r15d, %r12d
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#61:                                # %entry_ifend1160
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%rbp, %rsi
	movl	%r12d, %edx
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#62:                                # %entry_ifend1164
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	%rbp, %r15
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r14d
	jne	.LBB18_77
# BB#63:                                # %entry_condend1168
                                        #   in Loop: Header=BB18_13 Depth=1
	movl	88(%rsp), %eax
	incl	%eax
	movq	$0, 88(%rsp)
	jmp	.LBB18_64
.LBB18_40:                              # %label_elsezzzzzzzzzzzzzzzzzs
                                        #   in Loop: Header=BB18_13 Depth=1
	movl	112(%rsp), %r8d
	movl	$1, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#41:                                # %entry_ifend623
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#42:                                # %entry_ifend627
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%rax), %rax
	movq	$0, 88(%rsp)
	movl	%eax, %eax
.LBB18_36:                              # %label_if_endzzzzzzzzzzzzzzzzzs
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	%rax, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %edi
	callq	get_regex_global
	testl	%eax, %eax
	movq	%rbx, %rbp
	jne	.LBB18_13
	jmp	.LBB18_37
.LBB18_77:                              # %label_elsezzzzzzzzzzzzzzzzzu
                                        #   in Loop: Header=BB18_13 Depth=1
	movl	112(%rsp), %r8d
	movl	$1, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r15, %rsi
	movl	%r12d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#78:                                # %entry_ifend1176
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r15, %rsi
	movl	%r12d, %edx
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#79:                                # %entry_ifend1180
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	(%rax), %rax
	movq	$0, 88(%rsp)
	movl	%eax, %eax
.LBB18_64:                              # %label_if_endzzzzzzzzzzzzzzzzzu
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	%rax, 88(%rsp)
	movl	%r12d, %ebp
	movl	$0, gSigInt(%rip)
	movq	$0, 136(%rsp)
	movq	$1, 136(%rsp)
	movl	$1, %eax
	movq	16(%rsp), %rbx          # 8-byte Reload
	jmp	.LBB18_65
.LBB18_76:                              # %entry_ifend1388
                                        #   in Loop: Header=BB18_65 Depth=2
	movq	(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r12), %rax
	movq	%r12, %r15
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	136(%rsp), %eax
	incl	%eax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
.LBB18_65:                              # %for_start_pointzzzzzzzzzzzzzzzzzv
                                        #   Parent Loop BB18_13 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	120(%rsp), %ecx
	movl	$0, gSigInt(%rip)
	cmpl	%ecx, %eax
	jge	.LBB18_80
# BB#66:                                # %entry_condend1186
                                        #   in Loop: Header=BB18_65 Depth=2
	movl	96(%rsp), %r12d
	movl	112(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %rbp
	je	.LBB18_1
# BB#67:                                # %entry_ifend1191
                                        #   in Loop: Header=BB18_65 Depth=2
	movq	(%rax), %r8
	movl	136(%rsp), %r9d
	movq	%rbx, %rdi
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#68:                                # %entry_ifend1196
                                        #   in Loop: Header=BB18_65 Depth=2
	movq	(%rax), %r14
	movl	112(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#69:                                # %entry_ifend1200
                                        #   in Loop: Header=BB18_65 Depth=2
	movq	(%rax), %r8
	movl	136(%rsp), %r9d
	movq	%rbx, %rdi
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#70:                                # %entry_ifend1205
                                        #   in Loop: Header=BB18_65 Depth=2
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$8980, %esi             # imm = 0x2314
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#71:                                # %entry_ifend1208
                                        #   in Loop: Header=BB18_65 Depth=2
	movl	%r12d, %esi
	movq	%rbp, %r12
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	%rbx, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%esi, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_31
# BB#72:                                # %entry_ifend1247
                                        #   in Loop: Header=BB18_65 Depth=2
	movq	%r13, %rbx
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$8988, %esi             # imm = 0x231C
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%r15, %r12
	je	.LBB18_1
# BB#73:                                # %entry_ifend1282
                                        #   in Loop: Header=BB18_65 Depth=2
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	%rdx, %r15
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	%rbp, %r14
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	44(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_11
# BB#74:                                # %entry_ifend1315
                                        #   in Loop: Header=BB18_65 Depth=2
	movq	(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 144(%rsp)
	movq	%r13, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movl	72(%rsp), %ebx
	movl	$8996, %esi             # imm = 0x2324
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#75:                                # %entry_ifend1352
                                        #   in Loop: Header=BB18_65 Depth=2
	movq	48(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%r14, %rbx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebp, %ecx
	movq	%rbx, %r8
	movq	24(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB18_76
	jmp	.LBB18_31
.LBB18_80:                              # %label_for_endzzzzzzzzzzzzzzzzzv
                                        #   in Loop: Header=BB18_13 Depth=1
	movq	%rbx, 16(%rsp)          # 8-byte Spill
	movl	%ebp, 44(%rsp)          # 4-byte Spill
	movq	%r13, 24(%rsp)          # 8-byte Spill
	movl	56(%rsp), %edi
	callq	get_regex_global
	testl	%eax, %eax
	movq	224(%rsp), %rbp
	jne	.LBB18_13
# BB#81:                                # %entry_condend1429
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %ebx
	movl	88(%rsp), %r12d
	movl	$9112, %esi             # imm = 0x2398
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%r15, %rdx
	je	.LBB18_1
# BB#82:                                # %entry_ifend1434
	movq	%rbp, %r14
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rsi          # 8-byte Reload
	movq	$0, (%rsi)
	movq	%rcx, (%rsi)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rsi)
	movq	%rcx, 8(%rsi)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rsi)
	movq	%rcx, 16(%rsi)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rsi)
	movq	%rcx, 24(%rsi)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rsi)
	movq	%rcx, 32(%rsi)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rsi)
	movq	%rcx, 40(%rsi)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rsi)
	movq	%rcx, 48(%rsi)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rsi)
	movq	%rcx, 56(%rsi)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rsi)
	movq	%rcx, 64(%rsi)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rsi)
	movq	%rcx, 72(%rsi)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rsi)
	movq	%rcx, 80(%rsi)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rsi)
	movq	%rcx, 88(%rsi)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rsi)
	movq	%rcx, 96(%rsi)
	movq	%rsi, %r15
	movq	16(%rsp), %r8           # 8-byte Reload
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %esi
	movq	%rsi, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rsi
	movq	%rsi, (%r8)
	movq	$0, 8(%rcx)
	movl	%r12d, %esi
	movq	%rsi, 8(%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rsi
	movq	%rsi, (%r8)
	movq	$0, 8(%rcx)
	movl	$4294967295, %esi       # imm = 0xFFFFFFFF
	movq	%rsi, 8(%rcx)
	addq	$8, (%r8)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%rdx, %r12
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r8, %rbx
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_39
# BB#83:                                # %entry_ifend1473
	movq	%r12, %rbp
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rbp), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rbp), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$9120, %esi             # imm = 0x23A0
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#84:                                # %entry_ifend1508
	movq	%r14, %r12
	movq	48(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	%rbx, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r8)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_39
# BB#85:                                # %entry_ifend1541
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rbp), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rbp), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r14
	movq	$0, 144(%rsp)
	movq	%r13, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %ebx
	movl	$9128, %esi             # imm = 0x23A8
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#86:                                # %entry_ifend1578
	movq	48(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	%r14, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	jmp	.LBB18_47
.LBB18_31:                              # %then_block571
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB18_1
.LBB18_87:                              # %label_if_elifzzzzzzzzzzzzzzzzzp0a
	movl	$9332, %esi             # imm = 0x2474
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%r13, %r15
	je	.LBB18_1
# BB#88:                                # %entry_ifend1654
	movq	48(%rsp), %rcx
	movq	32(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	16(%rsp), %r14          # 8-byte Reload
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	4(%rsp), %edx           # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%r14, %rbp
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB18_89
.LBB18_11:                              # %then_block176
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB18_1
.LBB18_26:                              # %then_block425
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB18_1
.LBB18_37:                              # %entry_condend632
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %r13d
	movl	88(%rsp), %r14d
	movl	$8500, %esi             # imm = 0x2134
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%r15, %rbx
	je	.LBB18_1
# BB#38:                                # %entry_ifend637
	movq	%rbp, %r12
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	%rdx, %r15
	movq	16(%rsp), %rbp          # 8-byte Reload
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_39
# BB#43:                                # %entry_ifend676
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbp), %rax
	movq	%rbp, %r14
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$8508, %esi             # imm = 0x213C
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %rdx
	je	.LBB18_1
# BB#44:                                # %entry_ifend711
	movq	48(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%rdx, %r12
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_39
# BB#45:                                # %entry_ifend744
	movq	%r12, %rbp
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rbp), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rbp), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	%r14, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r12
	movq	$0, 136(%rsp)
	movq	%r14, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %ebx
	movl	$8516, %esi             # imm = 0x2144
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#46:                                # %entry_ifend781
	movq	48(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	%r12, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
.LBB18_47:                              # %entry_ifend781
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r8, %rbx
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_39
# BB#48:                                # %entry_ifend817
	movq	%rbp, %rcx
	movq	(%rcx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rcx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rcx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rcx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rcx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rcx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rcx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rcx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rcx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rcx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rcx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rcx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rcx), %rax
	movq	%rcx, %r14
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	jmp	.LBB18_94
.LBB18_89:                              # %entry_ifend1693
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$9340, %esi             # imm = 0x247C
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#90:                                # %entry_ifend1728
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	%r12, %r14
	movq	%rbp, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r8)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_39
# BB#91:                                # %entry_ifend1761
	movq	%r15, %rbx
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbp, %r12
	movq	$0, 128(%rsp)
	movq	%r13, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %ebp
	movl	$9348, %esi             # imm = 0x2484
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#92:                                # %entry_ifend1798
	movq	48(%rsp), %rcx
	movq	$0, (%r14)
	movq	%rcx, (%r14)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r14)
	movq	%rcx, 8(%r14)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r14)
	movq	%rcx, 16(%r14)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r14)
	movq	%rcx, 24(%r14)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r14)
	movq	%rcx, 32(%r14)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r14)
	movq	%rcx, 40(%r14)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r14)
	movq	%rcx, 48(%r14)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r14)
	movq	%rcx, 56(%r14)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r14)
	movq	%rcx, 64(%r14)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r14)
	movq	%rcx, 72(%r14)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r14)
	movq	%rcx, 80(%r14)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r14)
	movq	%rcx, 88(%r14)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r14)
	movq	%rcx, 96(%r14)
	movq	%r12, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r8, %rbp
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB18_93
.LBB18_39:                              # %then_block675
	movq	24(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
	jmp	.LBB18_1
.LBB18_93:                              # %entry_ifend1834
	movq	%rbx, %rcx
	movq	(%rcx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rcx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rcx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rcx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rcx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rcx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rcx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rcx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rcx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rcx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rcx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rcx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rcx), %rax
	movq	%rcx, %r14
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
.LBB18_94:                              # %label_whilezzzzzzzzzzzzzzzzzo
	movl	$0, gSigInt(%rip)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB18_2
.Lfunc_end18:
	.size	"String.sub(regex,Self,EqualableList)$$22", .Lfunc_end18-"String.sub(regex,Self,EqualableList)$$22"
	.cfi_endproc

	.globl	"String.sub(regex,Self)$$23"
	.align	16, 0x90
	.type	"String.sub(regex,Self)$$23",@function
"String.sub(regex,Self)$$23":           # @"String.sub(regex,Self)$$23"
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
	subq	$40, %rsp
.Ltmp230:
	.cfi_def_cfa_offset 96
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
	movq	%rdx, 8(%rsp)           # 8-byte Spill
	movq	%rsi, %rbp
	movq	96(%rsp), %rdi
	movq	(%r14), %r15
	movq	$0, 16(%rsp)
	movq	%r15, 16(%rsp)
	movq	8(%r14), %r12
	movq	$0, 24(%rsp)
	movq	%r12, 24(%rsp)
	movq	16(%r14), %r13
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$9520, %esi             # imm = 0x2530
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB19_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%r15, (%rbp)
	movq	$0, 8(%rbp)
	movq	%r12, 8(%rbp)
	movq	$0, 16(%rbp)
	movq	%r13, 16(%rbp)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
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
	movl	$22, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%rbx, %r8
	movq	8(%rsp), %rbp           # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB19_5
# BB#4:                                 # %then_block23
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB19_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB19_2
.LBB19_5:                               # %entry_ifend24
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r14), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbp, (%r14)
	movl	$1, %eax
.LBB19_2:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end19:
	.size	"String.sub(regex,Self)$$23", .Lfunc_end19-"String.sub(regex,Self)$$23"
	.cfi_endproc

	.globl	"String.sub(regex,lambda,EqualableList)$$24"
	.align	16, 0x90
	.type	"String.sub(regex,lambda,EqualableList)$$24",@function
"String.sub(regex,lambda,EqualableList)$$24": # @"String.sub(regex,lambda,EqualableList)$$24"
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
	subq	$184, %rsp
.Ltmp243:
	.cfi_def_cfa_offset 240
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
	movl	%r9d, 44(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %r14
	movq	%rsi, %r13
	movq	240(%rsp), %rbp
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movq	$0, 120(%rsp)
	movq	$0, 128(%rsp)
	movq	$0, 136(%rsp)
	movq	$0, 144(%rsp)
	movq	$0, 152(%rsp)
	movq	$0, 160(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$9528, %esi             # imm = 0x2538
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$9536, %esi             # imm = 0x2540
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#4:                                 # %entry_ifend7
	movq	48(%rsp), %rcx
	movq	%r13, 32(%rsp)          # 8-byte Spill
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r13)
	movq	%rcx, 64(%r13)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r13)
	movq	%rcx, 72(%r13)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r13)
	movq	%rcx, 80(%r13)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r13)
	movq	%rcx, 88(%r13)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r13)
	movq	%rcx, 96(%r13)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r13)
	movq	%rcx, 104(%r13)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r13)
	movq	%rcx, 112(%r13)
	movq	%r15, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbp)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	44(%rsp), %r12d         # 4-byte Reload
	movq	%rbp, %r13
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_5
# BB#6:                                 # %entry_ifend41
	movq	%r14, 24(%rsp)          # 8-byte Spill
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 80(%rsp)
	movq	%rbp, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %r14d
	movl	$9544, %esi             # imm = 0x2548
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r15
	je	.LBB20_1
# BB#7:                                 # %entry_ifend77
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 104(%rdx)
	movq	%rcx, 104(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 112(%rdx)
	movq	%rcx, 112(%rdx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_8
# BB#9:                                 # %entry_ifend114
	movl	%r12d, %ebp
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%r13, %r14
	movq	$0, 96(%rsp)
	movq	%rbx, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 104(%rsp)
	movq	$16, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$9552, %esi             # imm = 0x2550
	movq	240(%rsp), %rbx
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#10:                                # %entry_ifend153
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	104(%rsp), %r12d
	movl	$9564, %esi             # imm = 0x255C
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#11:                                # %entry_ifend157
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 104(%rdx)
	movq	%rcx, 104(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 112(%rdx)
	movq	%rcx, 112(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_8
# BB#12:                                # %entry_ifend197
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r15), %rax
	movq	%r15, %r12
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%r14, 16(%rsp)          # 8-byte Spill
	movq	$0, 112(%rsp)
	movq	%rbx, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movq	240(%rsp), %rbp
.LBB20_13:                              # %entry_condend
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB20_82 Depth 2
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %ebx
	movl	96(%rsp), %r13d
	movl	88(%rsp), %r14d
	movl	104(%rsp), %eax
	movl	%eax, (%rsp)            # 4-byte Spill
	movl	112(%rsp), %eax
	movl	%eax, 8(%rsp)           # 4-byte Spill
	movl	$9644, %esi             # imm = 0x25AC
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#14:                                # %entry_ifend241
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	%rbp, %r15
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 104(%rdx)
	movq	%rcx, 104(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 112(%rdx)
	movq	%rcx, 112(%rdx)
	movq	16(%rsp), %rsi          # 8-byte Reload
	movq	(%rsi), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%rsi), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rsi)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rsi, %rbp
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	(%rsp), %edx            # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$25, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_8
# BB#15:                                # %entry_ifend290
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbp, %r14
	movq	$0, 120(%rsp)
	movq	%rbx, 120(%rsp)
	movl	$0, gSigInt(%rip)
	cmpl	$1, %ebx
	sete	%al
	movq	$0, 168(%rsp)
	movzbl	%al, %eax
	movq	%rax, 168(%rsp)
	je	.LBB20_19
# BB#16:                                # %entry_condnotend
                                        #   in Loop: Header=BB20_13 Depth=1
	cmpl	$0, 72(%rsp)
	sete	%al
	movq	$0, 176(%rsp)
	movzbl	%al, %eax
	movq	%rax, 176(%rsp)
	jne	.LBB20_18
# BB#17:                                # %entry_condend334
                                        #   in Loop: Header=BB20_13 Depth=1
	testl	%ebx, %ebx
	setg	%al
	movzbl	%al, %eax
	movq	%rax, 176(%rsp)
.LBB20_18:                              # %label_and_endpointzzzzzzzzzzzzzzzzzzb
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	%rax, 168(%rsp)
.LBB20_19:                              # %label_or_endpointzzzzzzzzzzzzzzzzzz
                                        #   in Loop: Header=BB20_13 Depth=1
	testq	%rax, %rax
	je	.LBB20_61
# BB#20:                                # %entry_condend339
                                        #   in Loop: Header=BB20_13 Depth=1
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %r13d
	movl	88(%rsp), %eax
	movl	%eax, 8(%rsp)           # 4-byte Spill
	movl	112(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r12, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r15, %rbp
	je	.LBB20_1
# BB#21:                                # %entry_ifend345
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r12, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#22:                                # %entry_ifend348
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %rbx
	movl	$9836, %esi             # imm = 0x266C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#23:                                # %entry_ifend351
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	%rbp, %r15
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 104(%rdx)
	movq	%rcx, 104(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 112(%rdx)
	movq	%rcx, 112(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	44(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_8
# BB#24:                                # %entry_ifend394
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$9844, %esi             # imm = 0x2674
	movq	%r15, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#25:                                # %entry_ifend433
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	48(%rsp), %rcx
	movq	32(%rsp), %r15          # 8-byte Reload
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r15)
	movq	%rcx, 104(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r15)
	movq	%rcx, 112(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_8
# BB#26:                                # %entry_ifend470
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 128(%rsp)
	movq	%r13, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %ebx
	movl	$9852, %esi             # imm = 0x267C
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#27:                                # %entry_ifend511
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r15)
	movq	%rcx, 104(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r15)
	movq	%rcx, 112(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%r14, %rbx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebp, %ecx
	movq	%rbx, %r8
	movq	24(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_28
# BB#29:                                # %entry_ifend551
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %eax
	movl	%eax, 8(%rsp)           # 4-byte Spill
	movl	112(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r12, %r15
	movq	%rbx, %r14
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	240(%rsp), %rbp
	je	.LBB20_1
# BB#30:                                # %entry_ifend592
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#31:                                # %entry_ifend596
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movl	112(%rsp), %r8d
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#32:                                # %entry_ifend600
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#33:                                # %entry_ifend604
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %rbx
	movl	$9860, %esi             # imm = 0x2684
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#34:                                # %entry_ifend607
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	48(%rsp), %rcx
	movq	32(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	%r14, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %r14
	jne	.LBB20_28
# BB#35:                                # %entry_ifend650
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	%r13, %rbx
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r14), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r14), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$9868, %esi             # imm = 0x268C
	movq	%r14, %r13
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#36:                                # %entry_ifend689
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	%rbp, %r14
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	44(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_8
# BB#37:                                # %entry_ifend726
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r13), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r13), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movq	%rbx, 8(%rsp)           # 8-byte Spill
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 136(%rsp)
	movq	%rbx, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %eax
	movl	%eax, (%rsp)            # 4-byte Spill
	movl	$9876, %esi             # imm = 0x2694
	movq	240(%rsp), %rbx
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#38:                                # %entry_ifend767
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$9892, %esi             # imm = 0x26A4
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#39:                                # %entry_ifend770
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	24(%rsp), %r15          # 8-byte Reload
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_40
# BB#41:                                # %entry_ifend807
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r13), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r13), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	movq	(%r14), %rax
	leaq	-8(%rax), %rcx
	movq	%rcx, (%r14)
	movq	$0, -8(%rax)
	movl	(%rsp), %ecx            # 4-byte Reload
	movq	%rcx, -8(%rax)
	movq	(%r14), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r14)
	movq	$0, 8(%rax)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movl	%ecx, %ecx
	movq	%rcx, 8(%rax)
	movq	(%r14), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r14)
	movq	$0, 8(%rax)
	movq	%rbx, 8(%rax)
	addq	$8, (%r14)
	movl	$2, %edi
	movq	%r13, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	movq	%r14, %rbx
	movq	%r15, %r8
	movq	%r15, %r14
	callq	invoke_block_in_jit
	testl	%eax, %eax
	movq	240(%rsp), %rbp
	je	.LBB20_1
# BB#42:                                # %entry_ifend855
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rbx), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 144(%rsp)
	movq	%r15, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %r12d
	movl	$9908, %esi             # imm = 0x26B4
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#43:                                # %entry_ifend865
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 104(%rdx)
	movq	%rcx, 104(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 112(%rdx)
	movq	%rcx, 112(%rdx)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	44(%rsp), %r15d         # 4-byte Reload
	movl	%r15d, %ecx
	movq	%rbx, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_5
# BB#44:                                # %entry_ifend905
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r13), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r13), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %ebp
	movl	112(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r13, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	240(%rsp), %r15
	je	.LBB20_1
# BB#45:                                # %entry_ifend946
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r13, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#46:                                # %entry_ifend950
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	%r13, %r12
	movq	%r15, %rbx
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %ebp
	jne	.LBB20_52
# BB#47:                                # %entry_condend954
                                        #   in Loop: Header=BB20_13 Depth=1
	movl	88(%rsp), %eax
	incl	%eax
	movq	$0, 88(%rsp)
	jmp	.LBB20_48
.LBB20_61:                              # %label_elifzzzzzzzzzzzzzzzzzy1a
                                        #   in Loop: Header=BB20_13 Depth=1
	cmpl	$1, %ebx
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %eax
	movl	%eax, (%rsp)            # 4-byte Spill
	movl	88(%rsp), %eax
	movl	%eax, 8(%rsp)           # 4-byte Spill
	jle	.LBB20_110
# BB#62:                                # %entry_condend1218
                                        #   in Loop: Header=BB20_13 Depth=1
	movl	112(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r12, %r13
	movq	%r13, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r15, %rbp
	je	.LBB20_1
# BB#63:                                # %entry_ifend1224
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r13, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#64:                                # %entry_ifend1228
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %rbx
	movl	$10328, %esi            # imm = 0x2858
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#65:                                # %entry_ifend1231
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	48(%rsp), %rcx
	movq	32(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	(%rsp), %edx            # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	44(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	24(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_8
# BB#66:                                # %entry_ifend1274
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r13), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r13), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$10336, %esi            # imm = 0x2860
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#67:                                # %entry_ifend1313
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_8
# BB#68:                                # %entry_ifend1350
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r13), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r13), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 128(%rsp)
	movq	%rbx, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %r12d
	movl	$10344, %esi            # imm = 0x2868
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#69:                                # %entry_ifend1391
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	48(%rsp), %rcx
	movq	32(%rsp), %r15          # 8-byte Reload
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r15)
	movq	%rcx, 104(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r15)
	movq	%rcx, 112(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%r14, %rbx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebp, %ecx
	movq	%rbx, %r8
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_70
# BB#71:                                # %entry_ifend1431
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r13), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r13), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %eax
	movl	%eax, 8(%rsp)           # 4-byte Spill
	movl	112(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r13, %r15
	movq	%rbx, %r14
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r12, %r13
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	240(%rsp), %rbp
	je	.LBB20_1
# BB#72:                                # %entry_ifend1472
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#73:                                # %entry_ifend1476
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movl	112(%rsp), %r8d
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#74:                                # %entry_ifend1480
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#75:                                # %entry_ifend1484
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %rbx
	movl	$10352, %esi            # imm = 0x2870
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#76:                                # %entry_ifend1487
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 104(%rdx)
	movq	%rcx, 104(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 112(%rdx)
	movq	%rcx, 112(%rdx)
	movq	%rdx, %r12
	movq	%r14, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_28
# BB#77:                                # %entry_ifend1530
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	%r13, %rbx
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$10360, %esi            # imm = 0x2878
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#78:                                # %entry_ifend1569
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	%rbp, %r14
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	44(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_8
# BB#79:                                # %entry_ifend1606
                                        #   in Loop: Header=BB20_13 Depth=1
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 136(%rsp)
	movq	%rbx, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movl	72(%rsp), %r13d
	movl	$10368, %esi            # imm = 0x2880
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#80:                                # %entry_ifend1646
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	%r14, %rbx
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbx)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebp, %ecx
	movq	%rbx, %r8
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_70
# BB#81:                                # %entry_ifend1683
                                        #   in Loop: Header=BB20_13 Depth=1
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movq	$0, 144(%rsp)
	movq	$1, 144(%rsp)
	movl	$1, %eax
	jmp	.LBB20_82
.LBB20_93:                              # %entry_ifend1946
                                        #   in Loop: Header=BB20_82 Depth=2
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r13), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r13), %rax
	movq	%r13, %r15
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	144(%rsp), %eax
	incl	%eax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
.LBB20_82:                              # %for_start_pointzzzzzzzzzzzzzzzzzze
                                        #   Parent Loop BB20_13 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	120(%rsp), %ecx
	movl	$0, gSigInt(%rip)
	cmpl	%ecx, %eax
	jge	.LBB20_94
# BB#83:                                # %entry_condend1724
                                        #   in Loop: Header=BB20_82 Depth=2
	movl	96(%rsp), %eax
	movl	%eax, 16(%rsp)          # 4-byte Spill
	movl	112(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%rbx, %r14
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r12, %r13
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	240(%rsp), %rbp
	je	.LBB20_1
# BB#84:                                # %entry_ifend1729
                                        #   in Loop: Header=BB20_82 Depth=2
	movq	(%rax), %r8
	movl	144(%rsp), %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#85:                                # %entry_ifend1734
                                        #   in Loop: Header=BB20_82 Depth=2
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	112(%rsp), %r8d
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#86:                                # %entry_ifend1738
                                        #   in Loop: Header=BB20_82 Depth=2
	movq	(%rax), %r8
	movl	144(%rsp), %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#87:                                # %entry_ifend1743
                                        #   in Loop: Header=BB20_82 Depth=2
	movq	(%rax), %rbx
	movl	$10456, %esi            # imm = 0x28D8
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#88:                                # %entry_ifend1746
                                        #   in Loop: Header=BB20_82 Depth=2
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 104(%rdx)
	movq	%rcx, 104(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 112(%rdx)
	movq	%rcx, 112(%rdx)
	movq	%rdx, %r12
	movq	%r14, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	16(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_28
# BB#89:                                # %entry_ifend1789
                                        #   in Loop: Header=BB20_82 Depth=2
	movq	%r13, %rbx
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$10464, %esi            # imm = 0x28E0
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%r15, %r13
	je	.LBB20_1
# BB#90:                                # %entry_ifend1828
                                        #   in Loop: Header=BB20_82 Depth=2
	movq	48(%rsp), %rcx
	movq	%r12, %r15
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r15)
	movq	%rcx, 104(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r15)
	movq	%rcx, 112(%r15)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movq	%r14, (%rcx)
	movq	%rbp, %r14
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	44(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_8
# BB#91:                                # %entry_ifend1865
                                        #   in Loop: Header=BB20_82 Depth=2
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r13), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r13), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 160(%rsp)
	movq	%rbx, 160(%rsp)
	movl	$0, gSigInt(%rip)
	movl	72(%rsp), %r12d
	movl	$10472, %esi            # imm = 0x28E8
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#92:                                # %entry_ifend1906
                                        #   in Loop: Header=BB20_82 Depth=2
	movq	48(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r15)
	movq	%rcx, 104(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r15)
	movq	%rcx, 112(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%r14, %rbx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebp, %ecx
	movq	%rbx, %r8
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB20_93
	jmp	.LBB20_70
.LBB20_52:                              # %label_elsezzzzzzzzzzzzzzzzzzc
                                        #   in Loop: Header=BB20_13 Depth=1
	movl	112(%rsp), %r8d
	movl	$1, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r12, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#53:                                # %entry_ifend960
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r12, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#54:                                # %entry_ifend964
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %rax
	movq	$0, 88(%rsp)
	movl	%eax, %eax
.LBB20_48:                              # %label_if_endzzzzzzzzzzzzzzzzzzc
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	%rax, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %edi
	callq	get_regex_global
	testl	%eax, %eax
	movq	%rbx, %rbp
	jne	.LBB20_13
	jmp	.LBB20_49
.LBB20_94:                              # %label_for_endzzzzzzzzzzzzzzzzzze
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rbx), %rax
	movl	64(%rsp), %ecx
	movl	136(%rsp), %edx
	movl	72(%rsp), %esi
	movq	$0, (%rax)
	movq	%rcx, (%rax)
	movq	(%rbx), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%rbx)
	movq	$0, 8(%rax)
	movq	%rdx, 8(%rax)
	movq	(%rbx), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%rbx)
	movq	$0, 8(%rax)
	movq	%rsi, 8(%rax)
	addq	$8, (%rbx)
	movl	$2, %edi
	movq	%r15, %r14
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movq	%r12, %r8
	callq	invoke_block_in_jit
	testl	%eax, %eax
	movq	240(%rsp), %r15
	je	.LBB20_1
# BB#95:                                # %entry_ifend2001
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 152(%rsp)
	movq	%r13, 152(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %r12d
	movl	$10560, %esi            # imm = 0x2940
	movq	%r15, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#96:                                # %entry_ifend2011
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	48(%rsp), %rcx
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 104(%rdx)
	movq	%rcx, 104(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 112(%rdx)
	movq	%rcx, 112(%rdx)
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
	movq	%r14, %rdx
	movl	%ebp, %r12d
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	24(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_28
# BB#97:                                # %entry_ifend2051
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r14), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r14), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %ebp
	movl	112(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%rbx, 16(%rsp)          # 8-byte Spill
	movq	%r14, %rsi
	movl	%r12d, %edx
	movl	%r12d, 44(%rsp)         # 4-byte Spill
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#98:                                # %entry_ifend2092
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r14, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#99:                                # %entry_ifend2096
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	%r14, %r12
	movq	%r15, %rbx
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %ebp
	jne	.LBB20_107
# BB#100:                               # %entry_condend2100
                                        #   in Loop: Header=BB20_13 Depth=1
	movl	88(%rsp), %eax
	incl	%eax
	movq	$0, 88(%rsp)
	jmp	.LBB20_101
.LBB20_107:                             # %label_elsezzzzzzzzzzzzzzzzzzf
                                        #   in Loop: Header=BB20_13 Depth=1
	movl	112(%rsp), %r8d
	movl	$1, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r12, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#108:                               # %entry_ifend2108
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	16(%rsp), %rdi          # 8-byte Reload
	movq	%r12, %rsi
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB20_1
# BB#109:                               # %entry_ifend2112
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	(%rax), %rax
	movq	$0, 88(%rsp)
	movl	%eax, %eax
.LBB20_101:                             # %label_if_endzzzzzzzzzzzzzzzzzzf
                                        #   in Loop: Header=BB20_13 Depth=1
	movq	%rax, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %edi
	callq	get_regex_global
	testl	%eax, %eax
	movq	%rbx, %rbp
	jne	.LBB20_13
# BB#102:                               # %entry_condend2118
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %ebx
	movl	88(%rsp), %r15d
	movl	$10760, %esi            # imm = 0x2A08
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%r12, %rdx
	je	.LBB20_1
# BB#103:                               # %entry_ifend2123
	movq	%rbp, %r14
	movq	48(%rsp), %rcx
	movq	32(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	16(%rsp), %r8           # 8-byte Reload
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %esi
	movq	%rsi, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rsi
	movq	%rsi, (%r8)
	movq	$0, 8(%rcx)
	movl	%r15d, %esi
	movq	%rsi, 8(%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rsi
	movq	%rsi, (%r8)
	movq	$0, 8(%rcx)
	movl	$4294967295, %esi       # imm = 0xFFFFFFFF
	movq	%rsi, 8(%rcx)
	addq	$8, (%r8)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%rdx, %rbp
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r8, %rbx
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_51
# BB#104:                               # %entry_ifend2166
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rbp), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rbp), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%rbp), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%rbp), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$10768, %esi            # imm = 0x2A10
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#105:                               # %entry_ifend2205
	movq	%r14, %r15
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	%rbx, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r8)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_51
# BB#106:                               # %entry_ifend2242
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rbp), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rbp), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%rbp), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%rbp), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r14
	movq	$0, 160(%rsp)
	movq	%r13, 160(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %ebx
	movl	$10776, %esi            # imm = 0x2A18
	jmp	.LBB20_58
.LBB20_8:                               # %then_block113
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB20_1
.LBB20_28:                              # %then_block550
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB20_1
.LBB20_70:                              # %then_block1430
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB20_1
.LBB20_110:                             # %label_if_elifzzzzzzzzzzzzzzzzzy0a
	movl	$10980, %esi            # imm = 0x2AE4
	movq	%r15, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%r12, %r15
	je	.LBB20_1
# BB#111:                               # %entry_ifend2367
	movq	48(%rsp), %rcx
	movq	32(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	(%rsp), %edx            # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%r14, %rbp
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	24(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_5
# BB#112:                               # %entry_ifend2410
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$10988, %esi            # imm = 0x2AEC
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#113:                               # %entry_ifend2449
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	%rbp, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r8)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_5
# BB#114:                               # %entry_ifend2486
	movq	%r15, %rbx
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbp, %r13
	movq	$0, 128(%rsp)
	movq	%r15, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %ebp
	movl	$10996, %esi            # imm = 0x2AF4
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#115:                               # %entry_ifend2527
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	%r13, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r8, %rbp
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB20_116
.LBB20_5:                               # %then_block40
	movq	%r14, %rdi
	callq	get_try_catch_label_name
.LBB20_1:                               # %then_block
	xorl	%eax, %eax
.LBB20_2:                               # %then_block
	addq	$184, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB20_40:                              # %then_block806
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB20_1
.LBB20_49:                              # %entry_condend969
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %ebx
	movl	88(%rsp), %r15d
	movl	$10108, %esi            # imm = 0x277C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%r12, %rdx
	je	.LBB20_1
# BB#50:                                # %entry_ifend974
	movq	%rbp, %r14
	movq	48(%rsp), %rcx
	movq	32(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	16(%rsp), %r8           # 8-byte Reload
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %esi
	movq	%rsi, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rsi
	movq	%rsi, (%r8)
	movq	$0, 8(%rcx)
	movl	%r15d, %esi
	movq	%rsi, 8(%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rsi
	movq	%rsi, (%r8)
	movq	$0, 8(%rcx)
	movl	$4294967295, %esi       # imm = 0xFFFFFFFF
	movq	%rsi, 8(%rcx)
	addq	$8, (%r8)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%rdx, %rbp
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r8, %rbx
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_51
# BB#55:                                # %entry_ifend1017
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rbp), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rbp), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%rbp), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%rbp), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$10116, %esi            # imm = 0x2784
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#56:                                # %entry_ifend1056
	movq	%r14, %r15
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	%rbx, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r8)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB20_51
# BB#57:                                # %entry_ifend1093
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rbp), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rbp), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%rbp), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%rbp), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r14
	movq	$0, 152(%rsp)
	movq	%r13, 152(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %ebx
	movl	$10124, %esi            # imm = 0x278C
.LBB20_58:                              # %entry_ifend1093
	movq	%r15, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
# BB#59:                                # %entry_ifend1134
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 104(%r12)
	movq	%rcx, 104(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 112(%r12)
	movq	%rcx, 112(%r12)
	movq	%r14, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r8, %rbx
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB20_60
.LBB20_51:                              # %then_block1016
	movq	24(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
	jmp	.LBB20_1
.LBB20_116:                             # %entry_ifend2567
	movq	%rbx, %rcx
	movq	(%rcx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rcx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rcx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rcx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rcx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rcx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rcx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rcx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rcx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rcx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rcx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rcx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rcx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%rcx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%rcx), %rax
	movq	%rcx, %r14
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	jmp	.LBB20_117
.LBB20_60:                              # %entry_ifend1174
	movq	%rbp, %rcx
	movq	(%rcx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rcx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rcx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rcx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rcx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rcx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rcx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rcx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rcx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rcx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rcx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	88(%rcx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	96(%rcx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	104(%rcx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	112(%rcx), %rax
	movq	%rcx, %r14
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
.LBB20_117:                             # %label_whilezzzzzzzzzzzzzzzzzx
	movl	$0, gSigInt(%rip)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB20_2
.Lfunc_end20:
	.size	"String.sub(regex,lambda,EqualableList)$$24", .Lfunc_end20-"String.sub(regex,lambda,EqualableList)$$24"
	.cfi_endproc

	.globl	"String.sub(regex,lambda)$$25"
	.align	16, 0x90
	.type	"String.sub(regex,lambda)$$25",@function
"String.sub(regex,lambda)$$25":         # @"String.sub(regex,lambda)$$25"
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
	subq	$72, %rsp
.Ltmp256:
	.cfi_def_cfa_offset 128
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
	movl	%r9d, 28(%rsp)          # 4-byte Spill
	movq	%r8, 16(%rsp)           # 8-byte Spill
	movq	%rcx, %rbp
	movq	%rdx, 32(%rsp)          # 8-byte Spill
	movq	%rsi, %r15
	movq	128(%rsp), %rdi
	movq	(%rbp), %rbx
	movq	$0, 40(%rsp)
	movq	%rbx, 40(%rsp)
	movq	8(%rbp), %r13
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	movq	16(%rbp), %r14
	movq	$0, 56(%rsp)
	movq	%r14, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$11168, %esi            # imm = 0x2BA0
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB21_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$11184, %esi            # imm = 0x2BB0
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB21_1
# BB#4:                                 # %entry_ifend5
	movq	$0, (%r15)
	movq	%rbx, (%r15)
	movq	$0, 8(%r15)
	movq	%r13, 8(%r15)
	movq	$0, 16(%r15)
	movq	%r14, 16(%r15)
	movq	$0, 24(%r15)
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbx)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	%rbp, %r13
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB21_6
# BB#5:                                 # %then_block16
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB21_1
.LBB21_6:                               # %entry_ifend17
	movq	(%r13), %r14
	movq	$0, 40(%rsp)
	movq	%r14, 40(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r13), %rbp
	movq	$0, 56(%rsp)
	movq	%rbp, 56(%rsp)
	movq	24(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 64(%rsp)
	movq	%r12, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$11200, %esi            # imm = 0x2BC0
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB21_1
# BB#7:                                 # %entry_ifend34
	movq	$0, (%r15)
	movq	%r14, (%r15)
	movq	$0, 8(%r15)
	movq	8(%rsp), %rdi           # 8-byte Reload
	movq	%rdi, 8(%r15)
	movq	$0, 16(%r15)
	movq	%rbp, 16(%r15)
	movq	$0, 24(%r15)
	movq	%r12, 24(%r15)
	movq	%rbp, %rsi
	movq	%rbx, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%edi, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$24, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	32(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB21_9
# BB#8:                                 # %then_block57
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB21_1:                               # %then_block
	xorl	%eax, %eax
.LBB21_2:                               # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB21_9:                               # %entry_ifend58
	movq	(%r13), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbx, (%r13)
	movl	$1, %eax
	jmp	.LBB21_2
.Lfunc_end21:
	.size	"String.sub(regex,lambda)$$25", .Lfunc_end21-"String.sub(regex,lambda)$$25"
	.cfi_endproc

	.globl	"String.scan(regex)$$26"
	.align	16, 0x90
	.type	"String.scan(regex)$$26",@function
"String.scan(regex)$$26":               # @"String.scan(regex)$$26"
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
	subq	$136, %rsp
.Ltmp269:
	.cfi_def_cfa_offset 192
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
	movl	%r9d, 44(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %r12
	movq	%rsi, %r13
	movq	192(%rsp), %rbp
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	$0, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movq	$0, 120(%rsp)
	movq	$0, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$11208, %esi            # imm = 0x2BC8
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$11224, %esi            # imm = 0x2BD8
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#4:                                 # %entry_ifend3
	movq	48(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r13)
	movq	%rcx, 64(%r13)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r13)
	movq	%rcx, 72(%r13)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r13)
	movq	%rcx, 80(%r13)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	44(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%r12, %rbp
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB22_5
# BB#6:                                 # %entry_ifend29
	movq	%rbp, 32(%rsp)          # 8-byte Spill
	movl	%ebx, %r12d
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 64(%rsp)
	movq	%rbx, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %ebx
	movl	$11240, %esi            # imm = 0x2BE8
	movq	192(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#7:                                 # %entry_ifend57
	movq	48(%rsp), %rcx
	movq	%r13, 24(%rsp)          # 8-byte Spill
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r13)
	movq	%rcx, 64(%r13)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r13)
	movq	%rcx, 72(%r13)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r13)
	movq	%rcx, 80(%r13)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r15, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB22_5
# BB#8:                                 # %entry_ifend86
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	%r14, %r12
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 80(%rsp)
	movq	%rbx, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 88(%rsp)
	movq	$16, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$11248, %esi            # imm = 0x2BF0
	movq	192(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#9:                                 # %entry_ifend117
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	88(%rsp), %ebx
	movl	$11260, %esi            # imm = 0x2BFC
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#10:                                # %entry_ifend121
	movq	48(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	%r15, %r14
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	44(%rsp), %r13d         # 4-byte Reload
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	32(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB22_12
# BB#11:                                # %then_block152
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB22_1
.LBB22_12:                              # %entry_ifend153
	movq	(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r12), %rax
	movq	%r12, 16(%rsp)          # 8-byte Spill
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 96(%rsp)
	movq	%rbx, 96(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB22_13
.LBB22_32:                              # %entry_condend
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	%rax, 72(%rsp)
	movl	%ebp, %r13d
	movq	%rbx, %r14
.LBB22_13:                              # %entry_condend
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB22_52 Depth 2
	movl	%r13d, 44(%rsp)         # 4-byte Spill
	movq	%r14, %r12
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r14d
	movl	80(%rsp), %r15d
	movl	72(%rsp), %eax
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	88(%rsp), %r13d
	movl	96(%rsp), %ebx
	movl	$11344, %esi            # imm = 0x2C50
	movq	192(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#14:                                # %entry_ifend189
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	48(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movl	%r13d, %esi
	movq	%r12, %r13
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$25, %esi
	movq	%rax, %rdi
	movq	16(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %rdx
	movl	44(%rsp), %r15d         # 4-byte Reload
	movl	%r15d, %ecx
	movq	%r13, %r8
	movq	32(%rsp), %r12          # 8-byte Reload
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB22_15
# BB#16:                                # %entry_ifend230
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 104(%rsp)
	movq	%rbx, 104(%rsp)
	movl	$0, gSigInt(%rip)
	cmpl	$1, %ebx
	jne	.LBB22_36
# BB#17:                                # %entry_condend262
                                        #   in Loop: Header=BB22_13 Depth=1
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %eax
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	96(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%r13, %rbx
	movq	%rbp, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	192(%rsp), %rbp
	je	.LBB22_1
# BB#18:                                # %entry_ifend267
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#19:                                # %entry_ifend270
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %r13
	movl	96(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#20:                                # %entry_ifend274
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#21:                                # %entry_ifend278
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %r12
	movl	$11384, %esi            # imm = 0x2C78
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#22:                                # %entry_ifend281
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	48(%rsp), %rcx
	movq	24(%rsp), %r14          # 8-byte Reload
	movq	$0, (%r14)
	movq	%rcx, (%r14)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r14)
	movq	%rcx, 8(%r14)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r14)
	movq	%rcx, 16(%r14)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r14)
	movq	%rcx, 24(%r14)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r14)
	movq	%rcx, 32(%r14)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r14)
	movq	%rcx, 40(%r14)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r14)
	movq	%rcx, 48(%r14)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r14)
	movq	%rcx, 56(%r14)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r14)
	movq	%rcx, 64(%r14)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r14)
	movq	%rcx, 72(%r14)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r14)
	movq	%rcx, 80(%r14)
	movq	%rbx, %r15
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	12(%rsp), %edx          # 4-byte Reload
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
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	16(%rsp), %r12          # 8-byte Reload
	movq	%r12, %rdx
	movl	44(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB22_5
# BB#23:                                # %entry_ifend316
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r12), %rax
	movq	%r12, %r14
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$11392, %esi            # imm = 0x2C80
	movq	192(%rsp), %r12
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#24:                                # %entry_ifend347
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	48(%rsp), %rcx
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r15)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB22_5
# BB#25:                                # %entry_ifend376
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 112(%rsp)
	movq	%r13, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %ebp
	movl	$11400, %esi            # imm = 0x2C88
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#26:                                # %entry_ifend409
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	%r15, %rbx
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %rbp
	movq	%rbp, %rdx
	movl	44(%rsp), %r12d         # 4-byte Reload
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	32(%rsp), %r15          # 8-byte Reload
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB22_27
# BB#28:                                # %entry_ifend441
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movq	%rbp, %rsi
	movl	72(%rsp), %r13d
	movl	96(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movl	%r12d, %edx
	movl	%r12d, %ebp
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#29:                                # %entry_ifend474
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#30:                                # %entry_ifend478
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r13d
	jne	.LBB22_33
# BB#31:                                # %entry_condend482
                                        #   in Loop: Header=BB22_13 Depth=1
	movl	72(%rsp), %eax
	incl	%eax
	movq	$0, 72(%rsp)
	jmp	.LBB22_32
.LBB22_36:                              # %label_elifzzzzzzzzzzzzzzzzzzi1a
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	%r13, %rbx
	movl	$0, gSigInt(%rip)
	jle	.LBB22_68
# BB#37:                                # %entry_condend498
                                        #   in Loop: Header=BB22_13 Depth=1
	movl	80(%rsp), %eax
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	96(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%r15d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	192(%rsp), %rbp
	je	.LBB22_1
# BB#38:                                # %entry_ifend503
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#39:                                # %entry_ifend507
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %r13
	movl	96(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#40:                                # %entry_ifend511
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#41:                                # %entry_ifend515
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %r12
	movl	$11676, %esi            # imm = 0x2D9C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#42:                                # %entry_ifend518
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	48(%rsp), %rcx
	movq	24(%rsp), %r14          # 8-byte Reload
	movq	$0, (%r14)
	movq	%rcx, (%r14)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r14)
	movq	%rcx, 8(%r14)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r14)
	movq	%rcx, 16(%r14)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r14)
	movq	%rcx, 24(%r14)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r14)
	movq	%rcx, 32(%r14)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r14)
	movq	%rcx, 40(%r14)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r14)
	movq	%rcx, 48(%r14)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r14)
	movq	%rcx, 56(%r14)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r14)
	movq	%rcx, 64(%r14)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r14)
	movq	%rcx, 72(%r14)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r14)
	movq	%rcx, 80(%r14)
	movq	%rbx, %r15
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	12(%rsp), %edx          # 4-byte Reload
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
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	16(%rsp), %r14          # 8-byte Reload
	movq	%r14, %rdx
	movl	44(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB22_5
# BB#43:                                # %entry_ifend553
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$11684, %esi            # imm = 0x2DA4
	movq	192(%rsp), %r12
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#44:                                # %entry_ifend584
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	48(%rsp), %rcx
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r15)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB22_5
# BB#45:                                # %entry_ifend613
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 112(%rsp)
	movq	%rbp, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r13d
	movl	$11692, %esi            # imm = 0x2DAC
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#46:                                # %entry_ifend646
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	%r15, %rbx
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %rbp
	movq	%rbp, %rdx
	movl	44(%rsp), %r15d         # 4-byte Reload
	movl	%r15d, %ecx
	movq	%rbx, %r8
	movq	32(%rsp), %r12          # 8-byte Reload
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB22_15
# BB#47:                                # %entry_ifend678
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movq	%rbp, %rsi
	movl	72(%rsp), %r13d
	movl	96(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movl	%r15d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#48:                                # %entry_ifend711
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%r15d, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#49:                                # %entry_ifend715
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r13d
	jne	.LBB22_64
# BB#50:                                # %entry_condend719
                                        #   in Loop: Header=BB22_13 Depth=1
	movl	72(%rsp), %eax
	incl	%eax
	movq	$0, 72(%rsp)
	jmp	.LBB22_51
.LBB22_33:                              # %label_elsezzzzzzzzzzzzzzzzzzj
                                        #   in Loop: Header=BB22_13 Depth=1
	movl	96(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#34:                                # %entry_ifend488
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#35:                                # %entry_ifend492
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %rax
	movq	$0, 72(%rsp)
	movl	%eax, %eax
	jmp	.LBB22_32
.LBB22_64:                              # %label_elsezzzzzzzzzzzzzzzzzzk
                                        #   in Loop: Header=BB22_13 Depth=1
	movl	96(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%r15d, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#65:                                # %entry_ifend727
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%r15d, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#66:                                # %entry_ifend731
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	(%rax), %rax
	movq	$0, 72(%rsp)
	movl	%eax, %eax
.LBB22_51:                              # %label_if_endzzzzzzzzzzzzzzzzzzk
                                        #   in Loop: Header=BB22_13 Depth=1
	movq	%rax, 72(%rsp)
	movl	%r15d, %r13d
	movl	$0, gSigInt(%rip)
	movq	$0, 120(%rsp)
	movq	$1, 120(%rsp)
	movl	$1, %eax
	movq	%rbx, %r14
	jmp	.LBB22_52
.LBB22_67:                              # %entry_ifend919
                                        #   in Loop: Header=BB22_52 Depth=2
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	120(%rsp), %eax
	incl	%eax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
.LBB22_52:                              # %for_start_pointzzzzzzzzzzzzzzzzzzl
                                        #   Parent Loop BB22_13 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	cmpl	104(%rsp), %eax
	jge	.LBB22_13
# BB#53:                                # %entry_condend737
                                        #   in Loop: Header=BB22_52 Depth=2
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %r15d
	movl	96(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r14, %r12
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%r13d, %edx
	movl	%r13d, %ebx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	192(%rsp), %rbp
	je	.LBB22_1
# BB#54:                                # %entry_ifend742
                                        #   in Loop: Header=BB22_52 Depth=2
	movq	(%rax), %r8
	movl	120(%rsp), %r9d
	movq	%r12, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#55:                                # %entry_ifend747
                                        #   in Loop: Header=BB22_52 Depth=2
	movq	(%rax), %r14
	movl	96(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#56:                                # %entry_ifend751
                                        #   in Loop: Header=BB22_52 Depth=2
	movq	(%rax), %r8
	movl	120(%rsp), %r9d
	movq	%r12, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#57:                                # %entry_ifend756
                                        #   in Loop: Header=BB22_52 Depth=2
	movq	(%rax), %r13
	movl	$11940, %esi            # imm = 0x2EA4
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#58:                                # %entry_ifend759
                                        #   in Loop: Header=BB22_52 Depth=2
	movq	48(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movl	%r15d, %edx
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
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
	movl	$11, %esi
	movq	%rax, %rdi
	movq	16(%rsp), %r14          # 8-byte Reload
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r12, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB22_5
# BB#59:                                # %entry_ifend794
                                        #   in Loop: Header=BB22_52 Depth=2
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	%r12, %r15
	movl	$11948, %esi            # imm = 0x2EAC
	movq	192(%rsp), %r12
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#60:                                # %entry_ifend825
                                        #   in Loop: Header=BB22_52 Depth=2
	movq	48(%rsp), %rcx
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r15)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB22_5
# BB#61:                                # %entry_ifend854
                                        #   in Loop: Header=BB22_52 Depth=2
	movl	%ebx, %ebp
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 128(%rsp)
	movq	%r13, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %ebx
	movl	$11956, %esi            # imm = 0x2EB4
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#62:                                # %entry_ifend887
                                        #   in Loop: Header=BB22_52 Depth=2
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
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
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %rbx
	movq	%rbx, %rdx
	movl	%ebp, %r13d
	movq	%r15, %r14
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	32(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB22_67
# BB#63:                                # %then_block918
	movq	32(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
	jmp	.LBB22_1
.LBB22_5:                               # %then_block28
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB22_1:                               # %then_block
	xorl	%eax, %eax
.LBB22_2:                               # %then_block
	addq	$136, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB22_15:                              # %then_block229
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB22_1
.LBB22_68:                              # %label_if_elifzzzzzzzzzzzzzzzzzzi0a
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %eax
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	%rax, (%rcx)
	movl	$1, %eax
	jmp	.LBB22_2
.LBB22_27:                              # %then_block440
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB22_1
.Lfunc_end22:
	.size	"String.scan(regex)$$26", .Lfunc_end22-"String.scan(regex)$$26"
	.cfi_endproc

	.globl	"String.scan(regex,lambda)$$27"
	.align	16, 0x90
	.type	"String.scan(regex,lambda)$$27",@function
"String.scan(regex,lambda)$$27":        # @"String.scan(regex,lambda)$$27"
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
	subq	$168, %rsp
.Ltmp282:
	.cfi_def_cfa_offset 224
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
	movl	%r9d, 60(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %r12
	movq	%rsi, %r13
	movq	224(%rsp), %rbp
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movq	$0, 120(%rsp)
	movq	$0, 128(%rsp)
	movq	$0, 136(%rsp)
	movq	$0, 144(%rsp)
	movq	$0, 152(%rsp)
	movq	$0, 160(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$12312, %esi            # imm = 0x3018
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$12328, %esi            # imm = 0x3028
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#4:                                 # %entry_ifend5
	movq	64(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r13)
	movq	%rcx, 64(%r13)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r13)
	movq	%rcx, 72(%r13)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r13)
	movq	%rcx, 80(%r13)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r13)
	movq	%rcx, 88(%r13)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r13)
	movq	%rcx, 96(%r13)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	60(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%r12, %rbp
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_5
# BB#6:                                 # %entry_ifend35
	movq	%rbp, 48(%rsp)          # 8-byte Spill
	movl	%ebx, %r12d
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
	movq	48(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r14), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r14), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 88(%rsp)
	movq	%rbx, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %ebx
	movl	$12344, %esi            # imm = 0x3038
	movq	224(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#7:                                 # %entry_ifend67
	movq	64(%rsp), %rcx
	movq	%r13, 40(%rsp)          # 8-byte Spill
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r13)
	movq	%rcx, 64(%r13)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r13)
	movq	%rcx, 72(%r13)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r13)
	movq	%rcx, 80(%r13)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r13)
	movq	%rcx, 88(%r13)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r13)
	movq	%rcx, 96(%r13)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r14, %rbx
	movq	%rbx, %rdx
	movl	%r12d, %r14d
	movl	%r14d, %ecx
	movq	%r15, %r8
	movq	48(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_5
# BB#8:                                 # %entry_ifend100
	movl	%r14d, %r12d
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
	movq	48(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbx), %rax
	movq	%rbx, %r14
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 104(%rsp)
	movq	%rbx, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 112(%rsp)
	movq	$16, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$12352, %esi            # imm = 0x3040
	movq	224(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#9:                                 # %entry_ifend135
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	112(%rsp), %ebx
	movl	$12364, %esi            # imm = 0x304C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#10:                                # %entry_ifend139
	movq	64(%rsp), %rcx
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
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
	movq	%r14, %rbx
	movq	%rbx, %rdx
	movl	%r12d, %ecx
	movq	%r15, %r8
	movq	48(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_5
# BB#11:                                # %entry_ifend175
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
	movq	48(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbx), %rax
	movq	%rbx, %r12
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%r15, 24(%rsp)          # 8-byte Spill
	movq	$0, 120(%rsp)
	movq	%rbx, 120(%rsp)
	movl	$0, gSigInt(%rip)
	movq	224(%rsp), %rbp
	movq	%rbp, %rdi
	jmp	.LBB23_12
.LBB23_36:                              # %entry_condend
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	%rax, 96(%rsp)
	movq	%rbx, %rdi
.LBB23_12:                              # %entry_condend
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB23_53 Depth 2
	movl	$0, gSigInt(%rip)
	movl	72(%rsp), %r13d
	movl	104(%rsp), %ebx
	movl	96(%rsp), %ebp
	movl	112(%rsp), %r15d
	movl	120(%rsp), %r14d
	movl	$12448, %esi            # imm = 0x30A0
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#13:                                # %entry_ifend215
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	64(%rsp), %rcx
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movl	%ebp, %esi
	movq	24(%rsp), %rbp          # 8-byte Reload
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
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
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
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$25, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	60(%rsp), %r15d         # 4-byte Reload
	movl	%r15d, %ecx
	movq	%rbp, %r8
	movq	48(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_14
# BB#15:                                # %entry_ifend260
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 128(%rsp)
	movq	%r14, 128(%rsp)
	movl	$0, gSigInt(%rip)
	cmpl	$1, %r14d
	movq	%r12, %rbx
	jne	.LBB23_40
# BB#16:                                # %entry_condend296
                                        #   in Loop: Header=BB23_12 Depth=1
	movl	$0, gSigInt(%rip)
	movl	104(%rsp), %r14d
	movl	120(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%rbp, %r12
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %rbp
	je	.LBB23_1
# BB#17:                                # %entry_ifend301
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#18:                                # %entry_ifend304
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movl	120(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#19:                                # %entry_ifend308
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#20:                                # %entry_ifend312
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %r15
	movl	$12488, %esi            # imm = 0x30C8
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#21:                                # %entry_ifend315
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	64(%rsp), %rcx
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%rbx, %r14
	movq	%r14, %rdx
	movl	60(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r12, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_14
# BB#22:                                # %entry_ifend354
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	%r13, %rbp
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
	movq	48(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r14), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r14), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	%r12, %r15
	movl	$12496, %esi            # imm = 0x30D0
	movq	224(%rsp), %r12
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#23:                                # %entry_ifend389
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	64(%rsp), %rcx
	movq	40(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r15)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_5
# BB#24:                                # %entry_ifend422
                                        #   in Loop: Header=BB23_12 Depth=1
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
	movq	48(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r14), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r14), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%r15, %r13
	movq	$0, 136(%rsp)
	movq	%rbx, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$12504, %esi            # imm = 0x30D8
	movq	224(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#25:                                # %entry_ifend457
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$12520, %esi            # imm = 0x30E8
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#26:                                # %entry_ifend460
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rbp
	movq	%rbp, %rdx
	movl	60(%rsp), %r15d         # 4-byte Reload
	movl	%r15d, %ecx
	movq	%r13, %r8
	movq	48(%rsp), %r12          # 8-byte Reload
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_27
# BB#28:                                # %entry_ifend493
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbp), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbp), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 144(%rsp)
	movq	%r14, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %eax
	movl	%eax, 32(%rsp)          # 4-byte Spill
	movq	(%r13), %rax
	movl	80(%rsp), %ecx
	movl	136(%rsp), %edx
	movq	$0, (%rax)
	movq	%rcx, (%rax)
	movq	(%r13), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r13)
	movq	$0, 8(%rax)
	movq	%rdx, 8(%rax)
	movq	(%r13), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r13)
	movq	$0, 8(%rax)
	movl	%r14d, %ecx
	movq	%rcx, 8(%rax)
	addq	$8, (%r13)
	movl	$2, %edi
	movq	%rbp, %rsi
	movq	%rbp, %r14
	movl	%r15d, %edx
	movq	%r13, %rcx
	movq	%r12, %r8
	callq	invoke_block_in_jit
	testl	%eax, %eax
	movq	224(%rsp), %rbx
	je	.LBB23_1
# BB#29:                                # %entry_ifend541
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	%r13, %rbp
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$12536, %esi            # imm = 0x30F8
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#30:                                # %entry_ifend549
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	64(%rsp), %rcx
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	%rbp, %rbx
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	32(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%rbx)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %r12
	movq	%r12, %rdx
	movl	%r15d, %ebp
	movl	%ebp, %ecx
	movq	%rbx, %r8
	movq	48(%rsp), %r15          # 8-byte Reload
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_31
# BB#32:                                # %entry_ifend585
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %r13d
	movl	120(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r12, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %rbx
	je	.LBB23_1
# BB#33:                                # %entry_ifend622
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	24(%rsp), %rdi          # 8-byte Reload
	movq	%r12, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	48(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#34:                                # %entry_ifend626
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r13d
	jne	.LBB23_37
# BB#35:                                # %entry_condend630
                                        #   in Loop: Header=BB23_12 Depth=1
	movl	96(%rsp), %eax
	incl	%eax
	movq	$0, 96(%rsp)
	jmp	.LBB23_36
.LBB23_40:                              # %label_elifzzzzzzzzzzzzzzzzzzn1a
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	%rbp, %r12
	movl	$0, gSigInt(%rip)
	jle	.LBB23_77
# BB#41:                                # %entry_condend646
                                        #   in Loop: Header=BB23_12 Depth=1
	movl	104(%rsp), %r14d
	movl	120(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %rbp
	je	.LBB23_1
# BB#42:                                # %entry_ifend651
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#43:                                # %entry_ifend655
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movl	120(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#44:                                # %entry_ifend659
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#45:                                # %entry_ifend663
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %r15
	movl	$12812, %esi            # imm = 0x320C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#46:                                # %entry_ifend666
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	64(%rsp), %rcx
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%rbx, %r14
	movq	%r14, %rdx
	movl	60(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r12, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_14
# BB#47:                                # %entry_ifend705
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	%r13, %rbp
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
	movq	48(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r14), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r14), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	%r12, %r15
	movl	$12820, %esi            # imm = 0x3214
	movq	224(%rsp), %r12
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#48:                                # %entry_ifend740
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	64(%rsp), %rcx
	movq	40(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r15)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_5
# BB#49:                                # %entry_ifend773
                                        #   in Loop: Header=BB23_12 Depth=1
	movl	%ebx, %r13d
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
	movq	48(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r14), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r14), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 136(%rsp)
	movq	%rbx, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$12828, %esi            # imm = 0x321C
	movq	224(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#50:                                # %entry_ifend808
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$12844, %esi            # imm = 0x322C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#51:                                # %entry_ifend811
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	%r15, %r12
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rbx
	movq	%rbx, %rdx
	movl	%r13d, %r14d
	movl	%r14d, %ecx
	movq	%r12, %r8
	movq	48(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_14
# BB#52:                                # %entry_ifend844
                                        #   in Loop: Header=BB23_12 Depth=1
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
	movq	48(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbx), %rax
	movq	%rbx, 32(%rsp)          # 8-byte Spill
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 144(%rsp)
	movq	%r15, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 152(%rsp)
	movq	$1, 152(%rsp)
	movl	$1, %eax
	jmp	.LBB23_53
.LBB23_64:                              # %entry_ifend1083
                                        #   in Loop: Header=BB23_53 Depth=2
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
	movq	48(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	152(%rsp), %eax
	incl	%eax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
.LBB23_53:                              # %for_start_pointzzzzzzzzzzzzzzzzzzp
                                        #   Parent Loop BB23_12 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	128(%rsp), %ecx
	movl	$0, gSigInt(%rip)
	cmpl	%ecx, %eax
	jge	.LBB23_65
# BB#54:                                # %entry_condend881
                                        #   in Loop: Header=BB23_53 Depth=2
	movl	104(%rsp), %eax
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movl	120(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	%r14d, %edx
	movl	%r14d, %ebx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %rbp
	je	.LBB23_1
# BB#55:                                # %entry_ifend886
                                        #   in Loop: Header=BB23_53 Depth=2
	movq	(%rax), %r8
	movl	152(%rsp), %r9d
	movq	%r12, %rdi
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	48(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#56:                                # %entry_ifend891
                                        #   in Loop: Header=BB23_53 Depth=2
	movq	(%rax), %r14
	movl	120(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	48(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#57:                                # %entry_ifend895
                                        #   in Loop: Header=BB23_53 Depth=2
	movq	(%rax), %r8
	movl	152(%rsp), %r9d
	movq	%r12, %rdi
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	48(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#58:                                # %entry_ifend900
                                        #   in Loop: Header=BB23_53 Depth=2
	movq	(%rax), %r15
	movl	$12932, %esi            # imm = 0x3284
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#59:                                # %entry_ifend903
                                        #   in Loop: Header=BB23_53 Depth=2
	movq	64(%rsp), %rcx
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	20(%rsp), %edx          # 4-byte Reload
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
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	32(%rsp), %r14          # 8-byte Reload
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r12, %r8
	movq	48(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_5
# BB#60:                                # %entry_ifend942
                                        #   in Loop: Header=BB23_53 Depth=2
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
	movq	48(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r14), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r14), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	%r12, %r15
	movl	$12940, %esi            # imm = 0x328C
	movq	224(%rsp), %r12
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#61:                                # %entry_ifend977
                                        #   in Loop: Header=BB23_53 Depth=2
	movq	64(%rsp), %rcx
	movq	40(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r15)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_5
# BB#62:                                # %entry_ifend1010
                                        #   in Loop: Header=BB23_53 Depth=2
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
	movq	48(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r14), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r14), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 160(%rsp)
	movq	%r13, 160(%rsp)
	movl	$0, gSigInt(%rip)
	movl	144(%rsp), %ebx
	movl	$12948, %esi            # imm = 0x3294
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#63:                                # %entry_ifend1047
                                        #   in Loop: Header=BB23_53 Depth=2
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	%r15, %r12
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
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %rbx
	movq	%rbx, %rdx
	movl	60(%rsp), %r14d         # 4-byte Reload
	movl	%r14d, %ecx
	movq	%r12, %r8
	movq	48(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB23_64
	jmp	.LBB23_14
.LBB23_37:                              # %label_elsezzzzzzzzzzzzzzzzzzo
                                        #   in Loop: Header=BB23_12 Depth=1
	movl	120(%rsp), %r8d
	movl	$1, %r9d
	movq	24(%rsp), %rdi          # 8-byte Reload
	movq	%r12, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	48(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#38:                                # %entry_ifend636
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	24(%rsp), %rdi          # 8-byte Reload
	movq	%r12, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	48(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#39:                                # %entry_ifend640
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %rax
	movq	$0, 96(%rsp)
	movl	%eax, %eax
	jmp	.LBB23_36
.LBB23_65:                              # %label_for_endzzzzzzzzzzzzzzzzzzp
                                        #   in Loop: Header=BB23_12 Depth=1
	movl	96(%rsp), %r15d
	movl	120(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	%r14d, %edx
	movl	%r14d, %r12d
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %rbx
	je	.LBB23_1
# BB#66:                                # %entry_ifend1124
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	24(%rsp), %rdi          # 8-byte Reload
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	%r12d, %edx
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#67:                                # %entry_ifend1128
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r15d
	jne	.LBB23_73
# BB#68:                                # %entry_condend1132
                                        #   in Loop: Header=BB23_12 Depth=1
	movl	96(%rsp), %eax
	incl	%eax
	movq	$0, 96(%rsp)
	jmp	.LBB23_69
.LBB23_73:                              # %label_elsezzzzzzzzzzzzzzzzzzq
                                        #   in Loop: Header=BB23_12 Depth=1
	movl	120(%rsp), %r8d
	movl	$1, %r9d
	movq	24(%rsp), %rdi          # 8-byte Reload
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	%r12d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#74:                                # %entry_ifend1140
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	24(%rsp), %rdi          # 8-byte Reload
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	%r12d, %edx
	movq	%r13, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB23_1
# BB#75:                                # %entry_ifend1144
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rax), %rax
	movq	$0, 96(%rsp)
	movl	%eax, %eax
.LBB23_69:                              # %label_if_endzzzzzzzzzzzzzzzzzzq
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	%rax, 96(%rsp)
	movl	%r12d, %edx
	movq	%r13, 48(%rsp)          # 8-byte Spill
	movl	%edx, 60(%rsp)          # 4-byte Spill
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %r12d
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	(%rcx), %rax
	movl	80(%rsp), %ebp
	movl	136(%rsp), %edi
	movl	144(%rsp), %esi
	movq	$0, (%rax)
	movq	%rbp, (%rax)
	movq	(%rcx), %rax
	leaq	8(%rax), %rbp
	movq	%rbp, (%rcx)
	movq	$0, 8(%rax)
	movq	%rdi, 8(%rax)
	movq	(%rcx), %rax
	leaq	8(%rax), %rdi
	movq	%rdi, (%rcx)
	movq	$0, 8(%rax)
	movq	%rsi, 8(%rax)
	addq	$8, (%rcx)
	movl	$2, %edi
	movq	32(%rsp), %rsi          # 8-byte Reload
	movq	%rcx, %rbp
	movq	%r13, %r8
	callq	invoke_block_in_jit
	testl	%eax, %eax
	je	.LBB23_1
# BB#70:                                # %entry_ifend1161
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$13196, %esi            # imm = 0x338C
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#71:                                # %entry_ifend1169
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	%rbx, %r15
	movq	64(%rsp), %rcx
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rbp, %rbx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%rbx)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	32(%rsp), %r12          # 8-byte Reload
	movq	%r12, %rdx
	movl	60(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	48(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_72
# BB#76:                                # %entry_ifend1205
                                        #   in Loop: Header=BB23_12 Depth=1
	movq	(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%r15, %rdi
	jmp	.LBB23_12
.LBB23_5:                               # %then_block34
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB23_1:                               # %then_block
	xorl	%eax, %eax
.LBB23_2:                               # %then_block
	addq	$168, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB23_14:                              # %then_block259
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB23_1
.LBB23_77:                              # %label_if_elifzzzzzzzzzzzzzzzzzzn0a
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB23_2
.LBB23_27:                              # %then_block492
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB23_1
.LBB23_31:                              # %then_block584
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB23_1
.LBB23_72:                              # %then_block1204
	movq	48(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
	jmp	.LBB23_1
.Lfunc_end23:
	.size	"String.scan(regex,lambda)$$27", .Lfunc_end23-"String.scan(regex,lambda)$$27"
	.cfi_endproc

	.globl	"String.each(lambda)$$28"
	.align	16, 0x90
	.type	"String.each(lambda)$$28",@function
"String.each(lambda)$$28":              # @"String.each(lambda)$$28"
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
	movl	%r9d, %r14d
	movq	%r8, %rbp
	movq	%rcx, %r13
	movq	%rdx, %r12
	movq	(%r13), %r15
	movq	$0, 16(%rsp)
	movq	%r15, 16(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 32(%rsp)
	xorl	%ebx, %ebx
	jmp	.LBB24_1
	.align	16, 0x90
.LBB24_8:                               # %entry_ifend18
                                        #   in Loop: Header=BB24_1 Depth=1
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	incl	%ebx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
.LBB24_1:                               # %for_start_pointzzzzzzzzzzzzzzzzzzr
                                        # =>This Inner Loop Header: Depth=1
	movl	$2, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%r15d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB24_2
# BB#4:                                 # %entry_ifend
                                        #   in Loop: Header=BB24_1 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %ebx
	jge	.LBB24_9
# BB#5:                                 # %entry_condend
                                        #   in Loop: Header=BB24_1 Depth=1
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%r15d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB24_2
# BB#6:                                 # %entry_ifend7
                                        #   in Loop: Header=BB24_1 Depth=1
	movq	(%rax), %r8
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebx, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB24_2
# BB#7:                                 # %entry_ifend11
                                        #   in Loop: Header=BB24_1 Depth=1
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
	movq	%r12, %r8
	callq	invoke_block_in_jit
	testl	%eax, %eax
	jne	.LBB24_8
.LBB24_2:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB24_3
.LBB24_9:                               # %label_for_endzzzzzzzzzzzzzzzzzzr
	movl	%r15d, %eax
	movq	%rax, (%r13)
	movl	$1, %eax
.LBB24_3:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end24:
	.size	"String.each(lambda)$$28", .Lfunc_end24-"String.each(lambda)$$28"
	.cfi_endproc

	.globl	"String.split(char)$$29"
	.align	16, 0x90
	.type	"String.split(char)$$29",@function
"String.split(char)$$29":               # @"String.split(char)$$29"
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
	subq	$104, %rsp
.Ltmp308:
	.cfi_def_cfa_offset 160
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
	movl	%r9d, 52(%rsp)          # 4-byte Spill
	movq	%r8, %r12
	movq	%rcx, %r14
	movq	%rdx, (%rsp)            # 8-byte Spill
	movq	%rsi, %r13
	movq	160(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 56(%rsp)
	movq	%rbp, 56(%rsp)
	movq	8(%r14), %rbx
	movq	$0, 64(%rsp)
	movq	%rbx, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$13624, %esi            # imm = 0x3538
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB25_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$13640, %esi            # imm = 0x3548
	movq	160(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB25_1
# BB#4:                                 # %entry_ifend3
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	$0, 8(%r13)
	movq	%rbx, 8(%r13)
	movq	$0, 16(%r13)
	movq	$0, 24(%r13)
	movq	$0, 32(%r13)
	movq	$0, 40(%r13)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	(%rsp), %rbx            # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB25_6
# BB#5:                                 # %then_block18
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB25_1:                               # %then_block
	xorl	%eax, %eax
.LBB25_2:                               # %then_block
	addq	$104, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB25_6:                               # %entry_ifend19
	movq	(%r14), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r14), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	32(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	40(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %rbp
	movq	%rbp, 24(%rsp)          # 8-byte Spill
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 72(%rsp)
	movq	%rbp, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movq	%rbx, %rbp
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movq	$0, 88(%rsp)
	movl	%ebx, %eax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	%rax, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 96(%rsp)
	xorl	%eax, %eax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	xorl	%r15d, %r15d
	jmp	.LBB25_7
	.align	16, 0x90
.LBB25_16:                              # %label_if_endzzzzzzzzzzzzzzzzzzt
                                        #   in Loop: Header=BB25_7 Depth=1
	incl	%r15d
	movq	$0, 96(%rsp)
	movq	%r15, 96(%rsp)
.LBB25_7:                               # %for_start_pointzzzzzzzzzzzzzzzzzzs
                                        # =>This Inner Loop Header: Depth=1
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB25_1
# BB#8:                                 # %entry_ifend38
                                        #   in Loop: Header=BB25_7 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r15d
	jge	.LBB25_22
# BB#9:                                 # %entry_condend
                                        #   in Loop: Header=BB25_7 Depth=1
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB25_1
# BB#10:                                # %entry_ifend42
                                        #   in Loop: Header=BB25_7 Depth=1
	movq	(%rax), %r8
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movl	%r15d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB25_1
# BB#11:                                # %entry_ifend46
                                        #   in Loop: Header=BB25_7 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	movq	32(%rsp), %rcx          # 8-byte Reload
	cmpl	%ecx, %eax
	jne	.LBB25_17
# BB#12:                                # %entry_condend50
                                        #   in Loop: Header=BB25_7 Depth=1
	movl	$13764, %esi            # imm = 0x35C4
	movq	160(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB25_1
# BB#13:                                # %entry_ifend55
                                        #   in Loop: Header=BB25_7 Depth=1
	movq	$0, (%r13)
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r13)
	movq	$0, 8(%r13)
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%r13)
	movq	$0, 16(%r13)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 16(%r13)
	movq	$0, 24(%r13)
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 24(%r13)
	movq	$0, 32(%r13)
	movq	8(%rsp), %rsi           # 8-byte Reload
	movq	%rsi, 32(%r13)
	movq	$0, 40(%r13)
	movq	%r15, 40(%r13)
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
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB25_14
# BB#15:                                # %entry_ifend77
                                        #   in Loop: Header=BB25_7 Depth=1
	movq	(%r14), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r14), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%r14), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%r14), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	32(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	40(%r14), %r15
	movq	$0, 96(%rsp)
	movq	%r15, 96(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.3, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movq	$0, 88(%rsp)
	movl	%ebx, %eax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	%rax, 88(%rsp)
	jmp	.LBB25_16
	.align	16, 0x90
.LBB25_17:                              # %label_elsezzzzzzzzzzzzzzzzzzt
                                        #   in Loop: Header=BB25_7 Depth=1
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB25_1
# BB#18:                                # %entry_ifend101
                                        #   in Loop: Header=BB25_7 Depth=1
	movq	(%rax), %r8
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movl	%r15d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB25_1
# BB#19:                                # %entry_ifend106
                                        #   in Loop: Header=BB25_7 Depth=1
	movq	(%rax), %rbx
	movl	$13848, %esi            # imm = 0x3618
	movq	160(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB25_1
# BB#20:                                # %entry_ifend109
                                        #   in Loop: Header=BB25_7 Depth=1
	movq	$0, (%r13)
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r13)
	movq	$0, 8(%r13)
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%r13)
	movq	$0, 16(%r13)
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 16(%r13)
	movq	$0, 24(%r13)
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 24(%r13)
	movq	$0, 32(%r13)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movq	%rdx, 32(%r13)
	movq	$0, 40(%r13)
	movq	%r15, 40(%r13)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$9, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB25_14
# BB#21:                                # %entry_ifend131
                                        #   in Loop: Header=BB25_7 Depth=1
	movq	(%r14), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r14), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%r14), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%r14), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	32(%r14), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	40(%r14), %r15
	movq	$0, 96(%rsp)
	movq	%r15, 96(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	jmp	.LBB25_16
.LBB25_22:                              # %label_for_endzzzzzzzzzzzzzzzzzzs
	movq	24(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB25_2
.LBB25_14:                              # %then_block76
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB25_1
.Lfunc_end25:
	.size	"String.split(char)$$29", .Lfunc_end25-"String.split(char)$$29"
	.cfi_endproc

	.globl	"String.split(regex)$$30"
	.align	16, 0x90
	.type	"String.split(regex)$$30",@function
"String.split(regex)$$30":              # @"String.split(regex)$$30"
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
	subq	$136, %rsp
.Ltmp321:
	.cfi_def_cfa_offset 192
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
	movl	%r9d, 44(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %r12
	movq	%rsi, %r13
	movq	192(%rsp), %rbp
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	$0, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movq	$0, 120(%rsp)
	movq	$0, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$13992, %esi            # imm = 0x36A8
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$14008, %esi            # imm = 0x36B8
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#4:                                 # %entry_ifend3
	movq	48(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r13)
	movq	%rcx, 64(%r13)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r13)
	movq	%rcx, 72(%r13)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r13)
	movq	%rcx, 80(%r13)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	44(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%r12, %rbp
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB26_5
# BB#6:                                 # %entry_ifend29
	movq	%rbp, 32(%rsp)          # 8-byte Spill
	movl	%ebx, %r12d
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 64(%rsp)
	movq	%rbx, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %ebx
	movl	$14024, %esi            # imm = 0x36C8
	movq	192(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#7:                                 # %entry_ifend57
	movq	48(%rsp), %rcx
	movq	%r13, 24(%rsp)          # 8-byte Spill
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r13)
	movq	%rcx, 64(%r13)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r13)
	movq	%rcx, 72(%r13)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r13)
	movq	%rcx, 80(%r13)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r14, %rbx
	movq	%rbx, %rdx
	movl	%r12d, %r14d
	movl	%r14d, %ecx
	movq	%r15, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB26_5
# BB#8:                                 # %entry_ifend86
	movl	%r14d, %r12d
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbx), %rax
	movq	%rbx, %r14
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 80(%rsp)
	movq	%rbx, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 88(%rsp)
	movq	$16, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$14032, %esi            # imm = 0x36D0
	movq	192(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#9:                                 # %entry_ifend117
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	88(%rsp), %ebx
	movl	$14044, %esi            # imm = 0x36DC
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#10:                                # %entry_ifend121
	movq	48(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
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
	movq	%r14, %rbp
	movq	%rbp, %rdx
	movl	%r12d, %r13d
	movl	%r13d, %ecx
	movq	%r15, %r8
	movq	32(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB26_12
# BB#11:                                # %then_block152
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB26_1
.LBB26_12:                              # %entry_ifend153
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbp), %rax
	movq	%rbp, 16(%rsp)          # 8-byte Spill
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 96(%rsp)
	movq	%rbx, 96(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB26_13
.LBB26_30:                              # %entry_condend
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	%rax, 72(%rsp)
	movl	%ebp, %r13d
	movq	%rbx, %r15
.LBB26_13:                              # %entry_condend
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB26_48 Depth 2
	movq	%r15, %r14
	movl	%r13d, %r12d
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r13d
	movl	80(%rsp), %r15d
	movl	72(%rsp), %eax
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	88(%rsp), %eax
	movl	%eax, 44(%rsp)          # 4-byte Spill
	movl	96(%rsp), %ebx
	movl	$14128, %esi            # imm = 0x3730
	movq	192(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#14:                                # %entry_ifend189
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	48(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movl	%ebx, %esi
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$25, %esi
	movq	%rax, %rdi
	movq	16(%rsp), %r15          # 8-byte Reload
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	32(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB26_15
# BB#16:                                # %entry_ifend230
                                        #   in Loop: Header=BB26_13 Depth=1
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
	movq	56(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 104(%rsp)
	movq	%rbx, 104(%rsp)
	movl	$0, gSigInt(%rip)
	cmpl	$1, %ebx
	jne	.LBB26_34
# BB#17:                                # %entry_condend262
                                        #   in Loop: Header=BB26_13 Depth=1
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %eax
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	72(%rsp), %eax
	movl	%eax, 44(%rsp)          # 4-byte Spill
	movl	96(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r14, %rbp
	movq	%r15, %rsi
	movl	%r12d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	192(%rsp), %rbx
	je	.LBB26_1
# BB#18:                                # %entry_ifend268
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%r12d, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#19:                                # %entry_ifend271
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rax), %r13
	movl	$14168, %esi            # imm = 0x3758
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#20:                                # %entry_ifend274
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	48(%rsp), %rcx
	movq	24(%rsp), %r14          # 8-byte Reload
	movq	$0, (%r14)
	movq	%rcx, (%r14)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r14)
	movq	%rcx, 8(%r14)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r14)
	movq	%rcx, 16(%r14)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r14)
	movq	%rcx, 24(%r14)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r14)
	movq	%rcx, 32(%r14)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r14)
	movq	%rcx, 40(%r14)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r14)
	movq	%rcx, 48(%r14)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r14)
	movq	%rcx, 56(%r14)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r14)
	movq	%rcx, 64(%r14)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r14)
	movq	%rcx, 72(%r14)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r14)
	movq	%rcx, 80(%r14)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %r15
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	16(%rsp), %r13          # 8-byte Reload
	movq	%r13, %rdx
	movl	%r12d, %ecx
	movq	%r15, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB26_5
# BB#21:                                # %entry_ifend309
                                        #   in Loop: Header=BB26_13 Depth=1
	movl	%r12d, %ebx
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r13), %rax
	movq	%r13, %r14
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$14176, %esi            # imm = 0x3760
	movq	192(%rsp), %r12
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#22:                                # %entry_ifend340
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	48(%rsp), %rcx
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r15)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB26_5
# BB#23:                                # %entry_ifend369
                                        #   in Loop: Header=BB26_13 Depth=1
	movl	%ebx, 44(%rsp)          # 4-byte Spill
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 112(%rsp)
	movq	%r13, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %ebp
	movl	$14184, %esi            # imm = 0x3768
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#24:                                # %entry_ifend402
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	%r15, %rbx
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %rbp
	movq	%rbp, %rdx
	movl	44(%rsp), %r12d         # 4-byte Reload
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	32(%rsp), %r15          # 8-byte Reload
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB26_25
# BB#26:                                # %entry_ifend434
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movq	%rbp, %rsi
	movl	72(%rsp), %r13d
	movl	96(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movl	%r12d, %edx
	movl	%r12d, %ebp
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#27:                                # %entry_ifend467
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#28:                                # %entry_ifend471
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r13d
	jne	.LBB26_31
# BB#29:                                # %entry_condend475
                                        #   in Loop: Header=BB26_13 Depth=1
	movl	72(%rsp), %eax
	incl	%eax
	movq	$0, 72(%rsp)
	jmp	.LBB26_30
.LBB26_34:                              # %label_elifzzzzzzzzzzzzzzzzzzv1a
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	%r15, %rbp
	movq	%r14, %r15
	movl	$0, gSigInt(%rip)
	jle	.LBB26_64
# BB#35:                                # %entry_condend491
                                        #   in Loop: Header=BB26_13 Depth=1
	movl	80(%rsp), %eax
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	72(%rsp), %eax
	movl	%eax, 44(%rsp)          # 4-byte Spill
	movl	96(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbp, %rsi
	movl	%r12d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	192(%rsp), %rbx
	je	.LBB26_1
# BB#36:                                # %entry_ifend497
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbp, %rsi
	movl	%r12d, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#37:                                # %entry_ifend501
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rax), %r13
	movl	$14460, %esi            # imm = 0x387C
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#38:                                # %entry_ifend504
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	48(%rsp), %rcx
	movq	24(%rsp), %r14          # 8-byte Reload
	movq	$0, (%r14)
	movq	%rcx, (%r14)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r14)
	movq	%rcx, 8(%r14)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r14)
	movq	%rcx, 16(%r14)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r14)
	movq	%rcx, 24(%r14)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r14)
	movq	%rcx, 32(%r14)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r14)
	movq	%rcx, 40(%r14)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r14)
	movq	%rcx, 48(%r14)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r14)
	movq	%rcx, 56(%r14)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r14)
	movq	%rcx, 64(%r14)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r14)
	movq	%rcx, 72(%r14)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r14)
	movq	%rcx, 80(%r14)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%rbp, %r14
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r15, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB26_5
# BB#39:                                # %entry_ifend539
                                        #   in Loop: Header=BB26_13 Depth=1
	movl	%r12d, %ebx
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$14468, %esi            # imm = 0x3884
	movq	192(%rsp), %r12
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#40:                                # %entry_ifend570
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	48(%rsp), %rcx
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r15)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB26_5
# BB#41:                                # %entry_ifend599
                                        #   in Loop: Header=BB26_13 Depth=1
	movl	%ebx, 44(%rsp)          # 4-byte Spill
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 112(%rsp)
	movq	%rbp, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r13d
	movl	$14476, %esi            # imm = 0x388C
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#42:                                # %entry_ifend632
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	%r15, %rbx
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %rbp
	movq	%rbp, %rdx
	movl	44(%rsp), %r12d         # 4-byte Reload
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	32(%rsp), %r15          # 8-byte Reload
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB26_25
# BB#43:                                # %entry_ifend664
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rbp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movq	%rbp, %rsi
	movl	72(%rsp), %r13d
	movl	96(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movl	%r12d, %edx
	movl	%r12d, %ebp
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#44:                                # %entry_ifend697
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#45:                                # %entry_ifend701
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r13d
	jne	.LBB26_60
# BB#46:                                # %entry_condend705
                                        #   in Loop: Header=BB26_13 Depth=1
	movl	72(%rsp), %eax
	incl	%eax
	movq	$0, 72(%rsp)
	jmp	.LBB26_47
.LBB26_31:                              # %label_elsezzzzzzzzzzzzzzzzzzw
                                        #   in Loop: Header=BB26_13 Depth=1
	movl	96(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#32:                                # %entry_ifend481
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#33:                                # %entry_ifend485
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rax), %rax
	movq	$0, 72(%rsp)
	movl	%eax, %eax
	jmp	.LBB26_30
.LBB26_60:                              # %label_elsezzzzzzzzzzzzzzzzzzx
                                        #   in Loop: Header=BB26_13 Depth=1
	movl	96(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#61:                                # %entry_ifend713
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebp, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#62:                                # %entry_ifend717
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	(%rax), %rax
	movq	$0, 72(%rsp)
	movl	%eax, %eax
.LBB26_47:                              # %label_if_endzzzzzzzzzzzzzzzzzzx
                                        #   in Loop: Header=BB26_13 Depth=1
	movq	%rax, 72(%rsp)
	movl	%ebp, %r13d
	movq	%rbx, %r15
	movl	$0, gSigInt(%rip)
	movq	$0, 120(%rsp)
	movq	$1, 120(%rsp)
	movl	$1, %eax
	jmp	.LBB26_48
.LBB26_63:                              # %entry_ifend905
                                        #   in Loop: Header=BB26_48 Depth=2
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	120(%rsp), %eax
	incl	%eax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
.LBB26_48:                              # %for_start_pointzzzzzzzzzzzzzzzzzzy
                                        #   Parent Loop BB26_13 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	cmpl	104(%rsp), %eax
	jge	.LBB26_13
# BB#49:                                # %entry_condend723
                                        #   in Loop: Header=BB26_48 Depth=2
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %eax
	movl	%eax, 44(%rsp)          # 4-byte Spill
	movl	96(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r15, %r12
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%r13d, %edx
	movl	%r13d, %ebx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	192(%rsp), %rbp
	je	.LBB26_1
# BB#50:                                # %entry_ifend728
                                        #   in Loop: Header=BB26_48 Depth=2
	movq	(%rax), %r8
	movl	120(%rsp), %r9d
	movq	%r12, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#51:                                # %entry_ifend733
                                        #   in Loop: Header=BB26_48 Depth=2
	movq	(%rax), %r15
	movl	96(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#52:                                # %entry_ifend737
                                        #   in Loop: Header=BB26_48 Depth=2
	movq	(%rax), %r8
	movl	120(%rsp), %r9d
	movq	%r12, %rdi
	movq	16(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	32(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB26_1
# BB#53:                                # %entry_ifend742
                                        #   in Loop: Header=BB26_48 Depth=2
	movq	(%rax), %r13
	movl	$14724, %esi            # imm = 0x3984
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#54:                                # %entry_ifend745
                                        #   in Loop: Header=BB26_48 Depth=2
	movq	48(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	44(%rsp), %edx          # 4-byte Reload
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
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	16(%rsp), %r14          # 8-byte Reload
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r12, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB26_5
# BB#55:                                # %entry_ifend780
                                        #   in Loop: Header=BB26_48 Depth=2
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	%r12, %r15
	movl	$14732, %esi            # imm = 0x398C
	movq	192(%rsp), %r12
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#56:                                # %entry_ifend811
                                        #   in Loop: Header=BB26_48 Depth=2
	movq	48(%rsp), %rcx
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r15)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebx, %ecx
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB26_5
# BB#57:                                # %entry_ifend840
                                        #   in Loop: Header=BB26_48 Depth=2
	movl	%ebx, 44(%rsp)          # 4-byte Spill
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	24(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	32(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	40(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	48(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	56(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	64(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	72(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	80(%r14), %rax
	movq	%r14, %rbp
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 128(%rsp)
	movq	%r13, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %ebx
	movl	$14740, %esi            # imm = 0x3994
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB26_1
# BB#58:                                # %entry_ifend873
                                        #   in Loop: Header=BB26_48 Depth=2
	movq	48(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	72(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
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
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%rbp, %rbx
	movq	%rbx, %rdx
	movl	44(%rsp), %r13d         # 4-byte Reload
	movl	%r13d, %ecx
	movq	%r15, %r8
	movq	32(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB26_63
# BB#59:                                # %then_block904
	movq	32(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
	jmp	.LBB26_1
.LBB26_5:                               # %then_block28
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB26_1:                               # %then_block
	xorl	%eax, %eax
.LBB26_2:                               # %then_block
	addq	$136, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB26_15:                              # %then_block229
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB26_1
.LBB26_25:                              # %then_block433
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB26_1
.LBB26_64:                              # %label_if_elifzzzzzzzzzzzzzzzzzzv0a
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %eax
	movq	%rax, (%rbp)
	movl	$1, %eax
	jmp	.LBB26_2
.Lfunc_end26:
	.size	"String.split(regex)$$30", .Lfunc_end26-"String.split(regex)$$30"
	.cfi_endproc

	.globl	"String.split(regex,lambda)$$31"
	.align	16, 0x90
	.type	"String.split(regex,lambda)$$31",@function
"String.split(regex,lambda)$$31":       # @"String.split(regex,lambda)$$31"
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
	subq	$168, %rsp
.Ltmp334:
	.cfi_def_cfa_offset 224
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
	movl	%r9d, 60(%rsp)          # 4-byte Spill
	movq	%r8, %r12
	movq	%rcx, %r15
	movq	%rdx, %r14
	movq	%rsi, %r13
	movq	224(%rsp), %rbp
	movq	(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movq	$0, 120(%rsp)
	movq	$0, 128(%rsp)
	movq	$0, 136(%rsp)
	movq	$0, 144(%rsp)
	movq	$0, 152(%rsp)
	movq	$0, 160(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$15096, %esi            # imm = 0x3AF8
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$15112, %esi            # imm = 0x3B08
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#4:                                 # %entry_ifend5
	movq	64(%rsp), %rcx
	movq	%r13, %rbp
	movq	%rbp, 48(%rsp)          # 8-byte Spill
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	%r12, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbp)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	60(%rsp), %r12d         # 4-byte Reload
	movq	%rbp, %r13
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_5
# BB#6:                                 # %entry_ifend35
	movq	(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 88(%rsp)
	movq	%rbx, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %ebx
	movl	$15128, %esi            # imm = 0x3B18
	movq	224(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#7:                                 # %entry_ifend67
	movq	64(%rsp), %rcx
	movq	48(%rsp), %rbp          # 8-byte Reload
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_5
# BB#8:                                 # %entry_ifend100
	movq	%r14, 40(%rsp)          # 8-byte Spill
	movq	(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r15), %rax
	movq	%r15, 32(%rsp)          # 8-byte Spill
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%r13, %r14
	movq	$0, 104(%rsp)
	movq	%rbx, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 112(%rsp)
	movq	$16, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$15136, %esi            # imm = 0x3B20
	movq	224(%rsp), %r15
	movq	%r15, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#9:                                 # %entry_ifend135
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	112(%rsp), %ebx
	movl	$15148, %esi            # imm = 0x3B2C
	movq	%r15, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#10:                                # %entry_ifend139
	movq	64(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	32(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	60(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	40(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB27_12
# BB#11:                                # %then_block174
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB27_1
.LBB27_12:                              # %entry_ifend175
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
	movq	48(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%r14, 24(%rsp)          # 8-byte Spill
	movq	$0, 120(%rsp)
	movq	%rbx, 120(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB27_13
.LBB27_34:                              # %entry_condend623
                                        #   in Loop: Header=BB27_13 Depth=1
	movl	96(%rsp), %eax
	incl	%eax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
.LBB27_13:                              # %entry_condend
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB27_50 Depth 2
	movl	$0, gSigInt(%rip)
	movl	72(%rsp), %r12d
	movl	104(%rsp), %r14d
	movl	96(%rsp), %r13d
	movl	112(%rsp), %ebp
	movl	120(%rsp), %ebx
	movl	$15232, %esi            # imm = 0x3B80
	movq	%r15, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#14:                                # %entry_ifend215
                                        #   in Loop: Header=BB27_13 Depth=1
	movl	%ebx, %esi
	movq	64(%rsp), %rcx
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movl	%ebp, %edi
	movq	24(%rsp), %rbp          # 8-byte Reload
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%edi, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$25, %esi
	movq	%rax, %rdi
	movq	32(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	60(%rsp), %r14d         # 4-byte Reload
	movl	%r14d, %ecx
	movq	%rbp, %r8
	movq	40(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_15
# BB#16:                                # %entry_ifend260
                                        #   in Loop: Header=BB27_13 Depth=1
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
	movq	48(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 128(%rsp)
	movq	%r15, 128(%rsp)
	movl	$0, gSigInt(%rip)
	cmpl	$1, %r15d
	jne	.LBB27_38
# BB#17:                                # %entry_condend296
                                        #   in Loop: Header=BB27_13 Depth=1
	movl	$0, gSigInt(%rip)
	movl	104(%rsp), %eax
	movl	%eax, 8(%rsp)           # 4-byte Spill
	movl	96(%rsp), %eax
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movl	120(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movq	%rbx, %r15
	movl	%r14d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %rbx
	je	.LBB27_1
# BB#18:                                # %entry_ifend302
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r15, %rsi
	movl	%r14d, %edx
	movq	40(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#19:                                # %entry_ifend305
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	(%rax), %r13
	movl	$15276, %esi            # imm = 0x3BAC
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#20:                                # %entry_ifend308
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	%rbx, %r12
	movq	64(%rsp), %rcx
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rbp, %r13
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r14d, %ecx
	movq	%r13, %r8
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_21
# BB#22:                                # %entry_ifend347
                                        #   in Loop: Header=BB27_13 Depth=1
	movl	%r14d, %ebp
	movq	(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r13), %rax
	movq	%r13, %r14
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$15284, %esi            # imm = 0x3BB4
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#23:                                # %entry_ifend382
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	64(%rsp), %rcx
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	%rdx, %r12
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_21
# BB#24:                                # %entry_ifend415
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	%r14, %r13
	movq	(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 136(%rsp)
	movq	%rbx, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$15292, %esi            # imm = 0x3BBC
	movq	224(%rsp), %rbx
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#25:                                # %entry_ifend450
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movl	$15308, %esi            # imm = 0x3BCC
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#26:                                # %entry_ifend453
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	%r13, %r12
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rbx
	movq	%rbx, %rdx
	movl	%ebp, %r14d
	movl	%r14d, %ecx
	movq	%r12, %r8
	movq	40(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_15
# BB#27:                                # %entry_ifend486
                                        #   in Loop: Header=BB27_13 Depth=1
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
	movq	48(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 144(%rsp)
	movq	%rbp, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %eax
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movq	(%r12), %rax
	movl	80(%rsp), %ecx
	movl	136(%rsp), %edx
	movq	$0, (%rax)
	movq	%rcx, (%rax)
	movq	(%r12), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r12)
	movq	$0, 8(%rax)
	movq	%rdx, 8(%rax)
	movq	(%r12), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r12)
	movq	$0, 8(%rax)
	movl	%ebp, %ecx
	movq	%rcx, 8(%rax)
	addq	$8, (%r12)
	movl	$2, %edi
	movq	%rbx, %rsi
	movq	%rbx, %r15
	movl	%r14d, %edx
	movq	%r12, %rcx
	movq	%r12, %rbx
	movq	%r13, %r8
	callq	invoke_block_in_jit
	testl	%eax, %eax
	movq	224(%rsp), %rbp
	je	.LBB27_1
# BB#28:                                # %entry_ifend534
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$15324, %esi            # imm = 0x3BDC
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#29:                                # %entry_ifend542
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	64(%rsp), %rcx
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	movq	%rbx, %rbp
	addq	$8, (%rbp)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r15, %rbx
	movq	%rbx, %rdx
	movl	%r14d, %r12d
	movl	%r12d, %ecx
	movq	%rbp, %r8
	movq	40(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_15
# BB#30:                                # %entry_ifend578
                                        #   in Loop: Header=BB27_13 Depth=1
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
	movq	48(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %r14d
	movl	120(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r12d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %rbx
	je	.LBB27_1
# BB#31:                                # %entry_ifend615
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	24(%rsp), %rdi          # 8-byte Reload
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	40(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#32:                                # %entry_ifend619
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	%rbx, %r15
.LBB27_33:                              # %entry_ifend619
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r14d
	je	.LBB27_34
# BB#35:                                # %label_elsezzzzzzzzzzzzzzzzzzzc
                                        #   in Loop: Header=BB27_13 Depth=1
	movl	120(%rsp), %r8d
	movl	$1, %r9d
	movq	24(%rsp), %rdi          # 8-byte Reload
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	40(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#36:                                # %entry_ifend629
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	24(%rsp), %rdi          # 8-byte Reload
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	40(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#37:                                # %entry_ifend633
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	(%rax), %rax
	movq	$0, 96(%rsp)
	movl	%eax, %eax
	movq	%rax, 96(%rsp)
	jmp	.LBB27_13
.LBB27_38:                              # %label_elifzzzzzzzzzzzzzzzzzzzb1a
                                        #   in Loop: Header=BB27_13 Depth=1
	movl	$0, gSigInt(%rip)
	movl	104(%rsp), %eax
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movl	96(%rsp), %r15d
	jle	.LBB27_67
# BB#39:                                # %entry_condend639
                                        #   in Loop: Header=BB27_13 Depth=1
	movl	120(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	24(%rsp), %rdi          # 8-byte Reload
	movq	%rbx, %rsi
	movq	%rbx, %rbp
	movl	%r14d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %rbx
	je	.LBB27_1
# BB#40:                                # %entry_ifend645
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	24(%rsp), %rdi          # 8-byte Reload
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	40(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#41:                                # %entry_ifend649
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	(%rax), %r13
	movl	$15620, %esi            # imm = 0x3D04
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#42:                                # %entry_ifend652
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	%rbx, %r12
	movq	64(%rsp), %rcx
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	24(%rsp), %rsi          # 8-byte Reload
	movq	(%rsi), %rcx
	movq	$0, (%rcx)
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rsi), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rsi)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rsi), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rsi)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rsi, %r13
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%rbp, %r15
	movq	%r15, %rdx
	movl	%r14d, %ecx
	movq	%r13, %r8
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_21
# BB#43:                                # %entry_ifend691
                                        #   in Loop: Header=BB27_13 Depth=1
	movl	%r14d, %ebp
	movq	(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r13), %rax
	movq	%r13, %r14
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$15628, %esi            # imm = 0x3D0C
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#44:                                # %entry_ifend726
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	64(%rsp), %rcx
	movq	48(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_21
# BB#45:                                # %entry_ifend759
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	%r14, %r13
	movq	(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 136(%rsp)
	movq	%rbx, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$15636, %esi            # imm = 0x3D14
	movq	224(%rsp), %rbx
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#46:                                # %entry_ifend794
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movl	$15652, %esi            # imm = 0x3D24
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#47:                                # %entry_ifend797
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rbx
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r13, %r8
	movq	40(%rsp), %r15          # 8-byte Reload
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_48
# BB#49:                                # %entry_ifend830
                                        #   in Loop: Header=BB27_13 Depth=1
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
	movq	48(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 144(%rsp)
	movq	%r14, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 152(%rsp)
	movq	$1, 152(%rsp)
	movl	$1, %eax
	movq	%r13, %r14
	jmp	.LBB27_50
.LBB27_61:                              # %entry_ifend1069
                                        #   in Loop: Header=BB27_50 Depth=2
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
	movq	48(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	152(%rsp), %eax
	incl	%eax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
.LBB27_50:                              # %for_start_pointzzzzzzzzzzzzzzzzzzzd
                                        #   Parent Loop BB27_13 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	128(%rsp), %ecx
	movl	$0, gSigInt(%rip)
	cmpl	%ecx, %eax
	jge	.LBB27_62
# BB#51:                                # %entry_condend867
                                        #   in Loop: Header=BB27_50 Depth=2
	movl	104(%rsp), %eax
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movl	120(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movl	%ebp, %r13d
	movq	%r15, %rcx
	movq	%r15, %r12
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %rbp
	je	.LBB27_1
# BB#52:                                # %entry_ifend872
                                        #   in Loop: Header=BB27_50 Depth=2
	movq	(%rax), %r8
	movl	152(%rsp), %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r12, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#53:                                # %entry_ifend877
                                        #   in Loop: Header=BB27_50 Depth=2
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	120(%rsp), %r8d
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#54:                                # %entry_ifend881
                                        #   in Loop: Header=BB27_50 Depth=2
	movq	(%rax), %r8
	movl	152(%rsp), %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r12, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#55:                                # %entry_ifend886
                                        #   in Loop: Header=BB27_50 Depth=2
	movq	(%rax), %r15
	movl	$15740, %esi            # imm = 0x3D7C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#56:                                # %entry_ifend889
                                        #   in Loop: Header=BB27_50 Depth=2
	movq	64(%rsp), %rcx
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%rbx, %r15
	movq	%r15, %rdx
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	%r12, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_21
# BB#57:                                # %entry_ifend928
                                        #   in Loop: Header=BB27_50 Depth=2
	movl	%r13d, %ebp
	movq	(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$15748, %esi            # imm = 0x3D84
	movq	224(%rsp), %r12
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#58:                                # %entry_ifend963
                                        #   in Loop: Header=BB27_50 Depth=2
	movq	64(%rsp), %rcx
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_21
# BB#59:                                # %entry_ifend996
                                        #   in Loop: Header=BB27_50 Depth=2
	movq	(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 160(%rsp)
	movq	%r13, 160(%rsp)
	movl	$0, gSigInt(%rip)
	movl	144(%rsp), %ebx
	movl	$15756, %esi            # imm = 0x3D8C
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#60:                                # %entry_ifend1033
                                        #   in Loop: Header=BB27_50 Depth=2
	movq	64(%rsp), %rcx
	movq	48(%rsp), %r12          # 8-byte Reload
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r12)
	movq	%rcx, 16(%r12)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r12)
	movq	%rcx, 24(%r12)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r12)
	movq	%rcx, 32(%r12)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r12)
	movq	%rcx, 40(%r12)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r12)
	movq	%rcx, 48(%r12)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r12)
	movq	%rcx, 56(%r12)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r12)
	movq	%rcx, 64(%r12)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r12)
	movq	%rcx, 72(%r12)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r12)
	movq	%rcx, 80(%r12)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r12)
	movq	%rcx, 88(%r12)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r12)
	movq	%rcx, 96(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
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
	movq	%r15, %rbx
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	40(%rsp), %r15          # 8-byte Reload
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB27_61
	jmp	.LBB27_48
.LBB27_62:                              # %label_for_endzzzzzzzzzzzzzzzzzzzd
                                        #   in Loop: Header=BB27_13 Depth=1
	movl	88(%rsp), %r12d
	movq	(%r14), %rax
	movl	80(%rsp), %ecx
	movl	136(%rsp), %edx
	movl	144(%rsp), %esi
	movq	$0, (%rax)
	movq	%rcx, (%rax)
	movq	(%r14), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r14)
	movq	$0, 8(%rax)
	movq	%rdx, 8(%rax)
	movq	(%r14), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r14)
	movq	$0, 8(%rax)
	movq	%rsi, 8(%rax)
	addq	$8, (%r14)
	movl	$2, %edi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	movq	%r14, %rbx
	movq	%r15, %r8
	movq	%r15, %r14
	callq	invoke_block_in_jit
	testl	%eax, %eax
	movq	224(%rsp), %r15
	je	.LBB27_1
# BB#63:                                # %entry_ifend1121
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$15844, %esi            # imm = 0x3DE4
	movq	%r15, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#64:                                # %entry_ifend1129
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	64(%rsp), %rcx
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	movq	%rbx, %r12
	addq	$8, (%r12)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	32(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r12, %r8
	movq	%r14, %r13
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_15
# BB#65:                                # %entry_ifend1165
                                        #   in Loop: Header=BB27_13 Depth=1
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
	movq	48(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %r14d
	movl	120(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r12, 24(%rsp)          # 8-byte Spill
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movl	%ebp, 60(%rsp)          # 4-byte Spill
	movq	%r13, %rcx
	movq	%r13, 40(%rsp)          # 8-byte Spill
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB27_1
# BB#66:                                # %entry_ifend1202
                                        #   in Loop: Header=BB27_13 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	24(%rsp), %rdi          # 8-byte Reload
	movq	32(%rsp), %rsi          # 8-byte Reload
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	40(%rsp), %rcx          # 8-byte Reload
	callq	load_element
	cmpl	$0, 8(%rax)
	jne	.LBB27_33
	jmp	.LBB27_1
.LBB27_21:                              # %then_block346
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB27_1
.LBB27_15:                              # %then_block259
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB27_1
.LBB27_48:                              # %then_block829
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB27_1
.LBB27_67:                              # %label_if_elifzzzzzzzzzzzzzzzzzzzb0a
	movl	$16136, %esi            # imm = 0x3F08
	movq	224(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#68:                                # %entry_ifend1229
	movq	%rbp, %r12
	movq	64(%rsp), %rcx
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movl	%r15d, %esi
	movq	%rdx, %r15
	movq	24(%rsp), %rbp          # 8-byte Reload
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	60(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	%r13, %r14
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB27_69
.LBB27_5:                               # %then_block34
	movq	%r14, %rdi
	callq	get_try_catch_label_name
.LBB27_1:                               # %then_block
	xorl	%eax, %eax
.LBB27_2:                               # %then_block
	addq	$168, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB27_69:                              # %entry_ifend1268
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
	movq	48(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbx), %rax
	movq	%rbx, %r14
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbp, %rbx
	movl	$16144, %esi            # imm = 0x3F10
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#70:                                # %entry_ifend1303
	movq	64(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	%rbx, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r8)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	60(%rsp), %ecx          # 4-byte Reload
	movq	40(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_71
# BB#72:                                # %entry_ifend1336
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
	movq	48(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r14), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r14), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r12
	movq	$0, 136(%rsp)
	movq	%rbp, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$16152, %esi            # imm = 0x3F18
	movq	224(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#73:                                # %entry_ifend1371
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$16168, %esi            # imm = 0x3F28
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#74:                                # %entry_ifend1374
	movq	64(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	72(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	80(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	88(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	96(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	%r12, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r8)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	60(%rsp), %ecx          # 4-byte Reload
	movq	%r8, %rbp
	movq	40(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB27_71
# BB#75:                                # %entry_ifend1407
	movq	%r14, %rbx
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
	movq	48(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 144(%rsp)
	movq	%r15, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %r14d
	movq	(%rbp), %rax
	movl	80(%rsp), %ecx
	movl	136(%rsp), %edx
	movq	$0, (%rax)
	movq	%rcx, (%rax)
	movq	(%rbp), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%rbp)
	movq	$0, 8(%rax)
	movq	%rdx, 8(%rax)
	movq	(%rbp), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%rbp)
	movq	$0, 8(%rax)
	movl	%r15d, %ecx
	movq	%rcx, 8(%rax)
	addq	$8, (%rbp)
	movl	$2, %edi
	movq	%rbx, %rsi
	movq	%rbx, %r12
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	movq	40(%rsp), %r8           # 8-byte Reload
	callq	invoke_block_in_jit
	testl	%eax, %eax
	movq	224(%rsp), %rbx
	je	.LBB27_1
# BB#76:                                # %entry_ifend1455
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$16184, %esi            # imm = 0x3F38
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB27_1
# BB#77:                                # %entry_ifend1463
	movq	64(%rsp), %rcx
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rdx)
	movq	%rcx, 48(%rdx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rdx)
	movq	%rcx, 56(%rdx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rdx)
	movq	%rcx, 64(%rdx)
	movq	136(%rsp), %rcx
	movq	$0, 72(%rdx)
	movq	%rcx, 72(%rdx)
	movq	144(%rsp), %rcx
	movq	$0, 80(%rdx)
	movq	%rcx, 80(%rdx)
	movq	152(%rsp), %rcx
	movq	$0, 88(%rdx)
	movq	%rcx, 88(%rdx)
	movq	160(%rsp), %rcx
	movq	$0, 96(%rdx)
	movq	%rcx, 96(%rdx)
	movq	%rbp, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r8)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	60(%rsp), %ecx          # 4-byte Reload
	movq	%r8, %rbx
	movq	40(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB27_78
.LBB27_71:                              # %then_block1335
	movq	40(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
	jmp	.LBB27_1
.LBB27_78:                              # %entry_ifend1499
	movq	(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r12), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r12), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	40(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	48(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	56(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	64(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	72(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	80(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	88(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	96(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %eax
	movq	%rax, (%r12)
	movl	$1, %eax
	jmp	.LBB27_2
.Lfunc_end27:
	.size	"String.split(regex,lambda)$$31", .Lfunc_end27-"String.split(regex,lambda)$$31"
	.cfi_endproc

	.globl	"String.indexOf(Self,int)$$32"
	.align	16, 0x90
	.type	"String.indexOf(Self,int)$$32",@function
"String.indexOf(Self,int)$$32":         # @"String.indexOf(Self,int)$$32"
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
	subq	$136, %rsp
.Ltmp347:
	.cfi_def_cfa_offset 192
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
	movl	%r9d, 76(%rsp)          # 4-byte Spill
	movq	%r8, %rbp
	movq	%rcx, %rbx
	movq	%rdx, 56(%rsp)          # 8-byte Spill
	movq	%rsi, %r15
	movq	192(%rsp), %rdi
	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
	movq	(%rbx), %r14
	movq	$0, 80(%rsp)
	movq	%r14, 80(%rsp)
	movq	8(%rbx), %r13
	movq	$0, 88(%rsp)
	movq	%r13, 88(%rsp)
	movq	16(%rbx), %r12
	movq	$0, 96(%rsp)
	movq	%r12, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movq	$0, 120(%rsp)
	movq	$0, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$16376, %esi            # imm = 0x3FF8
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB28_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r15)
	movq	%r14, (%r15)
	movq	$0, 8(%r15)
	movq	%r13, 8(%r15)
	movq	$0, 16(%r15)
	movq	%r12, 16(%r15)
	movq	$0, 24(%r15)
	movl	$4294967295, %ecx       # imm = 0xFFFFFFFF
	movq	%rcx, 24(%r15)
	movq	$0, 32(%r15)
	movq	$0, 40(%r15)
	movq	$0, 48(%r15)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbp)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	76(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	56(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %r13
	movq	%r13, 8(%rsp)           # 8-byte Spill
	je	.LBB28_5
# BB#4:                                 # %then_block20
	movq	%r14, %rdi
	callq	get_try_catch_label_name
.LBB28_1:                               # %then_block
	xorl	%eax, %eax
.LBB28_2:                               # %then_block
	addq	$136, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB28_5:                               # %entry_ifend21
	movq	(%r13), %rax
	movq	%rax, 64(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	16(%r13), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	24(%r13), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	32(%r13), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	40(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	48(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movq	%rbx, 16(%rsp)          # 8-byte Spill
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbp, %rax
	movq	$0, 120(%rsp)
	movq	%rbx, 120(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 128(%rsp)
	xorl	%ebp, %ebp
	jmp	.LBB28_6
	.align	16, 0x90
.LBB28_19:                              # %label_if_endzzzzzzzzzzzzzzzzzzzg
                                        #   in Loop: Header=BB28_6 Depth=1
	incl	%ebp
	movq	$0, 128(%rsp)
	movq	%rbp, 128(%rsp)
	movq	56(%rsp), %r14          # 8-byte Reload
.LBB28_6:                               # %for_start_pointzzzzzzzzzzzzzzzzzzzf
                                        # =>This Inner Loop Header: Depth=1
	movl	$2, %r9d
	movq	%rax, %rbx
	movq	%rbx, %rdi
	movq	%r13, %rsi
	movl	76(%rsp), %edx          # 4-byte Reload
	movq	%r14, %rcx
	movq	%r14, %r12
	movq	64(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB28_1
# BB#7:                                 # %entry_ifend42
                                        #   in Loop: Header=BB28_6 Depth=1
	movq	(%rax), %rax
	cmpl	%eax, %ebp
	jge	.LBB28_8
# BB#10:                                # %entry_condend
                                        #   in Loop: Header=BB28_6 Depth=1
	movl	$0, gSigInt(%rip)
	movl	$16456, %esi            # imm = 0x4048
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r14
	je	.LBB28_1
# BB#11:                                # %entry_ifend49
                                        #   in Loop: Header=BB28_6 Depth=1
	movq	16(%rsp), %rdi          # 8-byte Reload
	leal	(%rdi,%rbp), %ecx
	movq	$0, (%r15)
	movq	64(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, (%r15)
	movq	$0, 8(%r15)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%r15)
	movq	$0, 16(%r15)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 16(%r15)
	movq	$0, 24(%r15)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 24(%r15)
	movq	$0, 32(%r15)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 32(%r15)
	movq	$0, 40(%r15)
	movq	%rdi, 40(%r15)
	movq	$0, 48(%r15)
	movq	%rbp, 48(%r15)
	movq	(%r14), %rdx
	movq	$0, (%rdx)
	movl	%esi, %esi
	movq	%rsi, (%rdx)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movl	%ebp, %esi
	movq	%rsi, 8(%rdx)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movl	%ecx, %ecx
	movq	%rcx, 8(%rdx)
	addq	$8, (%r14)
	movl	$13, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	76(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r12, %rbp
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r13, %rbx
	jne	.LBB28_12
# BB#13:                                # %entry_ifend76
                                        #   in Loop: Header=BB28_6 Depth=1
	movq	(%rbx), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	8(%rbx), %rax
	movq	%rax, 64(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	16(%rbx), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	24(%rbx), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	32(%rbx), %rbp
	movq	$0, 112(%rsp)
	movq	%rbp, 112(%rsp)
	movq	40(%rbx), %r13
	movq	$0, 120(%rsp)
	movq	%r13, 120(%rsp)
	movq	48(%rbx), %r12
	movq	$0, 128(%rsp)
	movq	%r12, 128(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$16464, %esi            # imm = 0x4050
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB28_1
# BB#14:                                # %entry_ifend100
                                        #   in Loop: Header=BB28_6 Depth=1
	movq	$0, (%r15)
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r15)
	movq	$0, 8(%r15)
	movq	64(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 8(%r15)
	movq	$0, 16(%r15)
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 16(%r15)
	movq	$0, 24(%r15)
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 24(%r15)
	movq	$0, 32(%r15)
	movq	%rbp, 32(%r15)
	movq	$0, 40(%r15)
	movq	%r13, 40(%r15)
	movq	$0, 48(%r15)
	movq	%r12, 48(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$14, %esi
	movq	%rax, %rdi
	movq	8(%rsp), %r13           # 8-byte Reload
	movq	%r13, %rdx
	movl	76(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	56(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB28_15
# BB#16:                                # %entry_ifend124
                                        #   in Loop: Header=BB28_6 Depth=1
	movq	(%r13), %rax
	movq	%rax, 64(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	16(%r13), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	24(%r13), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	32(%r13), %r12
	movq	$0, 112(%rsp)
	movq	%r12, 112(%rsp)
	movq	40(%r13), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	48(%r13), %rbp
	movq	$0, 128(%rsp)
	movq	%rbp, 128(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%r14, %rax
	testb	$1, %bl
	je	.LBB28_17
# BB#18:                                # %entry_condend147
                                        #   in Loop: Header=BB28_6 Depth=1
	movl	$0, gSigInt(%rip)
	incl	%r12d
	movq	%r12, 24(%rsp)          # 8-byte Spill
	movq	$0, 112(%rsp)
	movq	%r12, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movq	48(%rsp), %rcx          # 8-byte Reload
	cmpl	%ecx, %r12d
	jne	.LBB28_19
	jmp	.LBB28_20
	.align	16, 0x90
.LBB28_17:                              #   in Loop: Header=BB28_6 Depth=1
	movq	%r12, 24(%rsp)          # 8-byte Spill
	jmp	.LBB28_19
.LBB28_8:
	movq	40(%rsp), %rax          # 8-byte Reload
	jmp	.LBB28_9
.LBB28_12:                              # %then_block75
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB28_1
.LBB28_15:                              # %then_block123
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB28_1
.LBB28_20:                              # %entry_condend154
	movl	$0, gSigInt(%rip)
	movq	$0, 104(%rsp)
	movl	%ebp, %eax
	movq	%rax, 104(%rsp)
	movl	$0, gSigInt(%rip)
.LBB28_9:                               # %label_for_endzzzzzzzzzzzzzzzzzzzf
	movl	$0, gSigInt(%rip)
	movl	%eax, %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB28_2
.Lfunc_end28:
	.size	"String.indexOf(Self,int)$$32", .Lfunc_end28-"String.indexOf(Self,int)$$32"
	.cfi_endproc

	.globl	"String.indexOf(Self)$$33"
	.align	16, 0x90
	.type	"String.indexOf(Self)$$33",@function
"String.indexOf(Self)$$33":             # @"String.indexOf(Self)$$33"
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
	movl	$16796, %esi            # imm = 0x419C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB29_1
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
	movq	$1, 8(%rcx)
	addq	$8, (%rbx)
	movl	$32, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB29_5
# BB#4:                                 # %then_block15
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB29_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB29_2
.LBB29_5:                               # %entry_ifend16
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
.LBB29_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end29:
	.size	"String.indexOf(Self)$$33", .Lfunc_end29-"String.indexOf(Self)$$33"
	.cfi_endproc

	.globl	"String.indexOf(regex,int)$$34"
	.align	16, 0x90
	.type	"String.indexOf(regex,int)$$34",@function
"String.indexOf(regex,int)$$34":        # @"String.indexOf(regex,int)$$34"
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
	subq	$232, %rsp
.Ltmp373:
	.cfi_def_cfa_offset 288
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
	movl	%r9d, 100(%rsp)         # 4-byte Spill
	movq	%r8, %r12
	movq	%rcx, %r13
	movq	%rdx, 104(%rsp)         # 8-byte Spill
	movq	%rsi, %r15
	movq	288(%rsp), %rdi
	movq	(%r13), %r14
	movq	$0, 112(%rsp)
	movq	%r14, 112(%rsp)
	movq	8(%r13), %rbx
	movq	$0, 120(%rsp)
	movq	%rbx, 120(%rsp)
	movq	16(%r13), %rbp
	movq	$0, 128(%rsp)
	movq	%rbp, 128(%rsp)
	movq	$0, 136(%rsp)
	movq	$0, 144(%rsp)
	movq	$0, 152(%rsp)
	movq	$0, 160(%rsp)
	movq	$0, 168(%rsp)
	movq	$0, 176(%rsp)
	movq	$0, 184(%rsp)
	movq	$0, 192(%rsp)
	movq	$0, 200(%rsp)
	movq	$0, 208(%rsp)
	movq	$0, 216(%rsp)
	movq	$0, 224(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 136(%rsp)
	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
	movq	%rax, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 152(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$16804, %esi            # imm = 0x41A4
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB30_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r15)
	movq	%r14, (%r15)
	movq	$0, 8(%r15)
	movq	%rbx, 8(%r15)
	movq	$0, 16(%r15)
	movq	%rbp, 16(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	$0, 56(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	$0, 72(%r15)
	movq	$0, 80(%r15)
	movq	200(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	208(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	216(%rsp), %rcx
	movq	$0, 104(%r15)
	movq	%rcx, 104(%r15)
	movq	$0, 112(%r15)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	100(%rsp), %ecx         # 4-byte Reload
	movq	%r12, %r8
	movq	104(%rsp), %rbx         # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB30_5
# BB#4:                                 # %then_block36
	callq	get_try_catch_label_name
	jmp	.LBB30_1
.LBB30_5:                               # %entry_ifend37
	movq	(%r13), %rax
	movq	%rax, 88(%rsp)          # 8-byte Spill
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 80(%rsp)          # 8-byte Spill
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	16(%r13), %rax
	movq	%rax, 72(%rsp)          # 8-byte Spill
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	24(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	32(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	40(%r13), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	48(%r13), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	56(%r13), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	64(%r13), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	72(%r13), %rax
	movq	%rax, 64(%rsp)          # 8-byte Spill
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	80(%r13), %r14
	movq	$0, 192(%rsp)
	movq	%r14, 192(%rsp)
	movq	88(%r13), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	96(%r13), %rax
	movq	$0, 208(%rsp)
	movq	%rax, 208(%rsp)
	movq	104(%r13), %rax
	movq	$0, 216(%rsp)
	movq	%rax, 216(%rsp)
	movq	112(%r13), %rbp
	movq	$0, 224(%rsp)
	movq	%rbp, 224(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 160(%rsp)
	movq	%rbx, 160(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 168(%rsp)
	movq	$16, 168(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$16812, %esi            # imm = 0x41AC
	movq	288(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB30_1
# BB#6:                                 # %entry_ifend72
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$16824, %esi            # imm = 0x41B8
	movq	288(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB30_1
# BB#7:                                 # %entry_ifend76
	movq	$0, (%r15)
	movq	88(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r15)
	movq	$0, 8(%r15)
	movq	80(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%r15)
	movq	$0, 16(%r15)
	movq	72(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 16(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	$0, 56(%r15)
	movq	$16, 56(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	$0, 72(%r15)
	movq	64(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 72(%r15)
	movq	$0, 80(%r15)
	movq	%r14, 80(%r15)
	movq	200(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	208(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	216(%rsp), %rcx
	movq	$0, 104(%r15)
	movq	%rcx, 104(%r15)
	movq	$0, 112(%r15)
	movq	%rbp, 112(%r15)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	$16, 8(%rcx)
	addq	$8, (%r12)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	100(%rsp), %ebp         # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r12, %r8
	movq	104(%rsp), %rbx         # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	movq	%r12, %r14
	movl	%ebp, %r12d
	je	.LBB30_9
# BB#8:                                 # %then_block115
	callq	get_try_catch_label_name
.LBB30_1:                               # %then_block
	xorl	%eax, %eax
.LBB30_2:                               # %then_block
	addq	$232, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB30_9:                               # %entry_ifend116
	movl	%r12d, %ebp
	movq	(%r13), %rax
	movq	%rax, 72(%rsp)          # 8-byte Spill
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 80(%rsp)          # 8-byte Spill
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	16(%r13), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	24(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	32(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	40(%r13), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	48(%r13), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	56(%r13), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	64(%r13), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	72(%r13), %rax
	movq	%rax, 64(%rsp)          # 8-byte Spill
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	80(%r13), %rax
	movq	%rax, 56(%rsp)          # 8-byte Spill
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	88(%r13), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	96(%r13), %rax
	movq	$0, 208(%rsp)
	movq	%rax, 208(%rsp)
	movq	104(%r13), %rax
	movq	$0, 216(%rsp)
	movq	%rax, 216(%rsp)
	movq	112(%r13), %rax
	movq	%rax, 88(%rsp)          # 8-byte Spill
	movq	%r13, %r12
	movq	$0, 224(%rsp)
	movq	%rax, 224(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%r14, 16(%rsp)          # 8-byte Spill
	movq	$0, 176(%rsp)
	movq	%rbx, 176(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB30_10
.LBB30_42:                              # %entry_condend472
                                        #   in Loop: Header=BB30_10 Depth=1
	movl	144(%rsp), %eax
	incl	%eax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
.LBB30_10:                              # %entry_condend
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	movl	160(%rsp), %r14d
	movl	144(%rsp), %eax
	movl	%eax, 28(%rsp)          # 4-byte Spill
	movl	176(%rsp), %eax
	movl	%eax, 32(%rsp)          # 4-byte Spill
	movl	$16908, %esi            # imm = 0x420C
	movq	288(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	104(%rsp), %r13         # 8-byte Reload
	movq	16(%rsp), %rbx          # 8-byte Reload
	je	.LBB30_1
# BB#11:                                # %entry_ifend160
                                        #   in Loop: Header=BB30_10 Depth=1
	movq	$0, (%r15)
	movq	72(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r15)
	movq	$0, 8(%r15)
	movq	80(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%r15)
	movq	$0, 16(%r15)
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 16(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	$0, 56(%r15)
	movq	48(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 56(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	$0, 72(%r15)
	movq	64(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 72(%r15)
	movq	$0, 80(%r15)
	movq	56(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 80(%r15)
	movq	200(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	208(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	216(%rsp), %rcx
	movq	$0, 104(%r15)
	movq	%rcx, 104(%r15)
	movq	$0, 112(%r15)
	movq	88(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 112(%r15)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
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
	movl	32(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$25, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebp, %ecx
	movq	%rbx, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rbp
	movq	%r12, %r14
	jne	.LBB30_12
# BB#13:                                # %entry_ifend209
                                        #   in Loop: Header=BB30_10 Depth=1
	movq	(%r14), %rax
	movq	%rax, 72(%rsp)          # 8-byte Spill
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	8(%r14), %rax
	movq	%rax, 80(%rsp)          # 8-byte Spill
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	16(%r14), %r12
	movq	$0, 128(%rsp)
	movq	%r12, 128(%rsp)
	movq	24(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	32(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	40(%r14), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	48(%r14), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	56(%r14), %r13
	movq	$0, 168(%rsp)
	movq	%r13, 168(%rsp)
	movq	64(%r14), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	72(%r14), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	80(%r14), %rax
	movq	%rax, 56(%rsp)          # 8-byte Spill
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	88(%r14), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	96(%r14), %rax
	movq	$0, 208(%rsp)
	movq	%rax, 208(%rsp)
	movq	104(%r14), %rax
	movq	$0, 216(%rsp)
	movq	%rax, 216(%rsp)
	movq	112(%r14), %rax
	movq	%rax, 88(%rsp)          # 8-byte Spill
	movq	$0, 224(%rsp)
	movq	%rax, 224(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movq	%rbx, 64(%rsp)          # 8-byte Spill
	movl	%ebx, %edi
	callq	push_jit_object
	movq	%rbp, %rdi
	addq	$-8, (%rdi)
	movq	$0, 184(%rsp)
	movq	%rbx, 184(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%ebx, %ebx
	jle	.LBB30_31
# BB#14:                                # %entry_condend249
                                        #   in Loop: Header=BB30_10 Depth=1
	movq	%r13, 48(%rsp)          # 8-byte Spill
	movl	152(%rsp), %r13d
	incl	%r13d
	movq	$0, 152(%rsp)
	movq	%r13, 152(%rsp)
	movl	$0, gSigInt(%rip)
	cmpl	%r12d, %r13d
	movq	%r12, 40(%rsp)          # 8-byte Spill
	je	.LBB30_15
# BB#39:                                # %label_if_endzzzzzzzzzzzzzzzzzzzk
                                        #   in Loop: Header=BB30_10 Depth=1
	movl	144(%rsp), %r13d
	movl	176(%rsp), %r8d
	movl	$1, %r9d
	movq	%r14, %rsi
	movl	100(%rsp), %ebp         # 4-byte Reload
	movl	%ebp, %edx
	movq	104(%rsp), %rbx         # 8-byte Reload
	movq	%rdi, %r12
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%rbx, %rcx
	movq	%r12, %rdi
	je	.LBB30_1
# BB#40:                                # %entry_ifend464
                                        #   in Loop: Header=BB30_10 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r14, %rsi
	movl	%ebp, %edx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB30_1
# BB#41:                                # %entry_ifend468
                                        #   in Loop: Header=BB30_10 Depth=1
	movq	%r14, %r12
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r13d
	je	.LBB30_42
# BB#43:                                # %label_elsezzzzzzzzzzzzzzzzzzzq
                                        #   in Loop: Header=BB30_10 Depth=1
	movl	176(%rsp), %r8d
	movl	$1, %r9d
	movq	16(%rsp), %r14          # 8-byte Reload
	movq	%r14, %rdi
	movq	%r12, %rsi
	movl	%ebp, %edx
	movq	104(%rsp), %rbx         # 8-byte Reload
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB30_1
# BB#44:                                # %entry_ifend480
                                        #   in Loop: Header=BB30_10 Depth=1
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r12, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB30_1
# BB#45:                                # %entry_ifend484
                                        #   in Loop: Header=BB30_10 Depth=1
	movq	(%rax), %rax
	movq	$0, 144(%rsp)
	movl	%eax, %eax
	movq	%rax, 144(%rsp)
	jmp	.LBB30_10
.LBB30_12:                              # %then_block208
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB30_1
.LBB30_15:                              # %entry_condend255
	movl	176(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rsi
	movl	100(%rsp), %r12d        # 4-byte Reload
	movl	%r12d, %edx
	movq	104(%rsp), %rbx         # 8-byte Reload
	movq	%rdi, %rbp
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%rbx, %rcx
	je	.LBB30_1
# BB#16:                                # %entry_ifend259
	movq	(%rax), %r8
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	movq	%rcx, %rbx
	callq	load_element
	movq	%rbx, %rsi
	cmpl	$0, 8(%rax)
	je	.LBB30_1
# BB#17:                                # %entry_ifend262
	movl	%r12d, %edx
	movq	%r14, %rbx
	movq	%rbp, %rcx
	movq	%rsi, %rbp
	movq	(%rax), %rax
	movq	$0, 192(%rsp)
	movl	%eax, %esi
	movq	%rsi, 56(%rsp)          # 8-byte Spill
	movq	%rsi, 192(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%eax, %eax
	je	.LBB30_18
# BB#19:                                # %label_elsezzzzzzzzzzzzzzzzzzzl
	movq	$0, 200(%rsp)
	movl	$0, gSigInt(%rip)
	movl	160(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rcx, %r14
	movq	%r14, %rdi
	movq	%rbx, %r12
	movq	%r12, %rsi
	movl	%edx, %ebx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB30_1
# BB#20:                                # %entry_ifend272
	movl	%ebx, %r10d
	movq	%r14, %rcx
	movq	(%rax), %r14
	movq	$0, 208(%rsp)
	movq	%r14, 208(%rsp)
	movl	$0, gSigInt(%rip)
	movq	%r12, %rbx
	jmp	.LBB30_21
.LBB30_38:                              # %label_if_endzzzzzzzzzzzzzzzzzzzp
                                        #   in Loop: Header=BB30_21 Depth=1
	movq	208(%rsp), %r14
	movq	%rdx, %rbx
.LBB30_21:                              # %while_start_pointzzzzzzzzzzzzzzzzzzzm
                                        # =>This Inner Loop Header: Depth=1
	movl	160(%rsp), %r8d
	movl	$1, %r9d
	movq	%rcx, %r12
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB30_1
# BB#22:                                # %entry_ifend278
                                        #   in Loop: Header=BB30_21 Depth=1
	movq	(%rax), %rax
	addq	%r14, %rax
	cmpq	%rax, %r14
	movq	%rbx, %r14
	jae	.LBB30_30
# BB#23:                                # %entry_condend282
                                        #   in Loop: Header=BB30_21 Depth=1
	movl	$0, gSigInt(%rip)
	movq	208(%rsp), %rsi
	movq	72(%rsp), %rax          # 8-byte Reload
	movq	%rax, (%r15)
	movq	80(%rsp), %rax          # 8-byte Reload
	movq	%rax, 8(%r15)
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	%rax, 16(%r15)
	movq	136(%rsp), %rax
	movq	%rax, 24(%r15)
	movq	144(%rsp), %rax
	movq	%rax, 32(%r15)
	movq	%r13, 40(%r15)
	movq	160(%rsp), %rax
	movq	%rax, 48(%r15)
	movq	48(%rsp), %rax          # 8-byte Reload
	movq	%rax, 56(%r15)
	movq	176(%rsp), %rax
	movq	%rax, 64(%r15)
	movq	64(%rsp), %rax          # 8-byte Reload
	movq	%rax, 72(%r15)
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	%rax, 80(%r15)
	movq	200(%rsp), %rcx
	movq	%rcx, 88(%r15)
	movq	%rsi, 96(%r15)
	movq	216(%rsp), %rax
	movq	%rax, 104(%r15)
	movq	88(%rsp), %rax          # 8-byte Reload
	movq	%rax, 112(%r15)
	movb	(%rsi), %al
	movq	$0, 216(%rsp)
	movzbl	%al, %edx
	movq	%rdx, 216(%rsp)
	movl	$0, gSigInt(%rip)
	testb	%dl, %dl
	jns	.LBB30_34
# BB#24:                                # %entry_condend317
                                        #   in Loop: Header=BB30_21 Depth=1
	movq	%rdx, 32(%rsp)          # 8-byte Spill
	movb	%al, %cl
	shrb	$7, %cl
	movb	%al, %dl
	andb	$64, %dl
	shrb	$6, %dl
	addb	%cl, %dl
	movb	%al, %cl
	andb	$32, %cl
	shrb	$5, %cl
	addb	%dl, %cl
	andb	$16, %al
	shrb	$4, %al
	addb	%cl, %al
	movzbl	%al, %eax
	movq	%rax, 88(%rsp)          # 8-byte Spill
	movq	$0, 224(%rsp)
	movq	%rax, 224(%rsp)
	movl	$0, gSigInt(%rip)
	movq	288(%rsp), %rax
	movq	%rax, (%rsp)
	xorl	%r8d, %r8d
	movl	$17188, %r9d            # imm = 0x4324
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	100(%rsp), %edx         # 4-byte Reload
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB30_1
# BB#25:                                # %entry_ifend334
                                        #   in Loop: Header=BB30_21 Depth=1
	movq	%r14, %rbx
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	movq	88(%rsp), %rcx          # 8-byte Reload
	cmpl	%eax, %ecx
	jg	.LBB30_26
# BB#32:                                # %label_elsezzzzzzzzzzzzzzzzzzzo
                                        #   in Loop: Header=BB30_21 Depth=1
	movl	%ecx, %eax
	addq	208(%rsp), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 208(%rsp)
	movq	%rax, 208(%rsp)
	movl	$0, gSigInt(%rip)
	movl	200(%rsp), %eax
	incl	%eax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	%rbx, %r14
	jmp	.LBB30_35
.LBB30_34:                              # %label_elsezzzzzzzzzzzzzzzzzzzn
                                        #   in Loop: Header=BB30_21 Depth=1
	incq	%rsi
	movq	%rsi, 32(%rsp)          # 8-byte Spill
	movq	$0, 208(%rsp)
	movq	%rsi, 208(%rsp)
	movl	$0, gSigInt(%rip)
	incl	%ecx
	movq	$0, 200(%rsp)
	movq	%rcx, 200(%rsp)
.LBB30_35:                              # %label_if_endzzzzzzzzzzzzzzzzzzzn
                                        #   in Loop: Header=BB30_21 Depth=1
	movl	$0, gSigInt(%rip)
	movl	160(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	100(%rsp), %ebx         # 4-byte Reload
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB30_1
# BB#36:                                # %entry_ifend443
                                        #   in Loop: Header=BB30_21 Depth=1
	movl	%ebx, %r10d
	movq	%r14, %rdx
	movq	%r12, %rcx
	movq	32(%rsp), %rsi          # 8-byte Reload
	subq	(%rax), %rsi
	cmpq	56(%rsp), %rsi          # 8-byte Folded Reload
	jne	.LBB30_38
# BB#37:                                # %entry_condend452
	movl	$0, gSigInt(%rip)
	movq	%rdx, %r14
.LBB30_30:                              # %label_whilezzzzzzzzzzzzzzzzzzzm
	movl	$0, gSigInt(%rip)
	movl	200(%rsp), %eax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB30_31
.LBB30_18:                              # %entry_condend267
	movq	$0, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movq	%rbx, %r14
.LBB30_31:                              # %label_whilezzzzzzzzzzzzzzzzzzzi
	movl	$0, gSigInt(%rip)
	movl	136(%rsp), %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB30_2
.LBB30_26:                              # %entry_condend338
	movl	$17228, %esi            # imm = 0x434C
	movq	288(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbp, %r14
	movq	%r12, %rbp
	movl	100(%rsp), %r12d        # 4-byte Reload
	je	.LBB30_1
# BB#27:                                # %entry_ifend341
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 28(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.4, %edi
	callq	create_string_object
	movl	%eax, 16(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$17276, %esi            # imm = 0x437C
	movq	288(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB30_1
# BB#28:                                # %entry_ifend344
	movq	$0, (%r15)
	movq	72(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r15)
	movq	$0, 8(%r15)
	movq	80(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%r15)
	movq	$0, 16(%r15)
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 16(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	$0, 40(%r15)
	movq	%r13, 40(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	$0, 56(%r15)
	movq	48(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 56(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	$0, 72(%r15)
	movq	64(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 72(%r15)
	movq	$0, 80(%r15)
	movq	56(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 80(%r15)
	movq	200(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	208(%rsp), %rcx
	movq	$0, 96(%r15)
	movq	%rcx, 96(%r15)
	movq	$0, 104(%r15)
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 104(%r15)
	movq	$0, 112(%r15)
	movq	88(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 112(%r15)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	16(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r12d, %ecx
	movq	%rbp, %r8
	movq	%rbp, %r15
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB30_33
# BB#29:                                # %then_block383
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB30_1
.LBB30_33:                              # %entry_ifend384
	movq	%rbx, %rbp
	movq	(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	88(%rbp), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	96(%rbp), %rax
	movq	$0, 208(%rsp)
	movq	%rax, 208(%rsp)
	movq	104(%rbp), %rax
	movq	$0, 216(%rsp)
	movq	%rax, 216(%rsp)
	movq	112(%rbp), %rax
	movq	$0, 224(%rsp)
	movq	%rax, 224(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbx, (%rbp)
	movl	%ebx, %edi
	movq	%r14, %rsi
	callq	entry_exception_object
	jmp	.LBB30_1
.Lfunc_end30:
	.size	"String.indexOf(regex,int)$$34", .Lfunc_end30-"String.indexOf(regex,int)$$34"
	.cfi_endproc

	.globl	"String.indexOf(regex)$$35"
	.align	16, 0x90
	.type	"String.indexOf(regex)$$35",@function
"String.indexOf(regex)$$35":            # @"String.indexOf(regex)$$35"
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
	subq	$24, %rsp
.Ltmp386:
	.cfi_def_cfa_offset 80
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
	movl	$18372, %esi            # imm = 0x47C4
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB31_1
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
	movq	$1, 8(%rcx)
	addq	$8, (%rbx)
	movl	$34, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB31_5
# BB#4:                                 # %then_block15
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB31_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB31_2
.LBB31_5:                               # %entry_ifend16
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
	.size	"String.indexOf(regex)$$35", .Lfunc_end31-"String.indexOf(regex)$$35"
	.cfi_endproc

	.globl	"String.reverse()$$36"
	.align	16, 0x90
	.type	"String.reverse()$$36",@function
"String.reverse()$$36":                 # @"String.reverse()$$36"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp393:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp394:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp395:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp396:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp397:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp398:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp399:
	.cfi_def_cfa_offset 128
.Ltmp400:
	.cfi_offset %rbx, -56
.Ltmp401:
	.cfi_offset %r12, -48
.Ltmp402:
	.cfi_offset %r13, -40
.Ltmp403:
	.cfi_offset %r14, -32
.Ltmp404:
	.cfi_offset %r15, -24
.Ltmp405:
	.cfi_offset %rbp, -16
	movl	%r9d, 36(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, %r12
	movq	%rsi, %rbx
	movq	128(%rsp), %rdi
	movq	(%r15), %rbp
	movq	$0, 48(%rsp)
	movq	%rbp, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$18380, %esi            # imm = 0x47CC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB32_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB32_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movl	$18388, %esi            # imm = 0x47D4
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB32_1
# BB#5:                                 # %entry_ifend6
	movq	$0, (%rbx)
	movq	%rbp, (%rbx)
	movq	$0, 8(%rbx)
	movq	$0, 16(%rbx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	36(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r12, %rbx
	je	.LBB32_7
# BB#6:                                 # %then_block18
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
.LBB32_7:                               # %entry_ifend19
	movq	(%r15), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r12
	movq	%r12, 16(%rsp)          # 8-byte Spill
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 56(%rsp)
	movq	%r12, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 64(%rsp)
	xorl	%eax, %eax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	jmp	.LBB32_8
	.align	16, 0x90
.LBB32_15:                              # %entry_ifend52
                                        #   in Loop: Header=BB32_8 Depth=1
	movq	40(%rsp), %rax          # 8-byte Reload
	incl	%eax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%rbp, %rbx
	movl	%r12d, %ebp
.LBB32_8:                               # %for_start_pointzzzzzzzzzzzzzzzzzzzr
                                        # =>This Inner Loop Header: Depth=1
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rbx, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%rbx, %rcx
	movl	%ebp, %edx
	je	.LBB32_1
# BB#9:                                 # %entry_ifend31
                                        #   in Loop: Header=BB32_8 Depth=1
	movq	(%rax), %r12
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%edx, %ebx
	movq	%rcx, %rbp
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	movq	(%rax), %r13
	movl	8(%rax), %eax
	movq	40(%rsp), %rcx          # 8-byte Reload
	cmpl	%r12d, %ecx
	jge	.LBB32_16
# BB#10:                                # %entry_condend
                                        #   in Loop: Header=BB32_8 Depth=1
	testl	%eax, %eax
	movl	%ebx, %r12d
	je	.LBB32_1
# BB#11:                                # %entry_ifend35
                                        #   in Loop: Header=BB32_8 Depth=1
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r12d, %edx
	movq	%rbp, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB32_1
# BB#12:                                # %entry_ifend40
                                        #   in Loop: Header=BB32_8 Depth=1
	movq	(%rax), %rbx
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r12d, %edx
	movq	%rbp, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB32_1
# BB#13:                                # %entry_ifend44
                                        #   in Loop: Header=BB32_8 Depth=1
	movq	(%rax), %r9
	movq	40(%rsp), %rax          # 8-byte Reload
	subl	%eax, %r9d
	decl	%r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r12d, %edx
	movq	%rbp, %rcx
	movl	%ebx, %r8d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB32_1
# BB#14:                                # %entry_ifend49
                                        #   in Loop: Header=BB32_8 Depth=1
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r12d, %edx
	movq	%rbp, %rcx
	movl	%r13d, %r8d
	movq	40(%rsp), %r9           # 8-byte Reload
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB32_15
	jmp	.LBB32_1
.LBB32_16:                              # %label_for_endzzzzzzzzzzzzzzzzzzzr
	testl	%eax, %eax
	movq	%rbp, %r12
	movl	%ebx, %ebp
	je	.LBB32_1
# BB#17:                                # %entry_ifend59
	movq	$0, (%rsp)
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movl	%r13d, %r8d
	movq	40(%rsp), %r9           # 8-byte Reload
	callq	run_store_element
	testl	%eax, %eax
	je	.LBB32_1
# BB#18:                                # %entry_ifend63
	movl	$0, gSigInt(%rip)
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB32_1
# BB#19:                                # %entry_ifend68
	movq	(%rax), %rax
	movl	%eax, %r9d
	movl	$2, (%rsp)
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB32_1
# BB#20:                                # %entry_ifend71
	movl	$0, gSigInt(%rip)
	movq	16(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%r15)
	movl	$1, %eax
	jmp	.LBB32_2
.Lfunc_end32:
	.size	"String.reverse()$$36", .Lfunc_end32-"String.reverse()$$36"
	.cfi_endproc

	.globl	"String.upperCase()$$37"
	.align	16, 0x90
	.type	"String.upperCase()$$37",@function
"String.upperCase()$$37":               # @"String.upperCase()$$37"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp406:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp407:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp408:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp409:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp410:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp411:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp412:
	.cfi_def_cfa_offset 96
.Ltmp413:
	.cfi_offset %rbx, -56
.Ltmp414:
	.cfi_offset %r12, -48
.Ltmp415:
	.cfi_offset %r13, -40
.Ltmp416:
	.cfi_offset %r14, -32
.Ltmp417:
	.cfi_offset %r15, -24
.Ltmp418:
	.cfi_offset %rbp, -16
	movl	%r9d, %r14d
	movq	%r8, %r12
	movq	%rcx, %rbx
	movq	%rdx, %r13
	movq	(%rbx), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 32(%rsp)
	xorl	%ebp, %ebp
	jmp	.LBB33_1
	.align	16, 0x90
.LBB33_9:                               # %entry_ifend17
                                        #   in Loop: Header=BB33_1 Depth=1
	incl	%ebp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
.LBB33_1:                               # %for_start_pointzzzzzzzzzzzzzzzzzzzs
                                        # =>This Inner Loop Header: Depth=1
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB33_2
# BB#4:                                 # %entry_ifend
                                        #   in Loop: Header=BB33_1 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %ebp
	jge	.LBB33_10
# BB#5:                                 # %entry_condend
                                        #   in Loop: Header=BB33_1 Depth=1
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB33_2
# BB#6:                                 # %entry_ifend5
                                        #   in Loop: Header=BB33_1 Depth=1
	movq	(%rax), %r15
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB33_2
# BB#7:                                 # %entry_ifend10
                                        #   in Loop: Header=BB33_1 Depth=1
	movq	(%rax), %r8
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movl	%ebp, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB33_2
# BB#8:                                 # %entry_ifend14
                                        #   in Loop: Header=BB33_1 Depth=1
	movq	(%rax), %rdi
	callq	char_uppercase
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movl	%r15d, %r8d
	movl	%ebp, %r9d
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB33_9
.LBB33_2:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB33_3
.LBB33_10:                              # %label_for_endzzzzzzzzzzzzzzzzzzzs
	movq	16(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
.LBB33_3:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end33:
	.size	"String.upperCase()$$37", .Lfunc_end33-"String.upperCase()$$37"
	.cfi_endproc

	.globl	"String.lowerCase()$$38"
	.align	16, 0x90
	.type	"String.lowerCase()$$38",@function
"String.lowerCase()$$38":               # @"String.lowerCase()$$38"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp419:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp420:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp421:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp422:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp423:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp424:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp425:
	.cfi_def_cfa_offset 96
.Ltmp426:
	.cfi_offset %rbx, -56
.Ltmp427:
	.cfi_offset %r12, -48
.Ltmp428:
	.cfi_offset %r13, -40
.Ltmp429:
	.cfi_offset %r14, -32
.Ltmp430:
	.cfi_offset %r15, -24
.Ltmp431:
	.cfi_offset %rbp, -16
	movl	%r9d, %r14d
	movq	%r8, %r12
	movq	%rcx, %rbx
	movq	%rdx, %r13
	movq	(%rbx), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 32(%rsp)
	xorl	%ebp, %ebp
	jmp	.LBB34_1
	.align	16, 0x90
.LBB34_9:                               # %entry_ifend17
                                        #   in Loop: Header=BB34_1 Depth=1
	incl	%ebp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
.LBB34_1:                               # %for_start_pointzzzzzzzzzzzzzzzzzzzt
                                        # =>This Inner Loop Header: Depth=1
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB34_2
# BB#4:                                 # %entry_ifend
                                        #   in Loop: Header=BB34_1 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %ebp
	jge	.LBB34_10
# BB#5:                                 # %entry_condend
                                        #   in Loop: Header=BB34_1 Depth=1
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB34_2
# BB#6:                                 # %entry_ifend5
                                        #   in Loop: Header=BB34_1 Depth=1
	movq	(%rax), %r15
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movq	16(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB34_2
# BB#7:                                 # %entry_ifend10
                                        #   in Loop: Header=BB34_1 Depth=1
	movq	(%rax), %r8
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movl	%ebp, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB34_2
# BB#8:                                 # %entry_ifend14
                                        #   in Loop: Header=BB34_1 Depth=1
	movq	(%rax), %rdi
	callq	char_lowercase
	movl	%eax, %eax
	movq	%rax, (%rsp)
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movl	%r15d, %r8d
	movl	%ebp, %r9d
	callq	run_store_element
	testl	%eax, %eax
	jne	.LBB34_9
.LBB34_2:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB34_3
.LBB34_10:                              # %label_for_endzzzzzzzzzzzzzzzzzzzt
	movq	16(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
.LBB34_3:                               # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end34:
	.size	"String.lowerCase()$$38", .Lfunc_end34-"String.lowerCase()$$38"
	.cfi_endproc

	.globl	"String.to_int()$$39"
	.align	16, 0x90
	.type	"String.to_int()$$39",@function
"String.to_int()$$39":                  # @"String.to_int()$$39"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp432:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp433:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp434:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp435:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp436:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp437:
	.cfi_def_cfa_offset 56
	pushq	%rax
.Ltmp438:
	.cfi_def_cfa_offset 64
.Ltmp439:
	.cfi_offset %rbx, -56
.Ltmp440:
	.cfi_offset %r12, -48
.Ltmp441:
	.cfi_offset %r13, -40
.Ltmp442:
	.cfi_offset %r14, -32
.Ltmp443:
	.cfi_offset %r15, -24
.Ltmp444:
	.cfi_offset %rbp, -16
	movl	%r9d, %r12d
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %rbp
	movq	64(%rsp), %rdi
	movq	(%r14), %rbx
	movq	$0, (%rsp)
	movq	%rbx, (%rsp)
	movl	$0, gSigInt(%rip)
	movl	$18828, %esi            # imm = 0x498C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB35_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$26, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB35_5
# BB#4:                                 # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB35_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB35_2
.LBB35_5:                               # %entry_ifend6
	movq	(%r14), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%rbp, (%r14)
	movl	$1, %eax
.LBB35_2:                               # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end35:
	.size	"String.to_int()$$39", .Lfunc_end35-"String.to_int()$$39"
	.cfi_endproc

	.globl	"String.to_float()$$40"
	.align	16, 0x90
	.type	"String.to_float()$$40",@function
"String.to_float()$$40":                # @"String.to_float()$$40"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp445:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp446:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp447:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp448:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp449:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp450:
	.cfi_def_cfa_offset 56
	pushq	%rax
.Ltmp451:
	.cfi_def_cfa_offset 64
.Ltmp452:
	.cfi_offset %rbx, -56
.Ltmp453:
	.cfi_offset %r12, -48
.Ltmp454:
	.cfi_offset %r13, -40
.Ltmp455:
	.cfi_offset %r14, -32
.Ltmp456:
	.cfi_offset %r15, -24
.Ltmp457:
	.cfi_offset %rbp, -16
	movl	%r9d, %r12d
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %rbp
	movq	64(%rsp), %rdi
	movq	(%r14), %rbx
	movq	$0, (%rsp)
	movq	%rbx, (%rsp)
	movl	$0, gSigInt(%rip)
	movl	$18836, %esi            # imm = 0x4994
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB36_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$27, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB36_5
# BB#4:                                 # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB36_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB36_2
.LBB36_5:                               # %entry_ifend6
	movq	(%r14), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%rbp, (%r14)
	movl	$1, %eax
.LBB36_2:                               # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end36:
	.size	"String.to_float()$$40", .Lfunc_end36-"String.to_float()$$40"
	.cfi_endproc

	.globl	"String.to_double()$$41"
	.align	16, 0x90
	.type	"String.to_double()$$41",@function
"String.to_double()$$41":               # @"String.to_double()$$41"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp458:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp459:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp460:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp461:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp462:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp463:
	.cfi_def_cfa_offset 56
	pushq	%rax
.Ltmp464:
	.cfi_def_cfa_offset 64
.Ltmp465:
	.cfi_offset %rbx, -56
.Ltmp466:
	.cfi_offset %r12, -48
.Ltmp467:
	.cfi_offset %r13, -40
.Ltmp468:
	.cfi_offset %r14, -32
.Ltmp469:
	.cfi_offset %r15, -24
.Ltmp470:
	.cfi_offset %rbp, -16
	movl	%r9d, %r12d
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %rbp
	movq	64(%rsp), %rdi
	movq	(%r14), %rbx
	movq	$0, (%rsp)
	movq	%rbx, (%rsp)
	movl	$0, gSigInt(%rip)
	movl	$18844, %esi            # imm = 0x499C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB37_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$28, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB37_5
# BB#4:                                 # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB37_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB37_2
.LBB37_5:                               # %entry_ifend6
	movq	(%r14), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%rbp, (%r14)
	movl	$1, %eax
.LBB37_2:                               # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end37:
	.size	"String.to_double()$$41", .Lfunc_end37-"String.to_double()$$41"
	.cfi_endproc

	.globl	"String.multiply(int)$$42"
	.align	16, 0x90
	.type	"String.multiply(int)$$42",@function
"String.multiply(int)$$42":             # @"String.multiply(int)$$42"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp471:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp472:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp473:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp474:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp475:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp476:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp477:
	.cfi_def_cfa_offset 112
.Ltmp478:
	.cfi_offset %rbx, -56
.Ltmp479:
	.cfi_offset %r12, -48
.Ltmp480:
	.cfi_offset %r13, -40
.Ltmp481:
	.cfi_offset %r14, -32
.Ltmp482:
	.cfi_offset %r15, -24
.Ltmp483:
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
	movl	$18852, %esi            # imm = 0x49A4
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB38_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$18860, %esi            # imm = 0x49AC
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB38_1
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
	je	.LBB38_6
# BB#5:                                 # %then_block14
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB38_1
.LBB38_6:                               # %entry_ifend15
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
	jmp	.LBB38_7
	.align	16, 0x90
.LBB38_11:                              # %entry_ifend50
                                        #   in Loop: Header=BB38_7 Depth=1
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
.LBB38_7:                               # %for_start_pointzzzzzzzzzzzzzzzzzzzu
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	cmpl	%ebp, %r12d
	jge	.LBB38_12
# BB#8:                                 # %entry_condend
                                        #   in Loop: Header=BB38_7 Depth=1
	movl	$18940, %esi            # imm = 0x49FC
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB38_1
# BB#9:                                 # %entry_ifend32
                                        #   in Loop: Header=BB38_7 Depth=1
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
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %rbp           # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB38_11
# BB#10:                                # %then_block49
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB38_1:                               # %then_block
	xorl	%eax, %eax
.LBB38_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB38_12:                              # %label_for_endzzzzzzzzzzzzzzzzzzzu
	movl	%r13d, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB38_2
.Lfunc_end38:
	.size	"String.multiply(int)$$42", .Lfunc_end38-"String.multiply(int)$$42"
	.cfi_endproc

	.globl	"String.compare(Self)$$43"
	.align	16, 0x90
	.type	"String.compare(Self)$$43",@function
"String.compare(Self)$$43":             # @"String.compare(Self)$$43"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp484:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp485:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp486:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp487:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp488:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp489:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp490:
	.cfi_def_cfa_offset 80
.Ltmp491:
	.cfi_offset %rbx, -56
.Ltmp492:
	.cfi_offset %r12, -48
.Ltmp493:
	.cfi_offset %r13, -40
.Ltmp494:
	.cfi_offset %r14, -32
.Ltmp495:
	.cfi_offset %r15, -24
.Ltmp496:
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
	movl	$19020, %esi            # imm = 0x4A4C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB39_1
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
	movl	$29, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB39_5
# BB#4:                                 # %then_block12
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB39_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB39_2
.LBB39_5:                               # %entry_ifend13
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
.LBB39_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end39:
	.size	"String.compare(Self)$$43", .Lfunc_end39-"String.compare(Self)$$43"
	.cfi_endproc

	.globl	"String.compareWithIgnoreCase(Self)$$44"
	.align	16, 0x90
	.type	"String.compareWithIgnoreCase(Self)$$44",@function
"String.compareWithIgnoreCase(Self)$$44": # @"String.compareWithIgnoreCase(Self)$$44"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp497:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp498:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp499:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp500:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp501:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp502:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp503:
	.cfi_def_cfa_offset 80
.Ltmp504:
	.cfi_offset %rbx, -56
.Ltmp505:
	.cfi_offset %r12, -48
.Ltmp506:
	.cfi_offset %r13, -40
.Ltmp507:
	.cfi_offset %r14, -32
.Ltmp508:
	.cfi_offset %r15, -24
.Ltmp509:
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
	movl	$19028, %esi            # imm = 0x4A54
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB40_1
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
	movl	$30, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB40_5
# BB#4:                                 # %then_block12
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB40_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB40_2
.LBB40_5:                               # %entry_ifend13
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
.LBB40_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end40:
	.size	"String.compareWithIgnoreCase(Self)$$44", .Lfunc_end40-"String.compareWithIgnoreCase(Self)$$44"
	.cfi_endproc

	.globl	"String.hex()$$45"
	.align	16, 0x90
	.type	"String.hex()$$45",@function
"String.hex()$$45":                     # @"String.hex()$$45"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp510:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp511:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp512:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp513:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp514:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp515:
	.cfi_def_cfa_offset 56
	pushq	%rax
.Ltmp516:
	.cfi_def_cfa_offset 64
.Ltmp517:
	.cfi_offset %rbx, -56
.Ltmp518:
	.cfi_offset %r12, -48
.Ltmp519:
	.cfi_offset %r13, -40
.Ltmp520:
	.cfi_offset %r14, -32
.Ltmp521:
	.cfi_offset %r15, -24
.Ltmp522:
	.cfi_offset %rbp, -16
	movl	%r9d, %r12d
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %r13
	movq	64(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, (%rsp)
	movq	%rbp, (%rsp)
	movl	$0, gSigInt(%rip)
	movl	$19036, %esi            # imm = 0x4A5C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB41_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	addq	$8, (%rbx)
	movl	$31, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB41_5
# BB#4:                                 # %then_block8
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB41_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB41_2
.LBB41_5:                               # %entry_ifend9
	movq	(%r14), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbp, (%r14)
	movl	$1, %eax
.LBB41_2:                               # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end41:
	.size	"String.hex()$$45", .Lfunc_end41-"String.hex()$$45"
	.cfi_endproc

	.globl	"String.oct()$$46"
	.align	16, 0x90
	.type	"String.oct()$$46",@function
"String.oct()$$46":                     # @"String.oct()$$46"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp523:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp524:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp525:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp526:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp527:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp528:
	.cfi_def_cfa_offset 56
	pushq	%rax
.Ltmp529:
	.cfi_def_cfa_offset 64
.Ltmp530:
	.cfi_offset %rbx, -56
.Ltmp531:
	.cfi_offset %r12, -48
.Ltmp532:
	.cfi_offset %r13, -40
.Ltmp533:
	.cfi_offset %r14, -32
.Ltmp534:
	.cfi_offset %r15, -24
.Ltmp535:
	.cfi_offset %rbp, -16
	movl	%r9d, %r12d
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %r13
	movq	64(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, (%rsp)
	movq	%rbp, (%rsp)
	movl	$0, gSigInt(%rip)
	movl	$19044, %esi            # imm = 0x4A64
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB42_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	addq	$8, (%rbx)
	movl	$31, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB42_5
# BB#4:                                 # %then_block8
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB42_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB42_2
.LBB42_5:                               # %entry_ifend9
	movq	(%r14), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbp, (%r14)
	movl	$1, %eax
.LBB42_2:                               # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end42:
	.size	"String.oct()$$46", .Lfunc_end42-"String.oct()$$46"
	.cfi_endproc

	.globl	"String.chomp()$$47"
	.align	16, 0x90
	.type	"String.chomp()$$47",@function
"String.chomp()$$47":                   # @"String.chomp()$$47"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp536:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp537:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp538:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp539:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp540:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp541:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp542:
	.cfi_def_cfa_offset 128
.Ltmp543:
	.cfi_offset %rbx, -56
.Ltmp544:
	.cfi_offset %r12, -48
.Ltmp545:
	.cfi_offset %r13, -40
.Ltmp546:
	.cfi_offset %r14, -32
.Ltmp547:
	.cfi_offset %r15, -24
.Ltmp548:
	.cfi_offset %rbp, -16
	movl	%r9d, 28(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, 16(%rsp)          # 8-byte Spill
	movq	%rsi, %r12
	movq	128(%rsp), %rbp
	movq	(%r15), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	$0, 40(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.5, %edi
	callq	create_string_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movq	$0, 40(%rsp)
	movl	%r13d, %eax
	movq	%rax, 40(%rsp)
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %ebx
	movl	$19056, %esi            # imm = 0x4A70
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB43_1
# BB#3:                                 # %entry_ifend
	movq	32(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	40(%rsp), %rcx
	movq	$0, 8(%r12)
	movq	%rcx, 8(%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	28(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%ebp, %eax
	movq	%r15, %rbp
	movq	%rbx, %rdi
	je	.LBB43_5
# BB#4:                                 # %then_block7
	callq	get_try_catch_label_name
	jmp	.LBB43_1
.LBB43_5:                               # %entry_ifend8
	movq	%r12, 8(%rsp)           # 8-byte Spill
	movq	%rdi, %r12
	movq	%r14, %r15
	movl	%eax, %r13d
	movq	(%rbp), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	cmpl	$2, %ebx
	jl	.LBB43_30
# BB#6:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %eax
	movl	%eax, (%rsp)            # 4-byte Spill
	movl	$19100, %esi            # imm = 0x4A9C
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r13d, %ebx
	movq	%rbp, %r13
	movq	%r15, %rbp
	movq	8(%rsp), %rdx           # 8-byte Reload
	je	.LBB43_1
# BB#7:                                 # %entry_ifend17
	movq	32(%rsp), %rcx
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	(%rsp), %edx            # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	leaq	-1(%rdx), %r15
	movq	%r15, 8(%rcx)
	addq	$8, (%rbp)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebx, %ecx
	movq	%rbp, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB43_8
# BB#9:                                 # %entry_ifend31
	movq	%r15, (%rsp)            # 8-byte Spill
	movl	%ebx, %r15d
	movq	(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r13), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	cmpl	$13, %ebx
	sete	%al
	movq	$0, 48(%rsp)
	movzbl	%al, %eax
	movq	%rax, 48(%rsp)
	jne	.LBB43_13
# BB#10:                                # %entry_condend44
	movq	%rbp, %r14
	movl	32(%rsp), %ebp
	movl	$19148, %esi            # imm = 0x4ACC
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r15d, %ebx
	movq	8(%rsp), %rdx           # 8-byte Reload
	je	.LBB43_1
# BB#11:                                # %entry_ifend48
	movq	32(%rsp), %rcx
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r14, %rbp
	jne	.LBB43_8
# BB#12:                                # %entry_ifend62
	movl	%ebx, %r15d
	movq	(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r13), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	cmpl	$10, %ebx
	sete	%al
	movzbl	%al, %eax
	movq	%rax, 48(%rsp)
.LBB43_13:                              # %label_and_endpointzzzzzzzzzzzzzzzzzzzx
	testq	%rax, %rax
	je	.LBB43_17
# BB#14:                                # %entry_condend76
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %eax
	movl	%eax, 28(%rsp)          # 4-byte Spill
	movl	$19232, %esi            # imm = 0x4B20
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r15d, %ecx
	movq	%r12, %r14
	movq	8(%rsp), %rsi           # 8-byte Reload
	je	.LBB43_1
# BB#15:                                # %entry_ifend80
	movq	32(%rsp), %rdx
	movq	$0, (%rsi)
	movq	%rdx, (%rsi)
	movq	40(%rsp), %rdx
	movq	$0, 8(%rsi)
	movq	%rdx, 8(%rsi)
	movq	(%rbp), %rsi
	movq	$0, (%rsi)
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rsi)
	movq	(%rbp), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rsi)
	movq	(%rbp), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rsi)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	addq	$-2, %rdx
	movq	%rdx, 8(%rsi)
	addq	$8, (%rbp)
	movl	$13, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movq	%rbp, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r14, %rdi
	je	.LBB43_45
# BB#16:                                # %then_block96
	callq	get_try_catch_label_name
	jmp	.LBB43_1
.LBB43_30:                              # %label_elifzzzzzzzzzzzzzzzzzzzv1a
	movl	32(%rsp), %eax
	movl	%eax, (%rsp)            # 4-byte Spill
	movl	$19700, %esi            # imm = 0x4CF4
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r13d, %ebx
	movq	%rbp, %r13
	movq	%r12, %r14
	movq	%r15, %rbp
	movq	8(%rsp), %r15           # 8-byte Reload
	je	.LBB43_1
# BB#31:                                # %entry_ifend211
	movq	32(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	40(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	(%rsp), %edx            # 4-byte Reload
	movq	%rdx, (%rcx)
	addq	$8, (%rbp)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebx, %ecx
	movq	%rbp, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB43_33
# BB#32:                                # %then_block221
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB43_1
.LBB43_33:                              # %entry_ifend222
	movq	%r14, %r12
	movl	%ebx, %r14d
	movq	(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r13), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	testl	%ebx, %ebx
	jle	.LBB43_29
# BB#34:                                # %entry_condend236
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %eax
	movl	%eax, (%rsp)            # 4-byte Spill
	movl	$19744, %esi            # imm = 0x4D20
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r14d, %ebx
	movq	%rbp, %r14
	je	.LBB43_1
# BB#35:                                # %entry_ifend240
	movq	32(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	40(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	(%rsp), %edx            # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB43_36
.LBB43_8:                               # %then_block30
	movq	%r12, %rdi
	callq	get_try_catch_label_name
.LBB43_1:                               # %then_block
	xorl	%eax, %eax
.LBB43_2:                               # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB43_17:                              # %label_elifzzzzzzzzzzzzzzzzzzzw1a
	movl	32(%rsp), %eax
	movl	%eax, 28(%rsp)          # 4-byte Spill
	movl	$19312, %esi            # imm = 0x4B70
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r15d, %ebx
	movq	%r12, %r15
	movq	%rbp, %r14
	movq	8(%rsp), %rdx           # 8-byte Reload
	je	.LBB43_1
# BB#18:                                # %entry_ifend112
	movq	32(%rsp), %rcx
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	28(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB43_19
# BB#20:                                # %entry_ifend126
	movl	%ebx, 28(%rsp)          # 4-byte Spill
	movq	(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r13), %rax
	movq	%r13, %rbp
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	cmpl	$13, %ebx
	sete	%al
	movq	$0, 56(%rsp)
	movzbl	%al, %eax
	movq	%rax, 56(%rsp)
	je	.LBB43_24
# BB#21:                                # %entry_condnotend
	movl	32(%rsp), %r13d
	movl	$19360, %esi            # imm = 0x4BA0
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	8(%rsp), %rsi           # 8-byte Reload
	je	.LBB43_1
# BB#22:                                # %entry_ifend143
	movq	32(%rsp), %rdx
	movq	$0, (%rsi)
	movq	%rdx, (%rsi)
	movq	40(%rsp), %rdx
	movq	$0, 8(%rsi)
	movq	%rdx, 8(%rsi)
	movq	(%r14), %rsi
	movq	$0, (%rsi)
	movl	%r13d, %edx
	movq	%rdx, (%rsi)
	movq	(%r14), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rsi)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rsi)
	addq	$8, (%r14)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB43_19
# BB#23:                                # %entry_ifend157
	movq	(%rbp), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	cmpl	$10, %ebx
	sete	%al
	movzbl	%al, %eax
	movq	%rax, 56(%rsp)
.LBB43_24:                              # %label_or_endpointzzzzzzzzzzzzzzzzzzzy
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %r12d
	testq	%rax, %rax
	je	.LBB43_46
# BB#25:                                # %entry_condend172
	movl	$19444, %esi            # imm = 0x4BF4
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %rbx
	movq	8(%rsp), %rsi           # 8-byte Reload
	je	.LBB43_1
# BB#26:                                # %entry_ifend176
	movq	32(%rsp), %rdx
	movq	$0, (%rsi)
	movq	%rdx, (%rsi)
	movq	40(%rsp), %rdx
	movq	$0, 8(%rsi)
	movq	%rdx, 8(%rsi)
	movq	(%rbx), %rsi
	movq	$0, (%rsi)
	movl	%r12d, %edx
	movq	%rdx, (%rsi)
	movq	(%rbx), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rsi)
	movq	(%rbx), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rsi)
	movq	(%rsp), %rdx            # 8-byte Reload
	movq	%rdx, 8(%rsi)
	addq	$8, (%rbx)
	movl	$13, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB43_27
.LBB43_19:                              # %then_block125
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB43_1
.LBB43_36:                              # %entry_ifend254
	movq	%r12, %rbp
	movl	%ebx, %r15d
	movq	(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r13), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	cmpl	$13, %ebx
	sete	%al
	movq	$0, 64(%rsp)
	movzbl	%al, %eax
	movq	%rax, 64(%rsp)
	je	.LBB43_41
# BB#37:                                # %entry_condnotend269
	movl	32(%rsp), %eax
	movl	%eax, (%rsp)            # 4-byte Spill
	movl	$19792, %esi            # imm = 0x4D50
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r15d, %ebx
	movq	%rbp, %r15
	movq	%r14, %rbp
	movq	8(%rsp), %rdx           # 8-byte Reload
	je	.LBB43_1
# BB#38:                                # %entry_ifend273
	movq	32(%rsp), %rcx
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	40(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	(%rsp), %edx            # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebx, %ecx
	movq	%rbp, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %rdi
	movq	%rbp, %rcx
	je	.LBB43_40
# BB#39:                                # %then_block286
	callq	get_try_catch_label_name
	jmp	.LBB43_1
.LBB43_46:                              # %label_if_elifzzzzzzzzzzzzzzzzzzzw0a
	movq	$0, 40(%rsp)
	movl	%r12d, %eax
	movq	%rax, 40(%rsp)
	movq	%rbp, %r13
	jmp	.LBB43_29
.LBB43_40:                              # %entry_ifend287
	movq	%rdi, %rbp
	movl	%ebx, %r15d
	movq	(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r13), %rax
	movq	%rcx, %rbx
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r14
	cmpl	$10, %r12d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, 64(%rsp)
.LBB43_41:                              # %label_or_endpointzzzzzzzzzzzzzzzzzzzzb
	movl	$0, gSigInt(%rip)
	movl	32(%rsp), %ebx
	testq	%rax, %rax
	je	.LBB43_47
# BB#42:                                # %entry_condend303
	movl	$19872, %esi            # imm = 0x4DA0
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r15d, %ecx
	movq	%rbp, %r15
	movq	%r14, %rbp
	movq	8(%rsp), %rsi           # 8-byte Reload
	je	.LBB43_1
# BB#43:                                # %entry_ifend307
	movq	32(%rsp), %rdx
	movq	$0, (%rsi)
	movq	%rdx, (%rsi)
	movq	40(%rsp), %rdx
	movq	$0, 8(%rsi)
	movq	%rdx, 8(%rsi)
	movq	(%rbp), %rsi
	movq	$0, (%rsi)
	movl	%ebx, %edx
	movq	%rdx, (%rsi)
	movq	(%rbp), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rsi)
	movq	(%rbp), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rsi)
	movl	$4294967295, %edx       # imm = 0xFFFFFFFF
	decq	%rdx
	movq	%rdx, 8(%rsi)
	addq	$8, (%rbp)
	movl	$13, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movq	%rbp, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %rdi
	je	.LBB43_45
# BB#44:                                # %then_block323
	callq	get_try_catch_label_name
	jmp	.LBB43_1
.LBB43_45:                              # %entry_ifend97
	movq	(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r13), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
.LBB43_28:                              # %label_if_endzzzzzzzzzzzzzzzzzzzv
	movq	$0, 40(%rsp)
	movq	%rbx, 40(%rsp)
	jmp	.LBB43_29
.LBB43_47:                              # %label_elsezzzzzzzzzzzzzzzzzzzz
	movq	$0, 40(%rsp)
	movl	%ebx, %eax
	movq	%rax, 40(%rsp)
.LBB43_29:                              # %label_if_endzzzzzzzzzzzzzzzzzzzv
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB43_2
.LBB43_27:                              # %entry_ifend193
	movq	(%rbp), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	(%rbx), %rax
	movq	%rbx, %r14
	movq	%rbp, %r13
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	jmp	.LBB43_28
.Lfunc_end43:
	.size	"String.chomp()$$47", .Lfunc_end43-"String.chomp()$$47"
	.cfi_endproc

	.globl	"String.toBuffer()$$48"
	.align	16, 0x90
	.type	"String.toBuffer()$$48",@function
"String.toBuffer()$$48":                # @"String.toBuffer()$$48"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp549:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp550:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp551:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp552:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp553:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp554:
	.cfi_def_cfa_offset 56
	subq	$88, %rsp
.Ltmp555:
	.cfi_def_cfa_offset 144
.Ltmp556:
	.cfi_offset %rbx, -56
.Ltmp557:
	.cfi_offset %r12, -48
.Ltmp558:
	.cfi_offset %r13, -40
.Ltmp559:
	.cfi_offset %r14, -32
.Ltmp560:
	.cfi_offset %r15, -24
.Ltmp561:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebp
	movq	%r8, %r12
	movq	%rcx, %r15
	movq	%rdx, %rax
	movq	%rsi, %r14
	movq	(%r15), %rbx
	movq	$0, 56(%rsp)
	movq	%rbx, 56(%rsp)
	movq	$0, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rax, %rcx
	movq	%rax, %r13
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB44_1
# BB#3:                                 # %entry_ifend
	movq	144(%rsp), %rdi
	movq	(%rax), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movl	$20128, %esi            # imm = 0x4EA0
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB44_1
# BB#4:                                 # %entry_ifend3
	leaq	8(%r14), %rcx
	movq	$0, (%r14)
	movq	%rbx, (%r14)
	movq	$0, 8(%r14)
	movq	$0, 16(%r14)
	movq	$0, 24(%r14)
	movq	(%r12), %rdx
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$34, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebp, %ecx
	movq	%r12, %r8
	movq	%r13, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB44_6
# BB#5:                                 # %then_block17
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB44_1
.LBB44_6:                               # %entry_ifend18
	movq	%r14, 16(%rsp)          # 8-byte Spill
	movl	%ebp, 48(%rsp)          # 4-byte Spill
	movq	%rbx, 24(%rsp)          # 8-byte Spill
	movq	(%r15), %rbx
	movq	$0, 56(%rsp)
	movq	%rbx, 56(%rsp)
	movq	8(%r15), %r13
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movq	16(%r15), %rbp
	movq	$0, 72(%rsp)
	movq	%rbp, 72(%rsp)
	movq	24(%r15), %r14
	movq	%r15, 8(%rsp)           # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%r14, 80(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, gSigInt(%rip)
	movl	$20136, %esi            # imm = 0x4EA8
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB44_1
# BB#7:                                 # %entry_ifend30
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	%r13d, %edi
	callq	get_array_length
	movl	%eax, %eax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movl	$20144, %esi            # imm = 0x4EB0
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB44_1
# BB#8:                                 # %entry_ifend34
	movq	%rbx, %rcx
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	$0, 8(%rbx)
	movq	%r13, 8(%rbx)
	movq	$0, 16(%rbx)
	movq	%rbp, 16(%rbx)
	movq	$0, 24(%rbx)
	movq	%r14, 24(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$2, %esi
	movq	%rax, %rdi
	movq	8(%rsp), %r13           # 8-byte Reload
	movq	%r13, %rdx
	movl	48(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	24(%rsp), %r15          # 8-byte Reload
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB44_9
# BB#10:                                # %entry_ifend52
	movq	(%r13), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r13), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %rbp
	movq	%rbp, 40(%rsp)          # 8-byte Spill
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 72(%rsp)
	movq	%rbp, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 80(%rsp)
	xorl	%r14d, %r14d
	movq	%r13, %rbp
	movq	(%rsp), %r13            # 8-byte Reload
	jmp	.LBB44_11
	.align	16, 0x90
.LBB44_15:                              # %entry_ifend95
                                        #   in Loop: Header=BB44_11 Depth=1
	movq	(%rbp), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%rbp), %r13
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movq	16(%rbp), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%rbp), %r14
	movq	$0, 80(%rsp)
	movq	%r14, 80(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	incl	%r14d
	movq	$0, 80(%rsp)
	movq	%r14, 80(%rsp)
.LBB44_11:                              # %for_start_pointzzzzzzzzzzzzzzzzzzzzc
                                        # =>This Inner Loop Header: Depth=1
	movl	%r13d, %edi
	callq	get_array_length
	decl	%eax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %r14d
	jge	.LBB44_16
# BB#12:                                # %entry_condend
                                        #   in Loop: Header=BB44_11 Depth=1
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movl	48(%rsp), %edx          # 4-byte Reload
	movq	%r15, %rcx
	movl	%r13d, %r8d
	movl	%r14d, %r9d
	callq	load_element
	cmpl	$0, 8(%rax)
	je	.LBB44_1
# BB#13:                                # %entry_ifend74
                                        #   in Loop: Header=BB44_11 Depth=1
	movq	(%rax), %r15
	movl	$20228, %esi            # imm = 0x4F04
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB44_1
# BB#14:                                # %entry_ifend77
                                        #   in Loop: Header=BB44_11 Depth=1
	movq	$0, (%rbx)
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%rbx)
	movq	$0, 8(%rbx)
	movq	%r13, 8(%rbx)
	movq	$0, 16(%rbx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 16(%rbx)
	movq	$0, 24(%rbx)
	movq	%r14, 24(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movzbl	%r15b, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	48(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	24(%rsp), %r15          # 8-byte Reload
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB44_15
.LBB44_9:                               # %then_block51
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB44_1:                               # %then_block
	xorl	%eax, %eax
.LBB44_2:                               # %then_block
	addq	$88, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB44_16:                              # %label_for_endzzzzzzzzzzzzzzzzzzzzc
	movq	40(%rsp), %rax          # 8-byte Reload
	movl	%eax, %eax
	movq	%rax, (%rbp)
	movl	$1, %eax
	jmp	.LBB44_2
.Lfunc_end44:
	.size	"String.toBuffer()$$48", .Lfunc_end44-"String.toBuffer()$$48"
	.cfi_endproc

	.globl	"String.toPath()$$49"
	.align	16, 0x90
	.type	"String.toPath()$$49",@function
"String.toPath()$$49":                  # @"String.toPath()$$49"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp562:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp563:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp564:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp565:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp566:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp567:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp568:
	.cfi_def_cfa_offset 80
.Ltmp569:
	.cfi_offset %rbx, -56
.Ltmp570:
	.cfi_offset %r12, -48
.Ltmp571:
	.cfi_offset %r13, -40
.Ltmp572:
	.cfi_offset %r14, -32
.Ltmp573:
	.cfi_offset %r15, -24
.Ltmp574:
	.cfi_offset %rbp, -16
	movl	%r9d, 4(%rsp)           # 4-byte Spill
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, 8(%rsp)           # 8-byte Spill
	movq	%rsi, %rbp
	movq	80(%rsp), %r13
	movq	(%r14), %r15
	movq	$0, 16(%rsp)
	movq	%r15, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$20312, %esi            # imm = 0x4F58
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB45_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$20320, %esi            # imm = 0x4F60
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB45_1
# BB#4:                                 # %entry_ifend3
	movq	$0, (%rbp)
	movq	%r15, (%rbp)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%rbx, %r8
	movq	8(%rsp), %rbp           # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB45_6
# BB#5:                                 # %then_block11
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB45_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB45_2
.LBB45_6:                               # %entry_ifend12
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
.LBB45_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end45:
	.size	"String.toPath()$$49", .Lfunc_end45-"String.toPath()$$49"
	.cfi_endproc

	.globl	"String.toCommand()$$50"
	.align	16, 0x90
	.type	"String.toCommand()$$50",@function
"String.toCommand()$$50":               # @"String.toCommand()$$50"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp575:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp576:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp577:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp578:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp579:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp580:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp581:
	.cfi_def_cfa_offset 80
.Ltmp582:
	.cfi_offset %rbx, -56
.Ltmp583:
	.cfi_offset %r12, -48
.Ltmp584:
	.cfi_offset %r13, -40
.Ltmp585:
	.cfi_offset %r14, -32
.Ltmp586:
	.cfi_offset %r15, -24
.Ltmp587:
	.cfi_offset %rbp, -16
	movl	%r9d, 4(%rsp)           # 4-byte Spill
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, 8(%rsp)           # 8-byte Spill
	movq	%rsi, %rbp
	movq	80(%rsp), %r13
	movq	(%r14), %r15
	movq	$0, 16(%rsp)
	movq	%r15, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$20328, %esi            # imm = 0x4F68
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB46_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$20336, %esi            # imm = 0x4F70
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB46_1
# BB#4:                                 # %entry_ifend3
	movq	$0, (%rbp)
	movq	%r15, (%rbp)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
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
	addq	$8, (%rbx)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%rbx, %r8
	movq	8(%rsp), %rbp           # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB46_6
# BB#5:                                 # %then_block14
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB46_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB46_2
.LBB46_6:                               # %entry_ifend15
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
.LBB46_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end46:
	.size	"String.toCommand()$$50", .Lfunc_end46-"String.toCommand()$$50"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.zero	1
	.size	.Lglobal_string, 1

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.zero	1
	.size	.Lglobal_string.2, 1

	.type	.Lglobal_string.3,@object # @global_string.3
.Lglobal_string.3:
	.zero	1
	.size	.Lglobal_string.3, 1

	.type	.Lglobal_string.4,@object # @global_string.4
.Lglobal_string.4:
	.asciz	"unexpected error at String.indexOf"
	.size	.Lglobal_string.4, 35

	.type	.Lglobal_string.5,@object # @global_string.5
.Lglobal_string.5:
	.zero	1
	.size	.Lglobal_string.5, 1


	.section	".note.GNU-stack","",@progbits
