#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// permet de récupérer le chemin du répertoire de travail courant
// (getcwd = get current working directory)

#define BUFFER_SIZE 256

int	main(void)
{
	char buffer[BUFFER_SIZE];

	if (getcwd(buffer, BUFFER_SIZE) == NULL)
	{
		fprintf(stderr, "Cannot get current working directory path\n");
		if (errno == ERANGE)
		{
			fprintf(stderr, "Buffer size is too small.\n");
		}
		exit(EXIT_FAILURE);
	}

	printf("Current working directory: \n%s\n", buffer);

	return (EXIT_SUCCESS);
}