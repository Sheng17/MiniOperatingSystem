#include<iostream>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
using namespace std;


void validate_command(string);
void command_words_calculate(string,string*);
void accept_command();
void display();
int check_directory(string);
void create_directory(string);
int check_file(string,string);
void create_file(string , string);
void delete_file(string directory,string file);
void delete_directory(string directory);
void io_manager();
void memory_manager();
void process_manager();
void main_screen1();
void main_screen2();
int keycounter=0;

//double dimensional linked list with key generated by simple hash function where columns store directories and rows store files
struct node1
{
    string data;
    int key;
    struct node1* row;
    struct node1* column;
};
struct node1* head1=NULL;

//function to create a new directory
void create_directory(string directory)
{
    int flag=check_directory(directory);
    if(flag==1)
    {
        cout<<"directory already exists...\n"<<endl;
        accept_command();
    }
    else
    {
    keycounter++;
    node1* p=new node1;
    p->key=keycounter;
    p->data=directory;
    p->row=NULL;
    p->column=NULL;
    if(head1==NULL)
    {
       head1=p;
    }
    else
    {
     node1* current=head1;
     while(current->column!=NULL)
     {
            current=current->column;
     }
      current->column=p;
    }

     cout<<"directory '"<<directory<<"' created.\n"<<endl;
     accept_command();

    }


}

// function to check whether directory exists in file system or not
int check_directory(string directory)
{
   node1* current=head1;
   while(current!=NULL)
   {
       if(current->data==directory)
       {
           return 1;
       }
       current=current->column;
   }
   return 0;
}

//function to create a new file
void create_file(string directory,string file)
{
   int flag1=check_directory(directory);
   if(flag1==0)
   {
       cout<<"directory '"<<directory<<"' does not exist...\n"<<endl;
       accept_command();
   }

   int flag=check_file(directory,file);
   if(flag==1)
   {
       cout<<"file already exists...\n"<<endl;
       accept_command();
   }
   else
   {
    node1* p=new node1;
    node1* current = head1;
    p->data=file;
    p->row=NULL;
    p->column=NULL;

    while(current!=NULL)
    {
       if(current->data==directory)
          break;
       current=current->column;
    }

    p->key=current->key;

    while(current->row!=NULL)
    {
        current=current->row;
    }

    current->row=p;

    cout<<"file '"<<directory<<"\\"<<file<<"' created.\n"<<endl;
    accept_command();
   }

}

// function to check whether file exists in file system or not
int check_file(string directory, string file)
{
  node1* current=head1;
   while(current!=NULL)
   {
       if(current->data==directory)
           break;
       current=current->column;
   }

   while(current->row!=NULL)
   {
       current=current->row;
       if(current->data==file)
         return 1;
   }

   return 0;
}

//function to display all directories in file system
void show_directories()
{
   int counter=0;
   node1* current=head1;
   if(head1==NULL)
   {
       cout<<"no directories.\n"<<endl;
       accept_command();
   }
   else
   {
      while(current!=NULL)
      {
          counter++;
          cout<<"- "<<current->data<<endl;
          current=current->column;
      }
      cout<<"\n"<<counter<<" directories fetched.\n"<<endl;
   }
}

//function to display all files in a directory of the file system
void show_files(string directory)
{
   int flag=check_directory(directory);
   if(flag==0)
   {
       cout<<"directory does not exist...\n"<<endl;
       accept_command();
   }
   else
   {
   int counter=0;
   node1* current=head1;
   while(current!=NULL)
   {
      if(current->data==directory)
        break;
      current=current->column;
   }

   while(current->row!=NULL)
   {
       current=current->row;
       cout<<"- "<<current->data<<endl;
       counter++;
   }
   if(counter==0)
    cout<<"no files."<<endl;
      cout<<"\n"<<counter<<" files fetched.\n"<<endl;
      accept_command();
   }
}

//function to delete a directory from the file system
void delete_directory(string directory)
{
   int flag=check_directory(directory);
   if(flag==0)
   {
       cout<<"directory does not exist...\n"<<endl;
       accept_command();
   }
   else
   {
    node1 *current1=head1;
    node1 *current2=head1;
    if(head1->data==directory)
    {
        head1=current1->column;
        delete current1;
        delete current2;
    }
    else
    {
    while(current1->column!=NULL)
    {
      current2=current1;
      current1=current1->column;
      if(current1->data==directory)
      {
          current2->column=current1->column;
          delete current1;
          break;
      }
    }

    cout<<"directory '"<<directory<<"' deleted.\n"<<endl;
    accept_command();
    }
   }
}

//function to delete a file from the file system
void delete_file(string directory,string file)
{
  int flag=check_directory(directory);
   if(flag==0)
   {
       cout<<"directory does not exist...\n"<<endl;
       accept_command();
   }
   else
   {
   int flag1=check_file(directory,file);
   if(flag1==0)
   {
       cout<<"file does not exist...\n"<<endl;
       accept_command();
   }
   else
    {
    node1 *current1=head1;
    node1 *current2=head1;

    while(current1->column!=NULL)
    {
      if(current1->data==directory)
      break;
      current1=current1->column;
    }

    while(current1->row!=NULL)
    {
        current2=current1;
        current1=current1->row;
        if(current1->data==file)
        {
            current2->row=current1->row;
            delete current1;
            break;
        }
    }

    cout<<"file '"<<directory<<"\\"<<file<<"' deleted.\n"<<endl;
    accept_command();
    }
   }
}

//function to accept command to operate the file manager/system of the OS
void accept_command()
{
   string command="";                     // local variable
   void validate_command(string command);
   cout<<"root\\:>";
   getline(cin,command);
   validate_command(command);
}

////function to command given to operate the file manager/system of the OS
void validate_command(string command)
{
    void command_words_calculate(string command, string* command_words);
    void accept_command();

    string command_words[4]={""};
    command_words_calculate(command, command_words);

    if(command_words[1]=="")
    {
       cout<<"incomplete command...\n"<<endl;
       accept_command();
    }


    else if(command_words[0]=="create")
    {
        if(command_words[1]=="dir")
        {
            if(command_words[2]=="")
            {
                cout<<"directory name missing...\n"<<endl;
            }
            else
           create_directory(command_words[2]);
        }
        else if(command_words[1]=="file")
        {
            if(command_words[2]=="")
                cout<<"directory name missing...\n"<<endl;
            else if(command_words[3]=="")
                cout<<"file name or directory name missing...\n"<<endl;
            else
            {
                string temp=command_words[3];
                int i,k=0;
                for(i=0;i<temp.length();i++)
                {
                    char ch= temp.at(i);
                    if(ch=='.')
                    {
                        k=1;
                        break;
                    }
                }

                if(k==1)
                {
                    create_file(command_words[2],command_words[3]);
                }
                else
                {
                    cout<<"file type/extension missing...\n"<<endl;
                }
            }
        }
        else
        cout<<"'"<<command<<"' is not a recognized internal or external command...\n"<<endl;

        accept_command();
    }


    else if(command_words[0]=="show")
    {
        if(command_words[1]=="dir")
        {
            show_directories();
        }
        else if(command_words[1]=="files")
        {
            if(command_words[2]=="")
            {
                cout<<"directory name missing...\n"<<endl;
            }
            else
            {
                show_files(command_words[2]);
            }
        }
        else
        cout<<"'"<<command<<"' is not a recognized internal or external command...\n"<<endl;

        accept_command();
    }


    else if(command_words[0]=="delete")
    {
        if(command_words[1]=="dir")
        {
            if(command_words[2]=="")
            {
                cout<<"directory name missing...\n"<<endl;
            }
            else
            {
                delete_directory(command_words[2]);
            }
        }
        else if(command_words[1]=="file")
        {
            if(command_words[2]=="")
            {
                cout<<"directory name missing...\n"<<endl;
            }
            else if(command_words[3]=="")
            {
                cout<<"file name or directory name missing...\n"<<endl;
            }
            else
            {
                delete_file(command_words[2],command_words[3]);
            }
        }
        else
        cout<<"'"<<command<<"' is not a recognized internal or external command...\n"<<endl;

        accept_command();

    }


    else if(command_words[0]=="open")
    {
        if(command_words[1]=="file")
        {
            if(command_words[2]=="" || command_words[3]=="")
                cout<<"directory name missing...\n"<<endl;
            else
            {
                int flag=check_directory(command_words[2]);
                if(flag==0)
                    cout<<"directory does not exist...\n"<<endl;
                else
                {
                int flag1=check_file(command_words[2],command_words[3]);
                if(flag1==0)
                     cout<<"file does not exist...\n"<<endl;
                else
                cout<<"file '"<<command_words[2]<<"\\"<<command_words[3]<<"' opened.\n"<<endl;
                }
            }
        }
        else
        cout<<"'"<<command<<"' is not a recognized internal or external command...\n"<<endl;

        accept_command();
    }


    else if(command_words[0]=="close")
    {
        if(command_words[1]=="file")
        {
             if(command_words[2]=="" || command_words[3]=="")
                cout<<"directory name missing...\n"<<endl;
            else
            {
                int flag=check_directory(command_words[2]);
                if(flag==0)
                    cout<<"directory does not exist...\n"<<endl;
                else
                {
                int flag1=check_file(command_words[2],command_words[3]);
                if(flag1==0)
                     cout<<"file does not exist...\n"<<endl;
                else
                cout<<"file '"<<command_words[2]<<"\\"<<command_words[3]<<"' closed.\n"<<endl;
                }
            }
        }
        else
        cout<<"'"<<command<<"' is not a recognized internal or external command...\n"<<endl;

        accept_command();
    }

    else if(command_words[0]=="clr")
    {
        if(command_words[1]=="scr"&&command_words[2]==""&&command_words[3]=="")
        {
           display();
        }
        else
        {
        cout<<"'"<<command<<"' is not a recognized internal or external command...\n"<<endl;
        accept_command();
        }
    }

    else if(command=="system exit")
    {
        main_screen1();
    }

    else if(command=="process manager")
    {
        process_manager();
    }

    else if(command=="i/o manager")
    {
        io_manager();
    }

    else if(command=="memory manager")
    {
        memory_manager();
    }
    else
    {
        cout<<"'"<<command_words[0]<<"' is not a recognized internal or external command...\n"<<endl;
        accept_command();
    }

}

//function to split the command into words
void command_words_calculate(string command, string* command_words)
{
    int i,k=0;
    char ch,ch1;
    string duplicate="";
   for(i=0;i<command.length();i++)
    {
        ch=command.at(i);
        if(ch==' ')
            continue;
        else
            break;
    }

     command=command.substr(i,command.length());

    for(i=0;i<command.length();i++)
    {
        ch=command.at(i);
        if(i!=command.length()-1)
            ch1=command.at(i+1);
        if(ch==' ')
        {
            if(i!=command.length()-1&&ch1!=' ')
            {
            k++;
            continue;
            }
            else if(i==command.length()-1)
            {
                break;
            }
            else
                continue;
        }
        else
            command_words[k]=command_words[k]+ch;
    }

}

//start screen of the file manager
void display()
{
    void accept_command();
    system("cls");
    cout<<"                                     A.B.A.M OPERATING SYSTEM [Beta Version 1.0]\n"<<endl;
    cout<<"                                  -------------------------------------------------\n"<<endl;
    cout<<"                                                    File Manager.\n"<<endl;
    cout<<"                                  -------------------------------------------------\n\n\n"<<endl;
    accept_command();
}

//function to implement memory manager of the OS
void memory_manager()
 {
     system("cls");
     cout<<"                                     A.B.A.M OPERATING SYSTEM [Beta Version 1.0]\n"<<endl;
     cout<<"                                  -------------------------------------------------\n"<<endl;
     cout<<"                                                   Memory Manager.\n"<<endl;
     cout<<"                                  -------------------------------------------------\n\n\n"<<endl;
     int totalmemory[16];
     int partitions[16];
     int i;
     int choice=0;
     int reqd;
     int reqdideal=1;
     int allocated=0;
     int lb=0,ub=0,cntr=0;
     int diff=-1;
     int j;
     int b=0;
     int a=0;
     int todelete;
     int dup;
     int k,i2;
     int cntr1=0;

      //function to implement memory manager of the OS
     for(i=0;i<16;i++)
     {
         totalmemory[i]=9;
         partitions[i]=0;
     }
     //Setting last element of array to 1. i.e. partition at the end of memory
     partitions[15]=1;
     while(choice!=4)
     {
         cntr=0;
         lb=0,ub=0;
         reqdideal=1;
         allocated=0;
         diff=-1;
         cout<<"1.Allocate memory 2.Deallocate Memory 3.Display Memory used and unused 4.Exit ";
         cin>>choice;
         switch(choice)
         {
             case 1:cout<<"Enter amount of memory needed ";
                    cin>>reqd;
                    while(reqd>reqdideal)
                    {
                        reqdideal=reqdideal*2;
                    }
                    //finding out lower and upper bounds and difference between them
                    for(i=0;i<16;i++)
                    {
                        if(partitions[i]==1)
                        {
                            lb=ub;
                            ub=i+1;
                            diff=ub-lb;
                        }
                        if(diff==reqdideal && totalmemory[lb]==9)
                        {
                            for(j=lb;j<ub;j++)
                            {
                                if(cntr<reqd)
                                {
                                    totalmemory[j]=1;
                                }
                                if(cntr>=reqd)
                                {
                                    totalmemory[j]=0;
                                }
                                cntr++;
                                allocated=1;
                            }
                        }
                        else if(diff>reqdideal && totalmemory[lb]==9)
                        {
                            while(diff!=reqdideal)
                            {
                                partitions[lb+((ub-lb-1)/2)]=1;
                                ub=(ub+lb)/2;
                                diff=ub-lb;
                            }
                            for(j=lb;j<ub;j++)
                            {
                                if(cntr<reqd)
                                    totalmemory[j]=1;
                                else
                                    totalmemory[j]=0;
                                cntr++;
                                allocated=1;
                            }
                        }
                        else
                            continue;

                        if(allocated==1)
                            break;
                    }
                      //checking if memory has been allocated
                    cout<<"Memory Index                         |";
                    for(i=0;i<16;i++)
                    {
                        cout<<i<<" ";
                    }
                    cout<<endl;
                    cout<<"Memory Occupied/Unoccupied/Unusable  |";
                    for(i=0;i<16;i++)
                    {
                        if(i>=10)
                            cout<<totalmemory[i]<<"  ";
                        else
                            cout<<totalmemory[i]<<" ";
                    }
                    cout<<endl;
                    cout<<"Memory Partitions                    |";
                    for(i=0;i<16;i++)
                    {
                        if(i>=10)
                            cout<<partitions[i]<<"  ";
                        else
                            cout<<partitions[i]<<" ";
                    }
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                    cout<<"MEMORY OCCUPIED/UNOCCUPIED/UNUSABLE TABLE KEY"<<endl;
                    cout<<"1 indicates memory index is currently occupied"<<endl;
                    cout<<"0 indicates memory index is currently unoccupied but unusable because of current partitioning"<<endl;
                    cout<<"9 indicates memory index is currently unoccupied and can be used"<<endl;
                    cout<<endl;
                    cout<<"MEMORY PARTITIONS TABLE KEY"<<endl;
                    cout<<"0 indicates no partition at that index"<<endl;
                    cout<<"1 indicates partition at that index"<<endl;
                    cout<<endl;
                    cout<<endl;

                    break;


             case 2:a=0,b=0,cntr1=0;
                    cout<<"Enter starting position to delete";
                    cin>>todelete;
                    if(totalmemory[todelete]==0 || totalmemory[todelete]==9)
                    {
                        cout<<"No process resides in this memory location"<<endl;
                        continue;
                    }
                    totalmemory[todelete]=9;
                    a++;
                    i=todelete;
                    while(partitions[i]==0)
                    {
                        i++;
                        totalmemory[i]=9;
                        a++;
                    }
                    cout<<endl;
                    while(1)
                    {
                        b=0;
                        dup=i;
                        if(partitions[i]==0)
                        {
                            i2=i;
                            for(k=i2;k<16;k++)
                            {
                                if(partitions[k]==1)
                                {
                                    i=k;
                                    break;
                                }
                            }
                        }
                        if((i+1)%(2*a)!=0)
                        {
                            for(j=i+1;j<i+1+a;j++)
                            {
                                if(totalmemory[j]==9)
                                    b++;
                            }
                            if(a==b)
                                partitions[i]=0;
                            else
                                break;
                        }
                        else
                        {
                            i=i-(2*a);
                            for(j=i+1;j<i+1+a;j++)
                            {
                                if(totalmemory[j]==9)
                                    b++;
                            }
                            if(a==b)
                                partitions[i]=0;
                            else
                                break;
                            i=dup;
                        }
                        a=a*2;
                    }
                    for(i=0;i<16;i++)
                    {
                        if(totalmemory[i]==9)
                        {
                            cntr1++;
                        }
                    }
                    if(cntr1==16)
                    {
                        partitions[7]=0;
                    }

                    cout<<"Memory Index                         |";
                    for(i=0;i<16;i++)
                    {
                        cout<<i<<" ";
                    }
                    cout<<endl;
                    cout<<"Memory Occupied/Unoccupied/Unusable  |";
                    for(i=0;i<16;i++)
                    {
                        if(i>=10)
                            cout<<totalmemory[i]<<"  ";
                        else
                            cout<<totalmemory[i]<<" ";
                    }
                    cout<<endl;
                    cout<<"Memory Partitions                    |";
                    for(i=0;i<16;i++)
                    {
                        if(i>=10)
                            cout<<partitions[i]<<"  ";
                        else
                            cout<<partitions[i]<<" ";
                    }
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                    cout<<"MEMORY OCCUPIED/UNOCCUPIED/UNUSABLE TABLE KEY"<<endl;
                    cout<<"1 indicates memory index is currently occupied"<<endl;
                    cout<<"0 indicates memory index is currently unoccupied but unusable because of current partitioning"<<endl;
                    cout<<"9 indicates memory index is currently unoccupied and can be used"<<endl;
                    cout<<endl;
                    cout<<"MEMORY PARTITIONS TABLE KEY"<<endl;
                    cout<<"0 indicates no partition at that index"<<endl;
                    cout<<"1 indicates partition at that index"<<endl;
                    cout<<endl;
                    cout<<endl;

                    break;

             case 3:cout<<"Memory Index                         |";
                    for(i=0;i<16;i++)
                    {
                        cout<<i<<" ";
                    }
                    cout<<endl;
                    cout<<"Memory Occupied/Unoccupied/Unusable  |";
                    for(i=0;i<16;i++)
                    {
                        if(i>=10)
                            cout<<totalmemory[i]<<"  ";
                        else
                            cout<<totalmemory[i]<<" ";
                    }
                    cout<<endl;
                    cout<<"Memory Partitions                    |";
                    for(i=0;i<16;i++)
                    {
                        if(i>=10)
                            cout<<partitions[i]<<"  ";
                        else
                            cout<<partitions[i]<<" ";
                    }
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                    cout<<"MEMORY OCCUPIED/UNOCCUPIED/UNUSABLE TABLE KEY"<<endl;
                    cout<<"1 indicates memory index is currently occupied"<<endl;
                    cout<<"0 indicates memory index is currently unoccupied but unusable because of current partitioning"<<endl;
                    cout<<"9 indicates memory index is currently unoccupied and can be used"<<endl;
                    cout<<endl;
                    cout<<"MEMORY PARTITIONS TABLE KEY"<<endl;
                    cout<<"0 indicates no partition at that index"<<endl;
                    cout<<"1 indicates partition at that index"<<endl;
                    cout<<endl;
                    cout<<endl;

                    break;

             case 4:break;

             default:cout<<"Wrong choice "<<endl;



         }
     }

     main_screen2();

 }

//function to implement process manager of the OS
void process_manager()
{
    system("cls");
    cout<<"                                     A.B.A.M OPERATING SYSTEM [Beta Version 1.0]\n"<<endl;
    cout<<"                                  -------------------------------------------------\n"<<endl;
    cout<<"                                                   Process Manager.\n"<<endl;
    cout<<"                                  -------------------------------------------------\n\n\n"<<endl;
    int i,j,t,n,temp1,temp2,temp3,temp4,sumburst=0;
    char c;
    float avgwt=0,avgtat=0;

    cout<<"Enter number of processes"<<endl;
    cin>>n;

    int art[n],bt[n],complete[n],wt[n],tat[n],ntat[n];
    char pname[n];
    cout<<"Enter the burst times"<<endl;
    for(i=0;i<n;i++)
    {
        cin>>bt[i];
    }
    cout<<"Enter the arrival times"<<endl;
    for(i=0;i<n;i++)
    {
        cin>>art[i];
    }

    cout<<"\n";

    for(i=0,c='A';i<n;i++,c++)
    {
        pname[i]=c;
        complete[i]=0;
        sumburst=sumburst+bt[i];
    }

    cout<<"Name "<<" Arrival Time "<<" Burst Time "<<endl;
    for(i=0;i<n;i++)
    {
        cout<<pname[i]<<"\t"<<art[i]<<"\t\t"<<bt[i]<<endl;
    }

    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(art[i]>art[j])
            {
                temp1=art[i];
                art[i]=art[j];
                art[j]=temp1;

                temp2=bt[i];
                bt[i]=bt[j];
                bt[j]=temp2;

                temp3=pname[i];
                pname[i]=pname[j];
                pname[j]=temp3;

                temp4=complete[i];
                complete[i]=complete[j];
                complete[j]=temp4;

            }
        }
    }

    cout<<"\n";
    cout<<"After sorting, the order of processes is: "<<endl;
    cout<<"Name "<<" Arrival Time "<<" Burst Time "<<endl;
    for(i=0;i<n;i++)
    {
        cout<<pname[i]<<"\t"<<art[i]<<"\t\t"<<bt[i]<<endl;
    }
    cout<<"\n";
    cout<<"By applying the Response Ratio formula: "<<endl;

    cout<< "Name " << " Arrival Time " << " Burst Time " << " Turnaround Time " << " Waiting Time " << " Normalized TAT ";

    for(t=art[0];t<sumburst;)
    {
        float hrr= -9999;
        float z;
        int next;

        for(i=0;i<n;i++)
        {
            if(art[i]<=t && complete[i]!=1)
            {
                z=(bt[i] + (t-art[i]-bt[i]))/bt[i];

                if(hrr<z)
                {
                    hrr=z;
                    next=i;
                }
            }
        }

        t=t+bt[next];
        tat[next]=t-art[next];
        wt[next]=tat[next]-bt[next];

        avgtat=avgtat+tat[next];
        ntat[next]=((float)tat[next]/bt[next]);

        complete[next]=1;
        avgwt=avgwt+wt[next];

        cout<<"\n"<<pname[next]<<"\t"<<art[next];
        cout<<"\t\t"<<bt[next]<<"\t\t"<<tat[next];
        cout<<"\t\t"<<wt[next]<<"\t\t"<<ntat[next];

    }

    cout<<"\nAverage waiting time: "<<avgwt/n<<endl;
    cout<<"Average turnaround time: "<<avgtat/n<<endl;
    main_screen2();

}

//function to implement I/O manager of the OS
void io_manager()
{

    system("cls");
    cout<<"                                     A.B.A.M OPERATING SYSTEM [Beta Version 1.0]\n"<<endl;
    cout<<"                                  -------------------------------------------------\n"<<endl;
    cout<<"                                                     I/O Manager.\n"<<endl;
    cout<<"                                  -------------------------------------------------\n\n\n"<<endl;
    int n, i, j, temp, processincomplete=0;
    cout<<"Enter the number of I/O instructions to be completed"<<endl;
    cin>>n;
    int deadline[n];
    cout<<"Enter the deadlines(in seconds) of each I/O instruction "<<endl;
    int complete[n];
    for(i=0; i<n; i++)
    {
        complete[i]=0;
    }
    for(i=0; i<n; i++)
    {
        cin>>deadline[i];
    }

    //Sorting the processes in increasing order of their deadlines
    for(i=0; i<n; i++)
    {
        for(j=0; j<n-1; j++)
        {
            if(deadline[j]>deadline[j+1])
            {
                temp= deadline[j];
                deadline[j]=deadline[j+1];
                deadline[j+1]=temp;
            }
        }
    }

    cout<<"Instructions are sorted according to their deadlines and are as follows:"<<endl;
    for(i=0; i<n; i++)
    {
        cout<<"P"<<i+1<<": "<<deadline[i]<<endl;
    }

    //Creating a duplicate of deadline[] array
    int deadlinecopy[n];
    for(i=0; i<n; i++)
    {
        deadlinecopy[i]=deadline[i];
    }

    cout<<"Enter the time period for each instruction"<<endl;
    int period[n];
    for(i=0; i<n; i++)
    {
        cin>>period[i];
    }

    system("cls");

    cout<<"Enter the burst times of each instruction(in seconds)"<<endl;
    int burst[n];
    for(i=0; i<n; i++)
    {
        cin>>burst[i];
    }

    system("cls");

    cout<<"Instructions along with their deadlines and their burst times are:\n"<<endl;
    for(i=0; i<n; i++)
    {
       cout<<"P"<<i+1<<"     Deadline: "<<deadline[i]<<"    Burst time: "<<burst[i]<<endl;
    }

    cout<<"\n Press e to begin the I/O scheduling algorithm"<<endl;
    char begin;
    cin>>begin;

    if(begin=='e')
        system("cls");

    int count=0; //Used later to check if all instructions have been completed

    i=0;
    while(1)
    {
            //Finding out the instruction which is closest to its deadline
            int min = 1000;
            for(j=0; j<n; j++)
            {
                if(deadline[j]<min)
                    min=j;
            }


            //Letting instruction run for its allotted time period
            if((burst[min]-period[min])>=0)
            {
                burst[min]=burst[min]-period[min];
                for(j=0; j<n; j++)
                {
                    deadline[j]=deadline[j]-period[min];
                }
            }
            else
            {
                for(j=0; j<n; j++)
                {
                    deadline[j]=deadline[j]-burst[min];
                }
                burst[min]=0;
            }

            //Checking if any deadline have passed without the respective instruction being completed
            for(j=0; j<n; j++)
            {
                if(deadline[j]<=0 && burst[j]>>0)
                {
                    processincomplete=1;
                }
            }

            //Checking if the current instructions has been completed before its deadline has passed
            if(burst[min]==0 && deadline[min]>>0)
            {
                complete[min]=1;
            }
            if(processincomplete==1)
                break;

            //Checking if all instructions have been completed
            for(j=0; j<n; j++)
            {
                if(complete[j]==1)
                    count=count+1;
            }
            if(count==n)
                break;
        i++;
    }


    for(j=0; j<=10; j++)
    {
        system("cls");
          cout<<"LOADING..."<<(j*10)<<"%";
    }


    if(processincomplete==1)
        cout<<"\nDeadline scheduler failed to complete as process "<<i<<" failed to meet its deadline"<<endl;
    else
        cout<<"\nAll instructions were successfully executed"<<endl;

    main_screen2();

}

//command screen of the OS
void main_screen2()
{
   string command="";  // local variable
   cout<<"\nroot\\:>";
   fflush(stdin);
   getline(cin,command);
   if(command=="i/o manager")
     io_manager();
   else if(command=="memory manager")
     memory_manager();
   else if(command=="file manager")
     display();
   else if(command=="process manager")
     process_manager();
   else if(command=="system exit")
     main_screen1();
   else
   {
    cout<<"'"<<command<<"' is not a recognized internal or external command..."<<endl;
    main_screen2();
   }

}

//Boot screen of the OS
void main_screen1()
{
    system("cls");
     void display();
     for(int i=1;i<=50;i++)
      {
          system("cls");
          cout<<"\n\n\t\t\t\t\t\t      Loading\n\t\t\t\t  ";
          for(int j=1;j<=i;j++)
          {
              cout<<"�";
          }
          cout<<"\n\n\t\t\t\t\t          "<<2*i<<"%";

      }
      cout<<"  Complete.\n\n"<<endl;

    cout<<"                                     A.B.A.M OPERATING SYSTEM [Beta Version 1.0]\n"<<endl;
    cout<<"                                  -------------------------------------------------\n"<<endl;
    cout<<"                                       @  A.S.A.R 2020(c). All Rights Reserved.\n"<<endl;
    cout<<"                                  -------------------------------------------------\n\n\n"<<endl;
    main_screen2();

}

//main function
 int main()
{
    main_screen1();
    return 0;
}





