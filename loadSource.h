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

void LoadMTLFile(const char* objFilename)
{
	int nFileSize = 0;
	unsigned char* fileContent = LoadFileContent(objFilename, nFileSize);
	if (fileContent == nullptr)
	{
		std::cout << "fail to open "<< objFilename << endl;
		return;
	}
	std::cout << "Loading " << objFilename << " ... ";
	stringstream ssFileContent((char*)fileContent);
	string temp;
	string materialname;
	char szoneLine[256];
	while (!ssFileContent.eof())
	{
		ssFileContent.getline(szoneLine, 256);
		if (strlen(szoneLine) > 0)
		{
			stringstream ssOneLine(szoneLine);
			if (szoneLine[0] == 'n'&& szoneLine[1] == 'e'&& szoneLine[2] == 'w'&& szoneLine[3] == 'm'&& szoneLine[4] == 't'&& szoneLine[5] == 'l')
			{
				ssOneLine >> temp;
				ssOneLine >> materialname;
				//cout << materialname << endl;
			}
			else if (szoneLine[0] == 'K' && szoneLine[1] == 'a')
			{
				ssOneLine >> temp;
				vec3 ka;
				ssOneLine >> ka.x >> ka.y >> ka.z;
				KAs[materialname] = ka;
			}
			else if (szoneLine[0] == 'K' && szoneLine[1] == 'd')
			{
				ssOneLine >> temp;
				vec3 kd;
				ssOneLine >> kd.x >> kd.y >> kd.z;
				//cout << kd.x << " " << kd.y << " " << kd.z << endl;
				KDs[materialname] = kd;
			}
			else if (szoneLine[0] == 'K' && szoneLine[1] == 's')
			{
				ssOneLine >> temp;
				vec3 ks;
				ssOneLine >> ks.x >> ks.y >> ks.z;
				KAs[materialname] = ks;
			}
		}
	}
	delete fileContent;
	cout << "Success!" << endl;
}
