
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>


BOOL EnumInstalledSoft(TCHAR* subKey, TCHAR* subKeyName) {

	HKEY hKey = NULL;
	HKEY hSubKey = NULL;
	DWORD dwIndexs = 0;
	TCHAR keyName[MAX_PATH] = { 0 };
	DWORD dwLength = 256;
	TCHAR subKeyValue[MAX_PATH] = { 0 };


	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		while (RegEnumKeyEx(hKey, dwIndexs, keyName, &dwLength, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
		{
			RegOpenKey(hKey, keyName, &hSubKey);

			RegQueryValueEx(hSubKey,
				subKeyName,
				NULL,
				NULL,
				(LPBYTE)subKeyValue,
				&dwLength);

			printf("%s : %s  \n", keyName, subKeyValue);
			RegCloseKey(hSubKey);
			hSubKey = 0;
			++dwIndexs;
			dwLength = 256;
		}
	}
	else
	{
		return FALSE;
	}
	if (hKey != NULL)
	{
		RegCloseKey(hKey);
		return TRUE;
	}
}

int main()
{


	EnumInstalledSoft((TCHAR*)"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall",(TCHAR*)"DisplayName");
	EnumInstalledSoft((TCHAR*)"Software\\Classes\\Installer\\Products", (TCHAR*)"ProductName");
	system("pause");


	return 0;
}
