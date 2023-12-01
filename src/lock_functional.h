#pragma once
#include "lock_base.h"
#include "IState.h"


class Functional: public LOCK {
public:
	Functional(MouseInfo mouseinfo):LOCK(mouseinfo){
		std::cout << "[debug]: Functional 派生类构造" << std::endl;
	}
	//! 初始化lock 
	bool initLock() override;
	//! 获取错误信息
	IStates getLastError() override;
	//! 开始动作
	void action() override;
	//! 释放
	void Release() override;
private:
	std::vector<IStates> m_states; 
	~Functional(){std::cout << "[debug]: Functional 派生类析构" << std::endl;}
};

