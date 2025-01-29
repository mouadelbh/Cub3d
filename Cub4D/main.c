/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:26:07 by asebaai           #+#    #+#             */
/*   Updated: 2025/01/29 16:32:51 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.h"

int	prblem(char *msg1, char *msg2, char *msg3)
{
	int	rslt;

	while (*msg1)
		rslt = write(2, msg1++, 1);
	while (*msg2)
		rslt = write(2, msg2++, 1);
	while (*msg3)
		rslt = write(2, msg3++, 1);
	rslt = -1;
	return (rslt);
}

int	check_file_path(char *gamefile)
{
	int		fd;
	int		len;

	len = ft_strlen(gamefile);
	if (gamefile[len - 1] == 'b' && gamefile[len - 2] == 'u'
		&& gamefile[len - 3] == 'c' && gamefile[len - 4] == '.')
	{
		fd = open(gamefile, O_RDONLY);
		if (fd == -1)
		{
			perror("Error!\n");
			prblem(gamefile, "\n", "");
			return (-1);
		}
	}
	else
	{
		prblem("Error!\nBad map extension: ", gamefile, "\n");
		return (-1);
	}
	return (fd);
}

void	readfile_to_list(int fd, t_cubconfig *config)
{
	t_list	*tmp;

	while (1)
	{
		tmp = ft_lstnew(get_next_line(fd));
		if (!tmp)
			break ;
		ft_lstadd_back(&config->file, tmp);
	}
	close(fd);
}

char	*ft_strim_path(char *path)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = 1;
	j = ft_strlen(path) - 1;
	tmp = path;
	while (path[i] && (path[i] == ' ' || path[i] == '\t'))
		i++;
	while (path[j] && (path[j] == ' ' || path[j] == '\t' || path[j] == '\n'))
		j--;
	k = 0;
	while (i <= j)
		tmp[k++] = path[i++];
	tmp[k] = '\0';
	return (tmp);
}

int	element_already_present(char *line, t_cubconfig *config)
{
	if (line[0] == 'N' && config->no == NULL)
		config->no = ft_strim_path(line);
	else if (line[0] == 'S' && config->so == NULL)
		config->so = ft_strim_path(line);
	else if (line[0] == 'W' && config->we == NULL)
		config->we = ft_strim_path(line);
	else if (line[0] == 'E' && config->ea == NULL)
		config->ea = ft_strim_path(line);
	else if (line[0] == 'F' && config->f == NULL)
		config->f = ft_strim_path(line);
	else if (line[0] == 'C' && config->c == NULL)
		config->c = ft_strim_path(line);
	else
	{
		prblem("Error!\nElement already present: ", line, "\n");
		return (1);
	}
	config->nb_element++;
	return (0);
}

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
	if ((line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E'
			|| line[0] == 'C' || line[0] == 'F') && (line[1] == ' '
			|| line[1] == '\t'))
	{
		tmp++;
		while (*tmp && (*tmp == ' ' || *tmp == '\t'))
			tmp++;
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W'
			|| line[0] == 'E')
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

int	is_start_map(char *line)
{
	if (*line == '\n')
		return (0);
	while (*line)
	{
		if (*line != '1' && *line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	find_size(t_list *start)
{
	int		size;

	size = 0;
	while (start)
	{
		start = start->next;
		size++;
	}
	return (size);
}

static int	have_right_wall(char **map, int i, int j)
{
	while (map[i][j] && map[i][j] != '\n')
	{
		if (map[i][j] == ' ')
			return (0);
		if (map[i][j] == '1')
			return (1);
		j++;
	}
	return (0);
}

static int	have_left_wall(char **map, int i, int j)
{
	while (j >= 0)
	{
		if (map[i][j] == ' ')
			return (0);
		if (map[i][j] == '1')
			return (1);
		j--;
	}
	return (0);
}

static int	have_top_wall(char **map, int i, int j)
{
	while (i >= 0)
	{
		if (map[i][j] == ' ' || map[i][j] == '\n')
			return (0);
		if (map[i][j] == '1')
			return (1);
		i--;
	}
	return (0);
}

static int	have_bottom_wall(char **map, int i, int j, int size)
{
	while (i < size)
	{
		if (map[i][j] == ' ' || map[i][j] == '\n')
			return (0);
		if (map[i][j] == '1')
			return (1);
		i++;
	}
	return (0);
}

int	is_surrounded_by_walls(char **map, int size, int i, int j) 
{
	if (have_right_wall(map, i, j) && have_left_wall(map, i, j)
		&& have_top_wall(map, i, j) && have_bottom_wall(map, i, j, size))
		return (1);
	return (0);
}

int	check_wall(char **map, int size)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				&& (!is_surrounded_by_walls(map, size, i, j)))
				return (prblem("Error!\nMap not closed or space in map\n", "", ""));
			j++;
		}
		i++;
	}
	return (0);
}

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
	return (check_wall(map, size));
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

int	switch_info_to_list(t_cubconfig *config)
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
int	check_cub_content(t_cubconfig *config)
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

void	clear_list_ptr(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

void	garbage_collector(t_cubconfig *config)
{
	// free mlx ila khdmna bih!
	if (config->file)
		clear_list_ptr(&config->file);
	free(config->map);
}

int	check_cubfile(char *gamefile, t_cubconfig *config)
{
	int	fd;

	fd = check_file_path(gamefile);
	if (fd == -1)
		return (1);
	readfile_to_list(fd, config);
	if (switch_info_to_list(config) == -1 || check_cub_content(config) == -1)
	{
		garbage_collector(config);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_cubconfig	config;

	if (env && !env[0])
		return (prblem("error!\n", "environement NULL", "    *__*\n"));
	init_gameconfig(&config);
	if (argc == 2 && argv[1] && argv[1][0] != '\0')
	{
		if (check_cubfile(argv[1], &config) != 0)
			return (1);
		printf("WORK!\n");
		// hna ghatbda lcode ! mlx dyalna ntl3o raycast dyalna
	}
	else
		ft_putstr_fd("Error!\nParameter not valid\n", 2);
	return (0);
}
