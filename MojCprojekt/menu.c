#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"

int menu(int status) {

	int option1 = optionPrompt();

	int submenu = 0;

	switch (option1)
	{
	case INPUTING_TEAMS:
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
	case PRINT_SORTED:
		printingSortedTeams();
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

