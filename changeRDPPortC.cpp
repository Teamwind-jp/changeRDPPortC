#include <windows.h>
#include <stdio.h>

int isNumber(const char *str) {
    while (*str) {
        if (!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

#pragma region "reboot "


BOOL rebootWindows(void)
{
    DWORD	rc;
    HANDLE	hprocess;
    HANDLE	htoken;
    LUID	luid;
    TOKEN_PRIVILEGES tp, tpbuf;

    hprocess = GetCurrentProcess();

    OpenProcessToken(hprocess,TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &htoken);
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &luid);

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(htoken, FALSE, &tp, sizeof(tpbuf), &tpbuf, &rc);

    BOOL forceAppsClosed = TRUE;
    BOOL rebootAfterShutdown = TRUE;
	return InitiateSystemShutdownEx(NULL, NULL, 0, forceAppsClosed, rebootAfterShutdown, SHTDN_REASON_FLAG_USER_DEFINED);
}

#pragma endregion

#pragma region "onload "

int main(int argc, char *argv[]) {

	HKEY hKey;
	LONG result;

	//Argument. �����擾
	//If there are no arguments end. ���������͏I��
	//If you want to set it directly, delete the code below. ���ڃZ�b�g����ꍇ�́A�ȉ��̃R�[�h���폜���Ă��������B
	if(argc != 2)
		return 0;
	if(!isNumber(argv[1]))
		return 0;

	DWORD	dwport = atoi(argv[1]);

	//Registry rdp port change. ���W�X�g��rdp�|�[�g�ύX
	//If you do not use the argument, set it directly. �������g�p���Ȃ��ꍇ�́A���ڃZ�b�g���Ă��������B

    //Open Registry. ���W�X�g���L�[���J��
	result = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		L"SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp",
		0,
		KEY_SET_VALUE,
		&hKey
    );
	//Set rdp PortNumber
    if (result == ERROR_SUCCESS) {
		result = RegSetValueEx(
			hKey, 
			L"PortNumber", 
			0, 
			REG_DWORD, 
			reinterpret_cast<const BYTE*>(&dwport),
			sizeof(dwport)
		);
        RegCloseKey(hKey);
        if (result != ERROR_SUCCESS) {
			return 0;
        }
    } else {
		return 0;
    }

	//reboot
	rebootWindows();


    return 0;
}

#pragma endregion


