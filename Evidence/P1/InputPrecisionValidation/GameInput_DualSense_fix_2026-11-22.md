# DualSense GameInput 修复记录

日期：2026-11-22

## 找到的可运行实现

本机 `C:\Users\Administrator\Documents\Unreal Projects\NovaShooter` 工程已经使用 UE 5.9 的 `GameInputWindows`、`GameInput` 和 `GameInputBase` 接通 DualSense Edge。它按 USB VID/PID `054C:0DF2` 注册设备，并在运行时补齐 GameInput 导入器未填充的摇杆、扳机和按键映射。

FPSArena 已移植同一条接入路径：

- `FPSArena.uproject` 启用 `GameInputWindows` 和 `GameInput`。
- `FPSArena.Build.cs` 增加 `GameInputBase` 私有依赖。
- `Config/DefaultInput.ini` 增加 DualSense Edge `VendorId=1356,ProductId=3570` 配置。
- `ForgeController.cpp` 在本地控制器 BeginPlay 时补齐 6 个轴和 12 个按键映射。
- 左摇杆 Y 使用 `Scalar=-1.0`，右摇杆 Y 按 FPSArena 相机链路使用 `Scalar=+1.0`。
- 原有 Xbox/Steam Input 路径保留。

## 编译证据

使用 UE 5.9 UnrealBuildTool：

```text
C:\Program Files\Epic Games\UE_5.9\Engine\Build\BatchFiles\Build.bat FPSArenaEditor Win64 Development -Project='C:\Users\Administrator\Documents\Unreal Projects\FPSArena\FPSArena.uproject' -WaitMutex
```

结果：

```text
Result: Succeeded
```

编译器为 MSVC `14.52.37029`，Windows SDK `10.0.26100.0`。

## 运行日志证据

日志路径：

`C:\Users\Administrator\Documents\Unreal Projects\FPSArena\Saved\Logs\FPSArena.log`

关键日志：

```text
LogPluginManager: Mounting Engine plugin GameInputWindows
LogPluginManager: Mounting Engine plugin GameInput
LogGameInput: GameInputBase module startup...
LogGameInput: Compiled using GameInput major Version: 3
LogGameInput: Executing with detected GameInput Version: 3.1.26100.6879
LogFPSArena: Display: DualSense Edge GameInput mappings initialized: 6 axes, 12 buttons.
LogGameInput: Game Input Device Connected: ... ProdId: 0df2 (3570) VendId: 054c (1356)
LogInputDeviceRegistry: RegisterDevice: DeviceId=1 InputDeviceName=GameInput HardwareDeviceIdentifier=Hid
LogInputDeviceProperties: Input device connection change: NewState=EInputDeviceConnectionState::Connected, DeviceId=1, PlatformUser=0, Device Info=GameInput::Hid
```

## 当前状态

| 项目 | 状态 | 说明 |
|---|---|---|
| GameInput 插件加载 | PASS | UE 5.9 运行日志已确认 |
| DualSense Edge VID/PID 识别 | PASS | `054C:0DF2` 已连接 |
| 轴和按键映射初始化 | PASS | 6 个轴、12 个按键 |
| 实际摇杆、扳机、按键基础控制 | HUMAN-VERIFIED | 项目负责人确认 DualSense 已可控制 FPSArena 画面 |
| 左右摇杆方向 | HUMAN-VERIFIED | 项目负责人确认左右摇杆方向均正常 |
| 自动化逐帧轴/按键 CSV | UNVERIFIED | 当前修复日志尚未包含逐帧采样文件 |
| Steam、DS4Windows、reWASD 重复映射 | PASS（本轮进程检查） | 未发现运行中的接管进程 |

本记录只覆盖输入接入层修复，没有开发正式场景、角色、武器、怪物或 M1–M9 训练玩法。

项目负责人随后在前台运行窗口确认 DualSense 已恢复控制 FPSArena 画面。该结果记录为 `HUMAN-VERIFIED`，不替代自动化逐帧 CSV。

针对左右摇杆方向问题，FPSArena 的 `Gamepad_LeftY` 使用 `Scalar=-1.0`，右摇杆 `Gamepad_RightY` 使用 `Scalar=+1.0` 以匹配 FPSArena 相机链路。调整后已重新通过 UBT 编译并启动 `/Game/Training/Forge`，项目负责人确认左右摇杆方向均正常。
