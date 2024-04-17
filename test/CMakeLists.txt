add_executable(TestQueue
               TestQueue.cxx)
target_link_libraries(TestQueue gtest pthread)

add_test(NAME TestQueue COMMAND $<TARGET_FILE:TestQueue>)
