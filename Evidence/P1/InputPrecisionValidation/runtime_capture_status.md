# P1 运行时采样状态

- 隔离工程：`C:\P1InputValidation\P1InputValidation.uproject`
- 编译：PASS，UE 5.9 UBT `Result: Succeeded`
- 图形运行：PASS，窗口 `P1InputValidation（64-位 Development PCD3D_SM5）`
- 运行时 Enhanced Input 回调：PASS，日志出现 `P1_INPUT_SAMPLE`
- CSV 写盘：PASS，文件 `C:\P1InputValidation\Saved\P1InputSamples.csv`
- 当前 CSV 大小：约 40 MB
- 当前数据标签：`Unknown,Unknown`，因为未完成单设备隔离和用户动作序列
- Xbox 完整动作序列：BLOCKED，等待项目负责人操作并回复
- DualSense 完整动作序列：BLOCKED，等待 Xbox 阶段结束后执行

静止基线中观察到左摇杆约 `(-0.016907,-0.040894)`、右摇杆约 `(-0.077240,0.026215)`，经过 0.12 死区后为零。该数据只能作为未标识设备的运行时基线，不能作为 Xbox 或 DualSense 验收样本。
