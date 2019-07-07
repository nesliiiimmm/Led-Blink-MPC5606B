#include "MPC5606B.h"
#include<stdlib.h>
#include<stdio.h>
void initModesAndClks(void);
void initPeriClkGen(void);
void disableWatchdog(void);
void Delay(void);
long int i;
long int j;
int case1=0;
void initModesAndClks(void) {//mode clock ayarları..
	ME .MER.R = 0x0000001D; /* Enable DRUN, RUN0, SAFE, RESET modes */
	/* Initialize PLL before turning it on: */
	/* Use 1 of the next 2 lines depending on crystal frequency: */
	CGM .FMPLL_CR.R =0x02400100; /* 8 MHz xtal: Set PLL0 to 64 MHz */
	/*CGM.FMPLL[0].CR.R = 0x12400100;*//* 40 MHz xtal: Set PLL0 to 64 MHz */
       ME .RUN[0].R =0x001F0074; /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL */
	ME.RUNPC[0].R = 0x00000010; /* Peri. Cfg. 0 settings: only run in RUN0 mode */
	/* Use the next lines as needed for MPC56xxB/S: */
	ME.PCTL[32].R=0x0000;
	ME .PCTL[48].R = 0x0000; /* MPC56xxB LINFlex0: select ME.RUNPC[0] */
	ME .PCTL[68].R = 0x0000; /* MPC56xxB/S SIUL:  select ME.RUNPC[0] */
	/* Mode Transition to enter RUN0 mode: */
	ME .MCTL.R = 0x40005AF0; /* Enter RUN0 Mode & Key */
	ME .MCTL.R = 0x4000A50F; /* Enter RUN0 Mode & Inverted Key */
	while (ME .IS.B.I_MTC != 1) {
	} /* Wait for mode transition to complete */
	ME .IS.R = 0x00000001; /* Clear Transition flag */
}
void initPeriClkGen(void) {//peripheral clocklar...
	/* Use the following code as required for MPC56xxB or MPC56xxS:*/
	//CGM.SC_DC[0].R = 0x80;   /* MPC56xxB/S: Enable peri set 1 sysclk divided by 1 */
	CGM .SC_DC0.R = 0x80; /* MPC56xxB/S: Enable peri set 3 sysclk divided by 1 */
	CGM .SC_DC1.R = 0x80; /* MPC56xxB/S: Enable peri set 3 sysclk divided by 1 */
	CGM .SC_DC2.R = 0x80; /* MPC56xxB/S: Enable peri set 3 sysclk divided by 1 */
}
void disableWatchdog(void) {
	SWT .SR.R = 0x0000c520; /* Write keys to clear soft lock bit */
	SWT .SR.R = 0x0000d928;
	SWT .CR.R = 0x8000010A; /* Clear watchdog enable (WEN) */
}
void Delay()
{
	for(i=0;i<60000;i++)
	{for(j=0;j<60;j++){}}
}
int main(void) {
     volatile int i = 0;
	initModesAndClks ();//
	initPeriClkGen ();
	disableWatchdog ();
	
	//output pinlerini ayarladık//
   SIU.PCR[68].B.OBE=1;
   SIU.PCR[69].B.OBE=1;
   SIU.PCR[70].B.OBE=1;
   SIU.PCR[71].B.OBE=1;
   //input yani buttonun değerlerini ayarladık//
   SIU.PCR[64].B.IBE=1;
   SIU.PCR[65].B.IBE=1;
   SIU.PCR[66].B.IBE=1;
   SIU.PCR[67].B.IBE=1;
   //en başta sıfırlamamız gerekiyor..
   
   SIU.GPDO[68].R=1;
   SIU.GPDO[69].R=1;
   SIU.GPDO[70].R=1;
   SIU.GPDO[71].R=1;
 /*   Loop forever */
for (;;) {
	 if(SIU.GPDI[64].R==0x0000)
	 {
		 SIU.GPDO[68].R=0;
	 } 
	 if(SIU.GPDI[65].B.PDI==0)
	 {
		 SIU.GPDO[69].R=0;
	 }
	 if(SIU.GPDI[66].B.PDI==0)
	 {
	 	 SIU.GPDO[70].R=0;
	 }
	 if(SIU.GPDI[67].B.PDI==0)
	 {
	 	 SIU.GPDO[71].R=0;
	 }
	 i++;
  }}

