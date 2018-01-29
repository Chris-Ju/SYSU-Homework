 #include <stdio.h>
 #include <string.h>
 #include "date.h"

 Date* CreateDate(int year, int month, int day)
 {
	Date *node = (Date*)malloc(sizeof(Date));
	SetDate(node, year, month, day);
	return node;
 } 
 void DestroyDate(Date** p)
 {
 	free(*p);
 	*p = NULL;
 }
 
 Date* CopyDate(const Date* date)
 {
 	Date *note = (Date *)malloc(sizeof(Date));
	memcpy(note, date, sizeof(Date));
	return note;
 }
 
 int GetYear(const Date* date)
 {
 	 return date->year;
 }
 
 int GetMonth(const Date* date)
 {
 	return date->month;
 }
 
 int GetDay(const Date* date)
 {
 	return date->day;
 }
 
 void SetYear(Date* date, int year)
 {
 	date->year = year;
 }
 
 void SetMonth(Date* date, int month)
 {
 	date->month = month;
 }
 
 void SetDay(Date* date, int day)
 {
 	date->day = day;
 }
 
 void SetDate(Date* date, int year, int month, int day)
 {
 	SetYear(date, year);
	SetMonth(date, month);
	SetDay(date, day);
 }
 
 char* GetDateString(const Date* date)
 {
 	char *dateString = (char *)malloc(sizeof(char)*20);
 	for(int i = 0;i < 20; i++)
	 dateString[i] = 0;
 	char str[5];
 	sprintf(str, "%d", date->year);
 	strcat(dateString, str);
 	dateString[4] = '-';
 	sprintf(str, "%d", date->month);
 	if(date->month < 10)
 	dateString[5] = '0';
 	strcat(dateString, str);
 	dateString[7] = '-';
 	sprintf(str, "%d", date->day);
 	if(date->day < 10)
 	dateString[8] = '0';
 	strcat(dateString, str);
 	return dateString;
 }
 
 void DestroyDateString(char** p)
 {
 	free(*p);
 	*p = NULL;
 }
 
 int dayOfMonth(int year, int month)
 {
 	int day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 	if(year % 100 != 0 && year % 4 ==0 || year % 400 == 0)
 		day[2]++;
 	return day[month];
 }
 
 void IncreaseDate(Date* date)
 {
 	if(date->day < dayOfMonth(date->year, date->month))
 	date->day++;
 	else
 	{
 		if(date->month == 12)
 		{
 			date->month = 1;
 			date->day = 1;
 			date->year++;
		 }
		 else
		 {
		 	date->month++;
		 	date->day = 1;
		 }
	 }
 }
 
 void DecreaseDate(Date* date)
 {
 	if(date->day > 1)
 	{
 		date->day--;
	 }
	 else
	 {
	 	if(date->month == 1)
	 	{
	 		date->year--;
	 		date->month = 12;
	 		date->day = 31;
		 }
		 else
		 {
		 	date->month--;
		 	date->day = dayOfMonth(date->year, date->month);
		 }
	 }
 }
 
 
 