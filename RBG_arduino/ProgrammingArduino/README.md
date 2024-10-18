This is used in an Arduino to program a Bluetooth MAC address into the YX5200 module.

Currently the programming on the Orange Sidewinder RBG is<br>
```
--CMD 2 AT+VMLINK?
OK+VMLINK
BT_ADD_NUM=2
BT_NAME_NUM=2
Last_Add=0x1adad504eaed
VM_MacAdd0=0x1adad504eaed
VM_MacAdd1=0xf44efdecd39d
VM_Name0=E-go III Orange
VM_Name1=S1 Pro RBG Orange
```

| Order | Name | Mac Address |
| --- | --- | --- |
| 1 | E-go III Orange | 0x1adad504eaed |
| 2 | S1 Pro RBG Orange | 0xf44efdecd39d |
