#pragma once

typedef struct {
	char team1Name[50];
	char player1Name[50];
	char player2Name[50];
	short int score;
}Team1;
typedef struct {
	char team2Name[50];
	char player3Name[50];
	char player4Name[50];
	short int score2;
}Team2;

void inputingPlayers(Team1*,Team2*);
void stringCheck(char*);