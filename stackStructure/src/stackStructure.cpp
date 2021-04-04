#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define NUMBER_OF_RECORDS 3

struct reservation {
	char placeID[15];
	char firstName[64];
	char lastName[64];
};

void menuDisplay();
int chooseSearchingType();
int compareByID(struct reservation* pointerReservation, int numberOfRecords, char searchingBy[15]);
int compareByName(struct reservation* pointerReservation, int numberOfRecords, char searchingBy[64]);
int compareBySurname(struct reservation* pointerReservation, int numberOfRecords, char searchingBy[64]);

void displayRecords(struct reservation* pointerReservation, int numberOfRecords) {
	int i;
	if (numberOfRecords == 0) printf("\nNo records to read\n");
	else {
		for (i = 0; i < numberOfRecords; i++) {
			printf("Detail of %d customer: \n", i + 1);

			printf("ID of place: %s\n", pointerReservation->placeID);
			printf("First name: %s\n", pointerReservation->firstName);
			printf("Last name: %s\n", pointerReservation->lastName);
			printf("\n");

			pointerReservation++;
		}
		pointerReservation -= i;
	}
}

void displayOneRecord(struct reservation* pointerReservation, int id) {
	printf("\nDetail of %d customer: \n", id + 1);
	printf("ID of place: %s\n", pointerReservation->placeID);
	printf("First name: %s\n", pointerReservation->firstName);
	printf("Last name: %s\n", pointerReservation->lastName);
	printf("\n");
}

void addNewRecord(struct reservation* pointerReservation, int numberOfRecords, int *startPosition) {
	int count = 0;
	printf("\n\nHow many record do you want to add?\n");
	scanf_s("%d", &count);

	pointerReservation += *startPosition;
	int i = 0;
	for (i = *startPosition; i < (numberOfRecords + count) && i < 100; i++) {
		printf("\nEnter detail of %d customer: \n", i + 1);

		printf("Enter the number of place: ");
		scanf_s("%s", pointerReservation->placeID, sizeof(pointerReservation->placeID));

		printf("Enter name: \t");
		scanf_s("%s", pointerReservation->firstName, sizeof(pointerReservation->firstName));

		printf("Enter surname: \t");
		scanf_s("%s", pointerReservation->lastName, sizeof(pointerReservation->lastName));

		pointerReservation++;
	}
	*startPosition = i;
	pointerReservation -= i;
}

int deleteRecordHelper(struct reservation* pointerReservation, int numberOfRecords, int position) {
	pointerReservation += (position - 1);
	int i;
	for (i = position - 1 ; i < numberOfRecords - 1; i++) {
		memmove(pointerReservation->placeID, (pointerReservation + 1)->placeID, 4);
		memmove(pointerReservation->firstName, (pointerReservation + 1)->firstName, 16);
		memmove(pointerReservation->lastName, (pointerReservation + 1)->lastName, 16);

		pointerReservation++;
	}
	pointerReservation -= i;
	numberOfRecords--;
	return numberOfRecords;
}

int deleteRecord(struct reservation* pointerReservation, int numberOfRecords, int keyword) {
	if (keyword == 1) {
		int pointerHolder;
		printf("\nType ID: ");
		char searchingBy[15];
		scanf_s("%s", searchingBy, sizeof(searchingBy));
		pointerHolder = compareByID(pointerReservation, numberOfRecords, searchingBy);
		if (pointerHolder == -1) printf("\nSorry, I could not find an element.\n");
		else {
			numberOfRecords = deleteRecordHelper((pointerReservation), numberOfRecords, pointerHolder);
			return numberOfRecords;
		}
	}
	else if (keyword == 2) {
		int pointerHolder;
		printf("\nType first name: ");
		char searchingBy[64];
		scanf_s("%s", searchingBy, sizeof(searchingBy));
		pointerHolder = compareByName(pointerReservation, numberOfRecords, searchingBy);
		if (pointerHolder == -1) printf("\nSorry, I could not find an element.\n");
		else {
			numberOfRecords = deleteRecordHelper((pointerReservation), numberOfRecords, pointerHolder);
			return numberOfRecords;
		}
	}
	else if (keyword == 3) {
		int pointerHolder;
		printf("\nType surname: ");
		char searchingBy[64];
		scanf_s("%s", searchingBy, sizeof(searchingBy));
		pointerHolder = compareBySurname(pointerReservation, numberOfRecords, searchingBy);
		if (pointerHolder == -1) printf("\nSorry, I could not find an element.\n");
		else {
			numberOfRecords = deleteRecordHelper((pointerReservation), numberOfRecords, pointerHolder);
			return numberOfRecords;
		}
	}
	else {
		perror("");
		exit(1);
	}
	return numberOfRecords;
}

int chooseSearchingType() {
	int searchingType;
	
	printf("\nWith which you want to search or delete an item?\n"
		"If ID enter 1\n"
		"If first name enter 2\n"
		"if surname enter 3\n"
		"Enter here: ");
	do {
		scanf_s("%d", &searchingType);
	} while (searchingType < 1 || searchingType > 3);

	return searchingType;
}

void findRecord(struct reservation* pointerReservation, int numberOfRecords, int keyword) {
	if (keyword == 1) {
		int pointerHolder;
		printf("\nType ID: ");
		char searchingBy[15];
		scanf_s("%s", searchingBy, sizeof(searchingBy));
		pointerHolder = compareByID(pointerReservation, numberOfRecords, searchingBy);
		if (pointerHolder == -1) printf("\nSorry, I could not find an element.\n");
		else displayOneRecord(pointerReservation, pointerHolder);
	}
	else if (keyword == 2) {
		int pointerHolder;
		printf("\nType first name: ");
		char searchingBy[64];
		scanf_s("%s", searchingBy, sizeof(searchingBy));
		pointerHolder = compareByName(pointerReservation, numberOfRecords, searchingBy);
		if (pointerHolder == -1) printf("\nSorry, I could not find an element.\n");
		else displayOneRecord(pointerReservation, pointerHolder);
	}
	else if (keyword == 3) {
		int pointerHolder;
		printf("\nType surname: ");
		char searchingBy[64];
		scanf_s("%s", searchingBy, sizeof(searchingBy));
		pointerHolder = compareBySurname(pointerReservation, numberOfRecords, searchingBy);
		if (pointerHolder == -1) printf("\nSorry, I could not find an element.\n");
		else displayOneRecord(pointerReservation, pointerHolder);
	}
	else {
		perror("");
		exit(1);
	}
}

void writeToFile(struct reservation* pointerReservation, int numberOfRecords) {
	FILE* ListOfCustomers;
	errno_t ListOfCustomersErr;
	ListOfCustomersErr = fopen_s(&ListOfCustomers, "CustomersList.txt", "w");
	if (ListOfCustomersErr != 0) {
		printf("I could not open the file");
		exit(1);
	}
	int i;
	for (i = 0; i < numberOfRecords; i++) {
		fprintf_s(ListOfCustomers, "%s", pointerReservation->placeID);
		fprintf_s(ListOfCustomers, "%s", "\n");
		fprintf_s(ListOfCustomers, "%s", pointerReservation->firstName);
		fprintf_s(ListOfCustomers, "%s", "\n");
		fprintf_s(ListOfCustomers, "%s", pointerReservation->lastName);
		if (i != numberOfRecords - 1) {
			fprintf_s(ListOfCustomers, "%s", "\n");
		}

		pointerReservation++;
	}
	pointerReservation -= i;
	ListOfCustomersErr = fclose(ListOfCustomers);
}

void readFromFile(struct reservation* pointerReservation, int* howManyRecords) {
	FILE* ListOfCustomers;
	errno_t ListOfCustomersErr;
	ListOfCustomersErr = fopen_s(&ListOfCustomers, "CustomersList.txt", "r");
	if (ListOfCustomersErr != 0) {
		printf("I could not open the file");
		exit(1);
	}
	fseek(ListOfCustomers, 0L, SEEK_SET);
	int i=0;
	while (!feof(ListOfCustomers)) {
		if (ListOfCustomers) {
			fscanf_s(ListOfCustomers, "%s", pointerReservation->placeID, sizeof(pointerReservation->placeID));
			fscanf_s(ListOfCustomers, "%s", pointerReservation->firstName, sizeof(pointerReservation->firstName));
			fscanf_s(ListOfCustomers, "%s", pointerReservation->lastName, sizeof(pointerReservation->lastName));
			//_countof
			i++;
			pointerReservation++;
		}
	}
	*howManyRecords = i;
	pointerReservation -= i;
	ListOfCustomersErr = fclose(ListOfCustomers);
}

void menuDisplay() {
	printf("\nHello, what do you need?\n"
		"1- Add new\n"
		"2- Delete existing position\n"
		"3- Find already existing record\n"
		"4- Show all records\n"
		"5- Write to file\n"
		"6- Reading from file\n"
		"7- Close and exit\n"
		"Your choice: ");
}

/*------------------------------------------------------------MAIN-------------------------------------------------------------*/

int main() {

	struct reservation table[100];
	int howManyRecords=0;
	int choice;
	do {
		menuDisplay();
		scanf_s("%d", &choice);
		printf("\n");

		switch (choice) {
		case 1: addNewRecord(table, howManyRecords, &howManyRecords);
			break;
		case 2: howManyRecords = deleteRecord(table, howManyRecords, chooseSearchingType());
			break;
		case 3: findRecord(table, howManyRecords, chooseSearchingType());
			break;
		case 4: displayRecords(table, howManyRecords);
			break;
		case 5: writeToFile(table, howManyRecords);
			break;
		case 6: readFromFile(table, &howManyRecords);
			break;
		default: {
			perror("");
		}
		}
	} while (choice != 7);

	return 0;
}

/*------------------------------------------------------------MAIN-------------------------------------------------------------*/

int compareByID(struct reservation* pointerReservation, int numberOfRecords, char searchingBy[15]) {
	int i, pointerHolder = 0;
	for (i = 0; i < numberOfRecords; i++) {
		if (!(strncmp((pointerReservation->placeID), searchingBy, sizeof((pointerReservation->placeID))))) {
			pointerHolder = i;
			break;
		}
		else pointerHolder = -1;
		pointerReservation++;
	}
	return pointerHolder;
}
int compareByName(struct reservation* pointerReservation, int numberOfRecords, char searchingBy[64]) {
	int i, pointerHolder = 0;
	for (i = 0; i < numberOfRecords; i++) {
		if (!(strncmp((pointerReservation->firstName), searchingBy, sizeof((pointerReservation->firstName))))) {
			pointerHolder = i;
			break;
		}
		else pointerHolder = -1;
		pointerReservation++;
	}
	return pointerHolder;
}

int compareBySurname(struct reservation* pointerReservation, int numberOfRecords, char searchingBy[64]) {
	int i, pointerHolder = 0;
	for (i = 0; i < numberOfRecords; i++) {
		if (!(strncmp((pointerReservation->lastName), searchingBy, sizeof((pointerReservation->lastName))))) {
			pointerHolder = i;
			break;
		}
		else pointerHolder = -1;
		pointerReservation++;
	}
	return pointerHolder;
}