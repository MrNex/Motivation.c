#include <time.h>
#include <stdio.h>
#include <stdlib.h>

///
//Prints a usage message
void Usage(void)
{
	printf("Usage: Motivation <year> <month> <day> <hour> <minute> <second>\n");
}

///
//Prints out a tm structure in a labelled format
//
//Parameters:
//	date: A pointer to the structure to print
void FormattedPrint(struct tm* date)
{
	
	printf("%d years %d months %d days %d hours %d minutes %d seconds\n", date->tm_year, date->tm_mon, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec);
}

///
//Parses an array of strings to a date
//The array of strings must each contain an integer representing a unit in time
//The first must be years- the last must be seconds
//
//Parameters:
//	dest: A pointer to the structure to store the date in
//	strings: The array of strings to parse
void ParseStrings(struct tm* dest, char* strings[])
{
	dest->tm_year = atoi(strings[0]);
	dest->tm_mon = atoi(strings[1]);
	dest->tm_mday = atoi(strings[2]);
	dest->tm_hour = atoi(strings[3]);
	dest->tm_min = atoi(strings[4]);
	dest->tm_sec = atoi(strings[5]);	
}

///
//Takes a tm struct and makes it a traditional date rather than since 1900
//with zero-indexed months
//
//Parameters:
//	date: A pointer to the date to make absolute
void MakeAbsoluteDate(struct tm* date)
{
	date->tm_year += 1900;
	date->tm_mon += 1;
}

int main(int argc, char* argv[])
{
	//Check input
	if(argc != 7)
	{
		Usage();
		return -1;
	}

	//Get current date
	time_t t = time(NULL);
	struct tm date = *localtime(&t);
	MakeAbsoluteDate(&date);

	//Parse birthday
	struct tm birthday;
	ParseStrings(&birthday, argv + 1);

	//Print both
	printf("Now it is ");
	FormattedPrint(&date);
	printf("Your birthday is ");
	FormattedPrint(&birthday);

	return 0;
}


