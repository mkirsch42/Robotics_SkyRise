// Found online, works similar to strtok from strings.h
#define MAX_TOKEN_SIZE 50
#define MAX_BUFFER_SIZE 50
bool strtok(char *buffer, char *token, char *seperator)
{
  int pos = StringFind(buffer, seperator);
  char t_buff[MAX_BUFFER_SIZE];

  // Make sure we zero out the buffer and token
  memset(token, 0, MAX_TOKEN_SIZE);
  memset(&t_buff[0], 0, MAX_BUFFER_SIZE);

  // Looks like we found a seperator
  if (pos >= 0)
  {
    // Copy the first token into the token buffer, only if the token is
    // not an empty one
    if (pos > 0)
      memcpy(token, buffer, pos);
    // Now copy characters -after- the seperator into the temp buffer
    memcpy(&t_buff[0], buffer+(pos+1), strlen(buffer) - pos);
    // Zero out the real buffer
    memset(buffer, 0, strlen(buffer) + 1);
    // Copy the temp buffer, which now only contains everything after the
    // previous token into the buffer for the next round.
    memcpy(buffer, &t_buff[0], strlen(&t_buff[0]));
    return true;
  }
  // We found no seperator but the buffer still contains a string
  // This can happen when there is no trailing seperator
  else if(strlen(buffer) > 0)
  {
    // Copy the token into the token buffer
    memcpy(token, buffer, strlen(buffer));
    // Zero out the remainder of the buffer
    memset(buffer, 0, strlen(buffer) + 1);
    return true;
  }
  return false;
}






void lcdPrintLeft(short line, char* str)
{
	displayLCDString(line, 0, str);
}

void lcdPrintRight(short line, char* str)
{
	displayLCDString(line, 16-strlen(str), str);
}

void lcdPrintSpecial(char* input)
{
	char strArr[50];
	char* str = &strArr;
	memcpy(str,input,strlen(input));
	char line1[50];
	char* line1Ptr=&line1;
	char line2[50];
	char* line2Ptr=&line2;
	memset(line1Ptr,0,50);
	memset(line2Ptr,0,50);
	strtok(str,line1Ptr,"~");
	strtok(str,line2Ptr,"~");
	char str1[50];
	char* str1Ptr=&str1;
	char str2[50];
	char* str2Ptr=&str2;
	char str3[50];
	char* str3Ptr=&str3;
	strtok(line1Ptr,str1Ptr,"`");
	strtok(line1Ptr,str2Ptr,"`");
	strtok(line1Ptr,str3Ptr,"`");
	lcdPrintLeft(0, str1Ptr);
	displayLCDCenteredString(0, str2Ptr);
	lcdPrintRight(0, str3Ptr);
	strtok(line2Ptr,str1Ptr,"`");
	strtok(line2Ptr,str2Ptr,"`");
	strtok(line2Ptr,str3Ptr,"`");
	displayLCDCenteredString(1, str2Ptr);
	lcdPrintRight(1, str3Ptr);
	lcdPrintLeft(1, str1Ptr);
}

void lcdClear()
{
	clearLCDLine(0);
	clearLCDLine(1);
}

void lcdWaitForBtnUp()
{
	while(nLCDButtons!=0){}
}

void lcdWaitForBtnDown()
{
	while(nLCDButtons==0){}
}

bool lcdIsBtnDown(short btnCode)
{
	return nLCDButtons&btnCode;
}
