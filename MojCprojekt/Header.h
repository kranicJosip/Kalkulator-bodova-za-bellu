#pragma once
#include <stdbool.h>
typedef struct {
	char teamName[50];
	char player1Name[50];
	char player2Name[50];
	unsigned short int numOfWins;
	unsigned short int score;
}TEAM;


typedef enum {
	INPUTING_PLAYERS = 1,
	READING_TEAMS,
	START_GAME,
	DELETE_TEAM,
	EXIT_PROGRAM
} MenuOption;



void readingTeams();
void inputingPlayers();
void stringCheck(char*);
int optionPrompt();
int menu(int);
int subMenu(int);
int subMenuOptionPrompt();
TEAM* choosingTeams();
void playing(TEAM*, TEAM*,int);
int playingOptions();

void inputingNewTeams(TEAM**,TEAM**);
void updateNumOfWinsInFile(TEAM*);

void deleteTeam();
bool teamExists(const char* teamName);

int choice(int,int);