# Xbox 手柄自动化采样复验（2026-11-22）

## 范围

本次只使用隔离工程 `C:\P1InputValidation\P1InputValidation.uproject`，未修改 FPSArena 正式玩法。Windows 设备枚举为 Xbox One 控制器（VID `045E`）；运行日志注册为 `XInputInterface::XInputController`。采样器使用 UE 5.9 Enhanced Input 运行时映射，记录原始值、轴向死区输出、径向死区输出和按键状态。

## 构建与运行证据

- UBT 构建命令：`Build.bat P1InputValidationEditor Win64 Development -Project=C:\P1InputValidation\P1InputValidation.uproject -WaitMutex`
- 构建结果：`Result: Succeeded`
- 运行日志：`Evidence/P1/InputPrecisionValidation/Raw/Xbox_2026-11-22/P1InputValidation_buttons_and_full.log`
- 轴/扳机原始 CSV：`Evidence/P1/InputPrecisionValidation/Raw/Xbox_2026-11-22/P1InputSamples_xbox_axes.csv`
- 含按键的完整 CSV：`Evidence/P1/InputPrecisionValidation/Raw/Xbox_2026-11-22/P1InputSamples_xbox_full.csv`

## CSV 统计

完整 CSV 共 54,092 行，动作计数如下：

| 动作 | 行数 | 原始范围/状态 |
|---|---:|---|
| LeftStick | 23,554 | X/Y 均覆盖 `[-1, 1]`，最大模长 `1.154990` |
| RightStick | 23,554 | X/Y 均覆盖 `[-1, 1]`，最大模长 `1.114297` |
| LT_L2 | 1,057 | `0.011765–1.000000` |
| RT_R2 | 1,029 | `0.003922–1.000000` |
| A/B/X/Y | 643/639/870/660 | 均产生 `button_state=1` |
| LB/RB | 600/648 | 均产生 `button_state=1` |
| View/Menu | 95/131 | 均产生 `button_state=1` |
| LS/RS | 371/241 | 均产生 `button_state=1` |

## 死区、回中与跳变

- 轴向死区参数为 `0.12`。最终静止窗口中，左摇杆原始均值约 `(0.002960,-0.005859)`，右摇杆约 `(0.038179,-0.045839)`；两者原始最大模长分别 `0.006564` 和 `0.059656`，轴向输出均保持零。
- 径向死区参数为 `0.12`。相同静止窗口的径向输出均保持零；全行程和对角输入产生非零径向输出，说明径向分支实际执行。
- LT/RT 均达到 `1.0`，并记录了从低值到全行程的连续采样。
- 左右摇杆各有 1 次相邻样本步长超过 `0.75`，发生在用户从一个全行程方向切换到另一方向的动作边界；未发现额外重复跳变。LT/RT 没有超过 `0.75` 的相邻步长。
- 修正后的逐帧重复计数最大值为 `0`；CSV 中没有同一帧重复绑定事件证据。

## 状态

- Xbox 左右摇杆、LT/RT、A/B/X/Y、LB/RB、View/Menu、LS/RS：`PASS`（真实硬件 CSV）。
- 轴向与径向死区复验：`PASS`（原始/处理前后字段和静止窗口证据齐全）。
- 中心漂移：`PASS`（静止样本在径向死区内；保留原始偏移供复核）。
- 重复输入：`PASS`（修正逐帧集合后 duplicate_count 最大为 0）。
- 原始设备层字段 `device/connection/raw_layer_status`：`UNVERIFIED`。当前工具仍将底层 RawInput 层级标为 `UNVERIFIED`，因此不把 Enhanced Input 处理值冒充为 HID 原始报告。
