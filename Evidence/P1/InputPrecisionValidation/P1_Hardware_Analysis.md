# P1 Xbox / DualSense 实测分析

日期：2026-11-20

## Xbox 隔离采样

原始 CSV：`Evidence/P1/InputPrecisionValidation/RuntimeCaptures/Xbox_isolated.csv`

- 设备隔离：PASS。采样前 Windows PnP 仅报告 `Xbox One 控制器`，DualSense 已断开。
- 左摇杆样本：16,922 行，处理值 X/Y 范围均为 [-1, 1]
- 右摇杆样本：16,922 行，处理值 X/Y 范围均为 [-1, 1]
- LT：2,795 行，处理值范围 [0.007843, 1.0]
- RT：2,508 行，处理值范围 [0.007843, 1.0]
- 轴向死区：测试结果有零值和全行程值，CSV 已记录前后值
- 径向死区：初版公式产生约 1.8% 超出 1 的值，已在源码中增加 [-1,1] 限幅。该修正需要重新采样确认。
- 异常跳变：按相邻样本最大分量变化 >1.5 检查，当前为 0 次
- 重复回调：记录到高计数。该字段表示同一动作的回调重复次数，不能直接等同于 Steam Input 重复映射，仍需进一步分层验证。
- 中心漂移：当前 CSV 含回中和操作序列，但尚未生成独立统计阈值报告，标记 UNVERIFIED。

## DualSense

状态：BLOCKED。

Windows PnP 曾确认仅有 `DualSense Edge Wireless Controller`。项目负责人完成了动作序列，但对应运行窗口没有产生 `P1_INPUT_SAMPLE` 回调和 CSV 文件。原因是当前启动路径加载了 Editor 初始化流程，没有稳定进入隔离运行时采样入口。没有使用其他数据替代 DualSense 样本。

## 结论

Xbox 的设备隔离和摇杆/扳机范围采样已有真实 CSV。径向死区修正后需要重新确认，中心漂移和重复映射仍需分析。DualSense 完整实测尚未完成。
