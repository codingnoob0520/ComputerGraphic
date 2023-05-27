#pragma once
#include"main.h"
#include"loadSource.h"
using namespace std;
struct Float3 {
	float Data[3];
};
struct Float2 {
	float Data[3];
};
struct  Face
{
	int vertex[3][3];//三點構成一面 每個面有一個信息
};

class Module
{
public:
	Module(const char* objFilename, int partnumber);
	~Module();
	vector<Float3> mLocation;//VBOs
	vector<Float2> mTexcoord;//uVBOs
	vector<Float3> mNormal;//nVBOs
	vector<Face> mFace;
	
private:

};

Module::Module(const char* objFilename,int partnumber)
{
	int nFileSize = 0;
	unsigned char* fileContent = LoadFileContent(objFilename, nFileSize);    
	if (fileContent == nullptr)     
	{
		std::cout << "fail" << endl;
		return;
	}
	std::cout << "Loading " << objFilename << " ... ";
	stringstream ssFileContent((char*)fileContent);   
	string temp;      
	char szoneLine[256];       
	string currentmaterial;
	while (!ssFileContent.eof())
	{
		
		ssFileContent.getline(szoneLine, 256);    
		if (strlen(szoneLine) > 0)     
		{
			stringstream ssOneLine(szoneLine);
			if (szoneLine[0] == 'v' && szoneLine[1] == 't')    
			{
				ssOneLine >> temp;     
				Float2 tempTexcoord;
				ssOneLine >> tempTexcoord.Data[0] >> tempTexcoord.Data[1];   
				mTexcoord.push_back(tempTexcoord);         
			}
			if (szoneLine[0] == 'v' && szoneLine[1] == 'n')           
			{
				ssOneLine >> temp;      
				Float3 tempNormal;
				ssOneLine >> tempNormal.Data[0] >> tempNormal.Data[1] >> tempNormal.Data[2];
				mNormal.push_back(tempNormal);
			}
			if (szoneLine[0] == 'v' && szoneLine[1] == ' ')
			{

				ssOneLine >> temp;
				Float3 tempLocation;
				ssOneLine >> tempLocation.Data[0] >> tempLocation.Data[1] >> tempLocation.Data[2];
				//cout << tempLocation.Data[0] << " "<<tempLocation.Data[1] << " " << tempLocation.Data[2] << endl;
				mLocation.push_back(tempLocation);
			}
			if (szoneLine[0] == 'u' && szoneLine[1] == 's' && szoneLine[2] == 'e' && szoneLine[3] == 'm' && szoneLine[4] == 't' && szoneLine[5] == 'l')
			{
				ssOneLine >> temp;
				ssOneLine >> currentmaterial;
				//std::cout << currentmaterial << endl;
				
			}
			if (szoneLine[0] == 'f')
			{

				ssOneLine >> temp;
				string vertexStr;
				Face tempFace;
				for (int i = 0; i < 3; ++i)
				{
					ssOneLine >> vertexStr;
					size_t pos = vertexStr.find_first_of('/');
					string locIndexStr = vertexStr.substr(0, pos);
					size_t pos2 = vertexStr.find_first_of('/', pos + 1);
					string texIndexSrt = vertexStr.substr(pos + 1, pos2 - 1 - pos);
					string norIndexSrt = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2);
					tempFace.vertex[i][0] = atoi(locIndexStr.c_str());
					tempFace.vertex[i][1] = atoi(texIndexSrt.c_str());
					tempFace.vertex[i][2] = atoi(norIndexSrt.c_str());
				}
				
				mFace.push_back(tempFace);
				material[partnumber].push_back(currentmaterial);
			}
		}  
	} 
	delete fileContent;
	//VBOs
	glGenBuffers(1, &VBOs[partnumber]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[partnumber]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mLocation) * mLocation.size(), NULL, GL_STATIC_DRAW);
	int o = 0;
	for (int i = 0; i < mLocation.size(); i++) 
	{
		glBufferSubData(GL_ARRAY_BUFFER, o, sizeof(mLocation), mLocation[i].Data);
		o += sizeof(mLocation);
	}
	VBOsSIZE[partnumber] = sizeof(mLocation) * mLocation.size();
	//EBOs
	vector< int>tempelement;
	for (int i = 0; i < mFace.size(); i++) 
	{
		tempelement.push_back(mFace[i].vertex[0][0] - 1);
		tempelement.push_back(mFace[i].vertex[1][0] - 1);
		tempelement.push_back(mFace[i].vertex[2][0] - 1);
		
	}
	glGenBuffers(1, &EBOs[partnumber]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[partnumber]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mFace.size() * sizeof(tempelement), &tempelement[0], GL_STATIC_DRAW);
	EBOsSIZE[partnumber] = mFace.size() * sizeof(Face);
	//nEBOs
	
	tempelement.clear();
	for (int i = 0; i < mFace.size(); i++)
	{
		tempelement.push_back(mFace[i].vertex[0][2] - 1);
		tempelement.push_back(mFace[i].vertex[1][2] - 1);
		tempelement.push_back(mFace[i].vertex[2][2] - 1);

	}
	glGenBuffers(1, &nEBOs[partnumber]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nEBOs[partnumber]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mFace.size() * sizeof(tempelement), &tempelement[0], GL_STATIC_DRAW);
	//VAOs
	glGenVertexArrays(1, &VAOs[partnumber]);
	glBindVertexArray(VAOs[partnumber]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[partnumber]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	////uVBO
	//glGenBuffers(1, &uVBOs[partnumber]);
	//glBindBuffer(GL_ARRAY_BUFFER, uVBOs[partnumber]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(mTexcoord) * mTexcoord.size(), NULL, GL_STATIC_DRAW);
	//o = 0;
	//for (int i = 0; i < mLocation.size(); i++)
	//{
	//	glBufferSubData(GL_ARRAY_BUFFER, o, sizeof(mTexcoord), mTexcoord[i].Data);
	//	o += sizeof(mTexcoord);
	//}
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	//nVBO
	glBindVertexArray(VAOs[partnumber]);
	glGenBuffers(1, &nVBOs[partnumber]);
	glBindBuffer(GL_ARRAY_BUFFER, nVBOs[partnumber]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mNormal) * mNormal.size(), NULL, GL_STATIC_DRAW);
	o = 0;
	for (int i = 0; i < mNormal.size(); i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, o, sizeof(mNormal), mNormal[i].Data);
		o += sizeof(mNormal);
	}
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	
	std::cout << "Success!  ";
	std::cout << "元件面數 " << EBOsSIZE[partnumber] / sizeof(Face) << endl;
}

Module::~Module()
{
}

