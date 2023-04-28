#pragma once
#include <fstream>
#include <vector>
#include<iostream>

#include"main.h"

using namespace std;

unsigned char* LoadFileContent(const char* path, int& filesize) {
	unsigned char* fileContent = nullptr;
	filesize = 0;
	FILE* pFile;
	errno_t err = fopen_s(&pFile, path, "rb");
	if (err != 0)
	{
		cout << "not exist" << endl;
		return 0;
	}
	if (pFile) {
		fseek(pFile, 0, SEEK_END);
		int nLen = ftell(pFile);
		if (nLen > 0) {
			rewind(pFile);
			fileContent = new unsigned char[nLen + 1];
			fread(fileContent, sizeof(unsigned char), nLen, pFile);
			fileContent[nLen] = '\0';
			filesize = nLen;
		}
		fclose(pFile);
	}
	return fileContent;
}

