#------------------------------------------------#
#					STRUCTURE					 #
#------------------------------------------------#
# minishell
# ├── Makefile
# ├── minishell
# ├── src/
# |	  ├── main.c
# │   ├── parsing/
# │   |── error/
# │   └── exec/
# ├── .build/
# │	  ├── test1.o
# │	  └── test1.d
# ├── include/
# │   ├── minishell.h
# │   ├── parsing/
# │   ├── error/
# │   └── exec/
# └── lib/
#     └── libft/
#	      ├── libft.a
#	      ├── src/
#	      └── include/
#	          └── libft.h

# VPATH = src				\
# 		src/parsing			\
# 		src/exec			\
# 		src/error			\
# 		src/builtins		\
# 		include				\
# 		include/exec		\
# 		include/parsing		\
# 		include/error		\
# 		include/builtins	\

vpath %.c src src/builtins src/token src/data src/print src/env src/exec
vpath %.i include include/builtins include/parsing include/print include/exec

-include mk_files/token.mk mk_files/data.mk mk_files/builtins.mk mk_files/env.mk mk_files/print.mk mk_files/exec.mk

#------------------------------------------------#
#					NOTES						 #
#------------------------------------------------#
# run				:	make run ARGS="arg1 arg2"
# run with valgrind :	make valgrind ARGS="arg1 arg2"

#------------------------------------------------#
#					FILES						 #
#------------------------------------------------#
NAME		= minishell
LIBFT		= lib/libft/libft.a
INCLUDES	= minishell.h $(DATA_INC) $(TOKEN_INC) $(BUILTINS_INC) $(PRINT_INC) $(ENV_INC) $(EXEC_INC)
SRC_FILES	= main $(DATA_SRC) $(TOKEN_SRC) $(BUILTINS_SRC) $(PRINT_SRC) $(ENV_SRC) $(EXEC_SRC)

#------------------------------------------------#
#					DIRECTORY					 #
#------------------------------------------------#
OBJ_DIR		= .build/
INC_DIR		= include/

#------------------------------------------------#
#					PATHS						 #
#------------------------------------------------#
SRC			= $(addsuffix .c, $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEP 		= $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))
INC			= $(addprefix $(INC_DIR), $(INCLUDES))

#------------------------------------------------#
#					COMMANDS					 #
#------------------------------------------------#
CC			= cc
RM			= rm -rf

#------------------------------------------------#
#					FLAGS						 #
#------------------------------------------------#
CFLAGS		= -Wall -Wextra -Werror -g3
CPPFLAGS	= -MMD -MP $(IFLAGS)
LDFLAGS		= -Llib/libft
IFLAGS		= -Iinclude -Ilib/libft/include -Iinclude/builtins -Iinclude/parsing -Iinclude/print -Iinclude/exec
LDLIBS		= -lft
MAKEFLAGS	+= --no-print-directory
# DEBUG		= -g3

#------------------------------------------------#
#					RULES						 #
#------------------------------------------------#

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) | $(OBJ_DIR)
	@echo "\n$(MAGENTA)$(BOLD)💻 Compiling executable...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)$(BOLD)\n✅ Compilation successful!$(RESET)"
	@echo "$(CYAN)    └─ Ready to run: ./$(NAME)\n$(RESET)"

$(OBJ_DIR)%.o: %.c $(INC) Makefile | $(OBJ_DIR)
	@echo "  → Compiling $(YELLOW)$<$(RESET)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(LIBFT):
	@$(MAKE) -C lib/libft

-include $(DEP)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(MAGENTA)$(BOLD)🧹 Cleaning up project files...$(RESET)"
	@echo "$(CYAN)    ├─ Removed object files, and dependencies$(RESET)"
	@echo "$(CYAN)    └─ Cleaned build directory: $(OBJ_DIR)$(RESET)"

fclean: clean
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@echo "$(GREEN)$(BOLD)\n🗑️  Full clean-up completed:$(RESET)"
	@echo "$(CYAN)    └─ Executable removed: ./$(NAME)\n$(RESET)"

re: fclean all

libft:
	@$(MAKE) -C lib/libft

clean-libft:
	@$(MAKE) -C lib/libft clean

fclean-libft:
	@$(MAKE) -C lib/libft fclean

re-libft: fclean-libft libft

fclean-all: fclean fclean-libft

clean-all: clean clean-libft

re-all: fclean fclean-libft libft all

# debug:
# 	@$(NAME)

valgrind: all
	@echo "$(BOLD)Running with Valgrind:$(RESET)"
	@valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all ./$(NAME) $(ARGS)

run: all
	@echo "$(BOLD)🚀 Running:$(RESET) ./$(NAME) $(ARGS)"
	@./$(NAME) $(ARGS)

.PHONY: all clean fclean re debug valgrind run
.PHONY: libft clean-libft fclean-libft re-libft
.PHONY: clean-all fclean-all re-all

#------------------------------------------------#
#					COLORS						 #
#------------------------------------------------#
RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[1;33m
BLUE	= \033[0;34m
CYAN	= \033[0;36m
MAGENTA	= \033[0;35m
WHITE	= \033[1;37m
BOLD    = \033[1m
RESET   = \033[0m
