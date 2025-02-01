/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:20:39 by asebaai           #+#    #+#             */
/*   Updated: 2025/01/28 17:34:08 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_unsi(unsigned int nb)
{
	long		nbr;
	static int	len;

	nbr = nb;
	len = 0;
	if (nbr > 9)
		ft_printf_unsi(nbr / 10);
	len += ft_printf_char(nbr % 10 + 48);
	return (len);
}
