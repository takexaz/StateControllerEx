#pragma once
#include <Mebius.h>
#include "StateControllerExtension.h"
using namespace std;

extern vector<STX> gStateList;
static int STATEID = 0x7FFFFFFF;

int findTargetStateByName(string);
int regModState(void**, int);
int procModState(void);
void freeModState(void**);
