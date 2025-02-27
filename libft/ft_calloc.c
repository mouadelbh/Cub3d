/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:10:21 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/22 16:28:51 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t element, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(element * size * sizeof(char));
	if (!ptr || element == 0 || size == 0)
		return (ptr);
	if ((element * size) / element != size)
	{
		free(ptr);
		return (NULL);
	}
	ft_memset(ptr, 0, element * size);
	return (ptr);
}
/*
#include <stdint.h>
#include <stdio.h>

int	main(void)
{
	void	*ptr;

	ptr = calloc(0, 0);
	//printf("%p", ptr);
	free(ptr);
}
*/
