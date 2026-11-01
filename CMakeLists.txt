# CMakeList.txt: arquivo de projeto de CMake de nível superior, fazer configuração global
# e inclua subprojetos aqui.
#
cmake_minimum_required (VERSION 3.28)

function(configure_script_output SCRIPT_IN_FILE_PREFIX SCRIPT_OUT_FILE_PREFIX SCRIPT_TEMPLATE_EXTENSION)
    set(SCRIPT_IN_FILE ${SCRIPT_IN_FILE_PREFIX}.${SCRIPT_TEMPLATE_EXTENSION}.in)
	set(SCRIPT_OUT_FILE ${SCRIPT_OUT_FILE_PREFIX}.${SCRIPT_TEMPLATE_EXTENSION})
    configure_file(
        ${SCRIPT_IN_FILE}
        ${SCRIPT_OUT_FILE}
        @ONLY
    )
endfunction()

function(add_dg_ctl_path VCPKG_CURRENT_PREFIX SCRIPT_TEMPLATE_PREFIX OUT_FILE_PREFIX)
    set(DGCTL_EXTRA_SOURCE_PATH ${VCPKG_CURRENT_PREFIX}/tools/drogon)
    set(SCRIPT_IN_FILE "")
    set(SCRIPT_OUT_FILE "")
    if(WIN32)
        configure_script_output(${SCRIPT_TEMPLATE_PREFIX} ${OUT_FILE_PREFIX} ps1)
    else()
        configure_script_output(${SCRIPT_TEMPLATE_PREFIX} ${OUT_FILE_PREFIX} sh)
        configure_script_output(${SCRIPT_TEMPLATE_PREFIX} ${OUT_FILE_PREFIX} zsh)
    endif()
endfunction()

# Habilite a Recarga Dinâmica para compiladores MSVC, se houver suporte.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(DrogonSample LANGUAGES CXX VERSION 0.0.4)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(FETCHERS_LOCATION "Set Repo and File Fetcher location" ".")

function(set_msvc_debug_improvements TARGET_NAME)
    if(MSVC)
        target_compile_options(${TARGET_NAME} PRIVATE
            $<$<CONFIG:Debug>:/Od>
            $<$<CONFIG:Debug>:/Zi>
        )

        target_link_options(${TARGET_NAME} PRIVATE
            $<$<CONFIG:Debug>:/DEBUG>
        )
    endif()
endfunction()

include(FetchContent)

set(ARTIFACT_PREFIX ${PROJECT_BINARY_DIR})
if(WIN32)
    set(ARTIFACT_PREFIX ${CMAKE_INSTALL_PREFIX})
endif()

if(USES_VCPKG)
    set(VCPKG_CURRENT_PREFIX ${VCPKG_PREFIX_PATH}/${VCPKG_TARGET_TRIPLET})
    list(APPEND CMAKE_PREFIX_PATH ${VCPKG_CURRENT_PREFIX})
    set(VCPKG_ROOT_PREFIX ${VCPKG_CURRENT_PREFIX})
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(VCPKG_CURRENT_PREFIX ${VCPKG_CURRENT_PREFIX}/debug)
    endif()
    if(WIN32)
        set(ARTIFACT_PREFIX ${VCPKG_CURRENT_PREFIX})
    endif()
    add_dg_ctl_path(${VCPKG_ROOT_PREFIX} ${PROJECT_SOURCE_DIR}/dgctl_env/env ${PROJECT_SOURCE_DIR}/env)
endif()

# 2. Declare the download location and version details
FetchContent_Declare(
    cmake_helpers
    GIT_REPOSITORY https://github.com/bmarques1995/cmake_helpers.git
    #GIT_TAG        v1.14.0 # Best practice: Use a specific tag or commit hash
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/cmake_helpers
)

# 3. Download the library and make its targets available
FetchContent_MakeAvailable(cmake_helpers)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_helpers;${PROJECT_SOURCE_DIR}/cmake_extra")

include(target_destination)
include(source_downloader)
include(InstallRequiredSystemLibraries)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# Inclua subprojetos.
add_subdirectory("server")

