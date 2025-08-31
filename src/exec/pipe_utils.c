/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-31 20:01:48 by jmagand           #+#    #+#             */
/*   Updated: 2025-08-31 20:01:48 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

bool	has_redir_out(t_command *cmd)
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

bool	has_redir_in(t_command *cmd)
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
