#include<iostream>
#include<string.h>
#include <cctype>

using namespace std;


class BadInputException
{
private:
    char *msg;
public:
    BadInputException(char *msg)
    {
        this->msg = new char[strlen(msg)+1];
        strcpy(this->msg, msg);
    }
    void message()
    {
        cout<<msg<<endl;
    }
    ~BadInputException()
    {
        delete []msg;
    }
};
class StudentKurs
{
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
    static int MAX;
    const static int MINOCENKA;
public:
    StudentKurs(char* ime,int finalenIspit)
    {
        strcpy(this->ime,ime);
        this->ocenka=finalenIspit;
        this->daliUsno=false;
    }
    StudentKurs(){}
    static int setMAX(int m)
    {
        MAX = m;
    }
    friend ostream &operator<<(ostream& out,StudentKurs &s)
    {
        out<<s.ime<<" --- "<<s.ocena()<<endl;
        return out;
    }
    bool getDaliUsno()
    {
        return daliUsno;
    }
    virtual int ocena()
    {
        return ocenka;
    }
    char* getIme()
    {
        return ime;
    }
    const static int getMINOCENKA()
    {
        return MINOCENKA;
    }
    virtual ~StudentKurs(){}
};
int StudentKurs::MAX = 10;
const int StudentKurs::MINOCENKA = 6;

class StudentKursUsno : public StudentKurs
{
private:
    char *opisna;
public:
    StudentKursUsno(): StudentKurs()
    {
        this->opisna = new char[0];
        daliUsno = true;
    }
    StudentKursUsno(char* ime,int finalenIspit): StudentKurs(ime,finalenIspit)
    {
        this->opisna = new char[0];
        daliUsno=true;
    }
    StudentKursUsno(const StudentKursUsno &sku) : StudentKurs(sku)
    {
        this->opisna = new char [strlen(sku.opisna)+1];
        strcpy(this->opisna,sku.opisna);
    }
    StudentKursUsno& operator=(const StudentKursUsno &sku)
    {
        if(this!=&sku)
        {
            delete []opisna;
            strcpy(this->ime,sku.ime);
            this->daliUsno = sku.daliUsno;
            this->ocenka = sku.ocenka;
            this->opisna = new char [strlen(sku.opisna)+1];
            strcpy(this->opisna,sku.opisna);
        }
        return *this;
    }
    int ocena()
    {
        int osnovna = StudentKurs::ocena();
        if(strcmp(opisna,"odlicen")==0)
        {
            if(osnovna + 2<=MAX)
                return osnovna + 2;
            else if(osnovna + 1<=MAX)
                return osnovna + 1;
        }
        if(strcmp(opisna,"dobro")==0)
        {
            if(osnovna + 1<=MAX)
                return osnovna + 1;
        }
        if(strcmp(opisna,"losho")==0)
        {
            if(osnovna>1)
                return osnovna-1;
        }
        return osnovna;
    }
    StudentKursUsno& operator+=(char *nova)
    {
        for(int i=0;i<strlen(nova);i++)
        {
            if(!isalpha(nova[i]))
            {
                throw BadInputException("Greshna opisna ocenka");
            }
        }
        delete[]opisna;
        this->opisna = new char[strlen(nova)+1];
        strcpy(this->opisna,nova);
        return *this;
    }
    ~StudentKursUsno()
    {
        delete []opisna;
    }
};


class KursFakultet
{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj )
    {
        strcpy(this->naziv,naziv);
        for (int i=0; i<broj; i++)
        {
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno())
            {
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet()
    {
        for (int i=0; i<broj; i++) delete studenti[i];
    }

    void pecatiStudenti()
    {
        cout<<"Kursot "<<naziv<<" go polozile:"<<endl;
        for(int i=0;i<broj;i++)
        {
            if(studenti[i]->ocena()>=StudentKurs::getMINOCENKA())
            {
                cout<<*studenti[i];
            }
        }
    }
    void postaviOpisnaOcenka(char *ime,char *opisna)
    {
        for(int i=0;i<broj;i++)
        {
            if(strcmp(studenti[i]->getIme(),ime)==0)
            {
                StudentKursUsno * sku = dynamic_cast<StudentKursUsno*>(studenti[i]);
                if(sku!=0)
                {
                    *sku+=opisna;
                    break;
                }
            }
        }
    }


};

int main()
{

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0; i<n; i++)
    {
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0; i<n; i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0; i<m; i++)
    {
        cin>>ime>>opisna;
        try
        {
            programiranje.postaviOpisnaOcenka(ime,opisna);
        }
        catch(BadInputException &b)
        {
            b.message();
            char nova[30];
            int j=0;
            for(int i=0;i<strlen(opisna);i++)
            {
                if(isalpha(opisna[i]))
                {
                    nova[j] = opisna[i];
                    j++;
                }
            }
            programiranje.postaviOpisnaOcenka(ime,nova);
        }

    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
