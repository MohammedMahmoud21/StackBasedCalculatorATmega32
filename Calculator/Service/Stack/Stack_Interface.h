/***************************************************************************************/
/***************************************************************************************/
/**************************** Authors : Mohammed Elsayaad & Marwan nousir **************/
/**************************             Mohammed shokr & mostafa yousry ****************/
/**************************** Date : 9 June,2023         *******************************/
/**************************** Describtion: Stack header interface file     *************/
/***************************************************************************************/
/***************************************************************************************/


#ifndef STACK_INTERFACE_H_
#define STACK_INTERFACE_H_


#define STACK_SIZE	 50
#define STACK_32SIZE 20	
#define STACK_EMPTY  0
typedef enum
{
	STK_FULL,
	STK_EMPTY,
	STK_OK,
	STK_NOK
}Stack_Error_t;

/******************** Stack 8 bit declerations **************************************/
Stack_Error_t Stack_Push(u8 Copy_u8Data);
Stack_Error_t Stack_Pop(u8 *Copy_u8Data);
Stack_Error_t Stack_ReadTop(u8 *Copy_u8Data);
Stack_Error_t Stack_IsEmpty(void);

/******************** Stack 32 bit declerations **************************************/

Stack_Error_t Stack32_Push(u32 Copy_u32Data);
Stack_Error_t Stack32_Pop(u32 *Copy_u32Data);
Stack_Error_t Stack32_ReadTop(u32 *Copy_u32Data);
Stack_Error_t Stack32_IsEmpty(void);

#endif /* STACK_INTERFACE_H_ */