/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:37:49 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/24 19:59:37 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_str(char **str)
{
	if (!*str)
		return (NULL);
	free(*str);
	return (NULL);
}

void	*free_lst(t_buff **lst)
{
	t_buff	*tmp;

	if (!*lst)
		return (NULL);
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	return (NULL);
}

int	get_line_lenght(t_buff *buff)
{
	int	len;
	int	i;

	len = 0;
	while (buff->next)
	{
		len += buff->b_read;
		buff = buff->next;
	}
	i = 0;
	while (i < buff->b_read && buff->content[i] != '\n')
		i++;
	if (buff->content[i] == '\n')
		i++;
	return (len + i);
}

bool	line_is_complete(t_buff *buff)
{
	int	i;

	if (!buff)
		return (false);
	while (buff->next)
		buff = buff->next;
	if (buff->b_read == 0)
		return (true);
	i = 0;
	while (i < buff->b_read)
	{
		if (buff->content[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}
