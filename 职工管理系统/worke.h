#pragma once
#include<iostream>
using namespace std;
#include<string>
class worker
{
	public:
		int id;
		string name;
		string did;
		virtual void showinfor()=0;
		
};
