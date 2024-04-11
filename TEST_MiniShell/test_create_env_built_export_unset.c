#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_strchr_next(const char *s, int c)
{
	unsigned int	i;
	const char		*r;

	r = s;
	i = 0;
	while (i < ft_strlen(s))
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			r = &s[i + 1];
			return ((char *)r);
		}
		i++;
	}
	if (c == '\0')
	{
		r = &s[i];
		return ((char *)r);
	}
	return (NULL);
}

char	*ft_strndup(const char *s, int lenght)
{
	int		i;
	char	*dup;

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

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	char			*tab;
	int				k;

	if (!s2)
		return (NULL);
	tab = NULL;
	if (s1 == 0)
		return (malloc(0));
	tab = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!tab)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		tab[k++] = s1[i++];
	}
	i = 0;
	while (s2[i] != '\0')
	{
		tab[k++] = s2[i++];
	}
	tab[k] = '\0';
	return (tab);
}

char	*ft_strdup(const char *s)
{
	unsigned int	i;
	int				lenght;
	char			*dup;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		i++;
	}
	lenght = i;
	dup = (char *)malloc(sizeof(char) * (lenght + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
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

void	diplay_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("str[%d] = %s \n", i, str[i]);
		i++;
	}
}

void	builtin_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		write(1, "=", 1);
		i++;
		ft_putstr_fd(str[i], 1);
		write(1, "\n", 2);
		i++;
	}
}

void	builtin_unset(char **str, char *to_remove)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], to_remove, ft_strlen(to_remove)) == 0)
		{
			while (str[i + 2])
			{
				free(str[i]);
				free(str[i + 1]);
				str[i] = ft_strdup(str[i + 2]);
				str[i + 1] = ft_strdup(str[i + 3]);
				i++;
				i++;
			}
			free(str[i]);
			str[i] = NULL;
			free(str[i + 1]);
			str[i + 1] = NULL;
			return ;
		}
		i++;
	}
}

int	tab_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	// printf("i = %d \n", i);
	return (i);
}

void	free_the_tab(char **str)
{
	int	i;

	i = 0;
	while (i < tab_size(str)) // (str[i])//
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**copy_tab(char **to_copy, char **dest, int len_to_cpy)
{
	int	i;

	i = 0;
	free_the_tab(dest);
	dest = (char **)malloc(sizeof(char *) * (len_to_cpy));
	while (to_copy[i])
	{
		dest[i] = ft_strdup(to_copy[i]);
		i++;
	}
	free_the_tab(to_copy);
	dest[i] = NULL;
	return (dest);
}

char	**add_to_tab(char **str, char *to_add)
{
	char	**temp;
	int		lenght;
	int		i;
	int		count;

	i = 0;
	lenght = tab_size(str);
	temp = (char **)malloc(sizeof(char *) * ((lenght + 1)));
	while (str[i])
	{
		temp[i] = ft_strdup(str[i]);
		i++;
	}
	temp[i] = ft_strndup(to_add, ft_len(to_add));
	temp[i + 1] = NULL;
	return (copy_tab(temp, str, lenght + 2));
}

char	**builtin_export(char **str, char *to_add)
{
	// int i = 0;
	if (ft_strchr(to_add, '=') == NULL)
		return (str);
	// while(str[i])
	{
		//	printf("ft_strncmp = %d\n", ft_strncmp(str[i], to_add,
		//			ft_strlen(str[i])));
		//	printf("str[i] = %s\n", str[i]);
		// if(ft_strncmp(str[i], to_add, ft_strlen(str[i])) == 0)
		// existe deja dans env
		// {
		// 	printf("-------------------------existe deja\n");
		// 		printf("str[i] = %s\n", str[i]);
		// int j = 0;
		// while(to_add[j])
		// {
		// 	if(to_add[j] == '=' && to_add[j + 1] != '\0' )
		// 	{
		// 	//	free(str[i + 1]);
		// 		printf("= to_replace \n");
		// 		str[i + 1] = ft_strdup(&to_add[j]);
		// 		return (str);
		// 	}
		// 	else if(to_add[j] == '+' && to_add[j + 1] == '='
		//		&& to_add[j+ 2] != '\0' )
		// 	{
		// 	//	free(str[i + 1]);
		// 		printf("+= to add \n");
		// 		str[i + 1] = ft_strdup(&to_add[j]);
		// 				return (str);
		// 			}
		// 			else if (to_add[j] == '=' && to_add[j + 1] == '\0')
		// 				return (str);
		// 			j++;
		// 		}
		// 		//attention si NEW=to_add alors on remplace
		// 		//attention si NEW+=to_add alors on ajoute !
		// 		//attention si NEW= seul on ne fait rien
		// 		//attention si NEW+++=to_add alors "bash: export: `to_add': not a valid identifier"
		// 		return (str);
	}
	// 	if(ft_strncmp(str[i], to_add, ft_strlen(str[i])) != 0)
	// 	{
	// 			i++;
	// 			i++;
	//		}
	// 	}
	return (add_to_tab(str, to_add));
}

int	main(int argc, char **argv, char **env)
{
	char	**env_cpy;
	int		i;
	int		count;
	int		len;
	char	buff[100];

	(void)argc;
	(void)argv;
	len = 0;
	if (!env[0])
	{
		env_cpy = (char **)malloc(sizeof(char) * (3 + 1));
		getcwd(buff, 100);
		env_cpy[0] = ft_strdup(buff); // PWD
		env_cpy[1] = NULL;            // SHLVL
		env_cpy[2] = NULL;            // _
		env_cpy[3] = NULL;
	}
	else
	{
		len = tab_size(env);
		env_cpy = (char **)malloc(sizeof(char *) * ((len) + 1));
		// attention c'est 1 tab de tab !
		i = 0;
		while (env[i])
		{
			env_cpy[i] = ft_strndup(env[i], ft_strdup(env[i],
						ft_strlen(env[i])));
			i++;
		}
		env_cpy[i] = NULL;
	}
	printf("builtin ------ ENV ---------\n");
	builtin_env(env_cpy);
	// if(argc == 2)
	// {
	// 	printf("\nbuiltin ----------- UNSET ---------\n");
	// 	builtin_unset(env_cpy, argv[1]);
	// 	builtin_env(env_cpy);
	// }
	if (argc == 2)
	{
		printf("builtin EXPORT---------\n");
		env_cpy = builtin_export(env_cpy, argv[1]);
		builtin_env(env_cpy);
	}
	free_the_tab(env_cpy);
	return (0);
}
