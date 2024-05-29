/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_supp_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:41:07 by jlu               #+#    #+#             */
/*   Updated: 2024/04/17 17:30:26 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	quotes_scan(char *str)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n') \
		&& (count == 0 || count == 2))
			str[i] = 31;
		if (str[i] == c)
		{
			count += 1;
			str[i] = 31;
		}
		if ((str[i] == 39 || str[i] == 34) && count == 0)
		{
			c = str[i];
			count += 1;
			str[i] = 31;
		}
		i++;
	}
}

char	**cmd_split(char *str)
{
	char	**result;

	quotes_scan(str);
	result = ft_split(str, 31);
	if (!result)
		error_msg(ERR, NULL);
	return (result);
}

char	*find_cmd(char **ag, char **path)
{
	char	*cmd;

	cmd = NULL;
	if (ag[0] == NULL)
		error_msg(ERR_CMD, ag[0]);
	if (ag[0][0] == '/' || ag[0][0] == '.')
		cmd = ag[0];
	else
		cmd = exe_cmd(ag[0], path);
	return (cmd);
}
