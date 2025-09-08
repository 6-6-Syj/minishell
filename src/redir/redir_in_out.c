/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:27:38 by jmagand           #+#    #+#             */
/*   Updated: 2025/09/08 19:12:32 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "command.h"
#include "data.h"
#include "libft.h"
#include "redir.h"
#include "token.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static void	open_outfile(t_redir *file, int *fd, t_command *cmd, t_data *data)
{
	int	flags;

	if (file->type == REDIR_OUT || file->type == REDIR_APPEND)
	{
		if (file->type == REDIR_OUT)
			flags = (O_CREAT | O_TRUNC | O_RDWR);
		else
			flags = (O_CREAT | O_APPEND | O_RDWR);
		*fd = open(file->filename, flags, 0644);
		if (*fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(file->filename);
			data->err = 1;
			return ;
		}
		cmd->fd_out = *fd;
	}
}

static void	open_heredoc(t_command *cmd, t_redir *file, int *fd, t_data *data)
{
	if (!file->delimiter[0])
	{
		syntax_error(data);
		return ;
	}
	*fd = open(file->filename, O_RDONLY, 0644);
	if (*fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(file->filename);
		data->err = 1;
		return ;
	}
	cmd->fd_in = *fd;
}

static void	open_infile(t_redir *file, int *fd, t_command *cmd, t_data *data)
{
	data->syntax_err = false;
	if (file->type == REDIR_IN)
	{
		*fd = open(file->filename, O_RDONLY, 0644);
		if (*fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(file->filename);
			data->err = 1;
			return ;
		}
		cmd->fd_in = *fd;
	}
	else if (file->type == HERE_DOC)
		open_heredoc(cmd, file, fd, data);
}

void	open_files(t_command *cmd, t_data *data)
{
	t_redir	*file;
	int		new_fd_out;
	int		new_fd_in;

	file = cmd->redir;
	while (file)
	{
		open_infile(file, &new_fd_in, cmd, data);
		open_outfile(file, &new_fd_out, cmd, data);
		if (!data->err)
			file = file->next;
		else
			break ;
	}
	if (data->syntax_err == true)
		data->err = 2;
	if (cmd && cmd->args[0])
		redir(cmd, data);
}
