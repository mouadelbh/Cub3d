/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:00:11 by mel-bouh          #+#    #+#             */
/*   Updated: 2023/11/11 20:02:33 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	length;
	size_t	i;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	i = 0;
	if (start > length)
		len = 0;
	else if (len > (length - start))
		len = length - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	s = s + start;
	*(sub + len) = '\0';
	while (len-- && *s)
	{
		*(sub + i) = *(s + i);
		i++;
	}
	return (sub);
}
