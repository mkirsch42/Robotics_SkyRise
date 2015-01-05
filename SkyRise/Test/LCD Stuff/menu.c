#include "lcdAPI.h"

void diag()
{
string mainBattery, backupBattery;
while(nLCDButtons!=0){}
while(nLCDButtons!=2)                                       // An infinite loop to keep the program running until you terminate it
{
clearLCDLine(0);                                            // Clear line 1 (0) of the LCD
clearLCDLine(1);                                            // Clear line 2 (1) of the LCD

//Display the Primary Robot battery voltage
displayLCDString(0, 0, "Primary: ");
sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
displayNextLCDString(mainBattery);

//Display the Backup battery voltage
displayLCDString(1, 0, "Backup: ");
sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');    //Build the value to be displayed
displayNextLCDString(backupBattery);

//Short delay for the LCD refresh rate
wait1Msec(100);
}
}

task main()
{
	short Program;
	short leftButton = 1;
	short centerButton = 2;
	short rightButton = 4;
  int choice1;
  int choice2;
  bLCDBacklight = true;
  while(1){
  bool inMenu = true;
 	while(inMenu)
  {
  	lcdClear();
  	lcdWaitForBtnUp();
  	lcd_printf("\tChoice 1\nBLU\tDiag\tRED");
		lcdWaitForBtnDown();
  	if (lcdIsBtnDown(leftButton))
  	{
  		choice1=0;
  	}
  	if (lcdIsBtnDown(rightButton))
  	{
  		choice1=1;
  	}
  	if (lcdIsBtnDown(centerButton))
  	{
  		diag();
  		continue;
  	}

  	lcdClear();
  	lcdWaitForBtnUp();
		lcd_printf("\tChoice 2\n1\tBack\t2");
		lcdWaitForBtnDown();
    // Display menu 2
  	if (lcdIsBtnDown(leftButton))
  	{
  		choice2=0;
  	}
  	if (lcdIsBtnDown(rightButton))
  	{
  		choice2=2;
  	}
  	if (lcdIsBtnDown(centerButton))
  	{
  		continue;
  	}

  	inMenu=false;
	}
	Program = choice1 + choice2;
	lcdClear();
	displayLCDCenteredString(0, Program==0?"BLU1":Program==1?"RED1":Program==2?"BLU2":"RED2");
	lcdWaitForBtnUp();
	lcdWaitForBtnDown();}
}
