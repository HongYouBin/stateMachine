#include <string>
#include "StateMachine.h"


/*
	함수 이름 : StateMachine::run()
	기능	  : STATE_END 상태가 될 때까지 event-action 테이블에 정의된 규칙과 사용자에 의해 발생되는 이벤트에 따라 state machine을 동작시킴
	전달 인자 : 없음
	반환값    : 없음
*/
void StateMachine::run()
{
	int i, j;
	Event curEvent;		// 현재 이벤트

	curState = READY;				// 상태 초기화
    while (true)		
	{ 
		curEvent = getNextEvent();		// 다음 이벤트를 입력받음
		
        for (i = 0; i < NUMBER_OF_TABLE_ENTRIES; i++)   // 테이블에 정의된 전각체 행(transition 내용)에 대해 비교함
		{ 
			if (curState == table[i].curState)			// 현재 상태와 일치하는지 검사
			{ 
				if (curEvent == table[i].event)			// 입력된 현재 이벤트와 일치하는지 검사
				{
					// 해당 transition이 발생할 때 수행해야 할 action 함수들을 실행시킴
				(this->*table[i].action)();
				curState = table[i].nextState;		// 테이블에 정의된 다음 상태로 현재 상태를 변경함
				break;
				}
			} 
		} 
		cout << endl << endl;
	}
}



void StateMachine::tripRequested()
{
	cout << "request trip" << '\n';
}

void StateMachine::paymentFailed()
{
	cout << "payment failed" << '\n';
}

void StateMachine::requestPayment()
{
	cout << "request payment" << '\n';
}

void StateMachine::paymentSucceeded()
{
	cout << "payment succeeded" << '\n';
}

void StateMachine::tripCompleted()
{
	cout << "trip completed" << '\n';
}

/*
	함수 이름 : StateMachine::getNextEvent()
	기능	  : 사용자로부터 다음 이벤트를 입력받음
	전달 인자 : 없음
	반환값    : Event -> 입력받은 이벤트 값
*/
Event StateMachine::getNextEvent()
{
	Event selectedEvent;       // 반환할 이벤트
	int inputEvent;				// 사용자로부터 입력받은 이벤트

	// 입력 안내 메세지 출력
	cout << "[현재 상태 : " << getCurrentStateString() << "]" << endl;
	cout << "1. Press request trip" << endl;
	cout << "2. Press request payment" << endl;
	cout << "3. Press payment succeeded" << endl;
	cout << "4. Press payment failed" << endl;
	cout << "5. Press trip-completed" << endl;

	cout << "Select an event # : ";

	// 사용자로부터 이벤트 입력받음
	cin >> inputEvent;

	// 입력 값에 따라 반환할 이벤트 값을 결정함
	switch (inputEvent)
	{
	case 1:
		selectedEvent = REQUEST_TRIP;
		break;
	case 2:
		selectedEvent = REQUEST_PAYMENT;
		break;
	case 3:
		selectedEvent = PAYMENT_SUCCEEDED;
		break;
	case 4:		
		selectedEvent = PAYMENT_FAILED;
		break;
	case 5:
		selectedEvent = TRIP_COMPLETED;
		break;
	
	}

	return selectedEvent;
}



/*
	함수 이름 : StateMachine::getCurrentStateString()
	기능	  : 현재 상태에 해당하는 출력용 문자열을 생성해서 반환함
	전달 인자 : 없음
	반환값    : string -> 출력용 상태 문자열
*/
string StateMachine::getCurrentStateString()
{
	string returnedString;

	switch (curState)
	{
	case READY:
		returnedString = "STATE_READY";
		break;
	case TRIP_REQUESTED:
		returnedString = "STATE_TRIP REQUESTED";
		break;
	case PAYMENT_REQUESTED:
		returnedString = "STATE_PAYMENT REQUESTED";
		break;
	case DRIVER_ASSIGNED:
		returnedString = "STATE_DRIVER ASSIGNED";
		break;
}
	return returnedString;
}
