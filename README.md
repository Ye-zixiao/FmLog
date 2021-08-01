# FmLog：A Simple Asynchronous/Stdout Logger Library

## 1. 项目特点

1. 内存使用紧凑节省。对于日志行尽可能减少常量字符串的拷贝（使用`std::string_view`），并将日志行的元信息以编码的方式放入到日志行的缓冲区中而不是直接将日志消息`memcpy()`到其中，最后实时解析输出。
2. 而且日志缓冲队中的缓冲区内存会以池的形式得到重复利用，自己实测中基本重复利用两个日志缓冲块就可以满足日志的交换输入输出。
3. 可以使用异步日志工作方式，将真正的日志输出工作交给异步的背景线程去做。
4. 日志输出速度非常快。实测至少比muduo中实现的日志库更快，在`examples`目录中有类似于muduo的benchmark测试程序；
5. 日志文件支持每日滚动，并且默认每隔3秒自动刷新一下；
6. 使用了现代C++中很多新特性。



## 2. 原理图

![日志库](docs/image/日志库.png)

## 3. 使用说明

如下是一个简单的代码示例：

```cpp
#include "fmlog/Log.h"

int main(int argc, char *argv[]) {
  constexpr uint32_t mb = 1024 * 1024;
  fm::log::setLogLevel(fm::log::LogLevel::kINFO);
  // 初始化日志器是必须要做的
  fm::log::initialize(fm::log::AsyncLoggerTag{}, "./", 
                      ::basename(argv[0]), 100 * mb);

  // 连续输出10000行日志
  for(size_t i = 0; i < 10000; ++i)
      LOG_INFO << "talk is cheap, show me the code!";
    
  return 0;
}
```



## 4. 编译安装

```bash
$> ./build.sh
```



## 5. 参考资料

1. [muduo网络库](https://github.com/chenshuo/muduo)

