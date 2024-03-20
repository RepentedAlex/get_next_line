/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:46:36 by apetitco          #+#    #+#             */
/*   Updated: 2024/03/20 16:46:39 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

//strjoin + free and replace & buf->buf
static char	*append_buffer(char *basin, char *cup)
{
	char	*tmp;

	tmp = ft_strjoin(basin, cup);
	free(basin);
	return (tmp);
}

static char	*obtain_remaining(char *basin)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (basin[i] && basin[i] != '\n')
		i++;
	if (!basin[i])
	{
		free(basin);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(basin) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (basin[i])
		line[j++] = basin[i++];
	free(basin);
	return (line);
}

static char	*extract_line(char *basin)
{
	char	*line;
	int		i;

	i = 0;
	if (!basin[i])
		return (NULL);
	while (basin[i] && basin[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (basin[i] && basin[i] != '\n')
	{
		line[i] = basin[i];
		i++;
	}
	if (basin[i] && basin[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*read_from_file(int fd, char *basin)
{
	char	*cup;
	int		byte_read;

	if (!basin)
		basin = ft_calloc(1, 1);
	cup = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, cup, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(cup);
			return (NULL);
		}
		cup[byte_read] = 0;
		basin = append_buffer(basin, cup);
		if (ft_strchr(cup, '\n'))
			break ;
	}
	free(cup);
	return (basin);
}

char	*get_next_line(int fd)
{
	static char	*basin[NB_BUFFER];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	basin[fd] = read_from_file(fd, basin[fd]);
	if (!basin[fd])
		return (NULL);
	line = extract_line(basin[fd]);
	basin[fd] = obtain_remaining(basin[fd]);
	return (line);
}

/*
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
    int     fd2;
    int     fd3;

	fd1 = open("example1.txt", O_RDONLY);
	// fd1 = 0;
	if (fd1 == -1)
	{
		perror("Error opening file :");
		return (1);
	}
    fd2 = open("example2.txt", O_RDONLY);
	// fd1 = 0;
	if (fd2 == -1)
	{
		perror("Error opening file :");
		return (1);
	}
    fd3 = open("example3.txt", O_RDONLY);
	// fd1 = 0;
	if (fd3 == -1)
	{
		perror("Error opening file :");
		return (1);
	}
	i = 0;
	while (i < 4)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s\n", i, line);
		if (line)
			free(line);
		line = NULL;
        line = get_next_line(fd2);
		printf("line [%02d]: %s\n", i, line);
		if (line)
			free(line);
		line = NULL;
        line = get_next_line(fd3);
		printf("line [%02d]: %s\n", i, line);
		if (line)
			free(line);
		line = NULL;
		i++;
	}
	close(fd1);
    close(fd2);
    close(fd3);
	return (0);
}
*/
