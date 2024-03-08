/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:18:14 by jlu               #+#    #+#             */
/*   Updated: 2023/11/17 16:18:17 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	ch;

	ch = (unsigned char)c;
	str = ((unsigned char *)s);
	i = 0;
	while (i < n)
	{
		if (str[i] == ch || (ch == '\0' && str[i] == '\0'))
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
