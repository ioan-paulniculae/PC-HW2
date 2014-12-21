/* Programarea Calculatoarelor, seria CC
 * Tema2 - Snake
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT	10
#define MAX	50

/* Revizitați problema 1 din laboratorul 2.
 * http://elf.cs.pub.ro/programare/problema/lab-02-01
 */

int main(void)
{
	int random_number, i;

	/* Dacă veți comenta linia cu srand, veți observa
	 * că fiecare rulare produce aceleași COUNT numere
	 * Sunteți încurajați să încercați :)
	 */
	srand(time(NULL));

	printf("Vom afisa %d numere aleatoare intre 0 si %d\n", COUNT, MAX - 1);		
	for (i = 0; i < COUNT; i++) {
		random_number = rand() % MAX;
		printf("%d\n", random_number);
	}
			
	return 0;
}
