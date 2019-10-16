In order to use the .so in android, we need to compile it with the toolchain, and push the files to /vendor/lib/

In the code we should call it like this:

First include the header and define the typedef for the prototype of our function

```cpp
#include "dlfcn.h"
typedef int (*CAC_FUNC)(unsigned char *data, int width, int height);
```

After that we need to open it like 

```cpp
{
    void *data = NULL;
    data = (void *)(uint8_t *)frame->bufs[0]->buffer;

    void *handle;
    char *error;

    CAC_FUNC cac_func = NULL;

    handle = dlopen("/system/vendor/lib/libreadFrame.so", RTLD_NOW);

    if(!handle)
    {
        error = (char *)dlerror();
        LOGE("DL Open Error for libreadFrame: %s", error);
    }

    dlerror();
    *(void**)(&cac_func) = dlsym(handle, "readFrameCV");
    if(dlsym(handle, "readFrameCV") == NULL)
    {
        LOGE("readFrameCV DL Error: %s", error);
    }

    if((error = (char *)dlerror()) != NULL)
    {
        LOGE("readFrameCV dl error, exit failure: %s", error);
    }

    int tmp = cac_func((unsigned char *)data+4096, mFrameLenOffset.mp[0].width, mFrameLenOffset.mp[0].height);

    dlclose(handle);

    switch (tmp)
    {
    case 0:
        LOGE("---MERGIM_LOGS--- Function finished with return 0, image empty. tmp = %d", tmp);
        break;
    case 1:
        LOGE("---MERGIM_LOGS--- Function finished with return 1, image success. tmp = %d", tmp);
        break;
    default:
        LOGE("---MERGIM_LOGS--- Switch returned default. tmp = %d", tmp);
        break;
    }
}
```

To compile the example we need to call the cmake .. with the toolchain file. E.g.:

```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=/home/jimmyhalimi/Desktop/Desktop/capture_write/toolchain/android-ndk-r17c/build/cmake/android.toolchain.cmake 
```
Note: please update the path for your user