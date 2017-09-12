	.text
	.file	"Job.bc"
	.globl	"Job.toString()$$1"
	.align	16, 0x90
	.type	"Job.toString()$$1",@function
"Job.toString()$$1":                    # @"Job.toString()$$1"
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
	movq	(%rax), %rax
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
	.size	"Job.toString()$$1", .Lfunc_end0-"Job.toString()$$1"
	.cfi_endproc

	.globl	"Job.equals(Self)$$2"
	.align	16, 0x90
	.type	"Job.equals(Self)$$2",@function
"Job.equals(Self)$$2":                  # @"Job.equals(Self)$$2"
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
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %r12
	movq	(%rbx), %r8
	movq	$0, 8(%rsp)
	movq	%r8, 8(%rsp)
	movq	8(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %r13
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#4:                                 # %entry_ifend5
	movq	(%rax), %rax
	cmpl	%eax, %r13d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, (%rbx)
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
	.size	"Job.equals(Self)$$2", .Lfunc_end1-"Job.equals(Self)$$2"
	.cfi_endproc

	.globl	"Job.forground()$$3"
	.align	16, 0x90
	.type	"Job.forground()$$3",@function
"Job.forground()$$3":                   # @"Job.forground()$$3"
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
	subq	$88, %rsp
.Ltmp22:
	.cfi_def_cfa_offset 144
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
	movl	%r9d, 36(%rsp)          # 4-byte Spill
	movq	%r8, %r12
	movq	%rcx, %r15
	movq	%rdx, %r13
	movq	%rsi, %rbp
	movq	144(%rsp), %r14
	movq	(%r15), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	$0, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$340, %esi              # imm = 0x154
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$348, %esi              # imm = 0x15C
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#4:                                 # %entry_ifend2
	movq	40(%rsp), %rcx
	movq	%rbp, 24(%rsp)          # 8-byte Spill
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	48(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	56(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	64(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	72(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	36(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r12, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_5
# BB#6:                                 # %entry_ifend18
	movq	%r13, %rbp
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
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$356, %esi              # imm = 0x164
	movq	%r14, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#7:                                 # %entry_ifend35
	movq	40(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$97, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r12, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_8
# BB#9:                                 # %entry_ifend57
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
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, gSigInt(%rip)
	movq	%r15, %rsi
	movq	%r14, %r15
	movq	%r15, (%rsp)
	movl	$203, %r8d
	movl	$364, %r9d              # imm = 0x16C
	movq	%r12, %rdi
	movq	%r12, %r14
	movq	%rsi, %r12
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movq	%rbp, %r13
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#10:                                # %entry_ifend78
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movl	40(%rsp), %r8d
	movl	$2, %r9d
	movq	%r14, %rdi
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#11:                                # %entry_ifend82
	movq	(%rax), %rbp
	movl	$372, %esi              # imm = 0x174
	movq	%r15, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#12:                                # %entry_ifend85
	movq	40(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$98, %esi
	movq	%rax, %rdi
	movq	%r12, %rbp
	movq	%rbp, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_13
.LBB2_5:                                # %then_block17
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB2_1
.LBB2_13:                               # %entry_ifend110
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
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r8d
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%r14, %r12
	movq	%rbp, %rsi
	movl	%ebx, %edx
	movl	%ebx, %r14d
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	144(%rsp), %rdi
	je	.LBB2_1
# BB#14:                                # %entry_ifend132
	movq	(%rax), %rbx
	movl	$380, %esi              # imm = 0x17C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#15:                                # %entry_ifend135
	movq	40(%rsp), %rcx
	movq	24(%rsp), %r15          # 8-byte Reload
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
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%r12, %rbx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$96, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	%r14d, %ecx
	movq	%rbx, %r8
	movq	%r13, %r12
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_17
# BB#16:                                # %then_block156
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB2_1
.LBB2_17:                               # %entry_ifend157
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
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%rbx, %r13
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movq	%rcx, 8(%rsp)           # 8-byte Spill
	movl	%r14d, %r12d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	144(%rsp), %rbx
	je	.LBB2_1
# BB#18:                                # %entry_ifend179
	movq	(%rax), %r14
	movq	%rbx, (%rsp)
	movl	$80, %r8d
	movl	$388, %r9d              # imm = 0x184
	movq	%r13, %rdi
	movq	%rbp, %rsi
	movl	%r12d, %edx
	movq	8(%rsp), %rcx           # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#19:                                # %entry_ifend182
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movl	$396, %esi              # imm = 0x18C
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#20:                                # %entry_ifend185
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
	movq	%r14, %rdx
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$95, %esi
	movq	%rax, %rdi
	movq	%rbp, %rbx
	movq	%rbx, %rdx
	movl	%r12d, %r15d
	movl	%r15d, %ecx
	movq	%r13, %r8
	movq	8(%rsp), %rbp           # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_21
.LBB2_8:                                # %then_block56
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB2_1:                                # %then_block
	xorl	%eax, %eax
.LBB2_2:                                # %then_block
	addq	$88, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB2_21:                               # %entry_ifend207
	movq	(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movq	$0, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r8d
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%r13, %r14
	movq	%rbx, %rsi
	movq	%rbx, %r12
	movl	%r15d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	144(%rsp), %rbp
	je	.LBB2_1
# BB#22:                                # %entry_ifend229
	movq	(%rax), %rbx
	movq	%rbp, (%rsp)
	movl	$64, %r8d
	movl	$404, %r9d              # imm = 0x194
	movq	%r14, %rdi
	movq	%r12, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	8(%rsp), %rcx           # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#23:                                # %entry_ifend232
	movq	(%rax), %r13
	movl	$412, %esi              # imm = 0x19C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#24:                                # %entry_ifend235
	movq	24(%rsp), %r15          # 8-byte Reload
	leaq	16(%r15), %rcx
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
	movq	(%r14), %rdx
	movq	$0, (%rdx)
	movl	%ebx, %esi
	movq	%rsi, (%rdx)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$84, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#26:                                # %entry_ifend260
	movq	%r12, %r13
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
	movq	32(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 64(%rsp)
	movq	%r12, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %ebx
	movl	$420, %esi              # imm = 0x1A4
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#27:                                # %entry_ifend282
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
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$90, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#28:                                # %entry_ifend301
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
	movq	32(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	testb	$1, %r12b
	je	.LBB2_45
# BB#29:                                # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %ebx
	movl	$464, %esi              # imm = 0x1D0
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#30:                                # %entry_ifend323
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
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$91, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#31:                                # %entry_ifend342
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
	movq	32(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	subl	$-128, %ebx
	movq	$0, 72(%rsp)
	movq	%rbx, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$472, %esi              # imm = 0x1D8
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#32:                                # %entry_ifend363
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$480, %esi              # imm = 0x1E0
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#33:                                # %entry_ifend366
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
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#34:                                # %entry_ifend385
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
	movq	32(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r13), %rax
	movq	%r13, %r12
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 80(%rsp)
	movq	%r13, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$488, %esi              # imm = 0x1E8
	movq	%rbp, %rbx
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#35:                                # %entry_ifend407
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
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$97, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#36:                                # %entry_ifend429
	movq	%r12, %rbp
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
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %r8d
	movl	80(%rsp), %r9d
	movl	$2, (%rsp)
	movq	%r14, %rdi
	movq	%r14, %r15
	movq	%rbp, %rsi
	movq	%rbp, %r12
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	8(%rsp), %rcx           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB2_1
# BB#37:                                # %entry_ifend452
	movl	$0, gSigInt(%rip)
	movq	%rbx, (%rsp)
	movl	$203, %r8d
	movl	$496, %r9d              # imm = 0x1F0
	movq	%r15, %rdi
	movq	%r12, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	8(%rsp), %rcx           # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#38:                                # %entry_ifend455
	movq	(%rax), %r14
	movl	48(%rsp), %r13d
	movl	$504, %esi              # imm = 0x1F8
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#39:                                # %entry_ifend459
	movq	40(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	%r15, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$98, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r8, %rbp
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#40:                                # %entry_ifend484
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
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	movl	$512, %esi              # imm = 0x200
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#41:                                # %entry_ifend505
	movq	%rbx, %r14
	movq	40(%rsp), %rcx
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	48(%rsp), %rcx
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	56(%rsp), %rcx
	movq	$0, 16(%rdx)
	movq	%rcx, 16(%rdx)
	movq	64(%rsp), %rcx
	movq	$0, 24(%rdx)
	movq	%rcx, 24(%rdx)
	movq	72(%rsp), %rcx
	movq	$0, 32(%rdx)
	movq	%rcx, 32(%rdx)
	movq	80(%rsp), %rcx
	movq	$0, 40(%rdx)
	movq	%rcx, 40(%rdx)
	movq	%rdx, %rbx
	movl	$93, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#42:                                # %entry_ifend521
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
	movq	%r12, %r15
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$520, %esi              # imm = 0x208
	movq	%r14, %rdi
	jmp	.LBB2_62
.LBB2_45:                               # %label_elifzzzzzzzzzzzzzzzzzzzzzz1a
	movl	56(%rsp), %ebx
	movl	$600, %esi              # imm = 0x258
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#46:                                # %entry_ifend587
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
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$87, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#47:                                # %entry_ifend606
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
	movq	32(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	testb	$1, %r12b
	je	.LBB2_63
# BB#48:                                # %entry_condend627
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	40(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r13, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	8(%rsp), %rcx           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%rbp, %rbx
	je	.LBB2_1
# BB#49:                                # %entry_ifend631
	movq	(%rax), %rax
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%eax, %eax
	movq	%rax, (%rcx)
	addq	$8, (%r14)
	movq	%rbx, (%rsp)
	movl	$1, %r8d
	movl	$668, %r9d              # imm = 0x29C
	movq	%r14, %rdi
	movq	%r13, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	8(%rsp), %rcx           # 8-byte Reload
	callq	run_create_carray
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#50:                                # %entry_ifend637
	movq	(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$676, %esi              # imm = 0x2A4
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#51:                                # %entry_ifend640
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
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	addq	$8, (%r14)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r14, %rbp
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#52:                                # %entry_ifend662
	movq	%r13, %r14
	movq	(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r14), %rax
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
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	movq	%rbx, (%rsp)
	xorl	%r8d, %r8d
	movl	$684, %r9d              # imm = 0x2AC
	movq	%rbp, %rdi
	movq	%r14, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	8(%rsp), %rcx           # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#53:                                # %entry_ifend683
	movq	(%rax), %r12
	movl	40(%rsp), %r13d
	movl	$692, %esi              # imm = 0x2B4
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#54:                                # %entry_ifend687
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
	movq	%rbp, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$29, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r8, %rbx
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#55:                                # %entry_ifend709
	movq	(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r14), %rax
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
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movq	144(%rsp), %r13
	movq	%r13, (%rsp)
	movl	$203, %r8d
	movl	$708, %r9d              # imm = 0x2C4
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movq	%r14, %r12
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	8(%rsp), %rcx           # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#56:                                # %entry_ifend730
	movq	(%rax), %r14
	movl	48(%rsp), %ebp
	movl	$716, %esi              # imm = 0x2CC
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#57:                                # %entry_ifend734
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
	movq	%rbx, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$98, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#58:                                # %entry_ifend759
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
	movq	%r12, %r13
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r14
	movl	$0, gSigInt(%rip)
	movl	$724, %esi              # imm = 0x2D4
	movq	144(%rsp), %rbx
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#59:                                # %entry_ifend780
	movq	%rbx, %r12
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
	movq	%r15, %rbx
	movl	$93, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#60:                                # %entry_ifend796
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
	movq	32(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r13), %rax
	movq	%r13, %r15
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%r14, %rbp
	movl	$732, %esi              # imm = 0x2DC
	jmp	.LBB2_61
.LBB2_63:                               # %label_if_elifzzzzzzzzzzzzzzzzzzzzzz0a
	movq	%rbp, (%rsp)
	xorl	%r8d, %r8d
	movl	$852, %r9d              # imm = 0x354
	movq	%r14, %rdi
	movq	%r13, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	8(%rsp), %rcx           # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#64:                                # %entry_ifend861
	movq	(%rax), %rbx
	movl	40(%rsp), %r12d
	movl	$860, %esi              # imm = 0x35C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#65:                                # %entry_ifend865
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
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$29, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%r14, %rbx
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#66:                                # %entry_ifend887
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
	movq	32(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r13), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movq	%rbp, (%rsp)
	movl	$203, %r8d
	movl	$876, %r9d              # imm = 0x36C
	movq	%rbx, %rdi
	movq	%r13, %rsi
	movq	%r13, %r12
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	8(%rsp), %rcx           # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#67:                                # %entry_ifend908
	movq	(%rax), %r14
	movl	48(%rsp), %r13d
	movl	$884, %esi              # imm = 0x374
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#68:                                # %entry_ifend912
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
	movq	%rbx, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$98, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#69:                                # %entry_ifend937
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
	movq	%r12, %r13
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r14
	movl	$0, gSigInt(%rip)
	movl	$892, %esi              # imm = 0x37C
	movq	%rbp, %rbx
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#70:                                # %entry_ifend958
	movq	%rbx, %r12
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
	movq	%r15, %rbx
	movl	$93, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_25
# BB#71:                                # %entry_ifend974
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
	movq	32(%r13), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%r13), %rax
	movq	%r13, %r15
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%r14, %rbp
	movl	$900, %esi              # imm = 0x384
.LBB2_61:                               # %entry_ifend796
	movq	%r12, %rdi
.LBB2_62:                               # %entry_ifend796
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#43:                                # %entry_ifend542
	movq	40(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	48(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	56(%rsp), %rcx
	movq	$0, 16(%rbx)
	movq	%rcx, 16(%rbx)
	movq	64(%rsp), %rcx
	movq	$0, 24(%rbx)
	movq	%rcx, 24(%rbx)
	movq	72(%rsp), %rcx
	movq	$0, 32(%rbx)
	movq	%rcx, 32(%rbx)
	movq	80(%rsp), %rcx
	movq	$0, 40(%rbx)
	movq	%rcx, 40(%rbx)
	movq	%rbp, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r8)
	movl	$96, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	8(%rsp), %r9            # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_44
.LBB2_25:                               # %then_block259
	movq	8(%rsp), %rdi           # 8-byte Reload
	callq	get_try_catch_label_name
	jmp	.LBB2_1
.LBB2_44:                               # %entry_ifend564
	movq	%r15, %rbx
	movq	(%rbx), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	40(%rbx), %rax
	movq	%rbx, %r14
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	%rbp, %rbx
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, (%r14)
	movl	$1, %eax
	jmp	.LBB2_2
.Lfunc_end2:
	.size	"Job.forground()$$3", .Lfunc_end2-"Job.forground()$$3"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"Job<%s> is done.\n"
	.size	.Lglobal_string, 18


	.section	".note.GNU-stack","",@progbits
