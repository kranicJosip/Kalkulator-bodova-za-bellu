#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"

TEAM* firstTeam = NULL;
TEAM* secondTeam = NULL;
int gameMode;
int subMenu(int status) {
	int option = subMenuOptionPrompt();
	switch (option){
	case 1:
		getchar();
		firstTeam = choosingTeams();
		if (firstTeam == NULL) {
			printf("Nije pronaden tim pod tim imenom! \n");
			break;
		}
		secondTeam = choosingTeams();
		if (secondTeam == NULL) {
			printf("Nije pronaden tim pod tim imenom! \n");
			break;
		}
		gameMode = playingOptions();
		playing(firstTeam, secondTeam,gameMode);
		break;
	case 2:
		inputingNewTeams(&firstTeam, &secondTeam);
		gameMode = playingOptions();
		playing(firstTeam, secondTeam, gameMode);
	case 3:
		status = 0;
		break;
	default:
		break;
	}
	return status;
}


int subMenuOptionPrompt() {
	int opcija;
	printf("\t\t-----------Odaberite jednu od sljedecih opcija ------------\n");
	printf("\t\t-----------Odaberite dva vec postojeca tima: 1 <-----------\n");
	printf("\t\t-----------Unesite nove timove za igru:      2 <-----------\n");
	printf("\t\t-----------Vrati se u meni:                  3 <-----------\n");
	do {
		printf("Unesite opciju: ");
		if (scanf("%d", &opcija) != 1) { 
			printf("Neispravan unos. Molimo unesite broj.\n");
			
			while (getchar() != '\n');
		}
		else if (opcija < 1 || opcija > 3) {  
			printf("Neispravan unos. Unesite broj izmedu 1 i 3.\n");
		}
	} while (opcija < 1 || opcija > 3);

	return opcija;
}