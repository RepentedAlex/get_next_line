/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:02:06 by apetitco          #+#    #+#             */
/*   Updated: 2024/01/23 18:15:04 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*obtain_remaining(char *basin_buffer)
{
	char	*remaining;
	char	*start;
	int		i;
	int		len;

	if (!basin_buffer)
		return (NULL);
	if (basin_buffer[ft_strlen(basin_buffer) - 1] == '\n')
		return (NULL);
	start = ft_strchr(basin_buffer, '\n');
	start++;
	len = 0;
	while (start[len])
		len++;
	remaining = ft_calloc(len, sizeof(char));
	if (!remaining)
		return (NULL);
	i = 0;
	while (i <= len)
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

static char	*read_from_file(char *basin_buffer, int fd)
{
	int			bytes_read;
	char		*cup_buffer;

	cup_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!cup_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(cup_buffer), NULL);
		if (bytes_read == 0)
			return (free(cup_buffer), NULL);
		cup_buffer[bytes_read] = 0;
		basin_buffer = append_buffer(basin_buffer, cup_buffer);
		if (ft_strchr(basin_buffer, '\n'))
			break ;
	}
	free(cup_buffer);
	return (basin_buffer);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	static char	*basin_buffer = NULL;
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_strchr(basin_buffer, '\n'))
		basin_buffer = read_from_file(basin_buffer, fd);
	if (!basin_buffer)
		return (free(basin_buffer), NULL);
	line = extract_line(basin_buffer);
	tmp = obtain_remaining(basin_buffer);
	free(basin_buffer);
	basin_buffer = ft_strdup(tmp);
	free(tmp);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;
// 	int		count;

// 	count = 0;
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error opening file");
// 		return (1);
// 	}
// 	while (count < atoi(argv[2]))
// 	{
// 		line = get_next_line(fd);
// 		count++;
// 		printf("[%d]:%s\n", count, line);
// 		free(line);
// 		line = NULL;
// 	}

// 	close(fd);
// 	return (0);
// }

