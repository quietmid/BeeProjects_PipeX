/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:17:54 by jlu               #+#    #+#             */
/*   Updated: 2024/03/12 16:50:36 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_x.h"

/*
pipex should take in 3 to 5 arguments. 
store the first arg and read into the the arg[2] and [3] to determine what it should do. 
apply the cmd to file1 and file2 
output the final
*/

int	main(int ac, char **ag, char **envp)
{
	int fd[2];
	
	if (ac == 5)
	{
		if (pipe(fd) == -1)
			error_msg_params()
	}
	else
		error_msg_params(WRONG_ARGCOUNT, "Cmon man, I need FOUR arguments!"); // is this okay?
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	int id = fork();
	int n;
	if (id == 0)
		n = 1;
	else
		n = 6;
	if (id != 0)
		wait();
	int i;
	for (i = n; i < n + 5; i++)
		printf("%d ", i);
		fflush(stdout);
}

/*
if (pid < 0)
	fork failed
	printf Fork failed
	return 1 
*/