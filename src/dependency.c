#include "common.h"

#define LOCKFILE "./dependency_check.txt"

static BOOL flg_dependency_compile = FALSE; /* 依存チェックモード */

void set_dependency_compile()
{
  flg_dependency_compile = TRUE;
}

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
BOOL dependency_init(char* filename)
{
	FILE *fp;	/* (1)ファイルポインタの宣言 */
	char s[256];
  char s2[256];
  filename = get_filename(filename);
  if (!flg_dependency_compile) {
    if ((fp = fopen(LOCKFILE, "w")) == NULL) return 1;
  } else {
    strcpy(s2,filename);
    strcat(s2,"\n");
    if ((fp = fopen(LOCKFILE, "r")) == NULL) return 1;
    while (fgets(s, 256, fp) != NULL) {
      if(strcmp(s,s2)==0) {
        fclose(fp);
        return FALSE;
      }
    }
    fclose(fp);
    if ((fp = fopen(LOCKFILE, "a")) == NULL) return 1;
  }
  fprintf(fp,"%s\n", filename);
  fclose(fp);
	return TRUE;
}

// 依存ファイルコンパイル
BOOL dependency_compile(char* cwd, char* class_name, char* class_file_name, size_t class_file_name_size)
{
  // クラス名のソースファイル名を生成
  snprintf(class_file_name, class_file_name_size, "%s/%s.clcl", cwd, class_name);
  if(access(class_file_name, F_OK) == 0) {// ソースファイルがあった
    snprintf(class_file_name, class_file_name_size, "cclover2 -dependency %s/%s.clcl", cwd, class_name);
    // ソースファイルをコンパイル
    int rc = system(class_file_name);
    snprintf(class_file_name, class_file_name_size, "%s/%s.oclcl", cwd, class_name);// 一応名前を保存
    if(rc == 0) return TRUE;// 成功していたらリターン
  }
  snprintf(class_file_name, class_file_name_size, "%s/%s.oclcl", cwd, class_name);
  return FALSE;
}

void dependency_final()
{
  if(!flg_dependency_compile) {
    remove(LOCKFILE);
  }
}
