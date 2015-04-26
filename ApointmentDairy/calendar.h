/*
 * calendar.h
 * Created on: Ap 19, 2015
 * Author: Moshe Bartal
 * 	    
 */

#ifndef __CALENDAR_H__
#define __CALENDAR_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ADTDefs.h"

typedef struct Meeting Meeting;
typedef struct Node Node;
typedef struct List List;
typedef struct Ad Ad;
//todo why Ad_automations.h file can resolved pointer type only when definitions are in calendar.h or there

List* ListCreate();
ADTErr createAd(Ad** _Ad);
float InputHour();
ADTErr createMeet(Meeting** _mt);
void PushNode(Node* _prev, Node* _node, Node* _next);
ADTErr ListPushHead(Ad* _Ad, Meeting* _mt);
ADTErr ListPushTail(Ad* _Ad, Meeting* _mt);
ADTErr InsertMeet(Ad* _Ad, Meeting* _mt);
ADTErr removeMeet(Ad* _Ad, float _strart_hour);
ADTErr findMeet(Ad* _Ad, Meeting** _mt, float _strart_hour);
ADTErr destroyAd(Ad* _Ad);
ADTErr printAd(Ad* _Ad);
#endif /* __CALENDAR_H__*/
