/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:22:48 by jlu               #+#    #+#             */
/*   Updated: 2023/11/17 16:25:45 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str1)
{
	char	*strp;
	size_t	count;
	size_t	i;

	count = ft_strlen((char *)str1);
	strp = (char *)malloc((count + 1) * sizeof(*str1));
	if (!strp)
		return (strp);
	i = 0;
	while (str1[i] != '\0')
	{
		strp[i] = str1[i];
		i++;
	}
	strp[i] = '\0';
	return (strp);
}
