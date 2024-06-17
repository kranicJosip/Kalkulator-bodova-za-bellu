#pragma once
#include <stdbool.h>
#define MAX_STRING 100
extern const char splitter[50];

#define CHECK_FILE_EXIST(file) \
    do { \
        if ((file) == NULL) { \
            perror("Greska pri otvaranju dokumenta: "); \
            return; \
        } \
    } while (0)

typedef struct {
	char teamName[MAX_STRING];
	char player1Name[MAX_STRING];
	char player2Name[MAX_STRING];
	unsigned short int numOfWins;
	unsigned short int score;
}TEAM;

typedef enum {
	INPUTING_TEAMS = 1,
	READING_TEAMS,
	START_GAME,
	DELETE_TEAM,
	PRINT_SORTED,
	EXIT_PROGRAM
} MENU_OPTIONS;

typedef enum {
	CHOOSE_EXISTING_TEAMS = 1,
	INPUTING_NEW_TEAMS,
	BACK_TO_MENU,
} SUB_MENU_OPTIONS;

//generic functions:
bool teamExists(const char* const teamName);
void stringCheck(char* const);
int choice(const int, const int);

//menuFunctions:
int menu(int);
int optionPrompt();
void inputingPlayers();
void readingTeams();
void deleteTeam();
void printingSortedTeams();
int compareTeamsByWins(const void*, const void*);

//subMenuOptons:
int subMenu(int);
int subMenuOptionPrompt();
TEAM* choosingTeams();
int getMaxTeamNameLength(const TEAM* const,const TEAM* const);
int playingOptions();
void playing(TEAM* const, TEAM* const, const int);
void updateNumOfWinsInFile(TEAM* const);
int inputingNewTeams(TEAM** const, TEAM** const);


