	.text
	.file	"UShort.bc"
	.globl	"UShort.toByte()$$0"
	.align	16, 0x90
	.type	"UShort.toByte()$$0",@function
"UShort.toByte()$$0":                   # @"UShort.toByte()$$0"
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
	.size	"UShort.toByte()$$0", .Lfunc_end0-"UShort.toByte()$$0"
	.cfi_endproc

	.globl	"UShort.toUByte()$$1"
	.align	16, 0x90
	.type	"UShort.toUByte()$$1",@function
"UShort.toUByte()$$1":                  # @"UShort.toUByte()$$1"
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
	.size	"UShort.toUByte()$$1", .Lfunc_end1-"UShort.toUByte()$$1"
	.cfi_endproc

	.globl	"UShort.toShort()$$2"
	.align	16, 0x90
	.type	"UShort.toShort()$$2",@function
"UShort.toShort()$$2":                  # @"UShort.toShort()$$2"
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
	.size	"UShort.toShort()$$2", .Lfunc_end2-"UShort.toShort()$$2"
	.cfi_endproc

	.globl	"UShort.toUShort()$$3"
	.align	16, 0x90
	.type	"UShort.toUShort()$$3",@function
"UShort.toUShort()$$3":                 # @"UShort.toUShort()$$3"
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
	.size	"UShort.toUShort()$$3", .Lfunc_end3-"UShort.toUShort()$$3"
	.cfi_endproc

	.globl	"UShort.toInteger()$$4"
	.align	16, 0x90
	.type	"UShort.toInteger()$$4",@function
"UShort.toInteger()$$4":                # @"UShort.toInteger()$$4"
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
	movq	(%rax), %rax
	movzwl	%ax, %edi
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
	.size	"UShort.toInteger()$$4", .Lfunc_end4-"UShort.toInteger()$$4"
	.cfi_endproc

	.globl	"UShort.toUInteger()$$5"
	.align	16, 0x90
	.type	"UShort.toUInteger()$$5",@function
"UShort.toUInteger()$$5":               # @"UShort.toUInteger()$$5"
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
	movq	(%rax), %rax
	movzwl	%ax, %edi
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
	.size	"UShort.toUInteger()$$5", .Lfunc_end5-"UShort.toUInteger()$$5"
	.cfi_endproc

	.globl	"UShort.toLong()$$6"
	.align	16, 0x90
	.type	"UShort.toLong()$$6",@function
"UShort.toLong()$$6":                   # @"UShort.toLong()$$6"
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
	movzwl	%ax, %edi
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
	.size	"UShort.toLong()$$6", .Lfunc_end6-"UShort.toLong()$$6"
	.cfi_endproc

	.globl	"UShort.toULong()$$7"
	.align	16, 0x90
	.type	"UShort.toULong()$$7",@function
"UShort.toULong()$$7":                  # @"UShort.toULong()$$7"
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
	movzwl	%ax, %edi
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
	.size	"UShort.toULong()$$7", .Lfunc_end7-"UShort.toULong()$$7"
	.cfi_endproc

	.globl	"UShort.toChar()$$8"
	.align	16, 0x90
	.type	"UShort.toChar()$$8",@function
"UShort.toChar()$$8":                   # @"UShort.toChar()$$8"
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
	movq	(%rax), %rax
	movzwl	%ax, %edi
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
	.size	"UShort.toChar()$$8", .Lfunc_end8-"UShort.toChar()$$8"
	.cfi_endproc

	.globl	"UShort.toBool()$$9"
	.align	16, 0x90
	.type	"UShort.toBool()$$9",@function
"UShort.toBool()$$9":                   # @"UShort.toBool()$$9"
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
	movq	(%rax), %rax
	movzwl	%ax, %edi
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
	.size	"UShort.toBool()$$9", .Lfunc_end9-"UShort.toBool()$$9"
	.cfi_endproc

	.globl	"UShort.toString()$$10"
	.align	16, 0x90
	.type	"UShort.toString()$$10",@function
"UShort.toString()$$10":                # @"UShort.toString()$$10"
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
	movq	(%rax), %rax
	movzwl	%ax, %edi
	callq	run_uint_to_string_cast
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
	.size	"UShort.toString()$$10", .Lfunc_end10-"UShort.toString()$$10"
	.cfi_endproc

	.globl	"UShort.equals(Self)$$11"
	.align	16, 0x90
	.type	"UShort.equals(Self)$$11",@function
"UShort.equals(Self)$$11":              # @"UShort.equals(Self)$$11"
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
	movzwl	%r13w, %ecx
	movzwl	%ax, %eax
	cmpl	%eax, %ecx
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
	.size	"UShort.equals(Self)$$11", .Lfunc_end11-"UShort.equals(Self)$$11"
	.cfi_endproc

	.globl	"UShort.compare(Self)$$12"
	.align	16, 0x90
	.type	"UShort.compare(Self)$$12",@function
"UShort.compare(Self)$$12":             # @"UShort.compare(Self)$$12"
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
	movzwl	%cx, %ecx
	movzwl	%ax, %eax
	cmpl	%eax, %ecx
	jae	.LBB12_6
# BB#5:                                 # %entry_condend
	movl	$0, gSigInt(%rip)
	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
	movq	%rax, (%rbx)
	movl	$1, %eax
	jmp	.LBB12_2
.LBB12_6:                               # %label_elifq1a
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
	movzwl	%bp, %ecx
	movzwl	%ax, %eax
	cmpl	%eax, %ecx
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
.LBB12_11:                              # %label_if_elifq0a
	movq	$1, (%rbx)
	movl	$1, %eax
	jmp	.LBB12_2
.Lfunc_end12:
	.size	"UShort.compare(Self)$$12", .Lfunc_end12-"UShort.compare(Self)$$12"
	.cfi_endproc

	.globl	"UShort.getValue()$$16"
	.align	16, 0x90
	.type	"UShort.getValue()$$16",@function
"UShort.getValue()$$16":                # @"UShort.getValue()$$16"
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
	movzwl	%ax, %eax
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
	.size	"UShort.getValue()$$16", .Lfunc_end13-"UShort.getValue()$$16"
	.cfi_endproc

	.globl	"UShort.setValue(ushort)$$17"
	.align	16, 0x90
	.type	"UShort.setValue(ushort)$$17",@function
"UShort.setValue(ushort)$$17":          # @"UShort.setValue(ushort)$$17"
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
	movzwl	%dx, %r10d
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
	.size	"UShort.setValue(ushort)$$17", .Lfunc_end14-"UShort.setValue(ushort)$$17"
	.cfi_endproc

	.globl	"UShort.toFloat()$$18"
	.align	16, 0x90
	.type	"UShort.toFloat()$$18",@function
"UShort.toFloat()$$18":                 # @"UShort.toFloat()$$18"
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
	movzwl	%ax, %eax
	cvtsi2ssl	%eax, %xmm0
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
	.size	"UShort.toFloat()$$18", .Lfunc_end15-"UShort.toFloat()$$18"
	.cfi_endproc

	.globl	"UShort.toDouble()$$19"
	.align	16, 0x90
	.type	"UShort.toDouble()$$19",@function
"UShort.toDouble()$$19":                # @"UShort.toDouble()$$19"
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
	movzwl	%ax, %eax
	cvtsi2ssl	%eax, %xmm0
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
	.size	"UShort.toDouble()$$19", .Lfunc_end16-"UShort.toDouble()$$19"
	.cfi_endproc

	.globl	"UShort.toPointer()$$20"
	.align	16, 0x90
	.type	"UShort.toPointer()$$20",@function
"UShort.toPointer()$$20":               # @"UShort.toPointer()$$20"
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
	movzwl	%ax, %edi
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
	.size	"UShort.toPointer()$$20", .Lfunc_end17-"UShort.toPointer()$$20"
	.cfi_endproc

	.globl	"UShort.include(EqualableList)$$21"
	.align	16, 0x90
	.type	"UShort.include(EqualableList)$$21",@function
"UShort.include(EqualableList)$$21":    # @"UShort.include(EqualableList)$$21"
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
	movl	$1608, %esi             # imm = 0x648
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB18_1
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
	je	.LBB18_5
# BB#4:                                 # %then_block12
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB18_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB18_2
.LBB18_5:                               # %entry_ifend13
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
	.size	"UShort.include(EqualableList)$$21", .Lfunc_end18-"UShort.include(EqualableList)$$21"
	.cfi_endproc

	.globl	"UShort.printf(String)$$22"
	.align	16, 0x90
	.type	"UShort.printf(String)$$22",@function
"UShort.printf(String)$$22":            # @"UShort.printf(String)$$22"
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
	subq	$56, %rsp
.Ltmp121:
	.cfi_def_cfa_offset 112
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
	movl	$1624, %r9d             # imm = 0x658
	movq	%r13, %rdi
	movq	%r14, %rsi
	movl	%ebx, %edx
	movq	%rbp, %rcx
	callq	run_create_carray
	cmpl	$0, 8(%rax)
	je	.LBB19_1
# BB#3:                                 # %entry_ifend
	movq	(%rax), %rbp
	movl	%ebp, %edi
	callq	push_jit_object
	movl	$1632, %esi             # imm = 0x660
	movq	112(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB19_1
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
	je	.LBB19_6
# BB#5:                                 # %then_block18
	movq	%rbp, %rdi
	callq	get_try_catch_label_name
.LBB19_1:                               # %then_block
	xorl	%eax, %eax
	jmp	.LBB19_2
.LBB19_6:                               # %entry_ifend19
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
.LBB19_2:                               # %then_block
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end19:
	.size	"UShort.printf(String)$$22", .Lfunc_end19-"UShort.printf(String)$$22"
	.cfi_endproc

	.globl	"UShort.print()$$23"
	.align	16, 0x90
	.type	"UShort.print()$$23",@function
"UShort.print()$$23":                   # @"UShort.print()$$23"
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
	subq	$24, %rsp
.Ltmp134:
	.cfi_def_cfa_offset 80
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
	movl	$1640, %esi             # imm = 0x668
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
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
	jne	.LBB20_4
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
	movl	$1648, %esi             # imm = 0x670
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB20_1
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
	je	.LBB20_7
.LBB20_4:                               # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB20_1:                               # %then_block
	xorl	%eax, %eax
.LBB20_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB20_7:                               # %entry_ifend22
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, (%r14)
	movl	$1, %eax
	jmp	.LBB20_2
.Lfunc_end20:
	.size	"UShort.print()$$23", .Lfunc_end20-"UShort.print()$$23"
	.cfi_endproc

	.globl	"UShort.println()$$24"
	.align	16, 0x90
	.type	"UShort.println()$$24",@function
"UShort.println()$$24":                 # @"UShort.println()$$24"
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
	movl	$1656, %esi             # imm = 0x678
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB21_1
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
	jne	.LBB21_4
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
	movl	$1664, %esi             # imm = 0x680
	movq	80(%rsp), %rdi
	callq	get_class_with_load_and_initialize_in_jit
	testq	%rax, %rax
	je	.LBB21_1
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
	je	.LBB21_7
.LBB21_4:                               # %then_block5
	movq	%r15, %rdi
	callq	get_try_catch_label_name
.LBB21_1:                               # %then_block
	xorl	%eax, %eax
.LBB21_2:                               # %then_block
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.LBB21_7:                               # %entry_ifend22
	movq	(%r14), %rax
	movq	$0, 16(%rsp)
	movq	%rax, 16(%rsp)
	movq	(%rbx), %rax
	movl	-8(%rax), %edi
	callq	push_jit_object
	addq	$-8, (%rbx)
	movq	$0, (%r14)
	movl	$1, %eax
	jmp	.LBB21_2
.Lfunc_end21:
	.size	"UShort.println()$$24", .Lfunc_end21-"UShort.println()$$24"
	.cfi_endproc


	.section	".note.GNU-stack","",@progbits
