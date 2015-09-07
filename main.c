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

///
//Calculates the number of days in the current month of a struct tm.

int CalculateDaysInMonth(struct tm* date)
{
	switch(date->tm_mon)
	{
	case 1:
		return 31; break;
	case 2:
		return (date->tm_year % 4 == 0) ?
			 29 : 28; break;
	case 3: 
		return 31; break;
	case 4: 
		return 30; break;
	case 5:
		return 31; break;
	case 6:
		return 30; break;
	case 7:
		return 31; break;
	case 8:
		return 31; break;
	case 9:
		return 30; break;
	case 10:
		return 31; break;
	case 11:
		return 30; break;
	case 12:
		return 31; break;
	default:
		return 0;
	}
}

///
//Subtracts date B from date A (A - B) and stores the result in the destination
//
//Parameters:
//	dest: The destination to store the resulting timespan
//	dateA: The date which we are subtracting from
//	dateB: The date which we are subtracting
void SubtractDates(struct tm* dest, struct tm* dateA, struct tm* dateB)
{

	if(dateA->tm_sec < dateB->tm_sec)
	{
		dateA->tm_sec += 60;
		dateA->tm_min--;
	}
	dest->tm_sec = dateA->tm_sec - dateB->tm_sec;



	if(dateA->tm_min < dateB->tm_min)
	{
		dateA->tm_min += 60;
		dateA->tm_hour--;
	}
	dest->tm_min = dateA->tm_min - dateB->tm_min;


	if(dateA->tm_hour < dateB->tm_hour)
	{
		dateA->tm_hour += 24;
		dateA->tm_mday--;
	}
	dest->tm_hour = dateA->tm_hour - dateB->tm_hour;

	if(dateA->tm_mday < dateB->tm_mday)
	{
		dateA->tm_mday += CalculateDaysInMonth(dateA);
		dateA->tm_mon--;
	}
	dest->tm_mday = dateA->tm_mday - dateB->tm_mday;

	if(dateA->tm_mon < dateB->tm_mon)
	{
		dateA->tm_mon += 12;
		dateA->tm_year--;
	}
	dest->tm_mon = dateA->tm_mon - dateB->tm_mon;
	dest->tm_year = dateA->tm_year - dateB->tm_year;
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

	//Find the difference
	double differenceInSeconds = difftime(mktime(&date), mktime(&birthday));
	printf("The difference in seconds is %f\n", differenceInSeconds);
	
	struct tm difference;	
	SubtractDates(&difference, &date, &birthday);
	printf("The difference is ");
	FormattedPrint(&difference);

	return 0;
}


