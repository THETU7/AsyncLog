---
author: 宗阳
date: 2022.4.3
---

# AsyncLog

AsyncLog 是一款支持多线程的高性能日志库。

## 编译

```shell
mkdir build
cd build 
cmake ..
make
```

## 使用

导入`Asynclog.h`头文件，使用`LOGINFO`、`LOGWARN`、`LOGFATAL`等输出日志。如：

```cpp
    LOGINFO << "test ";
```

输出：

```
2022-04-05 20:17:31.5684	INFO	139816664762112	test 0	/home/thetu/Yang/code/CPP/asyncLoger/src/main.cc:18
```

可以通过`LogStream::setOutput`自定义输出，默认输出为`stdout`，可以通过设置`ASYNCLOGOUT`参数设置输出路径为默认的日志文件。如：
```cpp
  AsyncLog::LogStream::setOutput(AsyncLog::ASYNCLOGOUT);
```
  

## 参考

[muduo](https://github.com/chenshuo/muduo)

