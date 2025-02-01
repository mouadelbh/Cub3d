/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:51:05 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/01 22:33:38 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	error_cases(char **map, int row, int col, int *ply_pos)
{
	if (map[row][col] == '\t')
	{
		ft_putstr_fd("Error!\nDetecting tabulation in map part\n", 2);
		ft_putstr_fd("Please, replace it by spaces and try again\n", 2);
		return (-1);
	}
	if (map[row][col] != ' ' && map[row][col] != '1'
		&& map[row][col] != '0' && map[row][col] != 'N' && map[row][col] != 'S'
		&& map[row][col] != 'W' && map[row][col] != 'E')
		return (prblem("Error!\nWrong map content: ", map[row], "\n"));
	if (map[row][col] == 'N' || map[row][col] == 'S' || map[row][col] == 'W'
		|| map[row][col] == 'E')
		(*ply_pos)++;
	if (*ply_pos > 1)
		return (prblem("Error!\nThere is too many player in map\n", "", ""));
	return (0);
}

int	check_map_content(char **map, int size)
{
	int	row;
	int	col;
	int	ply_pos; 

	row = 0;
	ply_pos = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col] && map[row][col] != '\n')
		{
			if (error_cases(map, row, col, &ply_pos) == -1)
				return (-1);
			col++;
		}
		row++;
	}
	if (ply_pos == 0)
		return (prblem("Error!\nPlayer position missing\n", "", ""));
	return (check_wall1(map, size));
}

int	map_make(t_list *start, char ***map)
{
	int		i;
	int		size;

	size = find_size(start);
	*map = (char **)malloc(sizeof(char *) * (size + 1));
	if (!*map)
		return (prblem("Error!\n", "map_make: ", "Malloc failed\n"));
	i = 0;
	while (start)
	{
		if (!is_empty_line(start->content))
			(*map)[i++] = start->content;
		else
		{
			while (start && is_empty_line(start->content))
				start = start->next;
			if (start != NULL)
				return (prblem("Error\nToo much info after map\n", "", ""));
		}
		if (start)
			start = start->next;
	}
	(*map)[i] = NULL;
	return (check_map_content(*map, size));
}

int	switch_info_to_list(t_mlx *config)
{
	int		rslt;
	t_list	*tmp;

	rslt = 0;
	tmp = config->file;
	while (tmp)
	{
		if (valid_element(tmp->content)
			&& !element_already_present(tmp->content, config))
			rslt = 0;
		else if (is_empty_line(tmp->content))
			rslt = 0;
		else if (is_start_map(tmp->content) && config->nb_element == 6)
			return (map_make(tmp, &config->map));
		else
			rslt = -1;
		if (rslt == -1)
		{
			ft_putstr_fd("Error!\nNot correct element or bad map position ", 2);
			ft_putstr_fd("or a element is missing : ", 2);
			return (prblem((char *)tmp->content, "Please check again\n", ""));
		}
		tmp = tmp->next;
	}
	return (0);
}
int	check_cub_content(t_mlx *config)
{
	if (!config->file)
	{
		prblem("Error!\n", "Empty file\n", "");
		return (-1);
	}
	if (!config->no || !config->so || !config->we || !config->ea
		|| !config->f || !config->c || !config->map)
	{
		ft_putstr_fd("Error!\nGame configuration not complete\n", 2);
		ft_putstr_fd("Please check again\n", 2);
		return (-1);
	}
	return (0);
}
