/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:18:40 by jlu               #+#    #+#             */
/*   Updated: 2023/11/17 16:18:42 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*cdest;
	unsigned char	*csrc;

	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	if (cdest == NULL && csrc == NULL)
		return (NULL);
	i = 0;
	if (dest < src)
		ft_memcpy(cdest, csrc, len);
	else if (dest > src)
	{
		while (i < len)
		{
			cdest[len - 1] = csrc[len - 1];
			len--;
		}
	}
	return (dest);
}
