#include "common.h"
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>

BOOL load_module_from_file(ALLOC sCLModule** self, char* module_name);

sCLModule* gModules[CL_MODULE_HASH_SIZE];

void module_init()
{
    memset(gModules, 0, sizeof(gModules));
}

static BOOL append_module_to_table(char* name, sCLModule* module)
{
    int hash_value;
    sCLModule** p;

    hash_value = get_hash_key(name, CL_MODULE_HASH_SIZE);

    p = gModules + hash_value;

    while(1) {
        if(*p == NULL) {
            *p = module;
            break;
        }
        else {
            if(strcmp((*p)->mName, name) == 0) {
                return FALSE;
            }
            else {
                p++;

                if(p == gModules + CL_MODULE_HASH_SIZE) {
                    p = gModules;
                }
                else if(p == gModules + hash_value) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

// result: (NULL) overflow module table (sCLModule*) success
sCLModule* create_module(char* module_name)
{
    sCLModule* self;

    self = MCALLOC(1, sizeof(sCLModule));

    sBuf_init(&self->mBody);

    xstrncpy(self->mName, module_name, CL_MODULE_NAME_MAX);

    if(!append_module_to_table(module_name, self)) {
        return NULL;
    }

    return self;
}

static void free_module(sCLModule* self)
{
    MFREE(self->mBody.mBuf);

    MFREE(self);
}

static void remove_module_from_table(char* module_name)
{
    int hash_value;
    sCLModule** p;

    hash_value = get_hash_key(module_name, CL_MODULE_HASH_SIZE);

    p = gModules + hash_value;

    while(1) {
        if(*p == NULL) {
            break;
        }
        else {
            if(strcmp((*p)->mName, module_name) == 0) {
                free_module(*p);
                *p = NULL;
                break;
            }
            else {
                p++;

                if(p == gModules + CL_MODULE_HASH_SIZE) {
                    p = gModules;
                }
                else if(p == gModules + hash_value) {
                    break;
                }
            }
        }
    }
}

void unload_module(char* module_name)
{
    remove_module_from_table(module_name);
}

void module_final()
{
    sCLModule** p;

    p = gModules;

    while(p < gModules + CL_MODULE_HASH_SIZE) {
        if(*p != NULL) {
            free_module(*p);
        }

        p++;
    }
}

void append_character_to_module(sCLModule* self, char c)
{
    sBuf_append_char(&self->mBody, c);
}

void append_str_to_module(sCLModule* self, char* str)
{
    sBuf_append(&self->mBody, str, strlen(str));
}

sCLModule* get_module(char* module_name)
{
    int hash_value;
    sCLModule** p;

    hash_value = get_hash_key(module_name, CL_MODULE_HASH_SIZE);

    p = gModules + hash_value;

    while(1) {
        if(*p == NULL) {
            sCLModule* module;

            if(!load_module_from_file(&module, module_name)) {
                break;
            }

            return module;
        }
        else {
            if(strcmp((*p)->mName, module_name) == 0) {
                return *p;
            }
            else {
                p++;

                if(p == gModules + CL_MODULE_HASH_SIZE) {
                    p = gModules;
                }
                else if(p == gModules + hash_value) {
                    break;
                }
            }
        }
    }

    return NULL;
}

char* get_module_body(sCLModule* module)
{
    if(module) {
        return module->mBody.mBuf;
    }
    else {
        return NULL;
    }
}

static BOOL save_module_to_file(sCLModule* self)
{
    FILE* f;
    char fname[PATH_MAX];

    snprintf(fname, PATH_MAX, "%s.clm", self->mName);

    f = fopen(fname, "w+");

    if(f == NULL) { 
        return FALSE; 
    }

    fprintf(f, "%s", self->mBody.mBuf);

    fclose(f);

    return TRUE;
}

// result : (TRUE) found (FALSE) not found
static BOOL search_for_module_file_from_module_name(char* module_file, unsigned int module_file_size, char* module_name)
{
    int i;
    char* cwd;

    cwd = getenv("PWD");

    /// default search path ///
    snprintf(module_file, module_file_size, "%s/%s.clm", DATAROOTDIR, module_name);

    if(access(module_file, F_OK) == 0) {
        return TRUE;
    }

    /// .clover directory ////
    char* home = getenv("HOME");

    /// .clover directory ///
    if(home) {
        snprintf(module_file, module_file_size, "%s/%s.clm", home, module_name);

        if(access(module_file, F_OK) == 0) {
            return TRUE;
        }
    }

    /// current working directory ///
    if(cwd) {
        snprintf(module_file, module_file_size, "%s/%s.clm", cwd, module_name);

        if(access(module_file, F_OK) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL load_module_from_file(ALLOC sCLModule** self, char* module_name)
{
    char buf[BUFSIZ+1];
    int fd;
    char fname[PATH_MAX];

    if(!search_for_module_file_from_module_name(fname, PATH_MAX, module_name))
    {
        return FALSE;
    }

    /// load from file ///
    *self = create_module(module_name);

    fd = open(fname, O_RDONLY);

    if(fd < 0) {
        return FALSE;
    }

    while(1) {
        int size;

        size = read(fd, buf, BUFSIZ);
        if(size < 0) {
            close(fd);
            return FALSE;
        }

        buf[size] = 0;

        if(size < BUFSIZ) {
            append_str_to_module(*self, buf);
            break;
        }
        else {
            append_str_to_module(*self, buf);
        }
    }

    close(fd);

    return TRUE;
}

// result (TRUE): success (FALSE): failed to write module to the file
void write_all_modified_modules()
{
    sCLModule** p;

    p = gModules;

    while(p < gModules + CL_MODULE_HASH_SIZE) {
        if(*p != NULL) {
            if((*p)->mModified) {
                if(!save_module_to_file((*p))) {
                    printf("failed to write this module(%s)\n", (*p)->mName);
                }
            }
        }

        p++;
    }
}

void this_module_is_modified(sCLModule* self)
{
    self->mModified = TRUE;
}

