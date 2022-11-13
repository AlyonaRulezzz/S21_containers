# --gtest_brief=1 - to show only test failures

.PHONY: all re test clean check test style leak
#.PHONY если есть файлы с именем как цель, они игнорируются

CC = gcc
FLAGS = -Wall -Werror -Wextra -lstdc++ -std=c++17 -lgtest -Wno-unused -pedantic -g
# TST_LIBS := -lgtest -lm -lpthread

VECTOR = tests/vector_tests.cc

# HEADER = s21_containers.h

# 
CONTAINERS = $(VECTOR)

all: test

re: clean test

# 
test: vector_test

vector_test: vector_test.o
	$(CC) $(FLAGS) vector_test.o -o test_vector
	./test_vector --gtest_brief=1

vector_test.o:
	$(CC) $(FLAGS) -c $(VECTOR) -o vector_test.o



gcov_report: gcov_test.info
	@genhtml -o report/ gcov_test.info
	@open report/index.html

gcov_test.info: gcov_test gcov_test.gcda
	@lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_test: $(CONTAINERS)
	$(CC) $(CFLAGS) --coverage $(CONTAINERS) -o gcov_test

gcov_test.gcda:
	@chmod +x *
	@./gcov_test

clean: 
	@rm -rf *.o *.a test gcov_test *.gcno *.gcda *.info report *.dSYM \
	test_map test_set test_array test_multiset test_vector \
	test_list test_stack test_queue
	
style:
	cp ../materials/linters/.clang-format ./
	clang-format -i  *.c *.h *.hpp *.cc *.cpp iterators/* tests/*
	clang-format -n  *.c *.h *.hpp *.cc *.cpp iterators/* tests/*

leak:
	CK_FORK=no leaks -atExit -- ./gcov_test
