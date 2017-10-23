#include "jit_common.hpp"

extern "C"
{

static BOOL compile_jit_methods(sCLClass* klass)
{
    char module_name[PATH_MAX + 128];
    snprintf(module_name, PATH_MAX, "Module %s", CLASS_NAME(klass));
    TheModule = new Module(module_name, TheContext);

    TheFPM = llvm::make_unique<legacy::FunctionPassManager>(TheModule);
    
    //TheFPM->add(createInstructionCombiningPass());
    TheFPM->add(createReassociatePass());
    //TheFPM->add(createGVNPass());
    TheFPM->add(createCFGSimplificationPass());
    TheFPM->doInitialization();

    create_internal_functions();
    TheLabels.clear();

    int i;
    int num_compiled_method = 0;

    if(!(klass->mFlags & CLASS_FLAGS_INTERFACE)) {
        for(i=0; i<klass->mNumMethods; i++) {
            sCLMethod* method = klass->mMethods + i;

            if(strcmp(METHOD_NAME2(klass, method), "initialize") != 0 && strcmp(METHOD_NAME2(klass, method), "finalize") != 0 && !(method->mFlags & METHOD_FLAGS_NATIVE)) 
            {
                char method_path2[METHOD_NAME_MAX + 128];
                create_method_path_for_jit(klass, method, method_path2, METHOD_NAME_MAX + 128);

                sByteCode* code = &method->mByteCodes;
                sConst* constant = &klass->mConst;

                if(!compile_to_native_code(code, constant, klass, method, method_path2)) {
                    return FALSE;
                }

                num_compiled_method++;
            }
        }
    }

    if(num_compiled_method > 0) {
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

        /// llvm-as ///
        char command[1024];
        int result;

        snprintf(command, 1024, "/usr/bin/llvm-dis %s.bc", CLASS_NAME(klass));
        puts(command);
        result = system(command);

        if(result != 0) {
            fprintf(stderr, "llvm-dis is faield\n");
            return FALSE;
        }

        snprintf(command, 1024, "/usr/bin/llc -relocation-model=pic %s.bc", CLASS_NAME(klass));
        puts(command);
        result = system(command);

        if(result != 0) {
            fprintf(stderr, "llvm-dis is faield\n");
            return FALSE;
        }

        snprintf(command, 1024, "/usr/bin/clang -o %s.o -c %s.s", CLASS_NAME(klass), CLASS_NAME(klass));
        puts(command);
        result = system(command);

        if(result != 0) {
            fprintf(stderr, "clang is faield\n");
            return FALSE;
        }

        snprintf(command, 1024, "/usr/bin/gcc -shared -Wl,-soname=lib%s.so.1 -o lib%s.so.1.0.0 %s.o", CLASS_NAME(klass), CLASS_NAME(klass), CLASS_NAME(klass));
        puts(command);
        result = system(command);

        if(result != 0) {
            fprintf(stderr, "clang is faield\n");
            return FALSE;
        }

        snprintf(command, 1024, "ln -fs lib%s.so.1.0.0 lib%s.so", CLASS_NAME(klass), CLASS_NAME(klass));
        puts(command);
        result = system(command);

        if(result != 0) {
            fprintf(stderr, "ln -fs is faield\n");
            return FALSE;
        }
    }

    delete TheModule;

    return TRUE;
}

BOOL jit_compile_all_classes()
{
    jit_init();

    sClassTable* p = gHeadClassTable;

    while(p) {
        sCLClass* klass = p->mItem;
        if(klass->mFlags & CLASS_FLAGS_MODIFIED) {
            if(!compile_jit_methods(klass)) {
                jit_final();
                return FALSE;
            }
        }
        p = p->mNextClass;
    }

    jit_final();

    return TRUE;
}

}
