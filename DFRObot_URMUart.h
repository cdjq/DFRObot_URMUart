/*!
 * @file DFRObot_URMUart.h
 * @brief 这是一个获取障碍物距离的传感器库
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [PengKaixing](kaixing.peng@dfrobot.com)
 * @version V1.0.0
 * @date 2022-09-06
 * @url https://github.com/DFRobot/DFRObot_URMUart
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

class DFRObot_URMUart{
public:
  DFRObot_URMUart(HardwareSerial& theSerial);
    
  /**
   * @struct CallBackState
   * @brief 用来显示与传感器通信的返回状态
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
   * @brief 初始化函数
   * @param theBaudrate 串口通信波特率
   * @return boolean类型，表示返回初始化的状态
   * @retval 0 fail
   * @retval -1 success
   */
  boolean begin(unsigned long theBaudrate);

  /**
   * @fn available
   * @brief 查看串口数据是否是可获取的
   * @return boolean类型，表示数据返回的状态
   * @retval 0 fail
   * @retval -1 success
   */
  boolean available(void);

  /**
   * @fn requestDistance
   * @brief 向传感器请求距离数据
   * @param theAddress 传感器RS485地址
   * @param theTimeOutDuration  请求超时 
   * @return boolean类型，表示数据请求返回的状态
   * @retval 0 request fail
   * @retval -1 request success
   */
  boolean requestDistance(byte theAddress,unsigned long theTimeOutDuration=DefaultTimeOutDuration);

  /**
   * @fn requestTemperature
   * @brief 向传感器请求温度数据
   * @param theAddress 传感器RS485地址
   * @param theTimeOutDuration  请求超时 
   * @return boolean类型，表示数据请求返回的状态
   * @retval 0 request fail
   * @retval -1 request success
   */
  boolean requestTemperature(byte theAddress,unsigned long theTimeOutDuration=DefaultTimeOutDuration);

  /**
   * @fn requestMaxDistance
   * @brief 向传感器请求获取最大可探测距离数据
   * @param theAddress 传感器RS485地址
   * @param theTimeOutDuration  请求超时 
   * @return boolean类型，表示数据请求返回的状态
   * @retval 0 request fail
   * @retval -1 request success
   */
  boolean requestMaxDistance(byte theAddress,unsigned long theTimeOutDuration=DefaultTimeOutDuration);
  
  /**
   * @fn setMaxDistance
   * @brief 设置传感器最大可探测距离数据
   * @param theAddress 传感器RS485地址
   * @param ptheMaxDistance 待设置的最大距离
   * @param theTimeOutDuration  请求超时 
   * @return boolean类型，表示数据请求返回的状态
   * @retval 0 set fail
   * @retval -1 set success
   */
  boolean setMaxDistance(byte theAddress,int theMaxDistance,unsigned long theTimeOutDuration=DefaultTimeOutDuration);

  /**
   * @fn setBaudrate
   * @brief 设置传感器通信波特率
   * @param theAddress 传感器RS485波特率
   * @param ptheMaxDistance 待设置的串口通信波特率
   * @param theTimeOutDuration  请求超时 
   * @return boolean类型，表示数据请求返回的状态
   * @retval 0 set fail
   * @retval -1 set success
   */
  boolean setBaudrate(byte theAddress,unsigned long theBaudrate,unsigned long theTimeOutDuration=DefaultTimeOutDuration);

  /**
   * @fn setAddress
   * @brief 设置传感器通信地址
   * @param theAddress 传感器RS485地址
   * @param ptheMaxDistance 待设置的串口通信波特率
   * @param theTimeOutDuration  请求超时 
   * @return boolean类型，表示数据请求返回的状态
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
