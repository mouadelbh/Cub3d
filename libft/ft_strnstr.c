/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:31:30 by mel-bouh          #+#    #+#             */
/*   Updated: 2023/11/10 21:11:07 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!haystack && !len)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (*(haystack + i) && len--)
	{
		j = 0;
		while (*(haystack + i + j) == *(needle + j) \
		&& *(needle + j) && j <= len)
		{
			if (!*(needle + j + 1))
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
