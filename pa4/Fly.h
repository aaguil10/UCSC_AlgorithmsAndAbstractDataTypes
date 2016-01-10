//Alejandro Aguilar 
//fly.h

#ifndef _FLY_H_
#define _FLY_H_

#include "List.h"

typedef struct FlyObj* Fly;

Fly newFly(int n);
void freeFly(Fly* pF);
List returnList(Fly F, List L);


#endif

