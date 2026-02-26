 #pragma once
 #include<iostream>
 #include"employee.h"
#include"chairman.h"
#include"manager.h"
#include"worke.h"
#include<fstream>
#define filename "empfile.txt"
 using namespace std;
 class WorkerManager
 {
 	public:
 		WorkerManager();
 		
 		void show_menu();
 		int empnum;
 		worker **emparray;
 		void addemp();
 		void save();
 		void showemp();
 		bool fileisempty;
 		void modemp();
 		int getempnum();
 		void initemp();
 		void delemp();
 		int isexist(int id);
 		void exitsystem();
 		void findemp();
 		bool reid(int a);
 		bool freid(int a);
 		void sort();
 		void cleanflie();
 		
 		~WorkerManager();
 		
 	
 	
 	
 	
 };
