/* C++ Project -4 Employee Payroll Management System
P Asish Manoj Reddy 
//username,password - asish
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <string.h>
#include <windows.h>
#include <ctime>
#include <conio.h>
using namespace std;
int c=0;
unordered_map<int,int>m; 
//storing index in map to avoid searching time


//used goto function only in displaying payslip design
void gotoxy(int x, int y) 
{ 
    COORD c;
    c.X = y; 
    c.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

class Employee{
    protected:
    char temp[100];
    
    private:
    int id,age,exp;
    int grad=0; 
    char name[100],depart[100],pan[12],design[100];
    float day,base,da,hra,ma,ta,special,pt,pf,ctc,net,tds,leave=0;
    
    public:
    void grade();
    void sal(float );
    void details();
    
    void n_name();
    void n_age();
    void n_exp();
    void n_depart();
    void n_design();
    void n_sal();
    void n_grade();
    void leaves();

    friend void add(int ); 
    friend void modify();
    friend void slip();
    friend void saverecord();
    friend void readrec();
    friend void display();
    friend void del();
    friend void update();
    friend void search();
};
vector<Employee>o;  //using vector to not limit number of employees

void readrec(){
    c=0;
    ifstream file("payo.txt");
    if(!file)
    cout<<"No Records Saved-Add some Record"<<endl;
    else{
    Employee o1;
    int i=0;
    while(file>>o1.id){
     m[o1.id]=o1.id;
     file>>o1.name>>o1.age>>o1.exp>>o1.depart>>o1.design>>o1.grad>>o1.base>>o1.pan;
     if(o1.grad!=6)
     o1.grade();
     else
     o1.sal(o1.base);
     o.push_back(o1);
     i++;
     //  cout<<i<<' '<<m[o1.id]<<' '<<o1.id<<endl;
     }
     c=i;
   }
   file.close();
}
void update(){
     ofstream file("payo.txt");
     for(int i=0;i<c;i++){
        file<<i+1<<' '<<o[i].name<<' '<<o[i].age<<' '<<o[i].exp<<' '<<o[i].depart<<' '<<o[i].design<<' '<<o[i].grad<<' '<<o[i].base<<' '<<o[i].pan<<endl;
     }
     file.close();
}

//addition
void add(int n){
    system("cls");
    int k=c+1;
    for(int i=c;i<c+n;i++){
        m[i+1]=i+1;
        Employee o1;
        o1.id=k++;
        cout<<"Enter the Name: ";
        cin>>o1.name;
        cout<<"Enter the Age: ";
        cin>>o1.age;
        cout<<"Enter the experience: ";
        cin>>o1.exp;
        cout<<"Enter the Department: ";
        cin>>o1.depart;
        cout<<"Enter the Designation: ";
        cin>>o1.design;
        cout<<"\n1.Grade 1(Dean)\n2.Grade 2(professor)\n3.Grade 3(assistant profesors,consultants)\n4.Grade 4(Staff)\n5.Grade 5(Warden and Managers)\n6.Custom Salary\n\nSelect Option\\Grade:";
        cin>>o1.grad;
        o1.grade();
        cout<<"Enter the Pan ID: ";
        cin>>o1.pan;
        o.push_back(o1);
    }
    c=c+n;
    update();
}

//list of employees
void display(){
        system("cls");
        int i=0;
        if(c==0){
        cout<<"No Record Present Empty list"<<endl;
        return ;
        }
        cout<<"\nID   Name\t   Age\t Experience\tDepartment\tDesignation"<<endl;
        while(i<c){
        gotoxy(i+2,0);
        cout<<o[i].id;
        gotoxy(i+2,5);
        cout<<o[i].name;
        gotoxy(i+2,20);
        cout<<o[i].age<<"    "<<o[i].exp;
        gotoxy(i+2,41);
        cout<<o[i].depart;
        gotoxy(i+2,57);
        cout<<o[i].design<<endl;
         i++;
        }   
}

//searching an employee
void search(){
    int i=0;
     cout<<"Enter the Employee id to search: ";
     cin>>i;
     if(m[i]!=0){
     cout<<"\nEmployee ID found:\n\n";
     i=m[i]-1;
     cout<<"ID : "<<o[i].id<<endl;
     cout<<"Name : "<<o[i].name<<endl;
     cout<<"Age : "<<o[i].age<<endl;
     cout<<"Experience : "<<o[i].exp<<endl;
     cout<<"Department : "<<o[i].depart<<endl;
     cout<<"Grade : "<<o[i].grad<<endl;
     cout<<"PAN-ID : "<<o[i].pan<<endl;
      //modify this record?
     }
     else{
        cout<<"No Record Found with given id"<<endl;
        return ; 
     }
}

//changing record
void modify(){
     int i,ch;
     cout<<"Enter the Employee id to Modify: ";
     cin>>i;
     system("cls");
     if(m[i]!=0){
        cout<<"\n1.Edit Employee Details\n2.Edit Salary\n3.Change Grade\n4.Exit\n\nSelect the option to modify :";
        cin>>ch;
        switch(ch){
            case 1:
            o[i-1].details();
            break;
            case 2:
            o[i-1].n_sal();
            break;
            case 3:
            o[i-1].n_grade();
            break;
            default:
            return ;
        }
        update();
     }
     else{
        cout<<"No Record Found with given id"<<endl;
     }
}

void Employee::details(){
    system("cls");
    int ch;
    while(1){
    cout<<"\n1.Name\n2.Age\n3.Experience\n4.Department\n5.Designation\n6.Return\n\nSelect Which Parameter to Modify :";
    cin>>ch;
    switch(ch){
        case 1:
        n_name();
        break;
        case 2:
        n_age();
        break;
        case 3:
        n_exp();
        break;
        case 4:
        n_depart();
        break;
        case 5:
        n_design();
        break;
        default:
        return ;
    }
    }
}
void Employee::n_name(){
     cout<<"Enter the New Name :";
     cin>>name;
}
void Employee::n_age(){
     cout<<"Enter the Age :";
     cin>>age;
}
void Employee::n_exp(){
     cout<<"Enter the Experience :";
     cin>>exp;
}
void Employee::n_depart(){
     cout<<"Enter the Department :";
     cin>>depart;
}
void Employee::n_design(){
     cout<<"Enter the Designation :";
     cin>>design;
}
void Employee::n_sal(){
    grad=6;
    cout<<"Enter the New Base Salary :";
    cin>>base;
    sal(base);
}
void Employee::n_grade(){
    cout<<"Enter the New Grade :";
    cin>>grad;
    grade();
}
void Employee::sal(float base){
    Employee::base=base;
     day=base/30;  
     da=0.32*base;
     hra=0.28*base;
     ma=0.06*base;
     ta=0.09*base; 
     special=0.25*base;
     pt=200;
     pf=(base+da)*0.12;
     ctc=base+da+hra+special+ma+ta;
     net=ctc-pf-pt;
     tds=(net*12);
    if(tds>500000)
    tds=12500+0.20*(tds);
    else if(tds<=500000 and tds>250000)
    tds=tds*0.05;
    else
    tds=0;
    // cout<<"ctc="<<ctc<<' '<<" net ="<<net<<" tds="<<tds<<endl;
}

void Employee::grade(){
    switch(grad){
        case 1:
        sal(50000);
        break;
        case 2:
        sal(25000);
        break;
        case 3:
        sal(15000);
        break;
        case 4:
        sal(10000);
        break;
        case 5:
        sal(5000);
        break;
        case 6:
        n_sal();
        break;
        default:
        cout<<"Select Valid Grade"<<endl;
    }
}

//deletion of a record
void del(){
     Employee temp[c];
     int id;
     cout<<"Enter the Employee id to delete: ";
     cin>>id;
     if(m[id]!=0){
     for(int i=0;i<c;i++){
       temp[i]=o[i];
     }
     for(int i=m[id]-1;i<c-1;i++){
            m[i+1]=i+2;
            int k=o[i].id;
            o[i]=temp[i+1];
            o[i].id=k;
     }
     c--;
     cout<<"\nEmployee Record Deleted Successfully";
     update();
     }
     else
     cout<<"Employee not found, Please Enter Valid id!"<<endl;
}

void Employee::leaves(){
    net=net-leave*day;
    leave=leave*day;
}

//salary slip
void slip(){
    int i=0;
    cout<<"Enter the Employee id : ";
    cin>>i;
    if(m[i]!=0){
       i=m[i]-1;
       cout<<"Enter the Number of employee Leaves: ";
       cin>>o[i].leave;
       o[i].leaves();
       system("cls");
       cout<<"\n-----------------> SRM AP salary slip <-----------------"<<endl;
       time_t now = time(0);
       tm *t = localtime(&now);
       cout<<"Day: "<< t->tm_mday << endl; 
       cout<<"Month: "<< 1 + t->tm_mon<<endl;
       cout<<"Year: " << 1900 + t->tm_year<<endl;
       cout<<"Employee :"<<o[i].name<<endl;
       cout<<"Designation :"<<o[i].design<<endl;
       cout<<"Grade :"<<o[i].grad<<endl;
       cout<<"PAN ID :"<<o[i].pan<<endl<<endl;
       cout<<"\tEarnings\t\t     Deductions"<<endl<<endl;
       cout<<"Basic Sal : "<<o[i].base;
       gotoxy(12,32);
       cout<<"Provident Fund : "<<o[i].pf<<endl;
       cout<<"DA : "<<o[i].da;
       gotoxy(13,32);
       cout<<"Professional Tax : "<<o[i].pt<<endl;
       cout<<"HRA : "<<o[i].hra;
       gotoxy(14,32);
       cout<<"Tax Deducted At Source : "<<o[i].tds<<endl;
       cout<<"Medical Allowance : "<<o[i].ma;
       gotoxy(15,32);
       cout<<"Leave Deduction : "<<o[i].leave<<endl;
       cout<<"Travel Allowance  : "<<o[i].ta<<endl;
       cout<<"Special Allowance : "<<o[i].special;
       float ded=o[i].pt+o[i].pf+o[i].leave;
       for(int j=10;j<18;j++){
       gotoxy(j,29);
       cout<<"|";
       }
       gotoxy(19,1);
       cout<<"Total CTC(month) : "<<o[i].ctc;
       gotoxy(19,32);
       cout<<"Net Deduction : "<<ded;
       gotoxy(21,16);
       cout<<"-> Net Salary :Rupees "<<o[i].net<<endl;
    
    }
    else{
        cout<<"No Record Found with given id"<<endl;
        return ; 
    }
}
//password function
int passcheck(){
    int i=0;
    char user[100],pass[100];
    cout<<"\nEnter the Username: ";
    cin>>user;
    cout<<"Enter the Password: ";
    char x;
     while(1){
        x=getch();
    	if(x!=13){
    		cout<<"*";
			pass[i]=x;
			i++;
        } 
    	else break;
    }
    pass[i]='\0';
    if(strcmp(user,"asish")==0 && strcmp(pass,"asish")==0){
        system("cls");
    cout<<"\nLogin Successful"<<endl;
    return 1;
    }
    else{
    cout<<"\nInvalid Credentials!"<<endl;
    return 0;
    }
}
int main(){
    x:
    if(passcheck()){
    readrec();
    int n;
    int ch;
    cout<<"\n-----------------> SRMAP Payroll Management <-----------------"<<endl;
    while(1){ 
    cout<<"\n\n1.Add an Employee\n2.Display List\n3.Search an Employee\n4.Modify a Record\n5.Delete Record\n6.Employee Salary Slip\n\nEnter the Choice :";
    cin>>ch;
    switch(ch){
    case 1:{
      cout<<"Enter the Number of Employees to Add:";
      cin>>n;
      add(n);
      break;
    }
    case 2:
      display();
      break;
    case 3:
      search();
      break;
    case 4:
      modify();
      break;
    case 5:
      del();
      break;
    case 6:
      slip();
      break;
    case 7:
      update();
      break;
    default:
      cout<<"Choose Valid Option! :";
    }
   }
  }
    else{
        cout<<"Try Again "<<endl;
        goto x;
    }
}