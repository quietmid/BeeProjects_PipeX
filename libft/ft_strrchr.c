/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:26:52 by jlu               #+#    #+#             */
/*   Updated: 2023/11/17 16:26:54 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;
	size_t	len;

	str = (char *)s;
	len = ft_strlen(str);
	i = len;
	while (i >= 0)
	{
		if (str[i] == (char)c)
		{
			return (&str[i]);
		}
		i--;
	}
	return (NULL);
}
