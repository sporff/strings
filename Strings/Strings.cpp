// ConsoleTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <map>



void ReverseString(char *cstr) {
	int strLen = strlen(cstr);
	char tChar = 0;
	char *pStrStart = &cstr[0], *pStrEnd = &cstr[strLen - 1];

	// some error checking bullshit here to make sure this loop will end

	while (pStrStart < pStrEnd) {
		tChar = *pStrStart;
		*pStrStart = *pStrEnd;
		*pStrEnd = tChar;

		pStrStart++;
		pStrEnd--;
	}
}




static int compar(const void *c1, const void *c2) {
	return	(*(const char *)c1 > *(const char *)c2) ? 1 : ((*(const char *)c1 < *(const char *)c2) ? -1 : 0);
}


bool IsAnagram_qsort(char *cstr1, char *cstr2) {
	bool retVal = false;

	// Get string lengths and make sure they're equal
	int strLen = strlen(cstr1);
	if (strLen != strlen(cstr2))
		return false;

	// Allocate new strings since qsort is destructive
	char *sortStr1 = NULL, *sortStr2 = NULL;
	sortStr1 = (char*)malloc(strLen + 1);
	sortStr2 = (char*)malloc(strLen + 1);

	// Copy strings and convert to lower case
	for (int i = 0; i < strLen; i++) {
		sortStr1[i] = tolower(cstr1[i]);
		sortStr2[i] = tolower(cstr2[i]);
	}
	sortStr1[strLen] = 0;				// null terminate
	sortStr2[strLen] = 0;

	// Sort
	qsort(sortStr1, strLen, 1, compar);
	qsort(sortStr2, strLen, 1, compar);

	// Save string compare value
	retVal = (strcmp(sortStr1, sortStr2) == 0);

	// Release memory
	free(sortStr1);
	free(sortStr2);

	return retVal;
}



bool IsAnagram_fill(char *cstr1, char *cstr2) {
	bool retVal = true;
	char strLen = strlen(cstr1);
	if (strLen != strlen(cstr2))
		return false;

	char *str1lower = new char[strLen + 1];
	char *strFill = new char[strLen + 1];

	for (int i = 0; i < strLen; i++) {
		str1lower[i] = tolower(cstr1[i]);
		strFill[i] = 0;
	}
	str1lower[strLen] = 0;
	strFill[strLen] = 0;



	// Ew
	for (int i = 0; i < strLen; i++) {
		char lc = tolower(cstr2[i]);
		for (int j = 0; j < strLen; j++) {
			if (lc == str1lower[j] && strFill[j] != lc) {
				// Found open spot matching char.
				strFill[j] = lc;
				//std::cout << "Found: " << lc << std::endl;
				break;
			}
			else if (j == strLen - 1) {
				// Char found that didn't match the 1st string. Break out of everything early?
				//std::cout << "Cannot find char: " << lc << std::endl;
				//retVal = false;
			}
		}
	}

	// see if there are any missing characters now
	for (int i = 0; i < strLen; i++) {
		if (strFill[i] == 0)
			return false;
	}
	//retVal = (strcmp(str1lower, strFill) == 0);

	delete[] strFill;
	delete[] str1lower;

	return retVal;
}




bool IsAnagram_map(char *cstr1, char *cstr2) {
	bool retVal = true;
	char lc = 0;
	std::map<char, int> counts;
	std::map<char, int>::iterator iter;


	int strLen = strlen(cstr1);
	if (strLen != strlen(cstr2))
		return false;

	for (int i = 0; i < strLen; i++) {
		lc = tolower(cstr1[i]);
		iter = counts.find(lc);
		if (iter != counts.end()) {
			iter->second++;		// already in map
		}
		else {
			counts.insert(std::pair<char, int>(lc, 1));		// not yet in map
		}

		lc = tolower(cstr2[i]);
		iter = counts.find(lc);
		if (iter != counts.end()) {
			iter->second--;		// already in map
		}
		else {
			counts.insert(std::pair<char, int>(lc, -1));	// not yet in map
		}
	}

	iter = counts.begin();
	while (iter != counts.end()) {
		if (iter->second != 0) {
			retVal = false;
			break;
		}

		iter++;
	}

	counts.clear();
	return retVal;
}



int main() {
	char cstr[] = "Reverse this stupid fucking string!";
	std::cout << "\"" << cstr << "\"" << std::endl;

	ReverseString(cstr);

	std::cout << "\"" << cstr << "\"" << std::endl;

	std::cout << "\n\n";

	char anaStr1[] = "creative! shit";
	char anaStr2[] = "hiT reatcIVES!";

	std::cout << "\nString sort method:" << std::endl;
	std::cout << "Is \'" << anaStr1 << "\' an anagram of \'" << anaStr2 << "\'? " << (IsAnagram_qsort(anaStr1, anaStr2) ? "Yes!" : "Hell no.") << std::endl;

	std::cout << "\nString fill method:" << std::endl;
	std::cout << "Is \'" << anaStr1 << "\' an anagram of \'" << anaStr2 << "\'? " << (IsAnagram_fill(anaStr1, anaStr2) ? "Yes!" : "Hell no.") << std::endl;

	std::cout << "\nString fill method:" << std::endl;
	std::cout << "Is \'" << anaStr1 << "\' an anagram of \'" << anaStr2 << "\'? " << (IsAnagram_map(anaStr1, anaStr2) ? "Yes!" : "Hell no.") << std::endl;

	std::cout << std::endl << "Press any key...\n";

	_getch();
	return 0;
}

