#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"
const char splitter[50] = { "------------------------------------------------" };

void inputingPlayers(Team1* first, Team2* second) {
	puts(splitter);
	printf("Enter name of first team:  ");
	fgets(first->team1Name, 49, stdin);				stringCheck(first->team1Name);
	printf("Enter name of first player on  team: ");
	fgets(first->player1Name, 49, stdin);			stringCheck(first->player1Name);
	printf("Enter name of second player on team: ");
	fgets(first->player2Name, 49, stdin);			stringCheck(first->player2Name);
	puts(splitter);
	printf("Enter name of second team:  ");
	fgets(second->team2Name, 49, stdin);			stringCheck(second->team2Name);
	printf("Enter name of first player on  team: ");
	fgets(second->player3Name, 49, stdin);			stringCheck(second->player3Name);
	printf("Enter name of second player on team: ");
	fgets(second->player4Name, 49, stdin);			stringCheck(second->player4Name);
	puts(splitter);
	system("cls");
	system("pause");
}

void stringCheck(char* string) {
	int n = strlen(string);
	if (string[n - 1] == '\n') {
		string[n - 1] = '\0';
	}
}