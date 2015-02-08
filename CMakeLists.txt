cmake_minimum_required(VERSION 2.8)
project(pector)

enable_testing()

include(CMakeCompilers.txt)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INC_DIR})

set(HEADER_FILES 
	${INC_DIR}/pector/pector.h
	${INC_DIR}/pector/pector_internals.h
	${INC_DIR}/pector/enhanced_allocators.h
	${INC_DIR}/pector/malloc_allocator.h
	${INC_DIR}/pector/recommended_size.h
)

install(FILES ${HEADER_FILES} DESTINATION include/pector)

add_subdirectory(tests)
