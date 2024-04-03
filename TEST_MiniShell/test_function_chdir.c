#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> // mkdir
#include <unistd.h>   // chdir

// permet de changer le répertoire courant de travail

#define PATH "TEST"

int	main(void)
{
	if (mkdir(PATH, 0777) != 0) // cree 1 dossier test
	{
		fprintf(stderr, "Impossible de créer le dossier %s.\n", PATH);
		exit(EXIT_FAILURE);
	}

	if (chdir(PATH) != 0) // on va dans dossier test
	{
		fprintf(stderr, "Impossible de se placer dans le dossier %s.\n", PATH);
		exit(EXIT_FAILURE);
	}

	FILE *file = fopen("essai.txt", "w"); // on cree 1 fichier dans le dossier
	if (file == NULL)
	{
		fprintf(stderr, "Impossible d'ouvrir le fichier en écriture.\n");
		exit(EXIT_FAILURE);
	}

	fprintf(file, "Ok"); // on ecrit dans le fichier cree
	fclose(file);

	return (EXIT_SUCCESS);
}