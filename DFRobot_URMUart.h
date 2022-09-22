/*!
 * @file DFRobot_URMUart.h
 * @brief A sensor library for getting the distance between the sensor and obstacle ahead 
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [PengKaixing](kaixing.peng@dfrobot.com)
 * @version V1.0.0
 * @date 2022-09-06
 * @url https://github.com/DFRobot/DFRobot_URMUart
 */

#ifndef DFRObot_URMUart_RELEASE
#define DFRObot_URMUart_RELEASE 100
#include "Arduino.h"

#define ReceivedCommandStackLength 10
#define SendingCommandStackLength 10
#define DefaultTimeOutDuration 1000
#define Header0 0x55
#define Header1 0xaa

#define Header0Index 0
#define Header1Index 1
#define AddressIndex 2
#define LengthIndex 3
#define CommandIndex 4
#define Content0Index 5
#define Content1Index 6

//distance command
#define RequestDistanceCommand 0x02   
//temperature command
#define RequestTemperatureCommand 0x03   
//distance threshold        
#define RequestMaxDistanceCommand 0x05         
#define SetMaxDistanceCommand 0x04
#define SetBaudrateCommand 0x08
#define SetAddressCommand 0x55

#define BroadcastAddress 0xab

#define OperationSuccess 0xcc
#define OperationFailure 0xee

#define Baudrate1200BPS 0x00
#define Baudrate2400BPS 0x01
#define Baudrate4800BPS 0x02
#define Baudrate9600BPS 0x03
#define Baudrate14400BPS 0x04
#define Baudrate19200BPS 0x05
#define Baudrate28800BPS 0x06
#define Baudrate38400BPS 0x07
#define Baudrate57600BPS 0x08
#define Baudrate115200BPS 0x09
#define Baudrate128000BPS 0x0A
#define Baudrate256000BPS 0x0B

class DFRobot_URMUart{
public:
  DFRobot_URMUart(HardwareSerial& theSerial);
    
  /**
   * @struct CallBackState
   * @brief Display the return status of sensor communication  
   */
  enum CallBackState {
      OnNull,
      OnTimeOut,
      OnRequestDistance,
      OnRequestTemperature,
      OnRequestMaxDistance,
      OnSetMaxDistance,
      OnSetBaudrate,
      OnSetAddress,
      OnWrongStack
  } callBackState;
    
  /**
   * @fn begin
   * @brief Init function 
   * @param theBaudrate  Serial communication baud rate 
   * @return boolean type, return init status 
   * @retval 0 fail
   * @retval -1 success
   */
  boolean begin(unsigned long theBaudrate);

  /**
   * @fn available
   * @brief Check if there is available serial data 
   * @return boolean type, represents data return status 
   * @retval 0 fail
   * @retval -1 success
   */
  boolean available(void);

  /**
   * @fn requestDistance
   * @brief Request distance data from the sensor 
   * @param theAddress Sensor RS485 address 
   * @param theTimeOutDuration  Request timeout 
   * @return boolean type, represents the communication status of this command 
   * @retval 0 request fail
   * @retval -1 request success
   */
  boolean requestDistance(byte theAddress,unsigned long theTimeOutDuration=DefaultTimeOutDuration);

  /**
   * @fn requestTemperature
   * @brief Request temperature data from the sensor
   * @param theAddress Sensor RS485 address
   * @param theTimeOutDuration  Request timeout 
   * @return boolean type, represents the communication status of this command
   * @retval 0 request fail
   * @retval -1 request success
   */
  boolean requestTemperature(byte theAddress,unsigned long theTimeOutDuration=DefaultTimeOutDuration);

  /**
   * @fn requestMaxDistance
   * @brief Request max detectable distance from sensor 
   * @param theAddress Sensor RS485 address
   * @param theTimeOutDuration  Request timeout   
   * @return boolean type, represents the communication status of this command
   * @retval 0 request fail
   * @retval -1 request success
   */
  boolean requestMaxDistance(byte theAddress,unsigned long theTimeOutDuration=DefaultTimeOutDuration);
  
  /**
   * @fn setMaxDistance
   * @brief Set sensor max detectable distance  
   * @param theAddress  Sensor RS485 address
   * @param ptheMaxDistance Max distance to be set 
   * @param theTimeOutDuration  Request timeout  
   * @return boolean type, represents the communication status of this command 
   * @retval 0 set fail
   * @retval -1 set success
   */
  boolean setMaxDistance(byte theAddress,int theMaxDistance,unsigned long theTimeOutDuration=DefaultTimeOutDuration);

  /**
   * @fn setBaudrate
   * @brief Set sensor communication baud rate 
   * @param theAddress Sensor RS485 address
   * @param theBaudrate  Baud rate to be set 
   * @param theTimeOutDuration  Request timeout 
   * @return boolean type, represents the communication status of this command
   * @retval 0 set fail
   * @retval -1 set success
   */
  boolean setBaudrate(byte theAddress,unsigned long theBaudrate,unsigned long theTimeOutDuration=DefaultTimeOutDuration);

  /**
   * @fn setAddress
   * @brief Set sensor communication address
   * @param theAddress  Sensor RS485 address 
   * @param theTimeOutDuration  Request timeout 
   * @return boolean type, represents the communication status of this command
   * @retval 0 set fail
   * @retval -1 set success
   */
  boolean setAddress(byte theAddress,unsigned long theTimeOutDuration=DefaultTimeOutDuration);

private:
    void sendStack();
    void parseStack();
    boolean validateStack();
    //serial port to communicate with
    HardwareSerial& SerialTransceiver;      
    unsigned long timeOutTimer;
    unsigned long timeOutDuration;
    byte receivedCommandStack[ReceivedCommandStackLength];
    byte sendingCommandStack[SendingCommandStackLength];
    byte receivedCommandStackIndex;
    boolean isBusy;
    byte receivedAddress;
    int receivedContent;
};

#endif
