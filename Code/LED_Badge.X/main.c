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
    InitFrameAnimation();
    ReadyDisplay();

    int counter = 0;
    
    while(1)
    {
        ROW_EN = 1;     //Disable screen
        
        PopulateColumns();
        
        ROW_EN = 0;     // Enable screen
        // Display each row for this amount of time
        __delay_us(500); 
        
        ROW_EN = 1;     //Disable screen
        
        
        AdvanceRow();
        
        counter++;
        
        if(counter > 500){
            AdvanceAnimationFrame();
            counter = 0;
        }
        
    }

}

