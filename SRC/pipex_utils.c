/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:24:51 by jlu               #+#    #+#             */
/*   Updated: 2024/03/13 21:15:43 by jlu              ###   ########.fr       */
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

void	find_cmd(char *ag, char **envp)
{
	char	**cmd;
	char	*path;

	if (!ag)
		perror("Error");
	cmd = ft_split(ag, ' ');
	if (!cmd)
		error_msg("Split Fail");
		
}
