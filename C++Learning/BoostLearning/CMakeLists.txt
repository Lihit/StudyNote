cmake_minimum_required(VERSION 3.6)
project(BoostLearning)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp)
set(BoostLearning "/usr/local/include/boost")
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(BoostLearning ${SOURCE_FILES})
find_package(OpenCV REQUIRED)
target_link_libraries(BoostLearning ${OpenCV_LIBS})
target_link_libraries(BoostLearning boost_thread boost_system boost_filesystem boost_date_time boost_regex pthread)