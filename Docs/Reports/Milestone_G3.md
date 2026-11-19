# G3　基础训练闭环

| 验收项 | 记录 |
|---|---|
| 目标 | 从祭盘启动 M1，完成对准与保持，结算并读取历史。 |
| 交付与变更原因 | ForgeTraining、ForgeCharacter、ForgeHUD、ForgeStorage、TrackingTrial；共用会话、JSON、历史页及九模式入口。 |
| 工程 Git 提交 | `0d164e9b4ce01cc5e46dd5b9c39d26601ffb4564` |
| 完整编译 | PASS。UE 5.9 Win64 Development Editor，使用下方 UBT 命令。G7 最终全量编译为 `Saved/Logs/G7-final-build.txt`。 |
| 自动化与回归 | PASS。自动对准固定种子 173 的目标，验证两次连续保持、得分 100 和历史文件。 |
| 人工复测步骤 | 选择 M1，按 R / X 开始。对准发光环并保持，查看评级；再按 H / Y 打开历史，重启查看同一成绩。 |
| 环境 | Windows x64，UE 5.9，16 GB 内存，RTX 3060 Laptop。命令行逻辑回归使用 NullRHI。 |
| 缺陷、未完成及风险 | 真人完成整轮和首次引导易用性 UNVERIFIED。 |
| 下一阶段 | 继续验证右杆多轨迹及误差积分。 |

在工程根目录用 PowerShell 复测，核心代码与资产均在 `FPSArena` 工程仓库。阶段报告集中在独立的文档仓库。

```powershell
$Engine = 'C:\Program Files\Epic Games\UE_5.9\Engine'
$Project = (Resolve-Path FPSArena.uproject).Path
& "$Engine\Build\BatchFiles\Build.bat" FPSArenaEditor Win64 Development "-Project=$Project" -WaitMutex -Rebuild
& "$Engine\Binaries\Win64\UnrealEditor-Cmd.exe" $Project -BTGSmoke '-ExecCmds=Automation RunTests FPSArena' '-TestExit=Automation Test Queue Empty' -NullRHI -NoSound -Unattended
& "$Engine\Binaries\Win64\UnrealEditor-Cmd.exe" $Project -game -BTGSmoke -NullRHI -NoSound -Unattended -Seconds=110
```

## 该提交的文件清单

- `Config/DefaultEngine.ini`
- `Scripts/PlayTraining.ps1`
- `Source/FPSArena/FPSArena.Build.cs`
- `Source/FPSArena/Practice/ForgeCharacter.cpp`
- `Source/FPSArena/Practice/ForgeHUD.cpp`
- `Source/FPSArena/Practice/ForgeStorage.cpp`
- `Source/FPSArena/Practice/ForgeStorage.h`
- `Source/FPSArena/Practice/ForgeTraining.cpp`
- `Source/FPSArena/Practice/ForgeTraining.h`
- `Source/FPSArena/Practice/RangePrototype.cpp`
- `Source/FPSArena/Practice/RangePrototype.h`
- `Source/FPSArena/Practice/TrackingTrial.cpp`
- `Source/FPSArena/Practice/TrackingTrial.h`
- `Source/FPSArena/Practice/TrackingTrialTests.cpp`
