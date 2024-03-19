/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:24:51 by jlu               #+#    #+#             */
/*   Updated: 2024/03/19 16:33:05 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_x.h"

// when the file can't be found
// zsh: no such file or directiory: `input`
// 0: stdinput 1: stdoutput 2:stderror 
void	error_msg(char *msg)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putendl_fd(msg, 2);
	//perror(msg);
	exit (EXIT_FAILURE);
}

// go through the envp and search for PATH then get that string after the PATH 
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return(*envp + 5); // the 5 to get pass the PATH
}


