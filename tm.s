	.text
	.file	"tm.bc"
	.globl	"tm.second()$$3"
	.align	16, 0x90
	.type	"tm.second()$$3",@function
"tm.second()$$3":                       # @"tm.second()$$3"
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
	.size	"tm.second()$$3", .Lfunc_end0-"tm.second()$$3"
	.cfi_endproc

	.globl	"tm.setSecond(int)$$4"
	.align	16, 0x90
	.type	"tm.setSecond(int)$$4",@function
"tm.setSecond(int)$$4":                 # @"tm.setSecond(int)$$4"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp3:
	.cfi_def_cfa_offset 16
	subq	$32, %rsp
.Ltmp4:
	.cfi_def_cfa_offset 48
.Ltmp5:
	.cfi_offset %rbx, -16
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%rbx), %rdx
	movq	$0, 24(%rsp)
	movq	%rdx, 24(%rsp)
	movl	$0, gSigInt(%rip)
	movl	%edx, %r10d
	movl	$0, (%rsp)
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r9d, %edx
	movl	%eax, %r8d
	movq	%r10, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB1_2
.LBB1_1:                                # %then_block
	xorl	%eax, %eax
.LBB1_2:                                # %then_block
	addq	$32, %rsp
	popq	%rbx
	retq
.Lfunc_end1:
	.size	"tm.setSecond(int)$$4", .Lfunc_end1-"tm.setSecond(int)$$4"
	.cfi_endproc

	.globl	"tm.minuts()$$5"
	.align	16, 0x90
	.type	"tm.minuts()$$5",@function
"tm.minuts()$$5":                       # @"tm.minuts()$$5"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp6:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp7:
	.cfi_def_cfa_offset 32
.Ltmp8:
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
	je	.LBB2_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB2_2
.LBB2_1:                                # %then_block
	xorl	%eax, %eax
.LBB2_2:                                # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end2:
	.size	"tm.minuts()$$5", .Lfunc_end2-"tm.minuts()$$5"
	.cfi_endproc

	.globl	"tm.setMinuts(int)$$6"
	.align	16, 0x90
	.type	"tm.setMinuts(int)$$6",@function
"tm.setMinuts(int)$$6":                 # @"tm.setMinuts(int)$$6"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp9:
	.cfi_def_cfa_offset 16
	subq	$32, %rsp
.Ltmp10:
	.cfi_def_cfa_offset 48
.Ltmp11:
	.cfi_offset %rbx, -16
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%rbx), %rdx
	movq	$0, 24(%rsp)
	movq	%rdx, 24(%rsp)
	movl	$0, gSigInt(%rip)
	movl	%edx, %r10d
	movl	$1, (%rsp)
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r9d, %edx
	movl	%eax, %r8d
	movq	%r10, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB3_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB3_2
.LBB3_1:                                # %then_block
	xorl	%eax, %eax
.LBB3_2:                                # %then_block
	addq	$32, %rsp
	popq	%rbx
	retq
.Lfunc_end3:
	.size	"tm.setMinuts(int)$$6", .Lfunc_end3-"tm.setMinuts(int)$$6"
	.cfi_endproc

	.globl	"tm.hour()$$7"
	.align	16, 0x90
	.type	"tm.hour()$$7",@function
"tm.hour()$$7":                         # @"tm.hour()$$7"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp12:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp13:
	.cfi_def_cfa_offset 32
.Ltmp14:
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
	je	.LBB4_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB4_2
.LBB4_1:                                # %then_block
	xorl	%eax, %eax
.LBB4_2:                                # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end4:
	.size	"tm.hour()$$7", .Lfunc_end4-"tm.hour()$$7"
	.cfi_endproc

	.globl	"tm.setHour(int)$$8"
	.align	16, 0x90
	.type	"tm.setHour(int)$$8",@function
"tm.setHour(int)$$8":                   # @"tm.setHour(int)$$8"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp15:
	.cfi_def_cfa_offset 16
	subq	$32, %rsp
.Ltmp16:
	.cfi_def_cfa_offset 48
.Ltmp17:
	.cfi_offset %rbx, -16
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%rbx), %rdx
	movq	$0, 24(%rsp)
	movq	%rdx, 24(%rsp)
	movl	$0, gSigInt(%rip)
	movl	%edx, %r10d
	movl	$2, (%rsp)
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r9d, %edx
	movl	%eax, %r8d
	movq	%r10, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB5_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB5_2
.LBB5_1:                                # %then_block
	xorl	%eax, %eax
.LBB5_2:                                # %then_block
	addq	$32, %rsp
	popq	%rbx
	retq
.Lfunc_end5:
	.size	"tm.setHour(int)$$8", .Lfunc_end5-"tm.setHour(int)$$8"
	.cfi_endproc

	.globl	"tm.dayOfMonth()$$9"
	.align	16, 0x90
	.type	"tm.dayOfMonth()$$9",@function
"tm.dayOfMonth()$$9":                   # @"tm.dayOfMonth()$$9"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp18:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp19:
	.cfi_def_cfa_offset 32
.Ltmp20:
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
	je	.LBB6_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB6_2
.LBB6_1:                                # %then_block
	xorl	%eax, %eax
.LBB6_2:                                # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end6:
	.size	"tm.dayOfMonth()$$9", .Lfunc_end6-"tm.dayOfMonth()$$9"
	.cfi_endproc

	.globl	"tm.setDayOfMonth(int)$$10"
	.align	16, 0x90
	.type	"tm.setDayOfMonth(int)$$10",@function
"tm.setDayOfMonth(int)$$10":            # @"tm.setDayOfMonth(int)$$10"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp21:
	.cfi_def_cfa_offset 16
	subq	$32, %rsp
.Ltmp22:
	.cfi_def_cfa_offset 48
.Ltmp23:
	.cfi_offset %rbx, -16
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%rbx), %rdx
	movq	$0, 24(%rsp)
	movq	%rdx, 24(%rsp)
	movl	$0, gSigInt(%rip)
	movl	%edx, %r10d
	movl	$3, (%rsp)
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r9d, %edx
	movl	%eax, %r8d
	movq	%r10, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB7_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB7_2
.LBB7_1:                                # %then_block
	xorl	%eax, %eax
.LBB7_2:                                # %then_block
	addq	$32, %rsp
	popq	%rbx
	retq
.Lfunc_end7:
	.size	"tm.setDayOfMonth(int)$$10", .Lfunc_end7-"tm.setDayOfMonth(int)$$10"
	.cfi_endproc

	.globl	"tm.month()$$11"
	.align	16, 0x90
	.type	"tm.month()$$11",@function
"tm.month()$$11":                       # @"tm.month()$$11"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp24:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp25:
	.cfi_def_cfa_offset 32
.Ltmp26:
	.cfi_offset %rbx, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$4, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	incl	%eax
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
	.size	"tm.month()$$11", .Lfunc_end8-"tm.month()$$11"
	.cfi_endproc

	.globl	"tm.setMonth(int)$$12"
	.align	16, 0x90
	.type	"tm.setMonth(int)$$12",@function
"tm.setMonth(int)$$12":                 # @"tm.setMonth(int)$$12"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp27:
	.cfi_def_cfa_offset 16
	subq	$32, %rsp
.Ltmp28:
	.cfi_def_cfa_offset 48
.Ltmp29:
	.cfi_offset %rbx, -16
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %r10
	movq	$0, 16(%rsp)
	movq	%r10, 16(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movl	$0, gSigInt(%rip)
	decl	%eax
	movl	$4, (%rsp)
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r9d, %edx
	movl	%r10d, %r8d
	movq	%rax, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB9_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB9_2
.LBB9_1:                                # %then_block
	xorl	%eax, %eax
.LBB9_2:                                # %then_block
	addq	$32, %rsp
	popq	%rbx
	retq
.Lfunc_end9:
	.size	"tm.setMonth(int)$$12", .Lfunc_end9-"tm.setMonth(int)$$12"
	.cfi_endproc

	.globl	"tm.year()$$13"
	.align	16, 0x90
	.type	"tm.year()$$13",@function
"tm.year()$$13":                        # @"tm.year()$$13"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp30:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp31:
	.cfi_def_cfa_offset 32
.Ltmp32:
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
	je	.LBB10_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	addl	$1900, %eax             # imm = 0x76C
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB10_2
.LBB10_1:                               # %then_block
	xorl	%eax, %eax
.LBB10_2:                               # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end10:
	.size	"tm.year()$$13", .Lfunc_end10-"tm.year()$$13"
	.cfi_endproc

	.globl	"tm.setYear(int)$$14"
	.align	16, 0x90
	.type	"tm.setYear(int)$$14",@function
"tm.setYear(int)$$14":                  # @"tm.setYear(int)$$14"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp33:
	.cfi_def_cfa_offset 16
	subq	$32, %rsp
.Ltmp34:
	.cfi_def_cfa_offset 48
.Ltmp35:
	.cfi_offset %rbx, -16
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %r10
	movq	$0, 16(%rsp)
	movq	%r10, 16(%rsp)
	movq	8(%rbx), %rax
	movq	$0, 24(%rsp)
	movq	%rax, 24(%rsp)
	movl	$0, gSigInt(%rip)
	addl	$-1900, %eax            # imm = 0xFFFFFFFFFFFFF894
	movl	$5, (%rsp)
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r9d, %edx
	movl	%r10d, %r8d
	movq	%rax, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB11_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB11_2
.LBB11_1:                               # %then_block
	xorl	%eax, %eax
.LBB11_2:                               # %then_block
	addq	$32, %rsp
	popq	%rbx
	retq
.Lfunc_end11:
	.size	"tm.setYear(int)$$14", .Lfunc_end11-"tm.setYear(int)$$14"
	.cfi_endproc

	.globl	"tm.dayOfWeek()$$15"
	.align	16, 0x90
	.type	"tm.dayOfWeek()$$15",@function
"tm.dayOfWeek()$$15":                   # @"tm.dayOfWeek()$$15"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp36:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp37:
	.cfi_def_cfa_offset 32
.Ltmp38:
	.cfi_offset %rbx, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$6, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB12_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %eax
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
	.size	"tm.dayOfWeek()$$15", .Lfunc_end12-"tm.dayOfWeek()$$15"
	.cfi_endproc

	.globl	"tm.setDayOfWeek(int)$$16"
	.align	16, 0x90
	.type	"tm.setDayOfWeek(int)$$16",@function
"tm.setDayOfWeek(int)$$16":             # @"tm.setDayOfWeek(int)$$16"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp39:
	.cfi_def_cfa_offset 16
	subq	$32, %rsp
.Ltmp40:
	.cfi_def_cfa_offset 48
.Ltmp41:
	.cfi_offset %rbx, -16
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%rbx), %rdx
	movq	$0, 24(%rsp)
	movq	%rdx, 24(%rsp)
	movl	$0, gSigInt(%rip)
	movl	%edx, %r10d
	movl	$6, (%rsp)
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r9d, %edx
	movl	%eax, %r8d
	movq	%r10, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB13_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB13_2
.LBB13_1:                               # %then_block
	xorl	%eax, %eax
.LBB13_2:                               # %then_block
	addq	$32, %rsp
	popq	%rbx
	retq
.Lfunc_end13:
	.size	"tm.setDayOfWeek(int)$$16", .Lfunc_end13-"tm.setDayOfWeek(int)$$16"
	.cfi_endproc

	.globl	"tm.dayOfYear()$$17"
	.align	16, 0x90
	.type	"tm.dayOfYear()$$17",@function
"tm.dayOfYear()$$17":                   # @"tm.dayOfYear()$$17"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp42:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp43:
	.cfi_def_cfa_offset 32
.Ltmp44:
	.cfi_offset %rbx, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$7, %r9d
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
	.size	"tm.dayOfYear()$$17", .Lfunc_end14-"tm.dayOfYear()$$17"
	.cfi_endproc

	.globl	"tm.setDayOfYear(int)$$18"
	.align	16, 0x90
	.type	"tm.setDayOfYear(int)$$18",@function
"tm.setDayOfYear(int)$$18":             # @"tm.setDayOfYear(int)$$18"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp45:
	.cfi_def_cfa_offset 16
	subq	$32, %rsp
.Ltmp46:
	.cfi_def_cfa_offset 48
.Ltmp47:
	.cfi_offset %rbx, -16
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%rbx), %rdx
	movq	$0, 24(%rsp)
	movq	%rdx, 24(%rsp)
	movl	$0, gSigInt(%rip)
	movl	%edx, %r10d
	movl	$7, (%rsp)
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r9d, %edx
	movl	%eax, %r8d
	movq	%r10, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB15_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB15_2
.LBB15_1:                               # %then_block
	xorl	%eax, %eax
.LBB15_2:                               # %then_block
	addq	$32, %rsp
	popq	%rbx
	retq
.Lfunc_end15:
	.size	"tm.setDayOfYear(int)$$18", .Lfunc_end15-"tm.setDayOfYear(int)$$18"
	.cfi_endproc

	.globl	"tm.isDaylightSavingTime()$$19"
	.align	16, 0x90
	.type	"tm.isDaylightSavingTime()$$19",@function
"tm.isDaylightSavingTime()$$19":        # @"tm.isDaylightSavingTime()$$19"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp48:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp49:
	.cfi_def_cfa_offset 32
.Ltmp50:
	.cfi_offset %rbx, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$8, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB16_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB16_2
.LBB16_1:                               # %then_block
	xorl	%eax, %eax
.LBB16_2:                               # %then_block
	addq	$16, %rsp
	popq	%rbx
	retq
.Lfunc_end16:
	.size	"tm.isDaylightSavingTime()$$19", .Lfunc_end16-"tm.isDaylightSavingTime()$$19"
	.cfi_endproc

	.globl	"tm.setDaylightSavingTime(bool)$$20"
	.align	16, 0x90
	.type	"tm.setDaylightSavingTime(bool)$$20",@function
"tm.setDaylightSavingTime(bool)$$20":   # @"tm.setDaylightSavingTime(bool)$$20"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp51:
	.cfi_def_cfa_offset 16
	subq	$32, %rsp
.Ltmp52:
	.cfi_def_cfa_offset 48
.Ltmp53:
	.cfi_offset %rbx, -16
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	8(%rbx), %rdx
	movq	$0, 24(%rsp)
	movq	%rdx, 24(%rsp)
	movl	$0, gSigInt(%rip)
	movl	%edx, %r10d
	movl	$8, (%rsp)
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r9d, %edx
	movl	%eax, %r8d
	movq	%r10, %r9
	callq	store_field
	testl	%eax, %eax
	je	.LBB17_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB17_2
.LBB17_1:                               # %then_block
	xorl	%eax, %eax
.LBB17_2:                               # %then_block
	addq	$32, %rsp
	popq	%rbx
	retq
.Lfunc_end17:
	.size	"tm.setDaylightSavingTime(bool)$$20", .Lfunc_end17-"tm.setDaylightSavingTime(bool)$$20"
	.cfi_endproc

	.globl	"tm.toString()$$21"
	.align	16, 0x90
	.type	"tm.toString()$$21",@function
"tm.toString()$$21":                    # @"tm.toString()$$21"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp54:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp55:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp56:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp57:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp58:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp59:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp60:
	.cfi_def_cfa_offset 112
.Ltmp61:
	.cfi_offset %rbx, -56
.Ltmp62:
	.cfi_offset %r12, -48
.Ltmp63:
	.cfi_offset %r13, -40
.Ltmp64:
	.cfi_offset %r14, -32
.Ltmp65:
	.cfi_offset %r15, -24
.Ltmp66:
	.cfi_offset %rbp, -16
	movl	%r9d, 36(%rsp)          # 4-byte Spill
	movq	%r8, %r12
	movq	%rcx, 40(%rsp)          # 8-byte Spill
	movq	%rdx, %rbx
	movq	%rsi, %r14
	movq	112(%rsp), %r13
	movq	(%rcx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, 32(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	48(%rsp), %ebp
	movl	$1736, %esi             # imm = 0x6C8
	movq	%r13, %rdi
	movq	%r12, %r15
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#3:                                 # %entry_ifend
	movq	48(%rsp), %rcx
	movq	$0, (%r14)
	movq	%rcx, (%r14)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$13, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	36(%rsp), %ebp          # 4-byte Reload
	movl	%ebp, %ecx
	movq	%r15, %r8
	movq	%rbx, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%rbx, %r13
	jne	.LBB18_4
# BB#5:                                 # %entry_ifend6
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movl	%ebp, %ebx
	movl	-8(%rax), %r12d
	movl	%r12d, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	%r12d, %edi
	movl	%ebx, %r12d
	callq	create_integer
	movl	%eax, 28(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	48(%rsp), %ebp
	movl	$1740, %esi             # imm = 0x6CC
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#6:                                 # %entry_ifend14
	movq	48(%rsp), %rcx
	movq	$0, (%r14)
	movq	%rcx, (%r14)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$11, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r12d, %ecx
	movq	%r15, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r14, %rbx
	jne	.LBB18_4
# BB#7:                                 # %entry_ifend23
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	%ebp, %edi
	callq	create_integer
	movl	%eax, 24(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	48(%rsp), %ebp
	movl	$1744, %esi             # imm = 0x6D0
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#8:                                 # %entry_ifend35
	movq	48(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$9, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r12d, %ecx
	movq	%r15, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB18_4
# BB#9:                                 # %entry_ifend44
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	%ebp, %edi
	callq	create_integer
	movl	%eax, 20(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	48(%rsp), %ebp
	movl	$1748, %esi             # imm = 0x6D4
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#10:                                # %entry_ifend56
	movq	48(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$7, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r12d, %ecx
	movq	%r15, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB18_11
.LBB18_4:                               # %then_block5
	movq	%r13, %rdi
	callq	get_try_catch_label_name
.LBB18_1:                               # %then_block
	xorl	%eax, %eax
.LBB18_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB18_11:                              # %entry_ifend65
	movq	40(%rsp), %rax          # 8-byte Reload
	movq	(%rax), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	%ebp, %edi
	callq	create_integer
	movl	%eax, 16(%rsp)          # 4-byte Spill
	movl	%eax, %edi
	callq	push_jit_object
	movl	48(%rsp), %ebp
	movl	$1752, %esi             # imm = 0x6D8
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#12:                                # %entry_ifend77
	movq	48(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r15)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	40(%rsp), %rdx          # 8-byte Reload
	movl	%r12d, %ecx
	movq	%r15, %r8
	movq	%r13, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r13, %rdi
	je	.LBB18_14
# BB#13:                                # %then_block85
	callq	get_try_catch_label_name
	jmp	.LBB18_1
.LBB18_14:                              # %entry_ifend86
	movq	40(%rsp), %r13          # 8-byte Reload
	movq	(%r13), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	%rdi, %r14
	movl	-8(%rax), %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movl	%ebp, %edi
	callq	create_integer
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movq	(%r15), %rax
	movq	$0, (%rax)
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%rcx, (%rax)
	movq	(%r15), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r15)
	movq	$0, 8(%rax)
	movl	24(%rsp), %ecx          # 4-byte Reload
	movq	%rcx, 8(%rax)
	movq	(%r15), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r15)
	movq	$0, 8(%rax)
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%rcx, 8(%rax)
	movq	(%r15), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r15)
	movq	$0, 8(%rax)
	movl	16(%rsp), %ecx          # 4-byte Reload
	movq	%rcx, 8(%rax)
	movq	(%r15), %rax
	leaq	8(%rax), %rcx
	movq	%rcx, (%r15)
	movq	$0, 8(%rax)
	movl	%ebp, %ecx
	movq	%rcx, 8(%rax)
	addq	$8, (%r15)
	movq	112(%rsp), %rax
	movq	%rax, (%rsp)
	movl	$5, %r8d
	movl	$1756, %r9d             # imm = 0x6DC
	movq	%r15, %rdi
	movq	%r13, %rsi
	movl	%r12d, %edx
	movq	%r14, %rcx
	callq	run_create_carray
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#15:                                # %entry_ifend112
	movq	(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1764, %esi             # imm = 0x6E4
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
# BB#16:                                # %entry_ifend115
	movq	48(%rsp), %rcx
	movq	$0, (%rbx)
	movq	%rcx, (%rbx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	32(%rsp), %edx          # 4-byte Reload
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	addq	$8, (%r15)
	movl	$24, %esi
	movq	%rax, %rdi
	movq	%r13, %rdx
	movl	%r12d, %ecx
	movq	%r15, %r8
	movq	%r14, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	movq	%r14, %rdi
	je	.LBB18_18
# BB#17:                                # %then_block126
	callq	get_try_catch_label_name
	jmp	.LBB18_1
.LBB18_18:                              # %entry_ifend127
	movq	%r13, %rbx
	movq	(%rbx), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r15), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	movq	%rbp, (%rbx)
	movl	$1, %eax
	jmp	.LBB18_2
.Lfunc_end18:
	.size	"tm.toString()$$21", .Lfunc_end18-"tm.toString()$$21"
	.cfi_endproc

	.globl	"tm.to_time_t()$$22"
	.align	16, 0x90
	.type	"tm.to_time_t()$$22",@function
"tm.to_time_t()$$22":                   # @"tm.to_time_t()$$22"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp67:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp68:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp69:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp70:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp71:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp72:
	.cfi_def_cfa_offset 56
	pushq	%rax
.Ltmp73:
	.cfi_def_cfa_offset 64
.Ltmp74:
	.cfi_offset %rbx, -56
.Ltmp75:
	.cfi_offset %r12, -48
.Ltmp76:
	.cfi_offset %r13, -40
.Ltmp77:
	.cfi_offset %r14, -32
.Ltmp78:
	.cfi_offset %r15, -24
.Ltmp79:
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
	movl	$1772, %esi             # imm = 0x6EC
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB19_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%ebx, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%r13)
	movl	$45, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB19_5
# BB#4:                                 # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB19_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB19_2
.LBB19_5:                               # %entry_ifend6
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
.LBB19_2:                               # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end19:
	.size	"tm.to_time_t()$$22", .Lfunc_end19-"tm.to_time_t()$$22"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"%d-%02d-%02d %02d:%02d"
	.size	.Lglobal_string, 23


	.section	".note.GNU-stack","",@progbits
