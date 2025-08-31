/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:12:25 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/25 19:48:39 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "redir.h"

static bool	has_redir_out(t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			return (true);
		redir = redir->next;
	}
	return (false);
}

static bool	has_redir_in(t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			return (true);
		redir = redir->next;
	}
	return (false);
}

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

static bool right_cmd_got_redirout(t_ast *node)
{
    if (!node)
        return (false);
    if (node->type == CMD)
        return (has_redir_out(&node->command));
    else if (node->type == PIPE)
        return (right_cmd_got_redirout(node->pipe.right));
    return (false);
}

void handle_pipe(t_pipe *pipe, t_data *data, int *fd, t_pid_list **pids)
{
    if ((pipe->left && pipe->left->type == PIPE && 
         right_cmd_got_redirout(pipe->left)) ||
        (pipe->left && pipe->left->type == CMD && 
         has_redir_out(&pipe->left->command)))
    {
        int empty_pipe[2];
        w_pipe(empty_pipe, data);
        close(empty_pipe[1]);
        if (pipe->right && pipe->right->type == CMD)
        	pipe->right->command.fd_in = empty_pipe[0];
        handle_ast(pipe->left, data, fd, pids);
        handle_ast(pipe->right, data, fd, pids);
        close(empty_pipe[0]);
    }
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
        handle_ast(pipe->left, data, fd, pids);
        handle_ast(pipe->right, data, fd, pids);
        close(fd[1]);
        close(fd[0]);
    }
}



