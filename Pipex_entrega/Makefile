
LIBFT_DIR := Libft
LIBFT := $(LIBFT_DIR)/libft.a

NAME := pipex
SRC_FILES := pipex.c parse_command.c split_path.c commands_exec.c utils_prepare_command.c
OBJ_FILES := $(SRC_FILES:%.c=%.o)
HEADERS := pipex.h parse_command.h split_path.h $(LIBFT_DIR)/libft.h $(LIBFT_DIR)/ft_printf.h

LIBFT_INCLUDES := $(LIBFT_DIR)
override C_FLAGS += -g3 -Wall -Wextra -Werror -fPIE
override CPPFLAGS += $(addprefix -I, $(LIBFT_INCLUDES))

all : $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	cp $(LIBFT) $@
	$(CC) $(OBJ_FILES) $(LIBFT) -o $@ $(CC_FLAGS)

$(OBJ_FILES):%.o: %.c $(HEADERS)
	$(CC) -c $(CPPFLAGS) $(C_FLAGS) $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) C_FLAGS="$(C_FLAGS)" CPPFLAGS="$(CPPFLAGS)"

clean:
	rm -rf $(OBJ_FILES)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
re: fclean all

.PHONY: all clean fclean re

