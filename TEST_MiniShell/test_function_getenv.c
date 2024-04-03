#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	char	*path;

	if (argc > 1)
	{
		path = getenv(argv[1]);
		printf("%s -> %s\n", argv[1], path);
	}
	return (0);
}

// int	main(void)
// {
// 	char *path = getenv("PATH");
// 	printf("\nPATH -> %s\n", path);

// 	char *noexist = getenv("NOEXIST");
// 	printf("\nNOEXIST -> %s\n", noexist);

// 	char *user = getenv("USER");
// 	printf("\nUSER -> %s\n", user);

// 	return (0);
// }