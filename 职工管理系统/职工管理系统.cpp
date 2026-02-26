#include<iostream>
#include"WorkerManager.h"
#include"worke.h"
#include"employee.h"
#include"chairman.h"
#include"manager.h"
using namespace std;
int main()
{
	WorkerManager boss;
	int choice=0;
	
	
	while(1)
	{
			boss.show_menu();
			cout<<"ÇëÊäÈëÄúµÄÑ¡Ôñ"<<endl;
			cin>>choice;
			switch(choice)
			{
				case 0:
					boss.exitsystem();
					break;
				case 1:
					boss.addemp();
					system("pause");
					system("cls");
					break;
				case 2:
					boss.showemp();
					break;
				case 3:
					boss.delemp();
					break;
				case 4:
					boss.modemp();
					break;
				case 5:
					boss.findemp();
					break;
				case 6:
					boss.sort();
					break;
				case 7:
					boss.cleanflie();
					break;	
				default:
					system("cls");
					break;
											
				
				
			}
			 
	}

	
	
	

	system("pause");
	
	
	return 0;
} 
