# CMakeList.txt: projeto de CMake para Lust, incluir origem e definir
# lógica específica a um projeto aqui.
#

# Adicione a origem ao executável deste projeto.

set(TARGET_NAME "dgapp")

file(GLOB_RECURSE SAMPLE_SERVER_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.hh")
file(GLOB_RECURSE SAMPLE_SERVER_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cc")

add_executable(${TARGET_NAME} ${SAMPLE_SERVER_SRCS} ${SAMPLE_SERVER_HDRS})
find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE dglib)

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