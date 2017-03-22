# Django Notes

> What is Django ?
>
> 




## Django Authentication

> **用户模型**
> 
> 1. The `User` Object : django.contrib.auth.models.User
>     * Fields :
>         * _username_ : Required, 最长150个字符，只能由字母数字, +, -, @, _ 组成。在python2中默认为ASCII编码，python3中默认为Unicode编码。
>         * _password_ : Required, Django不会直接存储原始密码，而是存储密码的hash值，这意味着密码可以由任何字符组成。
>         * _first_name_ : Optional, 最长30个字符。
>         * _last_name_ : Optional, 最长30个字符。
>         * _email_ : Optional。
>         * _groups_ : 
>         * _user_permissions_ : 
>         * _is_staff_ : Boolean, 是否可以访问 admin 主站。
>         * _is_active_ : Boolean, 如果需要剔除某个用户，建议不要删除数据库中的信息，而是将这个值置为false，防止一些依赖这个用户的外键奔溃。
>         * _is_superuser_ : Boolean, 是否拥有所有权限。
>         * _last_login_ : 用户上一次登录时间。
>         * _date_joined_ : 账户创建日期。
> 
>     * Attributes :
>         * _is_autenticated_ : Read-only, 这个值永远为真。Django 不是以这个值判断权限的，这样做是为了和那些没有登录的用户区分开来。
>         * _is_anonymous_ : Read-only, 这个值永远为假。
>         * _username_validator_ : 用来判断用户名是否有效的一个指向某个 Validator 实体的指针。
>         
>     * Methods : 
>         * _get_username()_ : 
>         * _get_full_name()_ : first_name + ' ' + last_name。
>         * _get_short_name()_ : first_name。
>         * _set_password()_ : 调用这个方法后密码并不会保存到数据库，需要再调用 _save()_ 方法。
>         * _email_user()_ : 发送一封邮件给这个用户
> 
> 2. The `AnonymousUser` Object : django.contrib.auth.models.AnonymousUser(django.contrib.auth.models.User)
>     * 和 User 的不同的地方
>         * _id_ 始终为 None
>         * _username_ 始终为空字符串
>         * _is_anonymous_ 为真
>         * _is_authenticated_ 始终为 False
>         * _is_active_ 始终为 False
>         * _set_password()_, _check_password()_, _save()_, _delete()_ 始终返回 NotImplementedError
> 
> **权限模型**
> 
> 1. The `Permission` Object : django.contrib.auth.models.Permission
>     * Fields :
>         * _name_ : Required, 最长255个字符，比如'可以投票'
>         * _content_type_ : Required, 指向某个 model 的指针。
>         * _codename_ : Required, 最长100个字符，比如'can_vote'。
>     
>     * Methods : 继承父类的所有方法 
> 
> 2. The `Group` Object : django.contrib.auth.models.Group
>     * Fields :
>         * _name_ : Required, 最长80个字符，可以是任何字符。
>         * _permissions_ : Many-to-Many Field to `Permission`

* Authentication in Web Request (验证)
    
    > **What is Session ?**
    > > 所谓 Session, 其实是服务器用来记录当前访问用户信息的一种手段，它存储在服务器端，由服务器来管理。 
    * **How to use session in Django ?**
        1. Enable session functionality : 在 settings.py 中 _MIDDLEWARE_ 中添加 'django.contrib.sessions.middleware.SessionMiddleware'
        2. Configure the session engine : 默认 Session 会存储在数据库中 (用`django.contrib.sessions.models.Session`)
            * Database-backed Session : 默认，前提为`django.contrib.sessions` 在 settings.py 的 _INSTALLED_APP_ 中
            * Cached-backed Session : 
            * File-backed Session : 设置 _SESSION_ENGINE_ 为`django.contrib.sessions.backends.file`, 通过 _SESSION_FILE_PATH_ 设置路径。
            * Cookie-based Session : 设置 _SESSION_ENGINE_ 为`django.contrib.sessions.backends.signed_cookie`。开启 _SESSION_COOKIE_HTTPONLY_ 放置远程代码执行。注意 _SECRET_KEY_ 的保密。

    * **Request** : Django 利用 session 和中间件将验证信息插入到(hook) http request object 中。比如，如果用户没有登录，session会将一个`AnonymousUser` 赋值给`request.user`。可以通过`request.user.is_authenticated`来判断。

    * Log a user in : 通过 `django.contrib.auth.login()` 来将登录信息插入到 session 中。

            #Example:
            from django.contrib.auth import authenticate, login
            def my_view(request):
                username = request.POST['username']
                password = request.POST['password']
                user = authenticate(username=username, password=password) 
                if user is not None:
                    login(request, user)
                    # Redirect to a success page.
                    ...             
                else:
                    # Return an 'invalid login' error message.
                    ...

    * Log a user out : 通过`django.contrib.auth.logout()` 来将用户登录信息 session 全部删除。不会返回任何值，包括错误。

    * Limit access : 使用`@login_required` (django.contrib.auth.decorators.login_required) 修饰符
        * 如果用户没有登录，会被重定向到 _settions.LOGIN_URL_ 并将当前绝对路径当参数传入。
        * 如果用户已登录，正常执行 view。
    
