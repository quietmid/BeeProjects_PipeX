/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:13:32 by jlu               #+#    #+#             */
/*   Updated: 2023/11/18 17:17:51 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_int(const char *str, int i)
{
	unsigned long	nb;

	nb = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (i == 1 && nb > (unsigned long)LONG_MAX / 10)
			return (-1);
		else if (i == -1 && nb > (unsigned long)LONG_MAX / 10)
			return (0);
		nb = nb * 10;
		if (i == 1 && nb > (unsigned long)LONG_MAX - (*str - 48))
			return (-1);
		else if (i == -1 && nb > (unsigned long)LONG_MAX - (*str - 48))
			return (0);
		nb += (*str - 48);
		str++;
	}
	return (nb);
}

int	ft_atoi(const char *str)
{
	unsigned long	nb;
	int				i;

	nb = 0;
	i = 1;
	while (((*str > 8 && *str < 14) || *str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			i *= -1;
		str++;
	}
	nb = ft_get_int(str, i);
	return (nb * i);
}
