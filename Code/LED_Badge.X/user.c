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


// I could probably get better performance in my animation algorithms if i 
//implement the buffer as an array of 6 fixed length circular queues, one for each row.
//Now that i think about it, the hardware itself is made of shift registers which are like
// fixed length read only queues and i should be able to just push directly in.
//If i do that i wont need the bloat of a frame buffer but then could only do scroll animations

bool buf[6][8] = {
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1
};

int currentFrame = 0; //Current frame for frame animations
int scrollIndex = 0; //The index of the last used column for scroll animations
const int frameSize = 6;




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

void InitFrameAnimation()
{
    
    for(int y = 0;y<6;y++){
        for(int x =0,k = 7;x<8;x++,k--){
            buf[y][x] = (frameAnimation[y] >> k) & 1;
        }
    }
    
}

void InitScrollAnimation(){
    for(int i=0;i<8;i++){
        AdvanceAnimationScroll();
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

// Updates the Frame Buffer to contain a whole new frame
void AdvanceAnimationFrame(){
    if(currentFrame >= maxFrames){
        currentFrame = 0;
    } else {
        currentFrame++;
    }
    
    
    for(int y = 0;y<6;y++){

        
            for(int x =0,k = 7;x<8;x++,k--){
                buf[y][x] = (frameAnimation[(currentFrame*frameSize)+y] >> k) & 1;
            }

    }
    
    
}

// Shifts the frame buffer one place to the left then places a whole new column on the right
void AdvanceAnimationScroll(){
    if(scrollIndex >= animationLength){
        scrollIndex = 0;
    }
       
    
    
    for(int y = 0,k=5;y < 6;y++,k--){
        for(int x = 0;x <7;x++){
                buf[y][x] = buf[y][x+1];
        }
        buf[y][7] = (frameAnimation[scrollIndex] >> k) & 1;
    }
     scrollIndex++;
    
}


