# P1 Controller Capabilities

## Human verification

- Xbox 基础手柄控制：`HUMAN-VERIFIED`。项目负责人已在 UE 5.9 FPSArena 工程中人工确认可以正常控制游戏。
- DualSense 基础手柄控制：`HUMAN-VERIFIED`。项目负责人已在 UE 5.9 FPSArena 工程中人工确认可以正常控制游戏。
- 自动化采样日志：`UNVERIFIED`。目前没有逐帧采样日志。

## Windows device presence

- Xbox One 控制器：`OK`，USB `VID_045E&PID_0B00`
- DualSense Edge Wireless Controller：`OK`，USB `VID_054C&PID_0DF2`
- Nefarius Virtual Gamepad Emulation Bus：已发现，但属于虚拟设备，不作为实体硬件验收证据

## Unreal 实机采样

状态：`UNVERIFIED`。

已建立隔离工具 `Evidence/P1/InputPrecisionValidation`，但本轮没有在 UE 运行时接收真实手柄事件。左右摇杆、扳机、主要按键、时间戳、死区和重复输入数据没有自动化采样证据，CSV 中没有伪造数值。
