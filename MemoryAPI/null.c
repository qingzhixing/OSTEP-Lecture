#include <stdlib.h>
int main()
{
	int *ptr = NULL;
	free(ptr);
	return 0;
}