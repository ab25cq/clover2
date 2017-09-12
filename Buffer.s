	.text
	.file	"Buffer.bc"
	.globl	"Buffer.append(Self)$$4"
	.align	16, 0x90
	.type	"Buffer.append(Self)$$4",@function
"Buffer.append(Self)$$4":               # @"Buffer.append(Self)$$4"
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
	movl	%r9d, %r14d
	movq	%r8, %rbp
	movq	%rcx, %rbx
	movq	%rdx, %r13
	movq	%rsi, 40(%rsp)          # 8-byte Spill
	movq	(%rbx), %r12
	movq	$0, 56(%rsp)
	movq	%r12, 56(%rsp)
	movq	8(%rbx), %r8
	movq	%r8, 48(%rsp)           # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%r8, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#4:                                 # %entry_ifend5
	movq	(%rax), %r15
	movl	$2, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#5:                                 # %entry_ifend10
	addq	32(%rsp), %r15          # 8-byte Folded Reload
	cmpq	(%rax), %r15
	jb	.LBB0_6
# BB#15:                                # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rbp, %r15
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %ebp
	movl	%ebp, %edx
	movq	%r13, %r14
	movq	%r14, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#16:                                # %entry_ifend14
	movq	(%rax), %rax
	addq	32(%rsp), %rax          # 8-byte Folded Reload
	leaq	2(%rax,%rax), %r13
	movq	$0, 80(%rsp)
	movq	%r13, 80(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r14, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#17:                                # %entry_ifend22
	movq	(%rax), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movl	$944, %esi              # imm = 0x3B0
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#18:                                # %entry_ifend26
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r12, (%rcx)
	movq	$0, 8(%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	%r13, 24(%rcx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r15)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r15, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%ebp, %r13d
	movq	%r15, %rbp
	jne	.LBB0_19
# BB#20:                                # %entry_ifend41
	movq	(%rbx), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%rbx), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%rbx), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%rbx), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, (%rsp)
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r14, %rcx
	movl	%r12d, %r8d
	movq	%r15, %r9
	callq	store_field
	testl	%eax, %eax
	movl	%r13d, %r15d
	movq	%rbp, %r13
	movq	16(%rsp), %rbp          # 8-byte Reload
	je	.LBB0_1
# BB#21:                                # %entry_ifend54
	movl	$0, gSigInt(%rip)
	movl	$2, (%rsp)
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	jne	.LBB0_7
	jmp	.LBB0_1
.LBB0_6:
	xorl	%eax, %eax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movl	%r14d, %r15d
	movq	%r13, %r14
	movq	%rbp, %r13
	movq	%r12, %rbp
.LBB0_7:                                # %label_if_endzzzzzzzzzzzzzzzzzzzzd
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#8:                                 # %entry_ifend64
	movq	(%rax), %r12
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#9:                                 # %entry_ifend68
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movq	48(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#10:                                # %entry_ifend73
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$1024, %esi             # imm = 0x400
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#11:                                # %entry_ifend77
	addq	16(%rsp), %r12          # 8-byte Folded Reload
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	$0, 8(%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	32(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 24(%rcx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movq	%r12, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	%rsi, 8(%rcx)
	addq	$8, (%r13)
	movl	$12, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r15d, %ecx
	movq	%r13, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%r15d, %r12d
	movq	%r13, %rbp
	je	.LBB0_12
.LBB0_19:                               # %then_block40
	movq	%r14, %rdi
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
.LBB0_12:                               # %entry_ifend98
	movq	(%rbx), %r13
	movq	$0, 56(%rsp)
	movq	%r13, 56(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%rbx), %r15
	movq	$0, 72(%rsp)
	movq	%r15, 72(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movl	%r12d, %edx
	movq	%r14, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%rbp, %rdi
	je	.LBB0_1
# BB#13:                                # %entry_ifend117
	addq	(%rax), %r15
	movl	$1, (%rsp)
	movq	%rbx, %rsi
	movl	%r12d, %edx
	movq	%r14, %rcx
	movl	%r13d, %r8d
	movq	%r15, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB0_1
# BB#14:                                # %entry_ifend122
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB0_2
.Lfunc_end0:
	.size	"Buffer.append(Self)$$4", .Lfunc_end0-"Buffer.append(Self)$$4"
	.cfi_endproc

	.globl	"Buffer.append(byte)$$5"
	.align	16, 0x90
	.type	"Buffer.append(byte)$$5",@function
"Buffer.append(byte)$$5":               # @"Buffer.append(byte)$$5"
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
	subq	$88, %rsp
.Ltmp19:
	.cfi_def_cfa_offset 144
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
	movl	%r9d, %r15d
	movq	%r8, %r13
	movq	%rcx, %rbx
	movq	%rdx, %r14
	movq	%rsi, 40(%rsp)          # 8-byte Spill
	movq	(%rbx), %rbp
	movq	$0, 56(%rsp)
	movq	%rbp, 56(%rsp)
	movq	8(%rbx), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 72(%rsp)
	movq	$1, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %r12
	movl	$2, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#4:                                 # %entry_ifend6
	incq	%r12
	cmpq	(%rax), %r12
	jb	.LBB1_5
# BB#11:                                # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#12:                                # %entry_ifend10
	movq	(%rax), %rax
	leaq	4(%rax,%rax), %r12
	movq	$0, 80(%rsp)
	movq	%r12, 80(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#13:                                # %entry_ifend18
	movq	144(%rsp), %rdi
	movq	(%rax), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movl	$1068, %esi             # imm = 0x42C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#14:                                # %entry_ifend22
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	$0, 8(%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	$1, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	%r12, 24(%rcx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	addq	$8, (%r13)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r15d, %ecx
	movq	%r13, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_16
# BB#15:                                # %then_block36
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_5:
	xorl	%eax, %eax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movl	$1, %eax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	%rbp, %r12
.LBB1_6:                                # %label_if_endzzzzzzzzzzzzzzzzzzzze
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#7:                                 # %entry_ifend60
	movq	(%rax), %rbp
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#8:                                 # %entry_ifend64
	movq	(%rax), %rax
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	%r12, (%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	24(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 16(%rcx)
	movq	32(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 24(%rcx)
	movb	%dl, (%rbp,%rax)
	movq	(%rbx), %r12
	movq	$0, 56(%rsp)
	movq	%r12, 56(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%rbx), %rbp
	movq	$0, 72(%rsp)
	movq	%rbp, 72(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#9:                                 # %entry_ifend86
	addq	(%rax), %rbp
	movl	$1, (%rsp)
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%r12d, %r8d
	movq	%rbp, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB1_1
# BB#10:                                # %entry_ifend91
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB1_2
.LBB1_16:                               # %entry_ifend37
	movq	(%rbx), %r12
	movq	$0, 56(%rsp)
	movq	%r12, 56(%rsp)
	movq	8(%rbx), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%rbx), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%rbx), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 16(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, (%rsp)
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	movq	16(%rsp), %r9           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	je	.LBB1_1
# BB#17:                                # %entry_ifend50
	movl	$0, gSigInt(%rip)
	movl	$2, (%rsp)
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movl	%r12d, %r8d
	movq	32(%rsp), %r9           # 8-byte Reload
	callq	store_field
	testl	%eax, %eax
	jne	.LBB1_6
.LBB1_1:                                # %then_block
	xorl	%eax, %eax
.LBB1_2:                                # %then_block
	addq	$88, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end1:
	.size	"Buffer.append(byte)$$5", .Lfunc_end1-"Buffer.append(byte)$$5"
	.cfi_endproc

	.globl	"Buffer.chars(int)$$6"
	.align	16, 0x90
	.type	"Buffer.chars(int)$$6",@function
"Buffer.chars(int)$$6":                 # @"Buffer.chars(int)$$6"
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
	subq	$40, %rsp
.Ltmp32:
	.cfi_def_cfa_offset 96
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
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %r14
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 24(%rsp)
	movq	%r12, 24(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%r12d, %r12d
	jns	.LBB2_5
# BB#1:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_2
# BB#4:                                 # %entry_ifend
	movq	(%rax), %rax
	addl	%eax, %r12d
	movq	$0, 24(%rsp)
	movq	%r12, 24(%rsp)
.LBB2_5:                                # %label_if_endzzzzzzzzzzzzzzzzzzzzf
	movl	$0, gSigInt(%rip)
	testl	%r12d, %r12d
	setns	%al
	movq	$0, 32(%rsp)
	movzbl	%al, %eax
	movq	%rax, 32(%rsp)
	js	.LBB2_8
# BB#6:                                 # %entry_condend8
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_2
# BB#7:                                 # %entry_ifend13
	movq	(%rax), %rax
	cmpl	%eax, %r12d
	setl	%al
	movzbl	%al, %eax
	movq	%rax, 32(%rsp)
.LBB2_8:                                # %label_and_endpointzzzzzzzzzzzzzzzzzzzzh
	movl	$0, gSigInt(%rip)
	testq	%rax, %rax
	je	.LBB2_11
# BB#9:                                 # %entry_condend18
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_2
# BB#10:                                # %entry_ifend22
	movq	(%rax), %rax
	movl	%r12d, %ecx
	movq	8(%rsp), %rdx           # 8-byte Reload
	movq	%rbp, (%rdx)
	movq	%r12, 8(%rdx)
	movzbl	(%rax,%rcx), %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB2_3
.LBB2_11:                               # %label_elsezzzzzzzzzzzzzzzzzzzzg
	movq	96(%rsp), %rdi
	movl	$1436, %esi             # imm = 0x59C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_2
# BB#12:                                # %entry_ifend32
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 4(%rsp)           # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, (%rsp)            # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$1480, %esi             # imm = 0x5C8
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_2
# BB#13:                                # %entry_ifend35
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	4(%rsp), %edx           # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	(%rsp), %edx            # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r13d, %ecx
	movq	%r15, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_15
# BB#14:                                # %then_block46
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB2_2
.LBB2_15:                               # %entry_ifend47
	movq	(%rbx), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbp, (%rbx)
	movl	%ebp, %edi
	movq	%r14, %rsi
	callq	entry_exception_object
.LBB2_2:                                # %then_block
	xorl	%eax, %eax
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
	.size	"Buffer.chars(int)$$6", .Lfunc_end2-"Buffer.chars(int)$$6"
	.cfi_endproc

	.globl	"Buffer.chars(ulong)$$7"
	.align	16, 0x90
	.type	"Buffer.chars(ulong)$$7",@function
"Buffer.chars(ulong)$$7":               # @"Buffer.chars(ulong)$$7"
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
	subq	$40, %rsp
.Ltmp45:
	.cfi_def_cfa_offset 96
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
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %r14
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 24(%rsp)
	movq	%r12, 24(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 32(%rsp)
	movq	$1, 32(%rsp)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	cmpq	%rax, %r12
	sbbq	%rcx, %rcx
	andl	$1, %ecx
	cmpq	%rax, %r12
	movq	%rcx, 32(%rsp)
	movl	$0, gSigInt(%rip)
	jae	.LBB3_6
# BB#4:                                 # %entry_condend6
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r14, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#5:                                 # %entry_ifend10
	movq	(%rax), %rax
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rbp, (%rcx)
	movq	%r12, 8(%rcx)
	movzbl	(%rax,%r12), %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB3_2
.LBB3_6:                                # %label_elsezzzzzzzzzzzzzzzzzzzzi
	movq	96(%rsp), %rdi
	movl	$1744, %esi             # imm = 0x6D0
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#7:                                 # %entry_ifend18
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 4(%rsp)           # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%eax, (%rsp)            # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$1788, %esi             # imm = 0x6FC
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#8:                                 # %entry_ifend21
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	4(%rsp), %edx           # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	(%rsp), %edx            # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r13d, %ecx
	movq	%r15, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB3_10
# BB#9:                                 # %then_block32
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_10:                               # %entry_ifend33
	movq	(%rbx), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbp, (%rbx)
	movl	%ebp, %edi
	movq	%r14, %rsi
	callq	entry_exception_object
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
.Lfunc_end3:
	.size	"Buffer.chars(ulong)$$7", .Lfunc_end3-"Buffer.chars(ulong)$$7"
	.cfi_endproc

	.globl	"Buffer.equals(Self)$$8"
	.align	16, 0x90
	.type	"Buffer.equals(Self)$$8",@function
"Buffer.equals(Self)$$8":               # @"Buffer.equals(Self)$$8"
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
	subq	$56, %rsp
.Ltmp58:
	.cfi_def_cfa_offset 112
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
	movl	%r9d, %ebp
	movl	%ebp, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r12
	movq	%rcx, %r15
	movq	%rdx, %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	(%r15), %r13
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	movq	8(%r15), %rcx
	movq	$0, 40(%rsp)
	movq	%rcx, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	%ebp, %edx
	movq	%rcx, %rbp
	movq	%rax, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rbx
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#4:                                 # %entry_ifend5
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpq	%rax, %rbx
	je	.LBB4_7
# BB#5:                                 # %entry_condend
	movq	$0, (%r15)
	movl	$1, %eax
	jmp	.LBB4_2
.LBB4_7:                                # %label_if_endzzzzzzzzzzzzzzzzzzzzk
	movq	$0, 48(%rsp)
	xorl	%r14d, %r14d
	jmp	.LBB4_8
	.align	16, 0x90
.LBB4_17:                               # %label_if_endzzzzzzzzzzzzzzzzzzzzm
                                        #   in Loop: Header=BB4_8 Depth=1
	incq	%r14
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movq	%rbx, %r15
.LBB4_8:                                # %for_start_pointzzzzzzzzzzzzzzzzzzzzl
                                        # =>This Inner Loop Header: Depth=1
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r15, %rsi
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#9:                                 # %entry_ifend11
                                        #   in Loop: Header=BB4_8 Depth=1
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpq	%rax, %r14
	jae	.LBB4_18
# BB#10:                                # %entry_condend14
                                        #   in Loop: Header=BB4_8 Depth=1
	movl	$2056, %esi             # imm = 0x808
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#11:                                # %entry_ifend19
                                        #   in Loop: Header=BB4_8 Depth=1
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r14, 16(%rcx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	%r14, 8(%rcx)
	addq	$8, (%r12)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_12
# BB#13:                                # %entry_ifend32
                                        #   in Loop: Header=BB4_8 Depth=1
	movq	(%r15), %r14
	movq	$0, 32(%rsp)
	movq	%r14, 32(%rsp)
	movq	8(%r15), %rbp
	movq	$0, 40(%rsp)
	movq	%rbp, 40(%rsp)
	movq	16(%r15), %r13
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$2064, %esi             # imm = 0x810
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#14:                                # %entry_ifend45
                                        #   in Loop: Header=BB4_8 Depth=1
	movq	%rbx, (%rsp)            # 8-byte Spill
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r14, (%rcx)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r13, 16(%rcx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
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
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	24(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_12
# BB#15:                                # %entry_ifend61
                                        #   in Loop: Header=BB4_8 Depth=1
	movq	(%r15), %r13
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	movq	8(%r15), %rbp
	movq	$0, 40(%rsp)
	movq	%rbp, 40(%rsp)
	movq	16(%r15), %r14
	movq	%r15, %rbx
	movq	$0, 48(%rsp)
	movq	%r14, 48(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	(%rsp), %rax            # 8-byte Reload
	movzbl	%al, %eax
	movzbl	%r15b, %ecx
	cmpl	%ecx, %eax
	je	.LBB4_17
# BB#16:                                # %entry_condend77
	movl	$0, gSigInt(%rip)
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB4_2
.LBB4_12:                               # %then_block31
	movq	24(%rsp), %rdi          # 8-byte Reload
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
.LBB4_18:                               # %label_for_endzzzzzzzzzzzzzzzzzzzzl
	movq	$1, (%r15)
	movl	$1, %eax
	jmp	.LBB4_2
.Lfunc_end4:
	.size	"Buffer.equals(Self)$$8", .Lfunc_end4-"Buffer.equals(Self)$$8"
	.cfi_endproc

	.globl	"Buffer.clone()$$9"
	.align	16, 0x90
	.type	"Buffer.clone()$$9",@function
"Buffer.clone()$$9":                    # @"Buffer.clone()$$9"
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
	movl	%r9d, 52(%rsp)          # 4-byte Spill
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r12
	movq	%rsi, %rbp
	movq	128(%rsp), %rdi
	movq	(%r14), %r13
	movq	$0, 56(%rsp)
	movq	%r13, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2256, %esi             # imm = 0x8D0
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$2, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%r12, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movl	$2264, %esi             # imm = 0x8D8
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#5:                                 # %entry_ifend6
	movq	%rbp, 32(%rsp)          # 8-byte Spill
	movq	$0, (%rbp)
	movq	%r13, (%rbp)
	movq	$0, 8(%rbp)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$2, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	52(%rsp), %r13d         # 4-byte Reload
	movl	%r13d, %ecx
	movq	%rbx, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r12, %r15
	movl	%r13d, %r12d
	je	.LBB5_7
# BB#6:                                 # %then_block16
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_7:                                # %entry_ifend17
	movq	(%r14), %rbp
	movq	$0, 56(%rsp)
	movq	%rbp, 56(%rsp)
	movq	8(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r15, %rcx
	movq	%rbx, %r15
	je	.LBB5_1
# BB#8:                                 # %entry_ifend26
	movq	(%rax), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	movl	%ebp, %r8d
	movq	%rcx, %rbx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#9:                                 # %entry_ifend30
	movq	(%rax), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movl	$2, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movl	%r12d, %edx
	movq	%rbx, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#10:                                # %entry_ifend34
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movl	$2272, %esi             # imm = 0x8E0
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#11:                                # %entry_ifend37
	movq	32(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$12, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r15, %r8
	movq	%rbx, %r9
	movq	%rbx, %rbp
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%r12d, %r13d
	movq	%r14, %rbx
	je	.LBB5_13
# BB#12:                                # %then_block53
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_13:                               # %entry_ifend54
	movq	(%rbx), %r14
	movq	$0, 56(%rsp)
	movq	%r14, 56(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 64(%rsp)
	movq	%r12, 64(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%rbp, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movl	%r13d, %edx
	je	.LBB5_1
# BB#14:                                # %entry_ifend69
	movq	(%rax), %r9
	movl	$1, (%rsp)
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movq	%rbp, %rcx
	movl	%r12d, %r8d
	callq	store_field
	testl	%eax, %eax
	je	.LBB5_1
# BB#15:                                # %entry_ifend72
	movl	$0, gSigInt(%rip)
	movl	%r12d, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB5_2
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
.Lfunc_end5:
	.size	"Buffer.clone()$$9", .Lfunc_end5-"Buffer.clone()$$9"
	.cfi_endproc

	.globl	"Buffer.toString()$$10"
	.align	16, 0x90
	.type	"Buffer.toString()$$10",@function
"Buffer.toString()$$10":                # @"Buffer.toString()$$10"
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
	subq	$56, %rsp
.Ltmp84:
	.cfi_def_cfa_offset 112
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
	movl	%r9d, %ebp
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	(%r14), %r13
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 40(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movl	$1, %r9d
	movq	%rbx, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#4:                                 # %entry_ifend4
	movq	112(%rsp), %rdi
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movl	$2280, %esi             # imm = 0x8E8
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#5:                                 # %entry_ifend7
	leaq	8(%r12), %rcx
	movq	$0, (%r12)
	movq	%r13, (%r12)
	movq	$0, 8(%r12)
	movq	$0, 16(%r12)
	movq	(%rbx), %rdx
	movq	$0, (%rdx)
	movq	%rcx, (%rdx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	$1, 8(%rcx)
	addq	$8, (%rbx)
	movl	$33, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebp, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_6
# BB#7:                                 # %entry_ifend26
	movq	(%r14), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r14), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	$2288, %esi             # imm = 0x8F0
	movq	112(%rsp), %rax
	movq	%rax, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#8:                                 # %entry_ifend36
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$2296, %esi             # imm = 0x8F8
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#9:                                 # %entry_ifend40
	movq	$0, (%r12)
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r12)
	movq	$0, 8(%r12)
	movq	24(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, 8(%r12)
	movq	$0, 16(%r12)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, 16(%r12)
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
	addq	$8, (%rbx)
	movl	$2, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%ebp, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB6_10
.LBB6_6:                                # %then_block25
	movq	%r15, %rdi
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
.LBB6_10:                               # %entry_ifend56
	movq	(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	8(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	16(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, 48(%rsp)
	movq	%rbp, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	%ebp, %eax
	movq	%rax, (%r14)
	movl	$1, %eax
	jmp	.LBB6_2
.Lfunc_end6:
	.size	"Buffer.toString()$$10", .Lfunc_end6-"Buffer.toString()$$10"
	.cfi_endproc

	.globl	"Buffer.subBuffer(int,int)$$11"
	.align	16, 0x90
	.type	"Buffer.subBuffer(int,int)$$11",@function
"Buffer.subBuffer(int,int)$$11":        # @"Buffer.subBuffer(int,int)$$11"
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
	subq	$136, %rsp
.Ltmp97:
	.cfi_def_cfa_offset 192
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
	movl	%r9d, %ebx
	movq	%r8, %rdi
	movq	%rcx, %rbp
	movq	%rdx, %rcx
	movq	%rsi, 64(%rsp)          # 8-byte Spill
	movq	(%rbp), %r14
	movq	$0, 88(%rsp)
	movq	%r14, 88(%rsp)
	movq	8(%rbp), %r12
	movq	$0, 96(%rsp)
	movq	%r12, 96(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	$0, 112(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%r12d, %r12d
	jns	.LBB7_5
# BB#1:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rdi, %r13
	movq	%rbp, %rsi
	movq	%rbp, %r15
	movl	%ebx, %edx
	movq	%rcx, %rbp
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_2
# BB#4:                                 # %entry_ifend
	movq	(%rax), %rax
	addl	%eax, %r12d
	movq	$0, 96(%rsp)
	movq	%r12, 96(%rsp)
	movq	%rbp, %rcx
	movq	%r15, %rbp
	movq	%r13, %rdi
.LBB7_5:                                # %label_if_endzzzzzzzzzzzzzzzzzzzzn
	movl	$0, gSigInt(%rip)
	movq	104(%rsp), %r15
	testl	%r15d, %r15d
	jns	.LBB7_8
# BB#6:                                 # %entry_condend11
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rdi, 80(%rsp)          # 8-byte Spill
	movq	%rbp, %rsi
	movl	%ebx, %edx
	movq	%rcx, %r13
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_2
# BB#7:                                 # %entry_ifend16
	movq	(%rax), %rax
	leal	1(%rax,%r15), %r15d
	movq	$0, 104(%rsp)
	movq	%r15, 104(%rsp)
	movq	%r13, %rcx
	movq	80(%rsp), %rdi          # 8-byte Reload
.LBB7_8:                                # %label_if_endzzzzzzzzzzzzzzzzzzzzo
	movl	$0, gSigInt(%rip)
	testl	%r12d, %r12d
	jns	.LBB7_10
# BB#9:                                 # %entry_condend25
	movl	$0, gSigInt(%rip)
	movq	$0, 96(%rsp)
	xorl	%r12d, %r12d
.LBB7_10:                               # %label_if_endzzzzzzzzzzzzzzzzzzzzp
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rdi, 80(%rsp)          # 8-byte Spill
	movq	%rbp, %rsi
	movq	%rbp, 72(%rsp)          # 8-byte Spill
	movl	%ebx, %edx
	movq	%rcx, %r13
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_2
# BB#11:                                # %entry_ifend31
	movq	(%rax), %rax
	cmpl	%eax, %r15d
	jle	.LBB7_14
# BB#12:                                # %entry_condend35
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	80(%rsp), %rdi          # 8-byte Reload
	movq	72(%rsp), %rsi          # 8-byte Reload
	movl	%ebx, %edx
	movq	%r13, %rcx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_2
# BB#13:                                # %entry_ifend39
	movq	(%rax), %rax
	movq	$0, 104(%rsp)
	movl	%eax, %r15d
	movq	%r15, 104(%rsp)
.LBB7_14:                               # %label_if_endzzzzzzzzzzzzzzzzzzzzq
	movl	$0, gSigInt(%rip)
	cmpl	%r15d, %r12d
	setge	%al
	movq	$0, 120(%rsp)
	movzbl	%al, %eax
	movq	%rax, 120(%rsp)
	movl	%ebx, %edx
	movq	%r13, %rcx
	jge	.LBB7_19
# BB#15:                                # %entry_condnotend
	movl	$1, %r9d
	movq	80(%rsp), %rdi          # 8-byte Reload
	movq	72(%rsp), %rsi          # 8-byte Reload
	movl	%edx, %r13d
	movq	%rcx, %rbx
	movl	%r14d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_2
# BB#16:                                # %entry_ifend49
	movq	(%rax), %rax
	cmpl	%eax, %r12d
	setge	%al
	movq	$0, 128(%rsp)
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
	jge	.LBB7_18
# BB#17:                                # %entry_condnotend55
	testl	%r15d, %r15d
	sets	%al
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
.LBB7_18:                               # %label_or_endpointzzzzzzzzzzzzzzzzzzzzt
	movq	%rax, 120(%rsp)
	movl	%r13d, %edx
	movq	%rbx, %rcx
.LBB7_19:                               # %label_or_endpointzzzzzzzzzzzzzzzzzzzzs
	movl	$0, gSigInt(%rip)
	testq	%rax, %rax
	je	.LBB7_21
# BB#20:                                # %entry_condend62
	movl	$.Lglobal_string.3, %edi
	xorl	%esi, %esi
	callq	create_buffer_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	72(%rsp), %rcx          # 8-byte Reload
	movq	%rax, (%rcx)
	movl	$1, %eax
	jmp	.LBB7_3
.LBB7_21:                               # %label_if_endzzzzzzzzzzzzzzzzzzzzr
	movq	%rcx, 56(%rsp)          # 8-byte Spill
	movl	%edx, 52(%rsp)          # 4-byte Spill
	movq	192(%rsp), %rbx
	movl	$3004, %esi             # imm = 0xBBC
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_2
# BB#22:                                # %entry_ifend66
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%r15d, %r13d
	movl	%r12d, %eax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movl	$3012, %esi             # imm = 0xBC4
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_2
# BB#23:                                # %entry_ifend73
	subq	40(%rsp), %r13          # 8-byte Folded Reload
	movq	64(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r14, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r15, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	80(%rsp), %r12          # 8-byte Reload
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r12)
	movl	$2, %esi
	movq	%rax, %rdi
	movq	72(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	52(%rsp), %r14d         # 4-byte Reload
	movl	%r14d, %ecx
	movq	%r12, %r8
	movq	56(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB7_25
# BB#24:                                # %then_block87
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB7_2
.LBB7_25:                               # %entry_ifend88
	movq	(%rbx), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbx), %r15
	movq	$0, 96(%rsp)
	movq	%r15, 96(%rsp)
	movq	16(%rbx), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 112(%rsp)
	movq	%r13, 112(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	192(%rsp), %rbp
	je	.LBB7_2
# BB#26:                                # %entry_ifend102
	movq	(%rax), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	56(%rsp), %rcx          # 8-byte Reload
	movq	40(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_2
# BB#27:                                # %entry_ifend106
	movq	%rbp, %rdi
	movq	(%rax), %rbp
	movl	%r15d, %eax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	32(%rsp), %rax          # 8-byte Reload
	subl	%r15d, %eax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movl	$3020, %esi             # imm = 0xBCC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_2
# BB#28:                                # %entry_ifend116
	movq	%rbp, %rsi
	addq	8(%rsp), %rsi           # 8-byte Folded Reload
	movq	64(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r15, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	%r13, 24(%rcx)
	movq	%r12, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movq	%rsi, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$12, %esi
	movq	%rax, %rdi
	movq	%rbx, %r12
	movq	%r12, %rdx
	movl	%r14d, %ebx
	movl	%ebx, %ecx
	movq	%rbp, %r8
	movq	56(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB7_30
# BB#29:                                # %then_block136
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB7_2
.LBB7_30:                               # %entry_ifend137
	movq	(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r12), %rax
	movq	%rax, 64(%rsp)          # 8-byte Spill
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r12), %r13
	movq	$0, 104(%rsp)
	movq	%r13, 104(%rsp)
	movq	24(%r12), %r15
	movq	$0, 112(%rsp)
	movq	%r15, 112(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	movq	64(%rsp), %rax          # 8-byte Reload
	subl	%eax, %r13d
	movl	$1, (%rsp)
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	movl	%r15d, %r8d
	movq	%r13, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB7_2
# BB#31:                                # %entry_ifend159
	movl	$0, gSigInt(%rip)
	movl	$2, (%rsp)
	movq	80(%rsp), %rdi          # 8-byte Reload
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%r14, %rcx
	movl	%r15d, %r8d
	movq	%r13, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB7_2
# BB#32:                                # %entry_ifend167
	movl	$0, gSigInt(%rip)
	movl	%r15d, %eax
	movq	%rax, (%r12)
	movl	$1, %eax
	jmp	.LBB7_3
.LBB7_2:                                # %then_block
	xorl	%eax, %eax
.LBB7_3:                                # %then_block
	addq	$136, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end7:
	.size	"Buffer.subBuffer(int,int)$$11", .Lfunc_end7-"Buffer.subBuffer(int,int)$$11"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"Invalid range on Buffer.char"
	.size	.Lglobal_string, 29

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.asciz	"Invalid range on Buffer.char"
	.size	.Lglobal_string.2, 29

	.type	.Lglobal_string.3,@object # @global_string.3
.Lglobal_string.3:
	.asciz	"label_if_endzzzzzzzzzzzzzzzzzzzzr"
	.size	.Lglobal_string.3, 34


	.section	".note.GNU-stack","",@progbits
