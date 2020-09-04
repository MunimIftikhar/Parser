#include "stack.h"
#pragma once

struct PT_index
{
	string type;
	int index;
	int assignedNum;
};
struct tokens{
	string name;
	string type;
};

vector <vector<int>> grammerMatrix;
vector <vector<int>> parseTable;
vector <PT_index> ptCol;
vector <tokens>token;
vector <int>grammer;
Stack st;


void readGrammerMatrix();
void readParseTable();
void readPtColNo();
void readTokens();
void parsing();
PT_index searchColIndex(string type);
bool checkIftoken(int top);
void pushGrammerMatrixRow(int i);
void writeGrammer(vector <int> gr);

ofstream fout("GrmmerProduction.txt");
ofstream terror("errors.txt");

int main()
{
	readGrammerMatrix();
	readParseTable();
	readPtColNo();
	readTokens();
	parsing();

	return 0;
}



void parsing()
{
	int ptRow = 0;
	st.push(-4);//-4 is used as $ sign
	st.push(0);
	//grammer.push_back(0);
	PT_index tokenInfo;
	//pushGrammerMatrixRow(0);
	for (int i = 0; i < token.size(); i++)
	{
		int top = st.Top();
		tokenInfo = searchColIndex(token[i].type);
		//cout << tokenInfo.index << endl;
		while (top != tokenInfo.assignedNum)
		{
			grammer.push_back(top);
			PT_index infodollar = searchColIndex("$");
			if (checkIftoken(top) == true && top != infodollar.assignedNum)
			{
				st.pop();
				terror << token[i].name << " " << token[i].type << endl;
				//grammer.pop_back();
				break;
			}
			if (top == -4)
			{
				//grammer.push_back(0);
				//terror << token[i].name << " " << token[i].type << endl;
				st.push(0);
				break;
			}
			if (top == -3)
			{
				//grammer.pop_back();
				st.pop();
			}
			if (tokenInfo.index < 0)
			{
				break;
			}
			if (tokenInfo.index >= 0 && top>=0)
			{
				int lineNo = parseTable[top][tokenInfo.index];
				if (lineNo == -1 || lineNo == -2)
				{
					st.pop();
					terror << token[i].name << " " << token[i].type << endl;
				}
				if (lineNo >= 0)
				{
					//grammer.push_back(top);
					st.pop();
					pushGrammerMatrixRow(lineNo);
					writeGrammer(grammer);
					grammer.clear();
				}
			}
			
			top = st.Top();
		}
		if (top == tokenInfo.assignedNum)
		{
			
			st.pop();
			//grammer.pop_back();
			//grammer.clear();
			//grammer.push_back(0);
		}	
	}
}

void writeGrammer(vector <int> gr)
{
	fout << gr[0];
	fout << " -> ";
	for (int i = 1; i < gr.size(); i++)
	{
		fout << gr[i];
		fout << " ";
	}
	fout << endl;
}

void pushGrammerMatrixRow(int i)
{
	
	for (int m = grammerMatrix[i].size()-1; m >= 0; m--)
	{
		st.push(grammerMatrix[i][m]);
		//grammer.push_back(grammerMatrix[i][m]);
	}
	for (int m = 0; m < grammerMatrix[i].size(); m++)
	{
		grammer.push_back(grammerMatrix[i][m]);
	}
}

void readTokens()
{
	
	ifstream fin("tokens.txt");
	if (!fin.is_open())
	{
		cout << "Unable to open file.";
		return;
	}

	while (!fin.eof())
	{
		tokens t;
		fin >> t.name;
		fin >> t.type;
		token.push_back(t);
	}
	fin.close();
}

PT_index searchColIndex(string type)
{
	int size = ptCol.size();
	for (int i = 0; i < size; i++)
	{
		
		if (ptCol[i].type.compare(type) == 0)
		{
			//cout << ptCol[i].type << endl;
			return ptCol[i];
			
		}
	}
	PT_index temp;
	temp.index = -1;
	return temp;
}

bool checkIftoken(int top)
{
	int size = ptCol.size();
	for (int i = 0; i < size; i++)
	{
		if (top == ptCol[i].assignedNum)
		{
			return true;
		}
	}
	return false;
}

void readGrammerMatrix()
{
	int row = 0, col = 0; char line[1024];
	ifstream fin("grammerMatrix.txt");
	if (!fin.is_open())
	{
		cout << "Unable to open file.";
		return;
	}
	
	while (!fin.eof())
	{
		vector <int> num;
		fin.getline(line,1024);
		char* next;
		char* token = strtok_s(line, " ",&next);
		
		// Keep printing tokens while one of the 
		// delimiters present in str[]. 
		while (token != NULL)
		{
			num.push_back(stoi(token));
			token = strtok_s(NULL, " ",&next);
		}
		grammerMatrix.push_back(num);
	}
	fin.close();
}

void readParseTable()
{
	int row = 0, col = 0;
	ifstream fin("parseTable.txt");
	if (!fin.is_open())
	{
		cout << "Unable to open file.";
		return;
	}
	int i = 0, num = 0;
	fin >> row; fin >> col;
	while (i<row)
	{
		int k;
		vector<int>num1;
		for (k = 0; k < col; k++)
		{
			fin >> num;
			num1.push_back(num);
		}
		parseTable.push_back(num1);
		i++;
	}
	fin.close();
}

void readPtColNo()
{
	int row = 0, col = 0; PT_index ind;
	ifstream fin("PT_columns.txt");
	if (!fin.is_open())
	{
		cout << "Unable to open file.";
		return;
	}

	while (!fin.eof())
	{
		
		fin >> ind.type;
		fin >> ind.index;
		fin >> ind.assignedNum;
		ptCol.push_back(ind);	
	}
	fin.close();
}

