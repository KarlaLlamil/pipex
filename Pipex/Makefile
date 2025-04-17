CC := cc
LIBFT_DIR := Library
LIBFT := $(LIBFT_DIR)/libft.a

NAME := pipex
SRC_FILES := pipex.c pipex_parse_path.c
OBJ_FILES := $(SRC_FILES:.c=.o)
HEADERS := pipex.h $(LIBFT_DIR)/libft.h $(LIBFT_DIR)/ft_printf.h

LIBRARY_INCLDES := $(LIBFT_DIR)
override CC_FLAGS += -Wall -Wextra -Werror -fPIE
override CPPFLAGS += $(addprefix -I, $(LIBRARY_INCLUDES))

all : $(NAME)

$(NAME): $(LIBFT)$(OBJ_FILES)


