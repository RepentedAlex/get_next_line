/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:02:06 by apetitco          #+#    #+#             */
/*   Updated: 2024/01/29 16:56:55 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

char	*obtain_remaining(char *basin_buffer)
{
	char	*remaining;
	char	*start;
	int		i;
	int		len;

	if (!basin_buffer || basin_buffer[0] == 0/*|| basin_buffer[0] == '\n'*/)
		return (NULL);
	/*
	if (basin_buffer[ft_strlen(basin_buffer) - 1] == '\n')
		return (NULL);
	*/
	start = ft_strchr(basin_buffer, '\n');
	if (!start)
		return (NULL);
	start++;
	len = 0;
	while (start[len])
		len++;
	remaining = ft_calloc(len + 1, sizeof(char));
	if (!remaining)
		return (NULL);
	i = 0;
	while (i < len)
	{
		remaining[i] = start[i];
		i++;
	}
	remaining[i] = 0;
	return (remaining);
}

char	*extract_line(char *basin_buffer)
{
	char	*line;
	size_t	len;
	size_t	i;

	if (!basin_buffer || basin_buffer[0] == 0)
		return (NULL);
	len = 0;
	while (basin_buffer[len] && basin_buffer[len] != '\n')
		len++;
	line = ft_calloc(len + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		line[i] = basin_buffer[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*append_buffer(char *basin_buffer, char *cup_buffer)
{
	char	*tmp;

	tmp = ft_strjoin(basin_buffer, cup_buffer);
	free(basin_buffer);
	return (tmp);
}

static char	*read_from_file(t_buffer *buf, int fd)
{
	int			bytes_read;
	char		*cup_buffer;
	char 		**basin_buffer;
	
	basin_buffer = &buf->buf;
	cup_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!cup_buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(*basin_buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(cup_buffer), NULL);
		cup_buffer[bytes_read] = '\0';
		*basin_buffer = append_buffer(*basin_buffer, cup_buffer);
		if (bytes_read < BUFFER_SIZE)
			buf->eof = true;
	}
	free(cup_buffer);
	return (*basin_buffer);
}

bool get_buffer_for_fd(int fd, t_buffer **out) {
	static t_buffer	basin_buffer[NB_BUFFER] = {};
	int i;

	i = 0;
	while (i < NB_BUFFER) {
		if (basin_buffer[i].fd == fd || !basin_buffer[i].used) {
			basin_buffer[i].fd = fd;
			basin_buffer[i].used = true;
			*out = &basin_buffer[i];
			return (true);
		}
		i++;
	}
	return (false);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	char		*line;
	t_buffer 	*buf1;

	if (fd < 0 || BUFFER_SIZE <= 0 || !get_buffer_for_fd(fd, &buf1) || buf1->eof)
		return (NULL);
	if (!ft_strchr(buf1->buf, '\n'))
		read_from_file(buf1, fd);
	if (!buf1->buf)
		return (NULL);
	line = extract_line(buf1->buf);
	tmp = obtain_remaining(buf1->buf);
	free(buf1->buf);
	buf1->buf = ft_strdup(tmp);
	if (buf1->eof && ft_strlen(tmp) == 0)
		free(buf1->buf);
	free(tmp);
	return (line);
}


int	main(void)
{
	char	*line;
	int		i;
	int		fd1;

	fd1 = open("example.txt", O_RDONLY);
	if (fd1 == -1)
	{
		perror("Error opening file :");
		return (1);
	}
	i = 1;
	while (i < 10)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}

