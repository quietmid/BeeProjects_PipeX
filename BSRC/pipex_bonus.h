/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:52:42 by jlu               #+#    #+#             */
/*   Updated: 2024/04/05 16:03:30 by jlu              ###   ########.fr       */
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
# define ERR_HD "here_doc"
# define ERR ""



typedef struct s_pipex
{
	pid_t	*pid;
	int		here_doc;
	int		**fd;
	int		cmd_n;
	int		pipe_n;
	int		filein;
	int		fileout;
	int		status;
	char	*path;
	char	*cmd;
	char	**path_cmds;
	char	**cmd_a;
}		t_pipex;

// here_doc
void	ft_here_doc(char *ag, t_pipex *pipex);
int		arg_count(char *ag, t_pipex *pipex);

//util
void	pipe_closer(t_pipex *pipex);
char	*find_path(char **envp);
void	error_msg(char *err, char *ag);
void	quotes_scan(char *str);
void	free_parent(t_pipex *pipex);
void	free_arr(char **array);

//pipe & child process
void	child_process(char **ag, char **envp, t_pipex pipex, int idx);
void	get_filein(char **ag, t_pipex *pipex);
void	get_fileout(char *ag, t_pipex *pipex);

#endif