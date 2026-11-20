# P1 手柄输入精度验证报告

日期：2026-11-20

## 设备与基础控制

| 项目 | 状态 | 说明 |
|---|---|---|
| Xbox 基础手柄控制 | HUMAN-VERIFIED | 项目负责人已在 UE 5.9 FPSArena 工程中人工确认可以正常控制游戏 |
| DualSense 基础手柄控制 | HUMAN-VERIFIED | 项目负责人已在 UE 5.9 FPSArena 工程中人工确认可以正常控制游戏 |
| 自动化采样日志 | UNVERIFIED | 当前没有逐帧输入采样日志 |
| Windows 设备存在 | PASS | PnP 曾报告 Xbox One 控制器和 DualSense Edge 均为 OK |

## 隔离工具

已建立隔离工具目录 `Evidence/P1/InputPrecisionValidation`，包含 `InputPrecisionSampler.h/.cpp`、CSV 字段文件和使用说明。工具只记录 P1 验证数据，不接入正式角色、武器或训练玩法。

## 采样字段

工具设计记录：

- 左右摇杆 X/Y
- LT/RT 或 L2/R2
- 主要按键状态
- 回调时间戳
- Enhanced Input 回调值
- 轴向死区处理结果
- 径向死区处理结果
- 重复回调计数
- 原始设备层级状态

## 实际数据状态

`InputPrecisionSamples.csv` 目前只有字段行和设备占位行，没有填入任何模拟数值。以下测试均为 `UNVERIFIED`：

- 摇杆回中
- 微小输入
- 全行程
- 对角输入
- 轴向与径向死区的硬件对比
- Xbox 真实逐帧采样
- DualSense 真实逐帧采样
- Steam Input 或其他映射层重复输入检查

原因是本轮尚未在 UE 运行时加载该隔离工具并接收真实手柄事件。没有使用模拟输入替代硬件测试。

## P1 结论

基础控制可以记录为 `HUMAN-VERIFIED`，但输入精度验收仍未完成。需要在隔离验证工程中运行工具并分别采集 Xbox、DualSense 的真实 CSV 后，才能判断死区、全行程、对角输入和重复映射。
