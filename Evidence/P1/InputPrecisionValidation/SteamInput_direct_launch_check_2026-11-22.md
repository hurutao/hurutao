# Steam Input 直接启动复核

日期：2026-11-22

在 Steam 进程保持运行时，直接启动 `C:\P1InputValidation\P1InputValidation.uproject` 的 `-game` 窗口。UE 加载了 `XInputDevice`，但日志只注册了 `WindowsApplication`，没有出现 `XInputInterface::XInputController`，也没有产生 `P1_INPUT_SAMPLE` 或 `P1_RAW_AXIS`。

结论：Steam 运行本身不会自动接管直接启动的隔离工程。Steam Input 人工验证已通过，但自动化采样必须从 Steam 的非 Steam 游戏快捷方式启动并让 Steam 接管该进程。当前状态为 UNVERIFIED。
