/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnymella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:01:55 by lnymella          #+#    #+#             */
/*   Updated: 2020/12/09 15:08:18 by lnymella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t		i;
	char		*s1;

	s1 = (char *)s;
	i = 0;
	while (s1[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s)
{
	while (*s != '\n' && *s)
		s++;
	if (*s == '\n')
		return (s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2, int j)
{
	size_t	i;
	char	*str;
	size_t	l1;

	s2[j] = '\0';
	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	if (!(str = (char*)malloc(sizeof(char) * (l1 + ft_strlen(s2) + 1))))
		return (str);
	i = 0;
	while (i < l1)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		str[l1 + i] = s2[i];
		++i;
	}
	str[l1 + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}

char	*ft_strdup_n(char *src, char *s)
{
	char	*dst;
	int		i;

	i = 0;
	if (!(dst = malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (NULL);
	while (src[i] != '\0' && src[i] != '\n')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	free(s);
	return (dst);
}

char	*ft_strdup_after_n(char *src, int *flag)
{
	char	*dst;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(dst = malloc(sizeof(char) * ft_strlen(src) + 1)))
		return (NULL);
	while (src[i] != '\n')
		if (src[i++] == '\0')
		{
			*flag = 0;
			free(src);
			free(dst);
			dst = NULL;
			return (dst);
		}
	i++;
	while (src[i] != '\0')
		dst[j++] = src[i++];
	dst[j] = '\0';
	free(src);
	return (dst);
}
