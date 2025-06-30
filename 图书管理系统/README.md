# 图书管理系统使用指南

## 项目简介
这是一个基于Flask框架开发的图书管理系统，支持管理员和用户两种角色，提供图书检索、借阅、归还、管理等功能。

## 环境配置步骤
由于终端命令执行超时问题，请手动完成以下步骤：

### 1. 安装Python
确保已安装Python 3.7+，并勾选"Add Python to PATH"选项

### 2. 安装依赖包
打开命令提示符，导航到项目目录，执行：
```
pip install -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple
```

### 3. 运行应用
```
python app.py
```

## 功能说明
- 用户登录/管理员登录
- 图书检索和分类查看
- 借阅和归还图书
- 用户借阅历史记录
- 管理员图书库存管理

## 默认账户
- 管理员: admin/admin
- 测试用户: user/user

## 注意事项
- 数据库文件会自动创建在项目根目录(books.db)
- 如需备份数据，请定期保存books.db文件