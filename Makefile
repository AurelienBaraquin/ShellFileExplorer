##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

CFLAGS += -O3 -W -Wall -Wextra -lncurses
CPPFLAGS += -I./includes

OBJ_DIR = obj

SRC := $(shell find src -name "*.cpp")

OBJ := $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.cpp=.o)))

TARGET = prog

.PHONY: all clean fclean re

all: $(TARGET)

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	g++ $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJ)
	g++ -o $(TARGET) $^ $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(TARGET)

re: fclean all
