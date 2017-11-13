#include "common.h"

#define LOCKFILE "./cycle_check.txt"

BOOL cycle_compile = FALSE; /* 依存チェックモード */

/* ファイル名取得 */
static char* get_filename(char* filename) {
  char *fname;
  fname = strrchr(filename,'/'); /* ファイル名取得 */
  if(fname == NULL) {
    fname = strrchr(filename,'\\'); /* windows 対応 */
  }
  if (fname == NULL) {
    fname = filename; /* セパレータがなかった */
  } else {
    fname++; /* セパレータがあったら１つ戻す */
  }
  return fname;
}

/*
 * 再帰的呼び出しチェック
 */
static int cycle_init(char* filename)
{
	FILE *fp;	/* (1)ファイルポインタの宣言 */
	char s[256];
  char s2[256];
  filename = get_filename(filename);
  if (!cycle_compile) {
    if ((fp = fopen(LOCKFILE, "w")) == NULL) return 1;
  } else {
    strcpy(s2,filename);
    strcat(s2,"\n");
    if ((fp = fopen(LOCKFILE, "r")) == NULL) return 1;
    while (fgets(s, 256, fp) != NULL) {
      if(strcmp(s,s2)==0) {
        fclose(fp);
        return 1;
      }
    }
    fclose(fp);
    if ((fp = fopen(LOCKFILE, "a")) == NULL) return 1;
  }
  fprintf(fp,"%s\n", filename);
  fclose(fp);
	return 0;
}

static void cycle_final()
{
  if(!cycle_compile) {
    remove(LOCKFILE);
  }
}

static void compiler_init(BOOL no_load_fudamental_classes)
{
    init_nodes();
    init_node_types();
    init_node_block_types();
    class_init();
    if(!no_load_fudamental_classes) class_init_on_compile_time();
    init_vtable();
    module_init();
    parser_init();
}

static void compiler_final()
{
    parser_final();
    module_final();
    free_nodes();
    free_node_block_types();
    free_node_types();
    class_final();
    final_vtable();
    cycle_final();
}

static BOOL compiler(char* fname)
{
    if(access(fname, F_OK) != 0) {
        fprintf(stderr, "%s doesn't exist\n", fname);
        return FALSE;
    }

    sBuf source;
    sBuf_init(&source);
    if(!read_source(fname, &source)) {
        MFREE(source.mBuf);
        return FALSE;
    }

    sBuf source2;
    sBuf_init(&source2);

    if(!delete_comment(&source, &source2)) {
        MFREE(source.mBuf);
        MFREE(source2.mBuf);
        return FALSE;
    }

    if(!compile_script(fname, source2.mBuf)) {
        MFREE(source.mBuf);
        MFREE(source2.mBuf);
        return FALSE;
    }

    MFREE(source.mBuf);
    MFREE(source2.mBuf);

    return TRUE;
}


static BOOL class_compiler(char* fname)
{
    if(access(fname, F_OK) != 0) {
        fprintf(stderr, "%s doesn't exist\n", fname);
        return FALSE;
    }

    sBuf source;
    sBuf_init(&source);
    if(!read_source(fname, &source)) {
        MFREE(source.mBuf);
        return FALSE;
    }

    sBuf source2;
    sBuf_init(&source2);

    if(!delete_comment(&source, &source2)) {
        MFREE(source.mBuf);
        MFREE(source2.mBuf);
        return FALSE;
    }

    if(!compile_class_source(fname, source2.mBuf)) {
        MFREE(source.mBuf);
        MFREE(source2.mBuf);
        return FALSE;
    }

    if(!write_all_modified_classes()) {
        MFREE(source.mBuf);
        MFREE(source2.mBuf);
        return FALSE;
    }

    write_all_modified_modules();

#ifdef ENABLE_JIT
    if(!jit_compile_all_classes()) {
        fprintf(stderr, "faield in jit compile\n");
        MFREE(source.mBuf);
        MFREE(source2.mBuf);
        return FALSE;
    }
#endif

    MFREE(source.mBuf);
    MFREE(source2.mBuf);

    return TRUE;
}

int main(int argc, char** argv)
{
    int i;

    setlocale(LC_ALL, "");

    BOOL no_load_fudamental_classes = FALSE;
    BOOL clc_compile = FALSE;
    char sname[PATH_MAX];
    xstrncpy(sname, "", PATH_MAX);

    for(i=1; i<argc; i++) {
        if(strcmp(argv[i], "-no-load-fundamental-classes") == 0) {
            no_load_fudamental_classes = TRUE;
        }
        else if(strcmp(argv[i], "-core") == 0) {
            no_load_fudamental_classes = TRUE;
        }
        else if(strcmp(argv[i], "-class") == 0) {
            clc_compile = TRUE;
        }
        else if(strcmp(argv[i], "-cycle") == 0) {
          cycle_compile = TRUE;
        }
        else {
            xstrncpy(sname, argv[i], PATH_MAX);
        }
    }
    char* ext_sname = strstr(sname, ".");

    if(ext_sname != NULL && strcmp(ext_sname, ".clc") == 0) {
        clc_compile = TRUE;
    }

    if (cycle_init(sname) != 0) {
      fprintf(stderr, "cclover2 cycle check error %s\n", sname);
      return 1;
    }

    compiler_init(no_load_fudamental_classes);

    if(clc_compile) {
        if(!class_compiler(sname)) {
            fprintf(stderr, "cclover2 can't compile %s\n", argv[i]);
            compiler_final();
            return 1;
        }
    }
    else {
        if(!compiler(sname)) {
            fprintf(stderr, "cclover2 can't compile %s\n", argv[i]);
            compiler_final();
            return 1;
        }
    }

    compiler_final();

    return 0;
}
