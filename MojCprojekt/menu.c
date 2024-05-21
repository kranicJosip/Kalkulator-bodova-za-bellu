#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"

int menu(int status) {

	int option = optionPrompt();
	int submenu = 0;

	switch (option)
	{
	case 1:
		inputingPlayers();
		
		break;
	case 2:
		readingTeams();
		break;
	case 3:
		status = 1;
		while (status) {
			system("cls");
			status = subMenu(status);
		}
		status = 10;
		break;
	case 4:
		deleteTeam();
		break;
	case 5:
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
	printf("\t\t-----------Ispisivanje svih upianih timova:  2 <-----------\n");
	printf("\t\t-----------Zapocni igru:                     3 <-----------\n");
	printf("\t\t-----------Izbrisi tim iz baze podataka:     4 <-----------\n");
	printf("\t\t-----------Izlaz iz programa:                5 <-----------\n");
	
	opcija = choice(1, 5);

	return opcija;

}