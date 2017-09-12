	.text
	.file	"stat.bc"
	.globl	"stat.S_ISDIR()$$2"
	.align	16, 0x90
	.type	"stat.S_ISDIR()$$2",@function
"stat.S_ISDIR()$$2":                    # @"stat.S_ISDIR()$$2"
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
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %rbp
	movq	(%rbx), %r8
	movq	$0, 16(%rsp)
	movq	%r8, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %r12
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	%r12, (%rsp)
	movl	$1, %r8d
	movl	$1244, %r9d             # imm = 0x4DC
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %r13
	movq	%r12, (%rsp)
	movl	$2, %r8d
	movl	$1252, %r9d             # imm = 0x4E4
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB0_1
# BB#5:                                 # %entry_ifend6
	movq	8(%rsp), %rcx           # 8-byte Reload
	andl	%ecx, %r13d
	movq	(%rax), %rax
	cmpl	%eax, %r13d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, (%rbx)
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
	.size	"stat.S_ISDIR()$$2", .Lfunc_end0-"stat.S_ISDIR()$$2"
	.cfi_endproc

	.globl	"stat.S_ISCHR()$$3"
	.align	16, 0x90
	.type	"stat.S_ISCHR()$$3",@function
"stat.S_ISCHR()$$3":                    # @"stat.S_ISCHR()$$3"
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
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %rbp
	movq	(%rbx), %r8
	movq	$0, 16(%rsp)
	movq	%r8, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %r12
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	%r12, (%rsp)
	movl	$1, %r8d
	movl	$1260, %r9d             # imm = 0x4EC
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %r13
	movq	%r12, (%rsp)
	movl	$3, %r8d
	movl	$1268, %r9d             # imm = 0x4F4
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#5:                                 # %entry_ifend6
	movq	8(%rsp), %rcx           # 8-byte Reload
	andl	%ecx, %r13d
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
	.size	"stat.S_ISCHR()$$3", .Lfunc_end1-"stat.S_ISCHR()$$3"
	.cfi_endproc

	.globl	"stat.S_ISBLK()$$4"
	.align	16, 0x90
	.type	"stat.S_ISBLK()$$4",@function
"stat.S_ISBLK()$$4":                    # @"stat.S_ISBLK()$$4"
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
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %rbp
	movq	(%rbx), %r8
	movq	$0, 16(%rsp)
	movq	%r8, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %r12
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	%r12, (%rsp)
	movl	$1, %r8d
	movl	$1276, %r9d             # imm = 0x4FC
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %r13
	movq	%r12, (%rsp)
	movl	$4, %r8d
	movl	$1284, %r9d             # imm = 0x504
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#5:                                 # %entry_ifend6
	movq	8(%rsp), %rcx           # 8-byte Reload
	andl	%ecx, %r13d
	movq	(%rax), %rax
	cmpl	%eax, %r13d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB2_2
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
	.size	"stat.S_ISBLK()$$4", .Lfunc_end2-"stat.S_ISBLK()$$4"
	.cfi_endproc

	.globl	"stat.S_ISREG()$$5"
	.align	16, 0x90
	.type	"stat.S_ISREG()$$5",@function
"stat.S_ISREG()$$5":                    # @"stat.S_ISREG()$$5"
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
	movl	%r9d, %r14d
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %rbp
	movq	(%rbx), %r8
	movq	$0, 16(%rsp)
	movq	%r8, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %r12
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	%r12, (%rsp)
	movl	$1, %r8d
	movl	$1292, %r9d             # imm = 0x50C
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %r13
	movq	%r12, (%rsp)
	movl	$5, %r8d
	movl	$1300, %r9d             # imm = 0x514
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#5:                                 # %entry_ifend6
	movq	8(%rsp), %rcx           # 8-byte Reload
	andl	%ecx, %r13d
	movq	(%rax), %rax
	cmpl	%eax, %r13d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB3_2
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
	.size	"stat.S_ISREG()$$5", .Lfunc_end3-"stat.S_ISREG()$$5"
	.cfi_endproc

	.globl	"stat.S_ISFIFO()$$6"
	.align	16, 0x90
	.type	"stat.S_ISFIFO()$$6",@function
"stat.S_ISFIFO()$$6":                   # @"stat.S_ISFIFO()$$6"
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
	movl	%r9d, %r14d
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %rbp
	movq	(%rbx), %r8
	movq	$0, 16(%rsp)
	movq	%r8, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %r12
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	%r12, (%rsp)
	movl	$1, %r8d
	movl	$1308, %r9d             # imm = 0x51C
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %r13
	movq	%r12, (%rsp)
	movl	$6, %r8d
	movl	$1316, %r9d             # imm = 0x524
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#5:                                 # %entry_ifend6
	movq	8(%rsp), %rcx           # 8-byte Reload
	andl	%ecx, %r13d
	movq	(%rax), %rax
	cmpl	%eax, %r13d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB4_2
.LBB4_1:                                # %then_block
	xorl	%eax, %eax
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
	.size	"stat.S_ISFIFO()$$6", .Lfunc_end4-"stat.S_ISFIFO()$$6"
	.cfi_endproc

	.globl	"stat.S_ISLNK()$$7"
	.align	16, 0x90
	.type	"stat.S_ISLNK()$$7",@function
"stat.S_ISLNK()$$7":                    # @"stat.S_ISLNK()$$7"
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
	subq	$24, %rsp
.Ltmp71:
	.cfi_def_cfa_offset 80
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
	movl	%r9d, %r14d
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %rbp
	movq	(%rbx), %r8
	movq	$0, 16(%rsp)
	movq	%r8, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %r12
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	%r12, (%rsp)
	movl	$1, %r8d
	movl	$1324, %r9d             # imm = 0x52C
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %r13
	movq	%r12, (%rsp)
	movl	$7, %r8d
	movl	$1332, %r9d             # imm = 0x534
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#5:                                 # %entry_ifend6
	movq	8(%rsp), %rcx           # 8-byte Reload
	andl	%ecx, %r13d
	movq	(%rax), %rax
	cmpl	%eax, %r13d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB5_2
.LBB5_1:                                # %then_block
	xorl	%eax, %eax
.LBB5_2:                                # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end5:
	.size	"stat.S_ISLNK()$$7", .Lfunc_end5-"stat.S_ISLNK()$$7"
	.cfi_endproc

	.globl	"stat.S_ISSOCK()$$8"
	.align	16, 0x90
	.type	"stat.S_ISSOCK()$$8",@function
"stat.S_ISSOCK()$$8":                   # @"stat.S_ISSOCK()$$8"
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
	movl	%r9d, %r14d
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %rbp
	movq	(%rbx), %r8
	movq	$0, 16(%rsp)
	movq	%r8, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#3:                                 # %entry_ifend
	movq	80(%rsp), %r12
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	%r12, (%rsp)
	movl	$1, %r8d
	movl	$1340, %r9d             # imm = 0x53C
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %r13
	movq	%r12, (%rsp)
	movl	$8, %r8d
	movl	$1348, %r9d             # imm = 0x544
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#5:                                 # %entry_ifend6
	movq	8(%rsp), %rcx           # 8-byte Reload
	andl	%ecx, %r13d
	movq	(%rax), %rax
	cmpl	%eax, %r13d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB6_2
.LBB6_1:                                # %then_block
	xorl	%eax, %eax
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
	.size	"stat.S_ISSOCK()$$8", .Lfunc_end6-"stat.S_ISSOCK()$$8"
	.cfi_endproc

	.globl	"stat.permission()$$9"
	.align	16, 0x90
	.type	"stat.permission()$$9",@function
"stat.permission()$$9":                 # @"stat.permission()$$9"
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
	subq	$56, %rsp
.Ltmp97:
	.cfi_def_cfa_offset 112
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
	movl	%r9d, %r14d
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %rbp
	movq	(%rbx), %r8
	movq	$0, 48(%rsp)
	movq	%r8, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#3:                                 # %entry_ifend
	movq	112(%rsp), %r13
	movq	(%rax), %r12
	movq	%r13, (%rsp)
	movl	$9, %r8d
	movl	$1356, %r9d             # imm = 0x54C
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %rax
	movq	%rax, 40(%rsp)          # 8-byte Spill
	movq	%r13, (%rsp)
	movl	$10, %r8d
	movl	$1364, %r9d             # imm = 0x554
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#5:                                 # %entry_ifend6
	movq	(%rax), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	%r13, (%rsp)
	movl	$11, %r8d
	movl	$1372, %r9d             # imm = 0x55C
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#6:                                 # %entry_ifend9
	movq	(%rax), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	%r13, (%rsp)
	movl	$15, %r8d
	movl	$1380, %r9d             # imm = 0x564
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#7:                                 # %entry_ifend13
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	%r13, (%rsp)
	movl	$19, %r8d
	movl	$1388, %r9d             # imm = 0x56C
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#8:                                 # %entry_ifend17
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	%r13, (%rsp)
	movl	$23, %r8d
	movl	$1396, %r9d             # imm = 0x574
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%rbp, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB7_1
# BB#9:                                 # %entry_ifend21
	movq	40(%rsp), %rcx          # 8-byte Reload
	movq	32(%rsp), %rdx          # 8-byte Reload
	orl	%ecx, %edx
	movq	24(%rsp), %rcx          # 8-byte Reload
	orl	%edx, %ecx
	movq	16(%rsp), %rdx          # 8-byte Reload
	orl	%ecx, %edx
	movq	8(%rsp), %rcx           # 8-byte Reload
	orl	%edx, %ecx
	movq	(%rax), %rax
	orl	%ecx, %eax
	andl	%r12d, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB7_2
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
	.size	"stat.permission()$$9", .Lfunc_end7-"stat.permission()$$9"
	.cfi_endproc

	.globl	"stat.S_IXUGO()$$10"
	.align	16, 0x90
	.type	"stat.S_IXUGO()$$10",@function
"stat.S_IXUGO()$$10":                   # @"stat.S_IXUGO()$$10"
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
	subq	$56, %rsp
.Ltmp110:
	.cfi_def_cfa_offset 112
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
	movl	%r9d, %r15d
	movq	%r8, %r12
	movq	%rcx, %rbx
	movq	%rdx, %r14
	movq	(%rbx), %r8
	movq	%r8, 24(%rsp)           # 8-byte Spill
	movq	$0, 32(%rsp)
	movq	%r8, 32(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#3:                                 # %entry_ifend
	movq	112(%rsp), %rbp
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	%rbp, (%rsp)
	movl	$14, %r8d
	movl	$1404, %r9d             # imm = 0x57C
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %r13
	movq	%rbp, (%rsp)
	movl	$14, %r8d
	movl	$1412, %r9d             # imm = 0x584
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#5:                                 # %entry_ifend6
	movq	16(%rsp), %rcx          # 8-byte Reload
	andl	%ecx, %r13d
	movq	(%rax), %rax
	cmpl	%eax, %r13d
	sete	%al
	movq	$0, 40(%rsp)
	movzbl	%al, %eax
	movq	%rax, 40(%rsp)
	jne	.LBB8_15
# BB#6:                                 # %entry_condend
	movl	$1, %r9d
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	112(%rsp), %rcx
	movq	%rcx, %r13
	je	.LBB8_1
# BB#7:                                 # %entry_ifend10
	movq	(%rax), %rax
	movq	%rax, 16(%rsp)          # 8-byte Spill
	movq	%r13, (%rsp)
	movl	$18, %r8d
	movl	$1460, %r9d             # imm = 0x5B4
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#8:                                 # %entry_ifend13
	movq	%r13, %rcx
	movq	(%rax), %r13
	movq	%rcx, (%rsp)
	movl	$18, %r8d
	movl	$1468, %r9d             # imm = 0x5BC
	movq	%r12, %rdi
	movq	%rbx, %rsi
	movl	%r15d, %edx
	movq	%r14, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#9:                                 # %entry_ifend17
	movl	%r15d, %ebp
	movq	16(%rsp), %rcx          # 8-byte Reload
	andl	%ecx, %r13d
	movq	(%rax), %rax
	cmpl	%eax, %r13d
	sete	%al
	movq	$0, 48(%rsp)
	movzbl	%al, %eax
	movq	%rax, 48(%rsp)
	jne	.LBB8_14
# BB#10:                                # %entry_condend22
	movl	$1, %r9d
	movq	%r12, %r15
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r14, %r12
	movq	%r12, %rcx
	movq	24(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	movq	112(%rsp), %r13
	je	.LBB8_1
# BB#11:                                # %entry_ifend26
	movq	(%rax), %rax
	movq	%rax, 24(%rsp)          # 8-byte Spill
	movq	%r13, (%rsp)
	movl	$22, %r8d
	movl	$1516, %r9d             # imm = 0x5EC
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#12:                                # %entry_ifend29
	movq	(%rax), %r14
	movq	%r13, (%rsp)
	movl	$22, %r8d
	movl	$1524, %r9d             # imm = 0x5F4
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%ebp, %edx
	movq	%r12, %rcx
	callq	load_class_field
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#13:                                # %entry_ifend33
	movq	24(%rsp), %rcx          # 8-byte Reload
	andl	%ecx, %r14d
	movq	(%rax), %rax
	cmpl	%eax, %r14d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, 48(%rsp)
.LBB8_14:                               # %label_and_endpointzzzzzzzzzzzzzzzzzzzzw
	movq	%rax, 40(%rsp)
.LBB8_15:                               # %label_and_endpointzzzzzzzzzzzzzzzzzzzzv
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB8_2
.LBB8_1:                                # %then_block
	xorl	%eax, %eax
.LBB8_2:                                # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end8:
	.size	"stat.S_IXUGO()$$10", .Lfunc_end8-"stat.S_IXUGO()$$10"
	.cfi_endproc

	.globl	"stat.atime()$$11"
	.align	16, 0x90
	.type	"stat.atime()$$11",@function
"stat.atime()$$11":                     # @"stat.atime()$$11"
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
	movl	%r9d, %r13d
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %r12
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	80(%rsp), %rdi
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1612, %esi             # imm = 0x64C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$6, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movl	$1616, %esi             # imm = 0x650
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB9_1
# BB#5:                                 # %entry_ifend6
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r13d, %ecx
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
	.size	"stat.atime()$$11", .Lfunc_end9-"stat.atime()$$11"
	.cfi_endproc

	.globl	"stat.ctime()$$12"
	.align	16, 0x90
	.type	"stat.ctime()$$12",@function
"stat.ctime()$$12":                     # @"stat.ctime()$$12"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp130:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp131:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp132:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp133:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp134:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp135:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp136:
	.cfi_def_cfa_offset 80
.Ltmp137:
	.cfi_offset %rbx, -56
.Ltmp138:
	.cfi_offset %r12, -48
.Ltmp139:
	.cfi_offset %r13, -40
.Ltmp140:
	.cfi_offset %r14, -32
.Ltmp141:
	.cfi_offset %r15, -24
.Ltmp142:
	.cfi_offset %rbp, -16
	movl	%r9d, %r13d
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %r12
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	80(%rsp), %rdi
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1620, %esi             # imm = 0x654
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB10_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$8, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movl	$1624, %esi             # imm = 0x658
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB10_1
# BB#5:                                 # %entry_ifend6
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB10_7
# BB#6:                                 # %then_block14
	movq	%r12, %rdi
	callq	get_try_catch_label_name
.LBB10_1:                               # %then_block
	xorl	%eax, %eax
.LBB10_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB10_7:                               # %entry_ifend15
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
	jmp	.LBB10_2
.Lfunc_end10:
	.size	"stat.ctime()$$12", .Lfunc_end10-"stat.ctime()$$12"
	.cfi_endproc

	.globl	"stat.mtime()$$13"
	.align	16, 0x90
	.type	"stat.mtime()$$13",@function
"stat.mtime()$$13":                     # @"stat.mtime()$$13"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp143:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp144:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp145:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp146:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp147:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp148:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp149:
	.cfi_def_cfa_offset 80
.Ltmp150:
	.cfi_offset %rbx, -56
.Ltmp151:
	.cfi_offset %r12, -48
.Ltmp152:
	.cfi_offset %r13, -40
.Ltmp153:
	.cfi_offset %r14, -32
.Ltmp154:
	.cfi_offset %r15, -24
.Ltmp155:
	.cfi_offset %rbp, -16
	movl	%r9d, %r13d
	movq	%r8, %r14
	movq	%rcx, %rbx
	movq	%rdx, %r12
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	80(%rsp), %rdi
	movq	(%rbx), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$1628, %esi             # imm = 0x65C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB11_1
# BB#3:                                 # %entry_ifend
	movq	%rax, %rdi
	callq	create_object
	movl	%eax, %r15d
	movl	%r15d, %edi
	callq	push_jit_object
	movl	$7, %r9d
	movq	%r14, %rdi
	movq	%rbx, %rsi
	movl	%r13d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#4:                                 # %entry_ifend3
	movq	(%rax), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	movl	$1632, %esi             # imm = 0x660
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB11_1
# BB#5:                                 # %entry_ifend6
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	movq	(%r14), %rcx
	movq	$0, (%rcx)
	movl	%r15d, %edx
	movq	%rdx, (%rcx)
	movq	(%r14), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r14)
	movq	$0, 8(%rcx)
	movq	(%rsp), %rdx            # 8-byte Reload
	movq	%rdx, 8(%rcx)
	addq	$8, (%r14)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%rbx, %rdx
	movl	%r13d, %ecx
	movq	%r14, %r8
	movq	%r12, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB11_7
# BB#6:                                 # %then_block14
	movq	%r12, %rdi
	callq	get_try_catch_label_name
.LBB11_1:                               # %then_block
	xorl	%eax, %eax
.LBB11_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB11_7:                               # %entry_ifend15
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
	jmp	.LBB11_2
.Lfunc_end11:
	.size	"stat.mtime()$$13", .Lfunc_end11-"stat.mtime()$$13"
	.cfi_endproc

	.globl	"stat.size()$$14"
	.align	16, 0x90
	.type	"stat.size()$$14",@function
"stat.size()$$14":                      # @"stat.size()$$14"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp156:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp157:
	.cfi_def_cfa_offset 32
.Ltmp158:
	.cfi_offset %rbx, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$5, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB12_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB12_2
.LBB12_1:                               # %then_block
	xorl	%eax, %eax
.LBB12_2:                               # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end12:
	.size	"stat.size()$$14", .Lfunc_end12-"stat.size()$$14"
	.cfi_endproc

	.globl	"stat.uid()$$15"
	.align	16, 0x90
	.type	"stat.uid()$$15",@function
"stat.uid()$$15":                       # @"stat.uid()$$15"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp159:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp160:
	.cfi_def_cfa_offset 32
.Ltmp161:
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
	je	.LBB13_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB13_2
.LBB13_1:                               # %then_block
	xorl	%eax, %eax
.LBB13_2:                               # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end13:
	.size	"stat.uid()$$15", .Lfunc_end13-"stat.uid()$$15"
	.cfi_endproc

	.globl	"stat.gid()$$16"
	.align	16, 0x90
	.type	"stat.gid()$$16",@function
"stat.gid()$$16":                       # @"stat.gid()$$16"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp162:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp163:
	.cfi_def_cfa_offset 32
.Ltmp164:
	.cfi_offset %rbx, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$3, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB14_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB14_2
.LBB14_1:                               # %then_block
	xorl	%eax, %eax
.LBB14_2:                               # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end14:
	.size	"stat.gid()$$16", .Lfunc_end14-"stat.gid()$$16"
	.cfi_endproc

	.globl	"stat.userName()$$17"
	.align	16, 0x90
	.type	"stat.userName()$$17",@function
"stat.userName()$$17":                  # @"stat.userName()$$17"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp165:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp166:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp167:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp168:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp169:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp170:
	.cfi_def_cfa_offset 56
	subq	$120, %rsp
.Ltmp171:
	.cfi_def_cfa_offset 176
.Ltmp172:
	.cfi_offset %rbx, -56
.Ltmp173:
	.cfi_offset %r12, -48
.Ltmp174:
	.cfi_offset %r13, -40
.Ltmp175:
	.cfi_offset %r14, -32
.Ltmp176:
	.cfi_offset %r15, -24
.Ltmp177:
	.cfi_offset %rbp, -16
	movl	%r9d, 100(%rsp)         # 4-byte Spill
	movq	%r8, 80(%rsp)           # 8-byte Spill
	movq	%rcx, 88(%rsp)          # 8-byte Spill
	movq	%rdx, %r14
	movq	%rsi, %rbp
	movq	176(%rsp), %r13
	movq	(%rcx), %r12
	movq	$0, 104(%rsp)
	movq	%r12, 104(%rsp)
	movq	$0, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movq	$0, 112(%rsp)
	movl	%ebx, %r15d
	movq	%r15, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.2, %edi
	callq	create_path_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$1652, %esi             # imm = 0x674
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB15_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%r12, (%rbp)
	movq	$0, 8(%rbp)
	movq	%r15, 8(%rbp)
	movq	%rbp, 72(%rsp)          # 8-byte Spill
	movq	80(%rsp), %r15          # 8-byte Reload
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$9, %esi
	movq	%rax, %rdi
	movq	88(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	100(%rsp), %ecx         # 4-byte Reload
	movq	%r15, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB15_5
# BB#4:                                 # %then_block6
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB15_1
.LBB15_5:                               # %entry_ifend7
	movq	(%rbx), %r13
	movq	$0, 104(%rsp)
	movq	%r13, 104(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 112(%rsp)
	movq	%r12, 112(%rsp)
	movq	%r15, %rbp
	movq	(%rbp), %rax
	movq	%r14, %r15
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$1660, %esi             # imm = 0x67C
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	72(%rsp), %r14          # 8-byte Reload
	je	.LBB15_1
# BB#6:                                 # %entry_ifend15
	movq	$0, (%r14)
	movq	%r13, (%r14)
	movq	$0, 8(%r14)
	movq	%r12, 8(%r14)
	movq	%rbp, %r12
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	addq	$8, (%r12)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	88(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	100(%rsp), %ecx         # 4-byte Reload
	movq	%r12, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB15_8
# BB#7:                                 # %then_block25
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB15_1
.LBB15_8:                               # %entry_ifend26
	movq	(%rbx), %rax
	movq	%rax, 64(%rsp)          # 8-byte Spill
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	8(%rbx), %rax
	movq	%rax, 56(%rsp)          # 8-byte Spill
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	%r12, %rbp
	movq	(%rbp), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, 16(%rsp)
	movl	$0, 8(%rsp)
	movl	$0, (%rsp)
	movl	$.Lglobal_string.3, %edi
	xorl	%esi, %esi
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	xorl	%r8d, %r8d
	xorl	%r9d, %r9d
	callq	create_regex_object
	movq	%r15, %r13
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$1672, %esi             # imm = 0x688
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB15_1
# BB#9:                                 # %entry_ifend39
	movq	$0, (%r14)
	movq	64(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r14)
	movq	$0, 8(%r14)
	movq	56(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%r14)
	movq	%rbp, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r12, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$30, %esi
	movq	%rax, %rdi
	movq	88(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	100(%rsp), %ecx         # 4-byte Reload
	movq	%r8, %r15
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB15_11
# BB#10:                                # %then_block52
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB15_1
.LBB15_11:                              # %entry_ifend53
	movq	(%rbx), %rax
	movq	%rax, 64(%rsp)          # 8-byte Spill
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	8(%rbx), %rax
	movq	%rax, 56(%rsp)          # 8-byte Spill
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	%r15, %rbp
	movq	(%rbp), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 48(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%r13, 32(%rsp)
	movl	$0, 24(%rsp)
	movl	$2, 16(%rsp)
	movl	$2, 8(%rsp)
	movl	$166, (%rsp)
	movl	$1680, %ecx             # imm = 0x690
	movl	$264, %r8d              # imm = 0x108
	movl	$1944, %r9d             # imm = 0x798
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movq	%rbx, %r15
	movq	176(%rsp), %r12
	movq	%r12, %rdx
	callq	run_create_block_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2112, %esi             # imm = 0x840
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB15_1
# BB#12:                                # %entry_ifend66
	movq	$0, (%r14)
	movq	64(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r14)
	movq	$0, 8(%r14)
	movq	56(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%r14)
	movq	%rbp, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$13, %esi
	movq	%rax, %rdi
	movq	%r15, %rbp
	movq	%rbp, %rdx
	movl	100(%rsp), %ecx         # 4-byte Reload
	movq	%r8, %r15
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r13, %rdi
	je	.LBB15_14
# BB#13:                                # %then_block79
	callq	get_try_catch_label_name
.LBB15_1:                               # %then_block
	xorl	%eax, %eax
.LBB15_2:                               # %then_block
	addq	$120, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB15_14:                              # %entry_ifend80
	movq	(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	8(%rbp), %rbx
	movq	$0, 112(%rsp)
	movq	%rbx, 112(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$0, gSigInt(%rip)
	movl	%ebx, %eax
	movq	%rax, (%rbp)
	movl	$1, %eax
	jmp	.LBB15_2
.Lfunc_end15:
	.size	"stat.userName()$$17", .Lfunc_end15-"stat.userName()$$17"
	.cfi_endproc

	.globl	"stat.groupName()$$18"
	.align	16, 0x90
	.type	"stat.groupName()$$18",@function
"stat.groupName()$$18":                 # @"stat.groupName()$$18"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp178:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp179:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp180:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp181:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp182:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp183:
	.cfi_def_cfa_offset 56
	subq	$120, %rsp
.Ltmp184:
	.cfi_def_cfa_offset 176
.Ltmp185:
	.cfi_offset %rbx, -56
.Ltmp186:
	.cfi_offset %r12, -48
.Ltmp187:
	.cfi_offset %r13, -40
.Ltmp188:
	.cfi_offset %r14, -32
.Ltmp189:
	.cfi_offset %r15, -24
.Ltmp190:
	.cfi_offset %rbp, -16
	movl	%r9d, 100(%rsp)         # 4-byte Spill
	movq	%r8, 80(%rsp)           # 8-byte Spill
	movq	%rcx, 88(%rsp)          # 8-byte Spill
	movq	%rdx, %r14
	movq	%rsi, %rbp
	movq	176(%rsp), %r13
	movq	(%rcx), %r12
	movq	$0, 104(%rsp)
	movq	%r12, 104(%rsp)
	movq	$0, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.4, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movq	$0, 112(%rsp)
	movl	%ebx, %r15d
	movq	%r15, 112(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string.5, %edi
	callq	create_path_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2144, %esi             # imm = 0x860
	movq	%r13, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB16_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%r12, (%rbp)
	movq	$0, 8(%rbp)
	movq	%r15, 8(%rbp)
	movq	%rbp, 72(%rsp)          # 8-byte Spill
	movq	80(%rsp), %r15          # 8-byte Reload
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$9, %esi
	movq	%rax, %rdi
	movq	88(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	100(%rsp), %ecx         # 4-byte Reload
	movq	%r15, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB16_5
# BB#4:                                 # %then_block6
	movq	%r14, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB16_1
.LBB16_5:                               # %entry_ifend7
	movq	(%rbx), %r13
	movq	$0, 104(%rsp)
	movq	%r13, 104(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 112(%rsp)
	movq	%r12, 112(%rsp)
	movq	%r15, %rbp
	movq	(%rbp), %rax
	movq	%r14, %r15
	movq	-8(%rax), %rbx
	movl	%ebx, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$2152, %esi             # imm = 0x868
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	movq	72(%rsp), %r14          # 8-byte Reload
	je	.LBB16_1
# BB#6:                                 # %entry_ifend15
	movq	$0, (%r14)
	movq	%r13, (%r14)
	movq	$0, 8(%r14)
	movq	%r12, 8(%r14)
	movq	%rbp, %r12
	movq	(%r12), %rcx
	movq	$0, (%rcx)
	movq	%rbx, (%rcx)
	addq	$8, (%r12)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	88(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	100(%rsp), %ecx         # 4-byte Reload
	movq	%r12, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB16_8
# BB#7:                                 # %then_block25
	movq	%r15, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB16_1
.LBB16_8:                               # %entry_ifend26
	movq	(%rbx), %rax
	movq	%rax, 64(%rsp)          # 8-byte Spill
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	8(%rbx), %rax
	movq	%rax, 56(%rsp)          # 8-byte Spill
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	%r12, %rbp
	movq	(%rbp), %rax
	movq	-8(%rax), %r12
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%rbp)
	movl	$0, 16(%rsp)
	movl	$0, 8(%rsp)
	movl	$0, (%rsp)
	movl	$.Lglobal_string.6, %edi
	xorl	%esi, %esi
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	xorl	%r8d, %r8d
	xorl	%r9d, %r9d
	callq	create_regex_object
	movq	%r15, %r13
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2164, %esi             # imm = 0x874
	movq	176(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB16_1
# BB#9:                                 # %entry_ifend39
	movq	$0, (%r14)
	movq	64(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r14)
	movq	$0, 8(%r14)
	movq	56(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%r14)
	movq	%rbp, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	%r12, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$30, %esi
	movq	%rax, %rdi
	movq	88(%rsp), %rbx          # 8-byte Reload
	movq	%rbx, %rdx
	movl	100(%rsp), %ecx         # 4-byte Reload
	movq	%r8, %r15
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB16_11
# BB#10:                                # %then_block52
	movq	%r13, %rdi
	callq	get_try_catch_label_name
	jmp	.LBB16_1
.LBB16_11:                              # %entry_ifend53
	movq	(%rbx), %rax
	movq	%rax, 64(%rsp)          # 8-byte Spill
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	8(%rbx), %rax
	movq	%rax, 56(%rsp)          # 8-byte Spill
	movq	$0, 112(%rsp)
	movq	%rax, 112(%rsp)
	movq	%r15, %rbp
	movq	(%rbp), %rax
	movq	-8(%rax), %rdi
	movq	%rdi, 48(%rsp)          # 8-byte Spill
	callq	push_jit_object
	addq	$-8, (%rbp)
	movq	%r13, 32(%rsp)
	movl	$0, 24(%rsp)
	movl	$2, 16(%rsp)
	movl	$2, 8(%rsp)
	movl	$166, (%rsp)
	movl	$2172, %ecx             # imm = 0x87C
	movl	$264, %r8d              # imm = 0x108
	movl	$2436, %r9d             # imm = 0x984
	movq	%rbp, %rdi
	movq	%rbx, %rsi
	movq	%rbx, %r15
	movq	176(%rsp), %r12
	movq	%r12, %rdx
	callq	run_create_block_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movl	$2604, %esi             # imm = 0xA2C
	movq	%r12, %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB16_1
# BB#12:                                # %entry_ifend66
	movq	$0, (%r14)
	movq	64(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, (%r14)
	movq	$0, 8(%r14)
	movq	56(%rsp), %rcx          # 8-byte Reload
	movq	%rcx, 8(%r14)
	movq	%rbp, %r8
	movq	(%r8), %rcx
	movq	$0, (%rcx)
	movq	48(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r8), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r8)
	movq	$0, 8(%rcx)
	movl	%ebx, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r8)
	movl	$13, %esi
	movq	%rax, %rdi
	movq	%r15, %rbp
	movq	%rbp, %rdx
	movl	100(%rsp), %ecx         # 4-byte Reload
	movq	%r8, %r15
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r13, %rdi
	je	.LBB16_14
# BB#13:                                # %then_block79
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
.LBB16_14:                              # %entry_ifend80
	movq	(%rbp), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 104(%rsp)
	movq	8(%rbp), %rbx
	movq	$0, 112(%rsp)
	movq	%rbx, 112(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	$0, gSigInt(%rip)
	movl	%ebx, %eax
	movq	%rax, (%rbp)
	movl	$1, %eax
	jmp	.LBB16_2
.Lfunc_end16:
	.size	"stat.groupName()$$18", .Lfunc_end16-"stat.groupName()$$18"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.zero	1
	.size	.Lglobal_string, 1

	.type	.Lglobal_string.2,@object # @global_string.2
.Lglobal_string.2:
	.asciz	"/etc/passwd"
	.size	.Lglobal_string.2, 12

	.type	.Lglobal_string.3,@object # @global_string.3
.Lglobal_string.3:
	.asciz	"\\n"
	.size	.Lglobal_string.3, 3

	.type	.Lglobal_string.4,@object # @global_string.4
.Lglobal_string.4:
	.zero	1
	.size	.Lglobal_string.4, 1

	.type	.Lglobal_string.5,@object # @global_string.5
.Lglobal_string.5:
	.asciz	"/etc/group"
	.size	.Lglobal_string.5, 11

	.type	.Lglobal_string.6,@object # @global_string.6
.Lglobal_string.6:
	.asciz	"\\n"
	.size	.Lglobal_string.6, 3


	.section	".note.GNU-stack","",@progbits
