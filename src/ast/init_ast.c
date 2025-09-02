/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:08:13 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/09/02 20:42:39 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "data.h"
#include "libft.h"
#include "redir.h"
#include "token.h"

static t_ast	*create_ast_node(t_token *token, t_data *data);

static void	set_command_node(t_command *cmd, t_token *token, t_data *data)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == CMD || token->type == ARG)
		{
			cmd->args[i++] = ft_strdup(token->content);
			if (ft_strlen(token->content) != ft_strlen(cmd->args[i - 1]))
				malloc_fail(data);
		}
		token = token->next;
	}
}

static t_ast	*create_command_node(t_token *token, t_data *data)
{
	int		len;
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		malloc_fail(data);
	new_node->command.fd_in = -1;
	new_node->command.fd_out = -1;
	new_node->command.is_last_cmd = false;
	new_node->type = CMD;
	len = get_args_len(token);
	new_node->command.args = ft_calloc(len + 1, sizeof(char *));
	if (!new_node->command.args)
		malloc_fail(data);
	set_command_node(&new_node->command, token, data);
	init_redir(token, &new_node->command.redir, data);
	return (new_node);
}

static t_ast	*create_pipe_node(t_token *token, t_data *data)
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

static t_ast	*create_ast_node(t_token *token, t_data *data)
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
	if (*ast_lst && (*ast_lst)->type == CMD)
		(*ast_lst)->command.is_last_cmd = true;
	else if (*ast_lst && (*ast_lst)->type == PIPE)
		(*ast_lst)->pipe.right->command.is_last_cmd = true;
	data->err = 0;
	return (0);
}
