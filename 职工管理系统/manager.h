#pragma once
#include<iostream>
using namespace std;
#include"worke.h"

class manager:public worker
{
	public:
		manager(string name ,int id,string did);
		virtual void showinfor();
	
	
	
	
	
};
