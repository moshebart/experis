/*
 * calendar.c
 * Created on: Ap 19, 2015
 * Author: Moshe Bartal
 * 	    
 */
#include "calendar.h"
#define HOUR_BUFFER_SIZE 7
#define SUBJECT_BUFFER_SIZE 50
#define DATE_BUFFER_SIZE 11
typedef struct List List;

#define DEBUG 0
#define AUTOMATION 0

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

/*****************************************************************************************/
List* ListCreate() {
	List* list = malloc(sizeof(List));

	if (list == NULL) {
		printf("ERR_ALLOCATION_FAILED\n");
	}

	list->m_head.m_next = &(list->m_tail);
	list->m_head.m_prev = NULL;

	list->m_tail.m_prev = &(list->m_head);
	list->m_tail.m_next = NULL;

	return list;
}
/*****************************************************************************************/
ADTErr createAd(Ad** _Ad) {
	*_Ad = malloc(sizeof(Ad));
	if (*_Ad == NULL) {
		return ERR_ALLOCATION_FAILED;
	}
	(*_Ad)->meetings = ListCreate();

	if(!AUTOMATION){
		printf("insert date\n");
	}
	if (fgets((*_Ad)->m_date, DATE_BUFFER_SIZE, stdin) == NULL) {
		return ERR_INPUT;
	}

	return ERR_OK;
}
/*****************************************************************************************/
float InputHour()
{
	char hour_buf[HOUR_BUFFER_SIZE];

	if (fgets(hour_buf, HOUR_BUFFER_SIZE, stdin) == NULL) {
		return ERR_INPUT;
	}
	return  atof(hour_buf);
}
/*****************************************************************************************/
ADTErr createMeet(Meeting** _mt) {
	char subject_buf[SUBJECT_BUFFER_SIZE];
	size_t len;
	*_mt = malloc(sizeof(Meeting));
	if (*_mt == NULL) {
		return ERR_ALLOCATION_FAILED;
	}
	if(!AUTOMATION)
	{
	printf("Insert start time in this format hour.minutes\nFor example 17.05\n");
	}
	(*_mt)->m_strart_hour = InputHour();
	if(!AUTOMATION)
	{
	printf("Insert end time\n");
	}
	(*_mt)->m_end_hour = InputHour();

	if((*_mt)->m_end_hour <= (*_mt)->m_strart_hour)
	{
		return ERR_ILLIGAL_INPUT;
	}
	if(!AUTOMATION)
	{
	printf("insert the meeting subject\n");
	}
	if (fgets(subject_buf, SUBJECT_BUFFER_SIZE, stdin) == NULL) {
		return ERR_INPUT;
	}
	len = strlen(subject_buf) + 1;
	(*_mt)->m_subject = malloc(sizeof(char) * (len));
	if ((*_mt)->m_subject == NULL) {
		return ERR_ALLOCATION_FAILED;
	}
	strncpy((*_mt)->m_subject, subject_buf, len);
	return ERR_OK;
}
/*****************************************************************************************/
void PopNode(Node* _prev, Node* _node, Node* _next)
{
 _prev->m_next = _next;
 _next->m_prev = _prev;
 free(_node);
}
/*****************************************************************************************/
ADTErr InsertMeet(Ad* _Ad, Meeting* _mt) {
	Node *node, *tmp;
	ADTErr er;
	if (!_Ad) {
		return ERR_NO_AD;
	}
	if (!(_Ad->meetings)) {
		return ERR_NO_LIST;
	}
	if(_Ad->meetings->m_head.m_next != &(_Ad->meetings->m_tail) )
	{
		if (_mt->m_end_hour <= _Ad->meetings->m_head.m_next->m_meet->m_strart_hour)
		{
			if(DEBUG)
			{
				printf("ListPushHead()\n");
			}
			er = ListPushHead(_Ad, _mt);
			return er;
		}

		if (_mt->m_strart_hour >= _Ad->meetings->m_tail.m_prev->m_meet->m_end_hour)
		{
			if(DEBUG)
			{
				printf("ListPushTail()\n");
			}
			er = ListPushTail(_Ad, _mt);
			return er;
		}
	}
	else
	{
		if(DEBUG)
		{
			printf("ListPushHead()\n");
		}
		er = ListPushHead(_Ad, _mt);
		return er;
	}


	//in case of value is between the tail and the head
	tmp = _Ad->meetings->m_head.m_next;
	while (tmp != &(_Ad->meetings->m_tail)) {

		if ((_mt->m_strart_hour > tmp->m_meet->m_end_hour)
				&& (_mt->m_end_hour < tmp->m_next->m_meet->m_strart_hour))
		{
			if(DEBUG)
			{
				printf("Push in the middle\n");
			}
			node = malloc(sizeof(Node));
			if (node == NULL) {
				return ERR_ALLOCATION_FAILED;
			}
			node->m_meet = _mt;
			PushNode(tmp, node, tmp->m_next);

			return ERR_OK;
		} else
		{
			if (((_mt->m_strart_hour < tmp->m_meet->m_end_hour)
					&& (_mt->m_strart_hour > tmp->m_meet->m_strart_hour))
					|| ((_mt->m_end_hour < tmp->m_meet->m_end_hour)
							&& (_mt->m_end_hour > tmp->m_meet->m_strart_hour)))
			{
				if (DEBUG) {
					printf("ERR_TIME_TAKEN\n");
				}
				return ERR_TIME_TAKEN;
			}
			tmp = tmp->m_next;
		}
	}

	if (DEBUG) {
		printf("ERR_TIME_TAKEN\n");
	}
	return ERR_TIME_TAKEN;
	return ERR_OK;
}
/*****************************************************************************************/
ADTErr removeMeet(Ad* _Ad, float _strart_hour) {
	Node* tmp;
	if (!_Ad) {
		return ERR_NO_AD;
	}
	if (!(_Ad->meetings)) {
		return ERR_NO_LIST;
	}
	if(_Ad->meetings->m_head.m_next != &(_Ad->meetings->m_tail) )
	{
		if (_Ad->meetings->m_head.m_next->m_meet->m_strart_hour == _strart_hour)
		{
			if(DEBUG)
			{
				printf("ListPopHead()\n");
			}
			PopNode(&(_Ad->meetings->m_head), _Ad->meetings->m_head.m_next, _Ad->meetings->m_head.m_next->m_next);
			return ERR_OK;
		}

		if (_Ad->meetings->m_tail.m_prev->m_meet->m_strart_hour == _strart_hour)
		{
			if(DEBUG)
			{
				printf("ListPopTail()\n");
			}
		    PopNode(_Ad->meetings->m_tail.m_prev->m_prev, _Ad->meetings->m_tail.m_prev, &(_Ad->meetings->m_tail));
			return ERR_OK;
		}
	}
	else
	{
		return ERR_NO_SUCH_MEET;
	}
	tmp = _Ad->meetings->m_head.m_next;

	while (tmp->m_next) {
		if(_strart_hour == tmp->m_meet->m_strart_hour)
		{
			PopNode(tmp->m_prev, tmp, tmp->m_next);
			return ERR_OK;
		}
		tmp = tmp->m_next;
	}
	return ERR_NO_SUCH_MEET;
}
/*****************************************************************************************/
ADTErr findMeet(Ad* _Ad, Meeting** _mt, float _strart_hour) {
	Node* tmp;
	if (!_Ad) {
		return ERR_NO_AD;
	}
	if (!(_Ad->meetings)) {
		return ERR_NO_LIST;
	}

	tmp = _Ad->meetings->m_head.m_next;

	while (tmp->m_next) {
		if(_strart_hour == tmp->m_meet->m_strart_hour)
		{
			*_mt = tmp->m_meet;
			return ERR_OK;
		}
		tmp = tmp->m_next;
	}
	return ERR_NO_SUCH_MEET;
}
/*****************************************************************************************/
ADTErr destroyAd(Ad* _Ad) {
	  Node *tmp, *prev;

	  if (!_Ad)
	  {
		return ERR_NO_AD;
	  }
	  if (!(_Ad->meetings))
	  {
		return ERR_NO_LIST;
	  }

	  tmp = _Ad->meetings->m_head.m_next;

	  while(tmp->m_next)
	  {
	    prev = tmp;
	    tmp = tmp->m_next;

	    free(prev);
	  }

	  free(_Ad->meetings);
	  free(_Ad);
	return ERR_OK;
}
/*****************************************************************************************/
void PushNode(Node* _prev, Node* _node, Node* _next) {
	_node->m_prev = _prev;
	_node->m_next = _next;

	_next->m_prev = _node;
	_prev->m_next = _node;
}
/*****************************************************************************************/
ADTErr ListPushHead(Ad* _Ad, Meeting* _mt) {
	if (!_Ad) {
		return ERR_NO_AD;
	}
	if (!(_Ad->meetings)) {
		return ERR_NO_LIST;
	}

	Node* node = malloc(sizeof(Node));
	if (node == NULL) {
		return ERR_ALLOCATION_FAILED;
	}

	node->m_meet = _mt;
	PushNode(&(_Ad->meetings->m_head), node, _Ad->meetings->m_head.m_next);

	return ERR_OK;
}
/*****************************************************************************************/
ADTErr ListPushTail(Ad* _Ad, Meeting* _mt) {
	if (!_Ad) {
		return ERR_NO_AD;
	}
	if (!(_Ad->meetings)) {
		return ERR_NO_LIST;
	}
		Node* node = malloc(sizeof(Node));
		if (node == NULL) {
			return ERR_ALLOCATION_FAILED;
		}

		node->m_meet = _mt;
		PushNode(_Ad->meetings->m_tail.m_prev, node, &(_Ad->meetings->m_tail));

		return ERR_OK;
	}
/*****************************************************************************************/
ADTErr printAd(Ad* _Ad) {
	Node* tmp;
	if (!_Ad) {
		return ERR_NO_AD;
	}
	if (!(_Ad->meetings)) {
		return ERR_NO_LIST;
	}

	tmp = _Ad->meetings->m_head.m_next;

	while (tmp->m_next) {
		printf("Start hour: %.2f\nEnd our: %.2f\nSubject: %s\n\n", tmp->m_meet->m_strart_hour, tmp->m_meet->m_end_hour, tmp->m_meet->m_subject);
		tmp = tmp->m_next;
	}
	return ERR_OK;
}

