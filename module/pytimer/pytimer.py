# -*- coding: utf-8 -*-
import pytimer

timer = pytimer.CPyTimer()

def main_idle(id):
    print(f"{pytimer.gettime()} hello main_idle: {id}")

timer.settimer(1, 1000, main_idle)

print(pytimer.gettime())

# Lua 风格嵌套回调实现
timer.sleepms(2000, lambda : (
    (lambda count=[0]: (  # 闭包捕获可变对象
        print(f"sleepms 2000 {pytimer.gettime()}"),
        timer.settimer(2, 1000, lambda id: (
            (lambda count=count: (
                count.__setitem__(0, count[0] + 1),
                print(f"hello world {count[0]}"),
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