	.text
	.file	"Clover.bc"
	.globl	"Clover.test(String,bool)$$1"
	.align	16, 0x90
	.type	"Clover.test(String,bool)$$1",@function
"Clover.test(String,bool)$$1":          # @"Clover.test(String,bool)$$1"
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
	movl	%r9d, 52(%rsp)          # 4-byte Spill
	movq	%r8, 32(%rsp)           # 8-byte Spill
	movq	%rcx, 40(%rsp)          # 8-byte Spill
	movq	%rdx, %r14
	movq	%rsi, %rbx
	movq	128(%rsp), %rbp
	movq	(%rcx), %r12
	movq	$0, 56(%rsp)
	movq	%r12, 56(%rsp)
	movq	8(%rcx), %r15
	movq	$0, 64(%rsp)
	movq	%r15, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$432, %esi              # imm = 0x1B0
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbx)
	movq	%r12, (%rbx)
	movq	$0, 8(%rbx)
	movq	%r15, 8(%rbx)
	movq	%rbx, 24(%rsp)          # 8-byte Spill
	movq	32(%rsp), %rbx          # 8-byte Reload
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
	movq	40(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB0_5
# BB#4:                                 # %then_block11
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB0_1
.LBB0_5:                                # %entry_ifend12
	movq	%r14, 16(%rsp)          # 8-byte Spill
	movq	(%rbp), %r15
	movq	$0, 56(%rsp)
	movq	%r15, 56(%rsp)
	movq	8(%rbp), %r12
	movq	$0, 64(%rsp)
	movq	%r12, 64(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$440, %esi              # imm = 0x1B8
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	24(%rsp), %r14          # 8-byte Reload
	je	.LBB0_1
# BB#6:                                 # %entry_ifend21
	movq	$0, (%r14)
	movq	%r15, (%r14)
	movq	$0, 8(%r14)
	movq	%r12, 8(%r14)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	addq	$8, (%rbx)
	movl	$22, %esi
	movq	%rax, %rdi
	movq	%rbp, %r12
	movq	%r12, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	%rbx, %r13
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB0_8
# BB#7:                                 # %then_block31
	callq	get_try_catch_label_name
	jmp	.LBB0_1
.LBB0_8:                                # %entry_ifend32
	movq	(%r12), %rbp
	movq	$0, 56(%rsp)
	movq	%rbp, 56(%rsp)
	movq	8(%r12), %r15
	movq	$0, 64(%rsp)
	movq	%r15, 64(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movl	$448, %esi              # imm = 0x1C0
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#9:                                 # %entry_ifend46
	movq	$0, (%r14)
	movq	%rbp, (%r14)
	movq	$0, 8(%r14)
	movq	%r15, 8(%r14)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r12, %r15
	movq	%r15, %rdx
	movl	52(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r13, %r8
	movq	16(%rsp), %r12          # 8-byte Reload
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB0_10
# BB#11:                                # %entry_ifend57
	movq	(%r15), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r15), %r15
	movq	$0, 64(%rsp)
	movq	%r15, 64(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%r13, %rbx
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$460, %esi              # imm = 0x1CC
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebp, %ecx
	je	.LBB0_1
# BB#12:                                # %entry_ifend70
	movq	$0, (%r14)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movq	%rdx, (%r14)
	movq	$0, 8(%r14)
	movq	%r15, 8(%r14)
	movq	%rbx, %r8
	movq	(%r8), %rsi
	movq	$0, (%rsi)
	movl	%r13d, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%r8)
	movl	$23, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %rdx
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB0_13
.LBB0_10:                               # %then_block56
	movq	%r12, %rdi
	callq	get_try_catch_label_name
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
.LBB0_13:                               # %entry_ifend81
	movq	(%rbp), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, (%rbp)
	movl	$1, %eax
	jmp	.LBB0_2
.Lfunc_end0:
	.size	"Clover.test(String,bool)$$1", .Lfunc_end0-"Clover.test(String,bool)$$1"
	.cfi_endproc

	.globl	"Clover.time(lambda)$$2"
	.align	16, 0x90
	.type	"Clover.time(lambda)$$2",@function
"Clover.time(lambda)$$2":               # @"Clover.time(lambda)$$2"
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
	movq	%r8, %r14
	movq	%rcx, %r13
	movq	%rdx, %r12
	movq	%rsi, %r15
	movq	112(%rsp), %rdi
	movq	(%r13), %rbx
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$468, %esi              # imm = 0x1D4
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r15)
	movq	%rbx, (%r15)
	movq	$0, 8(%r15)
	movq	$0, 16(%r15)
	movl	$43, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r12, %rdi
	je	.LBB1_5
# BB#4:                                 # %then_block7
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_5:                                # %entry_ifend8
	movq	%rdi, 24(%rsp)          # 8-byte Spill
	movq	(%r13), %rbx
	movq	%rbx, 16(%rsp)          # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rbx, 32(%rsp)
	movq	8(%r13), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r13), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 40(%rsp)
	movq	%r12, 40(%rsp)
	movl	$0, gSigInt(%rip)
	movq	(%r14), %rax
	movq	$0, (%rax)
	movl	%ebx, %ecx
	movl	%ebp, %ebx
	movq	24(%rsp), %rbp          # 8-byte Reload
	movq	%rcx, (%rax)
	addq	$8, (%r14)
	xorl	%edi, %edi
	movq	%r13, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	movq	%rbp, %r8
	callq	invoke_block_in_jit
	testl	%eax, %eax
	je	.LBB1_1
# BB#6:                                 # %entry_ifend20
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	$476, %esi              # imm = 0x1DC
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#7:                                 # %entry_ifend28
	movq	$0, (%r15)
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r15)
	movq	$0, 8(%r15)
	movq	%r12, 8(%r15)
	movq	$0, 16(%r15)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, 16(%r15)
	movl	$43, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbp, %rdi
	je	.LBB1_9
# BB#8:                                 # %then_block37
	callq	get_try_catch_label_name
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
.LBB1_9:                                # %entry_ifend38
	movq	(%r13), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r13), %rbx
	movq	$0, 40(%rsp)
	movq	%rbx, 40(%rsp)
	movq	16(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 48(%rsp)
	movq	%rbp, 48(%rsp)
	movl	$0, gSigInt(%rip)
	subq	%rbx, %rbp
	movq	%rbp, (%r13)
	movl	$1, %eax
	jmp	.LBB1_2
.Lfunc_end1:
	.size	"Clover.time(lambda)$$2", .Lfunc_end1-"Clover.time(lambda)$$2"
	.cfi_endproc

	.globl	"Clover.realtime(lambda)$$3"
	.align	16, 0x90
	.type	"Clover.realtime(lambda)$$3",@function
"Clover.realtime(lambda)$$3":           # @"Clover.realtime(lambda)$$3"
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
	subq	$72, %rsp
.Ltmp32:
	.cfi_def_cfa_offset 128
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
	movl	%r9d, 36(%rsp)          # 4-byte Spill
	movq	%r8, %r12
	movq	%rcx, %r14
	movq	%rdx, 40(%rsp)          # 8-byte Spill
	movq	%rsi, %r15
	movq	128(%rsp), %rbp
	movq	(%r14), %rbx
	movq	$0, 48(%rsp)
	movq	%rbx, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$484, %esi              # imm = 0x1E4
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$496, %esi              # imm = 0x1F0
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#4:                                 # %entry_ifend2
	movq	%r15, 24(%rsp)          # 8-byte Spill
	movq	$0, (%r15)
	movq	%rbx, (%r15)
	movq	56(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	64(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	%r12, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbp)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	36(%rsp), %ebx          # 4-byte Reload
	movq	%rbp, %r13
	movl	%ebx, %ecx
	movq	%r13, %r8
	movq	40(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_5
# BB#6:                                 # %entry_ifend12
	movl	%ebx, %r15d
	movq	(%r14), %r12
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movq	8(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 56(%rsp)
	movq	%rbx, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movq	128(%rsp), %rbx
	movq	%rbx, (%rsp)
	movl	$57, %r8d
	movl	$508, %r9d              # imm = 0x1FC
	movq	%r13, %rdi
	movq	%r14, %rsi
	movq	%r14, 16(%rsp)          # 8-byte Spill
	movl	%r15d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#7:                                 # %entry_ifend22
	movq	(%rax), %r14
	movl	56(%rsp), %ebp
	movl	$516, %esi              # imm = 0x204
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#8:                                 # %entry_ifend26
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%r12, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$75, %esi
	movq	%rax, %rdi
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	36(%rsp), %r14d         # 4-byte Reload
	movl	%r14d, %ecx
	movq	%r13, %r8
	movq	40(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_5
# BB#9:                                 # %entry_ifend42
	movq	(%rbx), %r12
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movq	(%r13), %rax
	movq	$0, (%rax)
	movl	%r12d, %ecx
	movq	%rcx, (%rax)
	addq	$8, (%r13)
	xorl	%edi, %edi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movl	%r14d, %ebx
	movq	%r13, %rcx
	movq	%rbp, %r8
	callq	invoke_block_in_jit
	testl	%eax, %eax
	movq	128(%rsp), %rbp
	je	.LBB2_1
# BB#10:                                # %entry_ifend61
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%r13, %r15
	movl	$0, gSigInt(%rip)
	movl	$524, %esi              # imm = 0x20C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#11:                                # %entry_ifend69
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$536, %esi              # imm = 0x218
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#12:                                # %entry_ifend72
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%r12, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	%r15, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbp)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	16(%rsp), %r14          # 8-byte Reload
	movq	%r14, %rdx
	movl	%ebx, %r15d
	movl	%r15d, %ecx
	movq	%rbp, %r8
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_14
# BB#13:                                # %then_block84
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB2_1
.LBB2_14:                               # %entry_ifend85
	movq	%rbx, %r12
	movq	%r14, %rbx
	movq	(%rbx), %r13
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 64(%rsp)
	movq	%r14, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movq	128(%rsp), %r14
	movq	%r14, (%rsp)
	movl	$57, %r8d
	movl	$548, %r9d              # imm = 0x224
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r12, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#15:                                # %entry_ifend100
	movq	(%rax), %rbx
	movl	64(%rsp), %eax
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	$556, %esi              # imm = 0x22C
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#16:                                # %entry_ifend104
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%r13, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$75, %esi
	movq	%rax, %rdi
	movq	16(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	%r15d, %ecx
	movq	%rbp, %r8
	movq	%r12, %r14
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_18
# BB#17:                                # %then_block119
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB2_1
.LBB2_18:                               # %entry_ifend120
	movq	%r14, %r12
	movq	(%rbx), %r14
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %r13d
	movl	56(%rsp), %eax
	movl	%eax, 12(%rsp)          # 4-byte Spill
	movl	$564, %esi              # imm = 0x234
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#19:                                # %entry_ifend137
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%r14, (%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	12(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r15d, %ecx
	movq	%rbp, %r14
	movq	%r14, %r8
	movq	%r12, %rbp
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_20
.LBB2_5:                                # %then_block11
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB2_1:                                # %then_block
	xorl	%eax, %eax
.LBB2_2:                                # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB2_20:                               # %entry_ifend153
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%rbx)
	movl	$1, %eax
	jmp	.LBB2_2
.Lfunc_end2:
	.size	"Clover.realtime(lambda)$$3", .Lfunc_end2-"Clover.realtime(lambda)$$3"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"..."
	.size	.Lglobal_string, 4

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.asciz	"OK"
	.size	.Lglobal_string.2, 3


	.section	".note.GNU-stack","",@progbits
