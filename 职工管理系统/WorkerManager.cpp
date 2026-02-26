#include"WorkerManager.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(filename,ios::in);
	if(!ifs.is_open())
	{
		cout<<"当前未存在职工" <<endl; 
			this->empnum=0;
	this->emparray=NULL;
	this->fileisempty=true;
	ifs.close();
	return;
	}
	char ch;
	ifs>>ch;
	if(ifs.eof())
	{
	//	cout<<"文件为空"<<endl;
			this->empnum=0;
	this->emparray=NULL;
	this->fileisempty=true;
	ifs.close();
	return;
	}
	int num=this->getempnum();
	//cout<<"当前职工人数为: "<<num<<endl;
	this->empnum=num;
	this->emparray=new worker*[this->empnum];
	this->initemp();
	
	
	
	
}
void WorkerManager::delemp()
{
	if(this->fileisempty)
	{
		cout<<"文件不存在或记录为空" <<endl;
	}
	else{
		cout<<"请输入要删除职工编号"<<endl;
		int index;
		cin>>index;
	int uu=this->isexist(index);
	if(uu!=-1)
	{
		for(int i=index;i<this->empnum-1;i++)
		{
			this->emparray[i]=this->emparray[i+1];
		}
		this->empnum--;
		this->save();
		cout<<"删除成功"<<endl;
		
	}
	else{
		cout<<"该职工不存在"<<endl;
	}
	}
	system("pause");
	system("cls");
	
	
}
int WorkerManager::isexist(int id)
{
	int index=-1;
	for(int i=0;i<this->empnum;i++)
	{
		if(this->emparray[i]->id==id)
		{
			index=i;
			break;
		}
	}
	return index;	
}





void WorkerManager::showemp()
{
	if(this->fileisempty)
	{
		cout<<"文件不存在或记录为空"<<endl; 
	}
	else{
		for(int i=0;i<this->empnum;i++)
		{
			this->emparray[i]->showinfor();
		}
	}
	system("pause");
	system("cls");
		
}




 void WorkerManager::show_menu()
{
	cout<<"**************************************"<<endl;
	cout<<"******* 欢迎使用职工管理系统 *******"<<endl;
	cout<<"        0.退出" <<endl;
	cout<<"        1.添加职工信息" <<endl;
	cout<<"        2.显示职工信息" <<endl;
	cout<<"        3.删除离职职工" <<endl;
	cout<<"        4.修改职工信息" <<endl;
	cout<<"        5.查找职工信息" <<endl;
	cout<<"        6.按照编号排序" <<endl;
	cout<<"        7.清空所有文档" <<endl;
	cout<<"*************************************" <<endl;
}





void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(filename,ios::out);
	for(int i=0;i<this->empnum;i++)
	{
		ofs<<this->emparray[i]->id<<"  ";
		 ofs  <<this->emparray[i]->name<<"  ";
		  ofs <<this->emparray[i]->did<<endl;
	}
	ofs.close();
}
void WorkerManager::cleanflie()
{
	cout<<"确定清空？"<<endl;
	cout<<"1.确认"<<endl;
	cout<<"2.返回"<<endl;
	int select;
	cin>>select;
	if(select==1)
	{
		ofstream ofs;
		ofs.open(filename,ios::trunc);
		ofs.close();
		if(this->emparray!=NULL)
		{
			
			for(int i=0;i<this->empnum;i++)
			{
				delete this->emparray[i];
				this->emparray[i]=NULL;
			}
			delete[] this->emparray;
			this->emparray=NULL;
			this->fileisempty=true;
			this->empnum=0;
		}
		cout<<"清空成功"<<endl;
		system("pause");
		system("cls");
	}
	else{
		system("pause");
		system("cls");
	}
	
}


void WorkerManager::sort()
{
	if(this->fileisempty)
	{
		cout<<"文件不存在或记录为空"<<endl;
		system("pause");
		system("cls");
	}
	else{
		
		cout<<"请选择排序方式: "<<endl;
		cout<<"1.按职工编号升序排列"<<endl;
	cout<<"2.按职工编号降序排列"<<endl;
	int cho=0;
	for(int i=0;i<this->empnum;i++) 
	{
		int minomax=i;
		for(int j=i+1;j<this->empnum;j++)
		{
			if(cho==1)
			{
				
				if(this->emparray[minomax]->id > this->emparray[j]->id)
				{
					minomax=j;
				}
			}
			else{
					if(this->emparray[minomax]->id < this->emparray[j]->id)
				{
					minomax=j;
				}
				
				
				
			}
		}
		if(i!=minomax)
		{
			worker *temp=this->emparray[i];
			this->emparray[i]=this->emparray[minomax];
			this->emparray[minomax]=temp;
		}
		
	}
		
	}
	cout<<"排序成功,结果如下："<<endl;
	this->save(); 
	this->showemp();
	
	
	
	
	
	
	
}
 	
	 
	 
	 
	 	
void WorkerManager::addemp()
{
	cout<<"请输入添加职工数量"<<endl;
	int newaddnum=0;
	cin>>newaddnum;
	if(newaddnum>0) 
	{
		int newsize=this->empnum+newaddnum;
	worker ** newspace=	new worker*[newsize];
	if(this->emparray!=NULL)
	{
		for(int i=0;i<this->empnum;i++)
		{
			newspace[i]=this->emparray[i];
		}
	}
	for(int i=0;i<newaddnum;i++)
	{
		int Id;
		string Name;
		string Did;
		cout<<"请输入第"<<i+1<<"个职工编号： " <<endl;
		cin>>Id; 
		while(!this->freid(Id))
		{
			cout<<"该职工编号已经存在，请重新输入第"<<i+1<<"个职工编号: "<<endl; 
			cin>>Id;
		}
		cout<<"请输入第"<<i+1<<"个职工姓名： " <<endl;
		cin>>Name; 
		cout<<"请输入第"<<i+1<<"个职工岗位： " <<endl;
		cout<<"老板，经理，员工"<<endl;
		cin>>Did; 
		int num;
		if(Did=="老板")
		{
			num=1;
		}
		else if(Did=="经理")
		{num=2;
		}
		else{
			num=3;
		}
		worker *wworker=NULL;
		switch(num)
		{
			case 1:
			wworker =new chairman(Name,Id,Did);
			break;
			case 2:
			wworker =new manager(Name,Id,Did);
			break;
			case 3:
			wworker =new employee(Name,Id,Did);
			break;
			default:
				break;
		}
		newspace[this->empnum+i]=wworker;
	}
	delete[]this->emparray;
	this->emparray=newspace;
	this->empnum=newsize;
	cout<<"成功添加"<<newaddnum<<"名职工!"<<endl; 
	this->fileisempty=false;
	this->save();
	}
	else{
		cout<<"输入有错误"<<endl;
	}
}
bool WorkerManager::reid(int a)
{
	
	int num=a;
	
	for(int i=0;i<this->empnum;i++)
	{
		if(this->emparray[i]->id==num)
		{
			return false; 
		}
		
		
		
		
	}
	return true;
	
	
	
	
	
	
}
bool WorkerManager::freid(int a)
{
	
	
	if(this->reid( a))
	{
		return true;
	}
	else{
		cout<<"该职工编号已经存在"<<endl;
		return false;
	}
}






int WorkerManager::getempnum()
{
	ifstream ifs;
	ifs.open(filename,ios::in);
	int id;
	string name;
	string did;
	int num=0;
	while(ifs>>id && ifs>>name && ifs>>did)
	{
		num++;
	}
	return num;	
}






 void WorkerManager::initemp()
 {
 	ifstream ifs;
	ifs.open(filename,ios::in);
	int id;
	string name;
	string did;
	int index=0;
	
	while(ifs>>id && ifs>>name && ifs>>did)
	{
		worker *workerr=NULL;
		if(did=="员工")
		{
			workerr=new employee(name,id,did);
		}
		else if(did=="经理")
		{
			workerr=new manager(name,id,did);
		}
		else{
			workerr=new chairman(name,id,did);
		}
		this->emparray[index]=workerr;
		index++;
		
	}
	ifs.close();
 	
 	
 }
 
 
 
 
 
 void WorkerManager::modemp()
 {
 	if(this->fileisempty)
 	{
 		
 		
 		cout<<"文件不存在或记录为空"<<endl;
	}
	else{
		cout<<"请输入修改职工编号: "<<endl;
		int index;
		cin>>index;
		int num=this->isexist(index);
		if(num!=-1)
		{
			delete this->emparray[num];
			int newid;
			string newname;
			string newdid;
			cout<<"查找成功"<<endl;
			cout<<"请输入新职工编号："<<endl;
			cin>>newid;
			while(!this->freid(newid))
		{
			cout<<"该职工编号已经存在,请重新输入该职工编号: "<<endl; 
			cin>>newid;
		}
			cout<<"请输入新职工姓名："<<endl;
			cin>>newname;
			cout<<"请输入新职工岗位："<<endl;
			cout<<"老板，经理，员工"<<endl;
			cin>>newdid;
			worker *worker=NULL;
		// 替换原来的switch代码

if (newdid == "老板") {
    worker = new chairman(newname, newid, newdid);
} else if (newdid == "经理") {
    worker = new manager(newname, newid, newdid);
} else  {
    worker = new employee(newname, newid, newdid);
} 
			this->emparray[num]=worker;
			cout<<"修改成功"<<endl;
			this->save();
		}
		else{
			
			cout<<"该职工不存在"<<endl;
		}
		
	
		
		
		
	}
		system("pause");
		system("cls");
 	
 	
 	
 	
 	
 	
 	
 	
 	
 	
 	
 }

void WorkerManager::findemp()
{
	if(this->fileisempty)
	{
		cout<<"文件不存在或记录为空"<<endl;
	}
	else{
		
			cout<<"请输入要查找职工的姓名: "<<endl;
	string name;
	cin>>name;
	int flag=0;
	 for(int i=0;i<this->empnum;i++)
	 {
	 	if(this->emparray[i]->name==name)
	 	{
	 		cout<<"查找成功,该职工信息如下："<<endl;
	 		this->emparray[i]->showinfor();	
			 flag=1;		
		}
	 }
	 if(flag==0)
	 {
	 	cout<<"该员工不存在"<<endl;
	 }
		
	}
	system("pause");
	system("cls");
	

}




void WorkerManager::exitsystem()
{
	cout<<"欢迎下次使用"<<endl;
	system("pause");
	exit(0);
}
WorkerManager::~WorkerManager()
{
	if(this->emparray!=NULL)
	{
		delete[]this->emparray;
		this->emparray=NULL;
	}
	
	
	
}
