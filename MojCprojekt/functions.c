//File sa funkcijama koje se koriste i u meniu i u submeniu:

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"
#include <stdbool.h>


//Funkcija provjerava postoji li vec tim pod odredenim imenom u dokumentu:
bool teamExists(const char* const teamName) {
	FILE* file = fopen("teamsAndMembers.bin", "rb");
	if (file == NULL) {
		perror("Neuspjesno otvaranje dokumenta: ");
		return false;
	}

	TEAM tempTeam;

	while (fread(&tempTeam, sizeof(TEAM), 1, file) == 1) {
		if (strcmp(tempTeam.teamName, teamName) == 0) {
			fclose(file);
			return true;
		}
	}

	fclose(file);
	return false;
}

//Funkcija provjerava postoji li \n na kraju stringa i uklanja ga ako postoji:
void stringCheck(char* const string) {
	int n = strlen(string);
	if (string[n - 1] == '\n') {
		string[n - 1] = '\0';
	}
}



//Funkcija za unos opcije u određenom intervalu(ukljucuje  zastitu od unosa razmaka i slova):
int choice(const int ll, const int ul) {
	int opcija;
	char inputBuffer[MAX_STRING];

	do {
		printf("Unesite opciju: ");
		if (fgets(inputBuffer, sizeof(inputBuffer), stdin) != NULL) {
			stringCheck(inputBuffer);
			// Provjera ima li razmaka u inputu
			if (strchr(inputBuffer, ' ') != NULL) {
				printf("Pri unosu opcije nemojte koristit tipku za razmak!\n");
				continue;
			}

			// Konverzija stringa u integer
			char* endptr;
			opcija = strtol(inputBuffer, &endptr, 10);

			//Provjera je li konverzija uspješna
			if (*endptr != '\0') {
				printf("Neispravan unos. Molimo unesite broj.\n");
			}
			else if (opcija < ll || opcija > ul) {
				printf("Neispravan unos. Unesite broj izmedu %d i %d.\n", ll, ul);
			}
			else {
				return opcija;
			}
		}
		else {
			printf("Greska pri unosu.\n");
		}
	} while (1);

}

//int choice(int ll,int ul) {          STARA FUNKCIJA ZA UNOS!!  bez zastite za unos razmaka!
//	int opcija;
//	do {
//		printf("Unesite opciju: ");
//		if (scanf("%d", &opcija) != 1) {
//			printf("Neispravan unos. Molimo unesite broj.\n");
//
//			while (getchar() != '\n');
//		}
//		else if (opcija < ll || opcija > ul) {
//			printf("Neispravan unos. Unesite broj izmedu %d i %d.\n",ll,ul);
//		}
//	} while (opcija < ll || opcija > ul);
//
//	return opcija;
//}