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
#include "data.h"



bool buf[6][8] = {
    0,0,1,0,0,1,0,0,
    0,0,1,0,0,1,0,0,
    0,0,0,0,0,0,0,0,
    0,1,0,0,0,0,1,0,
    0,0,1,1,1,1,0,0,
    0,0,0,0,0,0,0,0
};

const unsigned int test[] = {36, 36, 0, 66, 60, 128, 36, 36, 0, 66, 60, 64, 36, 
                             36, 0, 66, 60, 32, 36, 36, 0, 66, 60, 16, 36, 36, 
                             0, 66, 60, 8, 36, 36, 0, 66, 60, 4, 36, 36, 0, 66, 
                             60, 2, 36, 36, 0, 66, 60, 1, 36, 36, 0, 66, 61, 0, 
                             36, 36, 0, 67, 60, 0, 36, 36, 1, 66, 60, 0, 36, 37,
                             0, 66, 60, 0, 37, 36, 0, 66, 60, 0, 38, 36, 0, 66, 
                             60, 0, 36, 36, 0, 66, 60, 0, 44, 36, 0, 66, 60, 0, 
                             52, 36, 0, 66, 60, 0, 36, 36, 0, 66, 60, 0, 100, 
                             36, 0, 66, 60, 0, 164, 36, 0, 66, 60, 0, 36, 164, 
                             0, 66, 60, 0, 36, 36, 128, 66, 60, 0, 36, 36, 0, 
                             194, 60, 0, 36, 36, 0, 66, 188, 0} ;



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

int rowCount = 2;

void AdvanceRow()
{

    if(rowCount >= 6)
        {
            ROW_SEL = 1;

            rowCount = 0;
        }
        
        ROW_CLK = 1;    
        ROW_CLK = 0;
        
        rowCount++;
    
}

void ReadyDisplay()
{
    ROW_EN = 1;
    
    ROW_SEL = 1;    //set select to high
    
    //Pulse the clock twice to set row A high
    ROW_CLK = 1;    
    ROW_CLK = 0;
    ROW_CLK = 1;    
    ROW_CLK = 0;  
    
    ROW_EN = 0;     //turn on display
}

uint8_t currentRow = 0;

void PopulateColumns()
{
    ROW_EN = 1;     //Disable screen
        
        // Populate the columns
        for(int i =7;i>=0;i--)
        {
            
           
            if(i==3)
            {
               COL_SEL = !buf[currentRow][0];
            }
            else if(i==2)
            {
               COL_SEL = !buf[currentRow][1];
            }
            else if(i==1)
            {
                COL_SEL = !buf[currentRow][2];
            }
            else if(i==0)
            {
               COL_SEL = !buf[currentRow][3];
            }
            else
            {
                COL_SEL = !buf[currentRow][i];
            }
            
            
            COL_CLK = 1;
            COL_CLK = 0;

            
            
        }
        
        
        // Enable screen
        ROW_EN = 0;
        
        currentRow++;
        if(currentRow == 6){
            currentRow = 0;
        }
        
}

void PopulateColumns2()
{
    ROW_EN = 1;     //Disable screen
        
        // Populate the columns
        for(int i =7;i==0;i--)
        {
            
           
            COL_SEL = 0;
            
            
            COL_CLK = 1;
            COL_CLK = 0;

            //__delay_us(100000); 
            
        }
        
        
        // Enable screen
        ROW_EN = 0;
}
