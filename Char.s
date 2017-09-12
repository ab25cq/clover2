	.text
	.file	"Char.bc"
	.globl	"Char.toByte()$$0"
	.align	16, 0x90
	.type	"Char.toByte()$$0",@function
"Char.toByte()$$0":                     # @"Char.toByte()$$0"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp0:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp1:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp2:
	.cfi_def_cfa_offset 32
.Ltmp3:
	.cfi_offset %rbx, -24
.Ltmp4:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
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
	movq	(%rax), %rdi
	callq	create_byte
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB0_2
.LBB0_1:                                # %then_block
	xorl	%eax, %eax
.LBB0_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end0:
	.size	"Char.toByte()$$0", .Lfunc_end0-"Char.toByte()$$0"
	.cfi_endproc

	.globl	"Char.toUByte()$$1"
	.align	16, 0x90
	.type	"Char.toUByte()$$1",@function
"Char.toUByte()$$1":                    # @"Char.toUByte()$$1"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp5:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp6:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp7:
	.cfi_def_cfa_offset 32
.Ltmp8:
	.cfi_offset %rbx, -24
.Ltmp9:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB1_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	create_ubyte
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB1_2
.LBB1_1:                                # %then_block
	xorl	%eax, %eax
.LBB1_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end1:
	.size	"Char.toUByte()$$1", .Lfunc_end1-"Char.toUByte()$$1"
	.cfi_endproc

	.globl	"Char.toShort()$$2"
	.align	16, 0x90
	.type	"Char.toShort()$$2",@function
"Char.toShort()$$2":                    # @"Char.toShort()$$2"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp10:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp11:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp12:
	.cfi_def_cfa_offset 32
.Ltmp13:
	.cfi_offset %rbx, -24
.Ltmp14:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB2_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	create_short
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB2_2
.LBB2_1:                                # %then_block
	xorl	%eax, %eax
.LBB2_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end2:
	.size	"Char.toShort()$$2", .Lfunc_end2-"Char.toShort()$$2"
	.cfi_endproc

	.globl	"Char.toUShort()$$3"
	.align	16, 0x90
	.type	"Char.toUShort()$$3",@function
"Char.toUShort()$$3":                   # @"Char.toUShort()$$3"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp15:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp16:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp17:
	.cfi_def_cfa_offset 32
.Ltmp18:
	.cfi_offset %rbx, -24
.Ltmp19:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB3_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	create_ushort
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB3_2
.LBB3_1:                                # %then_block
	xorl	%eax, %eax
.LBB3_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end3:
	.size	"Char.toUShort()$$3", .Lfunc_end3-"Char.toUShort()$$3"
	.cfi_endproc

	.globl	"Char.toInteger()$$4"
	.align	16, 0x90
	.type	"Char.toInteger()$$4",@function
"Char.toInteger()$$4":                  # @"Char.toInteger()$$4"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp20:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp21:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp22:
	.cfi_def_cfa_offset 32
.Ltmp23:
	.cfi_offset %rbx, -24
.Ltmp24:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB4_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	create_integer
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB4_2
.LBB4_1:                                # %then_block
	xorl	%eax, %eax
.LBB4_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end4:
	.size	"Char.toInteger()$$4", .Lfunc_end4-"Char.toInteger()$$4"
	.cfi_endproc

	.globl	"Char.toUInteger()$$5"
	.align	16, 0x90
	.type	"Char.toUInteger()$$5",@function
"Char.toUInteger()$$5":                 # @"Char.toUInteger()$$5"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp25:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp26:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp27:
	.cfi_def_cfa_offset 32
.Ltmp28:
	.cfi_offset %rbx, -24
.Ltmp29:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB5_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	create_uinteger
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB5_2
.LBB5_1:                                # %then_block
	xorl	%eax, %eax
.LBB5_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end5:
	.size	"Char.toUInteger()$$5", .Lfunc_end5-"Char.toUInteger()$$5"
	.cfi_endproc

	.globl	"Char.toLong()$$6"
	.align	16, 0x90
	.type	"Char.toLong()$$6",@function
"Char.toLong()$$6":                     # @"Char.toLong()$$6"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp30:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp31:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp32:
	.cfi_def_cfa_offset 32
.Ltmp33:
	.cfi_offset %rbx, -24
.Ltmp34:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB6_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %edi
	callq	create_long
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB6_2
.LBB6_1:                                # %then_block
	xorl	%eax, %eax
.LBB6_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end6:
	.size	"Char.toLong()$$6", .Lfunc_end6-"Char.toLong()$$6"
	.cfi_endproc

	.globl	"Char.toULong()$$7"
	.align	16, 0x90
	.type	"Char.toULong()$$7",@function
"Char.toULong()$$7":                    # @"Char.toULong()$$7"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp35:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp36:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp37:
	.cfi_def_cfa_offset 32
.Ltmp38:
	.cfi_offset %rbx, -24
.Ltmp39:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
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
	movl	%eax, %edi
	callq	create_ulong
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB7_2
.LBB7_1:                                # %then_block
	xorl	%eax, %eax
.LBB7_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end7:
	.size	"Char.toULong()$$7", .Lfunc_end7-"Char.toULong()$$7"
	.cfi_endproc

	.globl	"Char.toChar()$$8"
	.align	16, 0x90
	.type	"Char.toChar()$$8",@function
"Char.toChar()$$8":                     # @"Char.toChar()$$8"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp40:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp41:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp42:
	.cfi_def_cfa_offset 32
.Ltmp43:
	.cfi_offset %rbx, -24
.Ltmp44:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB8_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	create_char
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB8_2
.LBB8_1:                                # %then_block
	xorl	%eax, %eax
.LBB8_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end8:
	.size	"Char.toChar()$$8", .Lfunc_end8-"Char.toChar()$$8"
	.cfi_endproc

	.globl	"Char.toBool()$$9"
	.align	16, 0x90
	.type	"Char.toBool()$$9",@function
"Char.toBool()$$9":                     # @"Char.toBool()$$9"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp45:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp46:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp47:
	.cfi_def_cfa_offset 32
.Ltmp48:
	.cfi_offset %rbx, -24
.Ltmp49:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB9_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	create_bool
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB9_2
.LBB9_1:                                # %then_block
	xorl	%eax, %eax
.LBB9_2:                                # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end9:
	.size	"Char.toBool()$$9", .Lfunc_end9-"Char.toBool()$$9"
	.cfi_endproc

	.globl	"Char.toString()$$10"
	.align	16, 0x90
	.type	"Char.toString()$$10",@function
"Char.toString()$$10":                  # @"Char.toString()$$10"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp50:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp51:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp52:
	.cfi_def_cfa_offset 32
.Ltmp53:
	.cfi_offset %rbx, -24
.Ltmp54:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB10_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rdi
	callq	run_char_to_string_cast
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB10_2
.LBB10_1:                               # %then_block
	xorl	%eax, %eax
.LBB10_2:                               # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end10:
	.size	"Char.toString()$$10", .Lfunc_end10-"Char.toString()$$10"
	.cfi_endproc

	.globl	"Char.equals(Self)$$11"
	.align	16, 0x90
	.type	"Char.equals(Self)$$11",@function
"Char.equals(Self)$$11":                # @"Char.equals(Self)$$11"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp55:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp56:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp57:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp58:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp59:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp60:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp61:
	.cfi_def_cfa_offset 80
.Ltmp62:
	.cfi_offset %rbx, -56
.Ltmp63:
	.cfi_offset %r12, -48
.Ltmp64:
	.cfi_offset %r13, -40
.Ltmp65:
	.cfi_offset %r14, -32
.Ltmp66:
	.cfi_offset %r15, -24
.Ltmp67:
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
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %r13
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB11_1
# BB#4:                                 # %entry_ifend5
	movq	(%rax), %rax
	cmpl	%eax, %r13d
	sete	%al
	movzbl	%al, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB11_2
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
.Lfunc_end11:
	.size	"Char.equals(Self)$$11", .Lfunc_end11-"Char.equals(Self)$$11"
	.cfi_endproc

	.globl	"Char.compare(Self)$$12"
	.align	16, 0x90
	.type	"Char.compare(Self)$$12",@function
"Char.compare(Self)$$12":               # @"Char.compare(Self)$$12"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp68:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp69:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp70:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp71:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp72:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp73:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp74:
	.cfi_def_cfa_offset 80
.Ltmp75:
	.cfi_offset %rbx, -56
.Ltmp76:
	.cfi_offset %r12, -48
.Ltmp77:
	.cfi_offset %r13, -40
.Ltmp78:
	.cfi_offset %r14, -32
.Ltmp79:
	.cfi_offset %r15, -24
.Ltmp80:
	.cfi_offset %rbp, -16
	movl	%r9d, %r14d
	movq	%r8, %r15
	movq	%rcx, %rbx
	movq	%rdx, %r13
	movq	(%rbx), %rbp
	movq	$0, 8(%rsp)
	movq	%rbp, 8(%rsp)
	movq	8(%rbx), %r12
	movq	$0, 16(%rsp)
	movq	%r12, 16(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB12_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movq	%rax, (%rsp)            # 8-byte Spill
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB12_1
# BB#4:                                 # %entry_ifend5
	movq	(%rax), %rax
	movq	(%rsp), %rcx            # 8-byte Reload
	cmpl	%eax, %ecx
	jae	.LBB12_6
# BB#5:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB12_2
.LBB12_6:                               # %label_elifz1a
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB12_1
# BB#7:                                 # %entry_ifend10
	movq	(%rax), %rbp
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movl	%r14d, %edx
	movq	%r13, %rcx
	movl	%r12d, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB12_1
# BB#8:                                 # %entry_ifend14
	movq	(%rax), %rax
	movl	$0, gSigInt(%rip)
	cmpl	%eax, %ebp
	jne	.LBB12_11
# BB#9:                                 # %entry_condend17
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB12_2
.LBB12_1:                               # %then_block
	xorl	%eax, %eax
.LBB12_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB12_11:                              # %label_if_elifz0a
	movq	$1, (%rbx)
	movl	$1, %eax
	jmp	.LBB12_2
.Lfunc_end12:
	.size	"Char.compare(Self)$$12", .Lfunc_end12-"Char.compare(Self)$$12"
	.cfi_endproc

	.globl	"Char.getValue()$$16"
	.align	16, 0x90
	.type	"Char.getValue()$$16",@function
"Char.getValue()$$16":                  # @"Char.getValue()$$16"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp81:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
.Ltmp82:
	.cfi_def_cfa_offset 32
.Ltmp83:
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
	.size	"Char.getValue()$$16", .Lfunc_end13-"Char.getValue()$$16"
	.cfi_endproc

	.globl	"Char.setValue(char)$$17"
	.align	16, 0x90
	.type	"Char.setValue(char)$$17",@function
"Char.setValue(char)$$17":              # @"Char.setValue(char)$$17"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp84:
	.cfi_def_cfa_offset 16
	subq	$32, %rsp
.Ltmp85:
	.cfi_def_cfa_offset 48
.Ltmp86:
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
	je	.LBB14_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbx)
	movl	$1, %eax
	jmp	.LBB14_2
.LBB14_1:                               # %then_block
	xorl	%eax, %eax
.LBB14_2:                               # %then_block
	addq	$32, %rsp
	popq	%rbx
	retq
.Lfunc_end14:
	.size	"Char.setValue(char)$$17", .Lfunc_end14-"Char.setValue(char)$$17"
	.cfi_endproc

	.globl	"Char.toFloat()$$18"
	.align	16, 0x90
	.type	"Char.toFloat()$$18",@function
"Char.toFloat()$$18":                   # @"Char.toFloat()$$18"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp87:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp88:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp89:
	.cfi_def_cfa_offset 32
.Ltmp90:
	.cfi_offset %rbx, -24
.Ltmp91:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB15_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %eax
	cvtsi2ssq	%rax, %xmm0
	callq	create_float
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB15_2
.LBB15_1:                               # %then_block
	xorl	%eax, %eax
.LBB15_2:                               # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end15:
	.size	"Char.toFloat()$$18", .Lfunc_end15-"Char.toFloat()$$18"
	.cfi_endproc

	.globl	"Char.toDouble()$$19"
	.align	16, 0x90
	.type	"Char.toDouble()$$19",@function
"Char.toDouble()$$19":                  # @"Char.toDouble()$$19"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp92:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp93:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp94:
	.cfi_def_cfa_offset 32
.Ltmp95:
	.cfi_offset %rbx, -24
.Ltmp96:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
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
	cvtsi2ssq	%rax, %xmm0
	cvtss2sd	%xmm0, %xmm0
	callq	create_double
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB16_2
.LBB16_1:                               # %then_block
	xorl	%eax, %eax
.LBB16_2:                               # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end16:
	.size	"Char.toDouble()$$19", .Lfunc_end16-"Char.toDouble()$$19"
	.cfi_endproc

	.globl	"Char.toPointer()$$20"
	.align	16, 0x90
	.type	"Char.toPointer()$$20",@function
"Char.toPointer()$$20":                 # @"Char.toPointer()$$20"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp97:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp98:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp99:
	.cfi_def_cfa_offset 32
.Ltmp100:
	.cfi_offset %rbx, -24
.Ltmp101:
	.cfi_offset %rbp, -16
	movl	%r9d, %r10d
	movq	%rcx, %rbx
	movq	%rdx, %rcx
	movq	(%rbx), %rax
	movq	$0, (%rsp)
	movq	%rax, (%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r8, %rdi
	movq	%rbx, %rsi
	movl	%r10d, %edx
	movl	%eax, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB17_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	movl	%eax, %edi
	callq	create_pointer
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB17_2
.LBB17_1:                               # %then_block
	xorl	%eax, %eax
.LBB17_2:                               # %then_block
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.Lfunc_end17:
	.size	"Char.toPointer()$$20", .Lfunc_end17-"Char.toPointer()$$20"
	.cfi_endproc

	.globl	"Char.toLowerCase()$$21"
	.align	16, 0x90
	.type	"Char.toLowerCase()$$21",@function
"Char.toLowerCase()$$21":               # @"Char.toLowerCase()$$21"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp102:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp103:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp104:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp105:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp106:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp107:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp108:
	.cfi_def_cfa_offset 80
.Ltmp109:
	.cfi_offset %rbx, -56
.Ltmp110:
	.cfi_offset %r12, -48
.Ltmp111:
	.cfi_offset %r13, -40
.Ltmp112:
	.cfi_offset %r14, -32
.Ltmp113:
	.cfi_offset %r15, -24
.Ltmp114:
	.cfi_offset %rbp, -16
	movl	%r9d, %r14d
	movq	%r8, %r15
	movq	%rcx, %r13
	movq	%rdx, %r12
	movq	(%r13), %rbp
	movq	$0, 8(%rsp)
	movq	%rbp, 8(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	cmpl	$64, %eax
	seta	%cl
	movq	$0, 16(%rsp)
	movzbl	%cl, %ebx
	movq	%rbx, 16(%rsp)
	cmpl	$65, %eax
	jb	.LBB18_6
# BB#4:                                 # %entry_condend
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB18_1
# BB#5:                                 # %entry_ifend4
	movq	(%rax), %rax
	cmpl	$91, %eax
	sbbq	%rbx, %rbx
	andl	$1, %ebx
	movq	%rbx, 16(%rsp)
.LBB18_6:                               # %label_and_endpointzc
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	movq	(%rax), %rdi
	movl	8(%rax), %eax
	testq	%rbx, %rbx
	je	.LBB18_10
# BB#7:                                 # %entry_condend7
	testl	%eax, %eax
	je	.LBB18_1
# BB#8:                                 # %entry_ifend11
	addl	$32, %edi
	jmp	.LBB18_9
.LBB18_10:                              # %label_elsezb
	testl	%eax, %eax
	je	.LBB18_1
.LBB18_9:                               # %entry_ifend16
	callq	create_char
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB18_2
.LBB18_1:                               # %then_block
	xorl	%eax, %eax
.LBB18_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end18:
	.size	"Char.toLowerCase()$$21", .Lfunc_end18-"Char.toLowerCase()$$21"
	.cfi_endproc

	.globl	"Char.toUpperCase()$$22"
	.align	16, 0x90
	.type	"Char.toUpperCase()$$22",@function
"Char.toUpperCase()$$22":               # @"Char.toUpperCase()$$22"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp115:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp116:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp117:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp118:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp119:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp120:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp121:
	.cfi_def_cfa_offset 80
.Ltmp122:
	.cfi_offset %rbx, -56
.Ltmp123:
	.cfi_offset %r12, -48
.Ltmp124:
	.cfi_offset %r13, -40
.Ltmp125:
	.cfi_offset %r14, -32
.Ltmp126:
	.cfi_offset %r15, -24
.Ltmp127:
	.cfi_offset %rbp, -16
	movl	%r9d, %r14d
	movq	%r8, %r15
	movq	%rcx, %r13
	movq	%rdx, %r12
	movq	(%r13), %rbp
	movq	$0, 8(%rsp)
	movq	%rbp, 8(%rsp)
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB19_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rax
	cmpl	$96, %eax
	seta	%cl
	movq	$0, 16(%rsp)
	movzbl	%cl, %ebx
	movq	%rbx, 16(%rsp)
	cmpl	$97, %eax
	jb	.LBB19_6
# BB#4:                                 # %entry_condend
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB19_1
# BB#5:                                 # %entry_ifend4
	movq	(%rax), %rax
	cmpl	$123, %eax
	sbbq	%rbx, %rbx
	andl	$1, %ebx
	movq	%rbx, 16(%rsp)
.LBB19_6:                               # %label_and_endpointze
	movl	$0, gSigInt(%rip)
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r13, %rsi
	movl	%r14d, %edx
	movq	%r12, %rcx
	movl	%ebp, %r8d
	callq	get_field_from_object
	movq	(%rax), %rdi
	movl	8(%rax), %eax
	testq	%rbx, %rbx
	je	.LBB19_10
# BB#7:                                 # %entry_condend7
	testl	%eax, %eax
	je	.LBB19_1
# BB#8:                                 # %entry_ifend11
	addl	$-32, %edi
	jmp	.LBB19_9
.LBB19_10:                              # %label_elsezd
	testl	%eax, %eax
	je	.LBB19_1
.LBB19_9:                               # %entry_ifend16
	callq	create_char
	movl	%eax, %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	%ebp, %eax
	movq	%rax, (%r13)
	movl	$1, %eax
	jmp	.LBB19_2
.LBB19_1:                               # %then_block
	xorl	%eax, %eax
.LBB19_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end19:
	.size	"Char.toUpperCase()$$22", .Lfunc_end19-"Char.toUpperCase()$$22"
	.cfi_endproc

	.globl	"Char.multiply(int)$$23"
	.align	16, 0x90
	.type	"Char.multiply(int)$$23",@function
"Char.multiply(int)$$23":               # @"Char.multiply(int)$$23"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp128:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp129:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp130:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp131:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp132:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp133:
	.cfi_def_cfa_offset 56
	subq	$72, %rsp
.Ltmp134:
	.cfi_def_cfa_offset 128
.Ltmp135:
	.cfi_offset %rbx, -56
.Ltmp136:
	.cfi_offset %r12, -48
.Ltmp137:
	.cfi_offset %r13, -40
.Ltmp138:
	.cfi_offset %r14, -32
.Ltmp139:
	.cfi_offset %r15, -24
.Ltmp140:
	.cfi_offset %rbp, -16
	movl	%r9d, 20(%rsp)          # 4-byte Spill
	movq	%r8, %r15
	movq	%rcx, %r14
	movq	%rdx, 24(%rsp)          # 8-byte Spill
	movq	%rsi, 8(%rsp)           # 8-byte Spill
	movq	(%r14), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r14), %r12
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$.Lglobal_string, %edi
	callq	create_string_object
	movl	%eax, %ebx
	movl	%ebx, %edi
	callq	push_jit_object
	movq	$0, 56(%rsp)
	movl	%ebx, %ebp
	movq	%rbp, 56(%rsp)
	movl	$0, gSigInt(%rip)
	movq	$0, 64(%rsp)
	xorl	%r13d, %r13d
	jmp	.LBB20_1
	.align	16, 0x90
.LBB20_8:                               # %entry_ifend22
                                        #   in Loop: Header=BB20_1 Depth=1
	movq	(%r14), %rax
	movq	%rax, 32(%rsp)          # 8-byte Spill
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r14), %r12
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movq	16(%r14), %rbp
	movq	$0, 56(%rsp)
	movq	%rbp, 56(%rsp)
	movq	24(%r14), %r13
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
	movq	(%r15), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r15)
	incl	%r13d
	movq	$0, 64(%rsp)
	movq	%r13, 64(%rsp)
.LBB20_1:                               # %for_start_pointzf
                                        # =>This Inner Loop Header: Depth=1
	movl	$0, gSigInt(%rip)
	cmpl	%r12d, %r13d
	jge	.LBB20_9
# BB#2:                                 # %entry_condend
                                        #   in Loop: Header=BB20_1 Depth=1
	xorl	%r9d, %r9d
	movq	%r15, %rdi
	movq	%r14, %rsi
	movq	%r14, %rbx
	movl	20(%rsp), %edx          # 4-byte Reload
	movq	24(%rsp), %rcx          # 8-byte Reload
	movq	32(%rsp), %r8           # 8-byte Reload
	callq	get_field_from_object
	cmpl	$0, 8(%rax)
	je	.LBB20_3
# BB#5:                                 # %entry_ifend
                                        #   in Loop: Header=BB20_1 Depth=1
	movq	(%rax), %r14
	movl	$2016, %esi             # imm = 0x7E0
	movq	128(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_3
# BB#6:                                 # %entry_ifend7
                                        #   in Loop: Header=BB20_1 Depth=1
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	$0, (%rcx)
	movq	32(%rsp), %rdx          # 8-byte Reload
	movq	%rdx, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	$0, 16(%rcx)
	movq	%rbp, 16(%rcx)
	movq	$0, 24(%rcx)
	movq	%r13, 24(%rcx)
	movq	(%r15), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	movq	(%r15), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r15)
	movq	$0, 8(%rcx)
	movl	%r14d, %edx
	movq	%rdx, 8(%rcx)
	addq	$8, (%r15)
	movl	$9, %esi
	movq	%rax, %rdi
	movq	%rbx, %r14
	movq	%r14, %rdx
	movl	20(%rsp), %ecx          # 4-byte Reload
	movq	%r15, %r8
	movq	24(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB20_8
# BB#7:                                 # %then_block21
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB20_3:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB20_4
.LBB20_9:                               # %label_for_endzf
	movl	%ebp, %eax
	movq	%rax, (%r14)
	movl	$1, %eax
.LBB20_4:                               # %then_block
	addq	$72, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end20:
	.size	"Char.multiply(int)$$23", .Lfunc_end20-"Char.multiply(int)$$23"
	.cfi_endproc

	.globl	"Char.include(EqualableList)$$24"
	.align	16, 0x90
	.type	"Char.include(EqualableList)$$24",@function
"Char.include(EqualableList)$$24":      # @"Char.include(EqualableList)$$24"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp141:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp142:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp143:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp144:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp145:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp146:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp147:
	.cfi_def_cfa_offset 80
.Ltmp148:
	.cfi_offset %rbx, -56
.Ltmp149:
	.cfi_offset %r12, -48
.Ltmp150:
	.cfi_offset %r13, -40
.Ltmp151:
	.cfi_offset %r14, -32
.Ltmp152:
	.cfi_offset %r15, -24
.Ltmp153:
	.cfi_offset %rbp, -16
	movl	%r9d, 4(%rsp)           # 4-byte Spill
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %rbp
	movq	80(%rsp), %rdi
	movq	(%r14), %rbx
	movq	$0, 8(%rsp)
	movq	%rbx, 8(%rsp)
	movq	8(%r14), %r12
	movq	$0, 16(%rsp)
	movq	%r12, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2060, %esi             # imm = 0x80C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB21_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%rbp)
	movq	%rbx, (%rbp)
	movq	$0, 8(%rbp)
	movq	%r12, 8(%rbp)
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
	movl	$35, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	4(%rsp), %ecx           # 4-byte Reload
	movq	%r13, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB21_5
# BB#4:                                 # %then_block12
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB21_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB21_2
.LBB21_5:                               # %entry_ifend13
	movq	(%r14), %rax
	movq	$0, 8(%rsp)
	movq	%rax, 8(%rsp)
	movq	8(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %ebp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	cmpl	$-1, %ebp
	setne	%al
	movzbl	%al, %eax
	movq	%rax, (%r14)
	movl	$1, %eax
.LBB21_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end21:
	.size	"Char.include(EqualableList)$$24", .Lfunc_end21-"Char.include(EqualableList)$$24"
	.cfi_endproc

	.globl	"Char.printf(String)$$25"
	.align	16, 0x90
	.type	"Char.printf(String)$$25",@function
"Char.printf(String)$$25":              # @"Char.printf(String)$$25"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp154:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp155:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp156:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp157:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp158:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp159:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Ltmp160:
	.cfi_def_cfa_offset 112
.Ltmp161:
	.cfi_offset %rbx, -56
.Ltmp162:
	.cfi_offset %r12, -48
.Ltmp163:
	.cfi_offset %r13, -40
.Ltmp164:
	.cfi_offset %r14, -32
.Ltmp165:
	.cfi_offset %r15, -24
.Ltmp166:
	.cfi_offset %rbp, -16
	movl	%r9d, %ebx
	movl	%ebx, 28(%rsp)          # 4-byte Spill
	movq	%r8, %r13
	movq	%rcx, %r14
	movq	%rdx, %rbp
	movq	%rbp, 32(%rsp)          # 8-byte Spill
	movq	%rsi, 16(%rsp)          # 8-byte Spill
	movq	112(%rsp), %rdx
	movq	(%r14), %r15
	movq	$0, 40(%rsp)
	movq	%r15, 40(%rsp)
	movq	8(%r14), %r12
	movq	$0, 48(%rsp)
	movq	%r12, 48(%rsp)
	movl	$0, gSigInt(%rip)
	movq	(%r13), %rax
	movq	$0, (%rax)
	movl	%r15d, %ecx
	movq	%rcx, (%rax)
	addq	$8, (%r13)
	movq	%rdx, (%rsp)
	movl	$1, %r8d
	movl	$2076, %r9d             # imm = 0x81C
	movq	%r13, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	run_create_carray
	cmpl	$0, 8(%rax)
	je	.LBB22_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$2084, %esi             # imm = 0x824
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB22_1
# BB#4:                                 # %entry_ifend6
	movq	16(%rsp), %rcx          # 8-byte Reload
	movq	$0, (%rcx)
	movq	%r15, (%rcx)
	movq	$0, 8(%rcx)
	movq	%r12, 8(%rcx)
	movq	(%r13), %rcx
	movq	$0, (%rcx)
	movl	%r12d, %edx
	movq	%rdx, (%rcx)
	movq	(%r13), %rcx
	leaq	8(%rcx), %rdx
	movq	%rdx, (%r13)
	movq	$0, 8(%rcx)
	movq	%rbp, 8(%rcx)
	addq	$8, (%r13)
	movl	$5, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	28(%rsp), %ecx          # 4-byte Reload
	movq	%r13, %r8
	movq	32(%rsp), %rbp          # 8-byte Reload
	movq	%rbp, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB22_6
# BB#5:                                 # %then_block18
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB22_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB22_2
.LBB22_6:                               # %entry_ifend19
	movq	(%r14), %rax
	movq	$0, 40(%rsp)
	movq	%rax, 40(%rsp)
	movq	8(%r14), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 48(%rsp)
	movq	(%r13), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%r13)
	movq	$0, (%r14)
	movl	$1, %eax
.LBB22_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end22:
	.size	"Char.printf(String)$$25", .Lfunc_end22-"Char.printf(String)$$25"
	.cfi_endproc

	.globl	"Char.print()$$26"
	.align	16, 0x90
	.type	"Char.print()$$26",@function
"Char.print()$$26":                     # @"Char.print()$$26"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp167:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp168:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp169:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp170:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp171:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp172:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp173:
	.cfi_def_cfa_offset 80
.Ltmp174:
	.cfi_offset %rbx, -56
.Ltmp175:
	.cfi_offset %r12, -48
.Ltmp176:
	.cfi_offset %r13, -40
.Ltmp177:
	.cfi_offset %r14, -32
.Ltmp178:
	.cfi_offset %r15, -24
.Ltmp179:
	.cfi_offset %rbp, -16
	movl	%r9d, %r12d
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %r13
	movq	80(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2092, %esi             # imm = 0x82C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbx)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB23_4
# BB#5:                                 # %entry_ifend6
	movq	(%r14), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$2100, %esi             # imm = 0x834
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB23_1
# BB#6:                                 # %entry_ifend13
	movq	$0, (%r13)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	addq	$8, (%rbx)
	movl	$1, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB23_7
.LBB23_4:                               # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB23_1:                               # %then_block
	xorl	%eax, %eax
.LBB23_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB23_7:                               # %entry_ifend22
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, (%r14)
	movl	$1, %eax
	jmp	.LBB23_2
.Lfunc_end23:
	.size	"Char.print()$$26", .Lfunc_end23-"Char.print()$$26"
	.cfi_endproc

	.globl	"Char.println()$$27"
	.align	16, 0x90
	.type	"Char.println()$$27",@function
"Char.println()$$27":                   # @"Char.println()$$27"
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp180:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp181:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp182:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp183:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp184:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp185:
	.cfi_def_cfa_offset 56
	subq	$24, %rsp
.Ltmp186:
	.cfi_def_cfa_offset 80
.Ltmp187:
	.cfi_offset %rbx, -56
.Ltmp188:
	.cfi_offset %r12, -48
.Ltmp189:
	.cfi_offset %r13, -40
.Ltmp190:
	.cfi_offset %r14, -32
.Ltmp191:
	.cfi_offset %r15, -24
.Ltmp192:
	.cfi_offset %rbp, -16
	movl	%r9d, %r12d
	movq	%r8, %rbx
	movq	%rcx, %r14
	movq	%rdx, %r15
	movq	%rsi, %r13
	movq	80(%rsp), %rdi
	movq	(%r14), %rbp
	movq	$0, 16(%rsp)
	movq	%rbp, 16(%rsp)
	movl	$0, gSigInt(%rip)
	movl	$2108, %esi             # imm = 0x83C
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB24_1
# BB#3:                                 # %entry_ifend
	movq	$0, (%r13)
	movq	%rbp, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movl	%ebp, %edx
	movq	%rdx, (%rcx)
	addq	$8, (%rbx)
	movl	$10, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	jne	.LBB24_4
# BB#5:                                 # %entry_ifend6
	movq	(%r14), %rax
	movq	%rax, 8(%rsp)           # 8-byte Spill
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movq	-8(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movl	$2116, %esi             # imm = 0x844
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB24_1
# BB#6:                                 # %entry_ifend13
	movq	$0, (%r13)
	movq	8(%rsp), %rcx           # 8-byte Reload
	movq	%rcx, (%r13)
	movq	(%rbx), %rcx
	movq	$0, (%rcx)
	movq	%rbp, (%rcx)
	addq	$8, (%rbx)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	%r14, %rdx
	movl	%r12d, %ecx
	movq	%rbx, %r8
	movq	%r15, %r9
	callq	call_invoke_method
	cmpl	$1, %eax
	je	.LBB24_7
.LBB24_4:                               # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB24_1:                               # %then_block
	xorl	%eax, %eax
.LBB24_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB24_7:                               # %entry_ifend22
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, (%r14)
	movl	$1, %eax
	jmp	.LBB24_2
.Lfunc_end24:
	.size	"Char.println()$$27", .Lfunc_end24-"Char.println()$$27"
	.cfi_endproc

	.type	.Lglobal_string,@object # @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.zero	1
	.size	.Lglobal_string, 1


	.section	".note.GNU-stack","",@progbits
