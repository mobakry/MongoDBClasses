#pragma once
#include <iostream>
#include "mongoc.h"

uint64_t calculateDateBeforeEpoch_Ms(struct tm* date) {
	//check date
	struct tm retdate = { 0 };

	retdate.tm_year = 1970;
	retdate.tm_mday = 1 - date->tm_mday;
	if (!(retdate.tm_mday >= 0)) {
		retdate.tm_mday = 31;
		retdate.tm_mday -= date->tm_mday;
		retdate.tm_mon--;
		if (!(retdate.tm_mon >= 0)) {
			retdate.tm_mon = 11;
			retdate.tm_year--;
		}
	}

	retdate.tm_mon -= date->tm_mon;
	if (!(retdate.tm_mon >= 0)) {
		retdate.tm_mon = 10;
		retdate.tm_year--;
	}

	retdate.tm_year -= (date->tm_year + (uint32_t)1900);

	retdate.tm_year += 70;
	retdate.tm_mday += 2;

	//printf("Time Before Epoch %d-%d-%d,\n", retdate.tm_year, retdate.tm_mon, retdate.tm_mday);

	return -mktime(&retdate);
}

time_t getDesiredDate() {
	time_t current_time;
	current_time = time(NULL);
	//cout << "current_time " <<current_time;

	/*
	* { "date" : ISODate("1906-12-09") } to the document.
	*/
	struct tm dateTm = { 0 };
	dateTm.tm_year = 6; /* years are 1900-based */
	dateTm.tm_mon = 11; /* months are 0-based */
	dateTm.tm_mday = 9;
	uint64_t date = 0;
	date = mktime(&dateTm);


	if (date == -1) {
		//printf("Failed Time Representation %d-%d-%d,\n", dateTm.tm_year + 1900, dateTm.tm_mon + 1, dateTm.tm_mday);  
		date = calculateDateBeforeEpoch_Ms(&dateTm);
	}
	return current_time;
}

bson_t* createDocument(const char* firstName, const char* lastName) {
	time_t date = getDesiredDate();
	bson_t* document;
	document = BCON_NEW(
		"date", BCON_DATE_TIME(date * 1000),

		"name",
		"{",
		"first", BCON_UTF8(firstName),
		"last", BCON_UTF8(lastName),
		"}",
		"languages",
		"[",
		BCON_UTF8("C++"), BCON_UTF8("java"), BCON_UTF8("C#"),
		"]",

		"degrees",
		"[",
		"{", "degree", BCON_UTF8("BA"), "school", BCON_UTF8("Cairo"), "}",
		"{", "degree", BCON_UTF8("PhD"), "school", BCON_UTF8("Cairo"), "}",
		"]"

	);

	return document;
}
