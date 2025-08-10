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
			exit_error(data); // malloc_error;
		len = get_token_len(&data->input[i]);
		new_token->content = ft_strndup(&data->input[i], len);
		// if (!new_token->content)
		// 	exit_error(data);
		i += get_token_len(&data->input[i]);
	}
}

int	get_cmd_count(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == CMD)
			count++;
		token = token->next;
	}
	return (count);
}

bool	redir_is_valid(t_token *token)
{
	t_token *tmp;

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

bool	syntax_is_valid(t_token *token)
{
	if (!redir_is_valid(token))
		return (false);
	return (true);
}
// TODO: concatenate useless space

void	handle_space(t_token **token_lst, t_data *data)
{
	t_token *current;

	current = *token_lst;
	while (current)
	{
		if (current->type == SPACE)
		{
			free(current->content);
			current->content = ft_strdup(" ");
			if (!current->content)
			{
				//print_error_message
				exit_error(data);
			}
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
	remove_simple_quote(&data->token, data);
	// remove_space(&data->token, data);
	// print_all(data);
	handle_space(&data->token, data);
	set_file_type(&data->token);
	join_word(&data->token, data);
	set_command_type(&data->token);
	set_token_priority(&data->token);
	if (!syntax_is_valid(data->token))
	{
		ft_putstr_fd("Error\n", 2);
		exit_error(data);
	}
	// print_all(data);
}

// syntax_error:
// -redir without target
// -pipe without command or redir
// -convert tab in space
// -echo "" '' : must keep the space
