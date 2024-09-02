CC := g++
CFLAGS := -Wall -Wextra
SRCS := $(wildcard srcs/*.cpp)
OBJS := $(SRCS:srcs/%.cpp=%.o)
HEADERS := $(wildcard includes/*.hpp)
LIB := libftpp.a

all: $(LIB)

$(LIB): $(OBJS)
	ar rcs $@ $^

%.o: srcs/%.cpp includes/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@ -I includes

fclean:
	rm -f $(OBJS) $(LIB)

re: fclean all

.PHONY: all fclean re
