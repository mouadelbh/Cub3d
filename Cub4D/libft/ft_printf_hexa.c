/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:19:59 by asebaai           #+#    #+#             */
/*   Updated: 2025/01/28 17:34:08 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_hexa(unsigned int nbr, int indice)
{
	unsigned long	nb;
	static int		count;
	char			*hexa;

	nb = nbr;
	count = 0;
	hexa = "0123456789abcdef";
	if (indice == 1)
		hexa = "0123456789ABCDEF";
	if (nb >= 16)
	{
		ft_printf_hexa(nb / 16, indice);
	}
	count += ft_printf_char(hexa[nb % 16]);
	return (count);
}
