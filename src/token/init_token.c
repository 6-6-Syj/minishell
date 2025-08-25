/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:27:09 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/25 17:58:18 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "env.h"
#include "errno.h"
#include "libft.h"
#include "print.h"
#include "stdio.h"
#include "string.h"
#include "token.h"
#include "unistd.h"

void	lexer(t_data *data)
{
	t_token	*new_token;
	int		i;
	int		len;

	i = 0;
	while (data->input[i] && data->input[i] != '\n')
	{
		new_token = add_token_node(&data->token);
		if (!new_token)
			malloc_fail(data);
		len = get_token_len(&data->input[i]);
		new_token->content = ft_strndup(&data->input[i], len);
		if (!new_token->content)
			malloc_fail(data);
		i += get_token_len(&data->input[i]);
	}
}

bool	redir_is_valid(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		if (token->type & REDIR)
		{
			tmp = token->next;
			while (tmp && tmp->type == SPACE)
				tmp = tmp->next;
			if (!tmp || tmp->type != REDIR_TARGET)
				return (false);
		}
		token = token->next;
	}
	return (true);
}

// bool	pipe_is_valid(t_token *token)
// {
// 	t_token	*tmp;
// 	int	cmd_count;

// 	while (token && token->type != PIPE)
// 	{
// 		tmp = token;
// 		cmd_count = 0;
// 		while (tmp && tmp->type != PIPE)
// 		{
// 			if (tmp->type == CMD)
// 				cmd_count++;
// 			tmp = tmp->prev;
// 		}
// 		token = token->next;
// 	}
// 	return (true);
// }

bool	syntax_is_valid(t_token *token)
{
	// if (!pipe_is_valid(token))
	// 	return (false);
	if (!redir_is_valid(token))
		return (false);
	if (token->type == PIPE)
		return (false);
	return (true);
}

void	handle_space(t_token **token_lst, t_data *data)
{
	t_token	*current;

	current = *token_lst;
	if (current && !current->next && current->type == SPACE)
	{
		remove_node(current, data);
		data->ast = NULL;
		return ;
	}
	while (current)
	{
		if (current->type == SPACE)
		{
			free(current->content);
			current->content = ft_strdup(" ");
			if (!current->content)
				malloc_fail(data);
		}
		current = current->next;
	}
}

void	init_token(t_data *data)
{
	lexer(data);
	set_token_type(&data->token, data);
	remove_double_quote(&data->token, data);
	expand_var(&data->token, data);
	if (!data->token)
		return ;
	remove_simple_quote(&data->token, data);
	handle_space(&data->token, data);
	set_file_type(&data->token);
	join_word(&data->token, data);
	set_command_type(&data->token);
	set_token_priority(&data->token);
	if (data->token && !syntax_is_valid(data->token))
	{
		ft_putstr_fd("Error\n", 2);
		data->err = 2;
		exit_error(data);
	}
}
