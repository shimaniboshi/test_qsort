#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MEMORY_ERROR -1
#define MAX_NAME_LENGTH 32

#define print_single_rec(x) {printf("id = %10d\tname_length = %3d\tname = %s\n", (x).id, (x).name_length, (x).name);}


typedef int (*Comparator)(const void*, const void*);


typedef struct Record {
	int id;
	int name_length;
	char name[MAX_NAME_LENGTH];
} Record, * LPRecord;



int make_random_string(char* buffer, int max_length) {

	int cnt = 0;
	int length = rand() / ((RAND_MAX / max_length) + 1);

	do {
		char c = (char)(rand() % 128);
		if ((c == ' ') || (('A' <= c) && (c <= 'Z')) ) {
			buffer[cnt] = c;
			cnt++;
		}
	} while (cnt <= length);

	return cnt;
}


void make_test_records(LPRecord records, int entry) {

	for (int i = 0; i < entry; i++) {

		char buffer[MAX_NAME_LENGTH] = {0};
		int length = make_random_string(buffer, MAX_NAME_LENGTH - 1);

		Record rec;
		rec.id = rand();
		rec.name_length = length;
		strcpy(rec.name, buffer);

		records[i] = rec;
	}
}


int comp_by_id(const void* rec_1, const void* rec_2) {
	return (*((LPRecord*)rec_1))->id - (*((LPRecord*)rec_2))->id;			// Ascending-order
	//return (*((LPRecord*)rec_2))->id - (*((LPRecord*)rec_1))->id;			// Descending-order
}


int comp_by_name(const void* rec_1, const void* rec_2) {
	return strcmp((*((LPRecord*)rec_1))->name, (*((LPRecord*)rec_2))->name);	// Ascending-order
	//return strcmp((*((LPRecord*)rec_2))->name, (*((LPRecord*)rec_1))->name);	// Descending-order
}


int comp_by_namelength(const void* rec_1, const void* rec_2) {
	return (*((LPRecord*)rec_1))->name_length - (*((LPRecord*)rec_2))->name_length;		// Ascending-order
	//return (*((LPRecord*)rec_2))->name_length - (*((LPRecord*)rec_1))->name_length;	// Descending-order
}


// Definition of a function with no arguments which returns a pointer to a function which takes void * and void * arguments and returns an int type
// The returned value (function pointer) will be used in 4th argument of qsort() function.
Comparator select_comp_func(void) {		// int (*select_comp_func(void))(const void*, const void*)

	enum CompareMethod {
		ById,		// 0
		ByNameLength,	// 1
		ByName,		// 2
	} func_number;

	// Array consisting of function pointers
	Comparator comp_func[3] = {		 // int (*comp_func[3])(const void*, const void*)
		comp_by_id,
		comp_by_namelength,
		comp_by_name,
	};

	while (1) {
		puts("Please select a comparator function which will be used in sort process.");
		printf("Sort by id => 0 / by name length => 1 / by name => 2 : ");
		scanf("%d", &func_number);
		if (func_number < 0 || 2 < func_number) {
			continue;
		}
		break;
	}

	return comp_func[func_number];
}




int main(void) {


	int entry;

	// Pointer to a function
	Comparator comp_func;			//int (*comp_func)(const void*, const void*);	

	while (1) {
		printf("How many test records are you going to make?: ");
		scanf("%d", &entry);
		if (entry < 1) {
			puts("Invalid value. Please enter a figure more than 1.");
			continue;
		}
		break;
	}
	putchar('\n');



	// Allocate memory for an array of test records
	LPRecord records = (LPRecord)malloc(entry * sizeof(Record));
	if (records == NULL) {
		return MEMORY_ERROR;
	}
	memset(records, '\0', entry * sizeof(Record));
	

	// Create test data and set them to 'records'
	srand((unsigned int)time(NULL));
	make_test_records(records, entry);


	// Allocate memory for an array of pointers of the test records
	LPRecord* record_pointers = (LPRecord*)malloc(entry * sizeof(LPRecord));
	if (record_pointers == NULL) {
		return MEMORY_ERROR;
	}
	memset(record_pointers, '\0', entry * sizeof(LPRecord));


	// Create and set pointers in the array
	for (int i = 0; i < entry; i++) {
		record_pointers[i] = &(records[i]);
	}



	puts("Display test records");
	for (int i = 0; i < entry; i++) {
		printf("[%4d]: ", i);
		print_single_rec(*(record_pointers[i]));
	}
	putchar('\n');


	// Get an pointer to the selected comparator function and perform sort process utilizing that function
	comp_func = select_comp_func();
	qsort((void*)record_pointers, (size_t)entry, sizeof(LPRecord), comp_func);
	

	putchar('\n');
	puts("Processed records");
	for (int i = 0; i < entry; i++) {
		printf("[%4d]: ", i);
		print_single_rec(*record_pointers[i]);
	}

	// Clean up the memory of the pointers array prior to that of the records array which they point to
	free(record_pointers);
	record_pointers = NULL;

	// Clean up the memory for the records array 
	free(records);
	records = NULL;


	return 0;
}
