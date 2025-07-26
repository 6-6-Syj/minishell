#include "minishell.h"
#include "libft.h"

bool	is_expand(char *token_content)
{
	if (!token_content[0] || !token_content[1])
		return (false);
	if (token_content[0] == '$')
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
	return (i);
}

char	*get_expand(char *token, t_data *data)
{
	char	*expand_key;
	char	*expand_value;
	int		len;

	if (ft_strcmp(token, "$?") == 0)
		return (ft_itoa(data->err));
	len = get_expand_len(token);
	expand_key = ft_substr(token, 1, len - 1);
	if (!expand_key)
		exit_error(data);
	expand_value = get_env_var(data, expand_key);
	free(expand_key);
	return (expand_value);
}
