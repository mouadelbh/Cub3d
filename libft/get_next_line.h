/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebaai <asebaai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:22:10 by asebaai           #+#    #+#             */
/*   Updated: 2025/02/25 18:07:19 by asebaai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strndup(char *s, size_t n);
char	*ft_strjoin1(char *s1, char *s2);
char	*handle_prev_line(char *prev_line, char *buff);
char	*read_and_join(int fd, char *prev_line, char *buff);
char	*read_line(int fd, char *prev_line);

#endif
