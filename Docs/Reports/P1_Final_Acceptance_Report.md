# P1 Final Acceptance Report

日期：2026-11-22

> 说明：本报告保留了前序轮次的历史状态和阻断记录。报告末尾的“P1 最终验收复核（当前有效）”覆盖此前状态，是本次验收的最终结论。

## 本轮剩余任务状态

| 项目 | 状态 | 证据 |
|---|---|---|
| Unreal Editor 独立图形启动 | PASS | CUA 窗口清单观察到 `UnrealEditor.exe` |
| Unreal Editor 独立图形关闭 | PASS | `Alt+F4` 后 UE 窗口从清单消失 |
| 通过 GUI/运行入口打开 FPSArena P1 工程 | PASS | `/Game/Training/Forge` 运行日志确认 GameInput 初始化和实体设备连接 |
| Xbox 基础控制 | HUMAN-VERIFIED | 项目负责人已人工确认可以正常控制游戏，尚无自动化采样日志 |
| DualSense 基础控制 | HUMAN-VERIFIED | 项目负责人已人工确认可以正常控制游戏，尚无自动化采样日志 |
| UE Enhanced Input 精度采样 | PASS（Xbox）；UNVERIFIED（DualSense 精细数据延期） | Xbox 已有真实逐帧 CSV；DualSense 已完成 GameInput 粗粒度采样，精细数据按负责人决定延期 |
| GitHub `hurutao/hurutao` remote | PASS（网页存在性） | GitHub 页面可打开，仓库为 Public，默认分支 `main`；本地 origin 已更新为该地址 |
| GitHub Git CLI 读写权限 | PASS | `git push --dry-run origin master` 返回 `new branch master -> master` |
| GitHub 连接器登录 | PASS | `github_get_profile`、`github_get_repo` 和权限查询均成功返回 |
| P1 提交是否已推送 | PASS | 已执行普通 `git push origin master`，远程 `master` 与本地提交一致 |
| 本地 P1 提交 | PASS | 本次报告提交后以本地 `HEAD` 与远程 `origin/master` 核对 |
| Git LFS 本地配置 | PASS | Git LFS `3.8.1`，filter/storage 有效 |

## 结论

本轮完成了真实 Unreal Editor 独立启动和关闭验证，也确认 Windows 当前连接了 Xbox One 和 DualSense Edge 实体控制器。隔离 UE 采样工具已经通过 UBT 编译并产生 Xbox 真实逐帧数据，DualSense GameInput 粗粒度采样已经完成。GitHub 远程存在性、Git CLI 读写、实际推送和 Codex GitHub connector 登录均已复核通过。

P1 的硬验收项已满足。DualSense 精细死区、中心漂移、异常跳变和完整按键逐帧数据按项目负责人决定延期，保留为 `UNVERIFIED（延期）`，不阻塞本轮 P1 关闭。P2 尚未开始，等待项目负责人审批。

已建立隔离 P1 Enhanced Input 采样工具，未修改正式玩法。Xbox 自动化精度采样为 PASS；DualSense GameInput 粗粒度采样为 PASS，精细数据按负责人决定延期为 `UNVERIFIED（延期）`。基础手柄控制为 HUMAN-VERIFIED。没有开发正式场景、角色、武器、怪物或训练玩法。


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

## DualSense 最终采样复核

项目负责人已在前台运行窗口完成摇杆、扳机和按键操作。采样器和 RawInput 设备注册日志正常，但没有生成 `P1_INPUT_SAMPLE`、`P1_RAW_AXIS` 或新增 CSV 数据。该项最终状态为 BLOCKED，证据见 Evidence/P1/InputPrecisionValidation/DualSense_capture_final_blocker_2026-11-22.md。P1 不能完成验收。

## Steam Input 路径人工验证

项目负责人反馈，启动 Steam Input 后启动 UE5，DualSense 已能够控制 UE5 模型视野。该路径状态为 HUMAN-VERIFIED，证明 Steam Input 能提供可用的控制转换。隔离采样工程尚未产生 Steam Input 路径的自动化 CSV，因此精度、死区、重复输入和异常跳变仍为 UNVERIFIED。证据见 Evidence/P1/InputPrecisionValidation/SteamInput_human_verification_2026-11-22.md。

在 Steam 进程运行期间直接启动隔离 P1 工程，UE 没有注册 `XInputInterface::XInputController`，也没有产生采样回调。Steam Input 需要从 Steam 接管的非 Steam 游戏快捷方式启动该工程。证据见 Evidence/P1/InputPrecisionValidation/SteamInput_direct_launch_check_2026-11-22.md。

## PS5 输入范围变更

项目负责人决定取消正式 FPSArena 项目中的 PS5/DualSense 输入支持。正式工程已移除 DualSense HID、PS5 Steam Input 配置、自适应扳机、陀螺仪和专用测试，保留通用 Xbox/Steam 手柄输入。正式工程使用 UE 5.9 UnrealBuildTool 完整编译通过，提交为 `0020ae6 input: remove PlayStation controller support`。证据见 Evidence/P1/InputPrecisionValidation/PlayStation_support_removed_2026-11-22.md。DualSense 不再作为正式项目 P1 验收项。

## 非 DualSense 项复核

Unreal MCP 服务已恢复并通过 `initialize` 握手，服务端为 `unreal-mcp`，UE 版本为 `5.9.0-60351404`，项目为 FPSArena。MCP 状态更新为 PASS。

GitHub 连接器当前未登录，返回 `USER_NOT_LOGGED_IN`。本地仓库仍没有 `git remote`，因此 Beast-Training-Grounds 远程地址、读写权限和推送状态继续为 BLOCKED。不能凭空设置远程地址。

截图确认 GitHub 浏览器账户为 `hurutao`，本地已配置 `origin=https://github.com/hurutao/Beast-Training-Grounds.git`。`git ls-remote` 因当前环境连接 `github.com:443` 超时而未完成，Codex GitHub connector 仍返回 `USER_NOT_LOGGED_IN`。远程存在性、读写权限和推送状态继续为 BLOCKED。证据见 Evidence/P1/InputPrecisionValidation/github_remote_setup_2026-11-22.md。

Xbox CSV 缺少原始轴列的数值，现有文件只能验证处理后范围和跳变，不能从旧文件重新证明径向死区修正后的输出。径向死区复采继续为 UNVERIFIED。

## 当前有效验收快照（2026-11-22）

本节覆盖此前记录之后的最新范围决定和验证结果。此前关于 DualSense 采样阻断和取消支持的内容保留为历史证据。本轮根据已找到的 GameInput 实现恢复 DualSense 的正式输入接入，实际硬件事件仍需前台操作日志。

| 验收项 | 当前状态 | 依据 |
|---|---|---|
| 正式项目 DualSense GameInput 接入 | PASS | GameInput 识别 `054C:0DF2`，映射初始化 6 轴、12 按键 |
| DualSense 基础控制 | HUMAN-VERIFIED | 项目负责人确认已可控制 FPSArena 画面，尚无自动化逐帧 CSV |
| DualSense 左右摇杆方向 | HUMAN-VERIFIED | 项目负责人确认左右摇杆方向均正常 |
| DualSense GameInput 粗粒度采样 | PASS | GameInput 注册 `054C:0DF2`，隔离 CSV 记录左右摇杆及 LT/RT；精细数据按负责人决定延期 |
| 正式项目 Xbox/通用手柄输入 | 保留 | 通用 Gamepad/Steam Input 动作映射未删除 |
| 正式项目 UE 5.9 完整编译 | PASS | UnrealBuildTool 输出 `Result: Succeeded` |
| Unreal MCP 握手 | PASS | `serverInfo.name=unreal-mcp`，`projectName=FPSArena` |
| Xbox 径向死区复采 | PASS | `Evidence/P1/InputPrecisionValidation/Raw/Xbox_2026-11-22/P1InputSamples_xbox_full.csv` 含 `raw_x/raw_y`、轴向和径向输出；静止窗口径向输出为零，全行程/对角输入产生非零输出 |
| Xbox 摇杆、扳机和按键逐帧 CSV | PASS | 完整 CSV 共 54,092 行，含 LeftStick/RightStick、LT_L2/RT_R2 和 10 个按键动作 |
| Xbox 中心漂移与重复输入 | PASS | 静止窗口原始偏移在径向死区内；修正逐帧重复计数后 `duplicate_count` 最大为 0 |
| GitHub 远程存在性 | PASS（网页） | `https://github.com/hurutao/hurutao` 可打开，Public，默认分支 `main` |
| GitHub Git CLI 读写权限 | PASS | dry-run 已被远程接受 |
| GitHub 连接器登录 | PASS | `github_get_profile`、`github_get_repo`、`github_get_repo_collaborator_permission` 均成功；仓库权限为 `admin` |
| GitHub Git CLI P1 推送 | PASS | 普通 `git push origin master` 成功，远程 master 与本地 HEAD 一致 |
| P1 是否可进入 P2 | PASS（待项目负责人审批） | P1 硬验收项已完成；DualSense 精细数据明确延期，不自动启动 P2 |

DualSense 的 GameInput 接入层已恢复并通过运行日志验证，之前的 PS5 专用 Steam/HID 路径仍保持移除。Xbox 自动化采样、GitHub 网页存在性、Git CLI 写权限、P1 推送和 Codex GitHub connector 权限均已完成；项目仍停留在 P1，等待项目负责人审批后再决定是否进入 P2。

## Xbox 实体输入自动化复验（2026-11-22）

隔离工程已重新编译并在运行模式下捕获 Xbox One 控制器的真实 Enhanced Input 数据。完整 CSV 共 54,092 行：左右摇杆 X/Y 均覆盖 `[-1,1]`，LT/RT 均达到 `1.0`，并产生 A/B/X/Y、LB/RB、View/Menu、LS/RS 十个按键的 `button_state=1` 记录。原始轴值、处理前值、轴向死区值和径向死区值均写入 CSV。详细统计和文件路径见 `Evidence/P1/InputPrecisionValidation/Xbox_recapture_2026-11-22.md`。

静止窗口左摇杆原始最大模长为 `0.006564`、右摇杆为 `0.059656`，两者轴向和径向死区输出均为零；全行程和对角输入产生非零径向输出。修正逐帧集合清理后，`duplicate_count` 最大为 `0`。左右摇杆各有一次超过 `0.75` 的相邻步长，均出现在用户切换全行程方向的动作边界；没有额外异常跳变。Xbox 径向死区复采、中心漂移和重复输入更新为 `PASS`。

采样器仍将 `device`、`connection` 和 `raw_layer_status` 标为 `UNVERIFIED`，因为本轮验证的是 XInput/Enhanced Input 处理链路，没有把处理后的值冒充 HID 原始报告。原始 CSV 和运行日志位于 `Evidence/P1/InputPrecisionValidation/Raw/Xbox_2026-11-22/`。

## 当前 P1 验收结论（更新后）

- `PASS`：隔离采样工具可编译、可运行并产生真实 Xbox CSV；摇杆、扳机、十个主要按键、轴向/径向死区、中心静止窗口和逐帧重复计数均有证据。
- `HUMAN-VERIFIED`：FPSArena 中 Xbox 与 DualSense 基础控制，以及 DualSense 左右摇杆方向。
- `PASS`：GitHub `hurutao/hurutao` 网页存在性已确认，仓库为 Public，默认分支为 `main`；本地 `origin` 已更新为该准确地址。
- `PASS`：Git CLI 对 `hurutao/hurutao` 的推送权限已通过 `git push --dry-run origin master` 验证，远程返回将创建 `master` 分支。
- `BLOCKED`：GitHub 连接器账号连接仍返回 `USER_NOT_LOGGED_IN`。
- `PASS`：项目负责人授权后已执行普通 `git push origin master`，远程 `master` 与本地 HEAD 已重新核对一致。
- `UNVERIFIED`：采样 CSV 的底层 `RawInput/HID` 原始层级和设备字段；这不影响本轮 XInput/Enhanced Input 处理链路的 Xbox 验证。

P1 仍未完成，禁止进入 P2。下一步只剩项目负责人完成 GitHub 连接器登录或提供可访问的准确远程仓库后，复核远程存在性、读写权限和本地提交推送状态；完成后停止并等待项目负责人验收。

本轮已将包含 Xbox 采样、GitHub 复核、推送证据和最终验收报告的本地提交，通过普通 `git push origin master` 推送到远程 `master`；提交身份为 `local-user <local@localhost>`。Codex GitHub connector 认证仍未通过。

## 当前准确 GitHub 仓库复核（2026-11-22）

项目负责人确认的准确地址为 `https://github.com/hurutao/hurutao`。网页可访问该仓库，页面显示仓库为 Public、默认分支为 `main`，当前页面可见历史为 1 个提交，因此仓库存在性状态更新为 `PASS（网页存在性）`。本地 `origin` 已按负责人提供的地址更新，随后已将本地 `master` 分支推送到远程；实际推送证据见 `Evidence/P1/InputPrecisionValidation/github_push_2026-11-22.md`。

GitHub 连接器调用仍返回 `USER_NOT_LOGGED_IN`，本机对该地址执行 `git ls-remote` 曾在 `github.com:443` 超时。网页公开可读本身不等于写权限；随后 Git CLI dry-run 已单独验证写权限，但实际 P1 推送仍未执行，连接器登录仍未完成。

补充验证：先通过 `git push --dry-run origin master` 验证写权限，随后在项目负责人明确授权后执行普通 `git push origin master`，并同步了最终报告提交。最后一次 `git ls-remote origin refs/heads/master` 与本地 HEAD 核对一致，实际 P1 推送状态为 `PASS`。连接器登录仍为 `BLOCKED`，证据见 `Evidence/P1/InputPrecisionValidation/github_push_2026-11-22.md`。

## DualSense 隔离采样工具修复（2026-11-22）

为完成 P1 的 DualSense 自动化采样，隔离工程已启用 UE 5.9 `GameInputWindows`/`GameInput`，增加 `GameInputBase` 依赖，并加入 DualSense Edge `054C:0DF2` 的 6 轴、12 按键运行时映射。工程通过 UBT 编译，结果为 `Result: Succeeded`；运行日志确认 GameInput 模块启动并输出 `P1_INPUT DualSense GameInput mappings initialized: 6 axes, 12 buttons`。证据见 `Evidence/P1/InputPrecisionValidation/DualSense_sampler_GameInput_setup_2026-11-22.log`。

本次运行时已检测到 DualSense 并生成真实摇杆和 LT/RT CSV。由于项目负责人决定将精细输入数据留到后期调试，DualSense 的精细死区、中心漂移、异常跳变和完整按键逐帧数据保留为 `UNVERIFIED（延期）`；粗粒度 GameInput 路径更新为 `PASS`。证据见 `Evidence/P1/InputPrecisionValidation/DualSense_coarse_capture_2026-11-22.md`。

## DualSense GameInput 修复复核（2026-11-22）

项目负责人提供了已跑通 DualSense 的实现线索。经本机工程审计，`NovaShooter` 使用 UE 5.9 `GameInputWindows`/`GameInputBase`，通过 DualSense Edge 的 `054C:0DF2` VID/PID 配置和运行时映射补齐接通设备。该实现已移植到 FPSArena。

FPSArena 已启用 `GameInputWindows`、`GameInput`，增加 `GameInputBase` 依赖，并在 `ForgeController.cpp` 中配置 6 个轴、12 个按键。UE 5.9 UnrealBuildTool 完整编译结果为 `Result: Succeeded`。

运行日志已确认：

- `DualSense Edge GameInput mappings initialized: 6 axes, 12 buttons.`
- `Game Input Device Connected ... ProdId: 0df2 (3570) VendId: 054c (1356)`
- `RegisterDevice: DeviceId=1 InputDeviceName=GameInput HardwareDeviceIdentifier=Hid`

因此 DualSense 的 Windows/UE GameInput 接入层状态为 PASS，基础控制更新为 `HUMAN-VERIFIED`。自动化逐帧摇杆、扳机和按键 CSV 尚未生成，精度、死区、中心漂移、重复输入和异常跳变仍保持 UNVERIFIED。详细证据见 `Evidence/P1/InputPrecisionValidation/GameInput_DualSense_fix_2026-11-22.md`。

## DualSense 摇杆方向修正（2026-11-22）

对照项目负责人反馈，FPSArena 的 `Gamepad_LeftY` 使用 `Scalar=-1.0`，右摇杆 `Gamepad_RightY` 使用 `Scalar=+1.0` 以匹配 FPSArena 相机链路。修正后已重新通过 UE 5.9 UnrealBuildTool，并重新启动 `/Game/Training/Forge`。项目负责人确认左右摇杆方向均正常，方向状态更新为 `HUMAN-VERIFIED`。证据仍记录在 `Evidence/P1/InputPrecisionValidation/GameInput_DualSense_fix_2026-11-22.md`。

## P1 最终验收复核（当前有效，2026-11-22）

本节为当前有效的收口状态，覆盖此前连接器未登录时的历史记录。已实际调用 Codex GitHub connector 完成复核：

- `github_get_profile`：认证账号为 `hurutao`，调用成功。
- `github_get_repo({repository_full_name:"hurutao/hurutao"})`：仓库存在，`visibility=public`，默认分支为 `main`；返回 `admin=true`、`maintain=true`、`pull=true`、`push=true`、`triage=true`。
- `github_get_repo_collaborator_permission`：`hurutao` 在 `hurutao/hurutao` 的权限为 `admin`。
- `github_search_branches`：远程 `master` 分支存在。
- 逐次调用结果已记录在 `Evidence/P1/InputPrecisionValidation/github_connector_verification_2026-11-22.md`。
- 既有 P1 提交已通过普通 `git push origin master` 推送；本次报告更新时 Git CLI 重试遭遇 `Recv failure: Connection was reset`，因此使用已授权的 connector Contents API 将报告和证据文件以两个快进提交写入远程 `master`。未使用强制推送或覆盖远程历史。

### 最终状态

| 类别 | 状态 | 证据路径或说明 |
|---|---|---|
| PASS | P1 隔离采样工具可编译、可运行 | UE 5.9 UBT 输出 `Result: Succeeded`；工具源码在 `Evidence/P1/InputPrecisionValidation/Project/Source/P1InputValidation/` |
| PASS | Xbox 真实输入、轴向/径向死区、中心漂移、重复输入 | `Evidence/P1/InputPrecisionValidation/Raw/Xbox_2026-11-22/`；完整 CSV 54,092 行 |
| PASS | DualSense GameInput 接入及粗粒度采样 | `Evidence/P1/InputPrecisionValidation/DualSense_coarse_capture_2026-11-22.md` 及同目录 Raw CSV/日志 |
| HUMAN-VERIFIED | FPSArena 中 Xbox 与 DualSense 基础控制、DualSense 左右摇杆方向 | 项目负责人前台人工确认 |
| PASS | GitHub 仓库存在、Git CLI 读写、P1 提交推送 | `https://github.com/hurutao/hurutao`；`origin`；普通 `git push origin master` |
| PASS | Codex GitHub connector 登录与仓库权限 | `Evidence/P1/InputPrecisionValidation/github_connector_verification_2026-11-22.md`；仓库权限 `admin` |
| UNVERIFIED（延期） | DualSense 精细死区、中心漂移、异常跳变、完整按键逐帧统计 | 项目负责人明确决定后期再调试；当前不伪造精细数据 |
| FAIL | 本轮硬验收项 | 无 |
| BLOCKED | 本轮硬验收项 | 无 |

### P1/P2 门禁

P1 硬验收项当前为 `PASS`。DualSense 精细数据属于已明确延期的 `UNVERIFIED（延期）`，不是本轮硬阻塞。P2 **尚未启动**，本报告在项目负责人审批前停止；不得据此自动进入 P2。


