	.text
	.file	"CFFI.ocl"
	.globl	clover2_main            // -- Begin function clover2_main
	.p2align	2
	.type	clover2_main,@function
clover2_main:                           // @clover2_main
	.cfi_startproc
// %bb.0:                               // %entry
	stp	x23, x22, [sp, #-48]!   // 8-byte Folded Spill
	stp	x21, x20, [sp, #16]     // 8-byte Folded Spill
	stp	x19, x30, [sp, #32]     // 8-byte Folded Spill
	.cfi_def_cfa_offset 48
	.cfi_offset w30, -8
	.cfi_offset w19, -16
	.cfi_offset w20, -24
	.cfi_offset w21, -32
	.cfi_offset w22, -40
	.cfi_offset w23, -48
	mov	x19, x4
	mov	x20, x2
	adrp	x2, :got:gCodeData
	adrp	x4, :got:gConstData
	ldr	x2, [x2, :got_lo12:gCodeData]
	ldr	x4, [x4, :got_lo12:gConstData]
	mov	x0, x7
	mov	x1, x6
	mov	w21, w5
	mov	x22, x3
	mov	w3, #52
	mov	w5, #41
	bl	initialize_code_and_constant
	adrp	x23, :got:gSigInt
	ldr	x23, [x23, :got_lo12:gSigInt]
	adrp	x1, .Lglobal_string
	add	x1, x1, :lo12:.Lglobal_string
	orr	w2, wzr, #0x1
	mov	x0, x20
	str	wzr, [x23]
	bl	mark_source_position
	adrp	x1, .Lglobal_string.2
	add	x1, x1, :lo12:.Lglobal_string.2
	orr	w2, wzr, #0x1
	mov	x0, x20
	bl	mark_source_position2
	adrp	x0, .Lglobal_string.3
	add	x0, x0, :lo12:.Lglobal_string.3
	mov	w1, wzr
	bl	get_class_with_load_and_initialize
	cbz	x0, .LBB0_6
// %bb.1:                               // %entry_ifend
	orr	w1, wzr, #0x1
	mov	x2, x22
	mov	w3, w21
	mov	x4, x19
	mov	x5, x20
	bl	call_invoke_method
	cmp	w0, #1                  // =1
	b.eq	.LBB0_3
// %bb.2:                               // %then_block2
	mov	x0, x20
	bl	get_try_catch_label_name
	mov	w0, wzr
	b	.LBB0_6
.LBB0_3:                                // %entry_ifend3
	ldr	w8, [x23]
	tbz	w8, #0, .LBB0_5
// %bb.4:                               // %sigint_then_block
	adrp	x4, .Lglobal_string.4
	adrp	x5, .Lglobal_string.5
	add	x4, x4, :lo12:.Lglobal_string.4
	add	x5, x5, :lo12:.Lglobal_string.5
	mov	x0, x19
	mov	x1, x22
	mov	w2, w21
	mov	x3, x20
	str	wzr, [x23]
	bl	entry_exception_object_with_class_name2
	mov	w0, wzr
	b	.LBB0_6
.LBB0_5:                                // %entry_after_sigint
	ldr	x8, [x19]
	orr	w0, wzr, #0x1
	sub	x8, x8, #8              // =8
	str	x8, [x19]
.LBB0_6:                                // %then_block
	ldp	x19, x30, [sp, #32]     // 8-byte Folded Reload
	ldp	x21, x20, [sp, #16]     // 8-byte Folded Reload
	ldp	x23, x22, [sp], #48     // 8-byte Folded Reload
	ret
.Lfunc_end0:
	.size	clover2_main, .Lfunc_end0-clover2_main
	.cfi_endproc
                                        // -- End function
	.type	gCodeData,@object       // @gCodeData
	.data
	.globl	gCodeData
gCodeData:
	.asciz	"\017\000\000\000\020\000\000\000\000\000\000\000\001\000\000\000\021\000\000\000\020\000\000\000\001\000\000\000\270\013\000\000 \000\000\000\001\000\000\000 \000\000\000\022\000\000\000\001\000\000"
	.size	gCodeData, 52

	.type	gConstData,@object      // @gConstData
	.globl	gConstData
gConstData:
	.asciz	"code/CFFI.cl\000\000\000\000code/CFFI.cl\000\000\000\000CFFITest"
	.size	gConstData, 41

	.type	.Lglobal_string,@object // @global_string
	.section	.rodata,"a",@progbits
.Lglobal_string:
	.asciz	"code/CFFI.cl"
	.size	.Lglobal_string, 13

	.type	.Lglobal_string.2,@object // @global_string.2
.Lglobal_string.2:
	.asciz	"code/CFFI.cl"
	.size	.Lglobal_string.2, 13

	.type	.Lglobal_string.3,@object // @global_string.3
.Lglobal_string.3:
	.asciz	"CFFITest"
	.size	.Lglobal_string.3, 9

	.type	.Lglobal_string.4,@object // @global_string.4
.Lglobal_string.4:
	.asciz	"Exception"
	.size	.Lglobal_string.4, 10

	.type	.Lglobal_string.5,@object // @global_string.5
.Lglobal_string.5:
	.asciz	"Signal Interrupt"
	.size	.Lglobal_string.5, 17


	.section	".note.GNU-stack","",@progbits
