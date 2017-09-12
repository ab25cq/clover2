	.text
	.file	"Global.bc"
	.globl	"Global.getenv(String)$$0"
	.align	16, 0x90
	.type	"Global.getenv(String)$$0",@function
"Global.getenv(String)$$0":             # @"Global.getenv(String)$$0"
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
	pushq	%rax
.Ltmp6:
	.cfi_def_cfa_offset 64
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
	movl	$800, %esi              # imm = 0x320
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$17, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB0_5
# BB#4:                                 # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB0_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB0_2
.LBB0_5:                                # %entry_ifend6
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
.LBB0_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end0:
	.size	"Global.getenv(String)$$0", .Lfunc_end0-"Global.getenv(String)$$0"
	.cfi_endproc

	.globl	"Global.print(String)$$1"
	.align	16, 0x90
	.type	"Global.print(String)$$1",@function
"Global.print(String)$$1":              # @"Global.print(String)$$1"
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
	pushq	%rax
.Ltmp19:
	.cfi_def_cfa_offset 64
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
	movl	$808, %esi              # imm = 0x328
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$20, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB1_5
# BB#4:                                 # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB1_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB1_2
.LBB1_5:                                # %entry_ifend6
	movq	(%r14), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, (%r14)
	movl	$1, %eax
.LBB1_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end1:
	.size	"Global.print(String)$$1", .Lfunc_end1-"Global.print(String)$$1"
	.cfi_endproc

	.globl	"Global.printToError(String)$$2"
	.align	16, 0x90
	.type	"Global.printToError(String)$$2",@function
"Global.printToError(String)$$2":       # @"Global.printToError(String)$$2"
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
	pushq	%rax
.Ltmp32:
	.cfi_def_cfa_offset 64
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
	movl	$816, %esi              # imm = 0x330
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB2_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$22, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB2_5
# BB#4:                                 # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB2_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB2_2
.LBB2_5:                                # %entry_ifend6
	movq	(%r14), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, (%r14)
	movl	$1, %eax
.LBB2_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end2:
	.size	"Global.printToError(String)$$2", .Lfunc_end2-"Global.printToError(String)$$2"
	.cfi_endproc

	.globl	"Global.println(String)$$3"
	.align	16, 0x90
	.type	"Global.println(String)$$3",@function
"Global.println(String)$$3":            # @"Global.println(String)$$3"
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
	pushq	%rax
.Ltmp45:
	.cfi_def_cfa_offset 64
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
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %rbp
	movq	64(%rsp), %rdi
	movq	(%r14), %rbx
	movq	$0, (%rsp)
	movq	%rbx, (%rsp)
	movl	$0, gSigInt(%rip)
	movl	$824, %esi              # imm = 0x338
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB3_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$21, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB3_5
# BB#4:                                 # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB3_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB3_2
.LBB3_5:                                # %entry_ifend6
	movq	(%r14), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, (%r14)
	movl	$1, %eax
.LBB3_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end3:
	.size	"Global.println(String)$$3", .Lfunc_end3-"Global.println(String)$$3"
	.cfi_endproc

	.globl	"Global.printlnToError(String)$$4"
	.align	16, 0x90
	.type	"Global.printlnToError(String)$$4",@function
"Global.printlnToError(String)$$4":     # @"Global.printlnToError(String)$$4"
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
	pushq	%rax
.Ltmp58:
	.cfi_def_cfa_offset 64
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
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %rbp
	movq	64(%rsp), %rdi
	movq	(%r14), %rbx
	movq	$0, (%rsp)
	movq	%rbx, (%rsp)
	movl	$0, gSigInt(%rip)
	movl	$832, %esi              # imm = 0x340
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB4_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$23, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB4_5
# BB#4:                                 # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB4_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB4_2
.LBB4_5:                                # %entry_ifend6
	movq	(%r14), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, (%r14)
	movl	$1, %eax
.LBB4_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end4:
	.size	"Global.printlnToError(String)$$4", .Lfunc_end4-"Global.printlnToError(String)$$4"
	.cfi_endproc

	.globl	"Global.printf(String,Array)$$5"
	.align	16, 0x90
	.type	"Global.printf(String,Array)$$5",@function
"Global.printf(String,Array)$$5":       # @"Global.printf(String,Array)$$5"
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
	movq	%r8, %r12
	movq	%rcx, %r14
	movq	%rdx, %r13
	movq	%rsi, %r15
	movq	96(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movq	8(%r14), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$840, %esi              # imm = 0x348
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r15)
	movq	%rbp, (%r15)
	movq	$0, 8(%r15)
	movq	%rbx, 8(%r15)
	movq	$0, 16(%r15)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$24, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r13, %rdi
	je	.LBB5_5
# BB#4:                                 # %then_block14
	callq	get_try_catch_label_name
	jmp	.LBB5_1
.LBB5_5:                                # %entry_ifend15
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movq	%rdi, (%rsp)            # 8-byte Spill
	movq	8(%r14), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	16(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$848, %esi              # imm = 0x350
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB5_1
# BB#6:                                 # %entry_ifend27
	movq	$0, (%r15)
	movq	%rbp, (%r15)
	movq	$0, 8(%r15)
	movq	%rbx, 8(%r15)
	movq	$0, 16(%r15)
	movq	%r13, 16(%r15)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	movl	$20, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	(%rsp), %rbx            # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB5_8
# BB#7:                                 # %then_block39
	callq	get_try_catch_label_name
.LBB5_1:                                # %then_block
	xorl	%eax, %eax
.LBB5_2:                                # %then_block
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB5_8:                                # %entry_ifend40
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r14), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, (%r14)
	movl	$1, %eax
	jmp	.LBB5_2
.Lfunc_end5:
	.size	"Global.printf(String,Array)$$5", .Lfunc_end5-"Global.printf(String,Array)$$5"
	.cfi_endproc

	.globl	"Global.printf(String)$$6"
	.align	16, 0x90
	.type	"Global.printf(String)$$6",@function
"Global.printf(String)$$6":             # @"Global.printf(String)$$6"
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
	pushq	%rax
.Ltmp84:
	.cfi_def_cfa_offset 64
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
	movl	$856, %esi              # imm = 0x358
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB6_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$20, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB6_5
# BB#4:                                 # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB6_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB6_2
.LBB6_5:                                # %entry_ifend6
	movq	(%r14), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, (%r14)
	movl	$1, %eax
.LBB6_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end6:
	.size	"Global.printf(String)$$6", .Lfunc_end6-"Global.printf(String)$$6"
	.cfi_endproc

	.globl	"Global.printfToError(String,Array)$$7"
	.align	16, 0x90
	.type	"Global.printfToError(String,Array)$$7",@function
"Global.printfToError(String,Array)$$7": # @"Global.printfToError(String,Array)$$7"
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
	movl	%r9d, 12(%rsp)          # 4-byte Spill
	movq	%r8, %r12
	movq	%rcx, %r14
	movq	%rdx, %r13
	movq	%rsi, %r15
	movq	96(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movq	8(%r14), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	$0, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$864, %esi              # imm = 0x360
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r15)
	movq	%rbp, (%r15)
	movq	$0, 8(%r15)
	movq	%rbx, 8(%r15)
	movq	$0, 16(%r15)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r12), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r12)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r12)
	movl	$24, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r13, %rdi
	je	.LBB7_5
# BB#4:                                 # %then_block14
	callq	get_try_catch_label_name
	jmp	.LBB7_1
.LBB7_5:                                # %entry_ifend15
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movq	%rdi, (%rsp)            # 8-byte Spill
	movq	8(%r14), %rbx
	movq	$0, 24(%rsp)
	movq	%rbx, 24(%rsp)
	movq	16(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r12), %rax
	movq	-8(%rax), %r13
	movl	%r13d, %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, 32(%rsp)
	movq	%r13, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$872, %esi              # imm = 0x368
	movq	96(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB7_1
# BB#6:                                 # %entry_ifend27
	movq	$0, (%r15)
	movq	%rbp, (%r15)
	movq	$0, 8(%r15)
	movq	%rbx, 8(%r15)
	movq	$0, 16(%r15)
	movq	%r13, 16(%r15)
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movl	%r13d, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r12)
	movl	$22, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	12(%rsp), %ecx          # 4-byte Reload
	movq	%r12, %r8
	movq	(%rsp), %rbx            # 8-byte Reload
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %rdi
	je	.LBB7_8
# BB#7:                                 # %then_block39
	callq	get_try_catch_label_name
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
.LBB7_8:                                # %entry_ifend40
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%r14), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movq	16(%r14), %rax
	movq	$0, 32(%rsp)
	movq	%rax, 32(%rsp)
	movq	(%r12), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r12)
	movq	$0, (%r14)
	movl	$1, %eax
	jmp	.LBB7_2
.Lfunc_end7:
	.size	"Global.printfToError(String,Array)$$7", .Lfunc_end7-"Global.printfToError(String,Array)$$7"
	.cfi_endproc

	.globl	"Global.sprintf(String,Array)$$8"
	.align	16, 0x90
	.type	"Global.sprintf(String,Array)$$8",@function
"Global.sprintf(String,Array)$$8":      # @"Global.sprintf(String,Array)$$8"
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
	subq	$24, %rsp
.Ltmp110:
	.cfi_def_cfa_offset 80
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
	movl	$880, %esi              # imm = 0x370
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB8_1
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
	movl	$24, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB8_5
# BB#4:                                 # %then_block12
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB8_1:                                # %then_block
	xorl	%eax, %eax
	jmp	.LBB8_2
.LBB8_5:                                # %entry_ifend13
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
.LBB8_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end8:
	.size	"Global.sprintf(String,Array)$$8", .Lfunc_end8-"Global.sprintf(String,Array)$$8"
	.cfi_endproc


	.section	".note.GNU-stack","",@progbits
