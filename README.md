# SerialPowerSwitch
A small linux utility to control a powerswitch via DTR line on UART

Usage example to power on:
`./SerialPowerSwitch /dev/ttyUSB0 1`

View below is Male connector (PC side)
```
    1 2 3 4 5
  -------------
  \ O O O O O /
   \ O O O O /
     -------
     6 7 8 9
```
     
| Pin | Function | Signal Name         | DTE (PC) |
| --- | -------- | ------------------- | -------- |
| 1   | DCD      | Data Carrier Detect | in       |
| 2   | RXD      | Receive Data        | in       |  
| 3   | TXD      | Transmit Data       | out      |
| 4   | DTR      | Data Terminal Ready | out      |
| 5   | GND      | Signal Ground 	     | -        |
| 6   | DSR      | Data Set Ready      | in       |
| 7   | RTS      | Request to Send     | out      |
| 8   | CTS      | Clear to Send       | in       |
| 9   | RI       | Ring Indicator 	   | in       |
