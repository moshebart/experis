/*
 * list.c
 * Created on: Ap 19, 2015
 * Author: Moshe Bartal  
 * 	    
 */
#include "stdlib.h"
#include "ADTDefs.h"
#include "calendar.h"
#include <stdbool.h>

#include "Ad_automations.h"

int main()
{	
	int cont = 1;			// trigger to stop loop	
	unsigned int option;
	Ad* ad = NULL;
	Meeting* mt = NULL;
	ADTErr er = 0;
	float start_hour;
	while (cont) {
		printf("Choose an option: \n");
		printf("1:Create Ad.\n");
		printf("2:Create Meeting.\n");
		printf("3:Insert Meeting.\n");
		printf("4:Remove appointment from Ad (by begin hour).\n");
		printf("5:Find appointment in Ad (by begin hour).\n");
		printf("6:Destroy Ad.\n");
		printf("7:Print Ad.\n");
		printf("8:For exit.\n");
		scanf("%d", &option);
		getchar();

		switch (option) {
			case 1:
				er = createAd(&ad);
				break;
			case 2:
				er = createMeet(&mt);
				break;
			case 3:
				er = InsertMeet(ad, mt);
				break;
			case 4:	
				printf("Insert the meet start time\n");
				start_hour = InputHour();
				er = removeMeet(ad, start_hour);
				break;
			case 5:
				printf("Insert the meet start time\n");
				start_hour = InputHour();
				er = findMeet(ad, &mt, start_hour);
				break;	
			case 6:	
				er = destroyAd(ad);
				break;
			case 7:	
				er = printAd(ad);
				break;
			case 8:	
				cont = 0;
				break;
			default: cont = 0;	break;
		}
	}
	return 0;
}


