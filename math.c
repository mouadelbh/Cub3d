/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:20:25 by mel-bouh          #+#    #+#             */
/*   Updated: 2025/02/22 14:48:02 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	pythagore(int x0, int y0, int x, int y)
{
	int	Dx;
	int	Dy;
	int	result;

	Dx = abs(x - x0);
	Dy = abs(y - y0);
	result = sqrt(pow(Dx, 2) + pow(Dy, 2));
	return (result);
}
