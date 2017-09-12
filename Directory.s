	.text
	.file	"Directory.bc"
	.globl	"Directory.readdir()$$2"
	.align	16, 0x90
	.type	"Directory.readdir()$$2",@function
"Directory.readdir()$$2":               # @"Directory.readdir()$$2"
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
	movl	%r9d, %r13d
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %r15
	movq	%rsi, %r12
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
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %rcx
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	testq	%rax, %rax
	je	.LBB0_4
# BB#9:                                 # %label_if_endzzzzzzzzzzzzzzzzzzzzzo
	movl	$1, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#10:                                # %entry_ifend24
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$1116, %esi             # imm = 0x45C
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#11:                                # %entry_ifend27
	movq	$0, (%r12)
	movq	%rbp, (%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$52, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB0_7
# BB#12:                                # %entry_ifend36
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
	jmp	.LBB0_2
.LBB0_4:                                # %entry_condend
	movl	$988, %esi              # imm = 0x3DC
	movq	%rcx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#5:                                 # %entry_ifend3
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, 8(%rsp)           # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, 4(%rsp)           # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	$1032, %esi             # imm = 0x408
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#6:                                 # %entry_ifend6
	movq	$0, (%r12)
	movq	%rbp, (%r12)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	8(%rsp), %edx           # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movl	4(%rsp), %edx           # 4-byte Reload
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
	je	.LBB0_8
.LBB0_7:                                # %then_block14
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB0_1
.LBB0_8:                                # %entry_ifend15
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
	.size	"Directory.readdir()$$2", .Lfunc_end0-"Directory.readdir()$$2"
	.cfi_endproc

	.globl	"Directory.closedir()$$3"
	.align	16, 0x90
	.type	"Directory.closedir()$$3",@function
"Directory.closedir()$$3":              # @"Directory.closedir()$$3"
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
	movq	%r8, %r13
	movq	%rcx, %rbx
	movq	%rdx, %r15
	movq	%rsi, %r12
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.LBB1_9
# BB#4:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r13, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r15, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#5:                                 # %entry_ifend4
	movq	80(%rsp), %rdi
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movl	$1160, %esi             # imm = 0x488
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#6:                                 # %entry_ifend7
	movq	$0, (%r12)
	movq	%rbp, (%r12)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movq	8(%rsp), %rdx           # 8-byte Reload
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$53, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r14d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_8
# BB#7:                                 # %then_block12
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB1_1
.LBB1_8:                                # %entry_ifend13
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
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
	je	.LBB1_1
.LBB1_9:                                # %label_if_endzzzzzzzzzzzzzzzzzzzzzp
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
	.size	"Directory.closedir()$$3", .Lfunc_end1-"Directory.closedir()$$3"
	.cfi_endproc

	.globl	"Directory.entries(String)$$4"
	.align	16, 0x90
	.type	"Directory.entries(String)$$4",@function
"Directory.entries(String)$$4":         # @"Directory.entries(String)$$4"
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
	subq	$88, %rsp
.Ltmp32:
	.cfi_def_cfa_offset 144
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
	movq	%r8, %r14
	movq	%rdx, 24(%rsp)          # 8-byte Spill
	movq	%rsi, %r13
	movq	144(%rsp), %rbp
	movq	(%rcx), %rax
	movq	%rcx, %r12
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	$0, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movq	$0, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1240, %esi             # imm = 0x4D8
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
	movl	40(%rsp), %r15d
	movl	$1252, %esi             # imm = 0x4E4
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#4:                                 # %entry_ifend3
	movq	40(%rsp), %rcx
	movq	%r13, %rbp
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
	movq	%r14, %r13
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r12, %rbx
	movq	%rbx, %rdx
	movl	36(%rsp), %r15d         # 4-byte Reload
	movl	%r15d, %ecx
	movq	%r13, %r8
	movq	24(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_5
# BB#6:                                 # %entry_ifend20
	movq	%rbp, %r12
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
	movq	%rbx, %r14
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, 48(%rsp)
	movq	%rbx, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1264, %esi             # imm = 0x4F0
	movq	144(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#7:                                 # %entry_ifend34
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$1280, %esi             # imm = 0x500
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#8:                                 # %entry_ifend37
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
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r14, %rbx
	movq	%rbx, %rdx
	movl	%r15d, %ecx
	movq	%r13, %r8
	movq	24(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_9
# BB#10:                                # %entry_ifend54
	movq	%r12, %r15
	movq	%r15, 16(%rsp)          # 8-byte Spill
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
	movq	%rbx, %r12
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	(%r13), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%r13, %r14
	movq	$0, 56(%rsp)
	movq	%rbx, 56(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB2_11
.LBB2_35:                               # %entry_ifend319
                                        #   in Loop: Header=BB2_11 Depth=1
	movq	%rbx, %r15
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
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	%r13, %r14
.LBB2_11:                               # %entry_condend
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB2_12 Depth 2
	movq	144(%rsp), %rdi
.LBB2_12:                               # %entry_condend
                                        #   Parent Loop BB2_11 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %ebx
	movl	$1372, %esi             # imm = 0x55C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#13:                                # %entry_ifend74
                                        #   in Loop: Header=BB2_12 Depth=2
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
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$2, %esi
	movq	%rax, %rdi
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	24(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_9
# BB#14:                                # %entry_ifend91
                                        #   in Loop: Header=BB2_12 Depth=2
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
	movq	%r12, %rbp
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	(%r14), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%r13d, %r13d
	je	.LBB2_15
# BB#18:                                # %label_if_endzzzzzzzzzzzzzzzzzzzzzr
                                        #   in Loop: Header=BB2_12 Depth=2
	movl	$.Lglobal_string.2, %edi
	callq	create_string_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$1532, %esi             # imm = 0x5FC
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#19:                                # %entry_ifend117
                                        #   in Loop: Header=BB2_12 Depth=2
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
	movq	%r14, %rbx
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbx), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbx)
	movq	$0, 8(%rcx)
	movl	%r12d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$14, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	24(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_5
# BB#20:                                # %entry_ifend137
                                        #   in Loop: Header=BB2_12 Depth=2
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
	movq	(%rbx), %rax
	movl	-8(%rax), %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	testl	%r14d, %r14d
	sete	%al
	movq	$0, 80(%rsp)
	movzbl	%al, %eax
	movq	%rax, 80(%rsp)
	jne	.LBB2_24
# BB#21:                                # %entry_condend156
                                        #   in Loop: Header=BB2_12 Depth=2
	movl	64(%rsp), %r14d
	movl	$.Lglobal_string.3, %edi
	callq	create_string_object
	movl	%eax, %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	movl	$1588, %esi             # imm = 0x634
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#22:                                # %entry_ifend160
                                        #   in Loop: Header=BB2_12 Depth=2
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
	addq	$8, (%rbx)
	movl	$14, %esi
	movq	%rax, %rdi
	movq	%rbp, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	24(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_5
# BB#23:                                # %entry_ifend180
                                        #   in Loop: Header=BB2_12 Depth=2
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
	movq	(%rbx), %rax
	movl	-8(%rax), %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	testl	%r14d, %r14d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, 80(%rsp)
.LBB2_24:                               # %label_and_endpointzzzzzzzzzzzzzzzzzzzzzt
                                        #   in Loop: Header=BB2_12 Depth=2
	movq	%rbx, %r14
	movq	%rbp, %r12
	testq	%rax, %rax
	movq	144(%rsp), %rdi
	je	.LBB2_12
# BB#25:                                # %entry_condend200
                                        #   in Loop: Header=BB2_11 Depth=1
	movl	$0, gSigInt(%rip)
	movl	40(%rsp), %ebx
	movl	$1676, %esi             # imm = 0x68C
	movq	%rdi, %rbp
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#26:                                # %entry_ifend204
                                        #   in Loop: Header=BB2_11 Depth=1
	movq	%rbp, %r13
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
	movq	%r14, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
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
	movq	%r12, %r15
	movq	%r15, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	24(%rsp), %r12          # 8-byte Reload
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_27
# BB#28:                                # %entry_ifend224
                                        #   in Loop: Header=BB2_11 Depth=1
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
	movq	(%rbp), %rax
	movl	-8(%rax), %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	cmpl	$47, %ebx
	jne	.LBB2_36
# BB#29:                                # %entry_condend244
                                        #   in Loop: Header=BB2_11 Depth=1
	movl	$.Lglobal_string.4, %edi
	callq	create_string_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movq	(%rbp), %rax
	movl	40(%rsp), %ecx
	movl	64(%rsp), %edx
	movq	$0, (%rax)
	movq	%rcx, (%rax)
	movq	(%rbp), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%rbp)
	movq	$0, 8(%rax)
	movq	%rdx, 8(%rax)
	addq	$8, (%rbp)
	movq	%r13, %rbx
	movq	%rbx, (%rsp)
	movl	$2, %r8d
	movl	$1728, %r9d             # imm = 0x6C0
	movq	%rbp, %rdi
	movq	%r15, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	%r12, %rcx
	callq	run_create_carray
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#30:                                # %entry_ifend255
                                        #   in Loop: Header=BB2_11 Depth=1
	movq	(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$1736, %esi             # imm = 0x6C8
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#31:                                # %entry_ifend258
                                        #   in Loop: Header=BB2_11 Depth=1
	movq	40(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
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
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%rbp)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r15, %rbx
	movq	%rbx, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	%r12, %r14
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_5
# BB#32:                                # %entry_ifend278
                                        #   in Loop: Header=BB2_11 Depth=1
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
	movq	%rbx, %r14
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 72(%rsp)
	movq	%r15, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r12d
	movl	$1744, %esi             # imm = 0x6D0
	jmp	.LBB2_33
.LBB2_36:                               # %label_elsezzzzzzzzzzzzzzzzzzzzzu
                                        #   in Loop: Header=BB2_11 Depth=1
	movl	$.Lglobal_string.5, %edi
	callq	create_string_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movq	(%rbp), %rax
	movl	40(%rsp), %ecx
	movl	64(%rsp), %edx
	movq	$0, (%rax)
	movq	%rcx, (%rax)
	movq	(%rbp), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%rbp)
	movq	$0, 8(%rax)
	movq	%rdx, 8(%rax)
	addq	$8, (%rbp)
	movq	%r13, %rbx
	movq	%rbx, (%rsp)
	movl	$2, %r8d
	movl	$1840, %r9d             # imm = 0x730
	movq	%rbp, %rdi
	movq	%r15, %rsi
	movl	36(%rsp), %edx          # 4-byte Reload
	movq	%r12, %rcx
	callq	run_create_carray
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#37:                                # %entry_ifend347
                                        #   in Loop: Header=BB2_11 Depth=1
	movq	(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$1848, %esi             # imm = 0x738
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#38:                                # %entry_ifend350
                                        #   in Loop: Header=BB2_11 Depth=1
	movq	40(%rsp), %rcx
	movq	16(%rsp), %rdx          # 8-byte Reload
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
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	movq	(%rbp), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%rbp)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%rbp)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%r15, %rbx
	movq	%rbx, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	%r12, %r14
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB2_5
# BB#39:                                # %entry_ifend370
                                        #   in Loop: Header=BB2_11 Depth=1
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
	movq	%rbx, %r14
	movq	$0, 72(%rsp)
	movq	%rax, 72(%rsp)
	movq	(%rbp), %rax
	movq	-8(%rax), %r15
	movl	%r15d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	$0, 72(%rsp)
	movq	%r15, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %r12d
	movl	$1856, %esi             # imm = 0x740
.LBB2_33:                               # %entry_ifend278
                                        #   in Loop: Header=BB2_11 Depth=1
	movq	144(%rsp), %rbx
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#34:                                # %entry_ifend299
                                        #   in Loop: Header=BB2_11 Depth=1
	movq	40(%rsp), %rcx
	movq	16(%rsp), %rbx          # 8-byte Reload
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
	movq	%rbp, %r13
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r13)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	%r14, %r12
	movq	%r12, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	24(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_35
.LBB2_5:                                # %then_block19
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB2_1
.LBB2_15:                               # %entry_condend111
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %ebx
	movl	$2092, %esi             # imm = 0x82C
	movq	144(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#16:                                # %entry_ifend434
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
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r14)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%rbp, %rbx
	movq	%rbx, %rdx
	movl	36(%rsp), %ecx          # 4-byte Reload
	movq	%r14, %r8
	movq	24(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_17
.LBB2_9:                                # %then_block53
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
.LBB2_27:                               # %then_block223
	movq	%r12, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB2_1
.LBB2_17:                               # %entry_ifend451
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
	movq	(%r14), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r14)
	movl	$0, gSigInt(%rip)
	movl	56(%rsp), %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB2_2
.Lfunc_end2:
	.size	"Directory.entries(String)$$4", .Lfunc_end2-"Directory.entries(String)$$4"
	.cfi_endproc

	.globl	"Directory.glob(String,String,int)$$5"
	.align	16, 0x90
	.type	"Directory.glob(String,String,int)$$5",@function
"Directory.glob(String,String,int)$$5": # @"Directory.glob(String,String,int)$$5"
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
	subq	$104, %rsp
.Ltmp45:
	.cfi_def_cfa_offset 160
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
	movl	%r9d, 44(%rsp)          # 4-byte Spill
	movq	%r8, %r12
	movq	%rcx, %r13
	movq	%rdx, 32(%rsp)          # 8-byte Spill
	movq	%rsi, %r15
	movq	160(%rsp), %rbp
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	8(%r13), %rax
	movq	$0, 56(%rsp)
	movq	%rax, 56(%rsp)
	movq	16(%r13), %rax
	movq	$0, 64(%rsp)
	movq	%rax, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	$0, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2104, %esi             # imm = 0x838
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	48(%rsp), %r14d
	movl	$2116, %esi             # imm = 0x844
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#4:                                 # %entry_ifend6
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
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	44(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r12, %r8
	movq	32(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_5
# BB#6:                                 # %entry_ifend27
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
	movq	(%r12), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 72(%rsp)
	movq	%rbx, 72(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2128, %esi             # imm = 0x850
	movq	160(%rsp), %rbx
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#7:                                 # %entry_ifend46
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r14d
	movl	%r14d, %edi
	callq	push_jit_object
	movl	$2144, %esi             # imm = 0x860
	movq	%rbx, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#8:                                 # %entry_ifend49
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
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r14d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%ebp, %ecx
	movq	%r12, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB3_10
# BB#9:                                 # %then_block69
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_10:                               # %entry_ifend70
	movq	%rbp, %r14
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
	movq	%r13, 24(%rsp)          # 8-byte Spill
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 80(%rsp)
	movq	%rbx, 80(%rsp)
	movl	$0, gSigInt(%rip)
	jmp	.LBB3_11
.LBB3_31:                               # %entry_ifend336
                                        #   in Loop: Header=BB3_11 Depth=1
	movq	%rbx, %r14
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
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
.LBB3_11:                               # %entry_condend
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_12 Depth 2
	movq	160(%rsp), %rdi
.LBB3_12:                               # %entry_condend
                                        #   Parent Loop BB3_11 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	$0, gSigInt(%rip)
	movl	72(%rsp), %ebx
	movl	$2236, %esi             # imm = 0x8BC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#13:                                # %entry_ifend94
                                        #   in Loop: Header=BB3_12 Depth=2
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
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	movl	$2, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	%r14, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_5
# BB#14:                                # %entry_ifend115
                                        #   in Loop: Header=BB3_12 Depth=2
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
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 88(%rsp)
	movq	%r13, 88(%rsp)
	movl	$0, gSigInt(%rip)
	testl	%r13d, %r13d
	je	.LBB3_15
# BB#18:                                # %label_if_endzzzzzzzzzzzzzzzzzzzzzw
                                        #   in Loop: Header=BB3_12 Depth=2
	movl	56(%rsp), %ebx
	movl	64(%rsp), %r14d
	movl	$2392, %esi             # imm = 0x958
	movq	160(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#19:                                # %entry_ifend147
                                        #   in Loop: Header=BB3_12 Depth=2
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
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$63, %esi
	movq	%rax, %rdi
	movq	24(%rsp), %r13          # 8-byte Reload
	movq	%r13, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	32(%rsp), %r14          # 8-byte Reload
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_20
# BB#21:                                # %entry_ifend174
                                        #   in Loop: Header=BB3_12 Depth=2
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
	movq	(%r12), %rax
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	testb	$1, %bl
	movq	160(%rsp), %rdi
	je	.LBB3_12
# BB#22:                                # %entry_condend197
                                        #   in Loop: Header=BB3_11 Depth=1
	movl	$0, gSigInt(%rip)
	movl	48(%rsp), %ebx
	movl	$2436, %esi             # imm = 0x984
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#23:                                # %entry_ifend201
                                        #   in Loop: Header=BB3_11 Depth=1
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
	movq	%r12, %rbp
	movq	(%rbp), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
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
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%rbp, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_20
# BB#24:                                # %entry_ifend225
                                        #   in Loop: Header=BB3_11 Depth=1
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
	movq	(%rbp), %rax
	movl	-8(%rax), %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, gSigInt(%rip)
	cmpl	$47, %r12d
	jne	.LBB3_32
# BB#25:                                # %entry_condend249
                                        #   in Loop: Header=BB3_11 Depth=1
	movl	$.Lglobal_string.6, %edi
	callq	create_string_object
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movq	(%rbp), %rax
	movl	48(%rsp), %ecx
	movl	88(%rsp), %edx
	movq	$0, (%rax)
	movq	%rcx, (%rax)
	movq	(%rbp), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%rbp)
	movq	$0, 8(%rax)
	movq	%rdx, 8(%rax)
	addq	$8, (%rbp)
	movq	160(%rsp), %r12
	movq	%r12, (%rsp)
	movl	$2, %r8d
	movl	$2488, %r9d             # imm = 0x9B8
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movq	%r13, %rbx
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r14, %rcx
	callq	run_create_carray
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#26:                                # %entry_ifend260
                                        #   in Loop: Header=BB3_11 Depth=1
	movq	(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$2496, %esi             # imm = 0x9C0
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#27:                                # %entry_ifend263
                                        #   in Loop: Header=BB3_11 Depth=1
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
	movq	%rbp, %r12
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r12)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%rbx, %rbp
	movq	%rbp, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	%r14, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_5
# BB#28:                                # %entry_ifend287
                                        #   in Loop: Header=BB3_11 Depth=1
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
	movq	%rbp, %r14
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 96(%rsp)
	movq	%r13, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %ebx
	movl	$2504, %esi             # imm = 0x9C8
	jmp	.LBB3_29
.LBB3_32:                               # %label_elsezzzzzzzzzzzzzzzzzzzzzy
                                        #   in Loop: Header=BB3_11 Depth=1
	movl	$.Lglobal_string.7, %edi
	callq	create_string_object
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movq	(%rbp), %rax
	movl	48(%rsp), %ecx
	movl	88(%rsp), %edx
	movq	$0, (%rax)
	movq	%rcx, (%rax)
	movq	(%rbp), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%rbp)
	movq	$0, 8(%rax)
	movq	%rdx, 8(%rax)
	addq	$8, (%rbp)
	movq	160(%rsp), %r12
	movq	%r12, (%rsp)
	movl	$2, %r8d
	movl	$2600, %r9d             # imm = 0xA28
	movq	%rbp, %rdi
	movq	%r13, %rsi
	movq	%r13, %rbx
	movl	44(%rsp), %edx          # 4-byte Reload
	movq	%r14, %rcx
	callq	run_create_carray
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#33:                                # %entry_ifend368
                                        #   in Loop: Header=BB3_11 Depth=1
	movq	(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$2608, %esi             # imm = 0xA30
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#34:                                # %entry_ifend371
                                        #   in Loop: Header=BB3_11 Depth=1
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
	movq	%rbp, %r12
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movq	%r13, 8(%rcx)
	addq	$8, (%r12)
	movl	$8, %esi
	movq	%rax, %rdi
	movq	%rbx, %rbp
	movq	%rbp, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	%r14, %rbx
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB3_5
# BB#35:                                # %entry_ifend395
                                        #   in Loop: Header=BB3_11 Depth=1
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
	movq	%rbp, %r14
	movq	$0, 96(%rsp)
	movq	%rax, 96(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 96(%rsp)
	movq	%r13, 96(%rsp)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %ebx
	movl	$2616, %esi             # imm = 0xA38
.LBB3_29:                               # %entry_ifend287
                                        #   in Loop: Header=BB3_11 Depth=1
	movq	160(%rsp), %rbp
	movq	%rbp, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#30:                                # %entry_ifend312
                                        #   in Loop: Header=BB3_11 Depth=1
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
	movq	%r14, %r13
	movq	%r13, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	32(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB3_31
	jmp	.LBB3_5
.LBB3_20:                               # %then_block173
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB3_1
.LBB3_15:                               # %entry_condend139
	movl	$0, gSigInt(%rip)
	movl	72(%rsp), %ebx
	movl	$2852, %esi             # imm = 0xB24
	movq	160(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#16:                                # %entry_ifend471
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
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	24(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %rdx
	movl	44(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	32(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB3_17
.LBB3_5:                                # %then_block26
	movq	%rbx, %rdi
	callq	get_try_catch_label_name
.LBB3_1:                                # %then_block
	xorl	%eax, %eax
.LBB3_2:                                # %then_block
	addq	$104, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB3_17:                               # %entry_ifend492
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
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movl	$0, gSigInt(%rip)
	movl	80(%rsp), %eax
	movq	%rax, (%rbp)
	movl	$1, %eax
	jmp	.LBB3_2
.Lfunc_end3:
	.size	"Directory.glob(String,String,int)$$5", .Lfunc_end3-"Directory.glob(String,String,int)$$5"
	.cfi_endproc

	.globl	"Directory.glob(String,String)$$6"
	.align	16, 0x90
	.type	"Directory.glob(String,String)$$6",@function
"Directory.glob(String,String)$$6":     # @"Directory.glob(String,String)$$6"
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
	subq	$24, %rsp
.Ltmp58:
	.cfi_def_cfa_offset 80
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
	movl	$2864, %esi             # imm = 0xB30
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
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
	addq	$8, (%rbx)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB4_5
# BB#4:                                 # %then_block15
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB4_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB4_2
.LBB4_5:                                # %entry_ifend16
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
.LBB4_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end4:
	.size	"Directory.glob(String,String)$$6", .Lfunc_end4-"Directory.glob(String,String)$$6"
	.cfi_endproc

	.globl	"Directory.glob(String,int)$$7"
	.align	16, 0x90
	.type	"Directory.glob(String,int)$$7",@function
"Directory.glob(String,int)$$7":        # @"Directory.glob(String,int)$$7"
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
	subq	$40, %rsp
.Ltmp71:
	.cfi_def_cfa_offset 96
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
	movl	%r9d, 12(%rsp)          # 4-byte Spill
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, 16(%rsp)          # 8-byte Spill
	movq	%rsi, %rbp
	movq	(%r14), %r12
	movq	$0, 24(%rsp)
	movq	%r12, 24(%rsp)
	movq	8(%r14), %r15
	movq	$0, 32(%rsp)
	movq	%r15, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.8, %edi
	callq	create_string_object
	movl	%eax, %r13d
	movl	%r13d, %edi
	callq	push_jit_object
	movl	$2880, %esi             # imm = 0xB40
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%r12, (%rbp)
	movq	$0, 8(%rbp)
	movq	%r15, 8(%rbp)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
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
	movl	%r15d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%rbx)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%rbx, %r8
	movq	16(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB5_5
# BB#4:                                 # %then_block15
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB5_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB5_2
.LBB5_5:                                # %entry_ifend16
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
.LBB5_2:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end5:
	.size	"Directory.glob(String,int)$$7", .Lfunc_end5-"Directory.glob(String,int)$$7"
	.cfi_endproc

	.globl	"Directory.glob(String)$$8"
	.align	16, 0x90
	.type	"Directory.glob(String)$$8",@function
"Directory.glob(String)$$8":            # @"Directory.glob(String)$$8"
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
	subq	$24, %rsp
.Ltmp84:
	.cfi_def_cfa_offset 80
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
	movl	%r9d, 4(%rsp)           # 4-byte Spill
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, 8(%rsp)           # 8-byte Spill
	movq	%rsi, %r13
	movq	80(%rsp), %r12
	movq	(%r14), %r15
	movq	$0, 16(%rsp)
	movq	%r15, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.9, %edi
	callq	create_string_object
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$2896, %esi             # imm = 0xB50
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%r15, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
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
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%rbx, %r8
	movq	8(%rsp), %rbp           # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB6_5
# BB#4:                                 # %then_block11
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB6_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB6_2
.LBB6_5:                                # %entry_ifend12
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
	.size	"Directory.glob(String)$$8", .Lfunc_end6-"Directory.glob(String)$$8"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"This directory is not opened"
	.size	.Lglobal_string, 29

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.asciz	"."
	.size	.Lglobal_string.2, 2

	.type	.Lglobal_string.3,@object # @global_string.3
.Lglobal_string.3:
	.asciz	".."
	.size	.Lglobal_string.3, 3

	.type	.Lglobal_string.4,@object # @global_string.4
.Lglobal_string.4:
	.asciz	"%s%s"
	.size	.Lglobal_string.4, 5

	.type	.Lglobal_string.5,@object # @global_string.5
.Lglobal_string.5:
	.asciz	"%s/%s"
	.size	.Lglobal_string.5, 6

	.type	.Lglobal_string.6,@object # @global_string.6
.Lglobal_string.6:
	.asciz	"%s%s"
	.size	.Lglobal_string.6, 5

	.type	.Lglobal_string.7,@object # @global_string.7
.Lglobal_string.7:
	.asciz	"%s/%s"
	.size	.Lglobal_string.7, 6

	.type	.Lglobal_string.8,@object # @global_string.8
.Lglobal_string.8:
	.asciz	"."
	.size	.Lglobal_string.8, 2

	.type	.Lglobal_string.9,@object # @global_string.9
.Lglobal_string.9:
	.asciz	"."
	.size	.Lglobal_string.9, 2


	.section	".note.GNU-stack","",@progbits
