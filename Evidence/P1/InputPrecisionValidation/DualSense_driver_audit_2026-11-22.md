# DualSense 驱动栈审计

日期：2026-11-22

## 设备与驱动

DualSense Edge 的手柄接口为 `HID\\VID_054C&PID_0DF2&MI_03`，设备状态为 `OK`。对应驱动为 Windows 标准 `HID-compliant game controller` 和 `HidUsb`。USB 音频接口使用系统 `USB Audio Device`，与摇杆输入接口分离。

## 第三方映射层

系统安装了 `Nefarius Virtual Gamepad Emulation Bus`，驱动为 `vigembus.inf`，版本 `1.21.442.0`。当前设备枚举中没有活动的虚拟 Xbox 或虚拟 DualSense 控制器。当前没有运行中的 Steam、DS4Windows 或 reWASD 进程，Steam Client Service 状态为 `Stopped`。

## 结论

没有证据表明第三方映射层正在接管当前 DualSense 摇杆。DualSense 已被 Windows HID 和 UE RawInput 注册，但隔离采样器没有收到 `P1_INPUT_SAMPLE`，当前阻断点位于 UE RawInput 轴事件进入 Enhanced Input 的链路。驱动审计状态为 PASS，DualSense 自动化采样状态继续为 BLOCKED。
