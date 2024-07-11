#include <iostream>
#include <cstring>

using namespace std;
class InvalidProductionDate{
private:
    char *msg;
public:
    InvalidProductionDate(char *msg){
        this->msg=new char[strlen(msg)+1];
        ::strcpy(this->msg,msg);
    }
    void message(){
        cout<<msg<<endl;
    }
    ~InvalidProductionDate(){
        delete []msg;
    }
};
enum tip{smartfon,kompjuter};
class Device{
protected:
    char model[100];
    tip Tip;
    static float casovi;
    int godina;
public:
    Device(){}
    Device(char *model, tip Tip,int godina){
        ::strcpy(this->model,model);
        this->Tip=Tip;
        this->godina=godina;

    }
    friend ostream& operator<<(ostream &out,const Device &d)
    {
        float dopCasovi=0;
        out<<d.model<<endl;
        if(d.Tip==kompjuter)
        {
            out<<"Laptop ";
            dopCasovi+=2;

        }
        else if(d.Tip==smartfon)
        {
            out<<"Mobilen ";
        }
        if(d.godina>2015)
        {
            dopCasovi+=d.casovi+2;
        }
        else dopCasovi+=d.casovi;
        out<<dopCasovi<<endl;
        return out;
    }

    static void setPocetniCasovi(float casovi) {
        Device::casovi = casovi;
    }

    int getGodina() const {
        return godina;
    }
};
class MobileServis{
private:
    char adresa[100];
    Device *d;
    int n;
public:
    MobileServis(){
        n=0;
        d= new Device[0];
    }
    MobileServis(char *adresa){
        strcpy(this->adresa,adresa);
        n=0;
        d= new Device[0];
    }
    MobileServis(MobileServis &m){
        strcpy(this->adresa,m.adresa);
        this->n=m.n;
        this->d= new Device[m.n];
        for (int i=0;i<m.n;i++){
            this->d[i]=m.d[i];
        }
    }

    MobileServis&operator=(MobileServis &m){
        if(this!=&m) {
            delete []d;
            strcpy(this->adresa, m.adresa);
            this->n = m.n;
            this->d = new Device[m.n];
            for (int i = 0; i < m.n; i++) {
                this->d[i] = m.d[i];
            }
        }
        return  *this;
    }
    MobileServis &operator+=(Device &nov){
        if(nov.getGodina()>2019||nov.getGodina()<2000){
            throw InvalidProductionDate("Невалидна година на производство");
        }
        Device *temp= new Device[n+1];
        for (int i=0;i<n;i++){
            temp[i]=d[i];
        }
        temp[n]=nov;
        n++;
        delete []d;
        d=temp;
        return *this;
    }
    void pecatiCasovi(){
        cout<<"Ime: "<<adresa<<endl;
        for(int i=0;i<n;i++){
            cout<<d[i];
        }
    }
};
float Device::casovi=1;
int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &i){
                i.message();
            }

        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &i){
                i.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &i){
                i.message();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &i){
                i.message();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &i){
                i.message();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

