/*!
 * @file URMUartset.ino
 * @brief 这是一个使用URM07设置传感器通信地址以及最大探测距离的例子
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [PengKaixing](kaixing.peng@dfrobot.com)
 * @version V1.0.0
 * @date 2022-09-06
 * @url https://github.com/DFRobot/DFRobot_URMUart
 */
#include "DFRobot_URMUart.h"

/**TODO: set parameters**/
#define PRE_BAUDRATE 19200    //set the actual baudrate       
const byte URM_Address = 22;  //set new address  (0xAB is broadcast address)
/* Baudrate should be: 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200, 128000, 256000.  If others, it will use 19200*/
const unsigned long URM_Baudrate = 19200;  //set new baudrate

DFRobot_URMUart urm(Serial);  //select the Serial port for communication with Urm_485 sensor


/**inner definition**/
#define CustomizedTimeOutDuration 500   //Time Out Duration can be Customized in "ms" unit

void setup()
{     
  urm.begin(PRE_BAUDRATE);

  while(!urm.setAddress(URM_Address, CustomizedTimeOutDuration)) {
    commandProcess();
  }
  delay( CustomizedTimeOutDuration );
  commandProcess();

  while(!urm.setBaudrate(URM_Address, URM_Baudrate, CustomizedTimeOutDuration)) {
    commandProcess();
  }
  
  delay( CustomizedTimeOutDuration );
  commandProcess();
}

void loop() 
{
  commandProcess();  
    
  while(!urm.requestDistance(URM_Address, CustomizedTimeOutDuration)) {
    commandProcess();
  }   

  while(!urm.requestTemperature(URM_Address, CustomizedTimeOutDuration)) {
    commandProcess();
  }    

    
   delay(CustomizedTimeOutDuration >> 1);
}


/*  */
void onTimeOut()
{
  //If there is no reply from Urm_485 lasting for 1 second, this function will run. The time duration can be Customized
  //TODO write your code here:
  Serial.println("onTimeOut");

}
void onRequestDistance(byte theAddress, int theDistance)
{
  //If received Distance reply, this function will run.
  //theDistance is in "mm" unit
  //TODO write your code here:
  Serial.print("Address-");
  Serial.print(theAddress);
  Serial.print(":Distance=");
  Serial.print(theDistance);
  Serial.println("mm");

}
void onRequestTemperature(byte theAddress, float theTemperature)
{
  //If received Temperature reply, this function will run.
  //theTemperature is in "°C" unit
  //TODO write your code here:
  Serial.print("Address-");
  Serial.print(theAddress);
  Serial.print(":Temperature=");
  Serial.print(theTemperature);
  Serial.println(" C");

}

void onSetAddress(byte theAddress, boolean isOperationSuccess)
{
  //After setting the Address and getting a reply, this function will run.
  //TODO write your code here:
  Serial.print("Address:");
  Serial.println(theAddress);
  Serial.print("SetAddress:");
  if (isOperationSuccess) {
    Serial.println("Success");
  }
  else{
    Serial.println("Failure");
  }
}
void onWrongStack()
{
  //If received wrong command, this function will run.
  //TODO write your code here:
  Serial.println("WrongStack");
}


//Run the proper function based on the different kinds of states
void commandProcess()
{
  if (urm.available()) {
    switch (urm.callBackState) {
      case DFRobot_URMUart::OnTimeOut:
        onTimeOut();
        break;
      case DFRobot_URMUart::OnRequestDistance:
        onRequestDistance(urm.receivedAddress, urm.receivedContent);
        break;
      case DFRobot_URMUart::OnRequestTemperature:
        onRequestTemperature(urm.receivedAddress, urm.receivedContent/10.0);
        break;
      case DFRobot_URMUart::OnSetAddress:
        onSetAddress(urm.receivedAddress, urm.receivedContent);
        break;
      case DFRobot_URMUart::OnWrongStack:
        onWrongStack();
        break;
      default:
        break;
    }
  }
}












