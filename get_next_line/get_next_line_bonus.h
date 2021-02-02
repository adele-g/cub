/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnymella <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:31:54 by lnymella          #+#    #+#             */
/*   Updated: 2020/12/07 17:32:33 by lnymella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# define BUFFER_SIZE 100

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
char	*ft_strnew(size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strchr(char *s);
char	*ft_strjoin(char *s1, char *s2, int j);
char	*ft_strdup_n(char *src, char *s);
char	*ft_strdup_after_n(char *src, int *flag);

#endif
