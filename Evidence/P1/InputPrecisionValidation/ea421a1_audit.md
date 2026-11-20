# ea421a1 工具实际文件审计

审计对象：`ea421a1 docs: add P1 controller precision validation tool`

## 包含内容

- `InputPrecisionSampler.h`
- `InputPrecisionSampler.cpp`
- `InputPrecisionSamples.csv`
- `README.md`
- `P1_Input_Precision_Report.md`

## 缺失内容

- `.uproject`
- 模块 `Build.cs`
- Editor/Game Target
- Input Action 和 Input Mapping Context 资产
- 可运行的关卡或测试入口
- CSV 写盘实现
- Xbox/DualSense 运行时采样日志

## 代码问题

`ea421a1` 中调用了 `FInputActionValue::Get<FVector3f>()`。UE 5.9 的 `FInputActionValue` 不支持该类型转换，直接编译会触发 `static assertion failed: Unsupported conversion for type`。

因此 `ea421a1` 本身是源码草案和数据模板，不是可直接运行的采样工具。

后续已在隔离工程中改用 `FVector` 转换，建立 `.uproject`、`Build.cs` 和 Target 文件，并在 ASCII 路径 `C:\P1InputValidation` 通过 UBT 编译。该编译结果属于后续提交，不回溯标记 `ea421a1` 为通过。

## 采样结论

- Xbox 真实 CSV：UNVERIFIED
- DualSense 真实 CSV：UNVERIFIED
- 原始值：UNVERIFIED
- 时间戳：UNVERIFIED
- 死区前后实测值：UNVERIFIED
- 重复输入：UNVERIFIED
- 中心漂移：UNVERIFIED
- 异常跳变：UNVERIFIED

没有使用模拟数据。
