# -*- coding: utf-8 -*-
import pytimer

timer = pytimer.CPyTimer()


def main_idle():
    print("hello main_idle")


timer.settimer(1, 1000, lambda id: 
    timer.killtimer(id)
    main_idle()
)

print(module.gettime())

# warning: sleepms bind IDEvent=0
timer.sleepms(2000, lambda: 
    print("sleepms 2000 " + str(module.gettime()))

    count = 0
    timer.settimer(2, 1000, lambda id: 
        count += 1
        print("hello world " + str(count))
        if count >= 10:
            timer.killtimer(id)
            timer.killall()
            module.stop()
    )
)

module.run();
