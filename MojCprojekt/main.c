/*
aplikacija koja pomaže pri unosu rezultata i računanja pobjednika belle.
aplikacija unosi 2 tima po 2 igrača koji nakon partije mogu unjeti samo bodove i zvanja prikupljena od strane
jednog tima a aplikacija će izračunati za drugi tim. aplikacija također prati i ispisuje koji je igrač trenutno
na redu za mješati špil karata.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"

int main(void) {
	Team1* firstTeam = (Team1*)malloc(sizeof(Team1));
	Team2* secondTeam = (Team2*)malloc(sizeof(Team2));
	inputingPlayers(firstTeam, secondTeam);

	return 0;
}
	
	
	
