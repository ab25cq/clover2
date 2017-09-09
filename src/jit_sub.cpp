#include "jit_common.hpp"

extern "C"
{

LVALUE trunc_value(LVALUE* llvm_value, int size)
{
    LVALUE result = *llvm_value;

    Type* llvm_type = llvm_value->value->getType();
    Type::TypeID type_id = llvm_type->getTypeID();

    /// Constant Int ///
    if(llvm_value->constant_int_value) {
        ConstantInt* constant_int_value = dynamic_cast<ConstantInt*>(llvm_value->value);
        APInt apint_value = constant_int_value->getValue();

        int bit_width = constant_int_value->getBitWidth();
        bool signed_value = apint_value.isSignBit();

        switch(size) {
            case 1:
                if(signed_value) {
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(1));
                }
                else {
                    result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(1));
                }
                break;

            case 8:
                if(signed_value) {
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(8));
                }
                else {
                    result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(8));
                }
                break;

            case 16:
                if(signed_value) {
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(16));
                }
                else {
                    result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(16));
                }
                break;

            case 32:
                if(signed_value) {
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(32));
                }
                else {
                    result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(32));
                }
                break;

            case 64:
                if(signed_value) {
                    result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(64));
                }
                else {
                    result.value = ConstantInt::get(TheContext, apint_value.zextOrTrunc(64));
                }
                break;
        }
    }
    else if(llvm_value->constant_float_value) {
        ConstantFP* constant_float_value = dynamic_cast<ConstantFP*>(llvm_value->value);
        const APFloat apfloat_value = constant_float_value->getValueAPF();

        switch(size) {
            case 1: {
                APInt apint_value = apfloat_value.bitcastToAPInt();
                ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(1));
                }
                break;

            case 8: {
                APInt apint_value = apfloat_value.bitcastToAPInt();
                ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(8));
                }
                break;

            case 16: {
                APInt apint_value = apfloat_value.bitcastToAPInt();
                ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(16));
                }
                break;

            case 32: {
                APInt apint_value = apfloat_value.bitcastToAPInt();
                ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(32));
                }
                break;

            case 64: {
                APInt apint_value = apfloat_value.bitcastToAPInt();
                ConstantInt* value = ConstantInt::get(TheContext, apint_value);
                result.value = ConstantInt::get(TheContext, apint_value.sextOrTrunc(64));
                }
                break;
        }
    }
    /// Memory ///
    else if(type_id == Type::TypeID::FloatTyID) {
        switch(size) {
            case 1:
                result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt1Ty(TheContext));
                break;

            case 8:
                result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt8Ty(TheContext));
                break;

            case 16:
                result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt16Ty(TheContext));
                break;

            case 32:
                result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt32Ty(TheContext));
                break;

            case 64:
                result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt32Ty(TheContext));
                result.value = Builder.CreateCast(Instruction::ZExt, result.value, Type::getInt64Ty(TheContext));
                break;
        }
    }
    else if(type_id == Type::TypeID::DoubleTyID) {
        switch(size) {
            case 1:
                result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt1Ty(TheContext));
                break;

            case 8:
                result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt8Ty(TheContext));
                break;

            case 16:
                result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt16Ty(TheContext));
                break;

            case 32:
                result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt32Ty(TheContext));
                break;

            case 64:
                result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
                break;
        }
    }
    else if(llvm_type->isPointerTy()) {
        switch(size) {
            case 1:
                result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt1Ty(TheContext));
                break;

            case 8:
                result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt8Ty(TheContext));
                break;

            case 16:
                result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt16Ty(TheContext));
                break;

            case 32:
                result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt32Ty(TheContext));
                break;

            case 64:
                result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt64Ty(TheContext));
                break;
        }
    }
    else {
        switch(size) {
            case 1:
                if(!llvm_type->isIntegerTy(1)) {
                    result.value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt1Ty(TheContext));
                }
                break;

            case 8:
                if(llvm_type->isIntegerTy(1)) {
                    result.value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt8Ty(TheContext));
                }
                else if(!llvm_type->isIntegerTy(8)) {
                    result.value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt8Ty(TheContext));
                }
                break;

            case 16:
                if(llvm_type->isIntegerTy(1) || llvm_type->isIntegerTy(8)) {
                    result.value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt16Ty(TheContext));
                }
                else if(llvm_type->isIntegerTy(16)) {
                }
                else {
                    result.value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt16Ty(TheContext));
                }
                break;

            case 32:
                if(llvm_type->isIntegerTy(1) ||llvm_type->isIntegerTy(8) || llvm_type->isIntegerTy(16)) {
                    result.value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt32Ty(TheContext));
                }
                else {
                    result.value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt32Ty(TheContext));
                }
                break;

            case 64:
                if(!llvm_type->isIntegerTy(64)) {
                    result.value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt64Ty(TheContext));
                }
                break;
        }
    }

    return result;
}

// size --> 32: float 64:double
LVALUE trunc_value_to_float_or_double(LVALUE* llvm_value, int size)
{
    LVALUE result = *llvm_value;

    Type* llvm_type = llvm_value->value->getType();
    Type::TypeID type_id = llvm_type->getTypeID();

    /// Constant Int ///
    if(llvm_value->constant_int_value) {
        ConstantInt* constant_int_value = dynamic_cast<ConstantInt*>(llvm_value->value);
        APInt apint_value = constant_int_value->getValue();

        int bit_width = constant_int_value->getBitWidth();
        bool signed_value = apint_value.isSignBit();

        switch(size) {
            case 32:
                if(signed_value) {
                    result.value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getFloatTy(TheContext));
                }
                else {
                    result.value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext));
                }
                break;

            case 64:
                if(signed_value) {
                    result.value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
                }
                else {
                    result.value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
                }
                break;
        }
    }
    else if(llvm_value->constant_float_value) {
    }
    /// Memory ///
    else if(type_id == Type::TypeID::FloatTyID) {
        switch(size) {
            case 64:
                result.value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext));
                break;
        }
    }
    else if(type_id == Type::TypeID::DoubleTyID) {
        switch(size) {
            case 32:
                result.value = Builder.CreateCast(Instruction::FPTrunc, llvm_value->value, Type::getFloatTy(TheContext));
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
                break;

            case 64:
                result.value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt64Ty(TheContext));
                result.value = Builder.CreateCast(Instruction::UIToFP, result.value, Type::getDoubleTy(TheContext));
                break;
        }
    }
    else {
        switch(size) {
            case 32:
                result.value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext));
                break;

            case 64:
                result.value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
                break;
        }
    }

    return result;
}

LVALUE trunc_value_to_pointer(LVALUE* llvm_value)
{
    LVALUE result = *llvm_value;

    Type* llvm_type = llvm_value->value->getType();
    Type::TypeID type_id = llvm_type->getTypeID();

    /// Constant Int ///
    if(llvm_value->constant_int_value) {
        ConstantInt* constant_int_value = dynamic_cast<ConstantInt*>(llvm_value->value);
        APInt apint_value = constant_int_value->getValue();

        int bit_width = constant_int_value->getBitWidth();
        bool signed_value = apint_value.isSignBit();

        result.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 8), 0));
    }
    else if(llvm_value->constant_float_value) {
        ConstantFP* constant_float_value = dynamic_cast<ConstantFP*>(llvm_value->value);
        const APFloat apfloat_value = constant_float_value->getValueAPF();

        result.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 8), 0));
    }
    /// Memory ///
    else if(type_id == Type::TypeID::FloatTyID) {
        result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
        result.value = Builder.CreateCast(Instruction::IntToPtr, result.value, PointerType::get(IntegerType::get(TheContext, 8), 0));
    }
    else if(type_id == Type::TypeID::DoubleTyID) {
        result.value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getInt64Ty(TheContext));
        result.value = Builder.CreateCast(Instruction::IntToPtr, result.value, PointerType::get(IntegerType::get(TheContext, 8), 0));
    }
    else if(llvm_type->isPointerTy()) {
    }
    else {
        result.value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 8), 0));
    }

    return result;
}

void trunc_variable(LVALUE* llvm_value, int size)
{
    switch(size) {
        case 1:
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt8Ty(TheContext), "XXX");

            break;

        case 2:
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt16Ty(TheContext));
            break;

        case 4:
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt32Ty(TheContext));
            break;

        case 8:
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt64Ty(TheContext));
            break;

        case 16:
            llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext));
            break;

        case 32:
            llvm_value->value = Builder.CreateCast(Instruction::BitCast, llvm_value->value, Type::getDoubleTy(TheContext));
            break;

        case 64:
            llvm_value->value = Builder.CreateCast(Instruction::IntToPtr, llvm_value->value, PointerType::get(IntegerType::get(TheContext, 8), 0));
            break;
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
            break;

        case OP_UBYTE_TO_CDOUBLE_CAST:
        case OP_USHORT_TO_CDOUBLE_CAST:
        case OP_UINT_TO_CDOUBLE_CAST:
        case OP_CHAR_TO_CDOUBLE_CAST:
        case OP_ULONG_TO_CDOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            llvm_value->value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext), "fvalue");
            break;

        case OP_FLOAT_TO_CDOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext), "fvalue");
            break;

        case OP_DOUBLE_TO_CDOUBLE_CAST:
            break;

        case OP_BYTE_TO_CFLOAT_CAST:
        case OP_SHORT_TO_CFLOAT_CAST:
        case OP_INT_TO_CFLOAT_CAST:
        case OP_LONG_TO_CFLOAT_CAST:
        case OP_BOOL_TO_CFLOAT_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            break;

        case OP_UBYTE_TO_CFLOAT_CAST:
        case OP_USHORT_TO_CFLOAT_CAST:
        case OP_UINT_TO_CFLOAT_CAST:
        case OP_CHAR_TO_CFLOAT_CAST:
        case OP_ULONG_TO_CFLOAT_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
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
            break;

        case OP_FLOAT_TO_INTEGER_CAST:
        case OP_DOUBLE_TO_INTEGER_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPToSI, llvm_value->value, Type::getInt32Ty(TheContext));
            break;

        case OP_BYTE_TO_INTEGER_CAST:
        case OP_UBYTE_TO_INTEGER_CAST:
        case OP_SHORT_TO_INTEGER_CAST:
        case OP_USHORT_TO_INTEGER_CAST:
        case OP_INT_TO_INTEGER_CAST:
        case OP_UINT_TO_INTEGER_CAST:
        case OP_LONG_TO_INTEGER_CAST:
        case OP_ULONG_TO_INTEGER_CAST:
        case OP_CHAR_TO_INTEGER_CAST:
        case OP_POINTER_TO_INTEGER_CAST:
        case OP_BOOL_TO_INTEGER_CAST:{
            LVALUE llvm_value2 = trunc_value(llvm_value, 32);

            llvm_value->value = llvm_value2.value;
            }
            break;

        case OP_FLOAT_TO_CFLOAT_CAST:
            break;

        case OP_DOUBLE_TO_CFLOAT_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPTrunc, llvm_value->value, Type::getFloatTy(TheContext), "fvalue");
            break;


        case OP_CBYTE_TO_SHORT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::SExt, llvm_value->value, Type::getInt16Ty(TheContext), "value2");
            break;

        case OP_CBYTE_TO_INT_CAST:
        case OP_CSHORT_TO_INT_CAST : 
            llvm_value->value = Builder.CreateCast(Instruction::SExt, llvm_value->value, Type::getInt32Ty(TheContext), "value2");
            break;

        case OP_CBYTE_TO_LONG_CAST:
        case OP_CSHORT_TO_LONG_CAST : 
        case OP_INTEGER_TO_LONG_CAST:
        case OP_CBOOL_TO_LONG_CAST:
        case OP_CFLOAT_TO_LONG_CAST : 
        case OP_CDOUBLE_TO_LONG_CAST : 
            llvm_value->value = Builder.CreateCast(Instruction::SExt, llvm_value->value, Type::getInt64Ty(TheContext), "value2");
            break;

        case OP_CBYTE_TO_USHORT_CAST:
        case OP_CUBYTE_TO_SHORT_CAST:
        case OP_CUBYTE_TO_USHORT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::ZExt, llvm_value->value, Type::getInt16Ty(TheContext), "value2");
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
            break;


        case OP_CBYTE_TO_FLOAT_CAST:
        case OP_CSHORT_TO_FLOAT_CAST:
        case OP_INTEGER_TO_FLOAT_CAST:
        case OP_CLONG_TO_FLOAT_CAST: 
        case OP_CBOOL_TO_FLOAT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getFloatTy(TheContext));
            break;



        case OP_CBYTE_TO_DOUBLE_CAST:
        case OP_CSHORT_TO_DOUBLE_CAST:
        case OP_INTEGER_TO_DOUBLE_CAST:
        case OP_CLONG_TO_DOUBLE_CAST: 
        case OP_CBOOL_TO_DOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::SIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
            break;




        case OP_CUBYTE_TO_FLOAT_CAST:
        case OP_CUSHORT_TO_FLOAT_CAST:
        case OP_UINTEGER_TO_FLOAT_CAST:
        case OP_CULONG_TO_FLOAT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getFloatTy(TheContext));
            break;





        case OP_CUBYTE_TO_DOUBLE_CAST: 
        case OP_CUSHORT_TO_DOUBLE_CAST:
        case OP_UINTEGER_TO_DOUBLE_CAST:
        case OP_CULONG_TO_DOUBLE_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::UIToFP, llvm_value->value, Type::getDoubleTy(TheContext));
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
            break;

        case OP_CLONG_TO_INT_CAST:
        case OP_CLONG_TO_UINT_CAST:
        case OP_CULONG_TO_INT_CAST:
        case OP_CULONG_TO_UINT_CAST:
        case OP_CULONG_TO_CHAR_CAST:
        case OP_CCHAR_TO_INT_CAST : 
        case OP_CLONG_TO_CHAR_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::Trunc, llvm_value->value, Type::getInt32Ty(TheContext), "value2");
            break;


        case OP_CPOINTER_TO_BYTE_CAST:
        case OP_CPOINTER_TO_UBYTE_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt8Ty(TheContext), "value2");
            break;

        case OP_CPOINTER_TO_SHORT_CAST:
        case OP_CPOINTER_TO_USHORT_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt16Ty(TheContext), "value2");
            break;

        case OP_CPOINTER_TO_INT_CAST : 
        case OP_CPOINTER_TO_UINT_CAST :
        case OP_CPOINTER_TO_CHAR_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt32Ty(TheContext), "value2");
            break;

        case OP_CPOINTER_TO_LONG_CAST : 
        case OP_CPOINTER_TO_ULONG_CAST :
            llvm_value->value = Builder.CreateCast(Instruction::PtrToInt, llvm_value->value, Type::getInt64Ty(TheContext), "value2");
            break;




        case OP_CFLOAT_TO_DOUBLE_CAST: 
            llvm_value->value = Builder.CreateCast(Instruction::FPExt, llvm_value->value, Type::getDoubleTy(TheContext));
            break;

        case OP_CDOUBLE_TO_FLOAT_CAST:
            llvm_value->value = Builder.CreateCast(Instruction::FPTrunc, llvm_value->value, Type::getFloatTy(TheContext));
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
            }
            break;
    }
}

}
