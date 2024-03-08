/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:16:51 by jlu               #+#    #+#             */
/*   Updated: 2023/11/18 17:14:26 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isnegative(long n)
{
	if (n < 0)
		return (1);
	return (0);
}

static int	ft_intlength(int n)
{
	int		nbl_len;
	long	nbl;

	nbl_len = 0;
	nbl = n;
	if (n == 0)
		return (nbl_len + 1);
	if (n < 0)
	{
		n *= -1;
		nbl_len++;
	}
	while (nbl)
	{
		nbl = nbl / 10;
		nbl_len++;
	}
	return (nbl_len);
}

char	*ft_itoa(int n)
{
	long	nbl;
	int		len;
	char	*number;
	int		sign;

	nbl = n;
	sign = ft_isnegative(nbl);
	len = ft_intlength(nbl);
	number = malloc(len + 1 * sizeof(char));
	if (number == NULL)
		return (NULL);
	number[len--] = '\0';
	if (n == 0)
		number[len] = '0';
	if (nbl < 0)
		nbl = nbl * -1;
	while (len >= 0)
	{
		number[len] = (nbl % 10) + 48;
		nbl /= 10;
		len--;
	}
	if (sign == 1)
		number[0] = '-';
	return (number);
}
