# DFRObot_URMUart
- [中文版](./README_CN.md)

这个超声波静电换能器设计的一款大功率超声波。测量距离可达10米， 另外一个显著的特点是超声波探测夹角只有15°，而大多数的超声波是60°。

![Product Image](./resources/images/SEN0001.png)


## Product Link (https://www.dfrobot.com/product-1038.html)
    SKU: SEN0149

## Table of Contents

  * [Summary](#summary)
  * [Installation](#installation)
  * [Methods](#methods)
  * [Compatibility](#compatibility)
  * [History](#history)
  * [Credits](#credits)

## Summary

This is a library of range sensors.

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
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

```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32           |      √       |              |             | 
micro:bit        |      √       |              |             | 
ESP8266         |      √       |              |             |

## History

- 2022/09/6 - Version 1.0.0 released.

## Credits

Written by PengKaixing(kaixing.peng@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))





