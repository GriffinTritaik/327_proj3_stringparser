/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace KP_StringParserClass;
const int SIZE = 200;

		//dont forget to initialize member variables
	StringParserClass::StringParserClass(void){
		pStartTag = new char[SIZE];
		pEndTag = new char[SIZE];
		areTagsSet = false;
	}

		//call cleanup to release any allocated memory
	StringParserClass::~StringParserClass(void){
		cleanup();
		areTagsSet = false;
	}

		//these are the start tag and the end tags that we want to find,
		//presumably the data of interest is between them, please make a
		//COPY of what pStartTag and pEndTag point to.  In other words
		//DO NOT SET pStartTag = pStart
		//returns:
		//SUCCESS
		//ERROR_TAGS_NULL if either pStart or pEnd is null
	int StringParserClass::setTags(const char *pStart, const char *pEnd){
		if (pStart == NULL || pEnd == NULL){
			return ERROR_TAGS_NULL;
		}

		int startLen = strlen(pStart);
		int endLen = strlen(pEnd);

		pStartTag = new char[startLen+1];
		pEndTag = new char[endLen+1];

		strncpy(pStartTag, pStart, startLen);
		strncpy(pEndTag, pEnd, endLen);

		areTagsSet = true;

		return SUCCESS;
	}

		//First clears myVector
		//going to search thru pDataToSearchThru, looking for info bracketed by
		//pStartTag and pEndTag, will add that info only to myVector
		//returns
		//SUCCESS  finished searching for data between tags, results in myVector (0 or more entries)
		//ERROR_TAGS_NULL if either pStart or pEnd is null
		//ERROR_DATA_NULL pDataToSearchThru is null
	int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, std::vector<std::string> &myVector){
		myVector.clear();
		if (areTagsSet == false){
			return ERROR_TAGS_NULL;
		}
		if (pDataToSearchThru == NULL){
			return ERROR_DATA_NULL;
		}

		int pDataToSearchThruSize = strlen(pDataToSearchThru);
		char *SST = pDataToSearchThru;
		char *EST = pDataToSearchThru + pDataToSearchThruSize;
		char *SET = pDataToSearchThru;
		char *EET = pDataToSearchThru + pDataToSearchThruSize;

		std::string toAdd = "";

		while (findTag(pStartTag, pDataToSearchThru, EST) == SUCCESS){
			if(findTag(pEndTag, SET, EET) == FAIL){
				return SUCCESS;
			}
			if(findTag(pEndTag, SET, EET) == SUCCESS){
				while (EST != SET){
					toAdd += *EST;
					EST++;
				}
				myVector.push_back(toAdd);
				toAdd = "";
				pDataToSearchThru = EET;
				pDataToSearchThruSize = strlen(pDataToSearchThru);
				EST = pDataToSearchThru + pDataToSearchThruSize;
				EET = pDataToSearchThru + pDataToSearchThruSize;
				SET = pDataToSearchThru;
				SST = pDataToSearchThru;
			}
		}

		return SUCCESS;
	}


	void StringParserClass::cleanup(){
		if(pStartTag) {
			delete[] (pStartTag);
			pStartTag = 0;
		}
		if(pEndTag) {
			delete[] (pStartTag);
			pEndTag = 0;
		}

	}

		//Searches a string starting at pStart for pTagToLookFor
		//returns:
		//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
		//FAIL did not find pTagToLookFor and pEnd points to 0
		//ERROR_TAGS_NULL if either pStart or pEnd is null
	int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd){

		if (pStart == NULL || pEnd == NULL){
			return ERROR_TAGS_NULL;
		}

		int lenArray = strlen(pTagToLookFor);

		while (pStart != pEnd){
			if (*pStart == *pTagToLookFor){
				if(strncmp(pStart, pTagToLookFor, lenArray) == 0){
					pEnd = pStart + lenArray;
					return SUCCESS;
				}
			}
			pStart++;
		}
		return FAIL;
	}

