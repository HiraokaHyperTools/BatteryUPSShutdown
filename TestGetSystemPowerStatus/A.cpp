
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

int _tmain() {
	SYSTEM_POWER_STATUS t;
	if (!GetSystemPowerStatus(&t))
		return 1;
	printf(
		"ACLineStatus: %u \n"
		"BatteryFlag: %u \n"
		"BatteryLifePercent: %u \n"
		"Reserved1: %u \n"
		"BatteryLifeTime: %d \n"
		"BatteryFullLifeTime: %d \n"
		, 0U +t.ACLineStatus 
		, 0U +t.BatteryFlag 
		, 0U +t.BatteryLifePercent 
		, 0U +t.Reserved1 
		, 0 +t.BatteryLifeTime 
		, 0 +t.BatteryFullLifeTime 
		);
	return 0;
}

