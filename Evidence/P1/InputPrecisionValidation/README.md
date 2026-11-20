# P1 Enhanced Input 精度采样工具

该目录是隔离的 P1 技术验证工具，不属于 FPSArena 正式玩法代码。

## 编译验证

隔离工程已复制到 ASCII 路径 `C:\P1InputValidation`，并使用 UE 5.9 UBT 编译成功：

```text
Build.bat P1InputValidationEditor Win64 Development -Project=C:\P1InputValidation\P1InputValidation.uproject -WaitMutex
Result: Succeeded
```

中文工作区路径首次编译触发了 PCH 路径编码错误，未修改系统工具链。使用 ASCII 隔离路径后编译通过。

## 运行边界

工具尚未在 UE 运行时接收真实手柄事件。Xbox 与 DualSense 的人工基础控制已由项目负责人确认，输入精度 CSV 仍需真实设备运行采样。
