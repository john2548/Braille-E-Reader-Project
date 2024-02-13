#ifndef CHAR_C_H
#define CHAR_C_H

#include "pin.h"

typedef struct {
	char mappedChar;
	Pin pinOut[6];
} Char_c;

Char_c createChar(char cVal, bool pinVals[6]) {
	Char_c newChar;

	newChar.mappedChar = cVal;
	for (int i = 0; i < 6; ++i) {
		newChar.pinOut[i].raised = pinVals[i];
	}

	return newChar;
}

#endif // !CHAR_C_H
