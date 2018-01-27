#include "stdafx.h"
#include "string"
using namespace std;
#pragma once

//可以判断的三种类型
enum FileEnCodeType
{
	unkown = 0,
	utf8 = 1,
	unicode = 2,
	asni = 3
};
//文件操作类
class CFileOperation
{
private:
	CFile *pFile;
	CComBSTR bstrFilePath;
public:
	/*
	函数名：CheckEncode
	作用：检查文件的编码类型，可选：UTF-8,Unicode,asni
	参数：LPCTSTR strFilePath：文件全路径
	返回值：enum FileEnCodeType类型变量，与枚举中定义的类型相同
	*/
	static int CheckEncode(LPCTSTR strFilePath);
	/*
	函数名：WriteFileHead
	作用：创建新文件时在头部写入对应编码的文件头
	参数：CFile fFile：文件对象
		  FileEnCodeType etype：需要插入的文件头类型
	返回值：NULL
	*/
	static void WriteFileHead(CFile fFile, FileEnCodeType etype);
};

//字符串操作类
class CStringOperation
{
	/*
	函数名：UTF8ToUnicode
	作用：UTF8到Unicode的转换
	参数：LPCSTR src：单字节字符串，UTF8编码
		  CString *Result：返回翻译结果的双字节字符串，Unicode编码
	返回值：NULL
	*/
	static void utf8ToUnicode(LPCSTR src, CString *Result);
	/*
	函数名：UnicodeToUTF8
	作用：Unicode到UTF8的转换
	参数：
	返回值：string
	*/
	static string UnicodeToUTF8(LPCTSTR str);
};