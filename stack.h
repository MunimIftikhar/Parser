#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <tchar.h>
#pragma once
using namespace std;

class Stack{
private:
	vector <int> terminal;
	int size;
	int cur;
public:
	Stack()
	{
		cur = -1;
		size = 0;
	}
	void push(int num)
	{
		terminal.push_back(num);
		cur++;
		size++;
	}
	int pop()
	{
		int n = terminal[cur--]; 
		terminal.pop_back();
		return n;
	}
	int Top(){

		return terminal[cur];
	}

};