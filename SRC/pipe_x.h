/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_x.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:49 by jlu               #+#    #+#             */
/*   Updated: 2024/03/15 10:01:16 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_X_H
# define PIPE_X_H

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_pipex
{
	pid_t 	pid1;
	int		fd[2];
	int		filein;
	int		fileout;
	char	*path;
	char	*cmd;
	char	**path_cmds;
	char	**cmd_a;
}		t_pipex;

// Error Handling
void	error_msg(char *msg);

// Utils

void	find_cmd(char *ag, char **envp);
char	*find_path(char **envp);
void	exe_cmd(char *ag, char **envp);

//Processes
void	child_process(char **ag, char **envp, t_pipex pipex);
void	parent_process(char **ag, char **envp, t_pipex pipex);

#endif