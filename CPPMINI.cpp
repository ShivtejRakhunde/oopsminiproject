#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
int choice;

class Allotment{
    private:
        char userName[20],password[10], clgname[30];
        int rank, mincutoff, maxcutoff,id, availableSeats;
    public:
        void adminsignup();
        void adminlogin();
        void studentsignup();
        void studentlogin();
        void showcollege();
        int addcollege();
        void applycollege();
        int admin();
        int student();
        void menu()
        {
            cout<<"\n-----------------"<<endl;
            cout<<"----MENU----"<<endl;
            cout<<"1) Administrator Login "<<endl;
            cout<<"2) Administrator Sign Up"<<endl;
            cout<<"3) Student Login "<<endl;
            cout<<"4) Student Sign Up "<<endl;
            cout<<"5) Exit"<<endl;
            cout<<"-----------------\n"<<endl;
        }
}obj1,obj2,obj3;

void Allotment :: adminsignup(){
    fstream file;
    file.open("adminsg.txt",ios :: out | ios :: app);
    cout<<"\nEnter User Name :-";
    cin>>obj1.userName;
    cout<<"Enter Password :- ";
    cin>>obj1.password;
    file.write((char*)&obj1,sizeof(obj1));
    file.close();
    cout<<"Successfully Signed Up"<<endl;
}

void Allotment :: adminlogin(){
        fstream file;
        int flag=0;
        file.open("adminsg.txt",ios :: in);
        char searchName[20], searchPass[10];
        cout<<"Enter User Name :- "<<endl;
        cin>>searchName;
        cout<<"Enter Password :- "<<endl;
        cin>>searchPass;
        while(file.read((char*)&obj1,sizeof(obj1)))
        {
            if(strcmp(obj1.userName,searchName)==0 && strcmp(obj1.password,searchPass)==0)
            {
                cout<<"\nAccount Login Succesfull ";
                flag=1;
                file.close();
                obj1.admin();
            }
        }
        file.close();
        if(flag!=1)
        { cout<<"Incorrect Username or Password!"<<endl; }
}

void Allotment :: studentsignup(){
    fstream file;
    file.open("student.txt",ios :: out | ios :: app);
    cout<<"\nEnter User Name :-";
    cin>>obj2.userName;
    cout<<"Enter Password :- ";
    cin>>obj2.password;
    file.write((char*)&obj2,sizeof(obj2));
    file.close();
    cout<<"Successfully Signed Up"<<endl;
}

void Allotment :: studentlogin(){
        fstream file;
        int flag;
        file.open("student.txt",ios :: in);
        char searchName[20], searchPass[10];
        cout<<"\nEnter User Name :- "<<endl;
        cin>>searchName;
        cout<<"Enter Password :- "<<endl;
        cin>>searchPass;
        while(file.read((char*)&obj2,sizeof(obj2)))
        {
            if(strcmp(obj2.userName,searchName)==0 && strcmp(obj2.password,searchPass)==0)
            {
                cout<<"\nAccount Login Succesfull "; 
                flag=1;
                file.close();
                obj2.student();
            }
        }
        if(flag!=1)
        { cout<<"Incorrect Username or Password!"<<endl; }
        file.close();
        
}

int Allotment :: addcollege(){
            fstream file;
            int flag=0;
            int ck;
            file.open("clglist.txt",ios::in | ios::binary);
            cout<<"\nCollege ID :- ";
            cin>>ck;
            while(file.read((char*)&obj3,sizeof(obj3)))
            {
                if(obj3.id==ck || ck<0)
                {
                    cout<<"College ID Already Exist or Invalid"<<endl;
                    file.close();
                    return 0;
                }
            }
            file.close();
            file.open("clglist.txt",ios::out | ios::app);
            obj3.id=ck;
            cout<<"College Name :- ";
            cin.ignore();
            cin.getline(obj3.clgname,sizeof(obj3.clgname));
            bool validName=true;
            for(int i=0;obj3.clgname[i]!='\0';i++)
            {
                if(!isalpha(obj3.clgname[i]))
                {
                    validName=false;
                    break;
                }
            }
            if(!validName)
            {
                cout<<"Invalid Collage Name"<<endl;
                file.close();
                return 0;
            }
            cout<<"College CutOff Rank(min):- ";
            cin>>obj3.mincutoff;
            cout<<"College CutOff Rank(max):- ";
            cin>>obj3.maxcutoff;
            cout<<"Available Seats :- ";
            cin>>obj3.availableSeats;
            file.seekp(0,ios::end);
            file.write((char*)&obj3,sizeof(obj3));
            file.close();
}

void Allotment :: showcollege(){
            fstream file;
            file.open("clglist.txt",ios::in);
            cout<<"\n"<<"ID  "<<"College\t"<<"Cut Off\t"<<"Available Seats"<<endl;
            while(file.read((char*)&obj3,sizeof(obj3)))
            {
                cout<<obj3.id<<"\t"<<obj3.clgname<<"\t"<<obj3.mincutoff<<" - "<<obj3.maxcutoff<<"\t"<<obj3.availableSeats<<endl;
            }
            file.close();
}

void Allotment :: applycollege(){
            int flag=0;
            fstream file, temp;
            file.open("clglist.txt",ios::in);
            temp.open("temp.txt",ios::out | ios::binary);
            cout<<"Enter Rank:- ";
            cin>>rank;
            while(file.read((char*)&obj3,sizeof(obj3)))
            {
                if(rank>=obj3.mincutoff && rank<=obj3.maxcutoff && obj3.availableSeats>0)
                {
                    cout<<"Alloted College:- "<<obj3.id<<"\t"<<obj3.clgname<<endl;
                    flag=1;
                    obj3.availableSeats--; 
                    temp.write((char*)&obj3,sizeof(obj3));
                    //file.close();
                }
                else{
                    temp.write((char*)&obj3,sizeof(obj3));
                }
            }
            if(flag!=1)
            { cout<<"No Allotment"<<endl; }
            file.close();
            temp.close();
            remove("clglist.txt");
            rename("temp.txt","clglist.txt");
}

int Allotment :: admin(){
        int a;
        do{
        cout<<"\n1) Display College List\n"<<"2) Add New College\n"<<"3) Exit"<<endl;
        cout<<"Enter Choice:- ";
        cin>>a;
        switch(a)
        {
            case 1:
                obj1.showcollege();
                break;
            case 2:
                obj1.addcollege();
                break;
            case 3:
                return 0;
                break;
            default:
            cout<<"Invalid Choice"<<endl;
            break;
        }
    }while(a!=3);
}

int Allotment :: student(){
        int b;
        cout<<"\n1) Apply For College Allotment\n"<<"2) Exit"<<endl;
        cout<<"Enter Choice:- ";
        cin>>b;
        switch(b)
        {
            case 1:
                obj2.applycollege();
                break;
            case 2:
                return 0;
                break;
            default:
                cout<<"Invalid Choice"<<endl;
            break;  
        }
}

int main()
{
    do{
    obj1.menu();
    cout<<"Enter Choice:- ";
    cin>>choice;
    switch (choice)
    {
    case 1 :
        obj1.adminlogin();
        break;
    case 2 :
        obj1.adminsignup();
        break;
    case 3 :
        obj2.studentlogin();
        break;
    case 4 :
        obj2.studentsignup();
        break;
    case 5 :
        return 0;
        break;
    default:
        cout<<"Invalid Choice"<<endl;
        break;
    }
    }while(choice!=5);
}