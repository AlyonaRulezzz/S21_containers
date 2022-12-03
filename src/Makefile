# --gtest_brief=1 - to show only test failures

.PHONY: all re test clean check style leak
#.PHONY если есть файлы с именем как цель, они игнорируются

CC = gcc
FLAGS = -Wall -Werror -Wextra -lstdc++ -std=c++17 -lgtest -Wno-unused -pedantic -g
# TST_LIBS := -lgtest -lm -lpthread

VECTOR = tests/vector_tests.cc
MAP = tests/map_tests.cc

# HEADER = s21_containers.h

# 
CONTAINERS = $(VECTOR) $(MAP)

all: test

re: clean test

# 
test: vector_test map_test

vector_test: vector_test.o
	$(CC) $(FLAGS) vector_test.o -o test_vector
	./test_vector --gtest_brief=1

vector_test.o:
	$(CC) $(FLAGS) -c $(VECTOR) -o vector_test.o

map_test: map_test.o
	$(CC) $(FLAGS) map_test.o -o test_map
	./test_map --gtest_brief=1

map_test.o:
	$(CC) $(FLAGS) -c $(MAP) -o map_test.o



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
	clang-format -i *.h tests/*
	@# iterators/*
	clang-format -n *.h tests/*
	@# iterators/*

leak:
	# CK_FORK=no leaks -atExit -- ./test_vector
	CK_FORK=no leaks -atExit -- ./test_map
