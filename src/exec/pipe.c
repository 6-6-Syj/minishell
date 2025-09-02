/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:12:25 by jmagand           #+#    #+#             */
/*   Updated: 2025/09/02 19:14:28 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "wrappers.h"
#include "ast.h"
#include "data.h"
#include "exec.h"
#include <unistd.h>

static void	assign_pipe_fds(t_ast *node, int fd_in, int fd_out)
{
	if (!node)
		return ;
	if (node->type == CMD)
	{
		if (fd_in != -1 && !has_redir_in(&node->command))
			node->command.fd_in = fd_in;
		if (fd_out != -1 && !has_redir_out(&node->command))
			node->command.fd_out = fd_out;
	}
	else if (node->type == PIPE)
	{
		assign_pipe_fds(node->pipe.left, fd_in, -1);
		assign_pipe_fds(node->pipe.right, -1, fd_out);
	}
}

static bool	right_cmd_got_redirout(t_ast *node)
{
	if (!node)
		return (false);
	if (node->type == CMD)
		return (has_redir_out(&node->command));
	else if (node->type == PIPE)
		return (right_cmd_got_redirout(node->pipe.right));
	return (false);
}

static void	handle_pipe_with_redirout(t_pipe *pipe, t_data *data, int *fd)
{
	int	empty_pipe[2];

	w_pipe(empty_pipe, data);
	close(empty_pipe[1]);
	if (pipe->right && pipe->right->type == CMD)
		pipe->right->command.fd_in = empty_pipe[0];
	handle_ast(pipe->left, data, fd);
	handle_ast(pipe->right, data, fd);
	close(empty_pipe[0]);
}

void	handle_pipe(t_pipe *pipe, t_data *data, int *fd)
{
	if ((pipe->left && pipe->left->type == PIPE
			&& right_cmd_got_redirout(pipe->left)) || (pipe->left
			&& pipe->left->type == CMD && has_redir_out(&pipe->left->command)))
		handle_pipe_with_redirout(pipe, data, fd);
	else
	{
		w_pipe(fd, data);
		if (pipe->left && pipe->left->type == CMD)
		{
			if (!has_redir_out(&pipe->left->command))
				pipe->left->command.fd_out = fd[1];
		}
		else if (pipe->left && pipe->left->type == PIPE)
			assign_pipe_fds(pipe->left, -1, fd[1]);
		if (pipe->right && pipe->right->type == CMD)
		{
			if (!has_redir_in(&pipe->right->command))
				pipe->right->command.fd_in = fd[0];
		}
		handle_ast(pipe->left, data, fd);
		handle_ast(pipe->right, data, fd);
		close(fd[1]);
		close(fd[0]);
	}
}
