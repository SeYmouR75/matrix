CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra
TEST_DIR=./tests
BUILD_DIR=./build
REPORT_DIR=./report

ifeq ($(wildcard $(BUILD_DIR)), )
  $(shell mkdir $(BUILD_DIR))
endif
ifeq ($(wildcard $(REPORT_DIR)), )
  $(shell mkdir $(REPORT_DIR))
endif

SRC=$(wildcard *.c)
OBJ=$(addprefix $(BUILD_DIR)/,$(SRC:%.c=%.o))
TARGET=s21_matrix.a

$(TARGET): $(OBJ)
	ar rcs $@ $(OBJ)

$(BUILD_DIR)/%.o: %.c    
	$(CC) $(CFLAGS) -c $< -o $@

test: clean $(TARGET)
	cd $(TEST_DIR) && make test

gcov_report: clean gcov_flags $(TARGET)	
	cd $(TEST_DIR) && make gcov
	lcov -t "coverage_report" -o $(REPORT_DIR)/s21_matrix.info -c -d $(BUILD_DIR) -d $(TEST_DIR)/$(BUILD_DIR)
	genhtml $(REPORT_DIR)/s21_matrix.info -o report 
	xdg-open $(REPORT_DIR)/index.html

gcov_flags: 
	$(eval CFLAGS += -g3 --coverage)

clean_obj:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(TARGET)

clean_gcov:
	rm -rf $(REPORT_DIR)/*

clean: clean_obj clean_gcov
	cd $(TEST_DIR) && make clean

clang_check:
	clang-format -style=Google -n *.c *.h
	cd $(TEST_DIR) && make clang_check

clang_format: clang_check
	clang-format -style=Google -i *.c *.h
	cd $(TEST_DIR) && make clang_format

rebuild: clean all
