#include <iostream>
#include <string>
#include <fstream>

#include <inttypes.h>
#include <link.h>
#include <libgen.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>

#include <android/log.h>
#include "Substrate/CydiaSubstrate.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <thread>
#include <errno.h>
#include <string>
#include <string_view>
#include <sstream>
#include <memory>
#include <stdexcept>

#define LEN sizeof(struct MAPS)
#define FRE sizeof(struct FREEZE)
typedef struct MAPS *PMAPS;    //Daftar tertaut dari peta yang disimpan
typedef struct RESULT *PRES;   //Tertaut daftar hasil yang disimpan
typedef struct FREEZE *PFREEZE;//Daftar tertaut untuk menyimpan data beku

typedef char PACKAGENAME;

int isapkrunning(char *bm);//检测应用是否运行

namespace Tools
{
    void Hook(void *target, void *replace, void **backup);
    bool Read(void *addr, void *buffer, size_t length);
    bool Write(void *addr, void *buffer, size_t length);
    bool ReadAddr(void *addr, void *buffer, size_t length);
    bool WriteAddr(void *addr, void *buffer, size_t length);

    bool PVM_ReadAddr(void *addr, void *buffer, size_t length);
    bool PVM_WriteAddr(void *addr, void *buffer, size_t length);
    bool IsPtrValid(void *addr);
    uintptr_t FindPattern(const char *lib, const char* pattern);
    uintptr_t GetBaseAddress(const char *name);
    uintptr_t GetEndAddress(const char *name);

    std::string RandomString(const int len);
  //  std::string GetPackageName(JNIEnv *env, jobject context);

    std::string CalcMD5(std::string s);
    std::string CalcSHA256(std::string s);
}




