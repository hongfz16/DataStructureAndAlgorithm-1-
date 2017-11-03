#include"htmlFetcher.h"

void fetchHTML(TCHAR* url,FILE* tarFile)
{
	urlopen(url, tarFile);
}

void urlopen(TCHAR* url, FILE* tarFile)
{
	HINTERNET hSession = InternetOpen(L"SI_HTMLfetcher", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hSession != NULL)
	{
		HINTERNET hHttp = InternetOpenUrl(hSession, url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);

		if (hHttp != NULL)
		{
			char* Temp =new char[MAXSIZE];
			ULONG Number = 1;
			while (Number > 0)
			{
				InternetReadFile(hHttp, Temp, MAXSIZE - 1, &Number);
				Temp[Number] = '\0';
				fprintf(tarFile,"%s", Temp);
			}
			InternetCloseHandle(hHttp);
			hHttp = NULL;
			delete Temp;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
}
