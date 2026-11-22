# GitHub P1 实际推送证据（2026-11-22）

## 远程

```text
https://github.com/hurutao/hurutao.git
```

## 执行

在项目负责人明确授权后执行普通推送：

```text
git push origin master
```

结果：

```text
To https://github.com/hurutao/hurutao.git
 * [new branch]      master -> master
```

随后执行远程分支核对，并在报告更新后再次推送最终提交：

```text
git ls-remote origin refs/heads/master refs/heads/main
```

结果：

```text
cbb0995d77e3f2713241809a898876d9382438d3	refs/heads/main
d59ee8d8c887317bbe69f564fc8f7c7a8cdab537	refs/heads/master
```

最终本地 P1 HEAD 与远程 `master` 均为 `d59ee8d8c887317bbe69f564fc8f7c7a8cdab537`，推送状态：`PASS`。没有使用强制推送，也没有覆盖远程历史。

## 连接器分离状态

GitHub connector API 仍返回 `USER_NOT_LOGGED_IN`。本证据只证明 Git CLI 的远程写权限和实际推送成功，不把 Git CLI 凭据冒充为 Codex GitHub connector 登录。
