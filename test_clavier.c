#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char buff[4];
	char	c;
	int		size = 0;

	c = '\0';
	while (1)
	{
		size = read(0, buff, 1);
		// printf("ok\n");
		write(2, "ok\n", 3);

	}
	return (0);
}

