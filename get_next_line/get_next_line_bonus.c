/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnymella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 13:41:27 by lnymella          #+#    #+#             */
/*   Updated: 2020/12/07 17:31:10 by lnymella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	str = NULL;
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
}

int		get_next_line(int fd, char **line)
{
	static char		*ost[256];
	char			*buf;
	int				i;

	if (!(buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))) ||
			(!line || fd < 0 || BUFFER_SIZE <= 0))
	{
		free(buf);
		return (-1);
	}
	if (!ost[fd])
		ost[fd] = ft_strnew(1);
	i = 1;
	while (!ft_strchr(ost[fd]) && i)
	{
		if (((i = read(fd, buf, BUFFER_SIZE)) == -1))
		{
			free(buf);
			return (-1);
		}
		ost[fd] = ft_strjoin(ost[fd], buf, i);
	}
	*line = ft_strdup_n(ost[fd], buf);
	ost[fd] = ft_strdup_after_n(ost[fd], &i);
	return (!i ? 0 : 1);
}
