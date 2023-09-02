/***************************************************************************************/
/***************************************************************************************/
/**************************** Authors : Mohammed Elsayaad & Marwan nousir **************/
/****************************           Mohammed shokr & mostafa yousry ****************/
/**************************** Date : 9 June,2023         *******************************/
/**************************** Describtion: Stack c implementation     ******************/
/***************************************************************************************/
/***************************************************************************************/

#include "StdTypes.h"
#include "Utiles.h"

#include "Stack_Interface.h"
#include "Stack_Private.h"
#include "Stack_Config.h"
/****************************** Stack Array Definition ***************************/
#if  STACK_SIZE_OPTIONS == STACK_32IT_8BIT_UNIT


/******8 bit stack********/
static u8 Stack_u8Array[STACK_SIZE];
static u8 Stack_u8StackPointer; /* Point to current location to push data in it */
/******32 bit stack********/
static u32 Stack_u32Array[STACK_32SIZE];
static u32 Stack_u32StackPointer; /* Point to current location to push data in it */

#elif STACK_SIZE_OPTIONS == STACK_8BIT_UNIT

static u8 Stack_u8Array[STACK_SIZE];
static u8 Stack_u8StackPointer; /* Point to current location to push data in it */

#elif STACK_SIZE_OPTIONS == STACK_32BIT_UNIT

static u32 Stack_u32Array[STACK_32SIZE];
static u32 Stack_u32StackPointer; /* Point to current location to push data in it */

#else
	#error "Fault in Stack Configutation"
#endif


#if  STACK_SIZE_OPTIONS == STACK_32IT_8BIT_UNIT

/***********************Stack 8 bit APIs implementation**************************************/

Stack_Error_t Stack_Push(u8 Copy_u8Data)
{
	Stack_Error_t Local_Error=STK_OK;
	if(STACK_SIZE < Stack_u8StackPointer)
	{
		Local_Error = STK_FULL;
	}
	else
	{
		Stack_u8Array[Stack_u8StackPointer] = Copy_u8Data;
		Stack_u8StackPointer++;
	}
	
	return (Local_Error);
}
Stack_Error_t Stack_Pop(u8 *Copy_u8Data)
{
	Stack_Error_t Local_Error=STK_OK;
	if(STACK_EMPTY == Stack_u8StackPointer)
	{
		Local_Error = STK_EMPTY;
	}
	else if(NULL_PTR == Copy_u8Data)
	{
		Local_Error = STK_NOK; /*Null pointer passed*/
	}
	else
	{
		/* To make pointer point to top location to pop data from 
			 As in our assumption stack pointer is point always to empty location to be
			filled next.
		*/
		Stack_u8StackPointer--;
		*Copy_u8Data = Stack_u8Array[Stack_u8StackPointer];
	}
	return (Local_Error);
}

Stack_Error_t Stack_ReadTop(u8 *Copy_u8Data)
{
	Stack_Error_t Local_Error = STK_OK;
	if(NULL_PTR == Copy_u8Data)
	{
		Local_Error = STK_NOK;
	}
	else
	{
		if(STACK_EMPTY == Stack_u8StackPointer)
		{
			/*Can't read*/
			Local_Error = STK_EMPTY;
		}
		else
		{
			*Copy_u8Data = Stack_u8Array[Stack_u8StackPointer-1];
		}
		
	}
	return (Local_Error);
}
Stack_Error_t Stack_IsEmpty(void)
{
	Stack_Error_t Local_Error = STK_OK;
	if(STACK_EMPTY == Stack_u8StackPointer)
	{
		Local_Error = STK_EMPTY;
	}
	else
	{
		/*Nothing*/
	}
	
	
	return (Local_Error);
}

/***********************Stack 32 bit APIs implementation**************************************/

Stack_Error_t Stack32_Push(u32 Copy_u32Data)
{
	Stack_Error_t Local_Error=STK_OK;
	if(STACK_32SIZE < Stack_u32StackPointer)
	{
		Local_Error = STK_FULL;
	}
	else
	{
		Stack_u32Array[Stack_u32StackPointer] = Copy_u32Data;
		Stack_u32StackPointer++;
	}
	
	return (Local_Error);
}
Stack_Error_t Stack32_Pop(u32 *Copy_u32Data)
{
	Stack_Error_t Local_Error=STK_OK;
	
	
	if(STACK_EMPTY == Stack_u32StackPointer)
	{
		Local_Error = STK_EMPTY;
	}
	else if(NULL_PTR == Copy_u32Data)
	{
		Local_Error = STK_NOK; /*Null pointer passed*/
	}
	else
	{
		/* To make pointer point to top location to pop data from 
			 As in our assumption stack pointer is point always to empty location to be
			filled next.
		*/
		Stack_u32StackPointer--;
		*Copy_u32Data = Stack_u32Array[Stack_u32StackPointer];
	}
	return (Local_Error);
}
Stack_Error_t Stack32_ReadTop(u32 *Copy_u32Data)
{
	Stack_Error_t Local_Error = STK_OK;
	if(NULL_PTR == Copy_u32Data)
	{
		Local_Error = STK_NOK;
	}
	else
	{
		if(STACK_EMPTY == Stack_u32StackPointer)
		{
			/*Can't read*/
			Local_Error = STK_EMPTY;
		}
		else
		{
			*Copy_u32Data = Stack_u32Array[Stack_u32StackPointer-1];
		}
		
	}
	return (Local_Error);
}
Stack_Error_t Stack32_IsEmpty(void)
{
	Stack_Error_t Local_Error = STK_OK;
	if(STACK_EMPTY == Stack_u32StackPointer)
	{
		Local_Error = STK_EMPTY;
	}
	else
	{
		/*Nothing*/
	}
	
	
	return (Local_Error);
}

#elif  STACK_SIZE_OPTIONS == STACK_8BIT_UNIT

/***********************Stack 8 bit APIs implementation**************************************/

Stack_Error_t Stack_Push(u8 Copy_u8Data)
{
	Stack_Error_t Local_Error=STK_OK;
	if(STACK_SIZE < Stack_u8StackPointer)
	{
		Local_Error = STK_FULL;
	}
	else
	{
		Stack_u8Array[Stack_u8StackPointer] = Copy_u8Data;
		Stack_u8StackPointer++;
	}
	
	return (Local_Error);
}
Stack_Error_t Stack_Pop(u8 *Copy_u8Data)
{
	Stack_Error_t Local_Error=STK_OK;
	if(STACK_EMPTY == Stack_u8StackPointer)
	{
		Local_Error = STK_EMPTY;
	}
	else if(NULL_PTR == Copy_u8Data)
	{
		Local_Error = STK_NOK; /*Null pointer passed*/
	}
	else
	{
		/* To make pointer point to top location to pop data from 
			 As in our assumption stack pointer is point always to empty location to be
			filled next.
		*/
		Stack_u8StackPointer--;
		*Copy_u8Data = Stack_u8Array[Stack_u8StackPointer];
	}
	return (Local_Error);
}

Stack_Error_t Stack_ReadTop(u8 *Copy_u8Data)
{
	Stack_Error_t Local_Error = STK_OK;
	if(NULL_PTR == Copy_u8Data)
	{
		Local_Error = STK_NOK;
	}
	else
	{
		if(STACK_EMPTY == Stack_u8StackPointer)
		{
			/*Can't read*/
			Local_Error = STK_EMPTY;
		}
		else
		{
			*Copy_u8Data = Stack_u8Array[Stack_u8StackPointer-1];
		}
		
	}
	return (Local_Error);
}
Stack_Error_t Stack_IsEmpty(void)
{
	Stack_Error_t Local_Error = STK_OK;
	if(STACK_EMPTY == Stack_u8StackPointer)
	{
		Local_Error = STK_EMPTY;
	}
	else
	{
		/*Nothing*/
	}
	
	
	return (Local_Error);
}

#elif  STACK_SIZE_OPTIONS == STACK_32BIT_UNIT

/***********************Stack 32 bit APIs implementation**************************************/
Stack_Error_t Stack32_Push(u32 Copy_u32Data)
{
	Stack_Error_t Local_Error=STK_OK;
	if(STACK_SIZE < Stack_u8StackPointer)
	{
		Local_Error = STK_FULL;
	}
	else
	{
		Stack_u32Array[Stack_u32StackPointer] = Copy_u32Data;
		Stack_u32StackPointer++;
	}
	
	return (Local_Error);
}
Stack_Error_t Stack32_Pop(u32 *Copy_u32Data)
{
	Stack_Error_t Local_Error=STK_OK;
	
	
	if(STACK_EMPTY == Stack_u32StackPointer)
	{
		Local_Error = STK_EMPTY;
	}
	else if(NULL_PTR == Copy_u32Data)
	{
		Local_Error = STK_NOK; /*Null pointer passed*/
	}
	else
	{
		/* To make pointer point to top location to pop data from 
			 As in our assumption stack pointer is point always to empty location to be
			filled next.
		*/
		Stack_u32StackPointer--;
		*Copy_u32Data = Stack_u32Array[Stack_u32StackPointer];
	}
	return (Local_Error);
}
Stack_Error_t Stack32_ReadTop(u32 *Copy_u32Data)
{
	Stack_Error_t Local_Error = STK_OK;
	if(NULL_PTR == Copy_u32Data)
	{
		Local_Error = STK_NOK;
	}
	else
	{
		if(STACK_EMPTY == Stack_u32StackPointer)
		{
			/*Can't read*/
			Local_Error = STK_EMPTY;
		}
		else
		{
			*Copy_u32Data = Stack_u32Array[Stack_u32StackPointer-1];
		}
		
	}
	return (Local_Error);
}
Stack_Error_t Stack32_IsEmpty(void)
{
	Stack_Error_t Local_Error = STK_OK;
	if(STACK_EMPTY == Stack_u32StackPointer)
	{
		Local_Error = STK_EMPTY;
	}
	else
	{
		/*Nothing*/
	}
	
	
	return (Local_Error);
}

#else
	#error "ERROR in Stack Config"
	
#endif