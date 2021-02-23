#include "parser.h"

char			*remove_comma(char *data)
{
	while (*data == ',')
		data++;
	return (data);
}

void			ft_bzero(void *s, size_t n)
{
	char *s1;

	s1 = s;
	while (n--)
		*(s1++) = '\0';
}

void			*ft_calloc(size_t count, size_t size)
{
	char *s;

	if (!(s = malloc(count * size)))
		return (NULL);
	ft_bzero(s, count * size);
	return (s);
}

char			*remove_num(char *data)
{
	while (*data >= '0' && *data <= '9')
		data++;
	return (data);
}

char			*remove_space(char *data)
{
	while (*data == ' ')
		data++;
	if (*data == ' ')
		data++;
	return (data);
}
