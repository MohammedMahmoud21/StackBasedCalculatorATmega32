/***************************************************************************************/
/***************************************************************************************/
/**************************** Authors : Mohammed Elsayaad & Marwan nousir **************/
/**************************             Mohammed shokr & mostafa yousry ****************/
/**************************** Date : 9 June,2023         *******************************/
/**************************** Describtion: APP c implementation file     ***************/
/***************************************************************************************/
/***************************************************************************************/

/************************  Lib Includes ***************************************/
#include "StdTypes.h"
/************************* Lower Layers includes ********************************/
#include "Stack_Interface.h"
#include "Keypad_interface.h"
#include "LCD_interface.h"
/************************* Driver files Includes ************************/
#include "Calculator_Interface.h"
#include "Calculator_Private.h"
/*************************** Global Vars Definitions **************************/
static u8 Calc_u8UserInputArray[CALC_USER_ARRAY_SIZE];
static u8 Calc_u8PostfixFormulaArray[CALC_POSTFIX_ARRAY_SIZE];

/**************************  Extern functions implementation******************************/

void CALC_voidInit(void)
{
	Keypad_voidInit();
	HAL_LCD_voidInit();
}
void CALC_voidStart(void)
{
	u8 Local_u8Key = KEYPAD_NO_KEY;
	u8 Local_u8Iterator = 0; /* represent array index */
	s8 Local_s8TempIterator = 0; /* represent Temp array index */
	u32 Local_u32Result=0;
	u8 Local_u8PrevOp=0;		/*To hold operation which will be done on previous op and new op*/
	u8 Local_u8ProcessingFlag=0;
	u8 Local_u8PrevOpFlag=0;
	u8 Local_u8TempArray[14]={0};
	u8 Local_u8DisplayFlag=0; 
	while (1)
	{
		Local_u8Key = Keypad_u8GetKey();
		switch (Local_u8Key)
		{
			
		case '=':
			/**********************************************************************/
			/************* Make sure last element isn't ')' to add '.' ************/
			
			if(')' != Calc_u8UserInputArray[Local_u8Iterator-1])
			{
				Calc_u8UserInputArray[Local_u8Iterator]= '.';
				Local_u8Iterator++;
			}
			else
			{
				/***Nothing****/
			}
			/**********************************************************************/
			
			Calc_u8UserInputArray[Local_u8Iterator]='\0';
			Local_u8Iterator=0;       /*assign zero, so that if new numbers were entered by use it start for beginning in (Calc_u8userArray)*/
			/*Start processing*/
			if(1 == Local_u8DisplayFlag)
			{
				Calc_voidConvertToPost();              /*convert infix formula to postfix to make it easier to calc*/
				Local_u32Result = Calc_u32GetResult(); /*This API use Calc_u8PostfixArray to get the result*/
				Local_u8DisplayFlag =0;
			}
			else
			{
				
				/*User entered another '='*/
			}
			
			/**************************************************************/
			
			/******************** Display Part *************************/
			
			if(0 == Local_u8ProcessingFlag)
			{
				HAL_LCD_voidClearLCD();
				HAL_LCD_voidGoTo(LINE1,0);
				HAL_LCD_voidSendNumber(Local_u32Result);
				HAL_LCD_voidGoTo(LINE1,0);
				Local_u8ProcessingFlag=1;       /*Assign one to help in default state recognize if there were some chars on LCD or not*/
			}
			else
			{
				HAL_LCD_voidGoTo(LINE1,0);
				HAL_LCD_voidSendNumber(Local_u32Result);
				HAL_LCD_voidGoTo(LINE1,0);
			}
			break;
			
			
		case KEYPAD_NO_KEY:
			/*Don't do anything w8 user input*/
			break;
			
			
		default:
		
			/******Check if user want to use previous results in his calculation******/
			
			Local_u8DisplayFlag = 1;
			if(1 == Local_u8ProcessingFlag)
			{
				/*Clear LCD to start new operation*/
				
				Local_u8ProcessingFlag=0;
				if('0' <= Local_u8Key && '9' >= Local_u8Key)
				{
					/*User start new op, don't need to save last result*/
					HAL_LCD_voidClearLCD();
					Local_u8PrevOp = 0;
				}
				else if('=' == Local_u8Key)
				{
					/*Do nothing*/
				}
				else
				{
					
					/*User want to use previous calculations, so we need to add it to our (Calc_u8UserInputArray)*/
					HAL_LCD_voidClearLCD();
					Local_u8Iterator=0;
					if(0 == Local_u32Result)
					{
					
						Calc_u8UserInputArray[Local_u8Iterator] = Local_u32Result + '0';
						Local_u8Iterator++;
						Calc_u8UserInputArray[Local_u8Iterator] = '.';
						Local_u8Iterator++;
						Calc_u8UserInputArray[Local_u8Iterator] = Local_u8Key;
						Local_u8Iterator++;
					}
					else
					{
							while(Local_u32Result)
							{
								Local_u8TempArray[Local_s8TempIterator] = (Local_u32Result%10)+'0';
								Local_s8TempIterator++;
								Local_u32Result /=10;
							}
							
							Local_s8TempIterator--;
							
							while(Local_s8TempIterator >= 0)
							{
								Calc_u8UserInputArray[Local_u8Iterator] = Local_u8TempArray[Local_s8TempIterator];
								Local_u8Iterator++;
								Local_s8TempIterator--;
							}
							Calc_u8UserInputArray[Local_u8Iterator] = '.';
							Local_u8Iterator++;
							Calc_u8UserInputArray[Local_u8Iterator] = Local_u8Key; /*push operator in user array*/
							Local_u8Iterator++;
					}
					Local_u8PrevOpFlag=1;
					Local_s8TempIterator=0;
				}
			}
			else
			{
				/*Nothing*/
			}
			
			/********************* Put data in Array ****************************/
			
			
			if(CALC_USER_ARRAY_SIZE == Local_u8Iterator)
			{
				HAL_LCD_voidGoTo(LINE2,0); /*GoTo Line 2 first cell*/
				HAL_LCD_voidSendString("Can't write more than");
				HAL_LCD_voidGoTo(LINE3,0); /*GoTo Line 3 first cell*/
				HAL_LCD_voidSendNumber(Local_u8Iterator);
				HAL_LCD_voidSendString("number");
			}
			else
			{
				if(1 == Local_u8PrevOpFlag)
				{
					/*
					*if this condition is true this means user want to use previous result in an operation so its expected getting
						some thing like ANS +, this (+) we don't want to save it in the array.
					*Don't add this op to array as it affect last previous result
					*/
					Local_u8PrevOpFlag=0;
					HAL_LCD_voidSendString("ANS");
				}
				else
				{
					/****************************************************/
					/* To handle multi digits we will add '.' before operators like this,
						  54+77*9 -->  '5' '4' '.' '+' '7' '7' '.' '*' '9'
					*/
					/***************************************************/
					if(('0' <= Local_u8Key && '9' >= Local_u8Key)  || (')' == Calc_u8UserInputArray[Local_u8Iterator-1]))
					{
						Calc_u8UserInputArray[Local_u8Iterator] = Local_u8Key;
						Local_u8Iterator++;
					}
					else if('(' == Local_u8Key)
					{
						Calc_u8UserInputArray[Local_u8Iterator] = Local_u8Key;
						Local_u8Iterator++;
					}
					else
					{
						Calc_u8UserInputArray[Local_u8Iterator] = '.';
						Local_u8Iterator++;
						Calc_u8UserInputArray[Local_u8Iterator] = Local_u8Key;
						Local_u8Iterator++;
					}
				}
				HAL_LCD_voidSendChar(Local_u8Key);
			}
			
			
			break;
		}
	}
}





/**************************  Static functions implementation******************************/

static void Calc_voidConvertToPost(void)
{
	u8 Local_u8Char =0;			/*to hold user array value*/
	u8 Local_u8PopTemp =0;      /*to hold element from stack*/
	u8 Local_u8TopTemp =0;      /*to hold element at top of stack*/
	u8 Local_u8UserIterator=0; /*will be index of user array*/
	u8 Local_u8PostIterator=0; /*will be index of post array*/
	Stack_Error_t Local_Error=STK_OK;
	for(;Calc_u8UserInputArray[Local_u8UserIterator] != '\0';Local_u8UserIterator++)
	{
		Local_u8Char = Calc_u8UserInputArray[Local_u8UserIterator];
		switch (Local_u8Char)
		{
		case '(':
			Local_Error = Stack_Push(Local_u8Char);			
			if(STK_OK == Local_Error)
			{
				/*Continue no problem with stack*/
			}
			else
			{
				/*Print error mesaage on LCD*/
				HAL_LCD_voidGoTo(LINE4,0);
				HAL_LCD_voidSendString("Error with calc, Reset Calc");
				_delay_ms(1000);
				break;
			}
			break;
		case ')':
			Local_Error = Stack_Pop(&Local_u8PopTemp);
			if(STK_OK == Local_Error)
			{
				/*Continue no problem with stack*/
				while('(' != Local_u8PopTemp)
				{
					Calc_u8PostfixFormulaArray[Local_u8PostIterator] = Local_u8PopTemp;
					Local_u8PostIterator++;
					Local_Error = Stack_Pop(&Local_u8PopTemp);
					if(STK_OK == Local_Error || STK_EMPTY == Local_Error)
					{
						/*Continue no problem with stack*/
					}
					else
					{
						/*Print error mesaage on LCD*/
						HAL_LCD_voidGoTo(LINE4,0);
						HAL_LCD_voidSendString("Error with calc, Reset Calc");
						_delay_ms(1000);
						break;
					}
				}
			}
			else
			{
				/*Print error mesaage on LCD*/
				HAL_LCD_voidGoTo(LINE4,0);
				HAL_LCD_voidSendString("Error with calc, Reset Calc");
				_delay_ms(1000);
				break;/*break the for loop*/
			}
			
			break;
			
		case '+':
		case '*':
		case '/':
			Stack_ReadTop(&Local_u8TopTemp);
			while((STK_EMPTY !=Stack_IsEmpty()) && (Calc_u8GetPrecedence(Local_u8TopTemp) >= Calc_u8GetPrecedence(Local_u8Char)))
			{
				Stack_Pop(&Local_u8PopTemp);
				Calc_u8PostfixFormulaArray[Local_u8PostIterator] =Local_u8PopTemp; 
				Local_u8PostIterator++;
				Stack_ReadTop(&Local_u8TopTemp);
			}
			Stack_Push(Local_u8Char);
			break;
		default:
			//Stack_Pop(&Local_u8PopTemp);
			Calc_u8PostfixFormulaArray[Local_u8PostIterator] =Local_u8Char;
			Local_u8PostIterator++;
			break;
		}
	}
	while((STK_EMPTY !=Stack_IsEmpty()))
	{
		Stack_Pop(&Local_u8PopTemp);
		Calc_u8PostfixFormulaArray[Local_u8PostIterator] =Local_u8PopTemp;
		Local_u8PostIterator++;
		Stack_ReadTop(&Local_u8TopTemp);
	}
	Calc_u8PostfixFormulaArray[Local_u8PostIterator] = '\0';
}

static u8	Calc_u8GetPrecedence(u8 Copy_u8Char)
{
	u8 Local_u8RetVal=0;
	switch (Copy_u8Char)
	{
	case '*': Local_u8RetVal = 3; /* 3 is the higher value here, which means higher precedence */
		break;
	case '/': Local_u8RetVal = 3;
		break;
	case '+': Local_u8RetVal = 2;
		break;	
	}
	
	return (Local_u8RetVal);
}

static u32  Calc_u32GetResult(void)
{
	u32 Local_u32Result=0;
	u8 Local_u8PostIterator=0;
	u8 Local_u8Char=0;
	u32 Local_u32PopChar=0;
	u32 Local_u32First=0;
	u32 Local_u32Second=0;
	u32 Local_u32DotCounter=0;
	u32 Local_u32TensCount=1;
	u8 Local_u8OpFlag=0;
	for(;Calc_u8PostfixFormulaArray[Local_u8PostIterator];Local_u8PostIterator++)
	{
		Local_u8Char = Calc_u8PostfixFormulaArray[Local_u8PostIterator];
		
		if('0' <= Local_u8Char && '9' >= Local_u8Char)
		{
			Stack32_Push((u32)(Local_u8Char -'0'));
		}
		else if('.' == Local_u8Char)
		{
			Stack32_Push((u32)Local_u8Char);
		}
		else
		{
			Local_u8OpFlag=1;
			for(;(Local_u32DotCounter < 3) && (STK_EMPTY != Stack32_IsEmpty());)
			{
				Stack32_Pop(&Local_u32PopChar);
				if('.' == Local_u32PopChar)
				{
					Local_u32DotCounter++;
					Local_u32TensCount=1;
				}
				else
				{
					if(1 == Local_u32DotCounter)
					{
						/*First number*/
						Local_u32First += (Local_u32PopChar * Local_u32TensCount);
						Local_u32TensCount *=10;
						
					}
					else
					{
						/*Second Number*/
						Local_u32Second += (Local_u32PopChar*Local_u32TensCount);
						Local_u32TensCount *=10;
					}
				}
			}
			if (3 == Local_u32DotCounter)
			{
				Stack32_Push('.');
			}
			else
			{
				/*Nothing*/
			}
			switch(Local_u8Char)
			{
			case '+':
				Stack32_Push(Local_u32First+Local_u32Second);
				break;
			case '*':
				Stack32_Push(Local_u32First*Local_u32Second);
				break;
			case '/':
				Stack32_Push(Local_u32Second/Local_u32First);
				break;
			}
			Stack32_Push('.');
			Local_u32First =0;
			Local_u32Second=0;
			Local_u32DotCounter=0;
		}
	}
	if (0 == Local_u8OpFlag)
	{
		/*User entered number only without any operator ex: 60*/
		Stack32_Pop(&Local_u32PopChar); /*This one for taking '.' out before entering loop*/
		while (STK_EMPTY != Stack32_IsEmpty())
		{
			Stack32_Pop(&Local_u32PopChar);
			Local_u32Result += (Local_u32PopChar * Local_u32TensCount);
			Local_u32TensCount *= 10;
		}
	}
	else
	{
		Stack32_Pop(&Local_u32Result);
		Stack32_Pop(&Local_u32Result);
	}
	return (Local_u32Result);
}