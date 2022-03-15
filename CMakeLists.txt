cmake_minimum_required(VERSION 3.13)

project(RayTracing)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/include)

if (APPLE)
#        set(CMAKE_MACOSX_BUNDLE YES CACHE INTERNAL "" FORCE)
#        set(CMAKE_SYSTEM_NAME iOS CACHE INTERNAL "" FORCE)
#        set(CMAKE_OSX_SYSROOT "iphoneos" CACHE INTERNAL "" FORCE)
#        set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY	CACHE INTERNAL "" FORCE)
#        set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0などのターゲット" CACHE STRING   "" FORCE)
#        set(CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "チームID" CACHE STRING   "" FORCE)

        # オープンソースのサブプロジェクトを使うときに問題になりやすいので
        # BitcodeはOFFにします。
        set(CMAKE_XCODE_ATTRIBUTE_ENABLE_BITCODE
                "NO" CACHE INTERNAL "")

        # resourcesフォルダのファイルとフォルダを列挙し
        # 結果をRESOURCE_FILESに格納する
        file(GLOB RESOURCE_FILES	"../resources/*")

endif()
# /APPLE

include_directories(
        ${INC_DIR}
)

file(GLOB BASESRCS "${SRC_DIR}/*.cc" "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.c" "${SRC_DIR}/*.mm" "${INC_DIR}/*.h" "${INC_DIR}/*.hpp")

add_executable(
        myapp  ${BASESRCS}
)
