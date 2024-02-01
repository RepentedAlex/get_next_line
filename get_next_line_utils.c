/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:04:57 by apetitco          #+#    #+#             */
/*   Updated: 2024/02/01 20:50:11 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

char	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (size > __SIZE_MAX__ / nmemb)
		return (NULL);
	ptr = NULL;
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s || !c)
		return (NULL);
	i = 0;
	while (s[i] != (unsigned char)c)
	{
		if (s[i] == 0)
			return ((char *)0);
		i++;
	}
	return ((char *)&s[i]);
}

char	*ft_strdup(const char *s1)
{
	char	*new;
	size_t	i;

	if (!s1)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1)
	{
		new = ft_strdup(s2);
		if (!new)
			return (NULL);
		return (new);
	}
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)+ 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = 0;
	return (new);
}
