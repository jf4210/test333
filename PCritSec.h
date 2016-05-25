#pragma once
#include <windows.h>

class PCritSec
{
public:
	PCritSec(void);
	virtual ~PCritSec(void);
public:
	void Wait(void);
	void Signal(void);
protected:
    CRITICAL_SECTION m_CritSec;
};
