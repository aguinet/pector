# use valgrind if available
find_program(VALGRIND_TOOL NAMES valgrind)
if(VALGRIND_TOOL)
    set(VALGRIND_CHECK ${VALGRIND_TOOL} --error-exitcode=1)
else()
    set(VALGRIND_CHECK)
endif()

add_executable(instance instance.cpp)
add_test(instance ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/instance)

add_executable(append append.cpp)
add_test(append ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/append)

add_executable(copy_move copy_move.cpp)
add_test(copy_move ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/copy_move)

add_executable(assign assign.cpp)
add_test(assign ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/assign)

add_executable(iterators iterators.cpp)
add_test(iterators ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/iterators)

add_executable(forward_decl forward_decl.cpp)
add_test(forward_decl ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/forward_decl)

add_executable(sort sort.cpp)
add_test(sort ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/sort)

add_executable(insert insert.cpp)
add_test(insert ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/insert)

add_executable(erase erase.cpp)
add_test(erase ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/erase)

add_executable(resize resize.cpp)
add_test(resize ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/resize)

add_executable(overflow overflow.cpp)
add_test(overflow ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/overflow)

add_executable(recommended_sizes recommended_sizes.cpp)
add_test(recommended_sizes ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/recommended_sizes)

add_executable(enhanced_allocators enhanced_allocators.cpp)
add_test(enhanced_allocators ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/enhanced_allocators)

add_executable(min_construct min_construct.cpp)
add_test(min_construct ${VALGRIND_CHECK} ${CMAKE_BINARY_DIR}/tests/min_construct)

add_executable(grow_perfs grow_perfs.cpp)
