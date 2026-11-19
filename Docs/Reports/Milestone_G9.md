# G9 Windows 发行候选验收

2026 年 11 月 20 日。Windows x64 离线发行候选包通过本机功能、存档和性能验收。Steam 商业发行仍待平台权限验证与实体手柄签收。

## 交付物

| 文件 | 内容 |
|---|---|
| [Windows 玩家包](../../交付/BeastTrainingGrounds-Win64-Shipping.zip) | 完整解压后运行顶层 `FPSArena.exe`。47 个文件，343,176,129 字节，约 327.28 MiB。包含中文使用说明、运行库安装程序、素材来源和第三方许可。 |
| [SHA-256](../../交付/BeastTrainingGrounds-Win64-Shipping.zip.sha256) | `87aab879341bbe95e1541cdb7095a809142eae6b2c4ab158f9675c0ccf134017` |
| [包清单与校验记录](Evidence/Win64/package.json) | ZIP 所有条目的 CRC 校验通过，两级可执行文件的 SHA-256 与 UAT 暂存文件一致。 |

## 里程碑记录

| 项目 | 结果 |
|---|---|
| 1. 名称与目标 | G9。将本地单机游戏构建成可独立解压运行的 Windows Shipping 版本，并记录 Steam 发行门槛。 |
| 2. 完成功能 | 单场景、双视角、九种训练、目标工坊、战斗预演、输入配置、成绩与曲线、中英文界面、断开 Steam 后本地运行。玩家包携带 Steamworks DLL、动作清单与三个绑定布局。云存档已整理 Auto-Cloud 接入路径和规则。 |
| 3. 变更文件 | 工程的 `README.md` 为玩家说明，`Scripts/PackageWindows.ps1` 调用 UBT/UAT，`Scripts/ArchiveWindows.py` 生成 ZIP、校验和及文件清单；`docs/Release/Assets.zh-CN.md` 和 `SteamCloud.zh-CN.md` 分别记录资产来源和平台配置。文档仓库的本报告、G8 报告及 `Evidence/Win64` 保存验收结果。 |
| 4. 工程 Git 提交 | 游戏与 UAT 打包基线 `0c36fa86bcdc64d93ce6218cd5deba5af242e7eb`。最终交付脚本、说明及随包许可归档 `056897832840ce774e6b7e325e5bc5135f4528a6`。 |
| 5. 编译命令及结果 | **PASS**。Development Editor 全量 UBT 编译成功。Win64 Shipping 的 UAT Build、Cook、Stage 和 Archive 成功，Cook 报 0 错误、0 警告，退出码 0。复现命令见下文。[UBT 日志](Evidence/Win64/G9-release-build-extract.txt) · [UAT 日志](Evidence/Win64/G9-release-package-extract.txt) |
| 6. 自动化测试 | **PASS**。终版源码重新运行 5 项引擎测试，涵盖手柄报文、配置损坏恢复、设置与帧率、训练生命周期、跟踪规则。另启游戏模式完成 M1–M9，工坊保存、加载、战斗及重生均通过，两项命令退出码均为 0。[5 项测试](Evidence/Win64/G9-final-tests-extract.txt) · [九模式终版回归](Evidence/Win64/G9-final-smoke-extract.txt) |
| 7. 人工复测步骤 | 解压后双击程序，按 `F1` 改灵敏度并用 `Enter` 保存，按 `R` 完成 M1，回大厅选 M2、按 `N` 换种子再训练。退出重启后打开设置核对原值，按 `H` 打开历史、`R` 重试，核对种子及新成绩。该路径已用 Windows 窗口键盘事件实测 **PASS**；真人手感 **UNVERIFIED**。 |
| 8. 实测环境 | Windows 10 19045、Ryzen 7 5800H、RTX 3060 Laptop 6 GiB、16 GB 内存、驱动 621.01。Steam 客户端未运行。窗口输入复测使用独立 `UserDir`；第二次从解压包启动全新进程。性能采样为 1080p。[G8 性能记录](Milestone_G8.md) |
| 9. 已知缺陷 | 暂存曾因 Zen Cook 流程失败，已改用文件 Cook 并重复出包成功。测试范围内未发现阻断离线启动、训练或重启回读的崩溃。游戏窗口的桌面截图接口连续超时，重启交互以实际落盘数据交叉验证；大厅由游戏内截图确认。 |
| 10. 未完成事项 | **UNVERIFIED**。Xbox 和 DualSense USB／蓝牙逐键实操、体感方向、扳机阻力、震动触感、外部端到端延迟、干净 Windows 系统安装。跨版本升级回滚只覆盖已有配置格式和备份恢复用例，缺少已发行旧版升级样本。 |
| 11. 风险与阻断项 | **BLOCKED**。缺少可核验的本产品 Steam App ID 和合作伙伴账户权限。Steam 客户端启动、私有分支安装、正式动作布局、云同步及商店提审均未验证。**UNVERIFIED**。同一 Windows 用户切换多个 Steam 账户的存档隔离、配额及冲突恢复。 |
| 12. 下一阶段 | 有实体设备和正式 App ID 后，按 G7 硬件矩阵验收，在私有分支执行 Steam 启动和双机存档往返，记录结果后决定商业发行。 |

## 从发行程序验证重启

首次运行在独立用户目录里将灵敏度由默认 `150` 改为 `165`，生成了 JSON 和 SaveGame 备份。M1 以种子 `173` 完成，成绩 8。随后 M2 使用新种子 `359203`，成绩 6。

解压包的新进程从同一配置再增加一次灵敏度，结果为 `180`。从历史页发起重试后，游戏再次完成了 M2，保留 `359203` 和同一难度，生成新的局标识、成绩与轨迹文件。三局均标记为正常完成，轨迹分别有 1,517、1,674、1,659 个样本。两次 M2 均为 6 分。这组输入用于复核回读与复测流程。[会话、结果与文件摘要](Evidence/Win64/shipping-restart.json)

最终 ZIP 在新的解压内容中启动顶层程序并完成引擎截图后正常退出。该包与键盘回归使用的版本逐文件核对，31 个游戏运行文件字节相同，归档更新涉及说明、许可和 VC++ 运行库安装程序。[解压启动记录](Evidence/Win64/archive-launch.json)

## 构建与复测

在 `FPSArena.uproject` 所在目录执行下列 PowerShell 命令。归档脚本使用 Python 3.11 及以上版本；这台机器使用 Python 3.12。

```powershell
$engine = 'C:\Program Files\Epic Games\UE_5.9\Engine'
$project = (Resolve-Path FPSArena.uproject).Path
& "$engine\Build\BatchFiles\Build.bat" FPSArenaEditor Win64 Development "-Project=$project" -WaitMutex -Rebuild
& "$engine\Binaries\Win64\UnrealEditor-Cmd.exe" $project -BTGSmoke '-ExecCmds=Automation RunTests FPSArena' '-TestExit=Automation Test Queue Empty' -NullRHI -NoSound -Unattended
& "$engine\Binaries\Win64\UnrealEditor-Cmd.exe" $project -game -BTGSmoke -NullRHI -NoSound -Unattended -Seconds=110
.\Scripts\PackageWindows.ps1
python .\Scripts\ArchiveWindows.py .\Saved\Deliverables\BeastTrainingGrounds-Win64-Shipping.zip
```

在编辑器中打开 `/Game/Training/Forge` 并启动 PIE，可用 `[`、`]` 切换模式，`R` 开始，`F2` 进入工坊。实体手柄验收项见 [G7 报告](Milestone_G7.md)。
