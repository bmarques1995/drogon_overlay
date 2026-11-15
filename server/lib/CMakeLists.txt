# CMakeList.txt: projeto de CMake para Lust, incluir origem e definir
# lógica específica a um projeto aqui.
#

# Adicione a origem ao executável deste projeto.

function(merge_gql_schemas SCHEMA_FILES SCHEMA_OUTPUT)
	set(SCHEMAS ${SCHEMA_FILES})
    list(SORT SCHEMAS)
    set(GRAPHQL_SCHEMA_CONTENT "")

	foreach(SCHEMA IN LISTS SCHEMA_FILES)
		file(READ "${SCHEMA}" SCHEMA_CONTENT)

		string(APPEND GRAPHQL_SCHEMA_CONTENT
			"\n${SCHEMA_CONTENT}\n"
		)
	endforeach()

    file(WRITE
        "${SCHEMA_OUTPUT}"
        "${GRAPHQL_SCHEMA_CONTENT}"
    )

endfunction()

function(gen_gql_sources GENERATOR SCHEMA_FILE SCHEMA_NAME NAMESPACE OUTPUT_DIR)


    set(SCHEMAGEN_EXECUTABLE "")

    foreach(PROP IN ITEMS
        IMPORTED_LOCATION_RELEASE
        IMPORTED_LOCATION_RELWITHDEBINFO
        IMPORTED_LOCATION_MINSIZEREL
        IMPORTED_LOCATION_DEBUG
        IMPORTED_LOCATION
    )
        get_target_property(
            SCHEMAGEN_CANDIDATE
            ${GENERATOR}
            ${PROP}
        )

        if(SCHEMAGEN_CANDIDATE AND
           NOT SCHEMAGEN_CANDIDATE MATCHES "-NOTFOUND$")

            set(SCHEMAGEN_EXECUTABLE "${SCHEMAGEN_CANDIDATE}")

            message(STATUS "Schemagen found: ${SCHEMAGEN_EXECUTABLE}")
            break()
        endif()
    endforeach()

    if(NOT SCHEMAGEN_EXECUTABLE)
        message(FATAL_ERROR
            "Could not locate cppgraphqlgen::schemagen executable!"
        )
    endif()

    file(MAKE_DIRECTORY "${OUTPUT_DIR}")
    
    execute_process(
        COMMAND
            "${SCHEMAGEN_EXECUTABLE}"
            "${SCHEMA_FILE}"
            "${SCHEMA_NAME}"
            "${NAMESPACE}"
            --source-dir "${OUTPUT_DIR}"
            --header-dir "${OUTPUT_DIR}"
            --verbose

        WORKING_DIRECTORY "${OUTPUT_DIR}"

        RESULT_VARIABLE SCHEMAGEN_RESULT
        OUTPUT_VARIABLE SCHEMAGEN_OUTPUT
        ERROR_VARIABLE SCHEMAGEN_ERROR
    )

    if(NOT SCHEMAGEN_RESULT EQUAL 0)
        message(FATAL_ERROR
            "GraphQL schema generation failed!\n"
            "${SCHEMAGEN_ERROR}"
        )
    endif()

    message(STATUS "GraphQL schema generated successfully")
    message(STATUS "${SCHEMAGEN_OUTPUT}")

endfunction()

set(TARGET_NAME "dglib")

file(GLOB_RECURSE SAMPLE_SERVER_LIB_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.hh")
file(GLOB_RECURSE SAMPLE_SERVER_LIB_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cc")

add_library(${TARGET_NAME} ${SAMPLE_SERVER_LIB_SRCS} ${SAMPLE_SERVER_LIB_HDRS})
find_package(Drogon CONFIG REQUIRED)
find_package(JsonCpp CONFIG REQUIRED)
find_package(cppgraphqlgen CONFIG REQUIRED)

file(GLOB_RECURSE GRAPHQL_SCHEMAS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/graphql/*.gql")

merge_gql_schemas("${GRAPHQL_SCHEMAS}" "${CMAKE_CURRENT_BINARY_DIR}/dgapp.gql")
gen_gql_sources(cppgraphqlgen::schemagen "${CMAKE_CURRENT_BINARY_DIR}/dgapp.gql" "Dgctrl" "Dgql" "${CMAKE_CURRENT_BINARY_DIR}/schemas")
file(GLOB_RECURSE SAMPLE_SERVER_LIB_GQL_HDRS CONFIGURE_DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/*.h")
file(GLOB_RECURSE SAMPLE_SERVER_LIB_GQL_SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/*.cpp")

message(STATUS "Generated GraphQL sources: ${SAMPLE_SERVER_LIB_GQL_SRCS}")

target_sources(${TARGET_NAME} PRIVATE ${SAMPLE_SERVER_LIB_GQL_SRCS} ${SAMPLE_SERVER_LIB_GQL_HDRS})

target_sources(${TARGET_NAME} PRIVATE ${SAMPLE_SERVER_LIB_GQL_SRCS} ${SAMPLE_SERVER_LIB_GQL_HDRS})

#add_subdirectory(src/graphql)

target_link_libraries(${TARGET_NAME} PUBLIC Drogon::Drogon
                                            JsonCpp::JsonCpp
                                            cppgraphqlgen::graphqlservice
                                            cppgraphqlgen::graphqlresponse
                                            cppgraphqlgen::graphqljson
                                            cppgraphqlgen::graphqlpeg
                                            cppgraphqlgen::graphqlcoro)

target_include_directories(${TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/controllers> 
												 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/resolvers>
												 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/core>
												 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/common>
												 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/graphql>
												 $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
												 $<INSTALL_INTERFACE:include/dgapp/controllers>
												 $<INSTALL_INTERFACE:include/dgapp/resolvers>
												 $<INSTALL_INTERFACE:include/dgapp/core>
												 $<INSTALL_INTERFACE:include/dgapp/common>
												 $<INSTALL_INTERFACE:include/dgapp/graphql>
												 $<INSTALL_INTERFACE:include/dgapp/dgql>)
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