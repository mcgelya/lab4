add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_executable(stress_insert stress_insert.cpp)
add_executable(stress_erase stress_erase.cpp)
add_executable(stress_map stress_map.cpp)
