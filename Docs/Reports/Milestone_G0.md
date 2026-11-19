# G0 环境检查验收报告

**2026-11-19 · 待项目负责人审批**　本机已完成 Win64 原生构建、两项命令行自动化测试及 D3D12 编辑器启动验证。建议进入 G1 技术调研。

| 验收项 | 记录 |
| --- | --- |
| 1. 里程碑与目标 | G0，用现有 FPSArena 工程验证本机 UE 开发环境，确定进入 G1 的阻断项。 |
| 2. 完成内容 | 盘点系统、硬件、磁盘、UE、IDE、SDK、Git/LFS 和 Python，核对 Steamworks 文件，实测编译、链接、测试和图形启动。 |
| 3. 变更文件 | 当前工作区新增 `Docs/Reports/Environment_Check.md` 和本验收报告。现有 FPSArena 工程在检查后的 Git 工作区干净。 |
| 4. Git Commit Hash | 环境检查交付提交为 `3f4215f286311bc2c6ee3447d2d3fd332df82003`，本报告随后单独归档。受测 FPSArena 工程基线为 `1f5fe2ff6bfa2225ba9a986f37f978b8468511c8`。 |
| 5. 编译命令及结果 | **PASS**。通过工程指定的 Build.bat 调用 UBT，目标为 `FPSArenaEditor Win64 Development`。4 个动作完成，项目 DLL 链接成功，退出码 0。可复制命令见环境报告。 |
| 6. 自动化测试及结果 | **PASS**。`Automation RunTests FPSArena` 匹配 2 项；`FPSArena.Input.SettingsAndFrameRate` 和 `FPSArena.Training.RoundLifecycle` 均返回 Success，进程退出码 0。 |
| 7. 人工测试步骤 | 人工交互 **UNVERIFIED**。复验时在桌面用 UE 5.9 打开当前 FPSArena.uproject，确认 Lvl_FirstPerson 视口可见且可平移，在“输出日志”核对 D3D12 所选适配器后正常关闭。独立完成的程序化图形启动检查为 **PASS**，已检测到编辑器窗口、地图加载和正常退出。 |
| 8. 实测硬件与环境 | Windows 10 22H2 x64，Ryzen 7 5800H，16 GiB RAM，RTX 3060 Laptop 6 GiB；UE 5.9.0，VS Community 2026，MSVC 14.52.37029，Windows SDK 10.0.26100.0。 |
| 9. 已知缺陷 | UBT 报告编译器版本高于首选范围，以及 Fab 插件依赖声明警告。本次构建成功。 |
| 10. 未完成事项 | Steamworks 合作伙伴权限及产品 App ID、实体手柄、人工操作、Shipping 打包与 1080p 性能均为 **UNVERIFIED**。 |
| 11. 风险与阻断项 | VS 2022 缺失，现有工具链已完成 Editor 目标构建。G1 的本地调研可以进行；平台联调和发行需要另行完成产品授权核验。 |
| 12. 下一阶段建议 | 负责人批准 G0 后启动 G1 的三份文档。G1 交付后再次审批，决定是否进入 G2 编码。 |

逐项状态、确切工具路径、日志摘要和有条件的安装建议见[《环境检查报告》](Environment_Check.md)。
