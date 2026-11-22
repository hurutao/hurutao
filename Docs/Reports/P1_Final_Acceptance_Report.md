# P1 Final Acceptance Report

日期：2026-11-20

## 本轮剩余任务状态

| 项目 | 状态 | 证据 |
|---|---|---|
| Unreal Editor 独立图形启动 | PASS | CUA 窗口清单观察到 `UnrealEditor.exe` |
| Unreal Editor 独立图形关闭 | PASS | `Alt+F4` 后 UE 窗口从清单消失 |
| 通过 GUI 打开 FPSArena P1 工程 | BLOCKED | CUA 截图通道超时，窗口无可用项目打开控件 |
| Xbox 基础控制 | HUMAN-VERIFIED | 项目负责人已人工确认可以正常控制游戏，尚无自动化采样日志 |
| DualSense 基础控制 | HUMAN-VERIFIED | 项目负责人已人工确认可以正常控制游戏，尚无自动化采样日志 |
| UE Enhanced Input 精度采样 | UNVERIFIED | 已建立隔离采样工具，但尚无真实逐帧 CSV |
| GitHub Beast-Training-Grounds remote | BLOCKED | `git remote -v` 无输出 |
| GitHub 读写权限 | BLOCKED | 无远程地址和认证目标 |
| 本地 P1 提交 | PASS | `410b06d` |
| Git LFS 本地配置 | PASS | Git LFS `3.8.1`，filter/storage 有效 |

## 结论

本轮完成了真实 Unreal Editor 独立启动和关闭验证，也确认 Windows 当前连接了 Xbox One 和 DualSense Edge 实体控制器。UE 内 Enhanced Input 采样被 GUI 工程打开路径阻断，不能用系统枚举或模拟值替代。GitHub 远程检查被无 remote 阻断，没有执行推送或历史改写。

P1 仍未完成，不能进入 P2。下一轮需要先解决工程 GUI 启动路径或使用经批准的编辑器启动方式，再完成两类实体控制器的 UE 输入采样。GitHub 需要项目负责人提供或配置 Beast-Training-Grounds 私有仓库 remote 后，才能验证权限和推送状态。

已建立隔离 P1 Enhanced Input 采样工具，未修改正式玩法。基础手柄控制为 HUMAN-VERIFIED，输入精度自动化采样仍为 UNVERIFIED。没有开发正式场景、角色、武器、怪物或训练玩法。


## ea421a1 工具审计补充

指定提交 a421a1 包含采样器源码和 CSV 模板，但缺少可运行 UE 工程入口，且其 Get<FVector3f>() 调用无法通过 UE 5.9 编译。因此该提交不能标记为可运行工具。后续隔离工程已修正并通过 UBT 编译，但没有真实 Xbox/DualSense 运行时采样，输入精度、死区、重复输入、中心漂移和异常跳变均保持 UNVERIFIED。证据见 Evidence/P1/InputPrecisionValidation/ea421a1_audit.md。


## 手柄采样工具运行时补充

隔离工程已通过 UE 5.9 UBT 编译并在图形运行窗口中产生 P1_INPUT_SAMPLE 日志，CSV 写盘已验证。当前 CSV 的设备标签仍为 Unknown，且项目负责人尚未完成 Xbox/DualSense 动作序列，因此真实硬件精度、死区、中心漂移、异常跳变和重复映射仍为 BLOCKED/UNVERIFIED。


## Xbox / DualSense 实测补充

Xbox 已在仅连接 Xbox One 控制器的条件下产生真实 CSV，摇杆 X/Y 均在 [-1,1]，LT/RT 在 [0.007843,1.0]，相邻样本大跳变检查为 0 次。径向死区修正后尚需复采。DualSense 动作序列已执行，但对应运行窗口没有产生回调或 CSV，状态为 BLOCKED。详细分析见 Evidence/P1/InputPrecisionValidation/P1_Hardware_Analysis.md。


## DualSense 输入故障诊断补充

Windows PnP 可识别 DualSense，但 UE 日志只注册 XInputInterface::XInputController，没有注册 DualSense 游戏输入设备。当前 Gamepad_* Enhanced Input 映射因此只能驱动 Xbox/XInput。DualSense 状态为 Windows PASS、当前 UE 映射 FAIL、采样 BLOCKED。证据见 Evidence/P1/InputPrecisionValidation/DualSense_diagnosis.md。

## RawInput 接入复核

隔离工程启用 UE 5.9 RawInput 后，UnrealEditor-Cmd 在 BeginPlay 枚举设备时发生 `EXCEPTION_ACCESS_VIOLATION`，调用栈进入 `UnrealEditor-RawInput.dll`。该插件路径状态为 FAIL，已移除隔离工程依赖并重新通过 UBT 编译。证据见 Evidence/P1/InputPrecisionValidation/RawInput_plugin_test.md。DualSense 自动化采样仍为 BLOCKED，P1 尚未完成，禁止进入 P2。

## 2026-11-22 复核

Windows 当前仍能识别 DualSense Edge，设备状态为 `OK`。Codex 配置的 `http://127.0.0.1:8000/mcp` 当前无监听服务。隔离工程重新编译通过，DualSense 仍没有 UE Enhanced Input 回调和原始 CSV。详细记录见 Evidence/P1/InputPrecisionValidation/p1_recheck_2026-11-22.md。P1 继续保持未完成状态。

## DualSense 驱动栈审计补充

DualSense 手柄接口使用 Windows 标准 HID/HidUsb 驱动。系统安装了 Nefarius ViGEmBus，但没有活动虚拟手柄，也没有运行中的 Steam、DS4Windows 或 reWASD 进程。驱动层审计为 PASS，UE RawInput 轴事件链路仍未产生采样回调。证据见 Evidence/P1/InputPrecisionValidation/DualSense_driver_audit_2026-11-22.md。

