NAME := libft.a
CC := cc
CC_FLAGS ?= -Wall -Wextra -Werror
HEADERS := libft.h ft_printf.h
SRC_FILES := ft_isalpha.c ft_isascii.c  ft_memmove.c ft_strlcpy.c ft_substr.c \
	ft_isdigit.c  ft_memset.c   ft_strlen.c   ft_tolower.c ft_atoi.c ft_itoa.c\
	ft_isprint.c  ft_split.c ft_toupper.c ft_bzero.c ft_strmapi.c\
	ft_strchr.c   ft_strncmp.c  ft_calloc.c  ft_memchr.c ft_striteri.c \
	ft_strdup.c   ft_strnstr.c  ft_isalnum.c  ft_memcmp.c  ft_strjoin.c \
	ft_strrchr.c  ft_memcpy.c   ft_strlcat.c ft_strtrim.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	ft_len.c ft_printf.c f_hex.c fft_itoa.c ft_print_char.c\
	printf_format.c

OBJ_FILES := $(SRC_FILES:%.c=%.o)

BONUS_SRC := ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJ_BONUS := $(BONUS_SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar -rcs $(NAME) $(OBJ_FILES)

bonus: $(OBJ_FILES) $(OBJ_BONUS)
	ar -rcs $(NAME) $(OBJ_FILES) $(OBJ_BONUS)

%.o: %.c $(HEADERS)
	$(CC) $(CC_FLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJ_FILES) $(OBJ_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all bonus re

