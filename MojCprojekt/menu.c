#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"

int menu(int status) {
	
	int option1 = optionPrompt();

	int submenu = 0;

	switch (option1)
	{
	case INPUTING_PLAYERS:
		inputingPlayers();
		
		break;
	case READING_TEAMS:
		readingTeams();
		break;
	case START_GAME:
		status = 1;
		while (status) {
			system("cls");
			status = subMenu(status);
		}
		status = 10;
		break;
	case DELETE_TEAM:
		deleteTeam();
		break;
	case EXIT_PROGRAM:
		status = 0;
		break;
	default:
		break;
	}
	system("pause");
	return status;
}

int optionPrompt() {

	int opcija;

	printf("\t\t-----------Odaberite jednu od sljedecih opcija ------------\n");
	printf("\t\t-----------Upisivanje novih igraca i timova: 1 <-----------\n");
	printf("\t\t-----------Ispisivanje svih upisanih timova: 2 <-----------\n");
	printf("\t\t-----------Zapocni igru:                     3 <-----------\n");
	printf("\t\t-----------Izbrisi tim iz baze podataka:     4 <-----------\n");
	printf("\t\t-----------Izlaz iz programa:                5 <-----------\n");
	
	opcija = choice(1, 5);

	return opcija;

}