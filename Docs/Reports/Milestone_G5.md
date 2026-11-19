# G5　左摇杆训练

| 验收项 | 记录 |
|---|---|
| 目标 | M6–M9 记录路线、停靠、连段、移动跟踪。 |
| 交付与变更原因 | ForgeTraining、ForgeCharacter；角色碰撞回调、接触去重、动作记录和同步计分。 |
| 工程 Git 提交 | `0abfa88605dcda63d26ef0d4eb8cd05fe9602215` |
| 完整编译 | PASS。UE 5.9 Win64 Development Editor，使用下方 UBT 命令。G7 最终全量编译为 `Saved/Logs/G7-final-build.txt`。 |
| 自动化与回归 | PASS。M6 至 M9 的模拟局分别写出得分 50 / 96 / 70 / 48；M8 记录四个独立动作时间。自动路线测试使用位置和动作注入。 |
| 人工复测步骤 | M6 穿越标记区域；M7 入圈后刹停；M8 按提示依次冲刺、急停、滑铲、跳跃；M9 横移追踪并射击。检查误差、动作时间和命中数。 |
| 环境 | Windows x64，UE 5.9，16 GB 内存，RTX 3060 Laptop。命令行逻辑回归使用 NullRHI。 |
| 缺陷、未完成及风险 | 手动越界、斜向摇杆、运动手感和真实连段时序 UNVERIFIED。 |
| 下一阶段 | 用保存后再载入的方案复测目标工坊。 |

在工程根目录用 PowerShell 复测，核心代码与资产均在 `FPSArena` 工程仓库。阶段报告集中在独立的文档仓库。

```powershell
$Engine = 'C:\Program Files\Epic Games\UE_5.9\Engine'
$Project = (Resolve-Path FPSArena.uproject).Path
& "$Engine\Build\BatchFiles\Build.bat" FPSArenaEditor Win64 Development "-Project=$Project" -WaitMutex -Rebuild
& "$Engine\Binaries\Win64\UnrealEditor-Cmd.exe" $Project -BTGSmoke '-ExecCmds=Automation RunTests FPSArena' '-TestExit=Automation Test Queue Empty' -NullRHI -NoSound -Unattended
& "$Engine\Binaries\Win64\UnrealEditor-Cmd.exe" $Project -game -BTGSmoke -NullRHI -NoSound -Unattended -Seconds=110
```

## 该提交的文件清单

- `Source/FPSArena/Practice/ForgeCharacter.cpp`
- `Source/FPSArena/Practice/ForgeTraining.cpp`
- `Source/FPSArena/Practice/ForgeTraining.h`
