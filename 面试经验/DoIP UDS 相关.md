## 索引

## 0x10 DiagnosticSessionControl
包括三个 session ：0x01 default session，0x02 programming session，0x03 extended session
回复 50 SF [P2 server max 2 bytes] [P2* server max 2 bytes]
否定响应 0x12 subfunction not supported, 0x13 incorrent message length or invalid format, 0x22 condition not correct

## 0x11 ECU Reset
请求格式 0x11 [subfunction]
subfunction: 0x01 硬重启 0x02 ram存储器清除 0x03 软重启重新启动程序  0x04 enableRapidPowerShutDown 进入待机状态
回复：0x51 subfunction [0x00 -- x0FE powerdown time] / [0xFF 表示失败]
否定响应：0x12 subfunction not supported, 0x13 incorrect message length or invalid format, 0x22 condition not correct, 0x33 security access denied

## 0x14 Clear Diagnostic Information
请求格式：0x14 [DTC id 3 bytes]

## 0x19 Read DTC Information
请求格式：0x19 [subfunction] 
subfunction:
+ 0x01 reportNumberOfDTCByStatusMask
+ 0x02 reportDTCByStatusMask
+ 0x03 reportDTCSnapshotIdentification
+ 0x04 reportDTCSnapshotRecordByDTCNumber
+ 0x05 reportDTCStoredDataByRecordNumber
+ 0x0A reportSupportedDTC

## 0x22 Read Data By Identifier

否定响应：
+ 0x13 incorrect message length or invalid format
+ 0x14 response too long
+ 0x22 condition not correct
+ 0x31 request out of range
+ 0x33 security access denied

## 0x23 Read Memory By Address

## 0x24 Read Scaling Data By Identifier

## 0x27 Security Access
请求格式： 0x27 [奇数 request seed / 偶数 send key]
回复格式： 0x67 [security type] [security seed]
否定响应： 
+ 0x12  subfunction not supported, 
+ 0x13 incorrect message length or invalid format, 
+ 0x22 condition not correct, 
+ 0x24 request sequence error
+ 0x31 request out of range
+ 0x35 invalid key
+ 0x36 exceeded number of attempt
+ 0x37 required time delay not expired

## 0x28 Communication Control
请求格式： 0x28 [control type] [communication type] [node id 高字节] [node id 低字节]
control type：
+ 0x00 enable RX and Tx
+ 0x01 enable Rx and disable Tx
+ 0x02 disable Rx and enable Tx
+ 0x03 disable Rx and Tx

回复格式 0x68 [control type]
否定响应：
+ 0x12 subfunction not supported
+ 0x13 incorrect message length or invalid format
+ 0x22 condition not correct
+ 0x31 request out of range

## 0x29

## 0x2A Read Data By Periodic Identifier

## 0x2C 

## 0x2E DID 写入

## 0x2F 输入输出控制

## 0x31 routine control
请求格式：31 [routine control type] [routine id] [para]
routine control type: 0x01 start routine 0x02 stop a routine 0x03 获取运行结果
routine id:
+ 
否定响应：
+ 0x12 subfunction not supported
+ 0x13 incorrect message length or invalid format
+ 0x22 condition not correct
+ 0x24 request sequence error
+ 0x31 request out of range
+ 0x33 security access denied
+ 0x72 general programming failure

## 0x34 请求下载服务
请求格式：34 [data format id] [address & length format id]
回复格式：0x74 [length format id 高位表示 max number of block length 的长度] [max number of block length]
data format id: 高位指定压缩模式，低位指定加密模式，0x00 表示两个都不使用
address & length format id：高位表示接下来memory size数据的长度， 低位 表示接下来memory address的长度
max number of block length: 数通知客户端有多少数据字节（maxNumberOfBlockLength）包含在来自客户端的
每个TransferData请求消息中。
否定响应：
+ 0x13 incorrect message length or invalid format
+ 0x22 condition not correct
+ 0x31 request out of range 上述的参数无效
+ 0x33 security access denied
+ 0x70 upload/download not accepted

## 0x35 request upload
请求格式 0x35 [data format id] [address & length format id]
回复格式 0x75 [length format id] [max number of block length]
否定响应：
+ 0x13 incorrect message length or invalid format
+ 0x22 condition not correct
+ 0x31 request out of range 上述的参数无效
+ 0x33 security access denied
+ 0x70 upload/download not accepted

## 0x36
请求格式 36 [block sequence counter] [transfer data]
回复格式 76 [block sequence counter]
否定响应：
+ 0x13 incorrect message length or invalid format
+ 0x24 request sequence error
+ 0x31 request out of range
+ 0x71 transfer data suspended 长度不符合要求
+ 0x72 general programming failure 内存检测到错误
+ 0x73 wrong block sequence counter
+ 0x92/0x93 电压过高或者过低

## 0x37 request transfer exit
请求格式：0x37
回复格式：0x77
否定响应:
+ 0x13 incorrect message length or invalid format
+ 0x24 request sequence error
+ 0x31 request out of range 上述的参数无效
+ 0x72 general programming failure 内存检测到错误

## 0x38
请求格式：0x38 [操作模式] [file path or name length] [data format id] [file size para length] [file size uncompressed] [file size compressed]
回复格式：0x78 [操作模式] [length format id]
否定响应：
+ 0x13 incorrect message length or invalid format
+ 0x22 condition not correct
+ 0x31 request out of range 上述的参数无效
+ 0x33 security access denied
+ 0x70 upload/download not accepted

## 0x3D

## 0x3E Tester present
请求格式：0x3E [0x00 / 0x80 不需要回复]
回复格式：0x7E 0x00
否定响应：
+ 0x12: subfunction not supported
+ 0x13: incorrect message length or invalid format

## 0x85 Control DTC Setting
请求格式：0x85 [DTC Setting Type] [DTC Setting Control Option]
DTC Setting Type:
+ 0x01 up
+ 0x01 close
+ 0x40 - 0x5F vehicle manufacturer specific
+ 0x60 - 0x7E system supplier specific
回复格式：0xC5 [DTC Setting Type]
否定响应：
+ 0x12 subfunction not supported
+ 0x13 incorrect message length or invalid format
+ 0x22 condition not correct
+ 0x31 request out of range

## DoIP 服务
请求格式 [02 fd DoIP版本信息] [payload type 2 bytes] [payload length 4字节]
payload 类型：
1. 0x0000 vehicle announcement message
车辆启动后发送给doip网关，用于通知车辆的存在
传输的信息：vin(17), logical address[2], eid[6], gid[6]

2. 0x8001 uds message
传输的信息 [source address] [target address]

3. 0x0003 alive check request
检查doip节点是否存活

4. 0x0004 alive check response
回复doip节点是否存活

3. 0x0005 routing activation request
请求激活特定的路由
报文结构 [activation type 1 byte]

4. 0x0006 Routing Activation Response
响应路由激活请求，包含激活结果。

5. 0x0007 Diagnostic Communication Management
管理诊断通信，包括启动和停止诊断会话

## UDSonCan 报文结构
请求格式：[CanID 11位] [Data length code 8位] [data]
+ 单帧请求(以读取某个did为例) [0x7DF] [0x08] [0x02] [0x22] [0xF1] [0x90] [0x00] [0x00] [0x00] [0x00]
  + 0x02 
+ 标准回复 [0x7E8]