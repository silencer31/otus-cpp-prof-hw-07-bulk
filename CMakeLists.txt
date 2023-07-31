cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(bulk VERSION ${PROJECT_VERSION})

find_package(GTest REQUIRED)

configure_file(version.h.in version.h)

#Main target 
add_executable(bulk main.cpp "collector.cpp" "interpreter.cpp" "file_logger.cpp" "console.cpp")
add_library(lib_bulk lib.cpp "collector.cpp" "interpreter.cpp" "file_logger.cpp" "console.cpp")

#Test target
add_executable(g_test_input gtest_input.cpp "collector.cpp" "interpreter.cpp" "file_logger.cpp" "console.cpp")

set_target_properties(bulk lib_bulk g_test_input PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(lib_bulk 
    PRIVATE "${CMAKE_BINARY_DIR}"
)

# Add src to the include directories for the test target
target_include_directories(g_test_input
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add googletest to the include directories for the test target
target_include_directories(g_test_input
    PRIVATE ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(bulk PRIVATE
    lib_bulk
)

# Link test target against gtest libraries
if (MSVC)
    target_link_libraries(g_test_input PRIVATE
    	${GTEST_BOTH_LIBRARIES}
    )
else ()
    target_link_libraries(g_test_input PRIVATE
    	${GTEST_BOTH_LIBRARIES}
		pthread
    )
endif()

if (MSVC)
    target_compile_options(bulk PRIVATE
        /W4
    )
    target_compile_options(lib_bulk PRIVATE
        /W4
    )
	target_compile_options(g_test_input PRIVATE
        /W4
    )
else ()
    target_compile_options(bulk PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(lib_bulk PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
	target_compile_options(g_test_input PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()