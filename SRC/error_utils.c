/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:24:51 by jlu               #+#    #+#             */
/*   Updated: 2024/03/12 16:36:29 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_x.h"

// when the file can't be found
// zsh: no such file or directiory: `input`
// 0: stdinput 1: stdoutput 2:stderror 
void	error_msg_params(t_error error, char *msg)
{
	ft_putstr_fd("pipex: ", 2);
	if (error == CMD_MISSING)
	{
		ft_putendl_fd("command not found: ", 2);
		exit (1);
	}
	if (error == NO_PATH)
	{
		ft_putstr_fd("No such file or directory: ", 2);
		ft_putendl_fd(msg, 2);
		exit (1);
	}
	if (error == FAIL_EXCU)
	{
		ft_putstr_fd("permission denied: ", 2);
		if (!msg)
		{
			msg = "\n";
			ft_putendl_fd(msg, 2);
			exit (1);
		}
	}
	perror(msg);
	exit (EXIT_FAILURE);
}