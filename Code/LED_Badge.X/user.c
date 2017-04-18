/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"
#include "system.h"



/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Enable interrupts */
    ANSEL = 0b00000000;
    
    TRISA = 0b11111111;
    TRISC = 0b11000000;

    
}

void ClearDisplay()
{
    //Rows control the positive pins
    //Cols control the negative pins
    
    ROW_EN = 1; //turn off display
    
    ROW_SEL = 0;
    COL_SEL = 1;
    
    for(int i = 0;i<8;i++){
        ROW_CLK = 1;
        COL_CLK = 1;
        __delay_us(10);
                
        ROW_CLK = 0;
        COL_CLK = 0;
    }
    
    ROW_EN = 0; 
    
}

