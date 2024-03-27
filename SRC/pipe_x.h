/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_x.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:49 by jlu               #+#    #+#             */
/*   Updated: 2024/03/27 17:20:48 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_X_H
# define PIPE_X_H

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
//# include <sys/types.h>
# include <errno.h>

# define ERR_INPUT "Cmon man, do you know how to count up to four?"
# define ERR_CMD "command not found"
# define ERR ""

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int		filein;
	int		fileout;
	int		status;
	char	*path;
	char	*cmd;
	char	**path_cmds;
	char	**cmd_a;
}		t_pipex;

// Error Handling
void	error_msg(char *msg, char *ag);

// Utils

char	*find_path(char **envp);
void	pipe_closer(t_pipex *pipex);
void	free_arr(char **array);
void	free_parent(t_pipex *pipex);
void	free_child(t_pipex *pipex);
void	quotes_scan(char *str);
//Processes
void	child_process1(char **ag, char **envp, t_pipex pipex);
void	child_process2(char **ag, char **envp, t_pipex pipex);

#endif