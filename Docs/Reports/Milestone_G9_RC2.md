# G9 第二版 Windows 发行候选 · 存档与回滚验收

2026 年 11 月 20 日。此修订针对 Windows 存档覆盖失败和异常成绩干扰历史重试的问题。工程提交为 `7a494cdb9c75a1acdd5a717f7332594626b76038`，测试基线 RC1 为 `056897832840ce774e6b7e325e5bc5135f4528a6`。

[当前玩家包](../../交付/BeastTrainingGrounds-Win64-Shipping.zip) · [SHA-256](../../交付/BeastTrainingGrounds-Win64-Shipping.zip.sha256) · [归档清单](Evidence/Win64/RC2/package.json) · [上一版验收与可回滚包](Milestone_G9.md)

## 修订和验收

| 项目 | 验收结果 |
|---|---|
| Windows 文件替换 | **PASS**。在同一存档目录先完成临时文件写入，再调用 Windows 原子替换。测试持有一个禁止删除共享的文件句柄，确认替换失败后旧 JSON 仍可读取，解锁重试可写入新值，临时文件清理正常。 |
| 回滚时保护新版数据 | **PASS**。共享 JSON 写入函数读取目标文件版本，拒绝覆盖已识别的较新格式。设置页面显示新版输入配置只读，允许切换到其他可写配置档。测试覆盖启动前已存在和对象加载后才出现的新版数据。 |
| 历史成绩重试 | **PASS**。只接受具备有效局标识、战斗设置、模式、难度、整数成绩和种子的记录。较早的有效记录可在缺少新增遥测字段时继续使用。内容无效或高版本文件保留在磁盘上。 |
| 编译与游戏回归 | **PASS**。UBT 编译 Editor 成功；6 项 UE 自动化通过；九种训练均结算并存盘，工坊存取、战斗及重生通过；Windows Shipping Cook 记录 0 错误、0 警告，UAT 返回 0。[编译](Evidence/Win64/RC2/editor.txt) · [测试](Evidence/Win64/RC2/tests.txt) · [九模式](Evidence/Win64/RC2/modes.txt) · [打包](Evidence/Win64/RC2/package-log.txt) |
| 交付物 | **PASS**。ZIP 为 343,175,391 字节，含 47 个文件。归档 CRC 和两个可执行文件的字节摘要通过校验。SHA-256 为 `a4da62cc0b9b37282a8bb415a4b43e5939f0f107e6b0d90b6dddd63484913c16`。 |
| 改动位置 | `Practice/ForgeStorage.cpp` 处理替换、版本保护、历史筛选及其回归测试；`Practice/ForgeProfiles.cpp` 与 `Practice/ForgeHUD.cpp` 处理受保护配置档；`Practice/ForgeTraining.cpp` 按保存结果更新语言；`Platform/ForgePadTests.cpp` 验证旧配置对象无法覆盖新版文件。文件均位于工程的 `Source/FPSArena`。 |

## 复测环境与范围

测试使用 Windows 10 19045、NTFS、Ryzen 7 5800H、RTX 3060 Laptop 和 16 GB RAM。两个候选版本各自从 Windows ZIP 解压后运行，使用独立于玩家存档的测试目录。UE 自动化、九模式和打包命令与 [G9 基线](Milestone_G9.md) 相同。编辑器内可打开 `/Game/Training/Forge`，从大厅按 `F1` 调整设置，`H` 选择历史，`R` 重试。直接对照两份成绩的模式、难度、战斗状态和种子即可复核。

Windows 文件锁实验覆盖应用层替换失败，真实瞬间断电后的磁盘行为仍为 **UNVERIFIED**。Steam 商业发行 **BLOCKED**，本机缺少可核验的项目 App ID 和合作伙伴权限。Xbox 与 DualSense 实机手感、高级反馈、端到端输入延迟和全新 Windows 安装仍为 **UNVERIFIED**。正式发行前应在实际授权的私有分支及目标设备上签收这些项目。

## 两个发行程序的实际往返

| 操作 | 灵敏度 | 新记录 |
|---|---:|---|
| RC1 创建配置并开始 M2 | 165 | M2，种子 273690 |
| RC2 读取 RC1 配置并提高一级，在历史页重试 | 180 | M2，种子 273690 |
| RC2 新建 M3，切换随机种子 | 180 | M3，种子 806573 |
| 再次启动 RC1，提高一级，从历史页重试 | 195 | M3，种子 806573 |

**PASS**。四局均正常完成，有四个独立的局标识和对应轨迹。对 RC1 与 RC2 各自创建的源成绩、轨迹复算 SHA-256，往返前后字节一致。在 RC2 读取前向测试目录加入了两条排序靠前的异常记录，分别使用较新格式和非整数模式号，历史重试仍选中正确的旧局。回到 RC1 前将这两条人工构造的测试文件移出历史目录。兼容性范围限于这两个真实候选包。[程序摘要、四局成绩与轨迹校验](Evidence/Win64/RC2/roundtrip.json)

在已解压的 RC2 上，另外用 MSVC dumpbin 检查了 16 个 PE 模块的 299 条静态与延迟加载依赖。其中 11 条可在包内找到，192 条属于 Windows API Set，96 条可在测试机系统目录找到。随附 VC++ x64 安装程序的 Authenticode 签名有效，签名方为 Microsoft Corporation。这项检查覆盖 PE 导入表，首次安装及运行时动态加载仍需干净系统实测。[依赖明细](Evidence/Win64/RC2/runtime-imports.json)

## RC2 解压包的 1080p 性能

在 RTX 3060 Laptop 上独立运行三轮，每轮约 120 秒，使用 M2、M6、M9 的固定路线。渲染比例 100%，垂直同步关闭，帧率上限关闭，记录的五项画质均为 3。已从 CSV 重算帧数、均值、P95、最大帧时间和超过 50 ms 的帧数。

| 轮次 | 帧数 | 平均 FPS | 平均帧时间 | P95 | 最大帧时间 | 超过 50 ms |
|---|---:|---:|---:|---:|---:|---:|
| 1 | 14,910 | 124.25 | 8.05 ms | 9.76 ms | 17.37 ms | 0 |
| 2 | 15,586 | 129.88 | 7.70 ms | 9.59 ms | 20.72 ms | 0 |
| 3 | 15,843 | 132.02 | 7.57 ms | 9.37 ms | 18.89 ms | 0 |

**PASS**。共 46,339 帧，按总帧数与总时间计算为 128.72 FPS，三轮均达到平均 60 FPS 的目标。RC1 和 RC2 的相同路线及已记录的画质设置相同，RC1 上次测得 193.12 FPS。这两次采样分开进行，缺少同时段交替测试与功耗、温度的完整记录，差异的原因仍未确认。[RC2 汇总及逐轮设置](Evidence/Win64/RC2/Performance/summary.json) · [第一轮](Evidence/Win64/RC2/Performance/Run1.csv) · [第二轮](Evidence/Win64/RC2/Performance/Run2.csv) · [第三轮](Evidence/Win64/RC2/Performance/Run3.csv)
