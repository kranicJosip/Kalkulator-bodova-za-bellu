#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

TEAM* firstTeam = NULL;
TEAM* secondTeam = NULL;
int gameMode;
int subMenu(int status) {
	int option = subMenuOptionPrompt();

	switch (option) {
	case CHOOSE_EXISTING_TEAMS:
		
		firstTeam = choosingTeams();
		if (firstTeam == NULL) {
			printf("Nije pronaden tim pod tim imenom! \n");
			system("pause");
			break;
		}
		secondTeam = choosingTeams();
		if (secondTeam == NULL) {
			printf("Nije pronaden tim pod tim imenom! \n");
			system("pause");
			break;
		}
		gameMode = playingOptions();
		playing(firstTeam, secondTeam, gameMode);
		break;
	case INPUTING_NEW_TEAMS:
		if (inputingNewTeams(&firstTeam, &secondTeam)) {
			return status;
		}
		gameMode = playingOptions();
		playing(firstTeam, secondTeam, gameMode);
		free(firstTeam); free(secondTeam);
		firstTeam = NULL; secondTeam = NULL;
		break;
	case BACK_TO_MENU:
		status = 0;
		return status;
		break;
	default:
		break;
	}
	return status;
}
