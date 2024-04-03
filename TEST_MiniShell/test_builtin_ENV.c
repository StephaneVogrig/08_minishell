#include <stdio.h>
#include <stdlib.h>

char	*ft_strndup(const char *s, int lenght)
{
	unsigned int	i;
	char			*dup;

	i = 0;
	dup = (char *)malloc(sizeof(char) * (lenght + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i <= lenght)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strchr_i(char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i - 1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*path;
	int		i;
	int		count;
	char	*chm;

	count = 0;
	i = 0;
	if (argc > 0)
	{
		while (env[i])
		{
			count = ft_strchr_i(env[i], '=');
			// printf("\ncount = %d \n", count);
			path = ft_strndup(env[i], count);
			printf("%s=", path);
			chm = getenv(path);
			printf("%s\n", chm);
			free(path);
			i++;
		}
	}
	return (0);
}
