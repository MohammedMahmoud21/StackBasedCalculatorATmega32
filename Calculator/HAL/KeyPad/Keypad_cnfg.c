#include "StdTypes.h"
#include "Keypad_cnfg.h"
#include "DIO_Interface.h"


u8 Keypad_Array[KEYPAD_ROWS][KEYPAD_COLUM] =
{
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3',')'},
	{'(','0','=','+'}
};

u8 Keypad_Rows[KEYPAD_ROWS]   = {PC5,PC4,PC3,PC2};
u8 Keypad_Colum[KEYPAD_COLUM] = {PD7,PD6,PD5,PD3};