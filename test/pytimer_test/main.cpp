#include "gtest.h"
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include "dmformat.h"

namespace py = pybind11;
using namespace py::literals;

class TimerTest : public testing::Test {
protected:
    py::scoped_interpreter guard{}; // 启动解释器
    py::module_ pytimer;
    py::object timer;

    void SetUp() override {
        pytimer = py::module_::import("pytimer");
        timer = pytimer.attr("CPyTimer")(); // 创建定时器实例
    }
};

TEST_F(TimerTest, BasicTimerOperation) {

    py::exec(R"(
        # -*- coding: utf-8 -*-
        import pytimer

        timer = pytimer.CPyTimer()

        def main_idle(id):
            print(f"{pytimer.gettime()} [{id}] hello main_idle")

        timer.settimer(1, 1000, main_idle)

        print(f"{pytimer.gettime()} sleepms start")

        # warning: sleepms bind IDEvent=0
        timer.sleepms(2000, lambda : (
            (lambda count=[0]: (
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
    )");
}
