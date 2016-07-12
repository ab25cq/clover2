src/common.h:BOOL call_finalize_method_on_free_object(sCLClass* klass, CLObject self);
src/object.c:    if(!call_finalize_method_on_free_object(klass, self)) {
バイナリファイル src/object.o に一致しました
src/vm.c:BOOL call_finalize_method_on_free_object(sCLClass* klass, CLObject self)
