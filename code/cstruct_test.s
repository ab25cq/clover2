	.text
	.file	"cstruct_test.ocl"
	.globl	clover2_main            // -- Begin function clover2_main
	.p2align	2
	.type	clover2_main,@function
clover2_main:                           // @clover2_main
	.cfi_startproc
// %bb.0:                               // %entry
	str	x24, [sp, #-64]!        // 8-byte Folded Spill
	stp	x23, x22, [sp, #16]     // 8-byte Folded Spill
	stp	x21, x20, [sp, #32]     // 8-byte Folded Spill
	stp	x19, x30, [sp, #48]     // 8-byte Folded Spill
	.cfi_def_cfa_offset 64
	.cfi_offset w30, -8
	.cfi_offset w19, -16
	.cfi_offset w20, -24
	.cfi_offset w21, -32
	.cfi_offset w22, -40
	.cfi_offset w23, -48
	.cfi_offset w24, -64
	mov	x20, x4
	mov	x19, x2
	adrp	x2, :got:gCodeData
	adrp	x4, :got:gConstData
	ldr	x2, [x2, :got_lo12:gCodeData]
	ldr	x4, [x4, :got_lo12:gConstData]
	mov	x0, x7
	mov	x1, x6
	mov	w21, w5
	mov	x22, x3
	orr	w3, wzr, #0x70
	orr	w5, wzr, #0x7c
	bl	initialize_code_and_constant
	adrp	x24, :got:gSigInt
	ldr	x24, [x24, :got_lo12:gSigInt]
	adrp	x1, .Lglobal_string
	add	x1, x1, :lo12:.Lglobal_string
	orr	w2, wzr, #0x1
	mov	x0, x19
	str	wzr, [x24]
	bl	mark_source_position
	ldr	x8, [x20]
	adrp	x23, .Lglobal_string.2
	add	x23, x23, :lo12:.Lglobal_string.2
	adrp	x1, .Lglobal_string.3
	str	x23, [x8]
	ldr	x8, [x20]
	add	x1, x1, :lo12:.Lglobal_string.3
	orr	w2, wzr, #0x1
	mov	x0, x19
	add	x8, x8, #8              // =8
	str	x8, [x20]
	bl	mark_source_position2
	mov	x0, x23
	bl	puts
	ldr	x8, [x20]
	mov	w9, w0
	sub	x10, x8, #8             // =8
	str	x10, [x20]
	stur	x9, [x8, #-8]
	ldr	x8, [x20]
	add	x8, x8, #8              // =8
	str	x8, [x20]
	ldr	w8, [x24]
	tbz	w8, #0, .LBB0_3
// %bb.1:                               // %sigint_then_block
	adrp	x4, .Lglobal_string.4
	adrp	x5, .Lglobal_string.5
	add	x4, x4, :lo12:.Lglobal_string.4
	add	x5, x5, :lo12:.Lglobal_string.5
	str	wzr, [x24]
.LBB0_2:                                // %sigint_then_block
	mov	x0, x20
	mov	x1, x22
	mov	w2, w21
	mov	x3, x19
	bl	entry_exception_object_with_class_name2
	mov	w0, wzr
	b	.LBB0_9
.LBB0_3:                                // %entry_after_sigint
	ldr	x8, [x20]
	adrp	x1, .Lglobal_string.6
	add	x1, x1, :lo12:.Lglobal_string.6
	orr	w2, wzr, #0x3
	sub	x8, x8, #8              // =8
	mov	x0, x19
	str	x8, [x20]
	str	wzr, [x24]
	bl	mark_source_position
	adrp	x1, .Lglobal_string.7
	add	x1, x1, :lo12:.Lglobal_string.7
	orr	w2, wzr, #0x3
	mov	x0, x19
	bl	mark_source_position2
	adrp	x0, .Lglobal_string.8
	add	x0, x0, :lo12:.Lglobal_string.8
	mov	w1, wzr
	bl	get_class_with_load_and_initialize
	cbz	x0, .LBB0_9
// %bb.4:                               // %entry_ifend
	mov	w1, #5
	mov	x2, x22
	mov	w3, w21
	mov	x4, x20
	mov	x5, x19
	bl	call_invoke_method
	cmp	w0, #1                  // =1
	b.eq	.LBB0_6
// %bb.5:                               // %then_block10
	mov	x0, x19
	bl	get_try_catch_label_name
	mov	w0, wzr
	b	.LBB0_9
.LBB0_6:                                // %entry_ifend11
	ldr	w8, [x24]
	tbz	w8, #0, .LBB0_8
// %bb.7:                               // %sigint_then_block15
	adrp	x4, .Lglobal_string.9
	adrp	x5, .Lglobal_string.10
	str	wzr, [x24]
	add	x4, x4, :lo12:.Lglobal_string.9
	add	x5, x5, :lo12:.Lglobal_string.10
	b	.LBB0_2
.LBB0_8:                                // %entry_after_sigint16
	ldr	x8, [x20]
	orr	w0, wzr, #0x1
	sub	x8, x8, #8              // =8
	str	x8, [x20]
.LBB0_9:                                // %then_block
	ldp	x19, x30, [sp, #48]     // 8-byte Folded Reload
	ldp	x21, x20, [sp, #32]     // 8-byte Folded Reload
	ldp	x23, x22, [sp, #16]     // 8-byte Folded Reload
	ldr	x24, [sp], #64          // 8-byte Folded Reload
	ret
.Lfunc_end0:
	.size	clover2_main, .Lfunc_end0-clover2_main
	.cfi_endproc
                                        // -- End function
	.type	gCodeData,@object       // @gCodeData
	.data
	.globl	gCodeData
gCodeData:
	.asciz	"\017\000\000\000\020\000\000\000\000\000\000\000\001\000\000\000+#\000\000\030\000\000\000\021\000\000\000$\000\000\000\001\000\000\000\270\013\000\000<\000\000\000\000\000\000\000 \000\000\000\022\000\000\000\001\000\000\000\017\000\000\000\020\000\000\000@\000\000\000\003\000\000\000\021\000\000\000X\000\000\000\003\000\000\000\270\013\000\000p\000\000\000\005\000\000\000 \000\000\000\022\000\000\000\001\000\000"
	.size	gCodeData, 112

	.type	gConstData,@object      // @gConstData
	.globl	gConstData
gConstData:
	.asciz	"code/cstruct_test.cl\000\000\000\000HELLO WORLD\000code/cstruct_test.cl\000\000\000\000C\000\000\000code/cstruct_test.cl\000\000\000\000code/cstruct_test.cl\000\000\000\000CStructTest"
	.size	gConstData, 124

	.type	.Lglobal_string,@object // @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"code/cstruct_test.cl"
	.size	.Lglobal_string, 21

	.type	.Lglobal_string.2,@object // @global_string.2
.Lglobal_string.2:
	.asciz	"HELLO WORLD"
	.size	.Lglobal_string.2, 12

	.type	.Lglobal_string.3,@object // @global_string.3
.Lglobal_string.3:
	.asciz	"code/cstruct_test.cl"
	.size	.Lglobal_string.3, 21

	.type	.Lglobal_string.4,@object // @global_string.4
.Lglobal_string.4:
	.asciz	"Exception"
	.size	.Lglobal_string.4, 10

	.type	.Lglobal_string.5,@object // @global_string.5
.Lglobal_string.5:
	.asciz	"Signal Interrupt"
	.size	.Lglobal_string.5, 17

	.type	.Lglobal_string.6,@object // @global_string.6
.Lglobal_string.6:
	.asciz	"code/cstruct_test.cl"
	.size	.Lglobal_string.6, 21

	.type	.Lglobal_string.7,@object // @global_string.7
.Lglobal_string.7:
	.asciz	"code/cstruct_test.cl"
	.size	.Lglobal_string.7, 21

	.type	.Lglobal_string.8,@object // @global_string.8
.Lglobal_string.8:
	.asciz	"CStructTest"
	.size	.Lglobal_string.8, 12

	.type	.Lglobal_string.9,@object // @global_string.9
.Lglobal_string.9:
	.asciz	"Exception"
	.size	.Lglobal_string.9, 10

	.type	.Lglobal_string.10,@object // @global_string.10
.Lglobal_string.10:
	.asciz	"Signal Interrupt"
	.size	.Lglobal_string.10, 17


	.section	".note.GNU-stack","",@progbits
