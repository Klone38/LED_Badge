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
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1
};

int frame = 0;
int maxFrames = 24;
int frameSize = 6;




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
    
    T0IE = 0;

    
}

void InitAnimation()
{
    
    for(int y = 0;y<6;y++){
        for(int x =0,k = 7;x<8;x++,k--){
            buf[y][x] = (animation[y] >> k) & 1;
        }
    }
    
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
    
        
        // Populate the columns
        for(int i =7;i>=0;i--)
        {
            
            // Because i built the hardware wrong, columns 0-3 are reversed
            // so column index order is 7 6 5 4 0 1 2 3
            // this flips only that half so animations and display can be normal
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
        
        
        
        
        currentRow++;
        
        if(currentRow == 6){
            currentRow = 0;
        }
        
}

void AdvanceAnimation(){
    if(frame >= maxFrames){
        frame = 0;
    } else {
        frame++;
    }
    
    
    for(int y = 0;y<6;y++){

        
            for(int x =0,k = 7;x<8;x++,k--){
                buf[y][x] = (animation[(frame*frameSize)+y] >> k) & 1;
            }

    }
    
    
}


