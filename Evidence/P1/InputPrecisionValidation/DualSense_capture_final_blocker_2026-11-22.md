# DualSense 最终采样阻断记录

日期：2026-11-22

项目负责人按要求在前台运行窗口中操作 DualSense 摇杆、扳机和按键。采样器启动日志正常，且 RawInput 成功注册 `VendorID:054C ProductID:0DF2`。操作期间没有产生 `P1_INPUT_SAMPLE`、`P1_RAW_AXIS` 或重复输入日志。

`C:\P1InputValidation\Saved\P1InputSamples.csv` 文件长度保持 `594766` 字节，最后写入时间仍为 `2026-11-20T15:45:36.9299953+08:00`，没有新增 DualSense 数据。

结论为 BLOCKED。Windows HID 驱动和 UE RawInput 设备注册通过，UE 5.9 应用层没有收到该 DualSense 的轴或按键事件。现有 P1 工具无法生成真实 DualSense CSV，不能标记 DualSense 精度验收通过。
