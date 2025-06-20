#include "ast.h"
#include <redir.h>
#include <stdlib.h>

void		free_ast(t_ast **node);

void	free_redir_node(t_redir *redir_node)
{
	if (redir_node->delimiter)
		free(redir_node->delimiter);
	if (redir_node->filename)
		free(redir_node->filename);
	free(redir_node);
}

void	free_redir_lst(t_redir **redir_lst)
{
	t_redir	*current;
	t_redir	*tmp;

	current = *redir_lst;
	while (current)
	{
		tmp = current->next;
		free_redir_node(current);
		current = tmp;
	}
}

static void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs && strs[i])
	{
		if (strs[i])
			free(strs[i]);
		i++;
	}
	free(strs);
}

static void	free_pipe_node(t_ast *node)
{
	if (!node)
		return ;
	if (node->pipe.left)
		free_ast(&node->pipe.left);
	if (node->pipe.right)
		free_ast(&node->pipe.right);
	free(node);
}

static void	free_command_node(t_ast *node)
{
	if (!node)
		return ;
	if (node->command.args)
		free_strs(node->command.args);
	if (node->command.redir)
		free_redir_lst(&node->command.redir);
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