#include "libft.h"
#include "minishell.h"

bool	is_expand(char *token_content)
{
	if (!token_content[0] || !token_content[1])
		return (false);
	if (token_content[0] == '$')
		return (true);
	return (false);
}

int	get_expand_key_len(char *token_content)
{
	int	i;

	i = 1;
	if (!token_content)
		return (0);
	if (ft_strncmp(token_content, "$?", 2) == 0)
		return (1);
	// while (token_content[i] && is_part_of_word(token_content[i]))
	while (token_content[i] && token_content[i] != '$'
		&& token_content[i] != '/' && token_content[i] != ' ' && token_content[i] != '\'')
		i++;
	return (i - 1);
}

// int	get_expand_value_len(char *token_content)
// {
// 	int	i;

// 	i = 1;
// 	if (!token_content)
// 		return (0);
// 	if (ft_strncmp(token_content, "$?", 2) == 0)
// 		return (2);
// 	// while (token_content[i] && is_part_of_word(token_content[i]))
// 	while (token_content[i] && token_content[i] != '$'
// 		&& token_content[i] != '/' && token_content[i] != ' ' && token_content[i] != '\'')
// 		i++;
// 	return (i);
// 	// return (i - 1);
// }

char	*get_expand(char *token, t_data *data)
{
	char *expand_key;
	char *expand_value;
	int len;

	if (ft_strncmp(token, "$?", 2) == 0)
		return (ft_itoa(data->err));
	len = get_expand_key_len(token);
	// printf("token = %s\n", token);
	expand_key = ft_substr(token, 1, len);
	if (!expand_key)
		exit_error(data);
	// printf("expand_key = %s\n", expand_key);
	expand_value = get_env_var(data, expand_key);
	// printf("expand_value = %s\n", expand_value);
	free(expand_key);
	return (expand_value);
}