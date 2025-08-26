/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:03:05 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/08/26 16:54:23 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <redir.h>
#include <stdlib.h>
#include <utils.h>

void	free_ast(t_ast **node);

void	free_redir_lst(t_redir **redir_lst)
{
	t_redir	*current;
	t_redir	*tmp;

	current = *redir_lst;
	while (current)
	{
		tmp = current->next;
		if (current->delimiter)
			free(current->delimiter);
		if (current->filename)
			free(current->filename);
		free(current);
		current = tmp;
	}
}

static void	free_pipe_node(t_ast *node)
{
	if (!node)
		return ;
	if (node->pipe.left)
		free_ast(&node->pipe.left);
	if (node->pipe.right)
		free_ast(&node->pipe.right);
}

static void	free_command_node(t_ast *node)
{
	if (!node)
		return ;
	if (node->command.args)
		free_strs(node->command.args);
	if (node->command.redir)
		free_redir_lst(&node->command.redir);
}

void	free_ast(t_ast **node)
{
	if (!*node)
		return ;
	else if ((*node)->type == PIPE)
		free_pipe_node(*node);
	else if ((*node)->type == CMD)
		free_command_node(*node);
	if (*node)
		free(*node);
}
