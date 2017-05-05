# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

#配置CMake的最低版本
cmake_minimum_required(VERSION 3.4.1)

#配置工程路径
set(path_project /Users/admin/Documents/e/workspace_ndk/NdkStudy)
#set(path_project E:/workspace_ndk/NdkStudy)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library. so库名称
             study-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s). 源文件相对路径
             src/main/cpp/study-lib.cpp )

 add_library(
             cStudy
             SHARED
             src/main/cpp/cstudy/cStudy.cpp
            )

 add_library(
             jniStudy
             SHARED
             src/main/cpp/jnistudy/jniStudy.cpp
            )

 add_library(
              fmod-lib
              SHARED
              src/main/cpp/fmod/fmod-lib.cpp )

 #添加两个预编译的so库
 add_library( fmod
              SHARED
              IMPORTED
             )

 add_library( fmodL
              SHARED
              IMPORTED
             )

#设置两个预编译的库的路径，注意这里最好要使用绝对路径，不然会链接错误
set_target_properties(
                       fmod
                       PROPERTIES IMPORTED_LOCATION
                       ${path_project}/app/libs/${ANDROID_ABI}/libfmod.so
                    )

set_target_properties(
                       fmodL
                       PROPERTIES IMPORTED_LOCATION
                       ${path_project}/app/libs/${ANDROID_ABI}/libfmodL.so
                    )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       ## study-lib
                       fmod-lib
                       fmodL
                       fmod
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       )

#配置头文件的包含路径
include_directories(${path_project}/app/src/main/cpp/cstudy)
include_directories(${path_project}/app/src/main/cpp/jnistudy)
include_directories(${path_project}/app/src/main/cpp/fmod)