# PS5 手柄输入取消记录

日期：2026-11-22

项目负责人决定取消正式 FPSArena 项目中的 PS5/DualSense 输入支持。已从正式工程移除 DualSense HID 原生读取、PS5 专用 Steam Input 配置、PS5 自适应扳机、PS5 陀螺仪路径和 DualSense 专用自动化测试。通用 Xbox/Steam 手柄动作映射保留。

正式工程提交：`0020ae6 input: remove PlayStation controller support`

使用 UE 5.9 UnrealBuildTool 完整编译 `FPSArenaEditor Win64 Development`，结果为 `Result: Succeeded`。

P1 验收范围更新为 Xbox/通用手柄输入。DualSense 不再作为正式项目验收项。GitHub 远程权限和 Xbox 径向死区复采仍需单独完成。
