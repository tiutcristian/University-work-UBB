#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
	Să se citească un număr N de la tastatură, apoi N texte de maxim 20 de litere. Să se afișeze textele ordonate alfabetic.
sugestii: char**, malloc(), gets()
*/

void sortare (int n, char **a)
{
	for (int i = 0; i < n-1; i++)
		for (int j = i+1; j < n; j++)
			if (strcmp(a[i], a[j]) > 0)	{
				char *aux = a[i];
				a[i] = a[j];
				a[j] = aux;
			}
}

int main ()
{
	char **lista;
	int n;

	printf("Enter number: ");
	scanf("%d", &n);

	lista = (char**)malloc(n * sizeof(char*));	
	for(int i = 0; i < n; i++)
	{
        	lista[i] = (char*)malloc(21 * sizeof(char));
		printf("Enter text %d: ", i+1);
	        scanf("%s", lista[i]);
	}

	// do some sorting (but not std::sorting)
	sortare(n, lista);

	for (int i = 0; i < n; i++)
		printf("%s\n", lista[i]);

	// freeing stuff
	for (int i = 0; i < n; i++)
	{
        	free(lista[i]);
	}
	free(lista);

}

