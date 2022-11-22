#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<fstream.h>
#include<string.h>
#include<dos.h>
#include<stdio.h>
#include<iomanip.h>
#include<ctype.h>

#define f1 "./MyProj/data.dat"
#define f2 "./MyProj/temp.dat"
class details
{
int id;
char bname[25];
char authname[25];
float bprice;
int stock;
public:
Book(){
id=0;
strcpy(bname,"no name");
strcpy(authname,"no name");
bprice=0;
stock=0;
}

void getdetails()
{
clrscr();
cout<<"Enter the Book Id: ";
cin.ignore();
cin>>id;
cout<<"Enter the Book Name: ";
cin.clear();
cin.ignore();
cin.getline(bname,25);
cout<<"Enter the Author Name: ";
cin.clear();
cin.getline(authname,25);
cout<<"Enter the Book Price: ";
cin>>bprice;
cout<<"Enter the No of books in stock: ";
cin>>stock;
}
void modify_book()
{
cout<<"\nBook Id : "<<id;
cout<<"\nModify Book Name : ";
cin.clear();
cin.ignore();
cin.getline(bname,25);
cout<<"\nModify Author's Name: ";
cin.clear();
cin.getline(authname,25);
cout<<"\nModify Book Price: ";
cin>>bprice;
cout<<"\nEnter No. Of Books: ";
cin.clear();
cin.ignore();
cin>>stock;
}
int getbookid()
{
return id;
}
void show_book()
{
cout<<"\nBook Number: "<<id;
cout<<"\nBook Name: "<<bname;
cout<<"\nAuthor's Name: "<<authname;
cout<<"\nPrice: "<<bprice;
cout<<"\nStock: "<<stock;
}
void view()
{
cout<<setw(5)<<id<<setw(20)<<bname<<setw(20)<<authname<<setw(20)<<bprice<<setw(10)<<stock<<endl;}
};
void menu();
details d;
fstream fp;
void addbook()
{
details d1;
ifstream fb;
int more;
fp.open(f1,ios::app|ios::in);
fb.open(f1,ios::in);
if(!fp)
{
cout<<"File cant be opened";
}
else
{
do{d.getdetails();
while(fb.read((char*)&d1,sizeof(d1)))
{
if(d1.getbookid()==d.getbookid()){
cout<<"\n\n\nThis record cant be inserted.";
cout<<"\nRecord for this Book Id already exists. ";
cout<<"\nPlease use Modify if you want to update it.. ";
cout<<"\n\n-> Press any key to return to the Main Menu... ";
getch();
fb.close();
clrscr();
return;
}}
if(d.getbookid()==0){
cout<<"\n\nThis record cant be inserted.";
fp.close();
return;}
fp.write((char *)&d,sizeof(d));
cout<<"\nPress 1 to add more books.";
cout<<"\nPress 2 to return to main menu.\n";
cout<<"Enter: ";
cin>>more;
}while(more == 1);
fp.close();
clrscr();
cout<<"Book/s has been added successfully";
cout<<"\n\nPress any key to continue to the main menu";
}}
void display_all()
{
clrscr();
fp.open(f1,ios::in);
if(!fp)
{
cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
getch();
return;
}
cout<<"\n\n\t\t\t\tBook LIST\n\n";
cout<<"=============================================================================\n";
cout<<"Book Id"<<setw(18)<<"Book Name"<<setw(20)<<"Author"<<setw(20)<<"Price"<<setw(10)<<"Stock"<<endl;
cout<<"=============================================================================\n";
while(fp.read((char*)&d,sizeof(d)))
{
d.view();
}
cout<<"\n\n ->Press any key to return to Main Menu";
fp.close();
getch();
clrscr();
}

void update_book(){
clrscr();
int found=0,n;
cout<<"\n\n\tx-x- MODIFY BOOK -x-x";
cout<<"\n\nEnter The Book Id: ";
cin>>n;
fp.open(f1,ios::in|ios::out);
while(fp.read((char*)&d,sizeof(d)) && found==0)
{
if(d.getbookid()==n)
{
d.show_book();
int pos;
cout<<"\nEnter The New Details of book"<<endl;
d.modify_book();
pos=(-1)*sizeof(d);
fp.seekp(pos,ios::cur);
fp.write((char*)&d,sizeof(d));
cout<<"\n\n\t Record Updated Successfully...";
found=1;
}}
fp.close();
if(found==0)
cout<<"\n\n Record Not Found ";
getch();
}

void searchbook(int n)
{
int check=0;
cout<<"\nBOOK DETAILS\n";
fp.open(f1,ios::in);
while(fp.read((char*)&d,sizeof(d)))
{if(d.getbookid()==n)
{
d.show_book();
check=1;
}
}
fp.close();
if(check==0)
cout<<"\n\nBook does not exists";
cout<<"\n\nPress any key to return to Main Menu";
getch();
clrscr();
}
fstream ft;

void delbook()
{
clrscr();
int flag=0,n;char c;
cout<<"\n\n\n\tx-x- DELETE BOOK -x-x";
cout<<"\n\nEnter The Book's number You Want To Delete: ";
cin>>n;
fp.open(f1,ios::in|ios::out);
ft.open(f2,ios::out);
fp.seekg(0,ios::beg);
while(fp.read((char*)&d,sizeof(d)))
{
if(d.getbookid()!=n)
{
ft.write((char*)&d,sizeof(d));
}
else {
d.show_book();
cout<<"\n\nAre you sure you want to delete this record?\nEnter y for yes and n for no -> ";
cin>>c;
c=tolower(c);
switch(c)
{
case 'y':
flag=1;
break;
case 'n':
{
ft.write((char*)&d,sizeof(d));
flag=2;
break;
}}}}
ft.close();
fp.close();
remove(f1);
rename(f2,f1);
if(flag==1)
cout<<"\n\nRecord Deleted Successfully ..";
else if(flag==2)
cout<<"\n\nRecord Has not been Deleted ..";
else
cout<<"\n\nRecord not found";
cout<<"\n\n-> Press any key to return to the Main Menu";
getch();
clrscr();
}

void welcomeMessage()
{
cout<<"\n\n\n\n\n";
cout<<"\n\t\t **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
cout<<"\t\t      =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
cout<<"\n\t\t                    = WELCOME =";
cout<<"\n\t\t                      = TO =";
cout<<"\n\t\t                     = BOOK =";
cout<<"\n\t\t                    = STORE =";
cout<<"\n\t\t                  = MANAGEMENT =";
cout<<"\n\t\t                    = SYSTEM =";
cout<<"\n\t\t     =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
cout<<"\n\t\t **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n";
cout<<"\n\n\n\t\t Enter any key to continue.....";
getch();
}


void menu()
{
int choice=0;
do
{
cout<<"\n\n\t\tx-x- MAIN MENU -x-x";
cout<<"\n\n1. Add Books";
cout<<"\n2. Search Books";
cout<<"\n3. Update Books";
cout<<"\n4. Delete Books";
cout<<"\n5. View All Books";
cout<<"\n6. Exit";
cout<<"\nEnter the choice: ";
cin>>choice;
switch(choice)
{
case 1:
addbook();
break;
case 2:
int n;
clrscr();
cout<<"\t\tx-x-BOOK SEARCH -x-x \n";
cout<<"\n\nEnter the Book Id to search: ";
cin>>n;
searchbook(n);
break;
case 3:
update_book();
break;
case 4:
delbook();
break;
case 5:
display_all();
break;
case 6:
cout<<"Exiting\n";
sleep(1);
clrscr();
exit(1);
break;
default:
cout<<"Enter a valid input";
}
}
while(choice!=6);
}


void login()
{
int L=1,i,cpl=2;
char c[25],m[25],ch;
clrscr();
do
{
cout<<"\t\t\tx-x- LOGIN PAGE -x-x\n\n";
cout<<"\n\n\n\t\tEnter your Username:";
cin.getline(c,25);
cout<<"\n\t\tEnter the Password:";
for(i=0;i<8;i++)
{
ch = getch();
if(ch==13)
{
break;
}
m[i] = ch;
cout<<"*";
}
m[i]='\0';
if((!strcmp(c,"admin")) && (!strcmp(m,"admin")))
{
clrscr();
cout<<"\n\nWelcome! ";
cout<<"\nYou are Successfully Logged in ";
cout<<"\nPress any key to Continue ....";
getch();
clrscr();
menu();
}
else
{
cout<<"\n\n\t\tLogin Failed \n\t\tEnter Again Username & Password\n";
cout<<"\t\tYou have "<<cpl<<" chances left";
sleep(1);
clrscr();
L++;
cpl--;
}
}
while(L<=3);
if(L>3)
{
cout<<"\t\tLogin Failed";
cout<<"\n\t\tSorry,Unknown User.";
cout<<"\n\n\t\tExiting......";
sleep(1);
clrscr();
}
}

void main()
{
clrscr();
welcomeMessage();
login();
getch();
}