/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define ROW_CLK     PORTCbits.RC3
#define ROW_SEL     PORTCbits.RC1
#define ROW_EN      PORTCbits.RC4

#define COL_CLK     PORTCbits.RC2
#define COL_SEL     PORTCbits.RC0


/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */

void InitFrameAnimation(void);

void InitScrollAnimation(void);

void ClearDisplay(void);

void AdvanceRow(void);

void ReadyDisplay(void);

void PopulateColumns(void);

void AdvanceAnimationFrame(void);

void AdvanceAnimationScroll(void);