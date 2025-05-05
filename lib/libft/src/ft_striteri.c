/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/11/22 01:34:17 by dabuchhe          #+#    #+#             */
/*   Updated: 2024/11/22 01:34:17 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		f(i, &str[i]);
		i++;
	}
}
