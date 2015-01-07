#include "auton.h"
#include "lcdAPI.h"
#include "diag.h"

int Program;

////////////////////
// PRE-AUTONOMOUS //
////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;
	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...

  short leftButton = 1;
	short centerButton = 2;
	short rightButton = 4;
  int choice1;
  int choice2;
  bLCDBacklight = true;
  bool inMenu = true;
  while(inMenu)
  {
  	lcdClear();
  	char* c = "\tChoice 1\nBLU\tDiag\tRED";
  	lcd_printf(c);
		int code = lcdWaitForBtnClick();
  	if (code==leftButton)
  	{
  		choice1=0b00;
  	}
  	if (code==rightButton)
  	{
  		choice1=0b01;
  	}
  	if (code==centerButton)
  	{
  		diag();
  		lcdClear();
  		c="\tChoice 1\nBLU\tDiag\tRED";
  		continue;
  	}

  	lcdClear();
		lcd_printf("\tChoice 2\nAuto\tBack\tPole");
		code = lcdWaitForBtnClick();
    // Display menu 2
  	if (code==leftButton)
  	{
  		choice2=0b00;
  	}
  	if (code==rightButton)
  	{
  		choice2=0b10;
  	}
  	if (code==centerButton)
  	{
  		continue;
  	}
		Program = choice1 + choice2;
		while(1)
		{
			lcdClear();
			switch (Program)
			{
				case 0:
					lcd_printf("\tBLU Auto\nDiag\tOK\tBack");
					break;
				case 1:
					lcd_printf("\tRED Auto\nDiag\tOK\tBack");
					break;
				case 2:
					lcd_printf("\tBLU Pole\nDiag\tOK\tBack");
					break;
				case 3:
					lcd_printf("\tRED Pole\nDiag\tOK\tBack");
					break;
			}
			code = lcdWaitForBtnClick();
			if(code==centerButton)
			{
				inMenu=false;
				break;
			}
			else if (code==leftButton)
				diag();
			else
				break;
		} // while(1)
	} // while(inMenu)
	lcdClear();
	char* disp = (Program==0?"BLU Auto":Program==1?"RED Auto":Program==2?"BLU Pole":"RED Pole");
	displayLCDCenteredString(0, disp);
}

////////////////
// AUTONOMOUS //
////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................
	lcdClear();
	char* disp = (Program==0?"BLU Auto":Program==1?"RED Auto":Program==2?"BLU Pole":"RED Pole");
	displayLCDCenteredString(0, disp);

	switch(Program)
	{
		case 0:
			autonBluAuto();
		case 1:
			autonRedAuto();
		case 2:
			autonBluPole();
		case 3:
			autonRedPole();
	}
	
	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}