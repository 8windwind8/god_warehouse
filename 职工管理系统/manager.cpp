#include"manager.h"
manager::manager(string name,int id,string did)
{
	this->id=id;
	this->name=name;
	this->did=did;

}
void manager::showinfor()
{
	cout<<"职工编号 "<<this->id<<endl; 
			cout<<"职工姓名 "<<this->name<<endl;
			cout<<"职工岗位 "<<this->did<<endl;
			cout<<"岗位职责：完成老板交给的任务，并下发任务给员工"<<endl; 
	
}
