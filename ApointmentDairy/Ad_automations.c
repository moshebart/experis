/*
 * d_list_automations.c
 * Created on: Ap 19, 2015
 * Author: Moshe Bartal  
 * 	    
 */
#include"Ad_automations.h"
#define AUTOMATION 1
#define DEBUG 0
typedef struct Meeting {
	float m_strart_hour, m_end_hour;
	char* m_subject;
} Meeting;
typedef struct Node {

	Meeting* m_meet;
	struct Node *m_next, *m_prev;

} Node;
typedef struct List {

	Node m_head, m_tail;

} List;
typedef struct Ad {
	List* meetings;
	char m_date[11];
} Ad;
/* *****************************************************************************************/
bool autListInsert(size_t _size)
{
   printf("--------ListInsert()--------\n");
	Ad* ad = NULL;
	Meeting* mt = NULL;
	ADTErr er;
	float strart_hour = 6.01;
	int i;

	er = createAd(&ad);

	if (er == ERR_ALLOCATION_FAILED)
	{
		printf("createAd: ERR_ALLOCATION_FAILED\n");
		return false;
	}
	if (er == ERR_INPUT)
	{
		printf("createAd: ERR_INPUT\n");
		return false;
	}
	if (er == ERR_OK)
	{
		printf("createAd(): pass\n");

	}
	for(i=0;i<_size;++i)
	{
		er = createMeet(&mt);
		if (er == ERR_ALLOCATION_FAILED)
		{
			printf("createMeet: ERR_ALLOCATION_FAILED\n");
			return false;
		}
		if (er == ERR_INPUT)
		{
			printf("createMeet: fail ERR_INPUT\n");
			return false;
		}
		if (er == ERR_ILLIGAL_INPUT)
		{

			if(i!=8)
			{
			printf("createMeet: fail ERR_ILLIGAL_INPUT\n");
			return false;
			}
			else
			{
			printf("createMeet: pass ERR_ILLIGAL_INPUT\n");
			}
		}
		if (er == ERR_OK)
		{
			printf("createMeet(): pass\n");
			er = InsertMeet(ad, mt);
		}

		if (er == ERR_NO_AD)
		{
			printf("InsertMeet: fail ERR_NO_AD\n");
			return false;
		}
		if (er == ERR_NO_LIST)
		{
			printf("InsertMeet: fail ERR_NO_LIST\n");
			return false;
		}
		if (er == ERR_OK)
		{
			printf("InsertMeet(): pass\n");
			er = InsertMeet(ad, mt);
		}

	}
	printAd(ad);

	er = findMeet(ad, &mt, strart_hour);
	if(er == ERR_OK)
	{
		printf("findMeet(): pass\n");
		if(DEBUG)
		{
			printf("findMeet():\n Start hour: %.2f\nEnd our: %.2f\nSubject: %s\n\n", mt->m_strart_hour, mt->m_end_hour, mt->m_subject);
		}
	}
	er = removeMeet(ad, strart_hour);
	if (er == ERR_NO_AD)
	{
		printf("removeMeet:fail ERR_NO_AD\n");
		return false;
	}
	if (er == ERR_NO_LIST)
	{
		printf("removeMeet: fail ERR_NO_LIST\n");
		return false;
	}
	if (er == ERR_NO_SUCH_MEET)
	{
		printf("removeMeet: fail ERR_NO_SUCH_MEET\n");
		return false;
	}
	if (er == ERR_OK)
	{
		printf("removeMeet: pass\n");
	}
	printAd(ad);
	er = destroyAd(ad);
	if (er == ERR_NO_AD)
	{
		printf("destroyAd(): fail ERR_NO_AD\n");
		return false;
	}
	if (er == ERR_NO_LIST)
	{
		printf("destroyAd(): fail ERR_NO_LIST\n");
		return false;
	}
	if (er == ERR_OK)
	{
		printf("destroyAd(): pass\n");
		return true;
	}
	printAd(ad);
    return false;
}


