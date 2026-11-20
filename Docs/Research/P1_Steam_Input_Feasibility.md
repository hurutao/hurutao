# P1 Steam Input Feasibility

状态：UNVERIFIED / 研究结论。

工程未发现 Steamworks SDK 头文件、插件或合法 SDK 路径，因此无法确认本机 SDK 版本、函数签名或编译链接结果。`ISteamInput`、Action Manifest、`GetMotionData`、`InputMotionData_t`、`SetDualSenseTriggerEffect`、`TriggerVibrationExtended` 必须以实际 SDK 头文件和官方文档复核。

方案 A（Steam Input 负责高级控制器能力，Enhanced Input 负责游戏动作）耦合较低，但需要处理动作重复和 Steam 客户端运行时依赖。方案 B（原生设备输入与 Steam Input 明确切换）离线能力更清晰，但分支测试与映射维护成本更高。当前建议 P2 前采用 A 的实验性边界，前提是 SDK 合法可得并完成设备实测。不得宣称自适应扳机已支持。
