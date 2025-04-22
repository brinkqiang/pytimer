
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pytimer.h"
#include <iostream>
#include <atomic>
#include "dmutil.h"

std::atomic_bool CPyTimer::m_bStop{false};

CPyTimer::CPyTimer()
{

}

void CPyTimer::settimer(uint64_t qwIDEvent,  uint64_t qwElapse,
                         pybind11::function f)
{
    SetPyTimer(qwIDEvent, qwElapse, f);
}

void CPyTimer::killtimer(uint64_t qwIDEvent)
{
    KillTimer(qwIDEvent);
}

void CPyTimer::killall()
{
    KillTimer();
}

void CPyTimer::sleepms(uint64_t qwElapse, pybind11::function f)
{
    SetPyTimer(0, qwElapse, f, true);
}

std::string CPyTimer::gettime()
{
    return DMFormatDateTime();
}

void CPyTimer::stop()
{
    m_bStop = true;
}

void CPyTimer::run()
{
    int nEvent = 0;
    bool bBusy = false;

    while (!m_bStop)
    {
        bBusy = false;

        if (CDMTimerModule::Instance()->Run())
        {
            bBusy = true;
        }

        if (!bBusy)
        {
            SleepMs(1);
        }
    }

    CDMTimerModule::Instance()->Run();
}

int CPyTimer::poll()
{
    return CDMTimerModule::Instance()->Run();
}
