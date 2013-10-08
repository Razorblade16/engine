LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LS_CPP=$(subst $(1)/,,$(wildcard $(1)/*.cpp))
LS_CPP+= $(subst $(1)/,,$(wildcard $(1)/**/*.cpp))
LS_CPP+= $(subst $(1)/,,$(wildcard $(1)/**/**/*.cpp))
LS_CPP+= $(subst $(1)/,,$(wildcard $(1)/**/**/**/*.cpp))
LOCAL_CPPFLAGS  := -std=gnu++11
LOCAL_MODULE    := StarEngine
LOCAL_SRC_FILES := $(call LS_CPP,$(LOCAL_PATH))
LOCAL_LDLIBS    := -landroid -llog -lEGL -lGLESv1_CM -lGLESv2 -lOpenSLES
APP_PLATFORM := android-14
APP_OPTIM := debug

LOCAL_STATIC_LIBRARIES := android_native_app_glue png
LOCAL_SHARE_LIBRARIES := StarEngine

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
$(call import-module,libpng)