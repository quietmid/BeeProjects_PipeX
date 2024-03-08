/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:19:13 by jlu               #+#    #+#             */
/*   Updated: 2023/11/17 16:19:17 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbl;

	nbl = n;
	if (nbl < 0)
	{
		nbl *= -1;
		ft_putchar_fd('-', fd);
	}
	if (nbl < 10)
		ft_putchar_fd(nbl + '0', fd);
	else
	{
		ft_putnbr_fd((nbl / 10), fd);
		ft_putnbr_fd((nbl % 10), fd);
	}
}
