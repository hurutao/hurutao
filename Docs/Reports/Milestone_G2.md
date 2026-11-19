# G2 工程基础验收记录

工程提交 `023158874e300ef038cf9ba3a5e2f6cf09b58293`。本轮在已有工程中接入正式地图、角色运动和镜头设置。

| 项目 | 结果 |
| --- | --- |
| 工程变更 | Config 中指定原创 Forge 启动地图与游戏模式，Scripts/BuildForge.py 通过编辑器构建场地，Content/Training 内包含地图和六种材质。RangePrototype 与 RangeInputSettings 增加冲刺、步行、急停、滑铲、换肩和 60–115° FOV。 |
| 编译与自动化 | **PASS**。Build.bat FPSArenaEditor Win64 Development -Project=… -WaitMutex -Rebuild 完整重编并链接。最后一次 cpp 调整后再走 UBT。项目既有 SettingsAndFrameRate、RoundLifecycle 两项均为 Success。 |
| 正常启动 | **PASS**。UnrealEditor-Cmd.exe FPSArena.uproject -game -NullRHI -Unattended -NoSound -Seconds=8 实际加载 /Game/Training/Forge 与 RangeGameMode，正常退出。日志在本机临时目录 BTG-G2-play.log 与 BTG-G2-tests.log。图形材质通过启用渲染的编辑器命令生成。 |
| 环境 | Windows 10 x64、UE 5.9.0、RTX 3060 Laptop、16 GiB、MSVC 14.52。已枚举 Xbox 360 兼容设备，XInputGetState 槽 0 成功；设备识别 **PASS**。 |
| 人工复测 | 启动工程，WASD / 左摇杆移动，Shift / L3 冲刺，Ctrl 急停，移动中 C 滑铲，空格跳跃，V / R3 切视角，Q / RB 换肩。F1 / Menu 打开设置，调 FOV 后保存重进。 |
| 缺陷、未完成与风险 | 两种真实手柄的手感、撞墙视角与掉帧边界仍为 **UNVERIFIED**。原型设置暂由 SaveGame 持久化，JSON 和配置档进入后续里程碑。虚拟硬件识别不足以验收操作者反馈。 |
| 下一阶段 | 开发和实测可重复的 M1、持久化成绩和九模式选择，后续验收保留硬件待验项。 |
