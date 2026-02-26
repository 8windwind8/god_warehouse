#pragma once
#include<iostream>
#include"worke.h"
using namespace std;
class employee:public worker
{
	public:
		int id;
		string name;
		string did;
		employee(string name,int id,string did); 
		virtual void showinfor();
		
	
	
	
};
