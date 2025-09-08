/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:49:04 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/09/05 14:48:16 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "env.h"
#include "libft.h"
#include "token.h"

bool	is_expand(char *content)
{
	if (ft_strlen(content) < 2)
		return (false);
	if (ft_strncmp(content, "$?", 2) == 0)
		return (true);
	if (content[0] == '$' && (content[1] == '_' || ft_isalpha(content[1])))
		return (true);
	return (false);
}
bool	is_a_target_redir(t_token *token)
{
	if (token->prev)
		token = token->prev;
	while (token->type == SPACE)
		token = token->prev;
	if (token->type & REDIR)
		return (true);
	return (false);
}

int	get_expand_key_len(char *content)
{
	int	i;

	i = 1;
	if (!content)
		return (0);
	if (ft_strncmp(content, "$?", 2) == 0)
		return (1);
	while (content[i] && (content[i] == '_' || ft_isalnum(content[i])))
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
