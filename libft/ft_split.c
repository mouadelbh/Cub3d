/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:49:16 by mel-bouh          #+#    #+#             */
/*   Updated: 2023/11/10 20:38:32 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*(s + i))
	{
		while (*(s + i) == c && *(s + i))
			i++;
		if (*(s + i) != '\0')
		{
			count++;
			while (*(s + i) != c && *(s + i))
				i++;
		}
	}
	return (count);
}

static char	*cat_words(const char *s, char c)
{
	char	*word;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (*(s + i) != c && *(s + i))
		i++;
	word = (char *)malloc(sizeof(char) * i + 1);
	if (word == NULL)
		return (NULL);
	while (k < i)
	{
		*(word + k) = *(s + k);
		k++;
	}
	*(word + i) = '\0';
	return (word);
}

static void	free_split(char **split, int i)
{
	while (i > 0)
	{
		i--;
		free(split[i]);
	}
	free(split);
}

static char	**splited(char **split, char const *s, int counter, char c)
{
	int	i;

	i = 0;
	while (i < counter)
	{
		while (*s == c && *s)
			s++;
		if (*s != '\0')
		{
			split[i] = cat_words(s, c);
			if (!split[i])
			{
				free_split(split, i);
				return (NULL);
			}
			i++;
		}
		while (*s != c && *s)
			s++;
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		counter;
	char	**split;

	if (!s)
		return (NULL);
	counter = count_words(s, c);
	split = (char **)malloc(sizeof(char *) * (counter + 1));
	if (split == NULL)
		return (NULL);
	split = splited(split, s, counter, c);
	return (split);
}
