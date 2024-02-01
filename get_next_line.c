/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:02:06 by apetitco          #+#    #+#             */
/*   Updated: 2024/02/01 22:01:44 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

static void	obtain_remaining(t_buffer *buf)
{
	char	*start;
	int		i;
	int		len;

	// if (!basin_buffer || basin_buffer[0] == 0 || basin_buffer[0] == '\n')
	// 	return (NULL);
	// if (basin_buffer[ft_strlen(basin_buffer) - 1] == '\n')
	// 	return (NULL);
	i = -1;
	len = 0;
	start = ft_strchr(buf->buf, '\n');
	if (!start || !(start + 1)|| !buf->buf)
		return ;
	start++;
	while (start[len])
		len++;
	while (++i < len)
		buf->buf[i] = start[i];
	buf->buf[i] = 0;
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

//strjoin + free and replace & buf->buf
static void	append_buffer(t_buffer *buf, char *cup_buffer)
{
	char	*tmp;

	tmp = ft_strjoin(buf->buf, cup_buffer);
	free(buf->buf);
	buf->buf = tmp;
}

static void	read_from_file(t_buffer *buf, int fd)
{
	int			bytes_read;
	char		cup_buffer[BUFFER_SIZE + 1];
	int	i;
	
	bytes_read = 1;
	while (!ft_strchr(buf->buf, '\n'))
	{
		i = 0;
		while (i < BUFFER_SIZE)
			cup_buffer[i++] = 0;
		bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return ;
		cup_buffer[bytes_read] = '\0';
		append_buffer(buf, cup_buffer);
		if (!buf->buf)
			return ;
		if (bytes_read == 0)
		{
			printf("OEF\n");
			buf->eof = true;
			break ;
		}
	}
}

bool get_buffer_for_fd(int fd, t_buffer *out, t_buffer *basin_buffer)
{
	int i;

	i = 0;
	while (i < NB_BUFFER) {
		if (basin_buffer[i].fd == fd || !basin_buffer[i].used)
		{
			basin_buffer[i].fd = fd;
			basin_buffer[i].used = true;
			*out = basin_buffer[i];
			return (true);
		}
		i++;
	}
	return (false);
}

char	*get_next_line(int fd)
{
	char				*line;
	static t_buffer 	buf1 = {};
	//t_buffer			basin_buffer[NB_BUFFER] = {};

	if (fd < 0 || BUFFER_SIZE <= 0/* || !get_buffer_for_fd(fd, &buf1, basin_buffer)*/)
		return (NULL);
	if (!ft_strchr(buf1.buf, '\n'))
		read_from_file(&buf1, fd);
	if (!buf1.buf)
		return (NULL);
	line = extract_line(buf1.buf);
	if (!line && !buf1.eof)
		return (NULL);
	printf("OEF=%i\n", buf1.eof);
	if (buf1.eof)
	{
		printf("FREE\n");
		free(buf1.buf);
		buf1.buf = NULL;
		return (NULL);
	}
	obtain_remaining(&buf1);
	if (!buf1.buf)
		return (free(line), NULL);

	return (line);
}

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;

	fd1 = open("example.txt", O_RDONLY);
	// fd1 = 0;
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
		if (line)
			free(line);
		line = NULL;
		i++;
	}
	close(fd1);
	return (0);
}
