cmake_minimum_required(VERSION 3.10)

# Название проекта
project(4TEST_LAB)

# Устанавливаем флаги для покрытия (если нужно)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

# Указываем исходные файлы проекта
set(SOURCES
    src/array.h
)

# Создаем исполнимый файл для проекта
add_executable(laba1 ${SOURCES})

# Указываем исходные файлы для тестов
set(TEST_SOURCES
    test/test_array.h
)

# Создаем исполнимый файл для тестов
add_executable(test_all ${TEST_SOURCES})

# Линковка с GoogleTest
find_package(GTest REQUIRED)
target_link_libraries(test_all GTest::GTest GTest::Main)

# Регистрируем тесты с CTest
enable_testing()
add_test(NAME run_all_tests COMMAND test_all)

# Запуск тестов после сборки
add_custom_command(TARGET test_all POST_BUILD
    COMMAND ctest
    COMMENT "Запуск тестов после сборки"
)

# Команды для сбора покрытия
add_custom_target(coverage
    COMMAND lcov --directory . --capture --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage_cleaned.info
    COMMAND genhtml coverage_cleaned.info --output-directory out
    COMMENT "Генерация отчета покрытия"
)