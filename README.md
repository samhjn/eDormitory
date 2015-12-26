# eDomitory

eDormitory是一个提供远程家电控制的项目。它分为三大组件

## 服务器端

服务器使用Django框架，运行在远程服务器

## 中间件

中间件采用Python，运行在Raspberry Pi上

## 控制器客户端

控制器客户端是Arduino，需要Mirf库就能正常编译。理论上支持Arduino的所有版本。