#include "stdafx.h"
#include "FileEncodeCheck.h"
int CFileOperation::CheckEncode(LPCTSTR strFilePath)
{
	//如果找不到文件直接返回错误
	CFileFind fFind;
	BOOL bIsFileFind = fFind.FindFile(strFilePath);
	if (bIsFileFind)
	{
		return 0;
	}
	//如果找到了但是打不开，也直接反返回
	CFile fEncodeCheck;
	BOOL bOpen = fEncodeCheck.Open(strFilePath, CFile::modeRead);
	if (bOpen)
	{
		return 0;
	}
	//这里要用无符号，防止符号位导致的判断错误
	//判断Unicode
	unsigned char Unicodetest[1];
	fEncodeCheck.Read(Unicodetest, 2);
	if (Unicodetest[0] == 0xFE && Unicodetest[1] == 0xFF)
	{
		return unicode;
	}
	fEncodeCheck.SeekToBegin();

	//判断Utf-8
	unsigned char Utf8test[3];
	fEncodeCheck.Read(Utf8test, 3);
	if (Utf8test[0] == 0xEF && Utf8test[1] == 0xBB && Utf8test[2] == 0xBF)
	{
		return utf8;
	}
	fEncodeCheck.Close();
	//如果都不是，判断为单字节编码文本
	return asni;
}

void CFileOperation::WriteFileHead(CFile fFile, FileEnCodeType etype)
{
	if (etype == asni)
	{
		return;
	}
	if (etype == unicode)
	{
		const unsigned char LeadBytes[] = { 0xff, 0xfe };
		fFile.SeekToBegin();
		fFile.Write(LeadBytes, sizeof(LeadBytes));
	}
	if (etype == utf8)
	{
		const unsigned char LeadBytes[] = { 0xff, 0xbb ,0xbf};
		fFile.SeekToBegin();
		fFile.Write(LeadBytes, sizeof(LeadBytes));
	}

}

void CStringOperation::utf8ToUnicode(LPCSTR src, CString *Result)
{
	int wcsLen = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
	LPWSTR result = new wchar_t[wcsLen + 1];
	::MultiByteToWideChar(CP_UTF8, 0, src, -1, result, wcsLen);
	Result->Format(_T("%s"), result);
	delete result;
}


string CStringOperation::UnicodeToUTF8(LPCTSTR str)
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	::WideCharToMultiByte(CP_UTF8, 0, str, -1, pElementText, iTextLen, NULL, NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}