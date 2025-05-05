/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:10:52 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 20:10:52 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "errno.h"
#include "libft.h"

static char	*gnl_error(void)
{
	errno = 1;
	return (NULL);
}

static t_buff	*extract_next_line(t_buff *buff)
{
	t_buff	*tmp;
	int		i;
	int		j;

	if (!buff)
		return (NULL);
	while (buff->next)
	{
		tmp = buff->next;
		free(buff);
		buff = tmp;
	}
	i = 0;
	while (i < buff->b_read && buff->content[i] != '\n')
		i++;
	i++;
	j = 0;
	while (i < buff->b_read)
		buff->content[j++] = buff->content[i++];
	buff->b_read = j;
	if (buff->b_read == 0)
		return (free_lst(&buff));
	return (buff);
}

static char	*extract_curr_line(t_buff *buff)
{
	char	*dst;
	int		i;
	int		j;
	int		len;

	len = get_line_lenght(buff);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (gnl_error());
	i = 0;
	while (buff)
	{
		j = 0;
		while (i < len && j < buff->b_read && buff->content[j] != '\n')
			dst[i++] = buff->content[j++];
		if (j < buff->b_read && buff->content[j] == '\n')
			dst[i++] = buff->content[j];
		buff = buff->next;
	}
	dst[i] = '\0';
	if (dst[0] == '\0')
		return (free_str(&dst));
	return (dst);
}

static bool	read_fd(t_buff **buff, int fd)
{
	t_buff	*new;
	t_buff	*tmp;

	new = malloc(sizeof(t_buff));
	if (!new)
	{
		errno = 1;
		return (false);
	}
	new->content[0] = '\0';
	new->next = NULL;
	new->b_read = read(fd, new->content, BUFFER_SIZE);
	if (!*buff)
		*buff = new;
	else
	{
		tmp = *buff;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	if (new->b_read < 0)
		return (false);
	return (true);
}

char	*get_next_line(int fd)
{
	static t_buff	*buff;
	bool			nl;
	bool			rd;
	char			*dst;

	rd = true;
	nl = line_is_complete(buff);
	while (rd && !nl)
	{
		rd = read_fd(&buff, fd);
		nl = line_is_complete(buff);
	}
	if (!rd)
		return (free_lst(&buff));
	if (nl)
	{
		dst = extract_curr_line(buff);
		buff = extract_next_line(buff);
		return (dst);
	}
	return (NULL);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int fd;
// 	char *dst;
// 	int i = 100;

// 	fd = open("bible.txt", O_RDONLY);
// 	while (1)
// 	{
// 		dst = get_next_line(fd);
// 		printf("dst = %s\n", dst);
// 		if (!dst)
// 			return (0);
// 		if (dst)
// 			free(dst);
// 		i--;
// 	}
// }
