# G4　右摇杆训练

| 验收项 | 记录 |
|---|---|
| 目标 | M2–M5 可独立启动、复测并输出分段指标。 |
| 交付与变更原因 | ForgeTraining、TrackingTrial 和 TrackingTrialTests；水平、微控、对角及固定种子混合挑战。 |
| 工程 Git 提交 | `62af0869f064983ca3aae33ea30eed4a7de817f3` |
| 完整编译 | PASS。UE 5.9 Win64 Development Editor，使用下方 UBT 命令。G7 最终全量编译为 `Saved/Logs/G7-final-build.txt`。 |
| 自动化与回归 | PASS。M2、M3、M4、M5 回归记录各得 100 分；M5 写入四个不同阶段。30/60/120 Hz 的模拟保持和随机种子回放通过。 |
| 人工复测步骤 | 用左右方向键选择 M2–M5。保留种子和难度，分别观察水平轨迹、慢速漂移、对角和四段混合；重试并比较结果。 |
| 环境 | Windows x64，UE 5.9，16 GB 内存，RTX 3060 Laptop。命令行逻辑回归使用 NullRHI。 |
| 缺陷、未完成及风险 | 当前评级阈值尚缺真人样本标定。 |
| 下一阶段 | 在移动训练中记录动作事件、停靠误差与碰撞。 |

在工程根目录用 PowerShell 复测，核心代码与资产均在 `FPSArena` 工程仓库。阶段报告集中在独立的文档仓库。

```powershell
$Engine = 'C:\Program Files\Epic Games\UE_5.9\Engine'
$Project = (Resolve-Path FPSArena.uproject).Path
& "$Engine\Build\BatchFiles\Build.bat" FPSArenaEditor Win64 Development "-Project=$Project" -WaitMutex -Rebuild
& "$Engine\Binaries\Win64\UnrealEditor-Cmd.exe" $Project -BTGSmoke '-ExecCmds=Automation RunTests FPSArena' '-TestExit=Automation Test Queue Empty' -NullRHI -NoSound -Unattended
& "$Engine\Binaries\Win64\UnrealEditor-Cmd.exe" $Project -game -BTGSmoke -NullRHI -NoSound -Unattended -Seconds=110
```

## 该提交的文件清单

- `Source/FPSArena/Practice/ForgeTraining.cpp`
- `Source/FPSArena/Practice/ForgeTraining.h`
