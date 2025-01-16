cmake_minimum_required(VERSION 3.11)
project(CycleDB)

set(CMAKE_CXX_STANDARD 17)

add_library(CycleDB STATIC 
    src/Database.cpp
    src/helpers.cpp
)

target_include_directories(CycleDB PUBLIC include)

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)
target_include_directories(CycleDB PUBLIC ${nlohmann_json_SOURCE_DIR}/single_include)


add_executable(CycleDBCLI src/main.cpp)

target_link_libraries(CycleDBCLI PRIVATE CycleDB)

add_executable(CycleDBTests tests/example.cpp)

target_link_libraries(CycleDBTests PRIVATE CycleDB)
