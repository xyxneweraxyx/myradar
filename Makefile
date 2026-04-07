# Compilation
TARGET := my_radar
CC := clang
FLAGS := -Wall -Wextra -Wno-implicit-function-declaration -g3 -O2

# Sources
SRC := $(shell find . -name '*.c')
OBJ := $(SRC:.c=.o)
HDR := $(shell find . -name '*.h')

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) $(SRC) -o $(TARGET) -lcsfml-window -lcsfml-system -lcsfml-graphics -lm

clean:
	rm -f $(shell find . -name '*.o')
	rm -f $(shell find . -name '*.c~')
	rm -f $(shell find . -name '*.h~')
	rm -f $(shell find . -name '*#*')
	rm -f $(shell find . -name '*.pch')
	rm -f $(shell find . -name '*.out')
	rm -f $(shell find . -name '*~')

fclean: clean
	rm -f $(shell find . -name '$(TARGET)')

re: fclean $(TARGET)

print_src:
	$(info $(shell find . -name '*.c'))

epiclang_all:
	epiclang $(SRC) $(HDR)