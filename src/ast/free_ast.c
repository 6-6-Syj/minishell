#include "ast.h"
#include <stdlib.h>

void	free_ast(t_ast **node);

static void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static void	free_pipe_node(t_ast *node)
{
	if (!node)
		return ;
	free_ast(&node->pipe.left);
	free_ast(&node->pipe.right);
	free(node);
}

static void	free_command_node(t_ast *node)
{
	if (!node)
		return ;
	if (node->command.args)
		free_strs(node->command.args);
	free(node);
}

static void	free_logic_node(t_ast *node)
{
	if (!node)
		return ;
	free_ast(&node->logic.left);
	free_ast(&node->logic.right);
	free(node);
}

void	free_ast(t_ast **node)
{
	if (!*node)
		return ;
	else if ((*node)->type == PIPE)
		free_pipe_node(*node);
	else if ((*node)->type == CMD)
		free_command_node(*node);
	else if ((*node)->type == AND || (*node)->type == OR)
		free_logic_node(*node);
}
