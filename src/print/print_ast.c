#include "minishell.h"

void	print_ast_lst(t_ast *ast_lst)
{
	int	i;

	i = 0;
	ft_printf("+-----------------------+\n");
	ft_printf("|  AST LST              |\n");
	ft_printf("+-----------------------+\n");
	if (ast_lst->type == PIPE)
	{
		printf("node_type = PIPE\n");
		if (ast_lst->pipe.left)
			print_ast_lst(ast_lst->pipe.left);
		if (ast_lst->pipe.right)
			print_ast_lst(ast_lst->pipe.right);
	}
	else if (ast_lst->type == COMMAND)
	{
		printf("node_type = COMMAND\n");
		while (ast_lst->command.args[i])
			printf("cmd[i] = %s\n", ast_lst->command.args[i++]);
	}
	printf("\n\n");
	}