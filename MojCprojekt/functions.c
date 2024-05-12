#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"
#include <stdbool.h>
const char splitter[50] = { "------------------------------------------------" };

void inputingPlayers() {
	FILE* teamsAndMembers = NULL;
	
	teamsAndMembers = fopen("teamsAndMembers.bin", "ab+");
	if (teamsAndMembers == NULL) {
		perror("Error opening file for writing: ");
		return;
	}

	TEAM* team = (TEAM*)malloc(sizeof(TEAM));
	if (team == NULL) {
		perror("Neuspjesna alokacija memorije: ");
		fclose(teamsAndMembers);
		return;
	}
	
	puts(splitter);
	getchar();
	printf("Unesite ime tima:  ");
	fgets(team->teamName, 49, stdin);				stringCheck(team->teamName);

	if (teamExists(team->teamName)) {
		printf("tim s imenom: '%s' vec postoji\n", team->teamName);
		free(team);
		fclose(teamsAndMembers);
		return;
	}

	printf("Unesite ime prvog igraca u timu: ");
	fgets(team->player1Name, 49, stdin);			stringCheck(team->player1Name);
	printf("Unesite ime drugog igraca u timu: ");
	fgets(team->player2Name, 49, stdin);			stringCheck(team->player2Name);
	team->score = 0;
	team->numOfWins = 0;
	puts(splitter);
	
	fseek(teamsAndMembers, 0, SEEK_END);
	fwrite(team, sizeof(TEAM), 1, teamsAndMembers);

	printf("Tim uspjesno dodan.\n");
	free(team);
	fclose(teamsAndMembers);
} 
void readingTeams() {
	FILE* fpInput = fopen("teamsAndMembers.bin", "rb");
	if (fpInput == NULL) {
		perror("Unable to read file: ");
		return;
	}
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

TEAM* choosingTeams() {
	char inputedName[50];
	
	printf("Unesite ime tima kojeg pretrazujete: ");
	fgets(inputedName, 50, stdin);       stringCheck(inputedName);
	TEAM* tempTeam = malloc(1*sizeof(TEAM));
	if (tempTeam == NULL) {
		perror("Neuspjesno zauzeta memorija za privremeni tim: ");
		return NULL;
	}
	FILE* fpInput = fopen("teamsAndMembers.bin", "rb");
	if (fpInput == NULL) {
		perror("Neuspjesno otvoren file za citanje: ");
		return NULL;
	}
	while(fread(tempTeam,sizeof(TEAM),1,fpInput)==1){
		if (strcmp(tempTeam->teamName, inputedName) == 0) {
			fclose(fpInput);
			printf("Uspjesno pronaden tim pod trazenim imenom! \n");
			return tempTeam;
		}
	}
	fclose(fpInput);
	return NULL;
}



void playing(TEAM* firstTeam, TEAM* secondTeam, int gameMode) {
	int numOfWins1=0, numOfwins2=0;
	do {
		
		while (firstTeam->score <= gameMode && secondTeam->score <= gameMode) {
			int igra = 0;
			int zvanjaPrvog = 0;
			int zvanjaDrugog = 0;
			int team;
			do {
				printf("Unos bodova za tim %s tipka -> 1 <-  Unos bodova za tim %s tipka -> 2 <- ", firstTeam->teamName, secondTeam->teamName);
				scanf("%d", &team);
				printf("\n");
				if (team != 1 && team != 2) {
					printf("Unesena kriva opcija! ");
				}
			} while (team != 1 && team != 2);
			if (team == 1) {
				printf("Tim %s IGRA: ", firstTeam->teamName);
				scanf("%d", &igra);
				printf("Tim %s ZVANJA: ", firstTeam->teamName);
				scanf("%d", &zvanjaPrvog);
				printf("Tim %s zvanja: ", secondTeam->teamName);
				scanf("%d", &zvanjaDrugog);
				printf("\n");
				firstTeam->score += igra + zvanjaPrvog;
				secondTeam->score += (162 - igra) + zvanjaDrugog;
				printf("Team %s: %d\t\t\t\tTeam %s: %d\n", firstTeam->teamName, firstTeam->score, secondTeam->teamName, secondTeam->score);
				printf("Broj pobjeda: %d\t\t\t\tBroj pobjeda: %d\n", numOfWins1, numOfwins2);
				printf("-------------------------------------------------------------------------------------\n");
			}
			else {
				printf("Tim %s IGRA: ", secondTeam->teamName);
				scanf("%d", &igra);
				printf("Tim %s ZVANJA: ", secondTeam->teamName);
				scanf("%d", &zvanjaDrugog);
				printf("Tim %s zvanja: ", firstTeam->teamName);
				scanf("%d", &zvanjaPrvog);
				printf("\n");
				secondTeam->score += igra + zvanjaDrugog;
				firstTeam->score += (162 - igra) + zvanjaPrvog;
				printf("Team %s: %d\t\t\t\tTeam %s: %d\n", firstTeam->teamName, firstTeam->score, secondTeam->teamName, secondTeam->score);
				printf("Broj pobjeda: %d\t\t\t\tBroj pobjeda: %d\n", numOfWins1, numOfwins2);
				printf("-------------------------------------------------------------------------------------\n");
			}

		}
		if (firstTeam->score > secondTeam->score) {
			numOfWins1++;
			printf("Tim %s je pobjedio ovu rundu: \n",firstTeam->teamName);
			firstTeam->score = 0; secondTeam->score = 0;
		}
		else {
			numOfwins2++;
			printf("Tim %s je pobjedio ovu rundu: \n", secondTeam->teamName);
			firstTeam->score = 0; secondTeam->score = 0;
		}

		if (numOfWins1 == 2) {
			printf("Tim %s je pobjedio! \n", firstTeam->teamName);
			updateNumOfWinsInFile(firstTeam);
			
		}
		else if (numOfwins2 == 2) {
			printf("Tim %s je pobjedio! \n", secondTeam->teamName);
			updateNumOfWinsInFile(secondTeam);
		}
	} while (numOfWins1 < 2 && numOfwins2 < 2);

	system("pause");

	return;
}

void updateNumOfWinsInFile(TEAM*selectedTeam ) {
	FILE* file = fopen("teamsAndMembers.bin", "rb+");
	if (file == NULL) {
		perror("Neuspjesno otvoren file: ");
		return;
	}

	TEAM tempTeam;
	
	while (fread(&tempTeam, sizeof(TEAM), 1, file) == 1) {
		if (strcmp(tempTeam.teamName, selectedTeam->teamName) == 0) {
			selectedTeam->numOfWins ++;
			fseek(file, -((long)sizeof(TEAM)), SEEK_CUR);
			fwrite(selectedTeam, sizeof(TEAM), 1, file);
			printf("Broj pobjeda uspjesno azuriran!\n");
			fclose(file);
			return;
		}
	}
	fclose(file);
	return;
}

bool teamExists(const char* teamName) {
	FILE* file = fopen("teamsAndMembers.bin", "rb");
	if (file == NULL) {
		perror("Neuspjesno otvaranje dokumenta: ");
		return false;
	}

	TEAM tempTeam;

	while (fread(&tempTeam, sizeof(TEAM), 1, file) == 1) {
		if (strcmp(tempTeam.teamName, teamName) == 0) {
			fclose(file);
			return true;
		}
	}

	fclose(file);
	return false;
}


void deleteTeam() {
	char teamNameToDelete[50];
	getchar();
	printf("Unesite ime tima kojeg zelite izbrisati: ");
	fgets(teamNameToDelete, 50, stdin);							stringCheck(teamNameToDelete);

	if (!teamExists(teamNameToDelete)) {
		printf("Team '%s' does not exist in the file\n", teamNameToDelete);
		return;
	}

	FILE* originalFile = fopen("teamsAndMembers.bin", "rb");
	if (originalFile == NULL) {
		perror("Greska prilikom otvaranja originalnog dikumenta: ");
		return;
	}

	FILE* tempFile = fopen("temp.bin", "wb");
	if (tempFile == NULL) {
		perror("Greska prilikom kreiranja privremeog tima: ");
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


int playingOptions() {
	int gameMode;
	
		printf("\nIgra do 301  broj -> 1\n");
		printf("Igra do 501  broj -> 2\n");
		printf("Igra do 1001 broj -> 3\n");
		do {
			printf("Unesite opciju: ");
			if (scanf("%d", &gameMode) != 1) {
				printf("Neispravan unos. Molimo unesite broj.\n");

				while (getchar() != '\n');
			}
			else if (gameMode < 1 || gameMode > 3) {
				printf("Neispravan unos. Unesite broj izmedu 1 i 3.\n");
			}
		} while (gameMode < 1 || gameMode > 3);
		
		system("cls");

	if(gameMode==1){
		return 301;
	}
	else if (gameMode == 2) {
		return 501;
	}
	
	return 1001;
}


void inputingNewTeams(TEAM**firstTeam, TEAM**secondTeam) {
	*firstTeam = (TEAM*)malloc(sizeof(TEAM));
	if (firstTeam == NULL) {
		perror("Neuspjesno zauzimanje memorije: ");
		return;
	}
	*secondTeam = (TEAM*)malloc(sizeof(TEAM));
	if (secondTeam == NULL) {
		perror("Neuspjesno zauzimanje memorije: ");
		return;
	}

	puts(splitter);
	getchar();
	printf("Enter name of first team:  ");
	fgets((*firstTeam)->teamName, 49, stdin);				stringCheck((*firstTeam)->teamName);
	printf("Enter name of first player on  team: ");
	fgets((*firstTeam)->player1Name, 49, stdin);			stringCheck((*firstTeam)->player1Name);
	printf("Enter name of second player on team: ");
	fgets((*firstTeam)->player2Name, 49, stdin);			stringCheck((*firstTeam)->player2Name);
	(*firstTeam)->score = 0;
	(*firstTeam)->numOfWins = 0;
	puts(splitter);
	
	printf("Enter name of second team:  ");
	fgets((*secondTeam)->teamName, 49, stdin);				stringCheck((*secondTeam)->teamName);
	printf("Enter name of first player on  team: ");
	fgets((*secondTeam)->player1Name, 49, stdin);			stringCheck((*secondTeam)->player1Name);
	printf("Enter name of second player on team: ");
	fgets((*secondTeam)->player2Name, 49, stdin);			stringCheck((*secondTeam)->player2Name);
	(*secondTeam)->score = 0;
	(*secondTeam)->numOfWins = 0;
	puts(splitter);

	FILE* teamsAndMembers = NULL;

	teamsAndMembers = fopen("teamsAndMembers.bin", "ab+");
	if (teamsAndMembers == NULL) {
		perror("Error opening file for writing: ");
		return;
	}

	fseek(teamsAndMembers, 0, SEEK_END);
	fwrite(firstTeam, sizeof(TEAM), 1, teamsAndMembers);

	fseek(teamsAndMembers, 0, SEEK_END);
	fwrite(secondTeam, sizeof(TEAM), 1, teamsAndMembers);

	printf("Timovi uspjesno upisani: \n");
	fclose(teamsAndMembers);
	return;
}

void stringCheck(char* string) {
	int n = strlen(string);
	if (string[n - 1] == '\n') {
		string[n - 1] = '\0';
	}
}