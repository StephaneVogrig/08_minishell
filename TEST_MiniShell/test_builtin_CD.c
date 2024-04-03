#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // chdir

// #include <errno.h>
// #include <limits.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// char lastdir[_POSIX_PATH_MAX]; // initialized to zero

// int	exec_cd(char *arg)
// {
// 	char	curdir[_POSIX_PATH_MAX];
// 	char	path[_POSIX_PATH_MAX];

// 	if (getcwd(curdir, sizeof curdir))
// 	{
// 		/* current directory might be unreachable: not an error */
// 		*curdir = '\0';
// 	}
// 	if (arg == NULL)
// 	{
// 		arg = getenv("HOME");
// 	}
// 	if (!strcmp(arg, "-"))
// 	{
// 		if (*lastdir == '\0')
// 		{
// 			fprintf(stderr, "no previous directory\n");
// 			return (1);
// 		}
// 		arg = lastdir;
// 	}
// 	else
// 	{
// 		/* this should be done on all words during the parse phase */
// 		if (*arg == '~')
// 		{
// 			if (arg[1] == '/' || arg[1] == '\0')
// 			{
// 				snprintf(path, sizeof path, "%s%s", getenv("HOME"), arg + 1);
// 				arg = path;
// 			}
// 			else
// 			{
// 				/* ~name should expand to the home directory of user with login `name`
// 					this can be implemented with getpwent() */
// 				fprintf(stderr, "syntax not supported: %s\n", arg);
// 				return (1);
// 			}
// 		}
// 	}
// 	if (chdir(arg))
// 	{
// 		fprintf(stderr, "chdir: %s: %s\n", strerror(errno), path);
// 		return (1);
// 	}
// 	strcpy(lastdir, curdir);
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	char *path;

// 	if (argc > 1)
// 	{
// 		exec_cd(argv[1]);
// 	}
// 	return (0);
// }

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
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

int	main(int argc, char **argv)
{
	char	buff[100];
	int		ret;
	char	*old_dir;
	char	*cur_dir;

	ret = 0;
	getcwd(buff, 100); // on recupere ancien chemin
	old_dir = ft_strdup(buff);
	if (argc == 1) // si cd seul -> on va dans la maison
		argv[1] = getenv("HOME");
	else if (argv[1][0] == '\0')
		exit(0);
	else if ((argv[1][0] == '~' && !argv[1][1]))
		argv[1] = getenv("HOME"); // si cd ~ -> on va dans la maison
	else if (argv[1][0] == '~' && argv[1][1])
		argv[1] = ft_strjoin(argv[1] + 1, getenv("HOME"));
	ret = chdir(argv[1]); // on bouge dans le nouveau chemin
	if (ret == -1)
	{
		perror("");
		exit(1);
	}
	getcwd(buff, 100);
	cur_dir = ft_strdup(buff); // on recupere le nouveau chemin
	printf("Working in directory: %s\n", cur_dir);
	free(old_dir);
	free(cur_dir);
	return (0);
}
