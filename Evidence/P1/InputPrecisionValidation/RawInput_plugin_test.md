# RawInput 插件验证记录

日期：2026-11-22

在隔离 P1 工程中启用 UE 5.9 自带 `RawInput` 插件后，UnrealEditor-Cmd 启动到 `AP1InputValidationController::BeginPlay()` 时发生访问冲突。日志位置为 `C:\P1InputValidation\Saved\Logs\P1InputValidation.log`，错误为 `EXCEPTION_ACCESS_VIOLATION reading address 0x0000000000000070`，调用栈包含 `UnrealEditor-RawInput.dll`。

该路径状态为 FAIL。已从隔离工程移除 RawInput 依赖和启动枚举调用，重新使用 UnrealBuildTool 编译成功。正式 FPSArena 工程未启用该插件。
