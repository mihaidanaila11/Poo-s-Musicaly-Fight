cmake_minimum_required(VERSION 3.24)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
project(oop)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
option(BUILD_SHARED_LIBS "Build SFML as shared library" FALSE)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "install_dir" CACHE PATH "..." FORCE)
endif()

# disable sanitizers when releasing executables without explicitly requested debug info
# use generator expressions to set flags correctly in both single and multi config generators
set(is_debug "$<CONFIG:Debug>")
set(is_rel_with_deb "$<CONFIG:RelWithDebInfo>")
set(debug_mode "$<OR:${is_debug},${is_rel_with_deb}>")

###############################################################################

# custom functions

function(set_custom_stdlib_and_sanitizers target add_apple_asan)
    if(MSVC)
        # see https://gitlab.kitware.com/cmake/cmake/-/issues/24922
        set_target_properties(${target} PROPERTIES VS_USER_PROPS "${CMAKE_SOURCE_DIR}/disable_modules.props")
        target_compile_options(${target} PRIVATE /experimental:module-)
        # if(GITHUB_ACTIONS)
        target_compile_options(${target} PRIVATE "$<${debug_mode}:/fsanitize=address>")
        # endif()
        return()
    endif()

    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        target_compile_options(${target} PRIVATE -stdlib=libc++)
        target_link_options(${target} PRIVATE -stdlib=libc++)
    endif()

    if(APPLE)
        # first check Apple since Apple is also a kind of Unix
        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" AND add_apple_asan MATCHES true)
            target_compile_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
            target_link_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
        endif()
    elseif(UNIX)
        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
            if("${CMAKE_CXX_COMPILER_VERSION}" MATCHES "12.")
                # check leaks on Linux since macOS does not support the leaks sanitizer yet
                # leaks sanitizer is enabled by default on Linux, so we do not need to enable it explicitly
                target_compile_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
                target_link_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
            endif()
        elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
            if("${CMAKE_CXX_COMPILER_VERSION}" MATCHES "17.")
                # use semi-colons instead of spaces to separate arguments
                # it is recommended to quote generator expressions in order to avoid unintentional splitting
                target_compile_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=memory,undefined;-fsanitize-recover=memory,undefined;-fsanitize-memory-track-origins>")
                target_link_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=memory,undefined;-fsanitize-recover=memory,undefined;-fsanitize-memory-track-origins;-Wl,-rpath,tools/llvm-project/build/lib>")
            else()
                message("No matching Clang version to add sanitizer flags!")
            endif()
        endif()
    endif()
endfunction()

###############################################################################

# external dependencies with FetchContent
include(FetchContent)

# NOTE: Also update SFML_VERSION env var in .github/workflows/cmake.yml:126
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.6.1
  # GIT_TAG        69ea0cd863aed1d4092b970b676924a716ff718b # 2.6.1
  # GIT_TAG        origin/master
  GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
)


FetchContent_MakeAvailable(SFML)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
else()
    set_custom_stdlib_and_sanitizers(sfml-system false)
    set_custom_stdlib_and_sanitizers(sfml-window false)
    set_custom_stdlib_and_sanitizers(sfml-graphics false)
endif()

###############################################################################

# external dependencies with find_package

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${PROJECT_NAME}
    main.cpp
    generated/src/Helper.cpp
    env_fixes.h
        Classes/Hitbox/Hitbox.h
        Classes/Hitbox/Hitbox.cpp
        Classes/Entity/Entity.h
        Classes/Entity/Entity.cpp
        Classes/Weapon/Weapon.cpp
        Classes/Weapon/Weapon.h
        Classes/Enemy/Enemy.cpp
        Classes/Enemy/Enemy.h
        Classes/Player/Player.cpp
        Classes/Player/Player.h
        Classes/Scene/Scene.cpp
        Classes/Scene/Scene.hpp
        Classes/Button/Button.cpp
        Classes/Button/Button.h
        Classes/Game/Game.cpp
        Classes/Game/Game.h
        Scenes/MainMenu/MainMenu.cpp
        Scenes/MainMenu/MainMenu.h
        Classes/Hud/Hud.cpp
        Classes/Hud/Hud.h
        Classes/Hud/HealthBar/HealthBar.cpp
        Classes/Hud/HealthBar/HealthBar.h
        Exceptions/GraphicExceptions.hpp
        Classes/Alive/Alive.h
        Classes/Alive/Alive.cpp
        Classes/Enemy/Enemies/BasicEnemy/BasicEnemy.cpp
        Classes/Enemy/Enemies/GhostEnemy/GhostEnemy.cpp
        Classes/Enemy/Enemies/GhostEnemy/GhostEnemy.h
        Classes/Wave/Wave.cpp
        Classes/Wave/Wave.h
        Classes/Alert/Alert.cpp
        Classes/Alert/Alert.h
        Math/VectorMath.cpp
        Math/VectorMath.h
        Classes/Wave/Waves.cpp
        Classes/Enemy/Enemies/GiantEnemy/GiantEnemy.cpp
        Classes/Enemy/Enemies/GiantEnemy/GiantEnemy.h
        "Classes/Texture Manager/TextureManager.cpp"
        "Classes/Texture Manager/TextureManager.h"
        Classes/Enemy/Enemies/EnemyFactory.cpp
        Classes/Enemy/Enemies/EnemyFactory.h
        "Classes/Singleton CRTP/Singleton.h"
)

###############################################################################

# target definitions

if(GITHUB_ACTIONS)
    message("NOTE: GITHUB_ACTIONS defined")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GITHUB_ACTIONS)
endif()

###############################################################################

if(WARNINGS_AS_ERRORS)
    set_property(TARGET ${PROJECT_NAME} PROPERTY COMPILE_WARNING_AS_ERROR ON)
endif()

# custom compiler flags
message("Compiler: ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive- /wd4244 /wd4267 /wd4996 /external:anglebrackets /external:W0)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

###############################################################################

# sanitizers
set_custom_stdlib_and_sanitizers(${PROJECT_NAME} true)

###############################################################################

# use SYSTEM so cppcheck/clang-tidy does not report warnings from these directories
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE generated/include)
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-audio sfml-system Threads::Threads)

if(APPLE)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE X11)
endif()

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# update name in .github/workflows/cmake.yml:29 when changing "bin" name here
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY Textures DESTINATION bin)
install(DIRECTORY daydream_3 DESTINATION bin)
# install(FILES some_file1.txt some_file2.md DESTINATION bin)
if(APPLE)
    install(FILES launcher.command DESTINATION bin)
endif()
