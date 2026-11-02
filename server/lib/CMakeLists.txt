# CMakeList.txt: projeto de CMake para Lust, incluir origem e definir
# lógica específica a um projeto aqui.
#

# Adicione a origem ao executável deste projeto.

set(TARGET_NAME "SampleServerLib")

file(GLOB_RECURSE SAMPLE_SERVER_LIB_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.hh")
file(GLOB_RECURSE SAMPLE_SERVER_LIB_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cc")

add_library(${TARGET_NAME} ${SAMPLE_SERVER_LIB_SRCS} ${SAMPLE_SERVER_LIB_HDRS})
find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${TARGET_NAME} PUBLIC Drogon::Drogon)
target_include_directories(${TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/controllers> 
												 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/common> 
												 $<INSTALL_INTERFACE:include/controllers>
												 $<INSTALL_INTERFACE:include/common>)
if(BUILD_SHARED_LIBS)
	if(WIN32)
		target_compile_definitions(${TARGET_NAME} PRIVATE SERVER_WIN_EXPORT INTERFACE SERVER_WIN_IMPORT)
	endif()
endif()

set_cxx_project_standards(${TARGET_NAME} 20 FALSE)
set_artifacts_dir(${TARGET_NAME} ${PROJECT_BINARY_DIR})
set_msvc_target_utf8(${TARGET_NAME})
set_msvc_debug_improvements(${TARGET_NAME})
target_installation_behaviour(
	CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
	TARGET_NAME ${TARGET_NAME}
	VERSION ${PROJECT_VERSION}
	PROJECT_NAME ${PROJECT_NAME}
	NAMESPACE "Lust"
	COMPONENT Lust)