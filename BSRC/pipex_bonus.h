/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:52:42 by jlu               #+#    #+#             */
/*   Updated: 2024/04/03 16:26:51 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIPEX_BONUS_H
# define PIPEX_BONUS_H

// other functions library
# include "../libft/libft.h"

// Library Headers
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>

//error definition

# define ERR_CMD "command not found"
# define ERR_INPUT "trap card activated: not enough inputs"
# define ERR ""

typedef struct s_pipex
{
	pid_t	*pid;
	int		**fd;
	int		cmd_n;
	int		pipe_n;
	int		idx;
	int		filein;
	int		fileout;
	int		status;
	char	*path;
	char	*cmd;
	char	**path_cmds;
	char	**cmd_a;
}		t_pipex;

//util
void	pipe_closer(t_pipex *pipex);
char	*find_path(char **envp);
void	error_msg(char *err, char *ag);
void	quotes_scan(char *str);
void	waiting(t_pipex *pipex);
void	free_arr(char **array);

//pipe & child process
void	child_process(char **ag, char **envp, t_pipex pipex);
void	get_filein(char **ag, t_pipex *pipex);
void	get_fileout(char *ag, t_pipex *pipex);

#endif