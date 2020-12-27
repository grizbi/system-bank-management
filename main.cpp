#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;


void introduction()
{
    std::cout<<"\n\nBANK";
    std::cout<<"\n\nSYSTEM";
    std::cout<<"\n\nMANAGEMENT";
    std::cout<<"\n\nCREATED BY JAKUB KOS\n";
}

class Bank
{

int acc_number;
char name[15];
int balance;

public:
    Bank ()
:
    balance(0)
{

}
    int retacno();
    void create_account();
    void show_account();
    void manage_balance();
    void deposit(int);
    void withdraw(int);
    void report();


};

void Bank::create_account()
{
    std::cout<<"\nWitamy, prosze podac imie:"<<std::endl;
    std::cin>>name;
    std::cout<<std::endl;
    std::cout<<"\nProsze podac numer konta"<<std::endl;
    std::cin>>acc_number;
    cout<<"\nKonto zostalo utworzone";
}

void Bank::show_account()
{
    std::cout<<"Numer konta : "<<acc_number<<std::endl;
    std::cout<<"\Imie posiadacza konta : "<<name;
    std::cout<<"\nStan konta : "<<balance;
}

void Bank::deposit(int x)
{
    balance+=x;

}

int Bank::retacno()
{
    return acc_number;
}

void Bank::withdraw(int x)
{
    balance-=x;
}

void Bank::report()
{
    cout<<"\nImie posiadacza konta:"<<name<<"\tNumer konta:"<<acc_number<<"\tStan konta:"<<balance;
}

void write_account()
{

    Bank ac;
    ofstream file;
    file.open("account.dat",ios::binary | std::ios::app);
    ac.create_account();
    file.write(reinterpret_cast<char*> (&ac),sizeof(Bank));
    file.close();
}


void deposit_withdraw(int,int);
void display_balance(int);
void show_accounts();
void delete_account(int);




int main()
{
    introduction();

    int option;
    int num;
    do
    {
        cout<<"\n\nMenu Glowne";
        cout<<"\n\n1.Stworz konto";
        cout<<"\n\n2.Wplac pieniadze na konto";
        cout<<"\n\n3.Wyplac gotowke";
        cout<<"\n\n4.Stan konta";
        cout<<"\n\n5.Wszystkie konta w naszym banku";
        cout<<"\n\n6.Zamknij konto na dobre";
        cout<<"\n\n7.Wyjdz";

        cout<<"\n\nWybierz interesujaca cie opcje:";
        cin>>option;

        if((option<1)||(option>7))
            exit(1);


        system("cls");

        switch(option)
        {
            case 1:
                write_account();
                break;
            case 2:
                cout<<"Wprowadz numer konta:"; cin>>num;
                deposit_withdraw(num,1);
                break;
            case 3:
                cout<<"Wprowadz numer konta:"; cin>>num;
                deposit_withdraw(num,2);
            case 4:
                cout<<"Wprowadz numer konta:"; cin>>num;
                display_balance(num);
                break;
            case 5:
                show_accounts();
                break;
            case 6: cout<<"Wprowadz numer konta konta ktorego chcesz usunac:"; cin>>num;
                delete_account(num);
                break;
            case 7:
                exit(1);
        }
        cin.ignore();
        cin.get();


    }while(option!=7);

    return 0;
}


//function to withdraw money and deposit
void deposit_withdraw(int n, int option)
{
    int amt;
   bool found = false;
   Bank ac;
   fstream file;
   file.open("account.dat", ios::binary | ios::in | ios::out);
   if(!file.is_open())
   {
       cout<<"Nie moglem otworzyc pliku, nacisnij dowolny przycisk";
       return;
   }
   while(!file.eof() && found == false)
   {
       file.read(reinterpret_cast <char*> (&ac),sizeof(Bank));
       if(ac.retacno()==n)
       {
           ac.show_account();
           if(option==1)
           {
               cout<<"\n\nTo deposit money enter the amount you want to deposit:";
               cin>>amt;
               ac.deposit(amt);
           }
           else if(option==2)
           {
               cout<<"\n\nTo withdraw your money enter the amount you want to withdraw:";
               cin>>amt;
               ac.withdraw(amt);

           }



       int pos=(-1)*static_cast <int> (sizeof(ac));
       file.seekp(pos,ios::cur);
       file.write(reinterpret_cast <char*> (&ac),sizeof(Bank));
       cout<<"Record has been updated";
       found = true;
       }

   }
   file.close();
   if(found==false)
        cout<<"\n\nNie znaleziono uzytkownika o takim numerze";

}

    void display_balance(int n)
    {
        bool flag = false;
        ifstream file;
        Bank ac;
        file.open("account.dat", ios::binary);
        if(!file)
        {
            cout<<"\nNie udalo sie sprawdzi balansu konta";
            return;
        }
        while(file.read(reinterpret_cast <char*> (&ac),sizeof(Bank)));
        {
            if(ac.retacno()==n)
            {
                ac.show_account();
                flag = true;
            }


        }
        file.close();
        if(flag==false)
            cout<<"\nNie udalo sie znalezc uzytkownika o danym numerze";
    }

    void show_accounts()
    {
        ifstream file;
        file.open("account.dat",ios::binary);
        Bank ac;
        if(!file)
        {
            cout<<"Nie udalo mi sprawdzic aktywnych kont";
            return;
        }
        while(file.read(reinterpret_cast<char *> (&ac),sizeof(Bank)))
        {
            ac.report();
        }
        file.close();

    }

    void delete_account(int n)
    {
        ofstream temp;
        ifstream file;
        Bank ac;
        file.open("account.dat",ios::binary);
        if(!file)
        {
            cout<<"Nie udalo mi sie usunac nic, przepraszamy za klopoty";
            return;
        }
        temp.open("temp.dat",ios::binary);
        while(file.read(reinterpret_cast<char *> (&ac),sizeof(Bank)))
        {

            if(ac.retacno()!=n)
                temp.write(reinterpret_cast <char*> (&ac),sizeof(Bank));
        }
        file.close();
        temp.close();
        remove("account.dat");
        rename("temp.dat","account.dat");
        cout<<"\nKonto zostalo usuniete";

    }

