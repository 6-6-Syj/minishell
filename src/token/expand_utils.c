/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:49:04 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/09/02 18:29:48 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data.h"
#include "env.h"

static bool	is_special_char(char c)
{
	if (c == ',' || c == ' ')
		return (true);
	return (false);
}

bool	is_expand(char *token_content)
{
	if (ft_strlen(token_content) < 2)
		return (false);
	if (token_content[0] == '$' && !is_special_char(token_content[1]))
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
	while (token_content[i] && token_content[i] != '$'
		&& token_content[i] != '/' && token_content[i] != ' '
		&& token_content[i] != '\'')
		i++;
	return (i - 1);
}

char	*get_expand(char *token, t_data *data)
{
	char	*expand_key;
	char	*expand_value;
	int		len;

	if (ft_strncmp(token, "$?", 2) == 0)
	{
		expand_value = ft_itoa(data->err);
		if (!expand_value)
			malloc_fail(data);
		return (expand_value);
	}
	len = get_expand_key_len(token);
	expand_key = ft_substr(token, 1, len);
	if (!expand_key)
		malloc_fail(data);
	expand_value = get_env_var(data, expand_key);
	free(expand_key);
	return (expand_value);
}
