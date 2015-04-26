/**************************************************************************************
    Author: Izik Zur
    Creation date :      1.2.15
    Last modified date:  1.2.15
    Description : ADT General definitions.
***************************************************************************************/
#ifndef __ADTDEFS_H__
#define __ADTDEFS_H__

typedef enum
{
    /* General ADT Errors */
    ERR_OK = 0,
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_FREE_IS_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,
    ERR_INPUT,
    /* Vector Errors */

    /* Stack  Errors */
    ERR_STACK_BLABLABLA = 15,
      /* Queue  Errors */
    ERR_QUEUE_IS_EMPTY,
    ERR_QUEUE_IS_FULL,
    /* LinkedList  Errors */
    ERR_NO_DATA,
    ERR_NO_LIST,
    /* Bit Vector*/

    /*appointment dairy*/
    ERR_TIME_TAKEN,
    ERR_NO_AD,
    ERR_ILLIGAL_INPUT,
    ERR_NO_SUCH_MEET,
} ADTErr;

void HandleErr(ADTErr errNum, char *msg);

#endif /* __ADTDEFS_H__ */
