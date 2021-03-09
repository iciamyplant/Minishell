#include "libft.h"

char	*ft_strcat(char *s1, char *s2)
{
	char	*s;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	if (!(s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (*s1)
		s[i++] = *s1++;
	while (*s2)
		s[i++] = *s2++;
	s[i] = '\0';
	return (s);
}
