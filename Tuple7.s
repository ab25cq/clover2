	.text
	.file	"Tuple7.bc"
	.globl	"Tuple7.equals(Self)$$1"
	.align	16, 0x90
	.type	"Tuple7.equals(Self)$$1",@function
"Tuple7.equals(Self)$$1":               # @"Tuple7.equals(Self)$$1"
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
	movl	%r9d, %ebp
	movq	%r8, %r12
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %rbx
	movq	(%r14), %r8
	movq	$0, 8(%rsp)
	movq	%r8, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %r13
	movl	16(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#4:                                 # %entry_ifend5
	movq	128(%rsp), %r9
	movq	(%rax), %rax
	movq	8(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	16(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1220, %edi             # imm = 0x4C4
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r15, %r8
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#6:                                 # %entry_ifend16
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 24(%rsp)
	movq	%r13, 24(%rsp)
	testb	$1, %r13b
	je	.LBB0_36
# BB#7:                                 # %entry_condend
	movl	8(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#8:                                 # %entry_ifend26
	movq	(%rax), %r13
	movl	16(%rsp), %r8d
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#9:                                 # %entry_ifend30
	movq	(%rax), %rax
	movq	8(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	16(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1272, %edi             # imm = 0x4F8
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r15, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#10:                                # %entry_ifend44
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	testb	$1, %r13b
	je	.LBB0_35
# BB#11:                                # %entry_condend58
	movl	8(%rsp), %r8d
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#12:                                # %entry_ifend62
	movq	(%rax), %r13
	movl	16(%rsp), %r8d
	movl	$2, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#13:                                # %entry_ifend66
	movq	(%rax), %rax
	movq	8(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	16(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1324, %edi             # imm = 0x52C
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r15, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#14:                                # %entry_ifend80
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 40(%rsp)
	movq	%r13, 40(%rsp)
	testb	$1, %r13b
	je	.LBB0_34
# BB#15:                                # %entry_condend94
	movl	8(%rsp), %r8d
	movl	$3, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#16:                                # %entry_ifend98
	movq	(%rax), %r13
	movl	16(%rsp), %r8d
	movl	$3, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#17:                                # %entry_ifend102
	movq	(%rax), %rax
	movq	8(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	16(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1376, %edi             # imm = 0x560
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r15, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#18:                                # %entry_ifend116
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 48(%rsp)
	movq	%r13, 48(%rsp)
	testb	$1, %r13b
	je	.LBB0_33
# BB#19:                                # %entry_condend130
	movl	8(%rsp), %r8d
	movl	$4, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#20:                                # %entry_ifend134
	movq	(%rax), %r13
	movl	16(%rsp), %r8d
	movl	$4, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#21:                                # %entry_ifend138
	movq	(%rax), %rax
	movq	8(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	16(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1428, %edi             # imm = 0x594
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r15, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#22:                                # %entry_ifend152
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 56(%rsp)
	movq	%r13, 56(%rsp)
	testb	$1, %r13b
	je	.LBB0_32
# BB#23:                                # %entry_condend166
	movl	8(%rsp), %r8d
	movl	$5, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#24:                                # %entry_ifend170
	movq	(%rax), %r13
	movl	16(%rsp), %r8d
	movl	$5, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#25:                                # %entry_ifend174
	movq	(%rax), %rax
	movq	8(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	16(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1480, %edi             # imm = 0x5C8
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r15, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB0_5
# BB#26:                                # %entry_ifend188
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	testb	$1, %r13b
	je	.LBB0_31
# BB#27:                                # %entry_condend202
	movl	8(%rsp), %r8d
	movl	$6, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#28:                                # %entry_ifend206
	movq	(%rax), %r13
	movl	16(%rsp), %r8d
	movl	$6, %r9d
	movq	%r12, %rdi
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r15, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#29:                                # %entry_ifend210
	movq	(%rax), %rax
	movq	8(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	16(%rsp), %rcx
	movq	$0, 8(%rbx)
	movq	%rcx, 8(%rbx)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%eax, %eax
	movq	%rax, 8(%rcx)
	addq	$8, (%r12)
	movl	%r13d, (%rsp)
	movl	$1532, %edi             # imm = 0x5FC
	movq	%r14, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movq	%r15, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	je	.LBB0_30
.LBB0_5:                                # %then_block15
	movq	%r15, %rdi
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
.LBB0_30:                               # %entry_ifend224
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	andl	$1, %r13d
	movq	%r13, 64(%rsp)
.LBB0_31:                               # %label_and_endpointzzzzzzzzzzzzzzzo
	andl	$1, %r13d
	movq	%r13, 56(%rsp)
.LBB0_32:                               # %label_and_endpointzzzzzzzzzzzzzzzn
	andl	$1, %r13d
	movq	%r13, 48(%rsp)
.LBB0_33:                               # %label_and_endpointzzzzzzzzzzzzzzzm
	andl	$1, %r13d
	movq	%r13, 40(%rsp)
.LBB0_34:                               # %label_and_endpointzzzzzzzzzzzzzzzl
	andl	$1, %r13d
	movq	%r13, 32(%rsp)
.LBB0_35:                               # %label_and_endpointzzzzzzzzzzzzzzzk
	andl	$1, %r13d
	movq	%r13, 24(%rsp)
.LBB0_36:                               # %label_and_endpointzzzzzzzzzzzzzzzj
	movq	%r13, (%r14)
	movl	$1, %eax
	jmp	.LBB0_2
.Lfunc_end0:
	.size	"Tuple7.equals(Self)$$1", .Lfunc_end0-"Tuple7.equals(Self)$$1"
	.cfi_endproc

	.globl	"Tuple7.toString()$$2"
	.align	16, 0x90
	.type	"Tuple7.toString()$$2",@function
"Tuple7.toString()$$2":                 # @"Tuple7.toString()$$2"
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
	subq	$72, %rsp
.Ltmp19:
	.cfi_def_cfa_offset 128
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
	movq	%r8, %rbx
	movq	%rcx, %rbp
	movq	%rbp, 56(%rsp)          # 8-byte Spill
	movq	%rdx, %r12
	movq	%rsi, %r15
	movq	(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	64(%rsp), %r8d
	xorl	%r9d, %r9d
	movq	%rbx, %rdi
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	128(%rsp), %r9
	movq	(%rax), %rax
	movq	64(%rsp), %rcx
	movq	$0, (%r15)
	movq	%rcx, (%r15)
	movq	%rbx, %rcx
	movq	(%rcx), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%rcx)
	movl	%eax, (%rsp)
	movl	$1772, %edi             # imm = 0x6EC
	movq	56(%rsp), %rsi          # 8-byte Reload
	movl	%r14d, %edx
	movq	%r12, %r8
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%r15, %rbp
	movq	%r12, %rdi
	je	.LBB1_5
# BB#4:                                 # %then_block5
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_5:                                # %entry_ifend6
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%rbx, %r12
	movq	(%r12), %rax
	movq	%rdi, 48(%rsp)          # 8-byte Spill
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$1784, %esi             # imm = 0x6F8
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movl	%r14d, %ebx
	je	.LBB1_1
# BB#6:                                 # %entry_ifend13
	movq	64(%rsp), %rcx
	movq	$0, (%rbp)
	movq	%rcx, (%rbp)
	movq	%rbp, 40(%rsp)          # 8-byte Spill
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	%r15, 8(%rcx)
	addq	$8, (%r12)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%ebx, %ecx
	movq	%r12, %r8
	movq	48(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbp, %r14
	je	.LBB1_8
# BB#7:                                 # %then_block24
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_8:                                # %entry_ifend25
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%r12), %rax
	movl	%ebx, 36(%rsp)          # 4-byte Spill
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	%r12, %r15
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1796, %esi             # imm = 0x704
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	40(%rsp), %r12          # 8-byte Reload
	movq	%r14, %rbx
	je	.LBB1_1
# BB#9:                                 # %entry_ifend36
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	%r15, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	36(%rsp), %r15d         # 4-byte Reload
	movl	%r15d, %ecx
	movq	%r8, %r13
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_10
# BB#11:                                # %entry_ifend48
	movq	56(%rsp), %r14          # 8-byte Reload
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%r13, %rbp
	movq	(%rbp), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 24(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	64(%rsp), %r8d
	movl	$1, %r9d
	movq	%rbp, %rdi
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#12:                                # %entry_ifend60
	movq	(%rax), %rax
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	%rbp, %rcx
	movq	(%rcx), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%rcx)
	movl	%eax, (%rsp)
	movl	$1804, %edi             # imm = 0x70C
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%rbx, %r8
	movq	128(%rsp), %r13
	movq	%r13, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB1_14
# BB#13:                                # %then_block68
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_14:                               # %entry_ifend69
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	%r12, %rbx
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%r13, %rdi
	movq	%rbp, %r13
	movl	$1816, %esi             # imm = 0x718
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#15:                                # %entry_ifend80
	movq	64(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	%r13, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r15d, %ecx
	movq	%r8, %rbp
	movq	48(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_10
# BB#16:                                # %entry_ifend92
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbp, %r15
	movl	$.Lglobal_string.3, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1828, %esi             # imm = 0x724
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	40(%rsp), %r12          # 8-byte Reload
	je	.LBB1_1
# BB#17:                                # %entry_ifend103
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	%r15, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r13, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%ebp, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	36(%rsp), %r15d         # 4-byte Reload
	movl	%r15d, %ecx
	movq	%r8, %r13
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_10
# BB#18:                                # %entry_ifend115
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%r13, %rbp
	movq	(%rbp), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 24(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	64(%rsp), %r8d
	movl	$2, %r9d
	movq	%rbp, %rdi
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#19:                                # %entry_ifend127
	movq	(%rax), %rax
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	%rbp, %rcx
	movq	(%rcx), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%rcx)
	movl	%eax, (%rsp)
	movl	$1836, %edi             # imm = 0x72C
	movq	%r14, %rsi
	movl	%r15d, %edx
	movq	%rbx, %r8
	movq	128(%rsp), %r13
	movq	%r13, %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB1_21
# BB#20:                                # %then_block135
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_21:                               # %entry_ifend136
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	%r12, %rbx
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%r13, %rdi
	movq	%rbp, %r13
	movl	$1848, %esi             # imm = 0x738
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#22:                                # %entry_ifend147
	movq	64(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	%r13, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	24(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r15d, %ecx
	movq	%r8, %rbp
	movq	48(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_10
# BB#23:                                # %entry_ifend159
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%rbp, 16(%rsp)          # 8-byte Spill
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$.Lglobal_string.4, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1860, %esi             # imm = 0x744
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	40(%rsp), %r12          # 8-byte Reload
	movq	%rbx, %r9
	je	.LBB1_1
# BB#24:                                # %entry_ifend170
	movq	64(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	16(%rsp), %r8           # 8-byte Reload
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	%r13, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movl	%ebp, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r15d, %ecx
	movl	%r15d, %r13d
	movq	%r8, %rbx
	movq	%r9, %r15
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_25
# BB#26:                                # %entry_ifend182
	movq	%r14, %rbp
	movq	(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%rbx, %r14
	movq	(%r14), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 24(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	64(%rsp), %r8d
	movl	$3, %r9d
	movq	%r14, %rdi
	movq	%rbp, %rsi
	movl	%r13d, %edx
	movq	%r15, %rbx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#27:                                # %entry_ifend194
	movq	(%rax), %rax
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	%r14, %rcx
	movq	(%rcx), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%rcx)
	movl	%eax, (%rsp)
	movl	$1868, %edi             # imm = 0x74C
	movq	56(%rsp), %rsi          # 8-byte Reload
	movl	%r13d, %edx
	movl	%r13d, %r14d
	movq	%rcx, %rbp
	movq	%rbx, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB1_10
# BB#28:                                # %entry_ifend203
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbp, %r15
	movl	$1880, %esi             # imm = 0x758
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	movl	%r14d, %ecx
	je	.LBB1_1
# BB#29:                                # %entry_ifend214
	movq	64(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	%r15, %r8
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	24(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movq	%r13, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%ecx, %r15d
	movq	%r8, %rbp
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_10
# BB#30:                                # %entry_ifend226
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$.Lglobal_string.5, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1892, %esi             # imm = 0x764
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	je	.LBB1_1
# BB#31:                                # %entry_ifend237
	movq	64(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	16(%rsp), %r8           # 8-byte Reload
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	%r13, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movl	%ebp, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%r15d, %ecx
	movl	%r15d, %r14d
	movq	%r8, %rbx
	movq	%r9, %r15
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_25
# BB#32:                                # %entry_ifend249
	movq	56(%rsp), %rbp          # 8-byte Reload
	movq	(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 24(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	64(%rsp), %r8d
	movl	$4, %r9d
	movq	%rbx, %rdi
	movq	%rbx, %r13
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rbx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#33:                                # %entry_ifend261
	movq	(%rax), %rax
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	%r13, %rcx
	movq	(%rcx), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%rcx)
	movl	%eax, (%rsp)
	movl	$1900, %edi             # imm = 0x76C
	movq	56(%rsp), %rsi          # 8-byte Reload
	movl	%r14d, %edx
	movq	%rcx, %rbp
	movq	%rbx, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB1_10
# BB#34:                                # %entry_ifend270
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbp, %r15
	movl	$1912, %esi             # imm = 0x778
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	je	.LBB1_1
# BB#35:                                # %entry_ifend281
	movq	64(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	%r15, %r8
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	24(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movq	%r13, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%r14d, %ecx
	movq	%r8, %rbp
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_10
# BB#36:                                # %entry_ifend293
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$.Lglobal_string.6, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1924, %esi             # imm = 0x784
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	je	.LBB1_1
# BB#37:                                # %entry_ifend304
	movq	64(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	16(%rsp), %r8           # 8-byte Reload
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	%r13, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movl	%ebp, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%r14d, %ecx
	movq	%r8, %rbx
	movq	%r9, %r15
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_25
# BB#38:                                # %entry_ifend316
	movq	56(%rsp), %rbp          # 8-byte Reload
	movq	(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 24(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	64(%rsp), %r8d
	movl	$5, %r9d
	movq	%rbx, %rdi
	movq	%rbx, %r13
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rbx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#39:                                # %entry_ifend328
	movq	(%rax), %rax
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	%r13, %rcx
	movq	(%rcx), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%rcx)
	movl	%eax, (%rsp)
	movl	$1932, %edi             # imm = 0x78C
	movq	56(%rsp), %rsi          # 8-byte Reload
	movl	%r14d, %edx
	movq	%rcx, %rbp
	movq	%rbx, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB1_10
# BB#40:                                # %entry_ifend337
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbp, %r15
	movl	$1944, %esi             # imm = 0x798
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	je	.LBB1_1
# BB#41:                                # %entry_ifend348
	movq	64(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	%r15, %r8
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	24(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movq	%r13, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%r14d, %ecx
	movq	%r8, %rbp
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_10
# BB#42:                                # %entry_ifend360
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$.Lglobal_string.7, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1956, %esi             # imm = 0x7A4
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	je	.LBB1_1
# BB#43:                                # %entry_ifend371
	movq	64(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	16(%rsp), %r8           # 8-byte Reload
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	%r13, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movl	%ebp, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%r14d, %ecx
	movq	%r8, %rbx
	movq	%r9, %r15
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_44
.LBB1_25:                               # %then_block181
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_44:                               # %entry_ifend383
	movq	56(%rsp), %rbp          # 8-byte Reload
	movq	(%rbp), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 24(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	64(%rsp), %r8d
	movl	$6, %r9d
	movq	%rbx, %rdi
	movq	%rbx, %r13
	movq	%rbp, %rsi
	movl	%r14d, %edx
	movq	%r15, %rbx
	movq	%rbx, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#45:                                # %entry_ifend395
	movq	(%rax), %rax
	movq	64(%rsp), %rcx
	movq	$0, (%r12)
	movq	%rcx, (%r12)
	movq	%r13, %rcx
	movq	(%rcx), %rsi
	movq	$0, (%rsi)
	movl	%eax, %edx
	movq	%rdx, (%rsi)
	addq	$8, (%rcx)
	movl	%eax, (%rsp)
	movl	$1964, %edi             # imm = 0x7AC
	movq	56(%rsp), %rsi          # 8-byte Reload
	movl	%r14d, %edx
	movq	%rcx, %rbp
	movq	%rbx, %r8
	movq	128(%rsp), %r9
	callq	call_invoke_virtual_method
	cmpl	$1, %eax
	jne	.LBB1_10
# BB#46:                                # %entry_ifend404
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%rbp, %r15
	movl	$1976, %esi             # imm = 0x7B8
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	je	.LBB1_1
# BB#47:                                # %entry_ifend415
	movq	64(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	%r15, %r8
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	24(%rsp), %rsi          # 8-byte Reload
	movq	%rsi, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movq	%r13, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%r14d, %ecx
	movq	%r8, %rbp
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB1_10
# BB#48:                                # %entry_ifend427
	movq	56(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$.Lglobal_string.8, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1988, %esi             # imm = 0x7C4
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	%rbx, %r9
	je	.LBB1_1
# BB#49:                                # %entry_ifend438
	movq	64(%rsp), %rdx
	movq	$0, (%r12)
	movq	%rdx, (%r12)
	movq	16(%rsp), %r8           # 8-byte Reload
	movq	(%r8), %rdx
	movq	$0, (%rdx)
	movq	%r13, (%rdx)
	movq	(%r8), %rsi
	leaq	8(%rsi), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rsi)
	movl	%ebp, %edx
	movq	%rdx, 8(%rsi)
	addq	$8, (%r8)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	56(%rsp), %rdx          # 8-byte Reload
	movl	%r14d, %ecx
	movq	%r8, %rbp
	movq	%r9, %rbx
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_50
.LBB1_10:                               # %then_block47
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB1_1:                                # %then_block
	xorl	%eax, %eax
.LBB1_2:                                # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB1_50:                               # %entry_ifend450
	movq	56(%rsp), %r14          # 8-byte Reload
	movq	(%r14), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	%rbp, %rbx
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	%rbp, (%r14)
	movl	$1, %eax
	jmp	.LBB1_2
.Lfunc_end1:
	.size	"Tuple7.toString()$$2", .Lfunc_end1-"Tuple7.toString()$$2"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"tuple {"
	.size	.Lglobal_string, 8

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.asciz	","
	.size	.Lglobal_string.2, 2

	.type	.Lglobal_string.3,@object # @global_string.3
.Lglobal_string.3:
	.asciz	","
	.size	.Lglobal_string.3, 2

	.type	.Lglobal_string.4,@object # @global_string.4
.Lglobal_string.4:
	.asciz	","
	.size	.Lglobal_string.4, 2

	.type	.Lglobal_string.5,@object # @global_string.5
.Lglobal_string.5:
	.asciz	","
	.size	.Lglobal_string.5, 2

	.type	.Lglobal_string.6,@object # @global_string.6
.Lglobal_string.6:
	.asciz	","
	.size	.Lglobal_string.6, 2

	.type	.Lglobal_string.7,@object # @global_string.7
.Lglobal_string.7:
	.asciz	","
	.size	.Lglobal_string.7, 2

	.type	.Lglobal_string.8,@object # @global_string.8
.Lglobal_string.8:
	.asciz	"}"
	.size	.Lglobal_string.8, 2


	.section	".note.GNU-stack","",@progbits
