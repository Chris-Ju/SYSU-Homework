# Homework9

- 模仿 Github，设计一个博客网站的 API

用户注册
```
PUT /user
{
  "username":string,
  "password":string,
  "passwordComfirm":string,
  "nickname"string,
  "email":string
}

response:
200 注册成功
302 已登陆
401 用户名已存在
406 格式错误
```

用户登录
```
POST /user
{
  "username":string,
  "password":string
}

response:
200 登陆成功
302 已登陆
403 用户名或密码错误
406 格式错误
```

用户登出
```
DELETE /user

response:
200 登出成功
```

获取所有文章
```
GET /article

response:
200 获取成功
403 未登陆
```

获取某用户所有文章
```
GET /article/:username

response:
200 获取成功
403 未登录
```

获取某篇文章
```
GET /article/:id

response:
200 获取成功
403 未登录
```

发表文章
```
POST /article
{
  "title:string,
  "body":string,
}

response:
200 发表成功
403 未登录
406 格式错误
```

修改文章
```
PUT /article
{
  "title:string,
  "body":string,
}

response:
200 修改成功
403 无权限
406 格式错误
```

发表评论
```
POST /comment/:articleid
{
  "body":string
}

response:
200 发表成功
403 无权限
406 格式错误
```