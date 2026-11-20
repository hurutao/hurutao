# P1 Enhanced Input 精度采样工具

该目录是隔离的 P1 技术验证工具，不属于 FPSArena 正式玩法代码。

## 目标

- 通过 Enhanced Input Action 回调记录左右摇杆、LT/RT 或 L2/R2、主要按键
- 记录世界时间戳、动作值、死区处理前后值和设备标签
- 对比轴向死区与径向死区
- 统计重复回调，用于发现 Steam Input 与原生输入重叠

## 当前限制

本轮尚未在 UE 运行时执行该工具，因此 CSV 只有字段定义，没有伪造的硬件样本。项目负责人已经人工确认 Xbox 与 DualSense 可以控制游戏，这一项记录为 `HUMAN-VERIFIED`，不等同于自动化采样通过。

## 使用边界

需要在隔离 P1 验证工程中配置 Input Action 和 Mapping Context 后运行。不得把本工具接入正式角色、武器或训练模式。
