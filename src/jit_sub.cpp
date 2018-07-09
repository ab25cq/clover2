#include "jit_common.hpp"

extern "C"
{

LVALUE trunc_value(LVALUE* llvm_value, int size)
{
    LVALUE result = *llvm_value;

    if(llvm_value->kind == kLVKindMemory) {
        Value* value = Builder.CreateAlignedLoad(llvm_value->value, 8);

        switch(size) {
            case 1: {
                result.value = Builder.CreateCast(Instruction::Trunc, value, Type::getInt1Ty(TheContext));
                result.kind = kLVKindInt1;
            }
            break;

            case 8: {
                result.value = Builder.CreateCast(Instruction::Trunc, value, Type::getInt8Ty(TheContext));
                result.kind = kLVKindInt8;
            }
            break;

            case 16: {
                result.value = Builder.CreateCast(Instruction::Trunc, value, Type::getInt16Ty(TheContext));
                result.kind = kLVKindInt16;
            }
            break;

            case 32: {
                result.value = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext));
                result.kind = kLVKindInt32;
            }
            break;

            case 64: {
                result.value = Builder.CreateCast(Instruction::BitCast, value, Type::getInt64Ty(TheContext));
                result.kind = kLVKindInt64;
            }
            break;
        }
    }
    else {
        Type* llvm_type = llvm_value->value->getType();
        Type::TypeID type_id = llvm_type->getTypeID();

        /// Constant Int ///
        if(llvm_value->kind == kLVKindConstantInt1 || llvm_value->kind == kLVKindConstantInt8 || llvm_value->kind == kLVKindConstantUInt8 || llvm_value->kind == kLVKindConstantInt16 || llvm_value->kind == kLVKindConstantUInt16 || llvm_value->kind == kLVKindConstantInt32 || llvm_value->kind == kLVKindConstantUInt32 || llvm_value->kind == kLVKindConstantInt64 || llvm_value->kind == kLVKindConstantUInt64) 
        {
#if LLVM_VERSION_MAJOR >= 4
            ConstantInt* constant_int_value = (ConstantInt*)llvm_value->value;
            APInt apint_value = constant_int_value->getValue();

            //bool signed_value = llvm_value->kind == kLVKindConstantInt1 || llvm_value->kind == kLVKindConstantInt8 || llvm_value->kind == kLVKindConstantInt16 || llvm_value->kind == kLVKindConstantInt32 || llvm_value->kind == kLVKindConstantInt64;
            bool signed_value = apint_value.isSignBitSet();
#else
            ConstantInt* constant_int_value = dynamic_cast<ConstantInt*>(llvm_value->value);
            APInt apint_value = constant_int_value->getValue();
            bool signed_value = apint_value.isSignBit();
#endif

            switch(size) {
                case 1:
                    if(signed_value) {
                        result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(1));
                        result.kind = kLVKindConstantInt1;
                    }
                    else {
                        result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(1));
                        result.kind = kLVKindConstantInt1;
                    }
                    break;

                case 8:
                    if(signed_value) {
                        result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(8));
                        result.kind = kLVKindConstantInt8;
                    }
                    else {
                        result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(8));
                        result.kind = kLVKindConstantUInt8;
                    }
                    break;

                case 16:
                    if(signed_value) {
                        result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(16));
                        result.kind = kLVKindConstantInt16;
                    }
                    else {
                        result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(16));
                        result.kind = kLVKindConstantUInt16;
                    }
                    break;

                case 32:
                    if(signed_value) {
                        result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(32));
                        result.kind = kLVKindConstantInt32;
                    }
                    else {
                        result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(32));
                        result.kind = kLVKindConstantUInt32;
                    }
                    break;

                case 64:
                    if(signed_value) {
                        result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(64));
                        result.kind = kLVKindConstantInt64;
                    }
                    else {
                        result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(64));
                        result.kind = kLVKindConstantUInt64;
                    }
                    break;
            }
        }
        else if(llvm_value->kind == kLVKindConstantFloat || llvm_value->kind == kLVKindConstantDouble) {
#if LLVM_VERSION_MAJOR >= 4
            ConstantFP* constant_float_value = (ConstantFP*)llvm_value->value;
            const APFloat apfloat_value = constant_float_value->getValueAPF();
#else
            ConstantFP* constant_float_value = dynamic_cast<ConstantFP*>(llvm_value->value);
            const APFloat apfloat_value = constant_float_value->getValueAPF();
#endif

            switch(size) {
                case 1: {
                    APInt apint_value = apfloat_value.bitcastToAPInt();
                    //ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(1));
                    result.kind = kLVKindConstantInt1;
                    }
                    break;

                case 8: {
                    APInt apint_value = apfloat_value.bitcastToAPInt();
                    //ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(8));
                    result.kind = kLVKindConstantInt8;
                    }
                    break;

                case 16: {
                    APInt apint_value = apfloat_value.bitcastToAPInt();
                    //ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(16));
                    result.kind = kLVKindConstantInt16;
                    }
                    break;

                case 32: {
                    APInt apint_value = apfloat_value.bitcastToAPInt();
                    //ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(32));
                    result.kind = kLVKindConstantInt32;
                    }
                    break;

                case 64: {
                    APInt apint_value = apfloat_value.bitcastToAPInt();
                    //ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(64));
                    result.kind = kLVKindConstantInt64;
                    }
                    break;
            }
        }
        /// Memory ///
        else if(type_id == Type::TypeID::FloatTyID) {
            switch(size) {
                case 1:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt1Ty(TheContext));
                    result.kind = kLVKindInt1;
                    break;

                case 8:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt8Ty(TheContext));
                    result.kind = kLVKindInt8;
                    break;

                case 16:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt16Ty(TheContext));
                    result.kind = kLVKindInt16;
                    break;

                case 32:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt32Ty(TheContext));
                    result.kind = kLVKindInt32;
                    break;

                case 64:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt32Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::ZExt, result.value, Type::getInt64Ty(TheContext));
                    result.kind = kLVKindInt64;
                    break;
            }
        }
        else if(type_id == Type::TypeID::DoubleTyID) {
            switch(size) {
                case 1:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt1Ty(TheContext));
                    result.kind = kLVKindInt1;
                    break;

                case 8:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt8Ty(TheContext));
                    result.kind = kLVKindInt8;
                    break;

                case 16:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt16Ty(TheContext));
                    result.kind = kLVKindInt16;
                    break;

                case 32:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt32Ty(TheContext));
                    result.kind = kLVKindInt32;
                    break;

                case 64:
                    result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.kind = kLVKindInt64;
                    break;
            }
        }
        else if(llvm_type->isPointerTy()) {
            switch(size) {
                case 1:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt1Ty(TheContext));
                    result.kind = kLVKindInt1;
                    break;

                case 8:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt8Ty(TheContext));
                    result.kind = kLVKindInt8;
                    break;

                case 16:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt16Ty(TheContext));
                    result.kind = kLVKindInt16;
                    break;

                case 32:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt32Ty(TheContext));
                    result.kind = kLVKindInt32;
                    break;

                case 64:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.kind = kLVKindInt64;
                    break;
            }
        }
        else {
            switch(size) {
                case 1:
                    if(!llvm_type->isIntegerTy(1)) {
                        result.value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt1Ty(TheContext));
                        result.kind = kLVKindInt1;
                    }
                    break;

                case 8:
                    if(llvm_type->isIntegerTy(1)) {
                        result.value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt8Ty(TheContext));
                        result.kind = kLVKindInt8;
                    }
                    else if(!llvm_type->isIntegerTy(8)) {
                        result.value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt8Ty(TheContext));
                        result.kind = kLVKindInt8;
                    }
                    break;

                case 16:
                    if(llvm_type->isIntegerTy(1) || llvm_type->isIntegerTy(8)) {
                        result.value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt16Ty(TheContext));
                        result.kind = kLVKindInt16;
                    }
                    else if(llvm_type->isIntegerTy(16)) {
                    }
                    else {
                        result.value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt16Ty(TheContext));
                        result.kind = kLVKindInt16;
                    }
                    break;

                case 32:
                    if(llvm_type->isIntegerTy(1) ||llvm_type->isIntegerTy(8) || llvm_type->isIntegerTy(16)) {
                        result.value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt32Ty(TheContext));
                        result.kind = kLVKindInt32;
                    }
                    else {
                        result.value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt32Ty(TheContext));
                        result.kind = kLVKindInt32;
                    }
                    break;

                case 64:
                    if(!llvm_type->isIntegerTy(64)) {
                        result.value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt64Ty(TheContext));
                        result.kind = kLVKindInt64;
                    }
                    break;
            }
        }
    }

    return result;
}

// size --> 32: float 64:double
LVALUE trunc_value_to_float_or_double(LVALUE* llvm_value, int size)
{
    LVALUE result = *llvm_value;

    if(llvm_value->kind == kLVKindMemory) {
        Value* value = Builder.CreateAlignedLoad(llvm_value->value, 8);

        switch(size) {
            case 32:
                result.value = Builder.CreateCast(Instruction::Trunc, value, Type::getInt32Ty(TheContext));
                result.value = Builder.CreateCast(Instruction::BitCast, result.value, Type::getFloatTy(TheContext));
                result.kind = kLVKindFloat;
                break;

            case 64:
                result.value = Builder.CreateCast(Instruction::BitCast, value, Type::getDoubleTy(TheContext));
                result.kind = kLVKindDouble;
                break;
        }
    }
    else {
        Type* llvm_type = llvm_value->value->getType();
        Type::TypeID type_id = llvm_type->getTypeID();

        /// Constant Int ///
        if(llvm_value->kind == kLVKindConstantInt1 || llvm_value->kind == kLVKindConstantInt8 || llvm_value->kind == kLVKindConstantUInt8 || llvm_value->kind == kLVKindConstantInt16 || llvm_value->kind == kLVKindConstantUInt16 || llvm_value->kind == kLVKindConstantInt32 || llvm_value->kind == kLVKindConstantUInt32 || llvm_value->kind == kLVKindConstantInt64 || llvm_value->kind == kLVKindConstantUInt64) 
        {
#if LLVM_VERSION_MAJOR >= 4
            ConstantInt* constant_int_value = (ConstantInt*)(llvm_value->value);
            APInt apint_value = constant_int_value->getValue();

            bool signed_value = apint_value.isSignBitSet();
            //bool signed_value = llvm_value->kind == kLVKindConstantInt1 || llvm_value->kind == kLVKindConstantInt8 || llvm_value->kind == kLVKindConstantInt16 || llvm_value->kind == kLVKindConstantInt32 || llvm_value->kind == kLVKindConstantInt64;
#else
            ConstantInt* constant_int_value = dynamic_cast<ConstantInt*>(llvm_value->value);
            APInt apint_value = constant_int_value->getValue();
            bool signed_value = apint_value.isSignBit();
#endif

            switch(size) {
                case 32:
                    if(signed_value) {
                        result.value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getFloatTy(TheContext));
                        result.kind = kLVKindFloat;
                    }
                    else {
                        result.value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext));
                        result.kind = kLVKindFloat;
                    }
                    break;

                case 64:
                    if(signed_value) {
                        result.value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
                        result.kind = kLVKindDouble;
                    }
                    else {
                        result.value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
                        result.kind = kLVKindDouble;
                    }
                    break;
            }
        }
        else if(llvm_value->kind == kLVKindConstantFloat || type_id == Type::TypeID::FloatTyID || llvm_value->kind == kLVKindFloat) {
            switch(size) {
                case 64:
                    result.value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext));
                    result.kind = kLVKindDouble;
                    break;
            }
        }
        else if(type_id == Type::TypeID::DoubleTyID || llvm_value->kind == kLVKindConstantDouble || llvm_value->kind == kLVKindDouble) {
            switch(size) {
                case 32:
                    result.value = Builder.CreateCast(Instruction::FPTrunc, llvm_value->value, Type::getFloatTy(TheContext));
                    result.kind = kLVKindFloat;
                    break;

                case 64:
                    break;
            }
        }
        else if(llvm_type->isPointerTy()) {
            switch(size) {
                case 32:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt32Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::UIToFP, result.value, Type::getFloatTy(TheContext));
                    result.kind = kLVKindFloat;
                    break;

                case 64:
                    result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt64Ty(TheContext));
                    result.value = Builder.CreateCast(Instruction::UIToFP, result.value, Type::getDoubleTy(TheContext));
                    result.kind = kLVKindDouble;
                    break;
            }
        }
        else {
            switch(size) {
                case 32:
                    result.value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext));
                    result.kind = kLVKindFloat;
                    break;

                case 64:
                    result.value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
                    result.kind = kLVKindDouble;
                    break;
            }
        }
    }

    return result;
}

LVALUE trunc_value_to_pointer(LVALUE* llvm_value)
{
    LVALUE result = *llvm_value;

    if(llvm_value->kind == kLVKindMemory) {
        Value* value = Builder.CreateAlignedLoad(llvm_value->value, 8);

        result.value = Builder.CreateCast(Instruction::IntToPtr, value, PointerType::get(IntegerType::get(TheContext, 8), 0));
        result.kind = kLVKindPointer8;
    }
    else {
        Type* llvm_type = llvm_value->value->getType();
        Type::TypeID type_id = llvm_type->getTypeID();

        /// Constant Int ///
        if(llvm_value->kind == kLVKindConstantInt1 || llvm_value->kind == kLVKindConstantInt8 || llvm_value->kind == kLVKindConstantUInt8 || llvm_value->kind == kLVKindConstantInt16 || llvm_value->kind == kLVKindConstantUInt16 || llvm_value->kind == kLVKindConstantInt32 || llvm_value->kind == kLVKindConstantUInt32 || llvm_value->kind == kLVKindConstantInt64 || llvm_value->kind == kLVKindConstantInt64 || llvm_value->kind == kLVKindConstantUInt64) 
        {
#if LLVM_VERSION_MAJOR >= 4
            ConstantInt* constant_int_value = (ConstantInt*)(llvm_value->value);
            APInt apint_value = constant_int_value->getValue();
#else
            ConstantInt* constant_int_value = dynamic_cast<ConstantInt*>(llvm_value->value);
            APInt apint_value = constant_int_value->getValue();
#endif

            result.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 8), 0));
            result.kind = kLVKindPointer8;
        }
        else if(llvm_value->kind == kLVKindConstantFloat || llvm_value->kind == kLVKindConstantDouble) {
#if LLVM_VERSION_MAJOR >= 4
            ConstantFP* constant_float_value = (ConstantFP*)(llvm_value->value);
            const APFloat apfloat_value = constant_float_value->getValueAPF();
#else
            ConstantFP* constant_float_value = dynamic_cast<ConstantFP*>(llvm_value->value);
            const APFloat apfloat_value = constant_float_value->getValueAPF();
#endif

            result.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 8), 0));
            result.kind = kLVKindPointer8;
        }
        /// Memory ///
        else if(type_id == Type::TypeID::FloatTyID || llvm_value->kind == kLVKindFloat) {
            result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
            result.value = Builder.CreateCast(Instruction::IntToPtr, result.value, PointerType::get(IntegerType::get(TheContext, 8), 0));
            result.kind = kLVKindPointer8;
        }
        else if(type_id == Type::TypeID::DoubleTyID || llvm_value->kind == kLVKindDouble) {
            result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
            result.value = Builder.CreateCast(Instruction::IntToPtr, result.value, PointerType::get(IntegerType::get(TheContext, 8), 0));
            result.kind = kLVKindPointer8;
        }
        else if(llvm_type->isPointerTy()) {
        }
        else {
            result.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 8), 0));
            result.kind = kLVKindPointer8;
        }
    }

    return result;
}

void trunc_variable(LVALUE* llvm_value, int size)
{
    if(llvm_value->kind == kLVKindInt64) {
        switch(size) {
            case 1:
                llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt1Ty(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindInt1;
                break;

            case 8:
                llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt8Ty(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindInt8;
                break;

            case 16:
                llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt16Ty(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindInt16;
                break;

            case 32:
                llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt32Ty(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindInt32;
                break;

            case 64:
                llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt64Ty(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindInt64;
                break;

            case 128:
                llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt32Ty(TheContext));
                llvm_value->value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getFloatTy(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindFloat;
                break;

            case 256:
                llvm_value->value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getDoubleTy(TheContext), "trunc_variable");
                llvm_value->kind = kLVKindDouble;
                break;

            case 1024:
                llvm_value->value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 8), 0), "trunc_variable");
                llvm_value->kind = kLVKindPointer8;
                break;
        }
    }
}

void cast_llvm_value_from_inst(LVALUE* llvm_value, int inst) 
{
    switch(inst) {
        case OP_BYTE_TO_CDOUBLE_CAST:
        case OP_SHORT_TO_CDOUBLE_CAST:
        case OP_INT_TO_CDOUBLE_CAST:
        case OP_LONG_TO_CDOUBLE_CAST:
        case OP_BOOL_TO_CDOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            llvm_value->value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext), "fvalue");
            llvm_value->kind = kLVKindDouble;
            break;

        case OP_UBYTE_TO_CDOUBLE_CAST:
        case OP_USHORT_TO_CDOUBLE_CAST:
        case OP_UINT_TO_CDOUBLE_CAST:
        case OP_CHAR_TO_CDOUBLE_CAST:
        case OP_ULONG_TO_CDOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            llvm_value->value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext), "fvalue");
            llvm_value->kind = kLVKindDouble;
            break;

        case OP_FLOAT_TO_CDOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext), "fvalue");
            llvm_value->kind = kLVKindDouble;
            break;

        case OP_DOUBLE_TO_CDOUBLE_CAST:
            break;

        case OP_BYTE_TO_CFLOAT_CAST:
        case OP_SHORT_TO_CFLOAT_CAST:
        case OP_INT_TO_CFLOAT_CAST:
        case OP_LONG_TO_CFLOAT_CAST:
        case OP_BOOL_TO_CFLOAT_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            llvm_value->kind = kLVKindFloat;
            break;

        case OP_UBYTE_TO_CFLOAT_CAST:
        case OP_USHORT_TO_CFLOAT_CAST:
        case OP_UINT_TO_CFLOAT_CAST:
        case OP_CHAR_TO_CFLOAT_CAST:
        case OP_ULONG_TO_CFLOAT_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            llvm_value->kind = kLVKindFloat;
            break;

        case OP_BYTE_TO_CULONG_CAST:
        case OP_UBYTE_TO_CULONG_CAST:
        case OP_SHORT_TO_CULONG_CAST:
        case OP_USHORT_TO_CULONG_CAST:
        case OP_INT_TO_CULONG_CAST:
        case OP_UINT_TO_CULONG_CAST:
        case OP_LONG_TO_CULONG_CAST:
        case OP_ULONG_TO_CULONG_CAST:
        case OP_CHAR_TO_CULONG_CAST:
        case OP_POINTER_TO_CULONG_CAST:
        case OP_BOOL_TO_CULONG_CAST: {
            LVALUE llvm_value2;
            llvm_value2 = trunc_value(llvm_value, 64);

            llvm_value->value = llvm_value2.value;
            }
            break;

        case OP_FLOAT_TO_CULONG_CAST:
        case OP_DOUBLE_TO_CULONG_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPToUI, llvm_value->value, Type::getInt64Ty(TheContext));
            llvm_value->kind = kLVKindUInt64;
            break;

        case OP_BYTE_TO_CLONG_CAST:
        case OP_UBYTE_TO_CLONG_CAST:
        case OP_SHORT_TO_CLONG_CAST:
        case OP_USHORT_TO_CLONG_CAST:
        case OP_INT_TO_CLONG_CAST:
        case OP_UINT_TO_CLONG_CAST:
        case OP_LONG_TO_CLONG_CAST:
        case OP_ULONG_TO_CLONG_CAST:
        case OP_CHAR_TO_CLONG_CAST:
        case OP_POINTER_TO_CLONG_CAST:
        case OP_BOOL_TO_CLONG_CAST: {
            LVALUE llvm_value2;
            llvm_value2 = trunc_value(llvm_value, 64);

            llvm_value->value = llvm_value2.value;
            }
            break;

        case OP_FLOAT_TO_CLONG_CAST:
        case OP_DOUBLE_TO_CLONG_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPToSI, llvm_value->value, Type::getInt64Ty(TheContext));
            llvm_value->kind = kLVKindInt64;
            break;

        case OP_BYTE_TO_CUSHORT_CAST:
        case OP_UBYTE_TO_CUSHORT_CAST:
        case OP_SHORT_TO_CUSHORT_CAST:
        case OP_USHORT_TO_CUSHORT_CAST:
        case OP_INT_TO_CUSHORT_CAST:
        case OP_UINT_TO_CUSHORT_CAST:
        case OP_LONG_TO_CUSHORT_CAST:
        case OP_ULONG_TO_CUSHORT_CAST:
        case OP_CHAR_TO_CUSHORT_CAST:
        case OP_POINTER_TO_CUSHORT_CAST:
        case OP_BOOL_TO_CUSHORT_CAST: {
            LVALUE llvm_value2;
            llvm_value2 = trunc_value(llvm_value, 16);

            llvm_value->value = llvm_value2.value;
            }
            break;

        case OP_FLOAT_TO_CUSHORT_CAST:
        case OP_DOUBLE_TO_CUSHORT_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPToUI, llvm_value->value, Type::getInt16Ty(TheContext));
            llvm_value->kind = kLVKindUInt16;
            break;

        case OP_BYTE_TO_CSHORT_CAST:
        case OP_UBYTE_TO_CSHORT_CAST:
        case OP_SHORT_TO_CSHORT_CAST:
        case OP_USHORT_TO_CSHORT_CAST:
        case OP_INT_TO_CSHORT_CAST:
        case OP_UINT_TO_CSHORT_CAST:
        case OP_LONG_TO_CSHORT_CAST:
        case OP_ULONG_TO_CSHORT_CAST:
        case OP_CHAR_TO_CSHORT_CAST:
        case OP_POINTER_TO_CSHORT_CAST:
        case OP_BOOL_TO_CSHORT_CAST: {
            LVALUE llvm_value2;
            llvm_value2 = trunc_value(llvm_value, 16);
            llvm_value->value = llvm_value2.value;
            }
            break;

        case OP_FLOAT_TO_CSHORT_CAST:
        case OP_DOUBLE_TO_CSHORT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPToSI, llvm_value->value, Type::getInt16Ty(TheContext));
            llvm_value->kind = kLVKindInt16;
            break;

        case OP_BYTE_TO_CUBYTE_CAST:
        case OP_UBYTE_TO_CUBYTE_CAST:
        case OP_SHORT_TO_CUBYTE_CAST:
        case OP_USHORT_TO_CUBYTE_CAST:
        case OP_INT_TO_CUBYTE_CAST:
        case OP_UINT_TO_CUBYTE_CAST:
        case OP_LONG_TO_CUBYTE_CAST:
        case OP_ULONG_TO_CUBYTE_CAST:
        case OP_CHAR_TO_CUBYTE_CAST:
        case OP_POINTER_TO_CUBYTE_CAST:
        case OP_BOOL_TO_CUBYTE_CAST: {
            LVALUE llvm_value2;
            llvm_value2 = trunc_value(llvm_value, 8);

            llvm_value->value = llvm_value2.value;
            }
            break;

        case OP_FLOAT_TO_CUBYTE_CAST:
        case OP_DOUBLE_TO_CUBYTE_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPToUI, llvm_value->value, Type::getInt8Ty(TheContext));
            llvm_value->kind = kLVKindUInt8;
            break;

        case OP_BYTE_TO_CBYTE_CAST:
        case OP_UBYTE_TO_CBYTE_CAST:
        case OP_SHORT_TO_CBYTE_CAST:
        case OP_USHORT_TO_CBYTE_CAST:
        case OP_INT_TO_CBYTE_CAST:
        case OP_UINT_TO_CBYTE_CAST:
        case OP_LONG_TO_CBYTE_CAST:
        case OP_ULONG_TO_CBYTE_CAST:
        case OP_CHAR_TO_CBYTE_CAST:
        case OP_BOOL_TO_CBYTE_CAST: 
        case OP_POINTER_TO_CBYTE_CAST: {
            LVALUE llvm_value2 = trunc_value(llvm_value, 8);
            llvm_value->value = llvm_value2.value;
            }
            break;

        case OP_FLOAT_TO_CBYTE_CAST:
        case OP_DOUBLE_TO_CBYTE_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPToSI, llvm_value->value, Type::getInt8Ty(TheContext));
            llvm_value->kind = kLVKindInt8;
            break;

        case OP_BYTE_TO_UINTEGER_CAST:
        case OP_UBYTE_TO_UINTEGER_CAST:
        case OP_SHORT_TO_UINTEGER_CAST:
        case OP_USHORT_TO_UINTEGER_CAST:
        case OP_INT_TO_UINTEGER_CAST:
        case OP_UINT_TO_UINTEGER_CAST:
        case OP_LONG_TO_UINTEGER_CAST:
        case OP_ULONG_TO_UINTEGER_CAST:
        case OP_CHAR_TO_UINTEGER_CAST:
        case OP_POINTER_TO_UINTEGER_CAST:
        case OP_BOOL_TO_UINTEGER_CAST: {
            LVALUE llvm_value2 = trunc_value(llvm_value, 32);

            llvm_value->value = llvm_value2.value;
            }
            break;

        case OP_FLOAT_TO_UINTEGER_CAST:
        case OP_DOUBLE_TO_UINTEGER_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPToUI, llvm_value->value, Type::getInt32Ty(TheContext));
            llvm_value->kind = kLVKindUInt32;
            break;

        case OP_FLOAT_TO_INTEGER_CAST:
        case OP_DOUBLE_TO_INTEGER_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPToSI, llvm_value->value, Type::getInt32Ty(TheContext));
            llvm_value->kind = kLVKindInt32;
            break;

        case OP_POINTER_TO_INTEGER_CAST:
        case OP_BOOL_TO_INTEGER_CAST:{
            LVALUE llvm_value2 = trunc_value(llvm_value, 32);

            llvm_value->value = llvm_value2.value;
            }
            break;

        case OP_FLOAT_TO_CFLOAT_CAST:
            //llvm_value->value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            llvm_value->kind = kLVKindFloat;
            break;

        case OP_DOUBLE_TO_CFLOAT_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPTrunc, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            llvm_value->kind = kLVKindFloat;
            break;


        case OP_CBYTE_TO_SHORT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::SExt, llvm_value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value->kind = kLVKindInt16;
            break;

        case OP_CBYTE_TO_INT_CAST:
        case OP_CSHORT_TO_INT_CAST : 
            llvm_value->value = Builder.CreateCast(Instruction::SExt, llvm_value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value->kind = kLVKindInt32;
            break;

        case OP_CBYTE_TO_LONG_CAST:
        case OP_CSHORT_TO_LONG_CAST : 
        case OP_INTEGER_TO_LONG_CAST:
        case OP_CBOOL_TO_LONG_CAST:
        case OP_CFLOAT_TO_LONG_CAST : 
        case OP_CDOUBLE_TO_LONG_CAST : 
            llvm_value->value = Builder.CreateCast(Instruction::SExt, llvm_value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value->kind = kLVKindInt64;
            break;

        case OP_CBYTE_TO_USHORT_CAST:
        case OP_CUBYTE_TO_SHORT_CAST:
        case OP_CUBYTE_TO_USHORT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value->kind = kLVKindInt16;
            break;

        case OP_CBYTE_TO_UINT_CAST:
        case OP_CBYTE_TO_CHAR_CAST:
        case OP_CUBYTE_TO_INT_CAST:
        case OP_CUBYTE_TO_UINT_CAST:
        case OP_CUBYTE_TO_CHAR_CAST:
        case OP_CSHORT_TO_UINT_CAST :
        case OP_CSHORT_TO_CHAR_CAST:
        case OP_CUSHORT_TO_INT_CAST : 
        case OP_CUSHORT_TO_UINT_CAST :
        case OP_CUSHORT_TO_CHAR_CAST:
        case OP_CFLOAT_TO_CHAR_CAST:
        case OP_CDOUBLE_TO_CHAR_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value->kind = kLVKindInt32;
            break;

        case OP_CBYTE_TO_ULONG_CAST:
        case OP_CUBYTE_TO_LONG_CAST:
        case OP_CUBYTE_TO_ULONG_CAST:
        case OP_CSHORT_TO_ULONG_CAST :
        case OP_CUSHORT_TO_LONG_CAST : 
        case OP_CUSHORT_TO_ULONG_CAST :
        case OP_INTEGER_TO_ULONG_CAST:
        case OP_UINTEGER_TO_LONG_CAST : 
        case OP_UINTEGER_TO_ULONG_CAST:
        case OP_CBOOL_TO_ULONG_CAST:
        case OP_CCHAR_TO_LONG_CAST : 
        case OP_CFLOAT_TO_ULONG_CAST :
        case OP_CDOUBLE_TO_ULONG_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value->kind = kLVKindInt64;
            break;

        case OP_CBYTE_TO_FLOAT_CAST:
        case OP_CSHORT_TO_FLOAT_CAST:
        case OP_INTEGER_TO_FLOAT_CAST:
        case OP_CLONG_TO_FLOAT_CAST: 
        case OP_CBOOL_TO_FLOAT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getFloatTy(TheContext));
            llvm_value->kind = kLVKindFloat;
            break;

        case OP_CBYTE_TO_DOUBLE_CAST:
        case OP_CSHORT_TO_DOUBLE_CAST:
        case OP_INTEGER_TO_DOUBLE_CAST:
        case OP_CLONG_TO_DOUBLE_CAST: 
        case OP_CBOOL_TO_DOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
            llvm_value->kind = kLVKindDouble;
            break;

        case OP_CUBYTE_TO_FLOAT_CAST:
        case OP_CUSHORT_TO_FLOAT_CAST:
        case OP_UINTEGER_TO_FLOAT_CAST:
        case OP_CULONG_TO_FLOAT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext));
            llvm_value->kind = kLVKindFloat;
            break;

        case OP_CUBYTE_TO_DOUBLE_CAST: 
        case OP_CUSHORT_TO_DOUBLE_CAST:
        case OP_UINTEGER_TO_DOUBLE_CAST:
        case OP_CULONG_TO_DOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
            llvm_value->kind = kLVKindDouble;
            break;
            
        case OP_CSHORT_TO_BYTE_CAST:
        case OP_CSHORT_TO_UBYTE_CAST :
        case OP_CUSHORT_TO_BYTE_CAST:
        case OP_CUSHORT_TO_UBYTE_CAST :
        case OP_INTEGER_TO_BYTE_CAST:
        case OP_INTEGER_TO_UBYTE_CAST:
        case OP_UINTEGER_TO_BYTE_CAST:
        case OP_UINTEGER_TO_UBYTE_CAST:
        case OP_CLONG_TO_BYTE_CAST:
        case OP_CLONG_TO_UBYTE_CAST:
        case OP_CULONG_TO_UBYTE_CAST:
        case OP_CULONG_TO_BYTE_CAST:
        case OP_CBOOL_TO_BYTE_CAST:
        case OP_CBOOL_TO_UBYTE_CAST:
        case OP_CCHAR_TO_BYTE_CAST:
        case OP_CCHAR_TO_UBYTE_CAST :
        case OP_CFLOAT_TO_BYTE_CAST:
        case OP_CFLOAT_TO_UBYTE_CAST :
        case OP_CDOUBLE_TO_BYTE_CAST:
        case OP_CDOUBLE_TO_UBYTE_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt8Ty(TheContext), "value2");
            llvm_value->kind = kLVKindInt8;
            break;

        case OP_INTEGER_TO_SHORT_CAST:
        case OP_INTEGER_TO_USHORT_CAST:
        case OP_UINTEGER_TO_SHORT_CAST:
        case OP_UINTEGER_TO_USHORT_CAST:
        case OP_CLONG_TO_SHORT_CAST:
        case OP_CLONG_TO_USHORT_CAST:
        case OP_CULONG_TO_USHORT_CAST:
        case OP_CULONG_TO_SHORT_CAST:
        case OP_CBOOL_TO_SHORT_CAST:
        case OP_CBOOL_TO_USHORT_CAST:
        case OP_CCHAR_TO_SHORT_CAST:
        case OP_CCHAR_TO_USHORT_CAST :
        case OP_CFLOAT_TO_SHORT_CAST:
        case OP_CFLOAT_TO_USHORT_CAST :
        case OP_CDOUBLE_TO_SHORT_CAST:
        case OP_CDOUBLE_TO_USHORT_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value->kind = kLVKindInt16;
            break;

        case OP_CLONG_TO_INT_CAST:
        case OP_CLONG_TO_UINT_CAST:
        case OP_CULONG_TO_INT_CAST:
        case OP_CULONG_TO_UINT_CAST:
        case OP_CULONG_TO_CHAR_CAST:
        case OP_CCHAR_TO_INT_CAST : 
        case OP_CLONG_TO_CHAR_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value->kind = kLVKindInt32;
            break;

        case OP_CPOINTER_TO_BYTE_CAST:
        case OP_CPOINTER_TO_UBYTE_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt8Ty(TheContext), "value2");
            llvm_value->kind = kLVKindInt8;
            break;

        case OP_CPOINTER_TO_SHORT_CAST:
        case OP_CPOINTER_TO_USHORT_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt16Ty(TheContext), "value2");
            llvm_value->kind = kLVKindInt16;
            break;

        case OP_CPOINTER_TO_INT_CAST : 
        case OP_CPOINTER_TO_UINT_CAST :
        case OP_CPOINTER_TO_CHAR_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt32Ty(TheContext), "value2");
            llvm_value->kind = kLVKindInt32;
            break;

        case OP_CPOINTER_TO_LONG_CAST : 
        case OP_CPOINTER_TO_ULONG_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt64Ty(TheContext), "value2");
            llvm_value->kind = kLVKindInt64;
            break;

        case OP_CFLOAT_TO_DOUBLE_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext));
            llvm_value->kind = kLVKindDouble;
            break;

        case OP_CDOUBLE_TO_FLOAT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPTrunc, llvm_value->value, Type::getFloatTy(TheContext));
            llvm_value->kind = kLVKindFloat;
            break;

        case OP_CBYTE_TO_BYTE_CAST:
        case OP_CBYTE_TO_UBYTE_CAST:
        case OP_CUBYTE_TO_BYTE_CAST:
        case OP_CUBYTE_TO_UBYTE_CAST:

        case OP_CSHORT_TO_SHORT_CAST:
        case OP_CSHORT_TO_USHORT_CAST :
        case OP_CUSHORT_TO_SHORT_CAST:
        case OP_CUSHORT_TO_USHORT_CAST :

        case OP_INTEGER_TO_INT_CAST:
        case OP_INTEGER_TO_UINT_CAST:
        case OP_UINTEGER_TO_INT_CAST:
        case OP_UINTEGER_TO_UINT_CAST:

        case OP_CLONG_TO_LONG_CAST:
        case OP_CLONG_TO_ULONG_CAST:
        case OP_CULONG_TO_LONG_CAST:
        case OP_CULONG_TO_ULONG_CAST:

        case OP_INTEGER_TO_CHAR_CAST:
        case OP_UINTEGER_TO_CHAR_CAST:

        case OP_CBOOL_TO_INT_CAST : 
        case OP_CBOOL_TO_UINT_CAST :
        case OP_CBOOL_TO_CHAR_CAST: 

        case OP_CCHAR_TO_CHAR_CAST:
        case OP_CCHAR_TO_UINT_CAST :

        case OP_CFLOAT_TO_INT_CAST : 
        case OP_CFLOAT_TO_UINT_CAST :

        case OP_CFLOAT_TO_FLOAT_CAST:
        case OP_CDOUBLE_TO_INT_CAST : 
        case OP_CDOUBLE_TO_UINT_CAST :
            break;

        case OP_BYTE_TO_CPOINTER_CAST:
        case OP_UBYTE_TO_CPOINTER_CAST:
        case OP_SHORT_TO_CPOINTER_CAST:
        case OP_USHORT_TO_CPOINTER_CAST:
        case OP_INT_TO_CPOINTER_CAST:
        case OP_UINT_TO_CPOINTER_CAST:
        case OP_LONG_TO_CPOINTER_CAST:
        case OP_ULONG_TO_CPOINTER_CAST:
        case OP_CHAR_TO_CPOINTER_CAST: 
        case OP_BOOL_TO_CPOINTER_CAST: {
            llvm_value->value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 8), 0));
            llvm_value->kind = kLVKindPointer8;
            }
            break;

        case OP_POINTER_TO_CPOINTER_CAST:
            break;

        case OP_BYTE_TO_CBOOL_CAST:
        case OP_UBYTE_TO_CBOOL_CAST:
        case OP_SHORT_TO_CBOOL_CAST:
        case OP_USHORT_TO_CBOOL_CAST:
        case OP_INT_TO_CBOOL_CAST:
        case OP_UINT_TO_CBOOL_CAST:
        case OP_LONG_TO_CBOOL_CAST:
        case OP_ULONG_TO_CBOOL_CAST:
        case OP_CHAR_TO_CBOOL_CAST:
        case OP_POINTER_TO_CBOOL_CAST:{
            LVALUE llvm_value2;
            llvm_value2 = trunc_value(llvm_value, 32);

            llvm_value->value = llvm_value2.value;
            }
            break;

        case OP_BOOL_TO_CBOOL_CAST: 
            break;

        case OP_FLOAT_TO_CBOOL_CAST:
        case OP_DOUBLE_TO_CBOOL_CAST: {
            llvm_value->value = Builder.CreateCast(Instruction::FPToUI, llvm_value->value, Type::getInt32Ty(TheContext));
            llvm_value->kind = kLVKindUInt32;
            }
            break;

        case OP_BYTE_TO_CCHAR_CAST :
        case OP_UBYTE_TO_CCHAR_CAST:
        case OP_SHORT_TO_CCHAR_CAST:
        case OP_USHORT_TO_CCHAR_CAST:
        case OP_INT_TO_CCHAR_CAST:
        case OP_UINT_TO_CCHAR_CAST:
        case OP_LONG_TO_CCHAR_CAST:
        case OP_ULONG_TO_CCHAR_CAST:
        case OP_CHAR_TO_CCHAR_CAST:
        case OP_POINTER_TO_CCHAR_CAST:
        case OP_BOOL_TO_CCHAR_CAST: {
            LVALUE llvm_value2;
            llvm_value2 = trunc_value(llvm_value, 32);

            llvm_value->value = llvm_value2.value;
            }
            break;

        case OP_FLOAT_TO_CCHAR_CAST:
        case OP_DOUBLE_TO_CCHAR_CAST: {
            llvm_value->value = Builder.CreateCast(Instruction::FPToUI, llvm_value->value, Type::getInt32Ty(TheContext));
            llvm_value->kind = kLVKindUInt32;
            }
            break;
    }
}

}

extern "C"
{
Value* llvm_create_string(char* str)
{
    Constant* str_constant = ConstantDataArray::getString(TheModule->getContext(), str, true);

    GlobalVariable* gvar = new GlobalVariable(*TheModule, ArrayType::get(IntegerType::get(TheContext, 8), strlen(str)+1), true, GlobalValue::PrivateLinkage, 0, "global_string");
    gvar->setAlignment(1);

    gvar->setInitializer(str_constant);

    Value* value = Builder.CreateCast(Instruction::BitCast, gvar, PointerType::get(IntegerType::get(TheContext, 8), 0));

    return value;
}

Value* llvm_create_buffer(char* str, int len)
{
    uint8_t* str2 = (uint8_t*)str;
    ArrayRef<uint8_t> str_array(str2, len);
    Constant* str_constant = ConstantDataArray::get(TheModule->getContext(), str_array);

    GlobalVariable* gvar = new GlobalVariable(*TheModule, ArrayType::get(IntegerType::get(TheContext, 8), len) , true, GlobalValue::PrivateLinkage, 0, "global_buffer");
    gvar->setAlignment(1);

    gvar->setInitializer(str_constant);

    Value* value = Builder.CreateCast(Instruction::BitCast, gvar, PointerType::get(IntegerType::get(TheContext, 8), 0));

    return value;
}

LVALUE* get_stack_ptr_value_from_index(LVALUE* llvm_stack_ptr, int index)
{
    return llvm_stack_ptr + index;
}

void dec_stack_ptr(LVALUE** llvm_stack_ptr, int value)
{
    int i;
    for(i=0; i<value; i++) {
        (*llvm_stack_ptr)->value = 0;
        (*llvm_stack_ptr)->lvar_address_index = -1;
        (*llvm_stack_ptr)->lvar_stored = FALSE;
        (*llvm_stack_ptr)->kind = kLVKindNone;
        (*llvm_stack_ptr)->parent_var_num = 0;
        (*llvm_stack_ptr)->parent_stack = NULL;
        (*llvm_stack_ptr)->parent_llvm_stack = NULL;

        (*llvm_stack_ptr)--;
    }

    (*llvm_stack_ptr)->value = 0;
    (*llvm_stack_ptr)->lvar_address_index = -1;
    (*llvm_stack_ptr)->lvar_stored = FALSE;
    (*llvm_stack_ptr)->kind = kLVKindNone;
    (*llvm_stack_ptr)->parent_var_num = 0;
    (*llvm_stack_ptr)->parent_stack = NULL;
    (*llvm_stack_ptr)->parent_llvm_stack = NULL;
}

void push_value_to_stack_ptr(LVALUE** llvm_stack_ptr, LVALUE* value)
{
    (**llvm_stack_ptr) = *value;
    (*llvm_stack_ptr)++;
}

void insert_value_to_stack_ptr_with_offset(LVALUE** llvm_stack_ptr, LVALUE* value, int offset)
{
    (*(*llvm_stack_ptr+offset)) = *value;
}

void store_llvm_value_to_lvar_with_offset(LVALUE* llvm_stack, int index, LVALUE* llvm_value, BOOL except_parent_stack)
{
    /// 0 clear align 8 byte ///
    Value* zero = ConstantInt::get(TheContext, llvm::APInt(64, 0, true));
    Builder.CreateStore(zero, llvm_stack[index].value);

    /// store ///
    LVALUE llvm_value2;
    llvm_value2 = trunc_value(llvm_value, 64);
    
    /// go ///
    Builder.CreateAlignedStore(llvm_value2.value, llvm_stack[index].value, 8);

    llvm_stack[index].lvar_address_index = llvm_value->lvar_address_index;
    llvm_stack[index].lvar_stored = TRUE;
    llvm_stack[index].kind = llvm_value->kind;

    if(!except_parent_stack) {
        llvm_stack[index].parent_var_num = llvm_value->parent_var_num;
        llvm_stack[index].parent_stack = llvm_value->parent_stack;
        llvm_stack[index].parent_llvm_stack = llvm_value->parent_llvm_stack;
    }
}

void get_llvm_value_from_lvar_with_offset(LVALUE* result, LVALUE* llvm_stack, int index)
{
    LVALUE* llvm_value = llvm_stack + index;

    result->value = Builder.CreateLoad(llvm_value->value, "lvar"); // load from allocated value

    result->lvar_address_index = llvm_value->lvar_address_index;
    result->lvar_stored = llvm_value->lvar_stored;
    result->kind = kLVKindInt64;
    result->parent_var_num = llvm_value->parent_var_num;
    result->parent_stack = llvm_value->parent_stack;
    result->parent_llvm_stack = llvm_value->parent_llvm_stack;
}

LVALUE get_vm_stack_ptr_value_from_index_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, int align)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

/*
    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, 8*index, true));
    Value* stack_pointer_offset_value = Builder.CreateAdd(lvalue, rvalue, "stack_pointer_offset_value", true, true);
*/
    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, index, true));
    Value* stack_pointer_offset_value = Builder.CreateGEP(lvalue, rvalue, "stack_pointer_offset_value");

    LVALUE result;
    result.value = Builder.CreateAlignedLoad(stack_pointer_offset_value, align, "stack_pointer_offset_value");

    switch(align) {
        case 1:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt8Ty(TheContext));
            result.kind = kLVKindInt8;
            break;

        case 2:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt16Ty(TheContext));
            result.kind = kLVKindInt16;
            break;

        case 4:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt32Ty(TheContext));
            result.kind = kLVKindInt32;
            break;

        case 8:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt64Ty(TheContext));
            result.kind = kLVKindInt64;
            break;
    }

    result.lvar_address_index = -1;
    result.lvar_stored = FALSE;
    result.parent_var_num = 0;
    result.parent_stack = NULL;
    result.parent_llvm_stack = NULL;

    return result;
}

LVALUE get_method_call_result(std::map<std::string, Value*>& params, BasicBlock* current_block)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, -1, true));
    Value* stack_pointer_offset_value = Builder.CreateGEP(lvalue, rvalue, "stack_pointer_offset_value");

    LVALUE result;
    result.value = Builder.CreateAlignedLoad(stack_pointer_offset_value, 8, "stack_pointer_offset_value");

    //result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt64Ty(TheContext));
    result.kind = kLVKindInt64;

    result.lvar_address_index = -1;
    result.lvar_stored = FALSE;
    result.parent_var_num = 0;
    result.parent_stack = NULL;
    result.parent_llvm_stack = NULL;

    return result;
}

void inc_vm_stack_ptr(std::map<std::string, Value*> params, BasicBlock* current_block, int value)
{
    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateLoad(stack_ptr_address_value, "loaded_stack_ptr_address_value");

    Value* lvalue = loaded_stack_ptr_address_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, value, true));
    Value* inc_ptr_value = Builder.CreateGEP(lvalue, rvalue, "inc_ptr_value(1)");

    Builder.CreateStore(inc_ptr_value, stack_ptr_address_value);
}

void push_value_to_vm_stack_ptr_with_aligned(std::map<std::string, Value*> params, BasicBlock* current_block, LVALUE* llvm_value)
{
    Builder.SetInsertPoint(current_block);

    std::string stack_ptr_address_name("stack_ptr_address");
    Value* stack_ptr_address_value = params[stack_ptr_address_name];

    Value* loaded_stack_ptr_address_value = Builder.CreateAlignedLoad(stack_ptr_address_value, 8, "loaded_stack_ptr_address_value");

    /// zero clear///
    Value* zero = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
    Builder.CreateAlignedStore(zero, loaded_stack_ptr_address_value, 8);

    /// trunc ///
    LVALUE llvm_value2;
    llvm_value2 = trunc_value(llvm_value, 64);

    /// store ///
    Builder.CreateAlignedStore(llvm_value2.value, loaded_stack_ptr_address_value, 8);

    inc_vm_stack_ptr(params, current_block, 1);
}

LVALUE get_stack_value_from_index_with_aligned(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, int align)
{
    std::string stack_name("stack");
    Value* stack_address_value = params[stack_name];

    LVALUE result;
    if(index > 0) {
        Value* lvalue = stack_address_value;
        Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, index, true));
        Value* stack_offset_address_value = Builder.CreateGEP(lvalue, rvalue, "stack_offset_address_value");


        result.value = Builder.CreateAlignedLoad(stack_offset_address_value, align, "stack_offset_value");
    }
    else {
        result.value = Builder.CreateAlignedLoad(stack_address_value, align, "stack_offset_value");
    }


    switch(align) {
        case 1:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt8Ty(TheContext));
            result.kind = kLVKindInt8;
            break;

        case 2:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt16Ty(TheContext));
            result.kind = kLVKindInt16;
            break;

        case 4:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt32Ty(TheContext));
            result.kind = kLVKindInt32;
            break;

        case 8:
            result.value = Builder.CreateCast(Instruction::Trunc, result.value, Type::getInt64Ty(TheContext));
            result.kind = kLVKindInt64;
            break;
    }

    result.lvar_address_index = -1;
    result.lvar_stored = FALSE;
    result.parent_var_num = 0;
    result.parent_stack = NULL;
    result.parent_llvm_stack = NULL;

    return result;
}

void llvm_stack_to_vm_stack(LVALUE* llvm_stack_ptr, std::map<std::string, Value*> params, BasicBlock* current_block, int num)
{
    int i;
    for(i=0; i<num; i++) {
        LVALUE* llvm_value = llvm_stack_ptr + i - num;

        push_value_to_vm_stack_ptr_with_aligned(params, current_block, llvm_value);
    }
}

void parent_llvm_stack_to_parent_vm_stack(Value* parent_stack, LVALUE* parent_llvm_stack, BasicBlock* current_block, int parent_var_num)
{
    int i;

    for(i=0; i<parent_var_num; i++) {
        LVALUE* llvm_value = parent_llvm_stack + i;

        LVALUE llvm_value2;
        llvm_value2 = *llvm_value;
        llvm_value2.value = Builder.CreateAlignedLoad(llvm_value->value, 8);
        llvm_value2.kind = kLVKindInt64;

        Value* lvalue = parent_stack;
        Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, i*8, true));
        Value* parent_llvm_stack_address = Builder.CreateGEP(lvalue, rvalue);

        /// zero clear///
        Value* zero = ConstantInt::get(Type::getInt64Ty(TheContext), (uint64_t)0);
        Builder.CreateAlignedStore(zero, parent_llvm_stack_address, 8);

        /// trunc ///
        LVALUE llvm_value3;
        llvm_value3 = trunc_value(&llvm_value2, 64);

        /// store ///
        Builder.CreateAlignedStore(llvm_value3.value, parent_llvm_stack_address, 8);
    }
}

void parent_vm_stack_to_parent_llvm_stack(Value* parent_stack, LVALUE* parent_llvm_stack, BasicBlock* current_block, int parent_var_num)
{
    int i;

    for(i=0; i<parent_var_num; i++) {
        Value* lvalue = parent_stack;
        Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, i, true));
        Value* parent_llvm_stack_address = Builder.CreateGEP(lvalue, rvalue);

        /// load ///
        Value* value = Builder.CreateAlignedLoad(parent_llvm_stack_address, 8);

        LVALUE llvm_value2;
        llvm_value2.value = value;
        llvm_value2.kind = kLVKindInt64;
        llvm_value2.lvar_address_index = -1;
        llvm_value2.lvar_stored = FALSE;
        llvm_value2.parent_var_num = 0;
        llvm_value2.parent_stack = NULL;
        llvm_value2.parent_llvm_stack = NULL;

        /// store ///
        LVALUE* llvm_value = parent_llvm_stack + i;

        Builder.CreateAlignedStore(llvm_value2.value, llvm_value->value, 8);
    }
}

void llvm_give_type_to_params(LVALUE* llvm_stack_ptr, std::map<std::string, Value*> params, BasicBlock* current_block, sCLMethod* method, sCLClass* klass)
{
    int i;

    for(i=0; i<method->mNumParams; i++) {
        LVALUE* param = llvm_stack_ptr - method->mNumParams + i;

        sNodeType* node_type = create_node_type_from_cl_type(method->mParams[i].mType, klass);
        int size = get_var_size(node_type);

        trunc_variable(param, size);
    }
}

void if_value_is_zero_ret_zero(Value* value, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block)
{
    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Value* zero = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));

    Value* comp = Builder.CreateICmpEQ(value, zero, "ifcond");

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Builder.CreateRet(ret_value);

    Builder.SetInsertPoint(entry_ifend);
    *current_block = entry_ifend;
}

void if_value_is_null_ret_zero(Value* value, int value_bit, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block)
{
    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Value* zero = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Value* null_ptr = Builder.CreateCast(Instruction::IntToPtr, zero, PointerType::get(IntegerType::get(TheContext, value_bit), 0));

    Value* comp = Builder.CreateICmpEQ(value, null_ptr, "ifcond");

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Builder.CreateRet(ret_value);

    Builder.SetInsertPoint(entry_ifend);
    *current_block = entry_ifend;
}

void store_value_to_lvar_with_offset(std::map<std::string, Value*>& params, BasicBlock* current_block, int index, LVALUE* llvm_value)
{
    std::string lvar_arg_name("lvar");
    Value* lvar_value = params[lvar_arg_name];
    
    Value* lvalue = lvar_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, index, true));
    Value* lvar_offset_value = Builder.CreateGEP(lvalue, rvalue, "lvar_offset_value");

    LVALUE llvm_value2;
    llvm_value2 = trunc_value(llvm_value, 64);

    Builder.CreateAlignedStore(llvm_value2.value, lvar_offset_value, 8);
}

StructType* get_vm_info_struct_type()
{
    StructType* result_type = StructType::create(TheContext, "vm_info_struct");
    std::vector<Type*> fields;
    Type* field_type1 = PointerType::get(IntegerType::get(TheContext, 8), 0); // try_catch_label_name
    fields.push_back(field_type1);
    Type* field_type2 = PointerType::get(IntegerType::get(TheContext, 64), 0); // current_stack
    fields.push_back(field_type2);
    Type* field_type3 = IntegerType::get(TheContext, 32); // current_var_num
    fields.push_back(field_type3);
    Type* field_type4 = PointerType::get(IntegerType::get(TheContext, 8), 0); // sname
    fields.push_back(field_type4);
    Type* field_type5 = IntegerType::get(TheContext, 32);                       // sline
    fields.push_back(field_type5);
    Type* field_type6 = PointerType::get(IntegerType::get(TheContext, 8), 0);   // sname2
    fields.push_back(field_type6);
    Type* field_type7 = IntegerType::get(TheContext, 32);                       // sline2
    fields.push_back(field_type7);
    Type* field_type8 = IntegerType::get(TheContext, 32);                       // try_offset
    fields.push_back(field_type8);
    Type* field_type9 = PointerType::get(PointerType::get(IntegerType::get(TheContext, 8), 0), 0); // try_pc
    fields.push_back(field_type9);
    Type* field_type10 = PointerType::get(IntegerType::get(TheContext, 64), 0);      // try_code
    fields.push_back(field_type10);
    Type* field_type11 = PointerType::get(IntegerType::get(TheContext, 64), 0);      // running_class
    fields.push_back(field_type11);
    Type* field_type12 = PointerType::get(IntegerType::get(TheContext, 64), 0);      // running_method
    fields.push_back(field_type12);
    Type* field_type13 = IntegerType::get(TheContext, 64);                           // stack_id
    fields.push_back(field_type13);
    Type* field_type14 = ArrayType::get(IntegerType::get(TheContext, 8), EXCEPTION_MESSAGE_MAX);  // exception_message
    fields.push_back(field_type14);
    Type* field_type15 = ArrayType::get(PointerType::get(IntegerType::get(TheContext, 8), 0), STACK_TRACE_MAX);  // running_class_for_stack_trace
    fields.push_back(field_type15);
    Type* field_type16 = ArrayType::get(IntegerType::get(TheContext, 32), STACK_TRACE_MAX);  // running_method_for_stack_trace
    fields.push_back(field_type16);

    if(result_type->isOpaque()) {
        result_type->setBody(fields, false);
    }

    return result_type;
}

AllocaInst* create_entry_block_alloca(Function* function, int index)
{
    IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());
    char var_name[128];
    snprintf(var_name, 128, "lvar$%d$", index);
    return builder.CreateAlloca(Type::getInt64Ty(TheContext), 0, var_name);
}

void call_entry_exception_object_with_class_name2(std::map<std::string, Value *> params, char* class_name, char* message)
{
    Function* entry_exception_object_fun = TheModule->getFunction("entry_exception_object_with_class_name2");

    std::vector<Value*> params2;

    std::string stack_ptr_address_name("stack_ptr_address");
    Value* param1 = params[stack_ptr_address_name];
    params2.push_back(param1);

    std::string stack_value_name("stack");
    Value* param2 = params[stack_value_name];
    params2.push_back(param2);

    std::string var_num_value_name("var_num");
    Value* param3 = params[var_num_value_name];
    params2.push_back(param3);

    std::string info_value_name("info");
    Value* param4 = params[info_value_name];
    params2.push_back(param4);

    Value* param5 = llvm_create_string(class_name);
    params2.push_back(param5);

    Value* param6 = llvm_create_string(message);
    params2.push_back(param6);

    (void)Builder.CreateCall(entry_exception_object_fun, params2);
}

void if_value_is_zero_entry_exception_object(Value* value, int value_size, BOOL value_is_float, BOOL value_is_double, std::map<std::string, Value *> params, Function* function, BasicBlock** current_block, char* class_name, char* message)
{
    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Value* rvalue;
    Value* comp;
    if(value_is_float) {
        double dvalue = 0.0;
        rvalue = ConstantFP::get(TheContext, llvm::APFloat(dvalue)); 
        rvalue = Builder.CreateCast(Instruction::FPTrunc, rvalue, Type::getFloatTy(TheContext));

        comp = Builder.CreateFCmpOEQ(value, rvalue, "ifcond");
    }
    else if(value_is_double) {
        double dvalue = 0.0;
        rvalue = ConstantFP::get(TheContext, llvm::APFloat(dvalue)); 
        rvalue = Builder.CreateCast(Instruction::FPExt, rvalue, Type::getDoubleTy(TheContext));

        comp = Builder.CreateFCmpOEQ(value, rvalue, "ifcond");
    }
    else {
        rvalue = ConstantInt::get(TheContext, llvm::APInt(value_size, 0, true));

        comp = Builder.CreateICmpEQ(value, rvalue, "ifcond");
    }

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    call_entry_exception_object_with_class_name2(params, class_name, message);

    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Builder.CreateRet(ret_value);

    Builder.SetInsertPoint(entry_ifend);
    *current_block = entry_ifend;
}

void vm_lvar_to_llvm_lvar(LVALUE* llvm_stack,std::map<std::string, Value*>& params, BasicBlock* current_block, int var_num)
{
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value = get_stack_value_from_index_with_aligned(params, current_block, i, 8);
        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value, TRUE);
    }
}

void finish_method_call(Value* result, std::map<std::string, Value *> params, BasicBlock** current_block, Function* function, char** try_catch_label_name)
{
    // if result is FALSE ret 0
    Value* comp = Builder.CreateICmpNE(result, ConstantInt::get(TheContext, llvm::APInt(32, 1, true)), "ifcond");

    BasicBlock* then_block = BasicBlock::Create(TheContext, "then_block", function);
    BasicBlock* entry_ifend = BasicBlock::Create(TheContext, "entry_ifend", function);

    Builder.CreateCondBr(comp, then_block, entry_ifend);

    Builder.SetInsertPoint(then_block);

    Function* try_catch_label_name_fun = TheModule->getFunction("get_try_catch_label_name");

    std::vector<Value*> params2;

    std::string info_value_name("info");
    Value* info_value = params[info_value_name];
    params2.push_back(info_value);

    Value* try_catch_label_name_value = Builder.CreateCall(try_catch_label_name_fun, params2);

    Value* zero = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Value* null_ptr = Builder.CreateCast(Instruction::IntToPtr, zero, PointerType::get(IntegerType::get(TheContext, 8), 0));

    Value* comp2 = Builder.CreateICmpNE(try_catch_label_name_value, null_ptr, "catchcond");

    BasicBlock* then_block2 = BasicBlock::Create(TheContext, "then_block_b", function);
    BasicBlock* entry_ifend2 = BasicBlock::Create(TheContext, "entry_ifend_b", function);

    Builder.CreateCondBr(comp2, then_block2, entry_ifend2);

    Builder.SetInsertPoint(then_block2);

    if(*try_catch_label_name == nullptr) {
        Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
        Builder.CreateRet(ret_value);
    }
    else {
        std::string try_catch_label_name_string(*try_catch_label_name);
        BasicBlock* label = TheLabels[try_catch_label_name_string];
        if(label == nullptr) {
            label = BasicBlock::Create(TheContext, *try_catch_label_name, function);
            TheLabels[try_catch_label_name_string] = label;
        }

        if(label == nullptr) {
            Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
            Builder.CreateRet(ret_value);
        }
        else {
            Function* try_fun = TheModule->getFunction("try_function");

            std::vector<Value*> params2;

            std::string info_value_name("info");
            Value* vminfo_value = params[info_value_name];
            params2.push_back(vminfo_value);

            Value* catch_label_name_offset_value  = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);
            params2.push_back(catch_label_name_offset_value);

            Value* try_offset_value = ConstantInt::get(Type::getInt32Ty(TheContext), (uint32_t)0);
            params2.push_back(try_offset_value);

            std::string code_value_name("code");
            Value* code_value = params[code_value_name];
            params2.push_back(code_value);

            std::string constant_value_name("constant");
            Value* constant_value = params[constant_value_name];
            params2.push_back(constant_value);

            (void)Builder.CreateCall(try_fun, params2);

            Builder.CreateBr(label);
        }
    }

    Builder.SetInsertPoint(entry_ifend2);
    
    Value* ret_value = ConstantInt::get(TheContext, llvm::APInt(32, 0, true));
    Builder.CreateRet(ret_value);

    Builder.SetInsertPoint(entry_ifend); 
    *current_block = entry_ifend;
}

void lvar_of_vm_to_lvar_of_llvm(std::map<std::string, Value *> params, BasicBlock* current_block, LVALUE* llvm_stack, int var_num)
{
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value = get_stack_value_from_index_with_aligned(params, current_block, i, 8);
        store_llvm_value_to_lvar_with_offset(llvm_stack, i, &llvm_value, TRUE);
    }
}

void lvar_of_llvm_to_lvar_of_vm(std::map<std::string, Value *> params, BasicBlock* current_block, LVALUE* llvm_stack, int var_num)
{
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value;
        get_llvm_value_from_lvar_with_offset(&llvm_value, llvm_stack, i);

        if(llvm_value.value != 0) {
            store_value_to_lvar_with_offset(params, current_block, i, &llvm_value);
        }
    }
}

void trunc_value_from_inst(LVALUE* value, int inst) 
{
    switch(inst) {
        case OP_ANDAND: 
        case OP_OROR:
            *value = trunc_value(value, 1);
            break;

        case OP_BADD:
        case OP_BSUB:
        case OP_BMULT:
        case OP_BDIV:
        case OP_BMOD: 
        case OP_BLSHIFT:
        case OP_BRSHIFT:
        case OP_BAND: 
        case OP_BXOR: 
        case OP_BOR: 
        case OP_BCOMPLEMENT:
        case OP_BEQ:
        case OP_BNOTEQ:
        case OP_BGT:
        case OP_BLE:
        case OP_BGTEQ:
        case OP_BLEEQ:
        case OP_UBADD: 
        case OP_UBSUB:
        case OP_UBMULT:
        case OP_UBDIV:
        case OP_UBMOD:
        case OP_UBLSHIFT:
        case OP_UBRSHIFT: 
        case OP_UBAND:
        case OP_UBXOR:
        case OP_UBOR:
        case OP_UBCOMPLEMENT:
        case OP_UBEQ:
        case OP_UBNOTEQ:
        case OP_UBGT:
        case OP_UBLE: 
        case OP_UBGTEQ: 
        case OP_UBLEEQ:
            *value = trunc_value(value, 8);
            break;

        case OP_SADD:
        case OP_SSUB:
        case OP_SMULT:
        case OP_SDIV:
        case OP_SMOD:
        case OP_SLSHIFT:
        case OP_SRSHIFT:
        case OP_SAND:
        case OP_SXOR:
        case OP_SOR:
        case OP_SCOMPLEMENT:
        case OP_SEQ:
        case OP_SNOTEQ:
        case OP_SGT:
        case OP_SLE:
        case OP_SGTEQ:
        case OP_SLEEQ:
        case OP_USADD:
        case OP_USSUB:
        case OP_USMULT:
        case OP_USDIV:
        case OP_USMOD:
        case OP_USLSHIFT:
        case OP_USRSHIFT:
        case OP_USAND:
        case OP_USXOR:
        case OP_USOR:
        case OP_USCOMPLEMENT:
        case OP_USEQ:
        case OP_USNOTEQ:
        case OP_USGT:
        case OP_USLE:
        case OP_USGTEQ:
        case OP_USLEEQ:
            *value = trunc_value(value, 16);
            break;

        case OP_IADD: 
        case OP_ISUB:
        case OP_IMULT:
        case OP_IDIV:
        case OP_IMOD:
        case OP_ILSHIFT: 
        case OP_IRSHIFT:
        case OP_IAND:
        case OP_IXOR: 
        case OP_IOR:
        case OP_ICOMPLEMENT:
        case OP_IEQ:
        case OP_INOTEQ: 
        case OP_IGT: 
        case OP_ILE: 
        case OP_ILEEQ: 
        case OP_IGTEQ: 
        case OP_UIADD:
        case OP_UISUB:
        case OP_UIMULT:
        case OP_UIDIV:
        case OP_UIMOD:
        case OP_UILSHIFT:
        case OP_UIRSHIFT:
        case OP_UIAND:
        case OP_UIXOR:
        case OP_UIOR:
        case OP_UICOMPLEMENT:
        case OP_UIEQ:
        case OP_UINOTEQ:
        case OP_UILE:
        case OP_UIGT:
        case OP_UIGTEQ:
        case OP_UILEEQ: 
        case OP_CADD:
        case OP_CSUB:
        case OP_CEQ:
        case OP_CNOTEQ:
        case OP_CGT:
        case OP_CLE:
        case OP_CGTEQ:
        case OP_CLEEQ:
        case OP_OBJ_IDENTIFY:
        case OP_LOGICAL_DENIAL:
        case OP_REGEQ: 
        case OP_REGNOTEQ:
            *value = trunc_value(value, 32);
            break;

        case OP_LADD:
        case OP_LSUB:
        case OP_LMULT:
        case OP_LMOD: 
        case OP_LDIV:
        case OP_LLSHIFT: 
        case OP_LRSHIFT:
        case OP_LAND: 
        case OP_LXOR: 
        case OP_LOR: 
        case OP_LCOMPLEMENT:
        case OP_LEQ: 
        case OP_LNOTEQ: 
        case OP_LGT:
        case OP_LLE:
        case OP_LGTEQ:
        case OP_LLEEQ:
        case OP_ULADD: 
        case OP_ULMOD:
        case OP_ULLSHIFT:
        case OP_ULRSHIFT:
        case OP_ULAND:
        case OP_ULXOR:
        case OP_ULOR:
        case OP_ULCOMPLEMENT:
        case OP_ULEQ: 
        case OP_ULNOTEQ: 
        case OP_ULGT: 
        case OP_ULLE: 
        case OP_ULGTEQ: 
        case OP_ULLEEQ:
            *value = trunc_value(value, 64);
            break;

        case OP_FADD:
        case OP_FSUB:
        case OP_FMULT:
        case OP_FDIV:
        case OP_FEQ:
        case OP_FNOTEQ:
        case OP_FGT:
        case OP_FLE:
        case OP_FGTEQ:
        case OP_FLEEQ:
            *value = trunc_value_to_float_or_double(value, 32);
            break;

        case OP_DADD:
        case OP_DSUB:
        case OP_DMULT:
        case OP_DDIV:
        case OP_DEQ:
        case OP_DNOTEQ:
        case OP_DGT:
        case OP_DLE:
        case OP_DGTEQ:
        case OP_DLEEQ:
            *value = trunc_value_to_float_or_double(value, 64);
            break;

        case OP_PADD: 
        case OP_PEQ: 
        case OP_PNOTEQ: 
        case OP_PGT: 
        case OP_PLE:
        case OP_PGTEQ: 
        case OP_PLEEQ: 
            *value = trunc_value_to_pointer(value);
            break;
    }
}

void store_value_to_vm_lvar(std::map<std::string, Value*>& params, BasicBlock* current_block, int offset, LVALUE* llvm_value)
{
    std::string lvar_arg_name("lvar");
    Value* lvar_value = params[lvar_arg_name];

    Value* lvalue = lvar_value;
    Value* rvalue = ConstantInt::get(TheContext, llvm::APInt(64, offset, true));
    Value* lvar_offset_value = Builder.CreateGEP(lvalue, rvalue, "lvar_offset_value");

    /// 0 clear align 8 byte ///
    Value* zero = ConstantInt::get(TheContext, llvm::APInt(64, 0, true));
    Builder.CreateAlignedStore(zero, lvar_offset_value, 8);

    /// trunc ///
    LVALUE llvm_value2;
    llvm_value2 = trunc_value(llvm_value, 64);

    /// go ///
    Builder.CreateAlignedStore(llvm_value2.value, lvar_offset_value, 8);
}

void llvm_lvar_to_vm_lvar(LVALUE* llvm_stack,std::map<std::string, Value*>& params, BasicBlock* current_block, int var_num)
{
    int i;
    for(i=0; i<var_num; i++) {
        LVALUE llvm_value;
        get_llvm_value_from_lvar_with_offset(&llvm_value, llvm_stack, i);

        if(llvm_value.lvar_stored) {
            store_value_to_vm_lvar(params, current_block, i, &llvm_value);
        }
    }
}

void call_vm_mutex_on()
{
    Function* fun = TheModule->getFunction("vm_mutex_on");
    std::vector<Value*> params;
    (void)Builder.CreateCall(fun, params);
}

void call_vm_mutex_off()
{
    Function* fun = TheModule->getFunction("vm_mutex_off");
    std::vector<Value*> params;
    (void)Builder.CreateCall(fun, params);
}

void call_vm_mutex_on2(std::map<std::string, Value *> params)
{
    Function* fun = TheModule->getFunction("vm_mutex_on2");
    std::vector<Value*> params2;

    std::string info_value_name("info");
    Value* param1 = params[info_value_name];
    params2.push_back(param1);

    (void)Builder.CreateCall(fun, params2);
}

void call_vm_mutex_off2(std::map<std::string, Value *> params)
{
    Function* fun = TheModule->getFunction("vm_mutex_off2");
    std::vector<Value*> params2;

    std::string info_value_name("info");
    Value* param1 = params[info_value_name];
    params2.push_back(param1);

    (void)Builder.CreateCall(fun, params2);
}



}
