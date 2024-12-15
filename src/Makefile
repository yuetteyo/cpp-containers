# sudo apt install libgtest-dev
CC := g++
STANDARD := -std=c++17
CFLAGS := -Wall -Wextra -Werror $(STANDARD)
TEST_FLAGS := $(shell pkg-config gtest --libs)
GCOV_FLAGS := -fprofile-arcs -ftest-coverage
OS := $(shell uname -s)

PROJECT := s21_containers

all : test


clean :
	rm -rf *.a *.o s21_containers_test

rebuild : clean all


test : $(wildcard containers_tests/*.cpp)
	$(CC) $(CFLAGS) $(PROJECT)_$@.cpp $+ -o $(PROJECT)_$@ $(TEST_FLAGS)
	./$(PROJECT)_$@

format :
	clang-format --style=file:"../materials/linters/.clang-format" -i */*.cpp */*.h

check :
	clang-format --style=file:"../materials/linters/.clang-format" -n */*.cpp */*.h
	@# cppcheck --enable=all --suppress=missingIncludeSystem -$(STANDARD) --language=c++ */*.cpp */*.h

valgrind_check :
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(PROJECT)_test
