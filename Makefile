# Путь к Google Test  
GTEST_DIR = /path/to/googletest
GMOCK_DIR = /path/to/gmock

# Флаги компиляции
CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Isrc -I$(GTEST_DIR)/include -I$(GMOCK_DIR)/include -fprofile-arcs -ftest-coverage
LDFLAGS = -lgtest -lgmock -pthread -lgcov

# Директории
SRC_DIR = src
TEST_DIR = test
COVERAGE_DIR = coverage

# Находим все тестовые файлы автоматически
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

# Создаем список исполняемых файлов для тестов
EXES = $(TEST_FILES:$(TEST_DIR)/%.cpp=%)

# Сборка всех тестов
all: $(EXES)

# Компиляция каждого теста в отдельный исполняемый файл
$(EXES): %: $(TEST_DIR)/%.o
	$(CXX) -o $@ $^ $(LDFLAGS)

# Компиляция объектных файлов
$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск всех тестов
run-tests: all
	@for exe in $(EXES); do ./$$exe; done

# Сбор покрытия
coverage: $(EXES)
	@for exe in $(EXES); do ./$$exe; done  # Запускаем все тесты
	lcov --capture --directory . --output-file $(COVERAGE_DIR)/coverage.info --rc branch_coverage=1 --ignore-errors inconsistent --ignore-errors mismatch
	lcov --remove $(COVERAGE_DIR)/coverage.info '/usr/*' --output-file $(COVERAGE_DIR)/coverage_filtered.info
	genhtml $(COVERAGE_DIR)/coverage_filtered.info --output-directory $(COVERAGE_DIR) --branch-coverage
	@echo "Открыть отчет по покрытию в каталоге $(COVERAGE_DIR)"

# Очистка
clean:
	rm -f $(TEST_DIR)/*.o $(EXES)
	rm -rf $(COVERAGE_DIR)/*
	find $(TEST_DIR) -name "*.gcda" -exec rm -f {} \;

.PHONY: all clean run-tests coverage
