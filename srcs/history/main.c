#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int nread;
	int i;
	char entry[11];

	i = 0;
	nread = read(0, entry, 11);
	printf("READ=%i\n", nread);
	while (i < nread)
		printf("%hhi\n", entry[i++]);
	printf("fin\n\n");
	return (0);
}
