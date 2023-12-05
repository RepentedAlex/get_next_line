/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:54:35 by apetitco          #+#    #+#             */
/*   Updated: 2023/12/05 19:10:10 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cat_str;
	int		cat_len;
	int		i;
	int		j;

	i = 0;
	cat_len = ft_strlen(s1) + ft_strlen(s2);
	cat_str = malloc((cat_len + 1) * sizeof(char));
	if (!cat_len || !s1 || !s2)
		return (NULL);
	while (s1[i] != 0)
	{
		cat_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		cat_str[i] = s2[j];
		i++;
		j++;
	}
	cat_str[cat_len] = 0;
	return (cat_str);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != (unsigned char)c)
	{
		if (s[i] == 0)
			return ((char *)0);
		i++;
	}
	return ((char *)&s[i]);
}

void	ft_bzero(void *s, size_t n)
{
	char	*p;
	size_t	i;

	p = (char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*pointer;

	pointer = malloc(nmemb * size);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, nmemb * size);
	return (pointer);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
