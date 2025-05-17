
LIBFT_DIR := Library
LIBFT := $(LIBFT_DIR)/libft.a

NAME := pipex
SRC_FILES := pipex.c pipex_parse_path.c pipex_parse_command.c
OBJ_FILES := $(SRC_FILES:%.c=%.o)
HEADERS := pipex.h $(LIBFT_DIR)/libft.h $(LIBFT_DIR)/ft_printf.h

LIBRARY_INCLUDES := $(LIBFT_DIR)
#override CC_FLAGS += -g3 -fsanitize=address -Wall -Wextra -Werror -fPIE
override CC_FLAGS += -g3 -Wall -Wextra -Werror -fPIE
override CPPFLAGS += $(addprefix -I, $(LIBRARY_INCLUDES))

all : $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	cp $(LIBFT) $@
	$(CC) $(OBJ_FILES) $(LIBFT) -o $@ $(CC_FLAGS)

$(OBJ_FILES):%.o: %.c $(HEADERS)
	$(CC) -c $(CPPFLAGS) $(CC_FLAGS) $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) CC_FLAGS="$(CC_FLAGS)" CPPFLAGS="$(CPPFLAGS)"

clean:
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
re: fclean all

.PHONY: all clean fclean re

