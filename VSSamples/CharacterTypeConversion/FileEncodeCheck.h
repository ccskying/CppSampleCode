#include "stdafx.h"
#include "string"
using namespace std;
#pragma once

//�����жϵ���������
enum FileEnCodeType
{
	unkown = 0,
	utf8 = 1,
	unicode = 2,
	asni = 3
};
//�ļ�������
class CFileOperation
{
private:
	CFile *pFile;
	CComBSTR bstrFilePath;
public:
	/*
	��������CheckEncode
	���ã�����ļ��ı������ͣ���ѡ��UTF-8,Unicode,asni
	������LPCTSTR strFilePath���ļ�ȫ·��
	����ֵ��enum FileEnCodeType���ͱ�������ö���ж����������ͬ
	*/
	static int CheckEncode(LPCTSTR strFilePath);
	/*
	��������WriteFileHead
	���ã��������ļ�ʱ��ͷ��д���Ӧ������ļ�ͷ
	������CFile fFile���ļ�����
		  FileEnCodeType etype����Ҫ������ļ�ͷ����
	����ֵ��NULL
	*/
	static void WriteFileHead(CFile fFile, FileEnCodeType etype);
};

//�ַ���������
class CStringOperation
{
	/*
	��������UTF8ToUnicode
	���ã�UTF8��Unicode��ת��
	������LPCSTR src�����ֽ��ַ�����UTF8����
		  CString *Result�����ط�������˫�ֽ��ַ�����Unicode����
	����ֵ��NULL
	*/
	static void utf8ToUnicode(LPCSTR src, CString *Result);
	/*
	��������UnicodeToUTF8
	���ã�Unicode��UTF8��ת��
	������
	����ֵ��string
	*/
	static string UnicodeToUTF8(LPCTSTR str);
};