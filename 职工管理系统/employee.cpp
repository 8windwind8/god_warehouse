#include"employee.h"
employee:: employee(string name,int id,string did)
{
	this->id=id;
	this->name=name;
	this->did=did;

}
		 void employee:: showinfor()
		{
			
			cout<<"职工编号 "<<this->id<<endl; 
			cout<<"职工姓名 "<<this->name<<endl;
			cout<<"职工岗位 "<<this->did<<endl;
			cout<<"岗位职责：完成经理布置任务"<<endl; 
			
		}
		
