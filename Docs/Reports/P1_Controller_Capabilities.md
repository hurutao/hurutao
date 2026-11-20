# P1 Controller Capabilities

## Windows device presence

- Xbox One 控制器：`OK`，USB `VID_045E&PID_0B00`
- DualSense Edge Wireless Controller：`OK`，USB `VID_054C&PID_0DF2`
- Nefarius Virtual Gamepad Emulation Bus：已发现，但属于虚拟设备，不作为实体硬件验收证据

## Unreal 实机采样

状态：`BLOCKED`。

当前 GUI 自动化可以启动和关闭 Unreal Editor，但无法通过可用窗口路径打开 FPSArena P1 工程，截图通道也发生超时。因此没有在 UE Enhanced Input 中读取左右摇杆、扳机、按键、原始轴值、处理后轴值或死区行为，也没有使用模拟数据冒充实测结果。

证据：`Evidence/P1/remaining_validation.txt`。
