/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuliro- <lhuliro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:18:18 by lhuliro-          #+#    #+#             */
/*   Updated: 2023/04/17 23:36:39 by lhuliro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_file(int fd, char *buffer)
{
	int		read_size;
	char	*tmp;

	tmp = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (free(buffer), NULL);
	read_size = read(fd, tmp, BUFFER_SIZE);
	if (read_size == -1)
		return (free(tmp), free(buffer), NULL);
	while (read_size > 0)
	{
		buffer = ft_strjoin(buffer, tmp, read_size);
		if (buffer && ft_strchr(buffer, '\n'))
			break ;
		read_size = read(fd, tmp, BUFFER_SIZE);
		if (read_size == -1)
			return (free(tmp), tmp = NULL, free(buffer), NULL);
	}
	free(tmp);
	tmp = NULL;
	return (buffer);
}

static char	*ft_extract_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] != '\n')
	{
		line = (char *) malloc(sizeof(char) * (i + 1));
		ft_strlcpy(line, buffer, i + 1);
	}
	else
	{
		line = (char *) malloc(sizeof(char) * (i + 2));
		ft_strlcpy(line, buffer, i + 2);
	}
	return (line);
}

static char	*adjust_buffer(char *buffer, int len_line)
{
	char	*new_buffer;
	int		j;

	new_buffer = (char *) malloc((ft_strlen(buffer) - len_line + 1));
	if (!new_buffer)
		return (free(buffer), free(new_buffer), NULL);
	j = 0;
	while (buffer[len_line + j])
	{
		new_buffer[j] = buffer[len_line + j];
		j++;
	}
	new_buffer[j] = 0;
	if (new_buffer[0] == 0)
		return (free(buffer), free(new_buffer), NULL);
	return (free(buffer), new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_extract_line(buffer[fd]);
	buffer[fd] = adjust_buffer(buffer[fd], ft_strlen(line));
	return (line);
}
