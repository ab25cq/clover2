	.text
	.file	"Command.bc"
	.globl	"Command.setValue(Self)$$4"
	.align	16, 0x90
	.type	"Command.setValue(Self)$$4",@function
"Command.setValue(Self)$$4":            # @"Command.setValue(Self)$$4"
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
	.size	"Command.setValue(Self)$$4", .Lfunc_end0-"Command.setValue(Self)$$4"
	.cfi_endproc

	.globl	"Command.callingMethod(String,Array,int,int)$$5"
	.align	16, 0x90
	.type	"Command.callingMethod(String,Array,int,int)$$5",@function
"Command.callingMethod(String,Array,int,int)$$5": # @"Command.callingMethod(String,Array,int,int)$$5"
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
	subq	$136, %rsp
.Ltmp19:
	.cfi_def_cfa_offset 192
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
	movl	%r9d, 52(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %r12
	movq	%rsi, %r13
	movq	192(%rsp), %rbp
	movq	(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%r14), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%r14), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2188, %esi             # imm = 0x88C
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2196, %esi             # imm = 0x894
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#4:                                 # %entry_ifend7
	movq	56(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	64(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	72(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	88(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%r12, %rbp
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_5
# BB#6:                                 # %entry_ifend27
	movq	(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r14), %rax
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
	movq	48(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	56(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
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
	movq	$0, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %eax
	movl	%eax, 48(%rsp)          # 4-byte Spill
	movq	%rbp, 32(%rsp)
	movl	$0, 24(%rsp)
	movl	$7, 16(%rsp)
	movl	$2, 8(%rsp)
	movl	$3048, (%rsp)           # imm = 0xBE8
	movl	$2204, %ecx             # imm = 0x89C
	movl	$1408, %r8d             # imm = 0x580
	movl	$3612, %r9d             # imm = 0xE1C
	movq	%r15, %rdi
	movq	%r14, %rsi
	movq	192(%rsp), %rbx
	movq	%rbx, %rdx
	callq	run_create_block_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$6660, %esi             # imm = 0x1A04
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#7:                                 # %entry_ifend49
	movq	56(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	64(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	72(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	88(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	%r15, %rbx
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	48(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$4, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_5
# BB#8:                                 # %entry_ifend75
	movq	(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r14), %rax
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
	movq	48(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	56(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	testb	$1, 104(%rsp)
	je	.LBB1_14
# BB#9:                                 # %entry_condend
	movq	%r14, %r15
	movl	$0, gSigInt(%rip)
	movq	$0, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r14d
	movl	88(%rsp), %r12d
	movl	$6704, %esi             # imm = 0x1A30
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#10:                                # %entry_ifend104
	movq	56(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	64(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	72(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	88(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
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
	addq	$8, (%rbx)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r15, %r14
	jmp	.LBB1_11
.LBB1_14:                               # %label_elifzzzzzzzzzzzzzzzzzzzzzzj1a
	movq	96(%rsp), %rcx
	movq	$0, 120(%rsp)
	movl	%ecx, %eax
	movq	%rax, 120(%rsp)
	testb	$1, %cl
	movq	192(%rsp), %rdi
	jne	.LBB1_15
# BB#19:                                # %entry_condnotend
	movq	%rbx, %r12
	movl	80(%rsp), %eax
	decl	%eax
	cmpl	%eax, 72(%rsp)
	sete	%al
	movq	$0, 128(%rsp)
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
	jne	.LBB1_24
# BB#20:                                # %entry_condend164
	movq	%rdi, (%rsp)
	xorl	%r8d, %r8d
	movl	$6872, %r9d             # imm = 0x1AD8
	movq	%rdi, %rbx
	movq	%r12, %rdi
	movq	%r14, %rsi
	movq	%r14, %r15
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#21:                                # %entry_ifend167
	movq	(%rax), %r14
	movl	56(%rsp), %eax
	movl	%eax, 48(%rsp)          # 4-byte Spill
	movl	$6880, %esi             # imm = 0x1AE0
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#22:                                # %entry_ifend171
	movq	56(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	64(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	72(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	88(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	48(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$35, %esi
	movq	%rax, %rdi
	movq	%r15, %r14
	movq	%r14, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_5
# BB#23:                                # %entry_ifend197
	movq	(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r14), %rax
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
	movq	48(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	56(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	cmpl	$-1, %ebx
	setne	%al
	movzbl	%al, %eax
	movq	%rax, 128(%rsp)
	movq	192(%rsp), %rdi
.LBB1_24:                               # %label_and_endpointzzzzzzzzzzzzzzzzzzzzzzl
	movq	%rax, 120(%rsp)
	movq	%r12, %rbx
.LBB1_15:                               # %label_or_endpointzzzzzzzzzzzzzzzzzzzzzzk
	movq	%r14, 40(%rsp)          # 8-byte Spill
	movl	$0, gSigInt(%rip)
	testb	$1, %al
	je	.LBB1_25
# BB#16:                                # %entry_condend223
	movl	56(%rsp), %r14d
	movl	88(%rsp), %r12d
	movl	$7024, %esi             # imm = 0x1B70
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#17:                                # %entry_ifend228
	movq	56(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	64(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	72(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	88(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	%rbx, %r15
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$9, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_5
# BB#18:                                # %entry_ifend254
	movq	(%rbx), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbp, (%rbx)
	movl	$1, %eax
	jmp	.LBB1_2
.LBB1_25:                               # %label_if_elifzzzzzzzzzzzzzzzzzzzzzzj0a
	movq	$0, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r14d
	movl	88(%rsp), %r12d
	movl	$7144, %esi             # imm = 0x1BE8
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#26:                                # %entry_ifend284
	movq	56(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	64(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	72(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	80(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	88(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	96(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
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
	addq	$8, (%rbx)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %r14          # 8-byte Reload
.LBB1_11:                               # %entry_ifend104
	movq	%r14, %rdx
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_12
.LBB1_5:                                # %then_block26
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB1_1:                                # %then_block
	xorl	%eax, %eax
.LBB1_2:                                # %then_block
	addq	$136, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB1_12:                               # %entry_ifend133
	movq	(%r14), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	8(%r14), %rax
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
	movq	48(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	56(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbp, (%r14)
	movl	$1, %eax
	jmp	.LBB1_2
.Lfunc_end1:
	.size	"Command.callingMethod(String,Array,int,int)$$5", .Lfunc_end1-"Command.callingMethod(String,Array,int,int)$$5"
	.cfi_endproc

	.globl	"Command.callingMethod(String,Array,int,int)$$6"
	.align	16, 0x90
	.type	"Command.callingMethod(String,Array,int,int)$$6",@function
"Command.callingMethod(String,Array,int,int)$$6": # @"Command.callingMethod(String,Array,int,int)$$6"
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
	subq	$168, %rsp
.Ltmp32:
	.cfi_def_cfa_offset 224
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
	movl	%r9d, 84(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, %r12
	movq	%rsi, %r13
	movq	224(%rsp), %rbp
	movq	(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	$0, 128(%rsp)
	movq	$0, 136(%rsp)
	movq	$0, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$7224, %esi             # imm = 0x1C38
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$7232, %esi             # imm = 0x1C40
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#4:                                 # %entry_ifend9
	movq	88(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	84(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %rbp
	movq	%rbp, %r8
	movq	%r12, %r15
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_6
# BB#5:                                 # %then_block28
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB2_1
.LBB2_6:                                # %entry_ifend29
	movq	(%r14), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r14), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r14), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r14), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r14), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r14), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r14), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r14), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 128(%rsp)
	movq	%rbx, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movq	%rbp, %rdi
	movl	104(%rsp), %eax
	movl	%eax, 68(%rsp)          # 4-byte Spill
	movq	%r15, 32(%rsp)
	movq	%r15, 72(%rsp)          # 8-byte Spill
	movl	$0, 24(%rsp)
	movl	$8, 16(%rsp)
	movl	$2, 8(%rsp)
	movl	$3048, (%rsp)           # imm = 0xBE8
	movl	$7240, %ecx             # imm = 0x1C48
	movl	$1408, %r8d             # imm = 0x580
	movl	$8648, %r9d             # imm = 0x21C8
	movq	%r14, %rsi
	movq	%r14, %r15
	movq	224(%rsp), %rbx
	movq	%rbx, %rdx
	callq	run_create_block_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$11696, %esi            # imm = 0x2DB0
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#7:                                 # %entry_ifend51
	movq	88(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	68(%rsp), %edx          # 4-byte Reload
	movq	%rbp, %r14
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$4, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	84(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	72(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_8
# BB#9:                                 # %entry_ifend77
	movq	(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	testb	$1, 144(%rsp)
	je	.LBB2_16
# BB#10:                                # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %ebx
	movl	128(%rsp), %r12d
	movl	88(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	84(%rsp), %edx          # 4-byte Reload
	movq	72(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	224(%rsp), %rdi
	je	.LBB2_1
# BB#11:                                # %entry_ifend106
	movq	(%rax), %rbp
	movl	$11740, %esi            # imm = 0x2DDC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#12:                                # %entry_ifend109
	movq	88(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	%rbp, %rsi
	movq	%r14, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	84(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	72(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_13
# BB#14:                                # %entry_ifend138
	movq	(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%r14, (%r15)
	movl	$1, %eax
	jmp	.LBB2_2
.LBB2_16:                               # %label_elifzzzzzzzzzzzzzzzzzzzzzzu1a
	movq	136(%rsp), %rax
	movq	$0, 152(%rsp)
	movl	%eax, %ebx
	movq	%rbx, 152(%rsp)
	testb	$1, %al
	jne	.LBB2_17
# BB#23:                                # %entry_condnotend
	movq	%r15, %r12
	movl	120(%rsp), %eax
	decl	%eax
	cmpl	%eax, 112(%rsp)
	sete	%al
	movq	$0, 160(%rsp)
	movzbl	%al, %ebx
	movq	%rbx, 160(%rsp)
	jne	.LBB2_28
# BB#24:                                # %entry_condend169
	movq	224(%rsp), %rbx
	movq	%rbx, (%rsp)
	xorl	%r8d, %r8d
	movl	$11908, %r9d            # imm = 0x2E84
	movq	%r14, %rdi
	movq	%r14, %rbp
	movq	%r12, %rsi
	movl	84(%rsp), %edx          # 4-byte Reload
	movq	72(%rsp), %rcx          # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#25:                                # %entry_ifend172
	movq	(%rax), %r14
	movl	96(%rsp), %r15d
	movl	$11916, %esi            # imm = 0x2E8C
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#26:                                # %entry_ifend176
	movq	88(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rbp, %r14
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$35, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	84(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	72(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_27
.LBB2_8:                                # %then_block76
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB2_1:                                # %then_block
	xorl	%eax, %eax
.LBB2_2:                                # %then_block
	addq	$168, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB2_27:                               # %entry_ifend202
	movq	(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	cmpl	$-1, %ebx
	setne	%al
	movzbl	%al, %ebx
	movq	%rbx, 160(%rsp)
.LBB2_28:                               # %label_and_endpointzzzzzzzzzzzzzzzzzzzzzzw
	movq	%rbx, 152(%rsp)
	movq	%r12, %r15
.LBB2_17:                               # %label_or_endpointzzzzzzzzzzzzzzzzzzzzzzv
	movq	%r15, 56(%rsp)          # 8-byte Spill
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %r12d
	movl	128(%rsp), %eax
	movl	%eax, 68(%rsp)          # 4-byte Spill
	movl	88(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	84(%rsp), %edx          # 4-byte Reload
	movq	72(%rsp), %rcx          # 8-byte Reload
	callq	get_field_from_object
	movq	(%rax), %r15
	movl	8(%rax), %eax
	testb	$1, %bl
	je	.LBB2_29
# BB#18:                                # %entry_condend228
	testl	%eax, %eax
	movq	224(%rsp), %rdi
	je	.LBB2_1
# BB#19:                                # %entry_ifend234
	movl	$12060, %esi            # imm = 0x2F1C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#20:                                # %entry_ifend237
	movq	88(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	%r14, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	68(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$10, %esi
	jmp	.LBB2_21
.LBB2_29:                               # %label_if_elifzzzzzzzzzzzzzzzzzzzzzzu0a
	testl	%eax, %eax
	movq	224(%rsp), %rdi
	je	.LBB2_1
# BB#30:                                # %entry_ifend296
	movl	$12180, %esi            # imm = 0x2F94
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#31:                                # %entry_ifend299
	movq	88(%rsp), %rcx
	movq	$0, (%r13)
	movq	%rcx, (%r13)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r13)
	movq	%rcx, 8(%r13)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r13)
	movq	%rcx, 16(%r13)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r13)
	movq	%rcx, 24(%r13)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r13)
	movq	%rcx, 32(%r13)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r13)
	movq	%rcx, 40(%r13)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r13)
	movq	%rcx, 48(%r13)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r13)
	movq	%rcx, 56(%r13)
	movq	%r14, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	68(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$8, %esi
.LBB2_21:                               # %entry_ifend237
	movq	%rax, %rdi
	movq	56(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	84(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	72(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_22
.LBB2_13:                               # %then_block137
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB2_1
.LBB2_22:                               # %entry_ifend266
	movq	(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%r14, (%rbx)
	movl	$1, %eax
	jmp	.LBB2_2
.Lfunc_end2:
	.size	"Command.callingMethod(String,Array,int,int)$$6", .Lfunc_end2-"Command.callingMethod(String,Array,int,int)$$6"
	.cfi_endproc

	.globl	"Command.executeCommandWithGettingStderr(String,List,String)$$7"
	.align	16, 0x90
	.type	"Command.executeCommandWithGettingStderr(String,List,String)$$7",@function
"Command.executeCommandWithGettingStderr(String,List,String)$$7": # @"Command.executeCommandWithGettingStderr(String,List,String)$$7"
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
	subq	$216, %rsp
.Ltmp45:
	.cfi_def_cfa_offset 272
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
	movl	%r9d, %r12d
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, %rbx
	movq	%rsi, %rbp
	movq	272(%rsp), %rdi
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movq	$0, 120(%rsp)
	movq	$0, 128(%rsp)
	movq	$0, 136(%rsp)
	movq	$0, 144(%rsp)
	movq	$0, 152(%rsp)
	movq	$0, 160(%rsp)
	movq	$0, 168(%rsp)
	movq	$0, 176(%rsp)
	movq	$0, 184(%rsp)
	movq	$0, 192(%rsp)
	movq	$0, 200(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 120(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$12260, %esi            # imm = 0x2FE4
	movq	%rdi, %r13
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#3:                                 # %entry_ifend
	leaq	48(%rbp), %rdx
	leaq	40(%rbp), %rcx
	movq	72(%rsp), %rsi
	movq	$0, (%rbp)
	movq	%rsi, (%rbp)
	movq	80(%rsp), %rsi
	movq	$0, 8(%rbp)
	movq	%rsi, 8(%rbp)
	movq	88(%rsp), %rsi
	movq	$0, 16(%rbp)
	movq	%rsi, 16(%rbp)
	movq	96(%rsp), %rsi
	movq	$0, 24(%rbp)
	movq	%rsi, 24(%rbp)
	movq	104(%rsp), %rsi
	movq	$0, 32(%rbp)
	movq	%rsi, 32(%rbp)
	movq	112(%rsp), %rsi
	movq	$0, 40(%rbp)
	movq	%rsi, 40(%rbp)
	movq	120(%rsp), %rsi
	movq	$0, 48(%rbp)
	movq	%rsi, 48(%rbp)
	movq	128(%rsp), %rsi
	movq	$0, 56(%rbp)
	movq	%rsi, 56(%rbp)
	movq	136(%rsp), %rsi
	movq	$0, 64(%rbp)
	movq	%rsi, 64(%rbp)
	movq	144(%rsp), %rsi
	movq	$0, 72(%rbp)
	movq	%rsi, 72(%rbp)
	movq	152(%rsp), %rsi
	movq	$0, 80(%rbp)
	movq	%rsi, 80(%rbp)
	movq	160(%rsp), %rsi
	movq	$0, 88(%rbp)
	movq	%rsi, 88(%rbp)
	movq	168(%rsp), %rsi
	movq	$0, 96(%rbp)
	movq	%rsi, 96(%rbp)
	movq	176(%rsp), %rsi
	movq	$0, 104(%rbp)
	movq	%rsi, 104(%rbp)
	movq	184(%rsp), %rsi
	movq	$0, 112(%rbp)
	movq	%rsi, 112(%rbp)
	movq	192(%rsp), %rsi
	movq	$0, 120(%rbp)
	movq	%rsi, 120(%rbp)
	movq	200(%rsp), %rsi
	movq	$0, 128(%rbp)
	movq	%rsi, 128(%rbp)
	movq	(%r14), %rsi
	movq	$0, (%rsi)
	movq	%rdx, (%rsi)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	addq	$8, (%r14)
	movl	$80, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#5:                                 # %entry_ifend44
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	$12268, %esi            # imm = 0x2FEC
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#6:                                 # %entry_ifend85
	leaq	24(%rbp), %rcx
	leaq	32(%rbp), %rdx
	movq	72(%rsp), %rsi
	movq	$0, (%rbp)
	movq	%rsi, (%rbp)
	movq	80(%rsp), %rsi
	movq	$0, 8(%rbp)
	movq	%rsi, 8(%rbp)
	movq	88(%rsp), %rsi
	movq	$0, 16(%rbp)
	movq	%rsi, 16(%rbp)
	movq	96(%rsp), %rsi
	movq	$0, 24(%rbp)
	movq	%rsi, 24(%rbp)
	movq	104(%rsp), %rsi
	movq	$0, 32(%rbp)
	movq	%rsi, 32(%rbp)
	movq	112(%rsp), %rsi
	movq	$0, 40(%rbp)
	movq	%rsi, 40(%rbp)
	movq	120(%rsp), %rsi
	movq	$0, 48(%rbp)
	movq	%rsi, 48(%rbp)
	movq	128(%rsp), %rsi
	movq	$0, 56(%rbp)
	movq	%rsi, 56(%rbp)
	movq	136(%rsp), %rsi
	movq	$0, 64(%rbp)
	movq	%rsi, 64(%rbp)
	movq	144(%rsp), %rsi
	movq	$0, 72(%rbp)
	movq	%rsi, 72(%rbp)
	movq	152(%rsp), %rsi
	movq	$0, 80(%rbp)
	movq	%rsi, 80(%rbp)
	movq	160(%rsp), %rsi
	movq	$0, 88(%rbp)
	movq	%rsi, 88(%rbp)
	movq	168(%rsp), %rsi
	movq	$0, 96(%rbp)
	movq	%rsi, 96(%rbp)
	movq	176(%rsp), %rsi
	movq	$0, 104(%rbp)
	movq	%rsi, 104(%rbp)
	movq	184(%rsp), %rsi
	movq	$0, 112(%rbp)
	movq	%rsi, 112(%rbp)
	movq	192(%rsp), %rsi
	movq	$0, 120(%rbp)
	movq	%rsi, 120(%rbp)
	movq	200(%rsp), %rsi
	movq	$0, 128(%rbp)
	movq	%rsi, 128(%rbp)
	movq	(%r14), %rsi
	movq	$0, (%rsi)
	movq	%rdx, (%rsi)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	addq	$8, (%r14)
	movl	$80, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#7:                                 # %entry_ifend129
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	$12276, %esi            # imm = 0x2FF4
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#8:                                 # %entry_ifend174
	leaq	56(%rbp), %rdx
	leaq	64(%rbp), %rcx
	movq	72(%rsp), %rsi
	movq	$0, (%rbp)
	movq	%rsi, (%rbp)
	movq	80(%rsp), %rsi
	movq	$0, 8(%rbp)
	movq	%rsi, 8(%rbp)
	movq	88(%rsp), %rsi
	movq	$0, 16(%rbp)
	movq	%rsi, 16(%rbp)
	movq	96(%rsp), %rsi
	movq	$0, 24(%rbp)
	movq	%rsi, 24(%rbp)
	movq	104(%rsp), %rsi
	movq	$0, 32(%rbp)
	movq	%rsi, 32(%rbp)
	movq	112(%rsp), %rsi
	movq	$0, 40(%rbp)
	movq	%rsi, 40(%rbp)
	movq	120(%rsp), %rsi
	movq	$0, 48(%rbp)
	movq	%rsi, 48(%rbp)
	movq	128(%rsp), %rsi
	movq	$0, 56(%rbp)
	movq	%rsi, 56(%rbp)
	movq	136(%rsp), %rsi
	movq	$0, 64(%rbp)
	movq	%rsi, 64(%rbp)
	movq	144(%rsp), %rsi
	movq	$0, 72(%rbp)
	movq	%rsi, 72(%rbp)
	movq	152(%rsp), %rsi
	movq	$0, 80(%rbp)
	movq	%rsi, 80(%rbp)
	movq	160(%rsp), %rsi
	movq	$0, 88(%rbp)
	movq	%rsi, 88(%rbp)
	movq	168(%rsp), %rsi
	movq	$0, 96(%rbp)
	movq	%rsi, 96(%rbp)
	movq	176(%rsp), %rsi
	movq	$0, 104(%rbp)
	movq	%rsi, 104(%rbp)
	movq	184(%rsp), %rsi
	movq	$0, 112(%rbp)
	movq	%rsi, 112(%rbp)
	movq	192(%rsp), %rsi
	movq	$0, 120(%rbp)
	movq	%rsi, 120(%rbp)
	movq	200(%rsp), %rsi
	movq	$0, 128(%rbp)
	movq	%rsi, 128(%rbp)
	movq	(%r14), %rsi
	movq	$0, (%rsi)
	movq	%rdx, (%rsi)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	addq	$8, (%r14)
	movl	$80, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#9:                                 # %entry_ifend218
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movq	%rbx, 32(%rsp)
	movl	$0, 24(%rsp)
	movl	$10, 16(%rsp)
	movl	$2, 8(%rsp)
	movl	$251, (%rsp)
	movl	$12284, %ecx            # imm = 0x2FFC
	movl	$588, %r8d              # imm = 0x24C
	movl	$12872, %r9d            # imm = 0x3248
	movq	%r14, %rdi
	movq	%r15, %rsi
	movq	%rbx, %rax
	movl	%r12d, %ebx
	movq	%rax, 64(%rsp)          # 8-byte Spill
	movq	%r13, %r12
	movq	%r12, %rdx
	callq	run_create_block_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$13124, %esi            # imm = 0x3344
	movq	%r12, %rdi
	movl	%ebx, %r12d
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#10:                                # %entry_ifend261
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$81, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	64(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#11:                                # %entry_ifend302
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 144(%rsp)
	movq	%r13, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movl	120(%rsp), %r13d
	movl	$13132, %esi            # imm = 0x334C
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#12:                                # %entry_ifend346
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$40, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#13:                                # %entry_ifend387
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %r13d
	movl	$13140, %esi            # imm = 0x3354
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#14:                                # %entry_ifend431
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$40, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#15:                                # %entry_ifend472
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	136(%rsp), %r13d
	movl	$13148, %esi            # imm = 0x335C
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#16:                                # %entry_ifend516
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$40, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#17:                                # %entry_ifend557
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %r13d
	testl	%r13d, %r13d
	je	.LBB3_24
# BB#18:                                # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$13192, %esi            # imm = 0x3388
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#19:                                # %entry_ifend602
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#20:                                # %entry_ifend643
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 152(%rsp)
	movq	%r13, 152(%rsp)
	movl	$0, gSigInt(%rip)
	movl	112(%rsp), %eax
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r12d, %edx
	movq	%rbx, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#21:                                # %entry_ifend689
	movq	(%rax), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movl	$13200, %esi            # imm = 0x3390
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#22:                                # %entry_ifend692
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$42, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#23:                                # %entry_ifend739
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
.LBB3_24:                               # %label_if_endzzzzzzzzzzzzzzzzzzzzzzz
	movl	$0, gSigInt(%rip)
	movl	112(%rsp), %r13d
	movl	$13280, %esi            # imm = 0x33E0
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#25:                                # %entry_ifend784
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$40, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#26:                                # %entry_ifend825
	leaq	88(%rbp), %rax
	movq	%rax, 48(%rsp)          # 8-byte Spill
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string, %edi
	xorl	%esi, %esi
	callq	create_buffer_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movq	$0, 152(%rsp)
	movl	%r13d, %eax
	movq	%rax, 152(%rsp)
	movl	$0, gSigInt(%rip)
.LBB3_27:                               # %entry_condend868
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	movl	$13368, %esi            # imm = 0x3438
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#28:                                # %entry_ifend871
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$13376, %esi            # imm = 0x3440
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#29:                                # %entry_ifend874
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	$128, 8(%rcx)
	addq	$8, (%r14)
	movl	$2, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_30
# BB#31:                                # %entry_ifend918
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 160(%rsp)
	movq	%rbx, 160(%rsp)
	movl	$0, gSigInt(%rip)
	movl	104(%rsp), %r13d
	movl	$13384, %esi            # imm = 0x3448
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	64(%rsp), %r9           # 8-byte Reload
	je	.LBB3_1
# BB#32:                                # %entry_ifend963
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
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
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	$128, 8(%rcx)
	addq	$8, (%r14)
	movl	$41, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#33:                                # %entry_ifend1010
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 168(%rsp)
	movq	%r13, 168(%rsp)
	movl	$0, gSigInt(%rip)
	movl	152(%rsp), %r13d
	movl	160(%rsp), %eax
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movl	$13392, %esi            # imm = 0x3450
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	je	.LBB3_1
# BB#34:                                # %entry_ifend1055
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$4, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#35:                                # %entry_ifend1099
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	$13400, %esi            # imm = 0x3458
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#36:                                # %entry_ifend1142
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$13408, %esi            # imm = 0x3460
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#37:                                # %entry_ifend1145
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	$128, 8(%rcx)
	addq	$8, (%r14)
	movl	$2, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_30
# BB#38:                                # %entry_ifend1189
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 176(%rsp)
	movq	%rbx, 176(%rsp)
	movl	$0, gSigInt(%rip)
	movl	128(%rsp), %r13d
	movl	$13416, %esi            # imm = 0x3468
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	64(%rsp), %r9           # 8-byte Reload
	je	.LBB3_1
# BB#39:                                # %entry_ifend1234
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
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
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	$128, 8(%rcx)
	addq	$8, (%r14)
	movl	$41, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#40:                                # %entry_ifend1281
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 184(%rsp)
	movq	%r13, 184(%rsp)
	movl	$0, gSigInt(%rip)
	movl	152(%rsp), %r13d
	movl	176(%rsp), %eax
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movl	$13424, %esi            # imm = 0x3470
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#41:                                # %entry_ifend1326
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$4, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_4
# BB#42:                                # %entry_ifend1370
                                        #   in Loop: Header=BB3_27 Depth=1
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	cmpl	$0, 168(%rsp)
	sete	%al
	movq	$0, 208(%rsp)
	movzbl	%al, %eax
	movq	%rax, 208(%rsp)
	jne	.LBB3_44
# BB#43:                                # %entry_condend1415
                                        #   in Loop: Header=BB3_27 Depth=1
	cmpl	$0, 184(%rsp)
	sete	%al
	movzbl	%al, %eax
	movq	%rax, 208(%rsp)
.LBB3_44:                               # %label_and_endpointzzzzzzzzzzzzzzzzzzzzzzzd
                                        #   in Loop: Header=BB3_27 Depth=1
	testq	%rax, %rax
	je	.LBB3_27
# BB#45:                                # %entry_condend1420
	movl	$0, gSigInt(%rip)
	movl	104(%rsp), %r13d
	movl	$13756, %esi            # imm = 0x35BC
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#46:                                # %entry_ifend1427
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$40, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	movq	%rbx, %r13
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB3_48
# BB#47:                                # %then_block1467
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_4:                                # %then_block43
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB3_1:                                # %then_block
	xorl	%eax, %eax
.LBB3_2:                                # %then_block
	addq	$216, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB3_30:                               # %then_block917
	movq	64(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_48:                               # %entry_ifend1468
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	128(%rsp), %eax
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movl	$13764, %esi            # imm = 0x35C4
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r12d, %ebx
	je	.LBB3_1
# BB#49:                                # %entry_ifend1512
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$40, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r13, %r9
	movq	%r13, %r12
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_50
# BB#51:                                # %entry_ifend1553
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movq	$0, 160(%rsp)
	movl	$0, gSigInt(%rip)
	movl	144(%rsp), %r13d
	movq	272(%rsp), %rax
	movq	%rax, (%rsp)
	movl	$64, %r8d
	movl	$13772, %r9d            # imm = 0x35CC
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%ebx, %edx
	movq	%r12, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#52:                                # %entry_ifend1598
	movq	(%rax), %rax
	movq	%rax, 56(%rsp)          # 8-byte Spill
	movl	$13780, %esi            # imm = 0x35D4
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#53:                                # %entry_ifend1601
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$84, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_50
# BB#54:                                # %entry_ifend1648
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 168(%rsp)
	movq	%r13, 168(%rsp)
	movl	$0, gSigInt(%rip)
	movl	160(%rsp), %r13d
	movl	$13788, %esi            # imm = 0x35DC
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#55:                                # %entry_ifend1692
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$86, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_50
# BB#56:                                # %entry_ifend1733
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	cmpl	$64, %r13d
	jne	.LBB3_61
# BB#57:                                # %entry_condend1777
	movl	$13836, %esi            # imm = 0x360C
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebx, %r13d
	je	.LBB3_1
# BB#58:                                # %entry_ifend1780
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$13868, %esi            # imm = 0x362C
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#59:                                # %entry_ifend1783
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_50
# BB#60:                                # %entry_ifend1827
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%r15)
	movl	%ebp, %edi
	movq	%r12, %rsi
	callq	entry_exception_object
	jmp	.LBB3_1
.LBB3_61:                               # %label_if_endzzzzzzzzzzzzzzzzzzzzzzze
	movl	$13960, %esi            # imm = 0x3688
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#62:                                # %entry_ifend1871
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	152(%rsp), %r13d
	movl	$13968, %esi            # imm = 0x3690
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#63:                                # %entry_ifend1875
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_50
# BB#64:                                # %entry_ifend1916
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 48(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	160(%rsp), %r13d
	movl	$13976, %esi            # imm = 0x3698
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#65:                                # %entry_ifend1960
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$86, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_50
# BB#66:                                # %entry_ifend2001
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$13984, %esi            # imm = 0x36A0
	movq	272(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#67:                                # %entry_ifend2044
	movq	72(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	80(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	88(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 96(%rbp)
	movq	%rcx, 96(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 104(%rbp)
	movq	%rcx, 104(%rbp)
	movq	184(%rsp), %rcx
	movq	$0, 112(%rbp)
	movq	%rcx, 112(%rbp)
	movq	192(%rsp), %rcx
	movq	$0, 120(%rbp)
	movq	%rcx, 120(%rbp)
	movq	200(%rsp), %rcx
	movq	$0, 128(%rbp)
	movq	%rcx, 128(%rbp)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB3_68
.LBB3_50:                               # %then_block1552
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_68:                               # %entry_ifend2091
	movq	(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	8(%r15), %rax
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	16(%r15), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	24(%r15), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	32(%r15), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	40(%r15), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	48(%r15), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	56(%r15), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	64(%r15), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	72(%r15), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	80(%r15), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	88(%r15), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	96(%r15), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	104(%r15), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	112(%r15), %rax
	movq	$0, 184(%rsp)
	movq	%rax, 184(%rsp)
	movq	120(%r15), %rax
	movq	$0, 192(%rsp)
	movq	%rax, 192(%rsp)
	movq	128(%r15), %rax
	movq	$0, 200(%rsp)
	movq	%rax, 200(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%r15)
	movl	$1, %eax
	jmp	.LBB3_2
.Lfunc_end3:
	.size	"Command.executeCommandWithGettingStderr(String,List,String)$$7", .Lfunc_end3-"Command.executeCommandWithGettingStderr(String,List,String)$$7"
	.cfi_endproc

	.globl	"Command.executeCommand(String,List,String)$$8"
	.align	16, 0x90
	.type	"Command.executeCommand(String,List,String)$$8",@function
"Command.executeCommand(String,List,String)$$8": # @"Command.executeCommand(String,List,String)$$8"
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
	subq	$168, %rsp
.Ltmp58:
	.cfi_def_cfa_offset 224
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
	movl	%r9d, %r12d
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, %rbx
	movq	%rsi, %rbp
	movq	224(%rsp), %rdi
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
	movq	$0, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$13992, %esi            # imm = 0x36A8
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#3:                                 # %entry_ifend
	leaq	32(%rbp), %rdx
	leaq	24(%rbp), %rcx
	movq	64(%rsp), %rsi
	movq	$0, (%rbp)
	movq	%rsi, (%rbp)
	movq	72(%rsp), %rsi
	movq	$0, 8(%rbp)
	movq	%rsi, 8(%rbp)
	movq	80(%rsp), %rsi
	movq	$0, 16(%rbp)
	movq	%rsi, 16(%rbp)
	movq	88(%rsp), %rsi
	movq	$0, 24(%rbp)
	movq	%rsi, 24(%rbp)
	movq	96(%rsp), %rsi
	movq	$0, 32(%rbp)
	movq	%rsi, 32(%rbp)
	movq	104(%rsp), %rsi
	movq	$0, 40(%rbp)
	movq	%rsi, 40(%rbp)
	movq	112(%rsp), %rsi
	movq	$0, 48(%rbp)
	movq	%rsi, 48(%rbp)
	movq	120(%rsp), %rsi
	movq	$0, 56(%rbp)
	movq	%rsi, 56(%rbp)
	movq	128(%rsp), %rsi
	movq	$0, 64(%rbp)
	movq	%rsi, 64(%rbp)
	movq	136(%rsp), %rsi
	movq	$0, 72(%rbp)
	movq	%rsi, 72(%rbp)
	movq	144(%rsp), %rsi
	movq	$0, 80(%rbp)
	movq	%rsi, 80(%rbp)
	movq	152(%rsp), %rsi
	movq	$0, 88(%rbp)
	movq	%rsi, 88(%rbp)
	movq	160(%rsp), %rsi
	movq	$0, 96(%rbp)
	movq	%rsi, 96(%rbp)
	movq	(%r14), %rsi
	movq	$0, (%rsi)
	movq	%rdx, (%rsi)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	addq	$8, (%r14)
	movl	$80, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_4
# BB#5:                                 # %entry_ifend36
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
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	$14000, %esi            # imm = 0x36B0
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#6:                                 # %entry_ifend69
	leaq	40(%rbp), %rcx
	leaq	48(%rbp), %rdx
	movq	64(%rsp), %rsi
	movq	$0, (%rbp)
	movq	%rsi, (%rbp)
	movq	72(%rsp), %rsi
	movq	$0, 8(%rbp)
	movq	%rsi, 8(%rbp)
	movq	80(%rsp), %rsi
	movq	$0, 16(%rbp)
	movq	%rsi, 16(%rbp)
	movq	88(%rsp), %rsi
	movq	$0, 24(%rbp)
	movq	%rsi, 24(%rbp)
	movq	96(%rsp), %rsi
	movq	$0, 32(%rbp)
	movq	%rsi, 32(%rbp)
	movq	104(%rsp), %rsi
	movq	$0, 40(%rbp)
	movq	%rsi, 40(%rbp)
	movq	112(%rsp), %rsi
	movq	$0, 48(%rbp)
	movq	%rsi, 48(%rbp)
	movq	120(%rsp), %rsi
	movq	$0, 56(%rbp)
	movq	%rsi, 56(%rbp)
	movq	128(%rsp), %rsi
	movq	$0, 64(%rbp)
	movq	%rsi, 64(%rbp)
	movq	136(%rsp), %rsi
	movq	$0, 72(%rbp)
	movq	%rsi, 72(%rbp)
	movq	144(%rsp), %rsi
	movq	$0, 80(%rbp)
	movq	%rsi, 80(%rbp)
	movq	152(%rsp), %rsi
	movq	$0, 88(%rbp)
	movq	%rsi, 88(%rbp)
	movq	160(%rsp), %rsi
	movq	$0, 96(%rbp)
	movq	%rsi, 96(%rbp)
	movq	(%r14), %rsi
	movq	$0, (%rsi)
	movq	%rdx, (%rsi)
	movq	(%r14), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r14)
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	addq	$8, (%r14)
	movl	$80, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %r13
	jne	.LBB4_7
# BB#8:                                 # %entry_ifend105
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
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movq	%r13, 32(%rsp)
	movl	$0, 24(%rsp)
	movl	$8, 16(%rsp)
	movl	$2, 8(%rsp)
	movl	$228, (%rsp)
	movl	$14008, %ecx            # imm = 0x36B8
	movl	$484, %r8d              # imm = 0x1E4
	movl	$14492, %r9d            # imm = 0x389C
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r12d, %ebx
	movq	%r13, 56(%rsp)          # 8-byte Spill
	movq	224(%rsp), %r12
	movq	%r12, %rdx
	callq	run_create_block_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$14720, %esi            # imm = 0x3980
	movq	%r12, %rdi
	movl	%ebx, %r12d
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#9:                                 # %entry_ifend140
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
	addq	$8, (%r14)
	movl	$81, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	56(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_4
# BB#10:                                # %entry_ifend173
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
	movq	$0, 120(%rsp)
	movq	%r13, 120(%rsp)
	movl	$0, gSigInt(%rip)
	movl	112(%rsp), %r13d
	movl	$14728, %esi            # imm = 0x3988
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#11:                                # %entry_ifend209
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
	addq	$8, (%r14)
	movl	$40, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_4
# BB#12:                                # %entry_ifend242
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
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %r13d
	movl	$14736, %esi            # imm = 0x3990
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#13:                                # %entry_ifend278
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
	addq	$8, (%r14)
	movl	$40, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB4_15
# BB#14:                                # %then_block310
	callq	get_try_catch_label_name
	jmp	.LBB4_1
.LBB4_15:                               # %entry_ifend311
	movq	%rdi, %rbx
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
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %r13d
	testl	%r13d, %r13d
	je	.LBB4_22
# BB#16:                                # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$14784, %esi            # imm = 0x39C0
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#17:                                # %entry_ifend348
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
	addq	$8, (%r14)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_4
# BB#18:                                # %entry_ifend381
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
	movq	$0, 128(%rsp)
	movq	%r13, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movl	104(%rsp), %eax
	movl	%eax, 52(%rsp)          # 4-byte Spill
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r12d, %edx
	movq	%rbx, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#19:                                # %entry_ifend419
	movq	(%rax), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movl	$14792, %esi            # imm = 0x39C8
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#20:                                # %entry_ifend422
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
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$42, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_4
# BB#21:                                # %entry_ifend461
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
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
.LBB4_22:                               # %label_if_endzzzzzzzzzzzzzzzzzzzzzzzh
	movl	$0, gSigInt(%rip)
	movl	104(%rsp), %r13d
	movl	$14880, %esi            # imm = 0x3A20
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#23:                                # %entry_ifend498
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
	addq	$8, (%r14)
	movl	$40, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_4
# BB#24:                                # %entry_ifend531
	leaq	72(%rbp), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
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
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.3, %edi
	xorl	%esi, %esi
	callq	create_buffer_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movq	$0, 128(%rsp)
	movl	%r13d, %eax
	movq	%rax, 128(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB4_25
.LBB4_40:                               # %entry_ifend764
                                        #   in Loop: Header=BB4_25 Depth=1
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
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
.LBB4_25:                               # %entry_condend566
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	movl	$14968, %esi            # imm = 0x3A78
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#26:                                # %entry_ifend569
                                        #   in Loop: Header=BB4_25 Depth=1
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$14976, %esi            # imm = 0x3A80
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#27:                                # %entry_ifend572
                                        #   in Loop: Header=BB4_25 Depth=1
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
	movq	$128, 8(%rcx)
	addq	$8, (%r14)
	movl	$2, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_28
# BB#29:                                # %entry_ifend608
                                        #   in Loop: Header=BB4_25 Depth=1
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
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 136(%rsp)
	movq	%rbx, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %r13d
	movl	$14984, %esi            # imm = 0x3A88
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	56(%rsp), %r9           # 8-byte Reload
	je	.LBB4_1
# BB#30:                                # %entry_ifend645
                                        #   in Loop: Header=BB4_25 Depth=1
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
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	$128, 8(%rcx)
	addq	$8, (%r14)
	movl	$41, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_4
# BB#31:                                # %entry_ifend684
                                        #   in Loop: Header=BB4_25 Depth=1
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
	movq	$0, 144(%rsp)
	movq	%r13, 144(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%r13d, %r13d
	je	.LBB4_32
# BB#38:                                # %label_if_endzzzzzzzzzzzzzzzzzzzzzzzj
                                        #   in Loop: Header=BB4_25 Depth=1
	movl	128(%rsp), %r13d
	movl	136(%rsp), %eax
	movl	%eax, 52(%rsp)          # 4-byte Spill
	movl	$15148, %esi            # imm = 0x3B2C
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	je	.LBB4_1
# BB#39:                                # %entry_ifend728
                                        #   in Loop: Header=BB4_25 Depth=1
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
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$4, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB4_40
.LBB4_4:                                # %then_block35
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB4_1
.LBB4_28:                               # %then_block607
	movq	56(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
	jmp	.LBB4_1
.LBB4_32:                               # %entry_condend721
	movl	$0, gSigInt(%rip)
	movl	96(%rsp), %r13d
	movl	$15236, %esi            # imm = 0x3B84
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	je	.LBB4_1
# BB#33:                                # %entry_ifend801
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
	addq	$8, (%r14)
	movl	$40, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r12d, %ecx
	movq	%r14, %r8
	movq	%r9, %r13
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB4_34
.LBB4_7:                                # %then_block104
	movq	%r13, %rdi
	callq	get_try_catch_label_name
.LBB4_1:                                # %then_block
	xorl	%eax, %eax
.LBB4_2:                                # %then_block
	addq	$168, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB4_34:                               # %entry_ifend834
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
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movq	$0, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movl	120(%rsp), %eax
	movl	%eax, 52(%rsp)          # 4-byte Spill
	movq	224(%rsp), %rax
	movq	%rax, (%rsp)
	movl	$64, %r8d
	movl	$15244, %r9d            # imm = 0x3B8C
	movq	%r14, %rdi
	movq	%r15, %rsi
	movl	%r12d, %ebx
	movl	%ebx, %edx
	movq	%r13, %r12
	movq	%r12, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#35:                                # %entry_ifend871
	movq	(%rax), %r13
	movl	$15252, %esi            # imm = 0x3B94
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#36:                                # %entry_ifend874
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
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r13d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$84, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_37
# BB#41:                                # %entry_ifend913
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
	movq	$0, 144(%rsp)
	movq	%r13, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movl	136(%rsp), %r13d
	movl	$15260, %esi            # imm = 0x3B9C
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#42:                                # %entry_ifend949
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
	addq	$8, (%r14)
	movl	$86, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_37
# BB#43:                                # %entry_ifend982
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
	movl	-8(%rax), %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	cmpl	$64, %r13d
	jne	.LBB4_48
# BB#44:                                # %entry_condend1018
	movl	$15308, %esi            # imm = 0x3BCC
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebx, %r13d
	je	.LBB4_1
# BB#45:                                # %entry_ifend1021
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.4, %edi
	callq	create_string_object
	movl	%eax, 52(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$15340, %esi            # imm = 0x3BEC
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#46:                                # %entry_ifend1024
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
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_37
# BB#47:                                # %entry_ifend1060
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
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%r15)
	movl	%ebp, %edi
	movq	%r12, %rsi
	callq	entry_exception_object
	jmp	.LBB4_1
.LBB4_48:                               # %label_if_endzzzzzzzzzzzzzzzzzzzzzzzk
	movl	$15432, %esi            # imm = 0x3C48
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#49:                                # %entry_ifend1096
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 52(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	128(%rsp), %r13d
	movl	$15440, %esi            # imm = 0x3C50
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#50:                                # %entry_ifend1100
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
	addq	$8, (%r14)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_37
# BB#51:                                # %entry_ifend1133
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
	movq	-8(%rax), %rdi
	movq	%rdi, 40(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	136(%rsp), %r13d
	movl	$15448, %esi            # imm = 0x3C58
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#52:                                # %entry_ifend1169
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
	addq	$8, (%r14)
	movl	$86, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB4_37
# BB#53:                                # %entry_ifend1202
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
	movl	$15456, %esi            # imm = 0x3C60
	movq	224(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#54:                                # %entry_ifend1237
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
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	40(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r15, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB4_55
.LBB4_37:                               # %then_block912
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB4_1
.LBB4_55:                               # %entry_ifend1276
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
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbp, (%r15)
	movl	$1, %eax
	jmp	.LBB4_2
.Lfunc_end4:
	.size	"Command.executeCommand(String,List,String)$$8", .Lfunc_end4-"Command.executeCommand(String,List,String)$$8"
	.cfi_endproc

	.globl	"Command.executeCommandWithControllingTerminal(String,List)$$9"
	.align	16, 0x90
	.type	"Command.executeCommandWithControllingTerminal(String,List)$$9",@function
"Command.executeCommandWithControllingTerminal(String,List)$$9": # @"Command.executeCommandWithControllingTerminal(String,List)$$9"
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
	subq	$136, %rsp
.Ltmp71:
	.cfi_def_cfa_offset 192
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
	movl	%r9d, 60(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, %rbp
	movq	%rsi, %r13
	movq	192(%rsp), %r12
	movq	(%r15), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r15), %rax
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movq	$0, 120(%rsp)
	movq	$0, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movq	%rbp, 32(%rsp)
	movl	$0, 24(%rsp)
	movl	$3, 16(%rsp)
	movl	$3, 8(%rsp)
	movl	$204, (%rsp)
	movl	$15464, %ecx            # imm = 0x3C68
	movl	$380, %r8d              # imm = 0x17C
	movl	$15844, %r9d            # imm = 0x3DE4
	movq	%r14, %rdi
	movq	%r15, %rsi
	movq	%r12, %rdx
	callq	run_create_block_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$16048, %esi            # imm = 0x3EB0
	movq	%r12, %rdi
	movq	%r15, %r12
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#3:                                 # %entry_ifend
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
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$81, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	60(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%ebx, %ecx
	movq	%rbp, %rdi
	movq	%r13, %rbx
	je	.LBB5_5
# BB#4:                                 # %then_block21
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_5:                                # %entry_ifend22
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
	movq	(%r14), %rax
	movl	%ecx, %r15d
	movq	%r14, %rbp
	movq	%rdi, %r14
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 80(%rsp)
	movq	%r13, 80(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$16056, %esi            # imm = 0x3EB8
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#6:                                 # %entry_ifend47
	movq	64(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rbx)
	movq	%rcx, 16(%rbx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rbx)
	movq	%rcx, 24(%rbx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rbx)
	movq	%rcx, 32(%rbx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rbx)
	movq	%rcx, 40(%rbx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rbx)
	movq	%rcx, 48(%rbx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rbx)
	movq	%rcx, 56(%rbx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rbx)
	movq	%rcx, 64(%rbx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rsi
	movq	%rsi, (%rbp)
	movq	$0, 8(%rcx)
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$94, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%r15d, %ecx
	movq	%rbp, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%r15d, %r13d
	movq	%r14, %r15
	je	.LBB5_8
# BB#7:                                 # %then_block74
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_8:                                # %entry_ifend75
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
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %r14d
	movl	$16064, %esi            # imm = 0x3EC0
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#9:                                 # %entry_ifend103
	movq	64(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rbx)
	movq	%rcx, 16(%rbx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rbx)
	movq	%rcx, 24(%rbx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rbx)
	movq	%rcx, 32(%rbx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rbx)
	movq	%rcx, 40(%rbx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rbx)
	movq	%rcx, 48(%rbx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rbx)
	movq	%rcx, 56(%rbx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rbx)
	movq	%rcx, 64(%rbx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$96, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%r13d, %ecx
	movq	%rbp, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r15, %r14
	movq	%rbx, %r15
	jne	.LBB5_10
# BB#11:                                # %entry_ifend131
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
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	movq	$0, 88(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %eax
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movq	192(%rsp), %rax
	movq	%rax, (%rsp)
	movl	$64, %r8d
	movl	$16072, %r9d            # imm = 0x3EC8
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	%r13d, %edx
	movq	%r14, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	movq	%r14, %r13
	movq	%r15, %rbx
	je	.LBB5_1
# BB#12:                                # %entry_ifend159
	movq	(%rax), %r15
	movl	$16080, %esi            # imm = 0x3ED0
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#13:                                # %entry_ifend162
	leaq	24(%rbx), %rcx
	movq	64(%rsp), %rdx
	movq	$0, (%rbx)
	movq	%rdx, (%rbx)
	movq	72(%rsp), %rdx
	movq	$0, 8(%rbx)
	movq	%rdx, 8(%rbx)
	movq	80(%rsp), %rdx
	movq	$0, 16(%rbx)
	movq	%rdx, 16(%rbx)
	movq	88(%rsp), %rdx
	movq	$0, 24(%rbx)
	movq	%rdx, 24(%rbx)
	movq	96(%rsp), %rdx
	movq	$0, 32(%rbx)
	movq	%rdx, 32(%rbx)
	movq	104(%rsp), %rdx
	movq	$0, 40(%rbx)
	movq	%rdx, 40(%rbx)
	movq	112(%rsp), %rdx
	movq	$0, 48(%rbx)
	movq	%rdx, 48(%rbx)
	movq	120(%rsp), %rdx
	movq	$0, 56(%rbx)
	movq	%rdx, 56(%rbx)
	movq	128(%rsp), %rdx
	movq	$0, 64(%rbx)
	movq	%rdx, 64(%rbx)
	movq	(%rbp), %rdx
	movq	$0, (%rdx)
	movl	56(%rsp), %esi          # 4-byte Reload
	movq	%rsi, (%rdx)
	movq	(%rbp), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%rbp)
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$84, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movq	%rbp, %r14
	movl	60(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %r15
	je	.LBB5_15
# BB#14:                                # %then_block192
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_15:                               # %entry_ifend193
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
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 96(%rsp)
	movq	%rbx, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %eax
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movl	$16088, %esi            # imm = 0x3ED8
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#16:                                # %entry_ifend221
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
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$86, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%ebp, %eax
	movq	%r13, %rdi
	je	.LBB5_18
# BB#17:                                # %then_block245
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_18:                               # %entry_ifend246
	movq	%r14, %r13
	movq	%rdi, %r14
	movl	%eax, %ebp
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
	movq	(%r13), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	cmpl	$64, %ebx
	jne	.LBB5_23
# BB#19:                                # %entry_condend
	movl	$16136, %esi            # imm = 0x3F08
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebp, %ecx
	movq	%r13, %rbx
	movq	%r15, %rbp
	je	.LBB5_1
# BB#20:                                # %entry_ifend273
	movq	%rax, %rdi
	movl	%ecx, %r15d
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.5, %edi
	callq	create_string_object
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$16168, %esi            # imm = 0x3F28
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	movl	%r15d, %r8d
	testq	%rax, %rax
	je	.LBB5_1
# BB#21:                                # %entry_ifend276
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
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%r8d, %ecx
	movq	%rbx, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rbp
	jne	.LBB5_10
# BB#22:                                # %entry_ifend304
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
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbx, (%r12)
	movl	%ebx, %edi
	movq	%r14, %rsi
	callq	entry_exception_object
	jmp	.LBB5_1
.LBB5_23:                               # %label_if_endzzzzzzzzzzzzzzzzzzzzzzzn
	movl	88(%rsp), %eax
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movl	$16260, %esi            # imm = 0x3F84
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#24:                                # %entry_ifend333
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
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$90, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebp, %ecx
	movq	%r13, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r14, %rdi
	je	.LBB5_26
# BB#25:                                # %then_block357
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_26:                               # %entry_ifend358
	movq	%rdi, %r14
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
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	testb	$1, %bl
	je	.LBB5_51
# BB#27:                                # %entry_condend385
	movl	88(%rsp), %ebx
	movl	$16304, %esi            # imm = 0x3FB0
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%r14, %r9
	je	.LBB5_1
# BB#28:                                # %entry_ifend389
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
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$91, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebp, %ecx
	movq	%r13, %r8
	movq	%r9, %r14
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB5_10
# BB#29:                                # %entry_ifend414
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
	movq	(%r13), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	subl	$-128, %ebx
	movq	$0, 104(%rsp)
	movq	%rbx, 104(%rsp)
	movl	$0, gSigInt(%rip)
	movl	64(%rsp), %eax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$16312, %esi            # imm = 0x3FB8
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#30:                                # %entry_ifend442
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$16320, %esi            # imm = 0x3FC0
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#31:                                # %entry_ifend445
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
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebp, %ecx
	movq	%r13, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB5_10
# BB#32:                                # %entry_ifend470
	movq	%r12, %rbx
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
	movq	%r13, %r12
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 120(%rsp)
	movq	%r13, 120(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$16328, %esi            # imm = 0x3FC8
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%r14, %r9
	je	.LBB5_1
# BB#33:                                # %entry_ifend498
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
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r12, %r8
	movq	%r12, %r14
	movq	%r9, %r12
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB5_34
# BB#35:                                # %entry_ifend526
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
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	$16336, %esi            # imm = 0x3FD0
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#36:                                # %entry_ifend553
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	112(%rsp), %eax
	movl	%eax, 40(%rsp)          # 4-byte Spill
	movl	80(%rsp), %eax
	movl	%eax, 44(%rsp)          # 4-byte Spill
	movl	120(%rsp), %eax
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movl	$16340, %esi            # imm = 0x3FD4
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#37:                                # %entry_ifend559
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
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	40(%rsp), %edx          # 4-byte Reload
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
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r14, %r13
	movq	%r12, %r9
	movq	%r12, %r14
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB5_10
# BB#38:                                # %entry_ifend593
	movq	%rbx, %r12
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
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 128(%rsp)
	movq	%rbx, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movq	192(%rsp), %rax
	movq	%rax, (%rsp)
	xorl	%r8d, %r8d
	movl	$16344, %r9d            # imm = 0x3FD8
	movq	%r13, %rdi
	movq	%r12, %rsi
	movl	%ebp, %edx
	movq	%r14, %rbx
	movq	%rbx, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#39:                                # %entry_ifend620
	movq	(%rax), %r14
	movl	128(%rsp), %eax
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movl	$16352, %esi            # imm = 0x3FE0
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#40:                                # %entry_ifend624
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
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebp, %ecx
	movq	%r13, %r8
	movq	%rbx, %r9
	movq	%rbx, %r14
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB5_10
# BB#41:                                # %entry_ifend652
	movq	%r12, %rbx
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
	movq	%r13, %r12
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, gSigInt(%rip)
	movl	$16368, %esi            # imm = 0x3FF0
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebp, %ecx
	movq	%r14, %r9
	je	.LBB5_1
# BB#42:                                # %entry_ifend679
	movq	64(%rsp), %rdx
	movq	$0, (%r15)
	movq	%rdx, (%r15)
	movq	72(%rsp), %rdx
	movq	$0, 8(%r15)
	movq	%rdx, 8(%r15)
	movq	80(%rsp), %rdx
	movq	$0, 16(%r15)
	movq	%rdx, 16(%r15)
	movq	88(%rsp), %rdx
	movq	$0, 24(%r15)
	movq	%rdx, 24(%r15)
	movq	96(%rsp), %rdx
	movq	$0, 32(%r15)
	movq	%rdx, 32(%r15)
	movq	104(%rsp), %rdx
	movq	$0, 40(%r15)
	movq	%rdx, 40(%r15)
	movq	112(%rsp), %rdx
	movq	$0, 48(%r15)
	movq	%rdx, 48(%r15)
	movq	120(%rsp), %rdx
	movq	$0, 56(%r15)
	movq	%rdx, 56(%r15)
	movq	128(%rsp), %rdx
	movq	$0, 64(%r15)
	movq	%rdx, 64(%r15)
	movq	%r15, %r13
	movl	$93, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%ecx, %r14d
	movq	%r12, %r8
	movq	%r12, %r15
	movq	%r9, %r12
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB5_43
.LBB5_34:                               # %then_block525
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_51:                               # %label_elsezzzzzzzzzzzzzzzzzzzzzzzo
	movl	$16480, %esi            # imm = 0x4060
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%ebp, %ecx
	movq	%r14, %r9
	je	.LBB5_1
# BB#52:                                # %entry_ifend846
	movq	64(%rsp), %rdx
	movq	$0, (%r15)
	movq	%rdx, (%r15)
	movq	72(%rsp), %rdx
	movq	$0, 8(%r15)
	movq	%rdx, 8(%r15)
	movq	80(%rsp), %rdx
	movq	$0, 16(%r15)
	movq	%rdx, 16(%r15)
	movq	88(%rsp), %rdx
	movq	$0, 24(%r15)
	movq	%rdx, 24(%r15)
	movq	96(%rsp), %rdx
	movq	$0, 32(%r15)
	movq	%rdx, 32(%r15)
	movq	104(%rsp), %rdx
	movq	$0, 40(%r15)
	movq	%rdx, 40(%r15)
	movq	112(%rsp), %rdx
	movq	$0, 48(%r15)
	movq	%rdx, 48(%r15)
	movq	120(%rsp), %rdx
	movq	$0, 56(%r15)
	movq	%rdx, 56(%r15)
	movq	128(%rsp), %rdx
	movq	$0, 64(%r15)
	movq	%rdx, 64(%r15)
	movl	$93, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ecx, %r14d
	movq	%r13, %r8
	movq	%r9, %rbp
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r13, %rbx
	je	.LBB5_54
# BB#53:                                # %then_block867
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_54:                               # %entry_ifend868
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
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$16488, %esi            # imm = 0x4068
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r14d, %r10d
	movq	%rbp, %r9
	movq	%rbx, %r8
	je	.LBB5_1
# BB#55:                                # %entry_ifend895
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
	movq	%r15, 48(%rsp)          # 8-byte Spill
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
	movq	%r12, %rdx
	movl	%r10d, %ecx
	movl	%r10d, %r14d
	movq	%r8, %r15
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB5_45
# BB#56:                                # %entry_ifend923
	movq	%r12, %rbp
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
	movq	%r15, %r13
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movl	$16496, %esi            # imm = 0x4070
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r14d, %r12d
	movq	%rbx, %r15
	movq	48(%rsp), %rbx          # 8-byte Reload
	je	.LBB5_1
# BB#57:                                # %entry_ifend950
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.7, %edi
	callq	create_string_object
	movl	%eax, 44(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	88(%rsp), %r14d
	movl	$16508, %esi            # imm = 0x407C
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#58:                                # %entry_ifend954
	movq	64(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	72(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	80(%rsp), %rcx
	movq	$0, 16(%rbx)
	movq	%rcx, 16(%rbx)
	movq	88(%rsp), %rcx
	movq	$0, 24(%rbx)
	movq	%rcx, 24(%rbx)
	movq	96(%rsp), %rcx
	movq	$0, 32(%rbx)
	movq	%rcx, 32(%rbx)
	movq	104(%rsp), %rcx
	movq	$0, 40(%rbx)
	movq	%rcx, 40(%rbx)
	movq	112(%rsp), %rcx
	movq	$0, 48(%rbx)
	movq	%rcx, 48(%rbx)
	movq	120(%rsp), %rcx
	movq	$0, 56(%rbx)
	movq	%rcx, 56(%rbx)
	movq	128(%rsp), %rcx
	movq	$0, 64(%rbx)
	movq	%rcx, 64(%rbx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$86, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	movq	%r15, %r14
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB5_59
.LBB5_10:                               # %then_block130
	movq	%r14, %rdi
	callq	get_try_catch_label_name
.LBB5_1:                                # %then_block
	xorl	%eax, %eax
.LBB5_2:                                # %then_block
	addq	$136, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB5_59:                               # %entry_ifend979
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
	movq	%r13, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$16516, %esi            # imm = 0x4084
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r12d, %r8d
	movq	%r14, %r9
	movq	48(%rsp), %rdx          # 8-byte Reload
	je	.LBB5_1
# BB#60:                                # %entry_ifend1006
	movq	64(%rsp), %rcx
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
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	%r15, 8(%rcx)
	addq	$8, (%rbx)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	%r8d, %ecx
	movq	%rbx, %r8
	movq	%rbx, %r14
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB5_45
# BB#61:                                # %entry_ifend1037
	movq	%rbp, %rbx
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
	movq	%r14, %rbp
.LBB5_50:                               # %entry_ifend818
	movq	(%rbp), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%r14, (%rbx)
	movl	$1, %eax
	jmp	.LBB5_2
.LBB5_43:                               # %entry_ifend701
	movq	%rbx, %rbp
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
	movq	%r15, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$16376, %esi            # imm = 0x3FF8
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r14d, %r8d
	movq	%r12, %r9
	je	.LBB5_1
# BB#44:                                # %entry_ifend728
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
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	%r15, 8(%rcx)
	addq	$8, (%rbx)
	movl	$96, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	%r8d, %ecx
	movq	%rbx, %r8
	movq	%rbx, %r15
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB5_45
# BB#46:                                # %entry_ifend756
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
	movq	%r15, %r12
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, gSigInt(%rip)
	movl	$16384, %esi            # imm = 0x4000
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#47:                                # %entry_ifend783
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.6, %edi
	callq	create_string_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movl	104(%rsp), %eax
	movl	%eax, 56(%rsp)          # 4-byte Spill
	movl	$16396, %esi            # imm = 0x400C
	movq	192(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#48:                                # %entry_ifend787
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
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
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
	movl	56(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	60(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB5_49
.LBB5_45:                               # %then_block755
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_49:                               # %entry_ifend818
	movq	%rbp, %rbx
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
	movq	%r12, %rbp
	jmp	.LBB5_50
.Lfunc_end5:
	.size	"Command.executeCommandWithControllingTerminal(String,List)$$9", .Lfunc_end5-"Command.executeCommandWithControllingTerminal(String,List)$$9"
	.cfi_endproc

	.globl	"Command.executeCommandWithControllingTerminalByPipe(String,List,String)$$10"
	.align	16, 0x90
	.type	"Command.executeCommandWithControllingTerminalByPipe(String,List,String)$$10",@function
"Command.executeCommandWithControllingTerminalByPipe(String,List,String)$$10": # @"Command.executeCommandWithControllingTerminalByPipe(String,List,String)$$10"
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
	subq	$184, %rsp
.Ltmp84:
	.cfi_def_cfa_offset 240
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
	movl	%r9d, %r14d
	movq	%r8, %r15
	movq	%rcx, %rbp
	movq	%rdx, %r12
	movq	%rsi, %rbx
	movq	240(%rsp), %rdi
	movq	(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	$0, 112(%rsp)
	movq	$0, 120(%rsp)
	movq	$0, 128(%rsp)
	movq	$0, 136(%rsp)
	movq	$0, 144(%rsp)
	movq	$0, 152(%rsp)
	movq	$0, 160(%rsp)
	movq	$0, 168(%rsp)
	movq	$0, 176(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 120(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$16632, %esi            # imm = 0x40F8
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#3:                                 # %entry_ifend
	leaq	32(%rbx), %rdx
	leaq	24(%rbx), %rcx
	movq	88(%rsp), %rsi
	movq	$0, (%rbx)
	movq	%rsi, (%rbx)
	movq	96(%rsp), %rsi
	movq	$0, 8(%rbx)
	movq	%rsi, 8(%rbx)
	movq	104(%rsp), %rsi
	movq	$0, 16(%rbx)
	movq	%rsi, 16(%rbx)
	movq	112(%rsp), %rsi
	movq	$0, 24(%rbx)
	movq	%rsi, 24(%rbx)
	movq	120(%rsp), %rsi
	movq	$0, 32(%rbx)
	movq	%rsi, 32(%rbx)
	movq	128(%rsp), %rsi
	movq	$0, 40(%rbx)
	movq	%rsi, 40(%rbx)
	movq	136(%rsp), %rsi
	movq	$0, 48(%rbx)
	movq	%rsi, 48(%rbx)
	movq	144(%rsp), %rsi
	movq	$0, 56(%rbx)
	movq	%rsi, 56(%rbx)
	movq	152(%rsp), %rsi
	movq	$0, 64(%rbx)
	movq	%rsi, 64(%rbx)
	movq	160(%rsp), %rsi
	movq	$0, 72(%rbx)
	movq	%rsi, 72(%rbx)
	movq	168(%rsp), %rsi
	movq	$0, 80(%rbx)
	movq	%rsi, 80(%rbx)
	movq	176(%rsp), %rsi
	movq	$0, 88(%rbx)
	movq	%rsi, 88(%rbx)
	movq	%rbx, 80(%rsp)          # 8-byte Spill
	movq	(%r15), %rsi
	movq	$0, (%rsi)
	movq	%rdx, (%rsi)
	movq	(%r15), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r15)
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	addq	$8, (%r15)
	movl	$80, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	%r14d, %ecx
	movq	%r15, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%r14d, %r13d
	movq	%r12, %r14
	movq	%r15, %rbx
	jne	.LBB6_4
# BB#5:                                 # %entry_ifend34
	movq	(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%rbp), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movq	%r14, 32(%rsp)
	movl	$0, 24(%rsp)
	movl	$6, 16(%rsp)
	movl	$3, 8(%rsp)
	movl	$228, (%rsp)
	movl	$16640, %ecx            # imm = 0x4100
	movl	$484, %r8d              # imm = 0x1E4
	movl	$17124, %r9d            # imm = 0x42E4
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movq	240(%rsp), %r15
	movq	%r15, %rdx
	callq	run_create_block_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$17352, %esi            # imm = 0x43C8
	movq	%r15, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r15
	movq	80(%rsp), %rbx          # 8-byte Reload
	je	.LBB6_1
# BB#6:                                 # %entry_ifend63
	movq	88(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	96(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	104(%rsp), %rcx
	movq	$0, 16(%rbx)
	movq	%rcx, 16(%rbx)
	movq	112(%rsp), %rcx
	movq	$0, 24(%rbx)
	movq	%rcx, 24(%rbx)
	movq	120(%rsp), %rcx
	movq	$0, 32(%rbx)
	movq	%rcx, 32(%rbx)
	movq	128(%rsp), %rcx
	movq	$0, 40(%rbx)
	movq	%rcx, 40(%rbx)
	movq	136(%rsp), %rcx
	movq	$0, 48(%rbx)
	movq	%rcx, 48(%rbx)
	movq	144(%rsp), %rcx
	movq	$0, 56(%rbx)
	movq	%rcx, 56(%rbx)
	movq	152(%rsp), %rcx
	movq	$0, 64(%rbx)
	movq	%rcx, 64(%rbx)
	movq	160(%rsp), %rcx
	movq	$0, 72(%rbx)
	movq	%rcx, 72(%rbx)
	movq	168(%rsp), %rcx
	movq	$0, 80(%rbx)
	movq	%rcx, 80(%rbx)
	movq	176(%rsp), %rcx
	movq	$0, 88(%rbx)
	movq	%rcx, 88(%rbx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$81, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	%r13d, %ecx
	movq	%r15, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r14, %rdi
	je	.LBB6_8
# BB#7:                                 # %then_block93
	callq	get_try_catch_label_name
	jmp	.LBB6_1
.LBB6_8:                                # %entry_ifend94
	movq	(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%rbp), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%r15), %rax
	movl	%r13d, %r14d
	movq	%rdi, 72(%rsp)          # 8-byte Spill
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	$0, 128(%rsp)
	movq	%r13, 128(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$17360, %esi            # imm = 0x43D0
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbp, %r12
	movq	%rbx, %rbp
	je	.LBB6_1
# BB#9:                                 # %entry_ifend129
	movq	88(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rsi
	movq	%rsi, (%r15)
	movq	$0, 8(%rcx)
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$94, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%r14d, %ecx
	movq	%r15, %r8
	movq	72(%rsp), %r13          # 8-byte Reload
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_10
# BB#11:                                # %entry_ifend163
	movq	(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%r12), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%r12), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$0, gSigInt(%rip)
	movl	128(%rsp), %eax
	movl	%eax, 64(%rsp)          # 4-byte Spill
	movl	$17368, %esi            # imm = 0x43D8
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#12:                                # %entry_ifend197
	movq	88(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	64(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$96, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%r14d, %ecx
	movq	%r15, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_10
# BB#13:                                # %entry_ifend231
	movq	(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%r12), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%r12), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$0, gSigInt(%rip)
	movl	120(%rsp), %eax
	movl	%eax, 64(%rsp)          # 4-byte Spill
	movl	$17376, %esi            # imm = 0x43E0
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#14:                                # %entry_ifend265
	movq	88(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	96(%rsp), %rcx
	movq	$0, 8(%rbp)
	movq	%rcx, 8(%rbp)
	movq	104(%rsp), %rcx
	movq	$0, 16(%rbp)
	movq	%rcx, 16(%rbp)
	movq	112(%rsp), %rcx
	movq	$0, 24(%rbp)
	movq	%rcx, 24(%rbp)
	movq	120(%rsp), %rcx
	movq	$0, 32(%rbp)
	movq	%rcx, 32(%rbp)
	movq	128(%rsp), %rcx
	movq	$0, 40(%rbp)
	movq	%rcx, 40(%rbp)
	movq	136(%rsp), %rcx
	movq	$0, 48(%rbp)
	movq	%rcx, 48(%rbp)
	movq	144(%rsp), %rcx
	movq	$0, 56(%rbp)
	movq	%rcx, 56(%rbp)
	movq	152(%rsp), %rcx
	movq	$0, 64(%rbp)
	movq	%rcx, 64(%rbp)
	movq	160(%rsp), %rcx
	movq	$0, 72(%rbp)
	movq	%rcx, 72(%rbp)
	movq	168(%rsp), %rcx
	movq	$0, 80(%rbp)
	movq	%rcx, 80(%rbp)
	movq	176(%rsp), %rcx
	movq	$0, 88(%rbp)
	movq	%rcx, 88(%rbp)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	64(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$40, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%r14d, %ecx
	movq	%r15, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r13, %rdi
	movq	%r15, %r13
	je	.LBB6_16
# BB#15:                                # %then_block295
	callq	get_try_catch_label_name
	jmp	.LBB6_1
.LBB6_16:                               # %entry_ifend296
	movq	%rbp, %r15
	movq	(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%r12), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%r12), %rax
	movq	%r12, %rbx
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movl	104(%rsp), %r12d
	testl	%r12d, %r12d
	je	.LBB6_25
# BB#17:                                # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$17424, %esi            # imm = 0x4410
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r14d, %r8d
	movq	72(%rsp), %rbp          # 8-byte Reload
	movq	%rbx, %r14
	je	.LBB6_1
# BB#18:                                # %entry_ifend331
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r8d, %ecx
	movl	%r8d, %ebx
	movq	%r13, %r8
	movq	%rbp, %r12
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movl	%ebx, %ecx
	movq	%r14, %rbx
	jne	.LBB6_19
# BB#20:                                # %entry_ifend362
	movq	(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbp
	movq	%rbp, 64(%rsp)          # 8-byte Spill
	movl	%ebp, %edi
	movl	%ecx, %r14d
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 136(%rsp)
	movq	%rbp, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movl	112(%rsp), %eax
	movl	%eax, 60(%rsp)          # 4-byte Spill
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%rbx, %r12
	je	.LBB6_1
# BB#21:                                # %entry_ifend398
	movq	(%rax), %rbx
	movl	$17432, %esi            # imm = 0x4418
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#22:                                # %entry_ifend401
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	64(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	%rbx, 8(%rcx)
	addq	$8, (%r13)
	movl	$42, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%r14d, %ecx
	movq	%r13, %r8
	movq	72(%rsp), %r9           # 8-byte Reload
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB6_24
# BB#23:                                # %then_block437
	movq	72(%rsp), %rdi          # 8-byte Reload
	callq	get_try_catch_label_name
	jmp	.LBB6_1
.LBB6_24:                               # %entry_ifend438
	movq	(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%r12), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%r12), %rax
	movq	%r12, %rbx
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
.LBB6_25:                               # %label_if_endzzzzzzzzzzzzzzzzzzzzzzzr
	movl	$0, gSigInt(%rip)
	movl	112(%rsp), %eax
	movl	%eax, 80(%rsp)          # 4-byte Spill
	movl	$17520, %esi            # imm = 0x4470
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	72(%rsp), %r12          # 8-byte Reload
	je	.LBB6_1
# BB#26:                                # %entry_ifend473
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	80(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$40, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r14d, %ecx
	movq	%r13, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r12, %rbp
	je	.LBB6_28
# BB#27:                                # %then_block503
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB6_1
.LBB6_28:                               # %entry_ifend504
	movq	(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movq	$0, 136(%rsp)
	movl	$0, gSigInt(%rip)
	movl	128(%rsp), %r12d
	movq	240(%rsp), %rax
	movq	%rax, (%rsp)
	movl	$64, %r8d
	movl	$17528, %r9d            # imm = 0x4478
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#29:                                # %entry_ifend539
	movq	(%rax), %rax
	movq	%rax, 80(%rsp)          # 8-byte Spill
	movl	$17536, %esi            # imm = 0x4480
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#30:                                # %entry_ifend542
	leaq	48(%r15), %rcx
	movq	88(%rsp), %rdx
	movq	$0, (%r15)
	movq	%rdx, (%r15)
	movq	96(%rsp), %rdx
	movq	$0, 8(%r15)
	movq	%rdx, 8(%r15)
	movq	104(%rsp), %rdx
	movq	$0, 16(%r15)
	movq	%rdx, 16(%r15)
	movq	112(%rsp), %rdx
	movq	$0, 24(%r15)
	movq	%rdx, 24(%r15)
	movq	120(%rsp), %rdx
	movq	$0, 32(%r15)
	movq	%rdx, 32(%r15)
	movq	128(%rsp), %rdx
	movq	$0, 40(%r15)
	movq	%rdx, 40(%r15)
	movq	136(%rsp), %rdx
	movq	$0, 48(%r15)
	movq	%rdx, 48(%r15)
	movq	144(%rsp), %rdx
	movq	$0, 56(%r15)
	movq	%rdx, 56(%r15)
	movq	152(%rsp), %rdx
	movq	$0, 64(%r15)
	movq	%rdx, 64(%r15)
	movq	160(%rsp), %rdx
	movq	$0, 72(%r15)
	movq	%rdx, 72(%r15)
	movq	168(%rsp), %rdx
	movq	$0, 80(%r15)
	movq	%rdx, 80(%r15)
	movq	176(%rsp), %rdx
	movq	$0, 88(%r15)
	movq	%rdx, 88(%r15)
	movq	(%r13), %rdx
	movq	$0, (%rdx)
	movl	%r12d, %esi
	movq	%rsi, (%rdx)
	movq	(%r13), %rdx
	leaq	8(%rdx), %rsi
	movq	%rsi, (%r13)
	movq	$0, 8(%rdx)
	movq	%rcx, 8(%rdx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	80(%rsp), %rdx          # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$84, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r14d, %ecx
	movl	%r14d, %r12d
	movq	%r13, %r8
	movq	%rbp, %r9
	movq	%rbp, %r14
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_4
# BB#31:                                # %entry_ifend579
	movq	(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 144(%rsp)
	movq	%rbp, 144(%rsp)
	movl	$0, gSigInt(%rip)
	movl	136(%rsp), %ebp
	movl	$17544, %esi            # imm = 0x4488
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r12d, %r8d
	movq	%r14, %r9
	je	.LBB6_1
# BB#32:                                # %entry_ifend613
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$86, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r8d, %ecx
	movl	%r8d, %r14d
	movq	%r13, %r8
	movq	%r13, %rbp
	movq	%r9, %r13
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_10
# BB#33:                                # %entry_ifend644
	movq	%rbx, %r12
	movq	(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%r12), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%r12), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	%rbp, %rbx
	movq	(%rbx), %rax
	movl	-8(%rax), %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	cmpl	$64, %ebp
	jne	.LBB6_38
# BB#34:                                # %entry_condend678
	movl	$17592, %esi            # imm = 0x44B8
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#35:                                # %entry_ifend681
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.9, %edi
	callq	create_string_object
	movl	%eax, 80(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$17624, %esi            # imm = 0x44D8
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#36:                                # %entry_ifend684
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	80(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%r14d, %ecx
	movq	%rbx, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_10
# BB#37:                                # %entry_ifend718
	movq	(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%r12), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%r12), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	%rbx, %r15
	movq	(%r15), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbx, (%r12)
	movl	%ebx, %edi
	movq	%r13, %rsi
	callq	entry_exception_object
	jmp	.LBB6_1
.LBB6_38:                               # %label_if_endzzzzzzzzzzzzzzzzzzzzzzzs
	movl	136(%rsp), %eax
	movl	%eax, 80(%rsp)          # 4-byte Spill
	movl	$17716, %esi            # imm = 0x4534
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r14d, %ebp
	movq	%rbx, %r8
	je	.LBB6_1
# BB#39:                                # %entry_ifend753
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	80(%rsp), %esi          # 4-byte Reload
	movq	%rsi, (%rcx)
	addq	$8, (%r8)
	movl	$90, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebp, %ecx
	movl	%ebp, 56(%rsp)          # 4-byte Spill
	movq	%r8, %rbp
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_10
# BB#40:                                # %entry_ifend784
	movq	%r12, 48(%rsp)          # 8-byte Spill
	movq	(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%r12), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%r12), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	%rbp, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbx, %r14
	movl	$0, gSigInt(%rip)
	testb	$1, %r12b
	je	.LBB6_64
# BB#41:                                # %entry_condend817
	movl	136(%rsp), %r12d
	movl	$17760, %esi            # imm = 0x4560
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	56(%rsp), %ebx          # 4-byte Reload
	movq	%r14, %r8
	movq	48(%rsp), %rdx          # 8-byte Reload
	je	.LBB6_1
# BB#42:                                # %entry_ifend821
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %esi
	movq	%rsi, (%rcx)
	addq	$8, (%r8)
	movl	$91, %esi
	movq	%rax, %rdi
	movq	%rdx, %rbp
	movl	%ebx, %ecx
	movq	%r8, %rbx
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_10
# BB#43:                                # %entry_ifend852
	movq	%rbp, %r12
	movq	(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%r12), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%r12), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	%rbx, %r14
	movq	(%r14), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	subl	$-128, %ebx
	movq	$0, 152(%rsp)
	movq	%rbx, 152(%rsp)
	movl	$0, gSigInt(%rip)
	movl	88(%rsp), %eax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$17768, %esi            # imm = 0x4568
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	56(%rsp), %ebp          # 4-byte Reload
	je	.LBB6_1
# BB#44:                                # %entry_ifend886
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$17776, %esi            # imm = 0x4570
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#45:                                # %entry_ifend889
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movq	%r12, %rbx
	movl	%ebp, %ecx
	movq	%r14, %r8
	movq	%r14, %r12
	movq	%r13, %r9
	movq	%r13, %r14
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_4
# BB#46:                                # %entry_ifend920
	movq	(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 168(%rsp)
	movq	%r13, 168(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$17784, %esi            # imm = 0x4578
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#47:                                # %entry_ifend954
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
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
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r12, %r8
	movq	%r12, %r13
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_4
# BB#48:                                # %entry_ifend988
	movq	%rbx, %r12
	movq	(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%r12), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%r12), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	%r13, %rbx
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$0, gSigInt(%rip)
	movl	$17792, %esi            # imm = 0x4580
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#49:                                # %entry_ifend1021
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	160(%rsp), %eax
	movl	%eax, 60(%rsp)          # 4-byte Spill
	movl	128(%rsp), %eax
	movl	%eax, 64(%rsp)          # 4-byte Spill
	movl	168(%rsp), %eax
	movl	%eax, 80(%rsp)          # 4-byte Spill
	movl	$17796, %esi            # imm = 0x4584
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#50:                                # %entry_ifend1027
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	60(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	64(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	80(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebp, %ecx
	movl	%ebp, %r13d
	movq	%rbx, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_4
# BB#51:                                # %entry_ifend1067
	movq	(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%r12), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%r12), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	%rbx, %rbp
	movq	(%rbp), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 176(%rsp)
	movq	%rbx, 176(%rsp)
	movl	$0, gSigInt(%rip)
	movq	240(%rsp), %rax
	movq	%rax, (%rsp)
	xorl	%r8d, %r8d
	movl	$17800, %r9d            # imm = 0x4588
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movl	%r13d, %edx
	movq	%r14, %rbx
	movq	%rbx, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#52:                                # %entry_ifend1100
	movq	(%rax), %r14
	movl	176(%rsp), %eax
	movl	%eax, 80(%rsp)          # 4-byte Spill
	movl	$17808, %esi            # imm = 0x4590
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#53:                                # %entry_ifend1104
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movl	80(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbp)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%r13d, %ecx
	movq	%rbp, %r8
	movq	%rbp, %r13
	movq	%rbx, %r9
	movq	%rbx, %r14
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_4
# BB#54:                                # %entry_ifend1138
	movq	(%r12), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r12), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r12), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r12), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r12), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r12), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r12), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r12), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%r12), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%r12), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%r12), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%r12), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movl	$0, gSigInt(%rip)
	movl	$17824, %esi            # imm = 0x45A0
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	56(%rsp), %r8d          # 4-byte Reload
	movq	%r14, %r9
	je	.LBB6_1
# BB#55:                                # %entry_ifend1171
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movl	$93, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movq	%r12, %rbp
	movl	%r8d, %ecx
	movl	%r8d, %r14d
	movq	%r13, %r8
	movq	%r9, %r12
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB6_56
.LBB6_19:                               # %then_block361
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB6_1
.LBB6_64:                               # %label_elsezzzzzzzzzzzzzzzzzzzzzzzt
	movl	$17936, %esi            # imm = 0x4610
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	56(%rsp), %ebx          # 4-byte Reload
	movq	%r13, %r9
	movq	%r14, %r8
	movq	48(%rsp), %rdx          # 8-byte Reload
	je	.LBB6_1
# BB#65:                                # %entry_ifend1374
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movl	$93, %esi
	movq	%rax, %rdi
	movq	%rdx, %rbp
	movl	%ebx, %ecx
	movl	%ebx, %r13d
	movq	%r8, %r12
	movq	%r9, %r14
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB6_66
.LBB6_4:                                # %then_block33
	movq	%r14, %rdi
	callq	get_try_catch_label_name
.LBB6_1:                                # %then_block
	xorl	%eax, %eax
.LBB6_2:                                # %then_block
	addq	$184, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB6_66:                               # %entry_ifend1402
	movq	%rbp, %rbx
	movq	(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 80(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$17944, %esi            # imm = 0x4618
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r13d, %ebp
	movq	%r14, %r13
	je	.LBB6_1
# BB#67:                                # %entry_ifend1435
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	80(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$96, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r12, %r8
	movq	%r12, %r14
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_10
# BB#68:                                # %entry_ifend1469
	movq	(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	%r14, %r12
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, gSigInt(%rip)
	movl	$17952, %esi            # imm = 0x4620
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#69:                                # %entry_ifend1502
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 80(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.11, %edi
	callq	create_string_object
	movl	%eax, 64(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	136(%rsp), %r14d
	movl	$17964, %esi            # imm = 0x462C
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#70:                                # %entry_ifend1506
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	movl	$86, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%ebp, %ecx
	movq	%r12, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_10
# BB#71:                                # %entry_ifend1537
	movq	%rbx, %rbp
	movq	(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%rbp), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	%r12, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$17972, %esi            # imm = 0x4634
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	56(%rsp), %r8d          # 4-byte Reload
	je	.LBB6_1
# BB#72:                                # %entry_ifend1570
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	80(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	64(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	addq	$8, (%rbx)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	%r8d, %ecx
	movq	%rbx, %r8
	movq	%rbx, %r14
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB6_73
.LBB6_10:                               # %then_block162
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB6_1
.LBB6_73:                               # %entry_ifend1607
	movq	%rbp, %rbx
	movq	(%rbx), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%rbx), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%rbx), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%rbx), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%rbx), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%rbx), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%rbx), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%rbx), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%rbx), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%rbx), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%rbx), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	%r14, %rbp
	movq	(%rbp), %rax
	movq	-8(%rax), %r14
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%r14, (%rbx)
	movl	$1, %eax
	jmp	.LBB6_2
.LBB6_56:                               # %entry_ifend1199
	movq	(%rbp), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%rbp), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%rbp), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%rbp), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%rbp), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%rbp), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%rbp), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%rbp), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%rbp), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%rbp), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%rbp), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	%r13, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$17832, %esi            # imm = 0x45A8
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r14d, %r8d
	movq	%r12, %r9
	je	.LBB6_1
# BB#57:                                # %entry_ifend1232
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%rbx)
	movl	$96, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	%r8d, %ecx
	movq	%rbx, %r8
	movq	%rbx, %r14
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB6_58
# BB#59:                                # %entry_ifend1266
	movq	%rbp, %r13
	movq	(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%r13), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%r13), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%r13), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%r13), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	$17840, %esi            # imm = 0x45B0
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %rbp
	je	.LBB6_1
# BB#60:                                # %entry_ifend1299
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$.Lglobal_string.10, %edi
	callq	create_string_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	152(%rsp), %eax
	movl	%eax, 80(%rsp)          # 4-byte Spill
	movl	$17852, %esi            # imm = 0x45BC
	movq	240(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#61:                                # %entry_ifend1303
	movq	88(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	96(%rsp), %rcx
	movq	$0, 8(%r15)
	movq	%rcx, 8(%r15)
	movq	104(%rsp), %rcx
	movq	$0, 16(%r15)
	movq	%rcx, 16(%r15)
	movq	112(%rsp), %rcx
	movq	$0, 24(%r15)
	movq	%rcx, 24(%r15)
	movq	120(%rsp), %rcx
	movq	$0, 32(%r15)
	movq	%rcx, 32(%r15)
	movq	128(%rsp), %rcx
	movq	$0, 40(%r15)
	movq	%rcx, 40(%r15)
	movq	136(%rsp), %rcx
	movq	$0, 48(%r15)
	movq	%rcx, 48(%r15)
	movq	144(%rsp), %rcx
	movq	$0, 56(%r15)
	movq	%rcx, 56(%r15)
	movq	152(%rsp), %rcx
	movq	$0, 64(%r15)
	movq	%rcx, 64(%r15)
	movq	160(%rsp), %rcx
	movq	$0, 72(%r15)
	movq	%rcx, 72(%r15)
	movq	168(%rsp), %rcx
	movq	$0, 80(%r15)
	movq	%rcx, 80(%r15)
	movq	176(%rsp), %rcx
	movq	$0, 88(%r15)
	movq	%rcx, 88(%r15)
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
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	80(%rsp), %edx          # 4-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	56(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	%rbp, %r9
	movq	%rbp, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB6_62
.LBB6_58:                               # %then_block1265
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB6_1
.LBB6_62:                               # %entry_ifend1340
	movq	(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	8(%r13), %rax
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	16(%r13), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	24(%r13), %rax
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	32(%r13), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 120(%rsp)
	movq	40(%r13), %rax
	movq	$0, 128(%rsp)
	movq	%rax, 128(%rsp)
	movq	48(%r13), %rax
	movq	$0, 136(%rsp)
	movq	%rax, 136(%rsp)
	movq	56(%r13), %rax
	movq	$0, 144(%rsp)
	movq	%rax, 144(%rsp)
	movq	64(%r13), %rax
	movq	$0, 152(%rsp)
	movq	%rax, 152(%rsp)
	movq	72(%r13), %rax
	movq	$0, 160(%rsp)
	movq	%rax, 160(%rsp)
	movq	80(%r13), %rax
	movq	$0, 168(%rsp)
	movq	%rax, 168(%rsp)
	movq	88(%r13), %rax
	movq	$0, 176(%rsp)
	movq	%rax, 176(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	%rbx, (%r13)
	movl	$1, %eax
	jmp	.LBB6_2
.Lfunc_end6:
	.size	"Command.executeCommandWithControllingTerminalByPipe(String,List,String)$$10", .Lfunc_end6-"Command.executeCommandWithControllingTerminalByPipe(String,List,String)$$10"
	.cfi_endproc

	.globl	"Command.toString()$$11"
	.align	16, 0x90
	.type	"Command.toString()$$11",@function
"Command.toString()$$11":               # @"Command.toString()$$11"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp91:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp92:
	.cfi_def_cfa_offset 32
.Ltmp93:
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
	je	.LBB7_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB7_2
.LBB7_1:                                # %then_block
	xorl	%eax, %eax
.LBB7_2:                                # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end7:
	.size	"Command.toString()$$11", .Lfunc_end7-"Command.toString()$$11"
	.cfi_endproc

	.globl	"Command.toBool()$$12"
	.align	16, 0x90
	.type	"Command.toBool()$$12",@function
"Command.toBool()$$12":                 # @"Command.toBool()$$12"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp94:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp95:
	.cfi_def_cfa_offset 32
.Ltmp96:
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
	je	.LBB8_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB8_2
.LBB8_1:                                # %then_block
	xorl	%eax, %eax
.LBB8_2:                                # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end8:
	.size	"Command.toBool()$$12", .Lfunc_end8-"Command.toBool()$$12"
	.cfi_endproc

	.globl	"Command.toBoolAndOutput()$$13"
	.align	16, 0x90
	.type	"Command.toBoolAndOutput()$$13",@function
"Command.toBoolAndOutput()$$13":        # @"Command.toBoolAndOutput()$$13"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp97:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp98:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp99:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp100:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp101:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp102:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp103:
	.cfi_def_cfa_offset 80
.Ltmp104:
	.cfi_offset %rbx, -56
.Ltmp105:
	.cfi_offset %r12, -48
.Ltmp106:
	.cfi_offset %r13, -40
.Ltmp107:
	.cfi_offset %r14, -32
.Ltmp108:
	.cfi_offset %r15, -24
.Ltmp109:
	.cfi_offset %rbp, -16
	movl	%r9d, %r14d
	movq	%r8, %rbp
	movq	%rcx, %r13
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	(%r13), %rbx
	movq	$0, 16(%rsp)
	movq	%rbx, 16(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %rdi
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$18060, %esi            # imm = 0x468C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_1
# BB#4:                                 # %entry_ifend3
	movq	$0, (%r12)
	movq	%rbx, (%r12)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movl	%edx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbp)
	movl	$18, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%r14d, %ecx
	movq	%rbp, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB9_6
# BB#5:                                 # %then_block8
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB9_1
.LBB9_6:                                # %entry_ifend9
	movq	(%r13), %rbx
	movq	$0, 16(%rsp)
	movq	%rbx, 16(%rsp)
	movq	(%rbp), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebx, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#7:                                 # %entry_ifend17
	movq	(%rax), %rax
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB9_2
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
.Lfunc_end9:
	.size	"Command.toBoolAndOutput()$$13", .Lfunc_end9-"Command.toBoolAndOutput()$$13"
	.cfi_endproc

	.globl	"Command.write(String,int)$$14"
	.align	16, 0x90
	.type	"Command.write(String,int)$$14",@function
"Command.write(String,int)$$14":        # @"Command.write(String,int)$$14"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp110:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp111:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp112:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp113:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp114:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp115:
	.cfi_def_cfa_offset 56
	subq	$104, %rsp
.Ltmp116:
	.cfi_def_cfa_offset 160
.Ltmp117:
	.cfi_offset %rbx, -56
.Ltmp118:
	.cfi_offset %r12, -48
.Ltmp119:
	.cfi_offset %r13, -40
.Ltmp120:
	.cfi_offset %r14, -32
.Ltmp121:
	.cfi_offset %r15, -24
.Ltmp122:
	.cfi_offset %rbp, -16
	movl	%r9d, 52(%rsp)          # 4-byte Spill
	movq	%r8, %r14
	movq	%rcx, %r13
	movq	%rdx, 56(%rsp)          # 8-byte Spill
	movq	%rsi, 40(%rsp)          # 8-byte Spill
	movq	160(%rsp), %rbx
	movq	(%r13), %rbp
	movq	$0, 64(%rsp)
	movq	%rbp, 64(%rsp)
	movq	8(%r13), %r15
	movq	$0, 72(%rsp)
	movq	%r15, 72(%rsp)
	movq	16(%r13), %r12
	movq	$0, 80(%rsp)
	movq	%r12, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$18068, %esi            # imm = 0x4694
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB10_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 32(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movq	%rbx, (%rsp)
	movl	$33, %r8d
	movl	$18076, %r9d            # imm = 0x469C
	movq	%r14, %rdi
	movq	%r13, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	56(%rsp), %rcx          # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#4:                                 # %entry_ifend6
	movq	(%rax), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	%rbx, (%rsp)
	movl	$39, %r8d
	movl	$18084, %r9d            # imm = 0x46A4
	movq	%r14, %rdi
	movq	%r13, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	56(%rsp), %rcx          # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#5:                                 # %entry_ifend9
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	%rbx, (%rsp)
	movl	$31, %r8d
	movl	$18092, %r9d            # imm = 0x46AC
	movq	%r14, %rdi
	movq	%r13, %rsi
	movl	52(%rsp), %edx          # 4-byte Reload
	movq	56(%rsp), %rcx          # 8-byte Reload
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#6:                                 # %entry_ifend12
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$18100, %esi            # imm = 0x46B4
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB10_1
# BB#7:                                 # %entry_ifend17
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	16(%rsp), %rdx          # 8-byte Reload
	orl	%ecx, %edx
	movq	8(%rsp), %rsi           # 8-byte Reload
	orl	%edx, %esi
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r15, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r12, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	$0, 32(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	32(%rsp), %edx          # 4-byte Reload
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
	movl	%esi, %edx
	movq	%rdx, 8(%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	52(%rsp), %ebx          # 4-byte Reload
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	56(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbp, %rdi
	je	.LBB10_9
# BB#8:                                 # %then_block39
	callq	get_try_catch_label_name
	jmp	.LBB10_1
.LBB10_9:                               # %entry_ifend40
	movq	(%r13), %r15
	movq	$0, 64(%rsp)
	movq	%r15, 64(%rsp)
	movq	8(%r13), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r13), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r13), %rax
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	%rdi, %rbp
	movq	%r13, %r12
	movq	32(%r12), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
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
	xorl	%r9d, %r9d
	movq	%r14, %rdi
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	movl	%r15d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	160(%rsp), %rdi
	je	.LBB10_1
# BB#10:                                # %entry_ifend56
	movq	(%rax), %rbp
	movl	$18108, %esi            # imm = 0x46BC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB10_1
# BB#11:                                # %entry_ifend59
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	$0, 8(%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	%r13, 24(%rcx)
	movq	$0, 32(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 32(%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$48, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebx, %ecx
	movq	%r14, %r8
	movq	56(%rsp), %r15          # 8-byte Reload
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB10_12
# BB#13:                                # %entry_ifend76
	movq	(%r12), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	8(%r12), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	16(%r12), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 80(%rsp)
	movq	%rax, 80(%rsp)
	movq	24(%r12), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 88(%rsp)
	movq	%rax, 88(%rsp)
	movq	32(%r12), %rax
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
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%r12, %rsi
	movl	%ebx, %edx
	movq	%r15, %rcx
	movl	%r13d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	%r14, %rbp
	movq	160(%rsp), %rdi
	je	.LBB10_1
# BB#14:                                # %entry_ifend98
	movq	(%rax), %r14
	movl	$18116, %esi            # imm = 0x46C4
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB10_1
# BB#15:                                # %entry_ifend101
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	16(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movq	%rdx, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, 24(%rcx)
	movq	$0, 32(%rcx)
	movq	%r13, 32(%rcx)
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%edx, %edx
	movq	%rdx, (%rcx)
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
	movq	%r14, 8(%rcx)
	addq	$8, (%rbp)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	%ebx, %ecx
	movq	%rbp, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB10_16
.LBB10_12:                              # %then_block75
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB10_1:                               # %then_block
	xorl	%eax, %eax
.LBB10_2:                               # %then_block
	addq	$104, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB10_16:                              # %entry_ifend124
	movq	%rbp, %r14
	movq	(%r12), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%r12, %rbx
	movq	8(%rbx), %r15
	movq	$0, 72(%rsp)
	movq	%r15, 72(%rsp)
	movq	16(%rbx), %r12
	movq	$0, 80(%rsp)
	movq	%r12, 80(%rsp)
	movq	24(%rbx), %rbp
	movq	$0, 88(%rsp)
	movq	%rbp, 88(%rsp)
	movq	32(%rbx), %r13
	movq	$0, 96(%rsp)
	movq	%r13, 96(%rsp)
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	$18124, %esi            # imm = 0x46CC
	movq	160(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB10_1
# BB#17:                                # %entry_ifend144
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r15, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%r12, 16(%rcx)
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
	movl	52(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	56(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbp, %rdi
	je	.LBB10_19
# BB#18:                                # %then_block160
	callq	get_try_catch_label_name
	jmp	.LBB10_1
.LBB10_19:                              # %entry_ifend161
	movq	(%rbx), %rbp
	movq	$0, 64(%rsp)
	movq	%rbp, 64(%rsp)
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
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB10_2
.Lfunc_end10:
	.size	"Command.write(String,int)$$14", .Lfunc_end10-"Command.write(String,int)$$14"
	.cfi_endproc

	.globl	"Command.write(String)$$15"
	.align	16, 0x90
	.type	"Command.write(String)$$15",@function
"Command.write(String)$$15":            # @"Command.write(String)$$15"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp123:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp124:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp125:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp126:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp127:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp128:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp129:
	.cfi_def_cfa_offset 80
.Ltmp130:
	.cfi_offset %rbx, -56
.Ltmp131:
	.cfi_offset %r12, -48
.Ltmp132:
	.cfi_offset %r13, -40
.Ltmp133:
	.cfi_offset %r14, -32
.Ltmp134:
	.cfi_offset %r15, -24
.Ltmp135:
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
	movl	$18132, %esi            # imm = 0x46D4
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB11_1
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
	movl	$14, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB11_5
# BB#4:                                 # %then_block15
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB11_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB11_2
.LBB11_5:                               # %entry_ifend16
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
.LBB11_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end11:
	.size	"Command.write(String)$$15", .Lfunc_end11-"Command.write(String)$$15"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"while_start_pointzzzzzzzzzzzzzzzzzzzzzzzb"
	.size	.Lglobal_string, 42

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.asciz	"Command not found"
	.size	.Lglobal_string.2, 18

	.type	.Lglobal_string.3,@object # @global_string.3
.Lglobal_string.3:
	.asciz	"while_start_pointzzzzzzzzzzzzzzzzzzzzzzzi"
	.size	.Lglobal_string.3, 42

	.type	.Lglobal_string.4,@object # @global_string.4
.Lglobal_string.4:
	.asciz	"Command not found"
	.size	.Lglobal_string.4, 18

	.type	.Lglobal_string.5,@object # @global_string.5
.Lglobal_string.5:
	.asciz	"Command not found"
	.size	.Lglobal_string.5, 18

	.type	.Lglobal_string.6,@object # @global_string.6
.Lglobal_string.6:
	.zero	1
	.size	.Lglobal_string.6, 1

	.type	.Lglobal_string.7,@object # @global_string.7
.Lglobal_string.7:
	.zero	1
	.size	.Lglobal_string.7, 1

	.type	.Lglobal_string.8,@object # @global_string.8
.Lglobal_string.8:
	.zero	1
	.size	.Lglobal_string.8, 1

	.type	.Lglobal_string.9,@object # @global_string.9
.Lglobal_string.9:
	.asciz	"Command not found"
	.size	.Lglobal_string.9, 18

	.type	.Lglobal_string.10,@object # @global_string.10
.Lglobal_string.10:
	.zero	1
	.size	.Lglobal_string.10, 1

	.type	.Lglobal_string.11,@object # @global_string.11
.Lglobal_string.11:
	.zero	1
	.size	.Lglobal_string.11, 1


	.section	".note.GNU-stack","",@progbits
