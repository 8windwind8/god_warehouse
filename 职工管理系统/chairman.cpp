#include"chairman.h"
chairman::chairman(string name,int id,string did)
{
	this->id=id;
	this->name=name;
	this->did=did;

}
void chairman::showinfor()
{
	        cout<<"职工编号 "<<this->id<<endl; 
			cout<<"职工姓名 "<<this->name<<endl;
			cout<<"职工岗位 "<<this->did<<endl;
			cout<<"岗位职责：统筹全局"<<endl; 
	
}
