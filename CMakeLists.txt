cmake_minimum_required(VERSION 3.11)
project(CycleDB)

set(CMAKE_CXX_STANDARD 17)

# Добавьте все исходные файлы
add_executable(Database src/main.cpp src/Database.cpp src/helpers.cpp)

# Подключите nlohmann/json
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

target_include_directories(Database PUBLIC ${nlohmann_json_SOURCE_DIR}/single_include)