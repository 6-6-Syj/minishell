#include "minishell.h"

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
		new_token->content = ft_strndup(new_token->content, len);
		if (!new_token->content)
			exit_error(data);
		i += get_token_len(&data->input[i]);
	}
}

void	init_token(t_data *data)
{
	lexer(data);
	set_token_type(&data->token, data);
	parse_double_quote(&data->token, data);
	parse_expand(&data->token, data);
	parse_simple_quote(&data->token, data);
	join_word(&data->token, data);
	remove_space(&data->token, data);
	set_file_type(&data->token);
	set_command_type(&data->token);
	set_token_priority(&data->token);
}