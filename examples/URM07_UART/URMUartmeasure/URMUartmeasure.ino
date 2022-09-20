/*!
 * @file URMUartmeasure.ino
 * @brief 这是一个使用URM07两个传感器同时获取前方障碍物距离和板载温度的例子
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [PengKaixing](kaixing.peng@dfrobot.com)
 * @version V1.0.0
 * @date 2022-09-06
 * @url https://github.com/DFRobot/DFRobot_URMUart
 */

#include "DFRobot_URMUart.h"
     
/*todo: set actual parameters*/
const unsigned long URM_Baudrate = 19200;  
const byte URM1_Address = 0x11;          //0xAB is broadcast address
const byte URM2_Address = 22;  

DFRobot_URMUart urm(Serial);  //select the Serial port for communication with Urm sensor

/*inner define*/
#define CustomizedTimeOutDuration 300   //Time Out Duration can be Customized in "ms" unit. Default value is 1000ms.

void setup()
{     
  urm.begin(URM_Baudrate);
}

void loop() 
{
  commandProcess();  

  /*read module 1*/  
  while(!urm.requestDistance(URM1_Address, CustomizedTimeOutDuration)) {
    commandProcess();
  }   

  while(!urm.requestTemperature(URM1_Address, CustomizedTimeOutDuration)) {
    commandProcess();
  }    

  /*read module 2*/
  while(!urm.requestDistance(URM2_Address, CustomizedTimeOutDuration)) {
    commandProcess();
  }     
   
  delay(CustomizedTimeOutDuration >> 1);
}


/*  */
void onTimeOut()
{
  //If there is no reply from Urm lasting for 'CustomizedTimeOutDuration' second, this function will run. The time duration can be Customized
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












