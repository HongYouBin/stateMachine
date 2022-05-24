#include <iostream>

#define NUMBER_OF_TABLE_ENTRIES 100     // event-action table의 현재 entry 갯수
#define MAX_NUMBER_OF_ACTIONS   3       // transition 시 실행되는 최대 action 갯수

using namespace std;


// State 열거형 정의
typedef enum {
    READY,
    TRIP_REQUESTED,
    PAYMENT_REQUESTED,
    DRIVER_ASSIGNED
} State;


// Event 열거형 정의
typedef enum {
    REQUEST_TRIP,
    REQUEST_PAYMENT,
    PAYMENT_FAILED,
    PAYMENT_SUCCEEDED,
    TRIP_COMPLETED
} Event;


// 음료 자동판매기를 위한 StateMachine 클래스 정의
class StateMachine
{
private:
    State curState;     // 현재 상태

    // event-action table structure 정의
    typedef struct {
        State curState;             // 현재 상태
        Event event;                // 사용자로부터 발생된 이벤트
        void (StateMachine::*action)();   // action 함수 포인터의 배열
        State nextState;            // transition 후에 변경될 다음 상태
    } EventActionTable;
       
    // vending machine에서 사용할 event-action table 초기화
    EventActionTable table[NUMBER_OF_TABLE_ENTRIES] {
        {READY,	REQUEST_TRIP, {&StateMachine::tripRequested}, TRIP_REQUESTED},
        {TRIP_REQUESTED, REQUEST_PAYMENT, {&StateMachine::requestPayment}, PAYMENT_REQUESTED},
        {PAYMENT_REQUESTED, PAYMENT_FAILED, {&StateMachine::requestPayment}, TRIP_REQUESTED},
        {PAYMENT_REQUESTED, PAYMENT_SUCCEEDED, {&StateMachine::paymentSucceeded}, DRIVER_ASSIGNED},
        {DRIVER_ASSIGNED, TRIP_COMPLETED, {&StateMachine::tripCompleted}, READY},

    };

    void tripRequested();    
    void paymentFailed();
    void requestPayment();
    void paymentSucceeded();
    void tripCompleted();

    Event getNextEvent();       // 사용자로부터 다음 이벤트를 입력받음

    string getCurrentStateString();     // 현재 상태에 해당하는 문자열을 생성해서 반환함


public:
    void run();               // state machine 실행 
};






