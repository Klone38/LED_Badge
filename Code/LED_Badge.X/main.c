/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    ClearDisplay();
    
    ROW_EN = 0;     //turn on display
    ROW_SEL = 1;    //set select to high
    
    //Pulse the clock twice to set row A high
    ROW_CLK = 1;    
    ROW_CLK = 0;
    ROW_CLK = 1;    
    ROW_CLK = 0;
    
    int rowCount = 2;
    

    while(1)
    {
        ROW_EN = 1;     //Disable screen
        
        // Populate the columns
        for(int i =0;i<8;i++)
        {
            
           
            COL_SEL = 0;
            
            
            COL_CLK = 1;
            COL_CLK = 0;

            //__delay_us(100000); 
            
        }
        // Enable screen
        ROW_EN = 0;
        
        // Display each row for this ammount of time
        __delay_us(1000); 
        
        ROW_EN = 1;     //Disable screen
        
        // Advance to the next row
        if(rowCount >= 6)
        {
            ROW_SEL = 1;

            rowCount = 0;
        }
        
        ROW_CLK = 1;    
        ROW_CLK = 0;
        
        rowCount++;

        
        
    }

}

