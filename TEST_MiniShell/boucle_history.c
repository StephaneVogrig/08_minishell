#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char	*inpt;
	int		i;

	i = 0;
	while (i < 10)
	{
		inpt = readline("Enter text: ");
		add_history(inpt);
		printf("%s", inpt);
		printf("\n");
		++i;
	}
	return (0);
}
