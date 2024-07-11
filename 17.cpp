#include <iostream>
#include <cstring>
using namespace std;
class FudbalskaEkipa{
protected:
    char trener[100];
    int golovi[10];
public:
    FudbalskaEkipa(){}
    FudbalskaEkipa(char *trener, int *golovi){
        ::strcpy(this->trener,trener);
        for(int i=0;i<10;i++){
            this->golovi[i]=golovi[i];
        }
    }
    virtual char* Ime()=0;

    virtual void print(){
        cout<<trener<<endl;
        cout<< uspeh() << endl;
    }
    friend ostream& operator<<(ostream& os, FudbalskaEkipa& f) {
        f.print();
        return os;
    }
    bool operator>(FudbalskaEkipa &f){
        return this->uspeh()>f.uspeh();
    }
    virtual float uspeh()=0;
    FudbalskaEkipa& operator+=(int nova)
    {
        for(int x = 0;x<10;x++)
        {
            golovi[x] = golovi[x+1];
        }
        golovi[9] = nova;
        return *this;
    }
    ~FudbalskaEkipa(){}
};
class Klub:public FudbalskaEkipa{
private:
    char ime[100];
    int br_tituli;
public:
    Klub(){}
    Klub(char *trener, int *golovi,char *ime,int br_tituli):
            FudbalskaEkipa(trener,golovi)
    {
        strcpy(this->ime,ime);
        this->br_tituli=br_tituli;
    }
    void print(){
        cout<<ime<<endl;
        FudbalskaEkipa::print();
    }

    char *Ime(){
        return ime;
    }

    float uspeh(){
        float suma=0;
        for(int i=0;i<10;i++){
            suma+=golovi[i];
        }
        return suma*3+br_tituli*1000;
    }

};
class Reprezentacija:public FudbalskaEkipa{
private:
    char drzava[100];
    int vk_megjunarodni;
public:
    Reprezentacija():FudbalskaEkipa(){}
    Reprezentacija(char *trener, int *golovi,char *drzava, int vk_megjunarodni)
            :FudbalskaEkipa(trener, golovi){
        strcpy(this->drzava,drzava);
        this->vk_megjunarodni=vk_megjunarodni;
    }

    void print(){
        cout<<drzava<<endl;
        FudbalskaEkipa::print();
    }
    float uspeh(){
        float suma=0;
        for(int i=0;i<10;i++){
            suma+=golovi[i];
        }
        return suma*3+vk_megjunarodni*50;
    }
    char *Ime(){
        return drzava;
    }
};
void najdobarTrener(FudbalskaEkipa **ekipi, int n){
    FudbalskaEkipa *max = ekipi[0];
    for (int i=0;i<n;i++){
        if(ekipi[i]->uspeh()>max->uspeh()){
            max=ekipi[i];

        }
    }
    cout<<*max;
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}