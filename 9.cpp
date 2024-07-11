#include <iostream>
#include <cstring>

using namespace std;

class Exception
{
private:
    char *msg;
public:
    Exception (char *msg)
    {
        this->msg = new char[strlen(msg)+1];
        strcpy(this->msg,msg);
    }

    void message(){
        cout<<msg<<endl;
    }

    ~Exception()
    {
        delete []msg;
    }
};
class Trud
{
private:
    char tip;//J , C
    int god;
public:
    Trud(){}
    Trud(char tip,int god)
    {
        this->tip = tip;
        this->god = god;
    }
    char getTip()
    {
        return tip;
    }
    int getGodina()
    {
        return god;
    }

    friend istream& operator>>(istream &in, Trud &t)
    {
        in>>t.tip>>t.god;
        return in;
    }
    ~Trud(){}
};

class Student
{
protected:
    char ime[30];
    int index;
    int god_upis;
    int oceni[50];
    int n;
public:
    Student(){}
    Student(char *ime,int index,int god_upis,int *oceni,int n)
    {
        strcpy(this->ime,ime);
        this->index = index;
        this->god_upis = god_upis;
        this->n = n;
        for(int i=0;i<n;i++)
        {
            this->oceni[i] = oceni[i];
        }
    }
    virtual float rang()
    {
        int suma=0;
        for(int i=0;i<n;i++)
        {
            suma+=oceni[i];
        }
        return (float)suma/n;
    }
    int getIndex()
    {
        return index;
    }

    friend ostream& operator<<(ostream &out, Student &s)
    {
        out<<s.index<<" "<<s.ime<<" "<<s.god_upis<<" "<<s.rang()<<endl;
        return out;
    }

    virtual ~Student(){}
};

class PhDStudent : public Student
{
private:
    Trud *trudovi;
    int brT;
    static int bodoviJ;
    static int bodoviC;
public:
    PhDStudent() : Student()
    {
        this->brT = 0;
        trudovi = new Trud[0];
    }

    PhDStudent(char *ime,int index,int god_upis,int *oceni,int n,Trud *trudovi, int brT) : Student(ime, index,god_upis,oceni,n)
    {
        this->brT = brT;
        this->trudovi = new Trud[brT];
        for(int i=0;i<brT;i++)
        {
            this->trudovi[i] = trudovi[i];
        }
    }
    PhDStudent(const PhDStudent &phd) : Student(phd)
    {
        this->brT = phd.brT;
        this->trudovi = new Trud[brT];
        for(int i=0;i<brT;i++)
        {
            this->trudovi[i] = phd.trudovi[i];
        }
    }
    PhDStudent& operator=(const PhDStudent &phd)
    {
        if(this!=&phd)
        {
            delete []trudovi;
            strcpy(this->ime, phd.ime);
            this->index = phd.index;
            this->god_upis = phd.god_upis;
            this->n = phd.n;
            for(int i=0;i<phd.n;i++)
            {
                this->oceni[i] = phd.oceni[i];
            }
            this->brT = phd.brT;
            this->trudovi = new Trud[brT];
            for(int i=0;i<brT;i++)
            {
                this->trudovi[i] = phd.trudovi[i];
            }
        }
        return *this;
    }
    float rang()
    {
        int bodovi=0;
        float osnoven = Student::rang();
        for(int i=0;i<brT;i++)
        {
            if(trudovi[i].getTip()=='J' || trudovi[i].getTip()=='j')
                bodovi+=bodoviJ;
            else if(trudovi[i].getTip()=='C' || trudovi[i].getTip()=='c')
                bodovi+=bodoviC;
        }
        return osnoven + bodovi;
    }

    static void setBodoviJ(int j)
    {
        bodoviJ = j;
    }
    static void setBodoviC(int c)
    {
        bodoviC = c;
    }

    PhDStudent& operator+=( Trud &nov)
    {
        if(nov.getGodina() < god_upis)
        {
            throw Exception("Ne moze da se vnese dadeniot trud");
        }

        Trud *temp = new Trud[brT + 1];
        for(int i=0;i<brT;i++)
        {
            temp[i] = trudovi[i];
        }
        temp[brT] = nov;
        delete []trudovi;
        trudovi = temp;
        brT++;
        return *this;
    }
    ~PhDStudent()
    {
        delete []trudovi;
    }
};
int PhDStudent::bodoviC = 1;
int PhDStudent::bodoviJ = 3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;
        bool najde=false;
        for(int i=0;i<m;i++)
        {
            if(niza[i]->getIndex()==indeks)
            {

                PhDStudent *p = dynamic_cast<PhDStudent*> (niza[i]);
                if(p!=0)
                {
                    najde=true;
                    try
                    {
                        *p+=t;
                    }
                    catch(Exception &e)
                    {
                        e.message();
                    }
                }
            }
        }
        if(najde==false)
        {
            cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks

        Trud t;
        cin >> indeks;
        cin >> t;
        for(int i=0;i<m;i++)
        {
            if(niza[i]->getIndex()==indeks)
            {
                PhDStudent *p = dynamic_cast<PhDStudent*> (niza[i]);
                if(p!=0)
                {
                    try
                    {
                        *p+=t;
                    }
                    catch(Exception &e)
                    {
                        e.message();
                    }
                }
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            try
            {
                if(god_tr<god)
                    throw Exception ("Ne moze da se vnese dadeniot trud");
                Trud t(tip, god_tr);
                trud[j] = t;
            }
            catch(Exception &e)
            {
                e.message();
            }

        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;



        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

        for(int i=0;i<m;i++)
        {
            if(niza[i]->getIndex()==indeks)
            {
                PhDStudent *p = dynamic_cast<PhDStudent*> (niza[i]);
                if(p!=0)
                {
                    try
                    {
                        *p+=t;
                    }
                    catch(Exception &e)
                    {
                        e.message();
                    }
                }
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        PhDStudent::setBodoviJ(journal);
        PhDStudent::setBodoviC(conf);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}