## 账户管理(Bash)

* **useradd**[需要管理员权限] : `useradd [-u UID][-g 初始群组][-G 次要群组][-mM][-c 说明][-d 家目录绝对路径][-s shell] 账户名` 创建新用户。
    0. 必须参数 `账户名` : 用户账户名
    1. 可选参数[-u UID] : 指定用户UID
    2. 可选参数[-g 初始群组] : 登录账户时默认获得该群组权限
    3. 可选参数[-G 次要群组] : 该账户还可以加入的群组
    4. 可选参数[-mM] : -m 表示强制创建用户家目录。-M 表示强制不创建家目录
    5. 可选参数[-c] : 改账户的说明字段
    6. 可选参数[-d] : 指定家目录的绝对路径
    7. 可选参数[-s] : 指定该账户的 shell
    8. 可选参数[-e] : 账户失效日期，YYYY-MM-DD
    9. 输出参数[-D] : 输出默认配置

> Ubuntu 用户可以直接使用 `adduser username` 命令创建用户

* **passwd**[需要管理员权限]: `passwd [-l][-u][-S][-n 天数][-x 天数][-w 天数][-i 天数][账户名]` 设置账户密码等信息。
    0. 可选参数[-l] : lock, 使密码失效
    1. 可选参数[-u] : unlock, 使原密码重新有效
    2. 可选参数[-n] : 多久不可修改密码
    3. 可选参数[-x] : 多久内必须修改密码，密码修改周期
    4. 可选参数[-w] : 密码过期前几天开始警告
    5. 可选参数[-i] : 密码过期时间后几天如果用户没有更改密码，用户将无法登陆。
    6. 输出参数[-S] : 显示账户信息

* **chage**[需要管理员权限] : `chage [ldEImMW] 账户名` 微调账户用户配置。
    0. 输出参数[-l] : 列出该账户详细参数
    1. 可选参数[-E] : 修改账户失效日期，YYYY-MM-DD
    2. 可选参数[-I] : 密码过期后几天，用户将无法登陆
    3. 可选参数[-m] : 密码多少天后过期
    4. 可选参数[-M] : 密码变更周期
    5. 可选参数[-W] : 密码过期前多少天开始警告
    6. 可选参数[-d] : 最近一次更改密码日期，使用这个设置可以强制用户第一次登陆修改默认密码

* **usermod**[需要管理员权限] : `usermod [-cdefgGalsuLU] username` 修改用户账户配置
    0. 可选参数[-c] : 账户说明
    1. 可选参数[-d] : 修改账户家目录，绝对路径
    2. 可选参数[-e] : 修改账户失效日期，YYYY-MM-DD
    3. 可选参数[-f] : 密码失效天数
    4. 可选参数[-g] : 修改初始群组
    5. 可选参数[-G] : 修改次要群组
    6. 可选参数[-a] : 添加 ‘次要群组’ 支持
    7. 可选参数[-l] : 修改账号名称
    8. 可选参数[-s] : 修改 shell ，需要shell的绝对路径
    9. 可选参数[-u] : 修改账号UID
    10. 可选参数[-L] : 冻结账户
    11. 可选参数[-U] : 解冻账户

* **userdel**[需要管理员权限] : `userdel [-r] username` 删除用户。
    0. 可选参数[-r] : 连同家目录一起删除

* **finger** : `finger [-s] username` 查看用户相关信息。
    0. 可选参数[-s] : 仅显示用户名、全名、登录时间等信息

* **chfn** : `chfn [-foph] username` 修改用户其他信息。
    0. 可选参数[-f] : 后接完整用户名
    1. 可选参数[-o] : 您办公室地址
    2. 可选参数[-p] : 办公室电话号码
    3. 可选参数[-h] : 家里电话号码

* **chsh** : `chsh [-ls]` 修改当前用户shell
    0. 可选参数[-l] : 列出所有可用shell
    1. 可选参数[=s] : 修改默认shell

* **id** : `id ` 列出与当前账户id相关信息

## 群组管理(Bash)

* **groupadd** : `groupadd [-rg] groupname` 创建群组
    0. 可选参数[-g] : 直接指定GID
    1. 可选参数[-r] : 创建系统群组

* **groupmod** : `groupmod [-gn] groupname` 修改群组信息
    0. 可选参数[-g] : 修改群组GID
    1. 可选参数[-n] : 修改群组名

* **groupdel** : `groupdel groupname` 删除群组,删除群组需要先确保无用户以此群组为初始群组

* **gpasswd**[root 操作时] : 
    * `gpasswd groupname` : 为groupname设置密码
    * `gpasswd [-AM] groupname`
        0. 参数[-A] : 将指定用户设置为此群组的群组管理员
        1. 参数[-M] : 将指定用户添加到此群组中
    * `gpasswd [-rR] groupname`
        0. 参数[-r] : 将该群组密码移除
        1. 参数[-R] : 使群组密码失效

* **gpasswd**[群组管理员操作时] :
    * `gpasswd [-ad] groupname` 
        0. 参数[-a] : 将指定用户添加到群组当中
        1. 参数[-d] : 将制定用户移除出群组

## ACL (Access Control List) 管理 - 细粒度权限管理