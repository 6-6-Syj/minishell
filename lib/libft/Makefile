#------------------------------------------------#
#					COLORS						 #
#------------------------------------------------#
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
BLUE		= \033[0;34m
CYAN		= \033[0;36m
MAGENTA		= \033[0;35m
WHITE		= \033[1;37m
BOLD    	= \033[1m
RESET		= \033[0m

#------------------------------------------------#
#					FILES						 #
#------------------------------------------------#
NAME		= libft.a
FILES 		= ft_atoi ft_atoll ft_bzero ft_calloc ft_isalpha ft_isascii ft_isdigit \
			  ft_isprint ft_itoa ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset \
			  ft_putchar ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_split ft_strcat \
			  ft_strchr ft_strcmp ft_strdup ft_strndup ft_striteri ft_strjoin ft_strlcat ft_strlcpy \
			  ft_strlen ft_strmapi ft_strncmp ft_strnstr ft_strrchr ft_strtrim ft_substr \
			  ft_tolower ft_toupper ft_print_char ft_print_hex ft_print_int ft_printf get_next_line \
			  get_next_line_utils ft_lstnew ft_lstadd_back ft_lstadd_front ft_lstlast ft_lstsize \
			  ft_lstdelone ft_lstclear ft_lstiter ft_lstmap

#------------------------------------------------#
#					COMMANDS					 #
#------------------------------------------------#
AR			= ar
RM			= rm -rf

#------------------------------------------------#
#					FLAGS						 #
#------------------------------------------------#
ARFLAGS		= -rcs
CFLAGS		= -Wall -Wextra -Werror
CPPFLAGS	= -MMD -MP -Iinclude
MAKEFLAGS	+= --no-print-directory

#------------------------------------------------#
#					DIRECTORY					 #
#------------------------------------------------#
INC_DIR		= include/
SRC_DIR 	= src/
OBJ_DIR 	= .build/

#------------------------------------------------#
#					PATHS						 #
#------------------------------------------------#
INC			= include/libft.h
SRC			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJ			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))
DEP			= $(addprefix $(OBJ_DIR), $(addsuffix .d, $(FILES)))

#------------------------------------------------#
#					RULES						 #
#------------------------------------------------#
all: $(NAME)

$(NAME): $(OBJ) | $(OBJ_DIR)
	@echo "\n$(MAGENTA)$(BOLD)🛠️  Building static library...$(RESET)"
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	@echo "$(GREEN)$(BOLD)\n📚 Library created successfully!$(RESET)"
	@echo "$(CYAN)    ├─ Library name: $(NAME)$(RESET)"
	@echo "$(CYAN)    ├─ Objects: $(words $(OBJ))$(RESET)"
	@echo "$(CYAN)    └─ Dependencies: $(words $(DEP))\n$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC) Makefile | $(OBJ_DIR)
	@echo "  → Compiling $(YELLOW)$<$(RESET)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJ_DIR) $(OBJ)
	@echo "$(MAGENTA)$(BOLD)🧹 Cleaning up libft files...$(RESET)"
	@echo "$(CYAN)    ├─ Removed object files and dependencies"
	@echo "$(CYAN)    └─ Cleaned build directory: $(OBJ_DIR)$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)$(BOLD)\n🗑️  Libft full clean completed:$(RESET)"
	@echo "$(CYAN)    └─ Static library removed: $(NAME)$(RESET)\n"

-include $(DEP)

$(OBJ_DIR):
	@mkdir -p $@

re: fclean all

.PHONY: all clean fclean re
