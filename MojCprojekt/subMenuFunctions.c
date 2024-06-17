#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"
#include <stdbool.h>

//Funkcija za subMenu:
int subMenuOptionPrompt() {
	int opcija;
	printf("\t\t-----------Odaberite jednu od sljedecih opcija ------------\n");
	printf("\t\t-----------Odaberite dva vec postojeca tima: 1 <-----------\n");
	printf("\t\t-----------Unesite nove timove za igru:      2 <-----------\n");
	printf("\t\t-----------Vrati se u meni:                  3 <-----------\n");

	opcija = choice(1, 3);

	return opcija;
}

//Funkcija vraca odabrani tim za igru: (trazi po imenu tima):
TEAM* choosingTeams() {
	char inputedName[MAX_STRING];
	puts(splitter);
	printf("Unesite ime tima kojeg pretrazujete: ");
	fgets(inputedName, MAX_STRING, stdin);       stringCheck(inputedName);
	TEAM* tempTeam = malloc(1 * sizeof(TEAM));
	if (tempTeam == NULL) {
		perror("Neuspjesno zauzeta memorija za privremeni tim: ");
		return NULL;
	}
	FILE* fpInput = fopen("teamsAndMembers.bin", "rb");
	if (fpInput == NULL) {
		perror("Neuspjesno otvoren file za citanje: ");
		free(tempTeam);
		return NULL;
	}
	while (fread(tempTeam, sizeof(TEAM), 1, fpInput) == 1) {
		if (strcmp(tempTeam->teamName, inputedName) == 0) {
			fclose(fpInput);
			printf("Uspjesno pronaden tim pod trazenim imenom! \n");

			return tempTeam;
		}
	}
	free(tempTeam);
	fclose(fpInput);
	return NULL;
}

//Funkcija vraca broj koji predstavlja vrijednsot do koje se skupljaju bodovi:
int playingOptions() {
	int gameMode;
	puts(splitter);
	printf("Igra do 301  broj -> 1\n");
	printf("Igra do 501  broj -> 2\n");
	printf("Igra do 1001 broj -> 3\n");
	puts(splitter);
	gameMode = choice(1, 3);

	system("cls");

	if (gameMode == 1) {
		return 301;
	}
	else if (gameMode == 2) {
		return 501;
	}

	return 1001;
}

int getMaxTeamNameLength(const TEAM* const team1, const TEAM* const team2) {
	int len1 = strlen(team1->teamName);
	int len2 = strlen(team2->teamName);
	return (len1 > len2) ? len1 : len2;
}

//Glavna funkcija u koju igraci upisuju bodove i koja ispisuje trenutno stanje:
void playing( TEAM* const firstTeam , TEAM* const secondTeam, const int gameMode) {
	static int gamesPlayed = 0;
	int numOfWins1 = 0, numOfwins2 = 0;
	int maxLength = getMaxTeamNameLength(firstTeam,secondTeam);
	do {

		while (firstTeam->score <= gameMode && secondTeam->score <= gameMode) {
			int igra = 0;
			int zvanjaPrvog = 0;
			int zvanjaDrugog = 0;
			int team;
			
			printf("Unos bodova za tim %s tipka -> 1 <-  Unos bodova za tim %s tipka -> 2 <-  Izlaz iz igre -> 3 <-\n", firstTeam->teamName, secondTeam->teamName);
			team = choice(1, 3);
			
			if (team == 1) {
				printf("Tim %s IGRA: ", firstTeam->teamName);
				igra = choice(0, 162);
				printf("Tim %s ZVANJA: ", firstTeam->teamName);
				zvanjaPrvog = choice(0, gameMode);
				printf("Tim %s zvanja: ", secondTeam->teamName);
				zvanjaDrugog = choice(0, gameMode);
				printf("\n");
				firstTeam->score += igra + zvanjaPrvog;
				secondTeam->score += (162 - igra) + zvanjaDrugog;
				printf("Team %-*s: %3d\t\t\tTeam %-*s: %3d\n", maxLength, firstTeam->teamName, firstTeam->score,maxLength, secondTeam->teamName, secondTeam->score);
				printf("Broj pobjeda: %2d\t\tBroj pobjeda: %2d\n", numOfWins1, numOfwins2);
				printf("-------------------------------------------------------------------------------------\n");
			}
			else if(team==2){
				printf("Tim %s IGRA: ", secondTeam->teamName);
				igra = choice(0, 162);
				printf("Tim %s ZVANJA: ", secondTeam->teamName);
				zvanjaDrugog = choice(0, gameMode);
				printf("Tim %s zvanja: ", firstTeam->teamName);
				zvanjaPrvog = choice(0, gameMode);
				printf("\n");
				secondTeam->score += igra + zvanjaDrugog;
				firstTeam->score += (162 - igra) + zvanjaPrvog;
				printf("Team %-*s: %3d\t\t\tTeam %-*s: %3d\n",maxLength, firstTeam->teamName, firstTeam->score,maxLength, secondTeam->teamName, secondTeam->score);
				printf("Broj pobjeda: %2d\t\tBroj pobjeda: %2d\n", numOfWins1, numOfwins2);
				printf("-------------------------------------------------------------------------------------\n");
			}
			else {
				printf("Igra prekinuta rezultat se brise!\n");
				system("pause");
				return;
			}

		}
		if (firstTeam->score > secondTeam->score) {
			numOfWins1++;
			printf("Tim %s je pobjedio ovu rundu: \n", firstTeam->teamName);
			firstTeam->score = 0; secondTeam->score = 0;
		}
		else {
			numOfwins2++;
			printf("Tim %s je pobjedio ovu rundu: \n", secondTeam->teamName);
			firstTeam->score = 0; secondTeam->score = 0;
		}

		if (numOfWins1 == 2) {
			puts(splitter);
			printf("Tim %s je pobjedio! \n", firstTeam->teamName);
			puts(splitter);
			updateNumOfWinsInFile(firstTeam);

		}
		else if (numOfwins2 == 2) {
			puts(splitter);
			printf("Tim %s je pobjedio! \n", secondTeam->teamName);
			puts(splitter);
			updateNumOfWinsInFile(secondTeam);
		}
	} while (numOfWins1 < 2 && numOfwins2 < 2);

	gamesPlayed++; 
	printf("\nOdigrano igara otkad je program upaljen: %d\n", gamesPlayed);

	system("pause");

	return;
}

//Funkcija koja nakon sto igra zavrsi azurira broj pobjeda pobjednickog tima u dokumentu;
void updateNumOfWinsInFile(TEAM* const selectedTeam) {
	FILE* file = fopen("teamsAndMembers.bin", "rb+");
	CHECK_FILE_EXIST(file);

	TEAM tempTeam;

	while (fread(&tempTeam, sizeof(TEAM), 1, file) == 1) {
		if (strcmp(tempTeam.teamName, selectedTeam->teamName) == 0) {
			selectedTeam->numOfWins++;
			fseek(file, -((long)sizeof(TEAM)), SEEK_CUR);
			fwrite(selectedTeam, sizeof(TEAM), 1, file);
			printf("Broj pobjeda uspjesno azuriran!\n");
			fclose(file);
			return;
		}
	}
	printf("Broj pobjeda neuspjesno azuriran!!\n");
	fclose(file);
	return;
}

//Funkcija ubacuje 2 nova tima u dokument :
int inputingNewTeams(TEAM** const firstTeam, TEAM** const secondTeam) {
	FILE* teamsAndMembers = NULL;
	teamsAndMembers = fopen("teamsAndMembers.bin", "rb+");
	if (teamsAndMembers == NULL) {
		perror("Greska pri otvaranju dokumenta: ");
		system("pause");
		return 1;
	}

	*firstTeam = (TEAM*)malloc(sizeof(TEAM));
	if (firstTeam == NULL) {
		perror("Neuspjesno zauzimanje memorije: ");
		return 1;
	}
	*secondTeam = (TEAM*)malloc(sizeof(TEAM));
	if (secondTeam == NULL) {
		perror("Neuspjesno zauzimanje memorije: ");
		return 1;
	}

	puts(splitter);
	while (1) {
		printf("Unesite ime prvog tima:  ");
		fgets((*firstTeam)->teamName, MAX_STRING, stdin);			stringCheck((*firstTeam)->teamName);

		if (!teamExists((*firstTeam)->teamName)) {
			break;
		}
		printf("Tim s imenom %s vec postoji unesite neko drugo ime: ", (*firstTeam)->teamName);
	}

	printf("Unesite ime prvog igraca u timu: ");
	fgets((*firstTeam)->player1Name, MAX_STRING, stdin);			stringCheck((*firstTeam)->player1Name);
	printf("Unesite ime drugog igraca u timu: ");
	fgets((*firstTeam)->player2Name, MAX_STRING, stdin);			stringCheck((*firstTeam)->player2Name);
	(*firstTeam)->score = 0;
	(*firstTeam)->numOfWins = 0;
	puts(splitter);

	while (1) {
		printf("Unesite ime drugog tima:  ");
		fgets((*secondTeam)->teamName, MAX_STRING, stdin);			stringCheck((*secondTeam)->teamName);

		if (!teamExists((*secondTeam)->teamName)) {
			break;
		}
		printf("Tim s imenom %s vec postoji unesite neko drugo ime: ", (*secondTeam)->teamName);
	}

	printf("Unesite ime prvog igraca u timu: ");
	fgets((*secondTeam)->player1Name, MAX_STRING, stdin);			stringCheck((*secondTeam)->player1Name);
	printf("Unesite ime drugog igraca u timu: ");
	fgets((*secondTeam)->player2Name, MAX_STRING, stdin);			stringCheck((*secondTeam)->player2Name);
	(*secondTeam)->score = 0;
	(*secondTeam)->numOfWins = 0;
	puts(splitter);

	fseek(teamsAndMembers, 0, SEEK_END);
	fwrite(*firstTeam, sizeof(TEAM), 1, teamsAndMembers);

	fseek(teamsAndMembers, 0, SEEK_END);
	fwrite(*secondTeam, sizeof(TEAM), 1, teamsAndMembers);

	printf("Timovi uspjesno upisani: \n");
	fclose(teamsAndMembers);
	
	return 0;
}
