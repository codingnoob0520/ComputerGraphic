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
	vector<Float3> mLocation;
	vector<Float3> mNormal;
	vector<Float2> mTexcoord;
	vector<Face> mFace;
private:

};

Module::Module(const char* objFilename,int partnumber)
{
	int nFileSize = 0;
	unsigned char* fileContent = LoadFileContent(objFilename, nFileSize);    
	if (fileContent == nullptr)     
	{
		cout << "fail" << endl;
		return;
	}
	cout << "Loading " << objFilename << " ... ";
	stringstream ssFileContent((char*)fileContent);   
	string temp;      
	char szoneLine[256];       
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
	vector<unsigned int>tempelement;
	for (int i = 0; i < mFace.size(); i++) 
	{
		tempelement.push_back(mFace[i].vertex[0][0] - 1);
		tempelement.push_back(mFace[i].vertex[1][0] - 1);
		tempelement.push_back(mFace[i].vertex[2][0] - 1);
		
	}
	glGenBuffers(1, &EBOs[partnumber]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[partnumber]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mFace.size() * sizeof(Face), &tempelement[0], GL_STATIC_DRAW);
	EBOsSIZE[partnumber] = mFace.size() * sizeof(Face);
	cout << "Success!" << endl;
	cout << "元件面數 "<< EBOsSIZE[partnumber]/ sizeof(Face) << endl;
	glGenVertexArrays(1, &VAOs[partnumber]);
	glBindVertexArray(VAOs[partnumber]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

}

Module::~Module()
{
}

