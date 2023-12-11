#include <iostream>
using namespace std;

// 타이머 이벤트 열거형
enum TimerEvent 
{
    TIMER_START,
    TIMER_PAUSE,
    TIMER_RESET
};

// 타이머 이벤트 클래스
class TimerEventInfo
{
public:
    TimerEvent event;

    TimerEventInfo(TimerEvent e) : event(e) {}
};

// 타이머 핸들러 추상 클래스
class TimerHandler 
{
public:
    TimerHandler* nextHandler;

    TimerHandler() : nextHandler(nullptr) {}

    virtual void handleEvent(const TimerEventInfo& eventInfo) = 0;

    void setNextHandler(TimerHandler* handler) 
    {
        nextHandler = handler;
    }
};

// 타이머 시작 핸들러
class StartTimerHandler : public TimerHandler 
{
public:
    void handleEvent(const TimerEventInfo& eventInfo) override 
    {
        if (eventInfo.event == TIMER_START) 
        {
            cout << "Timer started." << endl;
        }
        else if (nextHandler != nullptr) 
        {
            nextHandler->handleEvent(eventInfo);
        }
    }
};

// 타이머 일시 정지 핸들러
class PauseTimerHandler : public TimerHandler 
{
public:
    void handleEvent(const TimerEventInfo& eventInfo) override 
    {
        if (eventInfo.event == TIMER_PAUSE) 
        {
            cout << "Timer paused." << endl;
        }
        else if (nextHandler != nullptr) 
        {
            nextHandler->handleEvent(eventInfo);
        }
    }
};

// 타이머 초기화 핸들러
class ResetTimerHandler : public TimerHandler 
{
public:
    void handleEvent(const TimerEventInfo& eventInfo) override 
    {
        if (eventInfo.event == TIMER_RESET) 
        {
            cout << "Timer reset." << endl;
        }
        else if (nextHandler != nullptr) 
        {
            nextHandler->handleEvent(eventInfo);
        }
    }
};

// 타이머 클래스
class Timer 
{
private:
    TimerHandler* eventHandler;

public:
    Timer(TimerHandler* handler) : eventHandler(handler) {}

    void fireEvent(const TimerEventInfo& eventInfo) 
    {
        if (eventHandler != nullptr) 
        {
            eventHandler->handleEvent(eventInfo);
        }
    }
};

int main() 
{
    // 타이머 핸들러 생성
    StartTimerHandler startHandler;
    PauseTimerHandler pauseHandler;
    ResetTimerHandler resetHandler;

    // 핸들러 연결
    startHandler.setNextHandler(&pauseHandler);
    pauseHandler.setNextHandler(&resetHandler);

    // 타이머 생성 및 핸들러 설정
    Timer timer(&startHandler);

    // 타이머 이벤트 발생
    TimerEventInfo startEvent(TIMER_START);
    TimerEventInfo pauseEvent(TIMER_PAUSE);
    TimerEventInfo resetEvent(TIMER_RESET);

    timer.fireEvent(startEvent);
    timer.fireEvent(pauseEvent);
    timer.fireEvent(resetEvent);

    return 0;
}
