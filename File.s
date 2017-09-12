	.text
	.file	"File.bc"
	.globl	"File.close()$$4"
	.align	16, 0x90
	.type	"File.close()$$4",@function
"File.close()$$4":                      # @"File.close()$$4"
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
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	cmpl	$-1, %eax
	je	.LBB0_10
# BB#4:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#5:                                 # %entry_ifend4
	movq	80(%rsp), %rdi
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$1188, %esi             # imm = 0x4A4
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#6:                                 # %entry_ifend7
	movq	$0, (%r12)
	movq	%rbp, (%r12)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$40, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r14d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB0_8
# BB#7:                                 # %then_block12
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB0_1
.LBB0_8:                                # %entry_ifend13
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movl	$0, (%rsp)
	movl	$4294967295, %r9d       # imm = 0xFFFFFFFF
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB0_1
# BB#9:                                 # %entry_ifend21
	movl	$0, gSigInt(%rip)
	movl	$1, (%rsp)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB0_1
.LBB0_10:                               # %label_if_endzzzzzzzzzzzzzzzzzzzzzb
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
	.size	"File.close()$$4", .Lfunc_end0-"File.close()$$4"
	.cfi_endproc

	.globl	"File.read(ulong)$$5"
	.align	16, 0x90
	.type	"File.read(ulong)$$5",@function
"File.read(ulong)$$5":                  # @"File.read(ulong)$$5"
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
	movl	%r9d, %ebp
	movl	%ebp, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	(%rbx), %r13
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 40(%rsp)
	movq	%r12, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%rax, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	112(%rsp), %rbp
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	$-1, %eax
	je	.LBB1_4
# BB#9:                                 # %label_if_endzzzzzzzzzzzzzzzzzzzzzc
	movl	$1420, %esi             # imm = 0x58C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#10:                                # %entry_ifend32
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$1428, %esi             # imm = 0x594
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#11:                                # %entry_ifend36
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	incq	%r12
	movq	$0, 16(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	addq	$8, (%r14)
	movl	$2, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	20(%rsp), %r15d         # 4-byte Reload
	movl	%r15d, %ecx
	movq	%r14, %r8
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_13
# BB#12:                                # %then_block51
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_4:                                # %entry_condend
	movl	$1304, %esi             # imm = 0x518
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#5:                                 # %entry_ifend4
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, (%rsp)            # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$1336, %esi             # imm = 0x538
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#6:                                 # %entry_ifend7
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	(%rsp), %edx            # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	24(%rsp), %r15          # 8-byte Reload
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_8
# BB#7:                                 # %then_block19
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_13:                               # %entry_ifend52
	movq	(%rbx), %r13
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	movl	%r15d, %ebp
	movq	8(%rbx), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 48(%rsp)
	movq	%r15, 48(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	112(%rsp), %rdi
	je	.LBB1_1
# BB#14:                                # %entry_ifend68
	movq	(%rax), %r12
	movl	$1436, %esi             # imm = 0x59C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#15:                                # %entry_ifend73
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	(%rsp), %rsi            # 8-byte Reload
	movq	%rsi, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r15, 16(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
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
	movq	%rsi, 8(%rcx)
	addq	$8, (%r14)
	movl	$41, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	24(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_17
# BB#16:                                # %then_block91
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_8:                                # %entry_ifend20
	movq	(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%rbx)
	movl	%ebp, %edi
	movq	%r15, %rsi
	callq	entry_exception_object
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
.LBB1_17:                               # %entry_ifend92
	movq	(%rbx), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%rbx), %rbp
	movq	$0, 48(%rsp)
	movq	%rbp, 48(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB1_2
.Lfunc_end1:
	.size	"File.read(ulong)$$5", .Lfunc_end1-"File.read(ulong)$$5"
	.cfi_endproc

	.globl	"File.to_stat()$$6"
	.align	16, 0x90
	.type	"File.to_stat()$$6",@function
"File.to_stat()$$6":                    # @"File.to_stat()$$6"
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
	movl	%r9d, %r13d
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %r15
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %rdi
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	testl	%eax, %eax
	je	.LBB2_4
# BB#9:                                 # %label_if_endzzzzzzzzzzzzzzzzzzzzzd
	movl	$1596, %esi             # imm = 0x63C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#10:                                # %entry_ifend23
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#11:                                # %entry_ifend27
	movq	(%rax), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movl	$1604, %esi             # imm = 0x644
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#12:                                # %entry_ifend30
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
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
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_7
# BB#13:                                # %entry_ifend42
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
	jmp	.LBB2_2
.LBB2_4:                                # %entry_condend
	movl	$1480, %esi             # imm = 0x5C8
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#5:                                 # %entry_ifend3
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, (%rsp)            # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$1512, %esi             # imm = 0x5E8
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#6:                                 # %entry_ifend6
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	(%rsp), %edx            # 4-byte Reload
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
	movq	%rbx, %rdx
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_8
.LBB2_7:                                # %then_block14
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB2_1
.LBB2_8:                                # %entry_ifend15
	movq	(%rbx), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%rbx)
	movl	%ebp, %edi
	movq	%r15, %rsi
	callq	entry_exception_object
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
	.size	"File.to_stat()$$6", .Lfunc_end2-"File.to_stat()$$6"
	.cfi_endproc

	.globl	"File.to_lstat()$$7"
	.align	16, 0x90
	.type	"File.to_lstat()$$7",@function
"File.to_lstat()$$7":                   # @"File.to_lstat()$$7"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp39:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp40:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp41:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp42:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp43:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp44:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp45:
	.cfi_def_cfa_offset 80
.Ltmp46:
	.cfi_offset %rbx, -56
.Ltmp47:
	.cfi_offset %r12, -48
.Ltmp48:
	.cfi_offset %r13, -40
.Ltmp49:
	.cfi_offset %r14, -32
.Ltmp50:
	.cfi_offset %r15, -24
.Ltmp51:
	.cfi_offset %rbp, -16
	movl	%r9d, %r13d
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %r15
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %rdi
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	testl	%eax, %eax
	je	.LBB3_4
# BB#9:                                 # %label_if_endzzzzzzzzzzzzzzzzzzzzze
	movl	$1764, %esi             # imm = 0x6E4
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#10:                                # %entry_ifend23
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#11:                                # %entry_ifend27
	movq	(%rax), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movl	$1772, %esi             # imm = 0x6EC
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#12:                                # %entry_ifend30
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	$1, 8(%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_7
# BB#13:                                # %entry_ifend45
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
	jmp	.LBB3_2
.LBB3_4:                                # %entry_condend
	movl	$1648, %esi             # imm = 0x670
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#5:                                 # %entry_ifend3
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, (%rsp)            # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.3, %edi
	callq	create_string_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$1680, %esi             # imm = 0x690
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#6:                                 # %entry_ifend6
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	(%rsp), %edx            # 4-byte Reload
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
	movq	%rbx, %rdx
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB3_8
.LBB3_7:                                # %then_block14
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_8:                                # %entry_ifend15
	movq	(%rbx), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%rbx)
	movl	%ebp, %edi
	movq	%r15, %rsi
	callq	entry_exception_object
.LBB3_1:                                # %then_block
	xorl	%eax, %eax
.LBB3_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end3:
	.size	"File.to_lstat()$$7", .Lfunc_end3-"File.to_lstat()$$7"
	.cfi_endproc

	.globl	"File.read(String)$$8"
	.align	16, 0x90
	.type	"File.read(String)$$8",@function
"File.read(String)$$8":                 # @"File.read(String)$$8"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp52:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp53:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp54:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp55:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp56:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp57:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp58:
	.cfi_def_cfa_offset 96
.Ltmp59:
	.cfi_offset %rbx, -56
.Ltmp60:
	.cfi_offset %r12, -48
.Ltmp61:
	.cfi_offset %r13, -40
.Ltmp62:
	.cfi_offset %r14, -32
.Ltmp63:
	.cfi_offset %r15, -24
.Ltmp64:
	.cfi_offset %rbp, -16
	movl	%r9d, 4(%rsp)           # 4-byte Spill
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, 8(%rsp)           # 8-byte Spill
	movq	%rsi, %r15
	movq	96(%rsp), %r12
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1780, %esi             # imm = 0x6F4
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$1788, %esi             # imm = 0x6FC
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#4:                                 # %entry_ifend3
	movq	$0, (%r15)
	movq	%rbp, (%r15)
	movq	$0, 8(%r15)
	movq	$0, 16(%r15)
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
	movl	$2, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%r13, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_5
# BB#6:                                 # %entry_ifend16
	movq	(%r14), %rbx
	movq	$0, 16(%rsp)
	movq	%rbx, 16(%rsp)
	movq	8(%r14), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r14), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 24(%rsp)
	movq	%r12, 24(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1796, %esi             # imm = 0x704
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#7:                                 # %entry_ifend27
	movq	$0, (%r15)
	movq	%rbx, (%r15)
	movq	$0, 8(%r15)
	movq	%r12, 8(%r15)
	movq	$0, 16(%r15)
	movq	%rbp, 16(%r15)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$9, %esi
	movq	%rax, %rdi
	movq	%r14, %rbp
	movq	%rbp, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%r13, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_5
# BB#8:                                 # %entry_ifend40
	movq	(%rbp), %r14
	movq	$0, 16(%rsp)
	movq	%r14, 16(%rsp)
	movq	8(%rbp), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 32(%rsp)
	movq	%r12, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1804, %esi             # imm = 0x70C
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#9:                                 # %entry_ifend56
	movq	$0, (%r15)
	movq	%r14, (%r15)
	movq	$0, 8(%r15)
	movq	%rbx, 8(%r15)
	movq	$0, 16(%r15)
	movq	%r12, 16(%r15)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$4, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%r13, %r8
	movq	8(%rsp), %rbx           # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB4_10
.LBB4_5:                                # %then_block15
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB4_1:                                # %then_block
	xorl	%eax, %eax
.LBB4_2:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB4_10:                               # %entry_ifend69
	movq	(%rbp), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%rbp), %rbx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movl	%ebx, %eax
	movq	%rax, (%rbp)
	movl	$1, %eax
	jmp	.LBB4_2
.Lfunc_end4:
	.size	"File.read(String)$$8", .Lfunc_end4-"File.read(String)$$8"
	.cfi_endproc

	.globl	"File.read()$$9"
	.align	16, 0x90
	.type	"File.read()$$9",@function
"File.read()$$9":                       # @"File.read()$$9"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp65:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp66:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp67:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp68:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp69:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp70:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp71:
	.cfi_def_cfa_offset 128
.Ltmp72:
	.cfi_offset %rbx, -56
.Ltmp73:
	.cfi_offset %r12, -48
.Ltmp74:
	.cfi_offset %r13, -40
.Ltmp75:
	.cfi_offset %r14, -32
.Ltmp76:
	.cfi_offset %r15, -24
.Ltmp77:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebp
	movl	%ebp, 36(%rsp)          # 4-byte Spill
	movq	%rcx, %r12
	movq	%rdx, %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	%rsi, %r14
	movq	(%r12), %r13
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r8, %rdi
	movq	%r8, %rbx
	movq	%r12, %rsi
	movl	%ebp, %edx
	movq	%rax, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#3:                                 # %entry_ifend
	movq	128(%rsp), %rdi
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	$-1, %eax
	je	.LBB5_4
# BB#9:                                 # %label_if_endzzzzzzzzzzzzzzzzzzzzzf
	movl	$1964, %esi             # imm = 0x7AC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#10:                                # %entry_ifend31
	movq	$0, (%r14)
	movq	%r13, (%r14)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r14)
	movq	%rcx, 8(%r14)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r14)
	movq	%rcx, 16(%r14)
	movq	%rbx, %r15
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$6, %esi
	movq	%rax, %rdi
	movq	%r12, %rbx
	movq	%rbx, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	40(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB5_11
# BB#12:                                # %entry_ifend44
	movq	(%rbx), %r12
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$1972, %esi             # imm = 0x7B4
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#13:                                # %entry_ifend59
	movq	$0, (%r14)
	movq	%r12, (%r14)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r14)
	movq	%rcx, 8(%r14)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r14)
	movq	%rcx, 16(%r14)
	movq	%r15, %r12
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%r12)
	movl	$14, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	40(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB5_14
.LBB5_11:                               # %then_block43
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_4:                                # %entry_condend
	movl	$1848, %esi             # imm = 0x738
	movq	%rdi, %r15
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#5:                                 # %entry_ifend3
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.4, %edi
	callq	create_string_object
	movl	%eax, 24(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$1880, %esi             # imm = 0x758
	movq	%r15, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#6:                                 # %entry_ifend6
	movq	$0, (%r14)
	movq	%r13, (%r14)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r14)
	movq	%rcx, 8(%r14)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r14)
	movq	%rcx, 16(%r14)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	24(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	40(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB5_8
# BB#7:                                 # %then_block18
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_8:                                # %entry_ifend19
	movq	(%r12), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r12), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r12), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%r15, (%r12)
	movl	%r15d, %edi
	movq	%r14, %rsi
	callq	entry_exception_object
	jmp	.LBB5_1
.LBB5_14:                               # %entry_ifend72
	movq	(%rbx), %r15
	movq	$0, 48(%rsp)
	movq	%r15, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	%rbx, 16(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 56(%rsp)
	movq	%rbp, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1980, %esi             # imm = 0x7BC
	movq	128(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#15:                                # %entry_ifend87
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movq	56(%rsp), %r13
	movl	$1988, %esi             # imm = 0x7C4
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#16:                                # %entry_ifend91
	incq	%r13
	movq	$0, (%r14)
	movq	%r15, (%r14)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r14)
	movq	%rcx, 8(%r14)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r14)
	movq	%rcx, 16(%r14)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r12)
	movl	$2, %esi
	movq	%rax, %rdi
	movq	16(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %rdx
	movl	36(%rsp), %r15d         # 4-byte Reload
	movl	%r15d, %ecx
	movq	%r12, %r8
	movq	40(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB5_18
# BB#17:                                # %then_block106
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_18:                               # %entry_ifend107
	movq	(%rbp), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbp), %rax
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
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbp, %rsi
	movq	24(%rsp), %rbp          # 8-byte Reload
	movl	%r15d, %edx
	movq	%r13, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	128(%rsp), %rdi
	je	.LBB5_1
# BB#19:                                # %entry_ifend123
	movq	(%rax), %rbx
	movl	64(%rsp), %r13d
	movq	56(%rsp), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$1996, %esi             # imm = 0x7CC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#20:                                # %entry_ifend128
	movq	$0, (%r14)
	movq	%rbp, (%r14)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r14)
	movq	%rcx, 8(%r14)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r14)
	movq	%rcx, 16(%r14)
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
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$41, %esi
	movq	%rax, %rdi
	movq	16(%rsp), %r14          # 8-byte Reload
	movq	%r14, %rdx
	movl	%r15d, %ecx
	movq	%r12, %r8
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB5_22
# BB#21:                                # %then_block146
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB5_1:                                # %then_block
	xorl	%eax, %eax
.LBB5_2:                                # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB5_22:                               # %entry_ifend147
	movq	(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB5_2
.Lfunc_end5:
	.size	"File.read()$$9", .Lfunc_end5-"File.read()$$9"
	.cfi_endproc

	.globl	"File.write(Buffer,ulong)$$10"
	.align	16, 0x90
	.type	"File.write(Buffer,ulong)$$10",@function
"File.write(Buffer,ulong)$$10":         # @"File.write(Buffer,ulong)$$10"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp78:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp79:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp80:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp81:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp82:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp83:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp84:
	.cfi_def_cfa_offset 128
.Ltmp85:
	.cfi_offset %rbx, -56
.Ltmp86:
	.cfi_offset %r12, -48
.Ltmp87:
	.cfi_offset %r13, -40
.Ltmp88:
	.cfi_offset %r14, -32
.Ltmp89:
	.cfi_offset %r15, -24
.Ltmp90:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebx
	movl	%ebx, 36(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	%rsi, %r13
	movq	(%r15), %rbp
	movq	$0, 48(%rsp)
	movq	%rbp, 48(%rsp)
	movq	8(%r15), %r12
	movq	$0, 56(%rsp)
	movq	%r12, 56(%rsp)
	movq	16(%r15), %rcx
	movq	%rcx, 24(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rcx, 64(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebx, %edx
	movq	%rax, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#3:                                 # %entry_ifend
	movq	128(%rsp), %rbx
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	$-1, %eax
	je	.LBB6_4
# BB#9:                                 # %label_if_endzzzzzzzzzzzzzzzzzzzzzg
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	40(%rsp), %rcx          # 8-byte Reload
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#10:                                # %entry_ifend35
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movl	$2156, %esi             # imm = 0x86C
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#11:                                # %entry_ifend40
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	$0, 8(%r13)
	movq	%r12, 8(%r13)
	movq	$0, 16(%r13)
	movq	24(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 16(%r13)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, (%rcx)
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
	movq	%rsi, 8(%rcx)
	addq	$8, (%r14)
	movl	$42, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	40(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB6_13
# BB#12:                                # %then_block58
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB6_1
.LBB6_4:                                # %entry_condend
	movl	$2040, %esi             # imm = 0x7F8
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#5:                                 # %entry_ifend6
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 16(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.5, %edi
	callq	create_string_object
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$2072, %esi             # imm = 0x818
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#6:                                 # %entry_ifend9
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	$0, 8(%r13)
	movq	%r12, 8(%r13)
	movq	$0, 16(%r13)
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 16(%r13)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	16(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB6_8
# BB#7:                                 # %then_block21
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB6_1
.LBB6_13:                               # %entry_ifend59
	movq	(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%r15)
	movl	$1, %eax
	jmp	.LBB6_2
.LBB6_8:                                # %entry_ifend22
	movq	(%r15), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r15), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%r15)
	movl	%ebp, %edi
	movq	%rbx, %rsi
	callq	entry_exception_object
.LBB6_1:                                # %then_block
	xorl	%eax, %eax
.LBB6_2:                                # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end6:
	.size	"File.write(Buffer,ulong)$$10", .Lfunc_end6-"File.write(Buffer,ulong)$$10"
	.cfi_endproc

	.globl	"File.write(Buffer)$$11"
	.align	16, 0x90
	.type	"File.write(Buffer)$$11",@function
"File.write(Buffer)$$11":               # @"File.write(Buffer)$$11"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp91:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp92:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp93:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp94:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp95:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp96:
	.cfi_def_cfa_offset 56
	subq	$40, %rsp
.Ltmp97:
	.cfi_def_cfa_offset 96
.Ltmp98:
	.cfi_offset %rbx, -56
.Ltmp99:
	.cfi_offset %r12, -48
.Ltmp100:
	.cfi_offset %r13, -40
.Ltmp101:
	.cfi_offset %r14, -32
.Ltmp102:
	.cfi_offset %r15, -24
.Ltmp103:
	.cfi_offset %rbp, -16
	movl	%r9d, %r12d
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	%rsi, %r13
	movq	(%r14), %r15
	movq	$0, 24(%rsp)
	movq	%r15, 24(%rsp)
	movq	8(%r14), %rbp
	movq	$0, 32(%rsp)
	movq	%rbp, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	movq	%rax, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#3:                                 # %entry_ifend
	movq	96(%rsp), %rdi
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$2164, %esi             # imm = 0x874
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_1
# BB#4:                                 # %entry_ifend6
	movq	$0, (%r13)
	movq	%r15, (%r13)
	movq	$0, 8(%r13)
	movq	%rbp, 8(%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	16(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB7_6
# BB#5:                                 # %then_block19
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB7_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB7_2
.LBB7_6:                                # %entry_ifend20
	movq	(%r14), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	8(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbp, (%r14)
	movl	$1, %eax
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
	.size	"File.write(Buffer)$$11", .Lfunc_end7-"File.write(Buffer)$$11"
	.cfi_endproc

	.globl	"File.write(String,Buffer,int)$$12"
	.align	16, 0x90
	.type	"File.write(String,Buffer,int)$$12",@function
"File.write(String,Buffer,int)$$12":    # @"File.write(String,Buffer,int)$$12"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp104:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp105:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp106:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp107:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp108:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp109:
	.cfi_def_cfa_offset 56
	subq	$104, %rsp
.Ltmp110:
	.cfi_def_cfa_offset 160
.Ltmp111:
	.cfi_offset %rbx, -56
.Ltmp112:
	.cfi_offset %r12, -48
.Ltmp113:
	.cfi_offset %r13, -40
.Ltmp114:
	.cfi_offset %r14, -32
.Ltmp115:
	.cfi_offset %r15, -24
.Ltmp116:
	.cfi_offset %rbp, -16
	movl	%r9d, 60(%rsp)          # 4-byte Spill
	movq	%r8, %r13
	movq	%rcx, %rbx
	movq	%rdx, 48(%rsp)          # 8-byte Spill
	movq	%rsi, 40(%rsp)          # 8-byte Spill
	movq	160(%rsp), %r14
	movq	(%rbx), %r15
	movq	$0, 64(%rsp)
	movq	%r15, 64(%rsp)
	movq	8(%rbx), %rbp
	movq	$0, 72(%rsp)
	movq	%rbp, 72(%rsp)
	movq	16(%rbx), %r12
	movq	$0, 80(%rsp)
	movq	%r12, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2172, %esi             # imm = 0x87C
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB8_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 32(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movq	%r14, (%rsp)
	movl	$33, %r8d
	movl	$2180, %r9d             # imm = 0x884
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	48(%rsp), %rcx          # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#4:                                 # %entry_ifend6
	movq	(%rax), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	%r14, (%rsp)
	movl	$39, %r8d
	movl	$2188, %r9d             # imm = 0x88C
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	48(%rsp), %rcx          # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#5:                                 # %entry_ifend9
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	%r14, (%rsp)
	movl	$31, %r8d
	movl	$2196, %r9d             # imm = 0x894
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	48(%rsp), %rcx          # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#6:                                 # %entry_ifend12
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$2204, %esi             # imm = 0x89C
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB8_1
# BB#7:                                 # %entry_ifend17
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	16(%rsp), %rdx          # 8-byte Reload
	orl	%ecx, %edx
	movq	8(%rsp), %rsi           # 8-byte Reload
	orl	%edx, %esi
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r12, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	$0, 32(%rcx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	32(%rsp), %edx          # 4-byte Reload
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
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	60(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	48(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbp, %rdi
	je	.LBB8_9
# BB#8:                                 # %then_block39
	callq	get_try_catch_label_name
	jmp	.LBB8_1
.LBB8_9:                                # %entry_ifend40
	movq	(%rbx), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 72(%rsp)
	movq	%r12, 72(%rsp)
	movq	%r13, %r14
	movq	16(%rbx), %rbp
	movq	$0, 80(%rsp)
	movq	%rbp, 80(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%rbx), %r15
	movq	$0, 96(%rsp)
	movq	%r15, 96(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 88(%rsp)
	movq	%r13, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2212, %esi             # imm = 0x8A4
	movq	160(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB8_1
# BB#10:                                # %entry_ifend57
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%rbp, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	%r13, 24(%rcx)
	movq	$0, 32(%rcx)
	movq	%r15, 32(%rcx)
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
	movl	$11, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	60(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	48(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbp, %rdi
	je	.LBB8_12
# BB#11:                                # %then_block76
	callq	get_try_catch_label_name
	jmp	.LBB8_1
.LBB8_12:                               # %entry_ifend77
	movq	(%rbx), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 72(%rsp)
	movq	%r12, 72(%rsp)
	movq	16(%rbx), %r15
	movq	$0, 80(%rsp)
	movq	%r15, 80(%rsp)
	movq	24(%rbx), %rbp
	movq	$0, 88(%rsp)
	movq	%rbp, 88(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 96(%rsp)
	movq	%r13, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2220, %esi             # imm = 0x8AC
	movq	160(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB8_1
# BB#13:                                # %entry_ifend97
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r15, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	%rbp, 24(%rcx)
	movq	$0, 32(%rcx)
	movq	%r13, 32(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$4, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	60(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	48(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbp, %rdi
	je	.LBB8_15
# BB#14:                                # %then_block113
	callq	get_try_catch_label_name
.LBB8_1:                                # %then_block
	xorl	%eax, %eax
.LBB8_2:                                # %then_block
	addq	$104, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB8_15:                               # %entry_ifend114
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
	movq	32(%rbx), %rbp
	movq	$0, 96(%rsp)
	movq	%rbp, 96(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB8_2
.Lfunc_end8:
	.size	"File.write(String,Buffer,int)$$12", .Lfunc_end8-"File.write(String,Buffer,int)$$12"
	.cfi_endproc

	.globl	"File.write(String,Buffer)$$13"
	.align	16, 0x90
	.type	"File.write(String,Buffer)$$13",@function
"File.write(String,Buffer)$$13":        # @"File.write(String,Buffer)$$13"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp117:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp118:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp119:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp120:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp121:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp122:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp123:
	.cfi_def_cfa_offset 80
.Ltmp124:
	.cfi_offset %rbx, -56
.Ltmp125:
	.cfi_offset %r12, -48
.Ltmp126:
	.cfi_offset %r13, -40
.Ltmp127:
	.cfi_offset %r14, -32
.Ltmp128:
	.cfi_offset %r15, -24
.Ltmp129:
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
	movl	$2228, %esi             # imm = 0x8B4
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_1
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
	movq	$420, 8(%rcx)           # imm = 0x1A4
	addq	$8, (%rbx)
	movl	$12, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB9_5
# BB#4:                                 # %then_block15
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB9_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB9_2
.LBB9_5:                                # %entry_ifend16
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
.LBB9_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end9:
	.size	"File.write(String,Buffer)$$13", .Lfunc_end9-"File.write(String,Buffer)$$13"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"File is not opened"
	.size	.Lglobal_string, 19

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.asciz	"File is not opened"
	.size	.Lglobal_string.2, 19

	.type	.Lglobal_string.3,@object # @global_string.3
.Lglobal_string.3:
	.asciz	"File is not opened"
	.size	.Lglobal_string.3, 19

	.type	.Lglobal_string.4,@object # @global_string.4
.Lglobal_string.4:
	.asciz	"File is not opened"
	.size	.Lglobal_string.4, 19

	.type	.Lglobal_string.5,@object # @global_string.5
.Lglobal_string.5:
	.asciz	"File is not opened"
	.size	.Lglobal_string.5, 19


	.section	".note.GNU-stack","",@progbits
