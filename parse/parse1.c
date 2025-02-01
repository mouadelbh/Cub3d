/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:51:05 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/01 22:17:59 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	readfile_to_list(int fd, t_mlx *config)
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

int	element_already_present(char *line, t_mlx *config)
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
