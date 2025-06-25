#include "data.h"
#include "env.h"
#include "libft.h"
#include "token.h"
#include "unistd.h"

// void	init_token(t_data*data)
// {
// 	t_token	*token_lst;
// 	t_token	*new_token;
// 	t_token	*current_token;

// 	token_lst = data->token;
// 	lexer(data->token); //
// 		add_new_token(new_token);
// 		set_token_content(new_token);

// 	set_token_type(new_token);
// 		set_pipe_type(new_token);
// 		set_quote_type(new_token);
// 		set_redir_type(new_token);
// 		set_target_redir_type(new_token);
// 		set_command_type(new_token);
// 		set_arg_type(new_token);

// 	parse_token_lst(data->token);
// 		parse_double_quote(current_token); // delete quote, set_token_type();
// 	do_expand(token_lst);
// 		parse_simple_quote(current_token); // delete quote, set_token_type();
// 		delete_unused_space(current_token);
// 	syntax_is_valid(token_lst);

// 	init_ast();
// }

void	set_token_content(t_token *token_node, char *new_content)
{
	int	len;

	len = get_token_len(new_content);
	token_node->content = ft_strndup(new_content, len);
}

void	lexer(t_data *data)
{
	t_token	*new_token;
	int		i;

	i = 0;
	while (data->input[i] && data->input[i] != '\n')
	{
		// while (data->input[i] == ' ')
		// 	i++;
		new_token = add_token_node(&data->token);
		if (!new_token)
			exit_error(data); // malloc_error;
		set_token_content(new_token, &data->input[i]);
		if (!new_token->content)
			exit_error(data); // malloc_error;
		i += get_token_len(&data->input[i]);
	}
}

void	set_token_type(t_token **token_lst, t_data *data)
{
	t_token	*current_token;

	current_token = *token_lst;
	while (current_token)
	{
		current_token->type = get_token_type(current_token);
		if (current_token->type == UNKNOWN)
			exit_error(data); // syntax_error;
		current_token = current_token->next;
	}
}

void	remove_quote(char **token_content)
{
	char	*buff;
	int		len;

	len = ft_strlen(*token_content);
	buff = ft_substr(*token_content, 1, len - 2);
	free(*token_content);
	*token_content = buff;
}

void	parse_simple_quote(t_token **token_lst, t_data *data)
{
	t_token	*current_token;

	current_token = *token_lst;
	while (current_token)
	{
		if (current_token->type == QUOTE_S)
		{
			remove_quote(&current_token->content);
			current_token->type = WORD;
		}
		if (!current_token->content)
			exit_error(data);
		current_token = current_token->next;
	}
}

void	parse_double_quote(t_token **token_lst, t_data *data)
{
	t_token	*current_token;

	current_token = *token_lst;
	while (current_token)
	{
		if (current_token->type == QUOTE_D)
		{
			remove_quote(&current_token->content);
			current_token->type = WORD;
		}
		if (!current_token->content)
			exit_error(data);
		current_token = current_token->next;
	}
}
bool	is_expand(char *token_content)
{
	int	i;

	i = 0;
	if (!token_content[i] || !token_content[i + 1])
		return (false);
	// if (token_content[i] == '$' && is_part_of_word(token_content[i + 1]))
	if (token_content[i] == '$')
		return (true);
	return (false);
}

int	get_expand_len(char *token_content)
{
	int	i;

	i = 1;
	if (!token_content)
		return (0);
	while (token_content[i] && is_part_of_word(token_content[i]))
		i++;
	ft_printf("expand_len = %s\n", token_content);
	return (i);
}

char	*get_expand(char *token, t_data *data)
{
	char	*expand_key;
	char	*expand_value;
	int		len;

	len = get_expand_len(token);
	// ft_printf("key_len = %d\n", len);
	expand_key = ft_substr(token, 1, len - 1);
	// ft_printf("expand_key = %s\n", expand_key);
	// if (!expand_key)
	// 	exit_error(data);
	expand_value = get_env_var(data, expand_key);
	return (expand_value);
}

char	*concatenate_expand(char *first, char *inter, char *last, t_data *data)
{
	char	*buff;
	char	*dst;

	buff = ft_strjoin(first, inter);
	dst = ft_strjoin(buff, last);
	free(buff);
	if (!dst)
		exit_error(data);
	return (dst);
}
int	set_file_type(t_token **token_lst)
{
	t_token	*token_node;

	token_node = *token_lst;
	while (token_node)
	{
		if (token_node->type & REDIR && token_node->next)
		{
			token_node->next->type = REDIR_TARGET;
		}
		token_node = token_node->next;
	}
	return (0);
}

bool	is_in_quote(char *token, int pos)
{
	int		i;
	bool	in_quote;

	i = 0;
	in_quote = false;
	while (token[i] && i < pos)
	{
		if (token[i] == '\"' && in_quote == false)
			in_quote = true;
		if (token[i] == '\"' && in_quote == true)
			in_quote = false;
		i++;
	}
	return (in_quote);
}

char	*handle_expand(char *token, t_data *data)
{
	char	*first;
	char	*expand;
	char	*last;
	int		len;
	int		i;

	i = 0;
	while (token && token[i])
	{
		// if (is_expand(&token[i]) && !is_in_quote(token, i))
		if (is_expand(&token[i]))
		{
			// ft_printf("i = %d\n", i);
			expand = get_expand(&token[i], data);
			len = get_expand_len(&token[i]);
			// ft_printf("len = %d\n", len);
			// ft_printf("expand = \"%s\"\n", expand);
			first = ft_substr(token, 0, i); // secu
			// ft_printf("first = \"%s\"\n", first);
			i += len;
			last = ft_strdup(&token[i]); // secu
			// ft_printf("token[i] = \"%s\"\n", &token[i]);
			// ft_printf("last = \"%s\"\n", last);
			free(token);
			token = concatenate_expand(first, expand, last, data);
			// free_expand_buffer(first, expand, last);
		}
		i++;
	}
	return (token);
}

void	parse_expand(t_token **token_lst, t_data *data)
{
	t_token	*current_token;

	current_token = *token_lst;
	while (current_token)
	{
		if (current_token->type != QUOTE_S)
			current_token->content = handle_expand(current_token->content,
					data);
		current_token = current_token->next;
	}
}

void	join_word(t_token **token_lst, t_data *data)
{
	t_token	*current;
	char	*buff;

	(void)data;
	current = *token_lst;
	while (current && current->next)
	{
		if (current->type == WORD && current->next->type == WORD)
		{
			buff = ft_strjoin(current->content, current->next->content);
			free(current->content);
			current->content = buff;
			remove_node(current->next, data);
		}
		current = current->next;
	}
}

void	remove_wrong_expand(t_token **token_lst, t_data *data)
{
	t_token	*current;
	t_token	*tmp;

	(void)data;
	current = *token_lst;
	while (current)
	{
		tmp = current->next;
		if (ft_strcmp(current->content, "$") == 0)
			remove_node(current, data);
		current = tmp;
	}
}

void	init_token(t_data *data)
{
	lexer(data);
	set_token_type(&data->token, data);
	// set_operator_type
	// set_quote_type
	// set_word_type
	set_file_type(&data->token);
	parse_double_quote(&data->token, data);
	parse_expand(&data->token, data);
	// remove_wrong_expand(&data->token, data);
	join_word(&data->token, data);
	// set_file_type
	// set_cmd_type
	parse_simple_quote(&data->token, data);
	remove_space(&data->token, data);
	// handle_expand(&data->token, data);
	// handle_simple_quote(data->token, data);
	// delete_unused_space(data->token, data);
	// if (!syntax_is_valid(data->token, data))
	// 	exit_error(data);
}