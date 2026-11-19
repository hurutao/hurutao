# G7　高级手柄功能

| 验收项 | 记录 |
|---|---|
| 目标 | 实现设备路由、三套设置、重映射、体感、扳机、震动和可调辅助。 |
| 交付与变更原因 | Platform/ForgeController、ForgePad、ForgePadTests、Practice/ForgeProfiles、RangeInputSettings 和训练遥测，Content/SteamInput 下的动作清单与布局。 |
| 工程 Git 提交 | `e09b0cdf27a5ec3cea1f150b62ee7548d9177078` |
| 完整编译 | PASS。UE 5.9 Win64 Development Editor，使用下方 UBT 命令。G7 最终全量编译为 `Saved/Logs/G7-final-build.txt`。 |
| 自动化与回归 | PASS。五项引擎自动化 Success，含合成 USB 报文、错误蓝牙 CRC、截断输入、按键回读、损坏 JSON 从备份恢复及未来版本保护。九模式回归已从 Forge 游戏入口运行。 |
| 人工复测步骤 | F1 / Menu 打开设置，改配置或重映射并保存重启。用 DualSense USB、蓝牙以及 Steam 原生布局逐项核查左/右杆、体感、扳机与震动，再换 Xbox。 |
| 环境 | Windows x64，UE 5.9，16 GB 内存，RTX 3060 Laptop。命令行逻辑回归使用 NullRHI。 |
| 缺陷、未完成及风险 | 软件 PASS。DualSense 实物效果、两种设备的人手操作、真实 Steam App ID 下的动作布局和外部端到端延迟 UNVERIFIED。 |
| 下一阶段 | 在 Shipping 包中测性能，补充真实硬件与 Steam 验收。 |

在工程根目录用 PowerShell 复测，核心代码与资产均在 `FPSArena` 工程仓库。阶段报告集中在独立的文档仓库。

```powershell
$Engine = 'C:\Program Files\Epic Games\UE_5.9\Engine'
$Project = (Resolve-Path FPSArena.uproject).Path
& "$Engine\Build\BatchFiles\Build.bat" FPSArenaEditor Win64 Development "-Project=$Project" -WaitMutex -Rebuild
& "$Engine\Binaries\Win64\UnrealEditor-Cmd.exe" $Project -BTGSmoke '-ExecCmds=Automation RunTests FPSArena' '-TestExit=Automation Test Queue Empty' -NullRHI -NoSound -Unattended
& "$Engine\Binaries\Win64\UnrealEditor-Cmd.exe" $Project -game -BTGSmoke -NullRHI -NoSound -Unattended -Seconds=110
```

## 该提交的文件清单

- `.gitignore`
- `Config/DefaultEngine.ini`
- `Config/DefaultGame.ini`
- `Config/DefaultInput.ini`
- `Content/SteamInput/actions.vdf`
- `Content/SteamInput/controller_ps5.vdf`
- `Content/SteamInput/controller_xbox360.vdf`
- `Content/SteamInput/controller_xboxone.vdf`
- `Source/FPSArena/FPSArena.Build.cs`
- `Source/FPSArena/Platform/ForgeController.cpp`
- `Source/FPSArena/Platform/ForgeController.h`
- `Source/FPSArena/Platform/ForgePad.cpp`
- `Source/FPSArena/Platform/ForgePad.h`
- `Source/FPSArena/Platform/ForgePadTests.cpp`
- `Source/FPSArena/Practice/ForgeCharacter.cpp`
- `Source/FPSArena/Practice/ForgeHUD.cpp`
- `Source/FPSArena/Practice/ForgeProfiles.cpp`
- `Source/FPSArena/Practice/ForgeTraining.cpp`
- `Source/FPSArena/Practice/ForgeTraining.h`
- `Source/FPSArena/Practice/ForgeWorkshop.cpp`
- `Source/FPSArena/Practice/RangeInputSettings.cpp`
- `Source/FPSArena/Practice/RangeInputSettings.h`
- `Source/FPSArena/Practice/RangePrototype.cpp`
- `Source/FPSArena/Practice/RangePrototype.h`
