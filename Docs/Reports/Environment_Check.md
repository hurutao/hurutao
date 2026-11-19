# 《魔兽训练场》G0 环境检查

**检查日期**　2026-11-19，上海时间。**结论**　本机具备 UE 5.9 Win64 原生编译、编辑器图形初始化及命令行自动化能力。建议负责人批准进入 G1 技术调研。VS 2022 缺失，现有 VS 2026 已实际构建成功；Steamworks 商业授权待负责人核验。

## 检查范围

本轮报告归档在当前工作目录 `C:\Users\Administrator\Documents\ChatGPT\训练场` 的 Git 仓库。使用项目规则指定的现有 `C:\Users\Administrator\Documents\Unreal Projects\FPSArena\FPSArena.uproject` 验证环境，工程基线为 `1f5fe2ff6bfa2225ba9a986f37f978b8468511c8`。工程与本轮文档使用不同仓库。构建会更新工程的生成目录，测试会写入本机日志。

状态定义：**PASS** 表示本次对所列能力的实测通过，**FAIL** 表示实测失败，**MISSING** 表示指定依赖缺失，**UNVERIFIED** 表示证据不足或尚未执行。

## 主机与存储

| 检查项 | 状态 | 本次证据 |
| --- | --- | --- |
| 操作系统与架构 | PASS | CIM 和注册表返回 Windows 10 家庭中文版 22H2，10.0.19045，x64。 |
| CPU | PASS | AMD Ryzen 7 5800H，8 物理核、16 逻辑处理器。 |
| GPU | PASS | NVIDIA GeForce RTX 3060 Laptop GPU，`nvidia-smi` 返回 6144 MiB 显存、驱动 621.01。UE 图形进程实际选择了这块 GPU。桌面分辨率 2560 × 1600。 |
| 内存 | PASS | 物理内存条合计 16 GiB，Windows 可见约 15.86 GiB。构建时 UBT 按可用内存将最大并发限制为 5。 |
| 工作目录与磁盘 | PASS | 工作目录、工程与引擎均位于 C 盘。检查时容量约 475.74 GiB，可用约 327.99 GiB（352,176,508,928 字节）。 |
| 1080p 性能目标 | UNVERIFIED | 本轮未运行 Shipping 场景基准，平均 FPS、P95 帧时间和卡顿数据留待真实构建实测。 |

## 开发与运行环境

| 检查项 | 状态 | 版本、位置或实测结果 |
| --- | --- | --- |
| Unreal Engine | PASS | `C:\Program Files\Epic Games\UE_5.9`。读取 `Engine/Build/Build.version` 得 5.9.0、CL 60351404、分支 `++UE5+Release-5.9`。编辑器与 UBT 均已运行。 |
| Visual Studio 2022 | MISSING | Visual Studio Installer 的 `vswhere -all -products *` 只列出 Visual Studio Community 2026，没有 17.x 实例。 |
| Visual Studio 2026 与 MSVC x64 | PASS | Community 18.12.12412.261 安装在 `C:\Program Files\Microsoft Visual Studio\18\Community`。x64 工具集目录 14.52.37025，UBT 实际使用编译器 14.52.37029。 |
| Windows SDK | PASS | UBT 实际使用 `C:\Program Files (x86)\Windows Kits\10` 下的 10.0.26100.0。已找到同版本 Include、Lib 和 x64 资源编译器。 |
| Win64 命令行构建 | PASS | `FPSArenaEditor Win64 Development` 执行 4 个构建动作，包含项目 C++ 编译及 DLL 链接。UBT 返回 `Result: Succeeded`，退出码 0。见下节。 |
| Unreal Editor 图形启动 | PASS | 启动独立 `UnrealEditor.exe`，使用 RTX 3060 Laptop GPU 的 D3D12 / SM6，完成引擎初始化、加载 `Lvl_FirstPerson.umap`。地图检查 0 错误、0 警告。通过 Win32 枚举到 `FPSArena - 虚幻编辑器` 主窗口。本次以隐藏窗口运行，仅覆盖图形启动与地图加载。 |
| 命令行自动化 | PASS | `UnrealEditor-Cmd.exe` 通过 NullRHI 运行现有 FPSArena 测试，日志逐项记录 Success，汇总为 2 项，退出码 0。 |
| 交互操作与打包 | UNVERIFIED | 本轮未人工操作视口或执行 PIE 手感验收，也未构建 Windows Shipping 包。 |
| Python | PASS | 系统 Python 3.12.10 x64 实际执行解释器命令。引擎内置 Python 3.11.8 亦可启动。 |
| Git 与 Git LFS | PASS | 实际运行 Git 2.56.0.windows.4、Git LFS 3.8.1。现有 FPSArena 仓库的 LFS 规则覆盖 `*.uasset`、`*.umap`，`git lfs ls-files` 列出 542 项。 |
| Steamworks 本地开发文件 | PASS | 引擎附带 `Steamv164`。已定位下列 Win64 头文件、导入库和 DLL。本项只覆盖本地文件可用性。 |
| Steamworks 账户、协议和应用权限 | UNVERIFIED | 本轮没有合作伙伴后台授权记录或本产品 App ID 归属证明。Steam 客户端已安装；产品授权需由负责人在合作伙伴后台核验。 |
| 手柄与 Steam Input 实机行为 | UNVERIFIED | 本轮未进行 Xbox、DualSense USB / 蓝牙、体感、扳机或震动实测。 |

## 可复核证据

以下是本次使用的 PowerShell 构建和测试命令。构建目标为已有工程的 Editor 配置。

```powershell
$engine = 'C:\Program Files\Epic Games\UE_5.9\Engine'
$project = 'C:\Users\Administrator\Documents\Unreal Projects\FPSArena\FPSArena.uproject'
& "$engine\Build\BatchFiles\Build.bat" FPSArenaEditor Win64 Development "-Project=$project" -WaitMutex
& "$engine\Binaries\Win64\UnrealEditor-Cmd.exe" $project '-ExecCmds=Automation RunTests FPSArena' -NullRHI -NoSound -Unattended '-TestExit=Automation Test Queue Empty'
```

| 证据 | 本轮关键记录 |
| --- | --- |
| UBT | `Compile [x64] Module.FPSArena.cpp`、`Link [x64] UnrealEditor-FPSArena.dll`、`Result: Succeeded`。日志位置 `%LOCALAPPDATA%\UnrealBuildTool\Log.txt`。 |
| 自动化 | `FPSArena.Input.SettingsAndFrameRate` 与 `FPSArena.Training.RoundLifecycle` 均记录 `Result={Success}`，汇总 `Automation Test Queue Empty 2 tests performed.`。日志位置为工程 `Saved/Logs/FPSArena.log`。 |
| 图形启动 | 使用 `UnrealEditor.exe` 独立启动项目，参数含 `-NoSplash -Unattended`。日志含 `Chosen D3D12 Adapter Id = 0`、`RHI D3D12 with Feature Level SM6 is supported and will be used.` 和 `Total Editor Startup Time, took 13.756`。本次独立日志为 `%TEMP%\G0-FPSArena-GUI-20261119-165142.log`。 |

Steamworks 文件相对引擎 `Engine` 目录的位置如下。

```text
Source/ThirdParty/Steamworks/Steamv164/sdk/public/steam/steam_api.h
Source/ThirdParty/Steamworks/Steamv164/sdk/public/steam/isteaminput.h
Source/ThirdParty/Steamworks/Steamv164/sdk/redistributable_bin/win64/steam_api64.lib
Binaries/ThirdParty/Steamworks/Steamv164/Win64/steam_api64.dll
```

## 缺失项、风险与进入 G1 的建议

1. **G1 本地技术调研没有工具链阻断。** 保留本次验证过的 UE、MSVC 和 Windows SDK 组合。UBT 明确提示 14.52.37029 高于其首选上限 14.50.35717，并提示 Fab 的 FabToolset 模块依赖 ToolsetRegistry、插件声明未列出该依赖。两条提示均未导致本次构建失败。后续变更工具链或制作 Shipping 包时应复测。
2. **Visual Studio 2022 是清单中的缺失项。** 当前没有为 G1 增装 IDE 的必要。若负责人要求建立 2022 对照环境，可在批准后从微软下载相应版本，在 Visual Studio Installer 选择“使用 C++ 的游戏开发”、MSVC x64/x86 工具和 Windows SDK，随后用上面的命令复验，并核对 UBT 实际选中的版本。[微软旧版下载](https://visualstudio.microsoft.com/vs/older-downloads/) · [Visual Studio Installer 组件管理](https://learn.microsoft.com/en-us/visualstudio/install/modify-visual-studio?view=vs-2022)
3. **Steam 授权是平台联调与发行的待办项。** 负责人可在 Steamworks 后台确认合作伙伴入驻、协议状态、本产品 App ID 与团队权限。G1 可先基于本机头文件与官方文档调研；涉及真实应用权限的结论等后台核验后记录。[Steamworks 入驻](https://partner.steamgames.com/doc/gettingstarted/onboarding) · [Steamworks SDK](https://partner.steamgames.com/doc/sdk)
4. **审批边界。** 建议批准 G1 的场景布局、输入技术方案和开发计划三份文档。正式业务编码仍需在三份文档完成并获负责人审批后启动。
