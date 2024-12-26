#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>

#include <jni.h>
#include <pthread.h>

#include "zygisk.hpp"

#include "utils.h"

#include "Engine/Dumper.h"

using zygisk::Api;
using zygisk::AppSpecializeArgs;
using zygisk::ServerSpecializeArgs;

class MyModule : public zygisk::ModuleBase {
public:
    void onLoad(Api *api, JNIEnv *env) override {
        m_env = env;
    }

    void preAppSpecialize(AppSpecializeArgs *args) override {
        const char *procName = m_env->GetStringUTFChars(args->nice_name, 0);
        m_procName = procName;
        m_env->ReleaseStringUTFChars(args->nice_name, procName);
    }

    void postAppSpecialize(const AppSpecializeArgs *) override {
        if (m_procName == "com.tencent.ig" || m_procName == "com.vng.pubgmobile"|| m_procName == "com.pubg.krmobile"|| m_procName == "com.rekoo.pubgm"|| m_procName == "com.pubg.imobile"|| m_procName == "com.tencent.igce") {
            pthread_t t;
            pthread_create(&t, 0, main_thread, 0);
        }
    }

private:
    JNIEnv *m_env;
    std::string m_procName;
};

REGISTER_ZYGISK_MODULE(MyModule)