# DualSense 输入故障诊断

日期：2026-11-20

## 现象

Windows PnP 能看到 `DualSense Edge Wireless Controller`，但隔离采样工程中 Xbox 可以产生 Enhanced Input 回调，切换 DualSense 后无法控制画面。

## 日志证据

`C:\P1InputValidation\Saved\Logs\P1InputValidation.log` 中：

- Xbox 阶段注册：`LogInputDeviceRegistry: RegisterDevice: DeviceId=1 InputDeviceName=XInputInterface HardwareDeviceIdentifier=XInputController`
- Xbox 断开：`NewState=Disconnected ... XInputInterface::XInputController`
- DualSense 阶段只出现音频设备切换到 `DualSense Edge Wireless Controller`
- 没有出现 DualSense 对应的 `LogInputDeviceRegistry` 游戏输入设备注册事件

## 结论

当前采样器的 `Gamepad_LeftX`、`Gamepad_RightX`、`Gamepad_LeftTriggerAxis` 等 Enhanced Input 映射依赖 UE 的 XInput 游戏手柄层。Windows 将 DualSense 作为 HID 游戏控制器暴露，但当前 UE 运行时没有将该 HID 设备注册为可用的 Gamepad 输入设备，因此它不能直接驱动当前映射。

这不是 DualSense 设备未被 Windows 识别，也不是基础手柄损坏。它是输入接入层不匹配。

## 状态

- Xbox → UE Enhanced Input：PASS
- DualSense → Windows PnP：PASS
- DualSense → 当前 UE XInput 映射：FAIL
- DualSense → 当前隔离采样器：BLOCKED
- Steam Input 转换层：UNVERIFIED。当前没有发现运行中的 Steam 进程或 `steam` 命令
- RawInput/其他 HID 接入：未实现

## 后续选择

需要项目负责人选择并批准一种接入路径后才能修复：

1. 使用 Steam Input 将 DualSense 转换为游戏动作/XInput，再继续使用 Enhanced Input
2. 为隔离工具增加 RawInput/HID 接入，直接读取 DualSense
3. 使用已批准的本地映射层将 DualSense 暴露为 XInput

本次没有安装软件、修改系统映射或引入第三方插件。
