#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"
#include <stdbool.h>

const char splitter[50] = "------------------------------------------------";

// Funkcija za main meni
int optionPrompt() {

	int opcija;

	printf("\t\t-----------Odaberite jednu od sljedecih opcija ------------\n");
	printf("\t\t-----------Upisivanje novih igraca i timova: 1 <-----------\n");
	printf("\t\t-----------Ispisivanje svih upisanih timova: 2 <-----------\n");
	printf("\t\t-----------Zapocni igru:                     3 <-----------\n");
	printf("\t\t-----------Izbrisi tim iz baze podataka:     4 <-----------\n");
	printf("\t\t-----------Ispisi po broju pobjeda timova    5 <-----------\n");
	printf("\t\t-----------Izlaz iz programa:                6 <-----------\n");

	opcija = choice(1, 6);

	return opcija;

}

//Funkcija za unos novih timova u bazu podataka:
void inputingPlayers() {
	FILE* teamsAndMembers = NULL;

	teamsAndMembers = fopen("teamsAndMembers.bin", "ab+");
	CHECK_FILE_EXIST(teamsAndMembers);

	TEAM* team = (TEAM*)malloc(sizeof(TEAM));
	if (team == NULL) {
		perror("Neuspjesna alokacija memorije: ");
		fclose(teamsAndMembers);
		return;
	}

	puts(splitter);
	printf("Unesite ime tima:  ");
	fgets(team->teamName, MAX_STRING, stdin);				stringCheck(team->teamName);

	if (teamExists(team->teamName)) {
		printf("tim s imenom: '%s' vec postoji\n", team->teamName);
		free(team);
		fclose(teamsAndMembers);
		return;
	}

	printf("Unesite ime prvog igraca u timu: ");
	fgets(team->player1Name, MAX_STRING, stdin);			stringCheck(team->player1Name);
	printf("Unesite ime drugog igraca u timu: ");
	fgets(team->player2Name, MAX_STRING, stdin);			stringCheck(team->player2Name);
	team->score = 0;
	team->numOfWins = 0;
	puts(splitter);

	fseek(teamsAndMembers, 0, SEEK_END);
	fwrite(team, sizeof(TEAM), 1, teamsAndMembers);

	printf("Tim uspjesno dodan.\n");
	free(team);
	fclose(teamsAndMembers);
}

//Funkcija cita sve timove u dokumentu i ispisuje ih
void readingTeams() {
	FILE* fpInput = fopen("teamsAndMembers.bin", "rb");
	CHECK_FILE_EXIST(fpInput);
	/*if (fpInput == NULL) {
		perror("Neuspjesno citanje daatoteke: ");
		return;
	}*/
	int num;

	fseek(fpInput, 0, SEEK_END);
	long fileSize = ftell(fpInput);
	rewind(fpInput);

	num = (int)((fileSize) / sizeof(TEAM));

	printf("Upisanih timova ima: %d\n", num);

	TEAM* teamsInfo = (TEAM*)malloc(num * sizeof(TEAM));
	if (teamsInfo == NULL) {
		printf("Neuspjesno zauzimanje memorije: \n");
		fclose(fpInput);
		return;
	}

	fread(teamsInfo, sizeof(TEAM), num, fpInput);

	for (int i = 0; i < num; i++) {
		printf("Team %d:\n", i + 1);
		printf("Ime tima: %s\n", teamsInfo[i].teamName);
		printf("Ime prog igraca: %s\n", teamsInfo[i].player1Name);
		printf("Ime drugog igraca: %s\n", teamsInfo[i].player2Name);
		printf("Broj pobjeda tima: %hu\n", teamsInfo[i].numOfWins);

		printf("\n");
	}
	free(teamsInfo);
	fclose(fpInput);
}

//Funkcija za brisanje odedenog tima iz baze (trazenje po imenu tima):
void deleteTeam() {
	char teamNameToDelete[MAX_STRING];
	
	printf("Unesite ime tima kojeg zelite izbrisati: ");
	fgets(teamNameToDelete, MAX_STRING, stdin);							stringCheck(teamNameToDelete);

	if (!teamExists(teamNameToDelete)) {
		printf("Team '%s' does not exist in the file\n", teamNameToDelete);
		return;
	}

	FILE* originalFile = fopen("teamsAndMembers.bin", "rb");
	CHECK_FILE_EXIST(originalFile);

	FILE* tempFile = fopen("temp.bin", "wb");
	if (tempFile == NULL) {
		perror("Greska prilikom kreiranja privremenog tima: ");
		fclose(originalFile);
		return;
	}

	TEAM tempTeam;

	while (fread(&tempTeam, sizeof(TEAM), 1, originalFile) == 1) {
		if (strcmp(tempTeam.teamName, teamNameToDelete) != 0) {
			fwrite(&tempTeam, sizeof(TEAM), 1, tempFile);
		}
	}

	fclose(originalFile);
	fclose(tempFile);

	if (remove("teamsAndMembers.bin") != 0) {
		perror("Greska pri brisanju originalnog dokumenta: ");
		return;
	}

	if (rename("temp.bin", "teamsAndMembers.bin") != 0) {
		perror("Greska u preimenovanju privremenog dokumenta: ");
		return;
	}

	printf("Timm '%s' uspjesno obrisan\n", teamNameToDelete);
}


//Funkcija koja cita sve timove i ispisuje ih sortirano po broju pobjeda(Silazno):
void printingSortedTeams() {
	FILE* fpInput = fopen("teamsAndMembers.bin", "rb");
	CHECK_FILE_EXIST(fpInput);

	fseek(fpInput, 0, SEEK_END);
	long fileSize = ftell(fpInput);
	rewind(fpInput);

	int numTeams = (int)(fileSize / sizeof(TEAM));
	printf("Upisanih timova ima: %d\n", numTeams);

	TEAM* teams = (TEAM*)malloc(numTeams * sizeof(TEAM));
	if (teams == NULL) {
		printf("Neuspjesno zauzimanje memorije: \n");
		fclose(fpInput);
		return;
	}

	fread(teams, sizeof(TEAM), numTeams, fpInput);
	fclose(fpInput);

	qsort(teams, numTeams, sizeof(TEAM), compareTeamsByWins);

	for (int i = 0; i < numTeams; i++) {
		printf("Team %d:\n", i + 1);
		printf("Ime tima: %s\n", teams[i].teamName);
		printf("Ime prog igraca: %s\n", teams[i].player1Name);
		printf("Ime drugog igraca: %s\n", teams[i].player2Name);
		printf("Broj pobjeda tima: %hu\n", teams[i].numOfWins);
		printf("\n");
	}

	free(teams);
}

//pomocna funkcija prethodonoj funkciji vraca pozitivnu/negativnu vrijednost ili 0:
int compareTeamsByWins(const void* a, const void* b) {
	TEAM* teamA = (TEAM*)a;
	TEAM* teamB = (TEAM*)b;
	return teamB->numOfWins - teamA->numOfWins;
}