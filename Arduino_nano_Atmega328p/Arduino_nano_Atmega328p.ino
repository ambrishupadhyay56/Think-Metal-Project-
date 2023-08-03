#define CMDBUFFER_SIZE 32
int Speed=0, Status=0,Num=0;
const int Switch=4, Fan_speed=9;
void setup()
{
 Serial.begin(115200); 
 pinMode(Switch,OUTPUT);
 pinMode(Fan_speed,OUTPUT);
 
}

void loop()
{
  digitalWrite(Switch,Status);
  if((Num<101)&&(Num>-1))
  {
  Speed = map(Num, 0, 100, 0, 255);
  analogWrite(Fan_speed,Speed);
  
}
}
void serialEvent()
{
  static char cmdBuffer[CMDBUFFER_SIZE] = "";
  char c;
  while(Serial.available()) 
  {
    c = processCharInput(cmdBuffer, Serial.read());
    Serial.print(c);
    if (c == '\n') 
    {
      Serial.println();
      //Full command received.  
      if (strcmp("ON", cmdBuffer) == 0)
      {
         Status=0;
      }
      if (strcmp("OFF",cmdBuffer) == 0)
      {
         Status=1;
      }
      Num = atoi(cmdBuffer);
      cmdBuffer[0] = 0;
    }
  }
  delay(1);
}

char processCharInput(char* cmdBuffer, const char c)
{
  //Store the character in the input buffer
  if (c >= 32 && c <= 126) //Ignore control characters and special ascii characters
  {
    if (strlen(cmdBuffer) < CMDBUFFER_SIZE) 
    { 
      strncat(cmdBuffer, &c, 1);   //Add it to the buffer
    }
    else  
    {   
      return '\n';
    }
  }
  else if ((c == 8 || c == 127) && cmdBuffer[0] != 0) //Backspace
  {

    cmdBuffer[strlen(cmdBuffer)-1] = 0;
  }

  return c;
}
