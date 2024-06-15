/*
aplikacija koja pomaže pri unosu rezultata i računanja pobjednika belle.
aplikacija unosi 2 tima po 2 igrača koji nakon partije mogu unjeti samo bodove i zvanja prikupljena od strane
jednog tima a aplikacija će izračunati za drugi tim. aplikacija također prati i ispisuje koji je igrač trenutno
na redu za mješati špil karata.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main(void) {
	int status = 1;
	while (status) {
		system("cls");
		status = menu(status);
	}

	return 0;
}