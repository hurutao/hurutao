# Codex GitHub connector 复核证据（2026-11-22）

## 复核对象

- 仓库：`hurutao/hurutao`
- 连接器：Codex GitHub connector
- 操作：只读查询；未创建、删除、覆盖或强制推送任何远程历史

## 实际返回

1. `github_get_profile({})`
   - 调用成功
   - 认证账号昵称：`hurutao`

2. `github_get_repo({repository_full_name:"hurutao/hurutao"})`
   - 调用成功
   - `visibility=public`
   - `default_branch=main`
   - 权限：`admin=true`、`maintain=true`、`pull=true`、`push=true`、`triage=true`

3. `github_get_repo_collaborator_permission({repository_full_name:"hurutao/hurutao",username:"hurutao"})`
   - 调用成功
   - `permission=admin`

4. `github_search_branches({owner:"hurutao",repo_name:"hurutao",query:"master"})`
   - 调用成功
   - 返回远程分支：`master`

## 结论

Codex GitHub connector 已登录并可以读取目标仓库及其权限信息。当前账号对 `hurutao/hurutao` 具有管理员和推送权限。Git CLI 的普通 `git push origin master` 已在另一份推送证据中完成；本轮没有使用强制推送。

