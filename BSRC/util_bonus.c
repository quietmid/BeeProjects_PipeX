/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:13:04 by jlu               #+#    #+#             */
/*   Updated: 2024/03/29 17:13:18 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_msg(char *err, char *ag)
{
	ft_putstr_fd("pipex: ", 2);
	if (err == ERR_CMD)
	{
		ft_putstr_fd(ag, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(err, 2);
		exit (127);
	}
	if (ag != NULL)
	{
		ft_putstr_fd(ag, 2);
		ft_putstr_fd(": ", 2);
	}
	perror("");
	exit (EXIT_FAILURE);
}