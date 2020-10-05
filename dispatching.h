// Header for dispatching.c.
#ifndef DISPATCHING
#define DISPATCHING
#include "main.h"

int getIsDispatching();
void setIsDispatching(int newIsDispatching);
enum check schedulingCheck;
enum check* getSchedulingCheck();
void* dispatching();

#endif