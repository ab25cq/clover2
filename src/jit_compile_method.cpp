#include "jit_common.hpp"
#include <signal.h>

#if LLVM_VERSION_MAJOR >= 4
#include "llvm/Bitcode/BitcodeWriter.h"
#else
#include "llvm/Bitcode/ReaderWriter.h"
#endif

extern "C"
{

static BOOL compile_jit_methods(sCLClass* klass)
{
printf("klass %s\n", CLASS_NAME(klass));
    char module_name[PATH_MAX + 128];
    snprintf(module_name, PATH_MAX, "Module %s", CLASS_NAME(klass));
    TheModule = new Module(module_name, TheContext);

    TheFPM = llvm::make_unique<legacy::FunctionPassManager>(TheModule);

    //TheFPM->add(createInstructionCombiningPass());
    TheFPM->add(createReassociatePass());
    //TheFPM->add(createGVNPass());
    TheFPM->add(createCFGSimplificationPass());
    TheFPM->doInitialization();

/*
    //TheFPM.add(new DataLayout(*EE->getDataLayout());

    //TheFPM->add(createBasicAliasAnalysisPass());
    TheFPM->add(createInstructionCombiningPass());
    TheFPM->add(createReassociatePass());
    //TheFPM->add(createNewGVNPass());
    TheFPM->add(createNewGVNPass());
    TheFPM->add(createCFGSimplificationPass());
*/

    TheFPM->doInitialization();

    create_internal_functions();
    TheLabels.clear();

    int i;
    int num_compiled_method = 0;

    if(!(klass->mFlags & CLASS_FLAGS_INTERFACE)) {
        for(i=0; i<klass->mNumMethods; i++) {
            sCLMethod* method = klass->mMethods + i;

            if(strcmp(METHOD_NAME2(klass, method), "initialize") != 0 && strcmp(METHOD_NAME2(klass, method), "finalize") != 0 && !(method->mFlags & METHOD_FLAGS_NATIVE) && !(method->mFlags & METHOD_FLAGS_C_FUNCTION))
            {
                char method_path2[METHOD_NAME_MAX + 128];
                create_method_path_for_jit(klass, method, method_path2, METHOD_NAME_MAX + 128);

printf("(%s)\n", method_path2);

                sByteCode* code = &method->mByteCodes;
                sConst* constant = &klass->mConst;

                int var_num = method->mVarNum;
                int real_param_num = method->mNumParams + ((method->mFlags & METHOD_FLAGS_CLASS_METHOD) ? 0:1);

                if(!compile_to_native_code(code, constant, klass, var_num, real_param_num, method_path2, FALSE, FALSE)) {
                    return FALSE;
                }

                num_compiled_method++;
            }
        }

        for(i=0; i<klass->mNumBlockObjects; i++) {
            sCLBlockObject* block_object = klass->mBlockObjects + i;

            char func_path[METHOD_NAME_MAX + 128];
            create_block_path_for_jit(klass, i, func_path, METHOD_NAME_MAX + 128);

            sByteCode* code = &block_object->mByteCodes;
            sConst* constant = &block_object->mConst;

            int var_num = block_object->mVarNum;
            int real_param_num = block_object->mNumParams;

            if(!compile_to_native_code(code, constant, klass, var_num, real_param_num, func_path, !block_object->mLambda, TRUE)) 
            {
                return FALSE;
            }

            num_compiled_method++;
        }
    }

    if(num_compiled_method > 0) {
#if LLVM_VERSION_MAJOR >= 4
        char path[PATH_MAX];
        snprintf(path, PATH_MAX, "%s.bc", CLASS_NAME(klass));

        (void)unlink(path);

        std::error_code ecode;
        llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

        std::string err_str;
        raw_string_ostream err_ostream(err_str);

        verifyModule(*TheModule);

        llvm::WriteBitcodeToFile(TheModule, output_stream, true);
        output_stream.flush();
#else
        char path[PATH_MAX];
        snprintf(path, PATH_MAX, "%s.bc", CLASS_NAME(klass));

        (void)unlink(path);

        std::error_code ecode;
        llvm::raw_fd_ostream output_stream(path, ecode, llvm::sys::fs::F_None);

        std::string err_str;
        raw_string_ostream err_ostream(err_str);

        verifyModule(*TheModule);

        llvm::WriteBitcodeToFile(TheModule, output_stream, true);
        output_stream.flush();
#endif
    }

    delete TheModule;

    return TRUE;
}

BOOL jit_compile_class(sCLClass* klass)
{
    jit_init();

    if(!compile_jit_methods(klass)) {
        jit_final();
        return FALSE;
    }

    jit_final();

    return TRUE;
}

}
