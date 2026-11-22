# Steam Input 路径人工验证

日期：2026-11-22

项目负责人反馈，启动 Steam Input 后再启动 UE5，DualSense 已能够控制当前 UE5 模型视野。系统同时运行 Steam 和 UE5 进程，DualSense 原始 HID 设备仍保持 `OK`。

该结果证明 Steam Input 可以在当前机器上为 DualSense 提供可用的 UE 控制路径，状态为 HUMAN-VERIFIED。当前隔离采样工程日志尚未产生 `P1_INPUT_SAMPLE` 或 `P1_RAW_AXIS`，因此 Steam Input 路径的自动化 CSV 仍为 UNVERIFIED。
