# pytimer

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

## Build status
| [Linux][lin-link] | [Mac][mac-link] | [Windows][win-link] |
| :---------------: | :----------------: | :-----------------: |
| ![lin-badge]      | ![mac-badge]       | ![win-badge]        |

[lin-badge]: https://github.com/brinkqiang/pytimer/workflows/linux/badge.svg "linux build status"
[lin-link]:  https://github.com/brinkqiang/pytimer/actions/workflows/linux.yml "linux build status"
[mac-badge]: https://github.com/brinkqiang/pytimer/workflows/mac/badge.svg "mac build status"
[mac-link]:  https://github.com/brinkqiang/pytimer/actions/workflows/mac.yml "mac build status"
[win-badge]: https://github.com/brinkqiang/pytimer/workflows/win/badge.svg "win build status"
[win-link]:  https://github.com/brinkqiang/pytimer/actions/workflows/win.yml "win build status"

## 项目介绍

pytimer 是一个高性能的 Python 定时器模块，基于 C++ 实现并通过 pybind11 提供 Python 接口。它提供了精确的定时功能，适用于需要高精度定时器的场景。

主要特性：
- 高精度定时
- 多线程支持
- 跨平台（Linux/Mac/Windows）
- 简单易用的 API

## 安装

### 从源码构建

1. 克隆仓库：
   ```bash
   git clone https://github.com/brinkqiang/pytimer.git
   cd pytimer
   ```

2. 构建项目：
   - Linux/Mac:
     ```bash
     ./build.sh
     ```
   - Windows:
     ```bat
     build.bat
     ```

## 使用示例

```python
# -*- coding: utf-8 -*-
import pytimer

timer = pytimer.CPyTimer()

def main_idle(id):
    print(f"{pytimer.gettime()} [{id}] hello main_idle")

timer.settimer(1, 1000, main_idle)

print(pytimer.gettime())

# 嵌套回调实现
# warning: sleepms bind IDEvent=0
timer.sleepms(2000, lambda : (
    (lambda count=[0]: (  # 闭包捕获可变对象
        print(f"{pytimer.gettime()} [0] sleepms 2000"),
        timer.settimer(2, 1000, lambda id: (
            (lambda count=count: (
                count.__setitem__(0, count[0] + 1),
                print(f"{pytimer.gettime()} [{id}] hello world {count[0]}"),
                count[0] >= 10 and (
                    timer.killtimer(id),
                    timer.killall(),
                    pytimer.stop()
                )
            ))()
        ))
    ))()
))

pytimer.run()
```

## 贡献指南

我们欢迎任何形式的贡献！请遵循以下步骤：

1. Fork 本项目
2. 创建您的特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交您的更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 提交 Pull Request

## 许可证

本项目采用 MIT 许可证 - 详情请参阅 [LICENSE](LICENSE) 文件。

