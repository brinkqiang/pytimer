# -*- coding: utf-8 -*-
import pytimer

timer = pytimer.CPyTimer()

def main_idle(id):
    print("hello main_idle: " + str(id))

timer.settimer(1, 1000, main_idle)

print(pytimer.gettime())

# 使用可变对象解决作用域问题
count_container = [0]

def sleep_callback(id):
    print("sleepms 2000 " + str(pytimer.gettime()))
    
    def timer_callback(id):
        count_container[0] += 1
        print("hello world " + str(count_container[0]))
        if count_container[0] >= 10:
            timer.killtimer(id)
            timer.killall()
            pytimer.stop()
    
    # 启动第二个定时器
    timer.settimer(2, 1000, timer_callback)

# 修正 sleepms 调用
timer.sleepms(2000, sleep_callback)

pytimer.run()