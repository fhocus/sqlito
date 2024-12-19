add_executable(generateDisk generateDisk.cpp)
target_link_libraries(generateDisk PRIVATE sqlito)

add_executable(createQuery createQuery.cpp)
target_link_libraries(createQuery PRIVATE sqlito)

add_executable(insertQuery insertQuery.cpp)
target_link_libraries(insertQuery PRIVATE sqlito)

add_executable(deleteQuery deleteQuery.cpp)
target_link_libraries(deleteQuery PRIVATE sqlito)