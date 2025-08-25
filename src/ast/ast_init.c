/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:08:13 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/08/25 16:12:32 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include "print.h"
#include "redir.h"
#include "token.h"
#include "unistd.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

t_ast	*create_command_node(t_token *token, t_data *data)
{
	int		i;
	int		len;
	t_ast	*new_node;
	t_token	*tmp;

	tmp = token;
	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		malloc_fail(data);
	new_node->command.fd_in = -1;
	new_node->command.fd_out = -1;
	new_node->type = CMD;
	len = get_args_len(tmp);
	new_node->command.args = ft_calloc(len + 2, sizeof(char *));
	if (!new_node->command.args)
		malloc_fail(data);
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD || tmp->type == ARG)
			new_node->command.args[i++] = ft_strdup(tmp->content);
		// SECUUUUUUUUUUUUUUUUUUUUUUUUURE
		tmp = tmp->next;
	}
	init_redir(token, &new_node->command.redir, data);
	return (new_node);
}

t_ast	*create_pipe_node(t_token *token, t_data *data)
{
	t_ast	*new_node;
	t_token	*token_left;
	t_token	*token_right;

	token_left = get_prev_priority_token(token);
	token_right = get_next_priority_token(token);
	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		malloc_fail(data);
	new_node->pipe.left = create_ast_node(token_left, data);
	new_node->pipe.right = create_ast_node(token_right, data);
	new_node->type = PIPE;
	return (new_node);
}

t_ast	*create_ast_node(t_token *token, t_data *data)
{
	if (!token)
		return (NULL);
	if (token->type == PIPE)
		return (create_pipe_node(token, data));
	if (token->type == CMD)
		return (create_command_node(token, data));
	else if (token->type & REDIR)
		return (create_command_node(token, data));
	return (NULL);
}

int	init_ast(t_ast **ast_lst, t_token **token_lst, t_data *data)
{
	t_token	*root_token;

	root_token = get_root_token(token_lst, 0);
	if (!root_token)
		return (1);
	*ast_lst = create_ast_node(root_token, data);
	return (0);
}
