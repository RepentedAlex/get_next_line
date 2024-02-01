/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:10:45 by apetitco          #+#    #+#             */
/*   Updated: 2024/02/01 21:36:44 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# ifndef NB_BUFFER
#  define NB_BUFFER 512
# endif

typedef struct  s_buffer
{
                char *buf;
                bool eof;
                int fd;
                bool used;
}               t_buffer;

char	*extract_line(char *basin_buffer);
void	ft_bzero(void *s, size_t n);
char	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);
// char	*append_buffer(char *basin_buffer, char *cup_buffer);
//static char	*obtain_remaining(t_buffer *buf1);
//static char	*read_from_file(char *basin_buffer, int fd);

#endif
