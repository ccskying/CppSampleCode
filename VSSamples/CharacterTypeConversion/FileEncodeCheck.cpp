#include "stdafx.h"
#include "FileEncodeCheck.h"
int CFileOperation::CheckEncode(LPCTSTR strFilePath)
{
	//����Ҳ����ļ�ֱ�ӷ��ش���
	CFileFind fFind;
	BOOL bIsFileFind = fFind.FindFile(strFilePath);
	if (bIsFileFind)
	{
		return 0;
	}
	//����ҵ��˵��Ǵ򲻿���Ҳֱ�ӷ�����
	CFile fEncodeCheck;
	BOOL bOpen = fEncodeCheck.Open(strFilePath, CFile::modeRead);
	if (bOpen)
	{
		return 0;
	}
	//����Ҫ���޷��ţ���ֹ����λ���µ��жϴ���
	//�ж�Unicode
	unsigned char Unicodetest[1];
	fEncodeCheck.Read(Unicodetest, 2);
	if (Unicodetest[0] == 0xFE && Unicodetest[1] == 0xFF)
	{
		return unicode;
	}
	fEncodeCheck.SeekToBegin();

	//�ж�Utf-8
	unsigned char Utf8test[3];
	fEncodeCheck.Read(Utf8test, 3);
	if (Utf8test[0] == 0xEF && Utf8test[1] == 0xBB && Utf8test[2] == 0xBF)
	{
		return utf8;
	}
	fEncodeCheck.Close();
	//��������ǣ��ж�Ϊ���ֽڱ����ı�
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