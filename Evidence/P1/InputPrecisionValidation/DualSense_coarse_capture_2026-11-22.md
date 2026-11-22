# DualSense 粗粒度输入采样（2026-11-22）

## 结果

隔离工程已使用 UE 5.9 `GameInputWindows`/`GameInput` 注册 DualSense Edge（VID `054C`、PID `0DF2`），日志确认 6 轴、12 按键映射初始化并完成设备连接。

本轮真实 CSV 记录了：

- 左右摇杆连续采样，X/Y 能达到全行程方向值；
- `LT_L2` 338 行，`RT_R2` 304 行；
- LT 原始值大部分在 `0–1`，有 1 个启动瞬态样本为 `1.121569`；RT 原始值为 `0–1`；
- 采样器的处理后扳机值已加入 `[0,1]` 限幅修复，但该修复后的扳机复采未完成。

## 当前验收口径

- DualSense GameInput 连接和粗粒度摇杆/扳机路径：`PASS`。
- DualSense 精细死区、中心漂移、异常跳变和完整按键逐帧数据：`UNVERIFIED（按项目负责人决定延期）`。
- 本轮不使用模拟数据，也不把 Xbox 数据替代 DualSense 数据。

原始证据：

- `Evidence/P1/InputPrecisionValidation/Raw/DualSense_2026-11-22/P1InputSamples_dualsense_sticks_partial.csv`
- `Evidence/P1/InputPrecisionValidation/Raw/DualSense_2026-11-22/P1InputSamples_dualsense_triggers_raw.csv`
- `Evidence/P1/InputPrecisionValidation/DualSense_sampler_GameInput_setup_2026-11-22.log`
