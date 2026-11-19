# 输入系统技术设计 · Win64

**审批建议**　把 Enhanced Input 设为游戏动作的唯一入口。无 Steam 时先用操作系统交给 UE 的键鼠和手柄输入。在选择 Steam 原生动作的设备上，由一个适配层把 Steam 动作送入同一组 Input Action。普通按键、摇杆、体感和反馈分别登记消费来源。G1 已核对接口；实体设备效果、Steam 应用权限和打包均待实测。

## 核对版本与工程起点

- UE **5.9.0，CL 60351404**。下文的 E 表示本机 `Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/`。具体声明以安装包为准；Epic 文档用于核对动作、映射上下文、修饰器、触发器的职责。[Epic 输入概览](https://dev.epicgames.com/documentation/en-us/unreal-engine/input-overview-in-unreal-engine)
- Steamworks **1.64**，目录 `Engine/Source/ThirdParty/Steamworks/Steamv164/sdk/public/steam/`，下文记为 S。接口版本常量为 `SteamInput006`。SDK 接口页和动作清单文档由 Valve 维护。[ISteamInput](https://partner.steamgames.com/doc/api/isteaminput) · [Action Manifest Files](https://partner.steamgames.com/doc/features/steam_controller/action_manifest_file)
- 工程基线 `1f5fe2f` 已采用 EnhancedPlayerInput、EnhancedInputComponent、运行时 IMC、独立鼠标和摇杆 Look 处理及 `RangeInput_v1` 存档。`DefaultInput.ini` 的多个手柄轴仍列有 0.25 死区；进入 G2 应测完整输入链的微动起点，核实轴配置、平台映射和动作修饰器实际生效的顺序。
- UE 自带的 `Engine/Plugins/Runtime/Steam/SteamController/SteamController.uplugin` 标为默认关闭。其 `Private/SteamController.cpp`（在 Source/SteamController 下）会初始化、读取数字及模拟动作并在销毁时关闭接口。G7 选择项目适配层时应核对最终加载模块，指定唯一 Steam Input 生命周期持有者。备选是复用该插件作为唯一读取者，前提是它能实现本项目的来源标记、输入隔离和数据记录。

## UE 接口核对表

下表均适用 UE 5.9.0；摘录返回值、函数名、参数及 const 限定，省略导出宏、virtual 和默认实参。所有行都处理本地玩家输入，可用于键鼠及由当前平台后端成功上报的 USB / 无线手柄。调试注入只覆盖软件层。

| 用途与头文件（E 下） | 已核对签名 | 不可用处理与最小验证 |
| --- | --- | --- |
| 添加 / 移除映射；EnhancedInputSubsystemInterface.h:265、274 | `void AddMappingContext(const UInputMappingContext* MappingContext, int32 Priority, const FModifyContextOptions& Options)`；`void RemoveMappingContext(const UInputMappingContext* MappingContext, const FModifyContextOptions& Options)` | 本地玩家就绪后注册；菜单打开时释放游戏上下文。按一次确认键，断言菜单确认 1 次、游戏开火 0 次；关菜单时按住的键须松开后再武装。 |
| Steam 动作进入 UE；同文件:153 | `void InjectInputForAction(const UInputAction* Action, FInputActionValue RawValue, const TArray<UInputModifier*>& Modifiers, const TArray<UInputTrigger*>& Triggers)` | IA 缺失就停用对应动作并报告；给连续半轴值、归零和按钮释放序列，核对单次处理。注入路径显式提供所需映射级变换，动作级变换只应用一次。 |
| 访问设置；EnhancedInputSubsystems.h:34 | `UEnhancedInputUserSettings* GetUserSettings() const` | 项目开启 `bEnableUserSettings` 后获取；空指针时维持默认键位，面板提示设置未准备好。重启后分两个本地配置读取。 |
| 可重映射行；UserSettings/EnhancedInputUserSettings.h:811、649 | `bool RegisterInputMappingContext(const UInputMappingContext* IMC)`；`void MapPlayerKey(const FMapPlayerKeyArgs& InArgs, FGameplayTagContainer& FailureReason)` | IMC 注册后验证稳定 MappingName 已建行；传 MappingName、Slot、NewKey、ProfileIdString，按需限定 HardwareDeviceId。检查失败标签和实际绑定；用有效行、未知行、保留键各测一次，失败保留原值。 |
| 创建 / 选用配置档；同文件:773、713、734 附近 | `UEnhancedPlayerMappableKeyProfile* CreateNewKeyProfile(const FPlayerMappableKeyProfileCreationArgs& InArgs)`；`bool SetActiveKeyProfile(const FString& InProfileId)`；`UEnhancedPlayerMappableKeyProfile* GetActiveKeyProfile() const` | 使用字符串 ProfileStringIdentifier 创建 A/B 两档；创建失败或 ID 无效保留当前档。给相同行设置不同键，切换后只接受选中档键位，再重启复测。旧 GameplayTag 切换接口已标弃用。 |
| 恢复默认 / 请求重建；同文件:684、EnhancedInputSubsystemInterface.h:336 | `void ResetKeyProfileIdToDefault(const FString& ProfileId, FGameplayTagContainer& FailureReason)`；`void RequestRebuildControlMappings(const FModifyContextOptions& Options, EInputMappingRebuildType RebuildType)` | 按档恢复并核查失败标签；仅在需要时请求重建，待重建完成再读下一帧结果。验证 B 档恢复不会改变 A 档。 |

**配置归属。** UE 键位档负责原生键鼠、UE 手柄物理键的改绑；Steam 原生动作的物理绑定由 Steam 布局管理，游戏提供打开布局入口和可用状态。两条路径都使用游戏的灵敏度档与动作逻辑。JSON 是游戏设置主记录，按 `SchemaVersion`、配置档及修订号保存；UE SaveGame 保留最近一次有效快照。先在内存校验，写同目录临时文件、回读后安全替换，再刷新备份。下次启动按有效主文件、有效备份、默认值的顺序恢复；更高版本配置保留原件并提示。旧 `RangeInput_v1` 在首次无新档时迁移，成功持久化后登记迁移版本，重复启动不得覆盖新设置。

## Steamworks 接口核对表

除另行说明，以下均为 **1.64 / SteamInput006**，头文件 `S/isteaminput.h`。表内按用途合并最小验证；Steam 管理的 Xbox 与 DualSense 均须先在相应 Steam 设置中启用并成功枚举。USB、无线适配器与蓝牙分别登记。接口声明确认与硬件通过分别记录。

| 用途 / 声明行 | 已核对签名或结构 | 适用条件、降级与最小验证 |
| --- | --- | --- |
| 初始化 / 帧更新，813–826 | `bool Init(bool bExplicitlyCallRunFrame)`；`void RunFrame(bool bReservedValue = true)`；`bool Shutdown()` | Steam API 可用且持有者唯一时初始化；选择显式更新就每输入帧先 RunFrame 再读。失败走 UE 路径。通过 Steam 启动和退出客户端后独立启动各一次，核对训练仍可用。 |
| 识别来源，842、984、988 | `int GetConnectedControllers(InputHandle_t *handlesOut)`；`ESteamInputType GetInputTypeForHandle(InputHandle_t inputHandle)`；`InputHandle_t GetControllerForGamepadIndex(int nIndex)` | 数组容量 STEAM_INPUT_MAX_COUNT；最后一个函数只映射 Steam 模拟的 XInput 槽，返回 0 表示没有该关联。用两只手柄交换插拔顺序，按物理操作核对句柄、本地玩家和当前槽；无法关联时禁用双路合并。 |
| Action Manifest，819 | `bool SetInputActionManifestFilePath(const char *pchInputActionManifestAbsolutePath)` | Steam 管理的手柄；本地调试传入真实磁盘上的清单绝对路径并检查 bool。分别从含空格的安装路径加载正确清单、缺文件清单；还要核对动作句柄和实际输入。失败退至可用基础路径。 |
| 动作集，881、886 | `InputActionSetHandle_t GetActionSetHandle(const char *pszActionSetName)`；`void ActivateActionSet(InputHandle_t inputHandle, InputActionSetHandle_t actionSetHandle)` | Steam 原生手柄。缓存成功解析的 Gameplay / Menu 句柄；坏名称拒绝启用对应集。菜单切换十次，核对动作不串集。 |
| 数字与轴，904、907、918、921 | `InputDigitalActionHandle_t GetDigitalActionHandle(const char *pszActionName)`；`InputDigitalActionData_t GetDigitalActionData(InputHandle_t inputHandle, InputDigitalActionHandle_t digitalActionHandle)`；`InputAnalogActionHandle_t GetAnalogActionHandle(const char *pszActionName)`；`InputAnalogActionData_t GetAnalogActionData(InputHandle_t inputHandle, InputAnalogActionHandle_t analogActionHandle)` | 有效句柄且 bActive 时消费。按键从 bState 边沿提取；摇杆按状态、鼠标式输出按增量处理，核对 eMode。失活时归零并释放。长按、单击、轴归中各一次，比对动作数及转角。 |
| 运动数据，736–770、947 | `InputMotionData_t GetMotionData(InputHandle_t inputHandle)`。结构全为 float：rotQuatX/Y/Z/W、posAccelX/Y/Z、rotVelX/Y/Z | 面向有 IMU 的设备，如 Steam 可识别的 DualSense。两种传输都要实测；普通 Xbox 手柄不给体感入口。数据没有时间戳或成功位。暖机、静止、单轴正反转、回中各跑一遍；异常或不可用时关闭原始体感，保留摇杆。 |
| 自适应扳机，1020；结构在 S/isteamdualsense.h:152 | `void SetDualSenseTriggerEffect(InputHandle_t inputHandle, const ScePadTriggerEffectParam *pParam)` | 仅向匹配的 DualSense 发送；零初始化结构，填写 triggerMask、对应侧 command 及合法强度。左、右单测，再向两侧发送 OFF；暂停、失焦与退出前清除，重连先归零。void 无设备确认。USB / 蓝牙分别盲测开关和强度，无实际效果则关闭该能力。 |
| 双电机 / 扳机马达，954、957 | `void TriggerVibration(InputHandle_t inputHandle, unsigned short usLeftSpeed, unsigned short usRightSpeed)`；`void TriggerVibrationExtended(InputHandle_t inputHandle, unsigned short usLeftSpeed, unsigned short usRightSpeed, unsigned short usLeftTriggerSpeed, unsigned short usRightTriggerSpeed)` | 主电机需设备支持；扩展扳机马达用于支持 Xbox Impulse Trigger 的型号。Windows 扩展扳机值还要求 Xbox Extended Feature Support 驱动。按四通道分别短测、发全零、核对设置关闭与拔插。扩展不可用就只用双电机；双电机不可用保留画面和音效。[Valve 震动说明](https://partner.steamgames.com/doc/api/isteaminput#TriggerVibrationExtended) |
| Steam 原生布局改键，981 附近 | `bool ShowBindingPanel(InputHandle_t inputHandle)` | 有效 Steam 手柄句柄；打开失败提示从 Steam 控制器设置进入。改一次 Confirm 并重进游戏核实，保留键鼠菜单入口。 |

**Manifest 交付方式。** 计划随 depot 提供独立可读的 VDF 及其引用的布局文件。根含 actions、localization 和 configurations；按控制器类型（如 controller_ps5、controller_xboxone）与优先级列出相对清单路径。Gameplay 提供 Move、Look、Fire 等，Menu 提供 Navigate、Confirm、Back。物理绑定放设备布局，动作 ID 稳定，用户可见名给中英文。合作伙伴后台配置随游戏分发的相对位置，本地覆盖使用头文件中的绝对路径接口。G7 验证真实句柄与输入，G9 在干净安装的 Shipping 目录验证清单位于 pak 外且修订配套。[Valve 清单格式及分发](https://partner.steamgames.com/doc/features/steam_controller/action_manifest_file)

## 一只设备如何只驱动一次相机

| 检测到的路径 | 按钮 / 摇杆 | 体感及反馈 |
| --- | --- | --- |
| Steam 不可用或该设备未接管 | UE 本地设备 → 对应 IMC → IA。键鼠始终保留。 | 仅走经实机证实的原生反馈后端；当前设备无法提供的选项显示原因。 |
| Steam 模拟 XInput 或鼠标 | 把平台呈现的输入交给 UE；不再为同一设备注入 Steam 原生动作。 | Steam 映射体感到鼠标或摇杆时，只消费映射后的增量 / 状态。原始体感关闭。 |
| Steam 原生动作，受控布局 | 先按本地玩家与设备源屏蔽该手柄的重复原生事件，再逐帧注入对应 IA。真实键鼠独立。 | 只选 Steam 映射体感或原始 IMU 之一。每个反馈事件只路由给当前设备的一个后端。 |

Steam 可以把体感映射成系统鼠标，应用可能无法区分它与真实鼠标。不能靠“最后使用设备”、幅值相似或同帧时间戳过滤。批准的原始体感预设须关闭该源的鼠标 / Look 模拟；无法确认自定义布局、混合输出或设备隔离时，使用单一映射路径并禁用原始叠加。断连时结束 held 动作、取消反馈、清空上一帧状态和滤波器，短暂暂停训练；重连先等摇杆回中，重新绑定玩家后再开始采样。记录中途换设备，分类为混合会话。[Valve 的 Windows 模拟输入说明](https://partner.steamgames.com/doc/features/steam_controller/steam_input_gamepad_emulation_bestpractices)

**运动单位。** 本机头文件将 rotVelX/Y/Z 依次说明为本地 pitch / roll / yaw，编码范围 ±32767 对应 ±2000°/s；posAccel 同范围对应 ±2g。四元数相对于设备唤醒，起始航向未知，初始若干包可能是单位姿态。方案优先从四元数差提取转动并处理符号连续性、回中及姿态补偿；角速率模式另行校准，按单调时间差积分一次。体感可设 ADS 激活、各轴比例、反转和平滑。重复轮询不得把同一姿态差累计两次。静止零值本身不足以判定设备损坏。

**摇杆、辅助和采样。** 用 UInputModifierDeadZone 的 LowerThreshold、UpperThreshold 与 Axial / Radial 将死区处理集中在一个阶段（E/InputModifiers.h:140–193）。左右杆独立；限定 0 ≤ 内阈值 < 外阈值 ≤ 1。依次应用归一化死区、连续曲线、反转和分轴腰射 / ADS 角速度；指数大于零，自定义点覆盖 (0,0) 至 (1,1)，横坐标严格递增，输出单调有界。角速度按秒积分一次，鼠标和体感姿态差按增量处理。辅助默认关闭，Rotational、Slowdown、窗口、Ease-in 和强度单独存入成绩。开火、命中、受击、滑铲、特殊移动各发一种有时限的反馈事件，强度乘用户总量并限幅。

每次实际读取记录会话单调时间、来源、设备、动作前值、处理后值及相机姿态；Steam 动作记录注明“Steam 映射后”，系统原始 HID 数据不可得时留空。计划另生成 60 Hz 分析时间轴，连续量按相邻样本插值，按钮保留原始边沿，掉帧间隙单列。软件延迟记录游戏读入到状态提交；物理输入到显示的延迟另用外部测量设备，单位毫秒。

## 最小实测矩阵与放行条件

以下均为 G2 / G7 待执行用例，实体功能状态 **UNVERIFIED**。记录 Windows 版本、Steam 客户端与覆盖设置、型号、固件、传输、实际布局、驱动、设备句柄变化和人工感觉。连接成功仅能证明连接层。[Sony 的 PC 连接与自适应扳机说明](https://www.playstation.com/en-us/pc/pc-accessories/)

| 设备 / 环境 | 核心操作 | 判定与降级 |
| --- | --- | --- |
| 无 Steam、键鼠；软件注入 | 限 30 / 60 / 120 FPS；用 `Input.+key Gamepad_Left2D X=0.7 Y=0.5` 后用 `Input.-key Gamepad_Left2D` 释放；再测试已持有按键时切菜单 | 连续一秒的积分结果在拟定 1% 容差内，释放归零。此行只验证软件层。 |
| Xbox USB、支持的蓝牙型号、Xbox 无线适配器分别记录 | Steam 关闭、模拟、原生动作各试；左右主电机单通道后发零；具备 Impulse Trigger 的设备再试扳机马达 | 每个按键边沿只触发一次；逐通道记录可感知效果。缺驱动或硬件时保留已测主电机。 |
| DualSense USB | 先在 Steam 关闭时验证原生枚举、摇杆和按键，再分别测试模拟、原生、体感映射与原始 IMU；比较 L2 / R2 开关和两档强度 | 离线基础输入若失败，G2 开展 Windows 输入后端验证，列为产品缺口；G7 按功能记录实测。 |
| 同一 DualSense 改蓝牙 | 同固件、同布局重复 USB 全套；额外做休眠唤醒、断连重连与暂停时停止反馈 | 蓝牙独立出结果。Sony 提醒部分 PC 游戏的扳机效果需要 USB；若本项目仅 USB 通过，显示已验证连接方式。 |
| 两只手柄、真实鼠标和自定义混合映射 | 固定摇杆转向一秒与单路径对照，静置摇杆仅转动手柄；分别打开映射与原始体感，切换焦点、菜单及设备 | 单一输入源在组合下的角位移偏差拟定 ≤1%（软件回放）；每次按键 1 个边沿；来源不明自动退回单路。实机另记录重复次数及误差分布。 |

候选 Windows 原生 DualSense 后端首先评估引擎已带的 GameInputWindows / RawInput，检查键位覆盖、传输稳定性及与 Xbox 路径的互斥。未获得实机证据前不承诺离线 DualSense 已覆盖，也不引入第三方插件。Steam 权限不足时，继续离线开发并保留 Steam 真机用例为待验。
