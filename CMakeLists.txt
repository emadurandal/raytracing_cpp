cmake_minimum_required(VERSION 3.20)

project(RayTracing)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/include)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)



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
	SET(CMAKE_CXX_STANDARD 11)
	SET(CMAKE_CXX_STANDARD_REQUIRED on)
endif()
# /APPLE


file(GLOB BASESRCS "${SRC_DIR}/*.cc" "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.c" "${SRC_DIR}/*.mm" "${INC_DIR}/*.h" "${INC_DIR}/*.hpp")

add_executable(
        myapp  ${BASESRCS}
)

# 単体テスト
find_package(GTest REQUIRED)
enable_testing()

add_executable(MyLibraryTest "${TEST_DIR}/main.test.cpp" )

target_link_libraries(MyLibraryTest GTest::gtest GTest::gtest_main)

add_test(NAME MyLibraryTest COMMAND MyLibraryTest)

# link_directories(
#         ${GTEST_LIBRARIES_DIR} /usr/local/lib
# )
        link_directories(/usr/local/lib)

# CTestに単体テストを登録
include(GoogleTest)
gtest_discover_tests(MyLibraryTest)

include_directories(
        ${INC_DIR} ${GTEST_INCLUDE_DIRS}
)