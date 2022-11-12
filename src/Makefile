# --gtest_brief=1 - to show only test failures

CC = gcc
FLAGS = -Wall -Werror -Wextra -lstdc++ -std=c++17 -lgtest

VECTOR = tests/vector_tests.cc

# HEADER = s21_containers.h

CONTAINERS = $(VECTOR)

all: test

re: clean test

test: vector_test

vector_test:
	$(CC) $(FLAGS) $(VECTOR) -o test_vector
	./test_vector --gtest_brief=1