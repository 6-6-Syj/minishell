#include "minishell.h"

void	print_ast_lst(t_ast *ast_lst)
{
	t_ast	*ast_left_node;
	t_ast	*ast_right_node;

	ft_printf("+-----------------------+\n");
	ft_printf("|  AST LST              |\n");
	ft_printf("+-----------------------+\n");
	if (ast_lst)
	{
		ast_left_node = ast_lst->left;
		ast_right_node = ast_lst->right;
		if (ast_lst->args[0])
			ft_printf("head->args[0] = %s\n", ast_lst->args[0]);
		if (ast_lst->args[1])
			ft_printf("head->args[1] = %s\n", ast_lst->args[1]);
		printf("\n\n");
		if (ast_left_node->args[0])
			ft_printf("left_node->args[0] = %s\n", ast_left_node->args[0]);
		if (ast_left_node->args[1])
			ft_printf("left_node->args[1] = %s\n", ast_left_node->args[1]);
		printf("\n\n");
		if (ast_right_node->args[0])
			ft_printf("right_node->args[0] = %s\n", ast_right_node->args[0]);
		if (ast_right_node->args[1])
			ft_printf("right_node->args[1] = %s\n", ast_right_node->args[1]);
		printf("\n\n");
	}
}
