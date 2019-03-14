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

StringParserClass::StringParserClass() {
	//*pStartTag = new char;
	//*pEndTag = new char();
	areTagsSet = false;
}

int KP_StringParserClass::StringParserClass::setTags(const char *pStart, const char *pEnd) {
	return 0;
}

int KP_StringParserClass::StringParserClass::getDataBetweenTags
		(char *pDataToSearchThru, std::vector<std::string> &myVector){
	return 0;
}
