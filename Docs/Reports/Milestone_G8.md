# G8 场景、表现与性能验收

2026 年 11 月 19 日测试，11 月 20 日复核。铸场可运行，实测达到本机 1080p 平均 60 FPS 的目标。

| 项目 | 结果 |
|---|---|
| 1. 名称与目标 | G8。完成暗黑铸场、四类训练目标、玩家与武器表现，复测训练规则及性能。 |
| 2. 完成功能 | 铸铁与玄武岩表面、铜饰、符文窄桥、塔楼、火炬、雾与区域照明。四类目标沿用工坊数据。符文武器提供施法、充能、命中声音和闪光。结算与历史支持曲线及相同条件重试。 |
| 3. 变更文件 | `Scripts/ArtForge.py` 生成场景、材质与合成音效；`Content/Training/Forge.umap`、`Materials/M_AntiqueBrass`、`M_Basalt`、`M_CastIron`、`Audio/S_Cast`、`S_Charge`、`S_Impact` 保存内容。`Config/DefaultEngine.ini`、`DefaultGame.ini` 配置渲染与打包。`Source/FPSArena/Practice` 下的 `ForgeBenchmark.cpp/.h`、`ForgeCharacter.cpp`、`ForgeHUD.cpp`、`ForgeHistory.cpp`、`ForgeProfiles.cpp`、`ForgeTraining.cpp/.h` 和 `RangePrototype.cpp` 负责表现、历史、设置和测量。 |
| 4. 工程 Git 提交 | `b062db91b15ed952305b13d06c06a4e2cc9d2a75` |
| 5. 编译命令及结果 | **PASS**。`Build.bat FPSArenaEditor Win64 Development -Project=<FPSArena.uproject> -WaitMutex -Rebuild`，UBT 返回 `Succeeded`。编辑器也完成了材质和场景保存。[构建摘录](Evidence/Win64/G8-build-extract.txt) · [内容生成日志](Evidence/Win64/G8-material-save-extract.txt) |
| 6. 自动化测试 | **PASS**。九种模式各自结算并保存。综合挑战经过四段，动作连段产生四个节点。工坊保存、读取、战斗与重生均成功。这些是固定输入的功能回归分数。[九模式结果](Evidence/Win64/nine-modes.json) · [运行日志](Evidence/Win64/G8-smoke-extract.txt) |
| 7. 人工复测步骤 | 从大厅进入，切换 `V` 视角和 `Q` 肩位。分别在快慢移动下观察目标边缘、遮挡和闪光，在命中与充能时辨听声音。大厅中文显示已从 Shipping 截图核对。真人长时游玩和听感评审为 **UNVERIFIED**。[大厅原始截图](Evidence/Win64/ForgeHub.png) |
| 8. 实测环境 | Windows 10 家庭中文版 22H2，内部版本 19045。Ryzen 7 5800H、16 GB 内存、RTX 3060 Laptop 6 GiB、NVIDIA 驱动 621.01，Windows 平衡电源方案。UE 5.9 Win64 Shipping。GPU 功率上限查询返回 `N/A`。 |
| 9. 已知缺陷 | 曾发现打包后 HUD 字体显示异常，现已改用引擎 MediumFont，已从最终包核对大厅中文。三轮相同路线的帧率有差异，未采集温度或频率，无法归因。 |
| 10. 未完成事项 | 掌机、其他 GPU、其他分辨率及连续数小时的性能 **UNVERIFIED**。 |
| 11. 风险与阻断项 | 本次性能样本覆盖三种代表玩法，未分别为所有模式或任意复杂工坊布局做压力测试。 |
| 12. 下一阶段 | G9 使用同一玩法与表现基线做离线启动、存档重启回读和玩家包完整性验收。见 [G9 报告](Milestone_G9.md)。 |

## 帧时间

每轮 120 秒，同一种子 `173`。每 40 秒切换一次，依次为 M2 跟踪、M6 移动和 M9 战斗施法。测试窗口分辨率为 1920 × 1080，渲染比例 100%，关闭垂直同步，帧率无限制。记录的阴影、特效、抗锯齿、视距和纹理档位均为 3。采样从预热后开始，帧时间为连续游戏帧的墙钟间隔。

| 轮次 | 帧数 | 平均 FPS | 平均帧时间 | P95 帧时间 | 最大帧时间 | 超过 50 ms |
|---|---:|---:|---:|---:|---:|---:|
| 1 | 26,483 | 220.68 | 4.53 ms | 5.29 ms | 11.92 ms | 0 |
| 2 | 22,304 | 185.87 | 5.38 ms | 5.86 ms | 12.62 ms | 0 |
| 3 | 20,739 | 172.82 | 5.79 ms | 6.30 ms | 11.97 ms | 0 |

逐帧 CSV 按帧号复核，P95 取升序的第 `ceil(N × 0.95)` 帧。总计 69,526 帧、360.005 秒，按总帧数与总时间计算为 193.12 FPS。可用发行包中的 `FPSArena.exe -BTGBenchmark -windowed -ResX=1920 -ResY=1080 -ForceRes` 重跑；实际 CVar 值以每轮 JSON 为准。[性能汇总](Evidence/Win64/Performance/summary.json) · [第一轮 CSV](Evidence/Win64/Performance/Run1.csv) · [第二轮 CSV](Evidence/Win64/Performance/Run2.csv) · [第三轮 CSV](Evidence/Win64/Performance/Run3.csv)
