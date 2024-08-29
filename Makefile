CC := g++
CFLAGS := -Wall -Wextra #-std=c++11
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
HEADERS := $(wildcard *.hpp)
LIB := libftpp.a

all: $(LIB)

$(LIB): $(OBJS)
	ar rcs $@ $^

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

fclean:
	rm -f $(OBJS) $(LIB)

re: fclean all

.PHONY: all fclean re
