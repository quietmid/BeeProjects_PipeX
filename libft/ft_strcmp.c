/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 23:21:20 by jlu               #+#    #+#             */
/*   Updated: 2024/04/11 16:13:03 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	result;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	result = (s1[i] - s2[i]);
	return (result);
}

/*
int	main(void)
{
	char	str1[] = "abcde";
	char	str2[] = "abcde";

	printf("The first string is: %s\n", str1);
	printf("The second string is: %s\n", str2);
	printf("String compare: %d\n", ft_strcmp(str1, str2));
	return (0);
}*/