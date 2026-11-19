# G6　目标编辑器与怪物 AI

| 验收项 | 记录 |
|---|---|
| 目标 | 创建目标和路径，保存方案、重新载入、进入预演或 M9 战斗。 |
| 交付与变更原因 | ForgeWorkshop、ForgeTraining、ForgeCharacter、ForgeHUD；四种外形、六种轨迹、生命与刷新、巡逻和近身攻击。 |
| 工程 Git 提交 | `44dd72285e82c9b550044e47ded926cbb076f6ca` |
| 完整编译 | PASS。UE 5.9 Win64 Development Editor，使用下方 UBT 命令。G7 最终全量编译为 `Saved/Logs/G7-final-build.txt`。 |
| 自动化与回归 | PASS。运行日志记录 workshop save=1 load=1 combat=1 respawn=1；方案回读包含路径点，三只战斗怪物生成，目标持续受击后消失并按时刷新。 |
| 人工复测步骤 | 祭盘按 F2 / LT，选放置、路径、速度、生命、刷新工具；保存，退出重进再加载。进入预演，射击并等待重生。 |
| 环境 | Windows x64，UE 5.9，16 GB 内存，RTX 3060 Laptop。命令行逻辑回归使用 NullRHI。 |
| 缺陷、未完成及风险 | 基础 AI 采用扫掠和沿墙移动。复杂封闭障碍的绕路能力及长时间真人战斗 UNVERIFIED。 |
| 下一阶段 | 验证多档手柄配置与降级。 |

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
- `Source/FPSArena/Practice/ForgeHUD.cpp`
- `Source/FPSArena/Practice/ForgeTraining.cpp`
- `Source/FPSArena/Practice/ForgeTraining.h`
- `Source/FPSArena/Practice/ForgeWorkshop.cpp`
- `Source/FPSArena/Practice/ForgeWorkshop.h`
- `Source/FPSArena/Practice/RangePrototype.cpp`
- `Source/FPSArena/Practice/RangePrototype.h`
