/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:51:05 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/27 18:25:42 by mel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

char	*dlt_spaces(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (line);
}

static int	check_info(char *tmp)
{
	int	i;
	int	start_digit;
	int	end_digit;

	i = 0;
	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
		i++;
	start_digit = i;
	while (tmp[i] && ft_isdigit(tmp[i]))
		i++;
	end_digit = i;
	if (start_digit == end_digit)
		return (prblem("Error!\n", "Bad information\n", ""));
	while (tmp[i])
	{
		if (tmp[i] != ' ' && tmp[i] != '\t' && tmp[i] != ',' && tmp[i] != '\n')
			return (prblem("Error!\n", "Bad information", "\n"));
		i++;
	}
	tmp[end_digit] = '\0';
	if (ft_atoi(tmp + start_digit) < 0 || ft_atoi(tmp + start_digit) > 255)
		return (prblem("Error!\nColor code has to be between 0-255\n", "", ""));
	return (0);
}

int	with_correct_info(char *line)
{
	char	**tab;
	int		i;

	tab = ft_split(line, ',');
	if (!tab)
		return (prblem("Error!\nWith_correct_info: Malloc failed\n", "", ""));
	i = 0;
	while (tab[i])
	{
		if (i > 2 || check_info(tab[i]) == -1)
		{
			free_tab(tab);
			return (0);
		}
		i++;
	}
	free_tab(tab);
	if (i < 3)
		return (0);
	return (1);
}

int	valid_element(char *line)
{
	char	*tmp;

	line = dlt_spaces(line);
	tmp = line;
	if (((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)) && (line[2] == ' ' || line[2] == '\t')) || ((line[0] == 'C' || line[0] == 'F') && (line[1] == ' ' || line[1] == '\t')))
	{
		tmp += 2;
		while (*tmp && (*tmp == ' ' || *tmp == '\t'))
			tmp++;
		if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)))
		{
			while (*tmp && *tmp != ' ' && *tmp != '\t')
				tmp++;
			tmp = dlt_spaces(tmp);
			if (*tmp && *tmp != '\n')
				return (0);
			return (1);
		}
		else if ((line[0] == 'C' || line[0] == 'F') && with_correct_info(tmp))
			return (1);
	}
	return (0);
}
