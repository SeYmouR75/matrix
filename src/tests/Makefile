CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra
LIBS=-lcheck -lm -lsubunit

BUILD_DIR=./build
SRC=$(wildcard %.c)
OBJ=$(addprefix $(BUILD_DIR)/,$(SRC_C:%.c=%.o))

TARGET=s21_test_matrix.exe

S21_LIB=../s21_matrix.a

ifeq ($(wildcard $(BUILD_DIR)), )
  $(shell mkdir $(BUILD_DIR))
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(S21_LIB) -o $(BUILD_DIR)/$@ $(LIBS)

$(OBJ):
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

test: $(TARGET)
	./$(BUILD_DIR)/$(TARGET)

gcov: gcov_flags test

gcov_flags:
	$(eval CFLAGS += -g3 --coverage)

clang_check:
	clang-format -style=Google -n *.c *.h

clang_format: clang_check
	clang-format -style=Google -i *.c

clean:
	rm -rf $(BUILD_DIR)