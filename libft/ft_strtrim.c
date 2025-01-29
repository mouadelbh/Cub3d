/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:23:41 by mel-bouh          #+#    #+#             */
/*   Updated: 2023/11/11 19:57:24 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char const *set, char s1)
{
	if (!set)
		return (0);
	while (*set)
	{
		if (*set == s1)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*trim;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	size = ft_strlen(s1);
	while (check(set, *(s1 + i)) && *(s1 + i))
		i++;
	while (check(set, *(s1 + (size - 1))) && size > i)
		size--;
	trim = (char *)malloc(sizeof(char) * (size - i + 1));
	if (trim == NULL)
		return (NULL);
	j = 0;
	while (i < size)
	{
		*(trim + j) = *(s1 + i);
		i++;
		j++;
	}
	*(trim + j) = '\0';
	return (trim);
}
