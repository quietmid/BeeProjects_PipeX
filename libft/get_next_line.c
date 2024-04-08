/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:16:02 by jlu               #+#    #+#             */
/*   Updated: 2024/04/08 17:18:47 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char **str)
{
	if (*str)
		free (*str);
	*str = NULL;
	return (NULL);
}

static char	*read_line(int fd, char *s_buff, char *rd_buf, int *check)
{
	int		bytes;
	char	*temp_line;

	bytes = 1;
	while (!ft_gnl_strchr(rd_buf, '\n'))
	{
		bytes = read(fd, rd_buf, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		if (bytes == 0)
			break ;
		rd_buf[bytes] = '\0';
		if (!s_buff)
			s_buff = ft_strdup("");
		temp_line = s_buff;
		s_buff = ft_gnl_strjoin(temp_line, rd_buf);
		if (!s_buff)
		{
			*check = 1;
			return (ft_free(&temp_line));
		}
		ft_free(&temp_line);
	}
	return (s_buff);
}

static char	*update_line(char *line, int *check)
{
	int		i;
	char	*s_buff;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	s_buff = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	if (!s_buff)
	{
		*check = 1;
		if (line)
			return (ft_free(&line));
		return (NULL);
	}
	if (s_buff[0] == '\0')
		return (ft_free(&s_buff));
	return (s_buff);
}

static char	*fix_line(char *line)
{
	int		i;
	char	*result;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	result = ft_substr(line, 0, i + 1);
	return (result);
}

char	*get_next_line(int fd)
{
	static int	check;
	static char	*buff;
	char		*line;
	char		rd_buf[BUFFER_SIZE + 1];
	char		*result;

	line = NULL;
	result = NULL;
	if ((fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0) && check == 0)
		return (ft_free(&buff));
	line = read_line(fd, buff, rd_buf, &check);
	if (!line)
		return (NULL);
	check = 0;
	buff = update_line(line, &check);
	if (check == 1)
		return (NULL);
	result = fix_line(line);
	ft_free(&line);
	if (!result && buff)
		return (ft_free(&buff));
	return (result);
}

//#include <fcntl.h>
//#include <stdio.h>

//int	main(void)
//{
//	int	fd;
//	char	*line;
//	int	i;

//	fd = open("testMap.txt", O_RDONLY);

//	if (fd == -1)
//	{
//		perror("Error opening file");
//		return (1);
//	}
//	i = 0;
//	while ((line = get_next_line(fd)) != NULL)
//	{
//		printf("%d%s", i++, line);
//		free(line);
//	}
//	close(fd);
//	return 0;
//}