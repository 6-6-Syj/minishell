/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:27:09 by jmagand           #+#    #+#             */
/*   Updated: 2025/09/08 22:31:21 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "libft.h"
#include "token.h"

static void	lexer(t_data *data)
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

static void	handle_space(t_token **token_lst, t_data *data)
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
	data->syntax_err = false;
	lexer(data);
	set_token_type(&data->token);
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
		syntax_error(data);
		free_tmp_data(data);
	}
}
