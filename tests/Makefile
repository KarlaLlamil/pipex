NAME := tests
CC := cc
CFLAGS := -g3 -Wall -Werror -Wextra
CPPFLAGS := -I ../ -I ../Library

SRCS := ../split_path.c tests.c ../parse_command.c
OBJS :=  $(SRCS:.c=.o)

######################################################

all: $(NAME)

$(NAME): $(OBJS) ../Library/libft.a
	$(CC) -o $@ $^

%.o: %.c
		$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<


../Library/libft.a: 
	make -C ../Library

clean:
	rm -f $(OBJS)

.PHONY: all clean