/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:20:09 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/22 16:29:46 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_nbr(int nb)
{
	int			sign;
	long		nbr;
	static int	len;

	sign = 0;
	nbr = nb;
	len = 0;
	if (nbr < 0)
	{
		ft_printf_char('-');
		nbr *= -1;
		sign = 1;
	}
	if (nbr > 9)
		ft_printf_nbr(nbr / 10);
	len += ft_printf_char(nbr % 10 + 48);
	return (len + sign);
}
