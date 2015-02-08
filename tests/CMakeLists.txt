add_executable(instance instance.cpp)
add_test(instance instance)

add_executable(append append.cpp)
add_test(append append)

add_executable(copy_move copy_move.cpp)
add_test(copy_move copy_move)

add_executable(assign assign.cpp)
add_test(assign assign)

add_executable(iterators iterators.cpp)
add_test(iterators iterators)

add_executable(forward_decl forward_decl.cpp)
add_test(forward_decl forward_decl)

add_executable(sort sort.cpp)
add_test(sort sort)

add_executable(insert insert.cpp)
add_test(insert insert)

add_executable(erase erase.cpp)
add_test(erase erase)

add_executable(resize resize.cpp)
add_test(resize resize)

add_executable(overflow overflow.cpp)
add_test(overflow overflow)

add_executable(recommended_sizes recommended_sizes.cpp)
add_test(recommended_sizes recommended_sizes)

add_executable(enhanced_allocators enhanced_allocators.cpp)
add_test(enhanced_allocators enhanced_allocators)

add_executable(min_construct min_construct.cpp)
add_test(min_construct min_construct)

add_executable(grow_perfs grow_perfs.cpp)
