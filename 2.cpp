#include <iostream>
#include <cstring>
using namespace std;
class Vozac{
protected:
    char ime[100];
    int vozrast;
    int brTrki;
    bool daliVeteran;
public:
    Vozac(){}
    Vozac(char *ime, int vozrast, int brTrki,bool daliVeteran){
        ::strcpy(this->ime,ime);
        this->vozrast=vozrast;
        this->brTrki=brTrki;
        this->daliVeteran=daliVeteran;
    }
    virtual float zarabotuvacka(){return 0;}
    virtual float danok(){
        return 0;
    }
    friend ostream &operator<<(ostream &os,Vozac &v){
        os<<v.ime<<endl;
        os<<v.vozrast<<endl;
        os<<v.brTrki<<endl;
        if(v.daliVeteran){
            os<<"VETERAN"<<endl;
        }
        return os;
    }
    bool operator==(Vozac &v){
        return this->zarabotuvacka()==v.zarabotuvacka();
    }
    virtual ~Vozac(){}
};
class Avtomobilist:public Vozac{
private:
    float cena;
public:
    Avtomobilist(): Vozac(){}
    Avtomobilist(char *ime, int vozrast, int brTrki,bool daliVeteran,
                 float cena ): Vozac(ime,vozrast,brTrki,daliVeteran){
        this->cena=cena;
    }
    float zarabotuvacka(){
        return cena/5;
    }
    float danok(){
        if(brTrki>10){
            return 15*zarabotuvacka()/100.0;
        }
        return 10*zarabotuvacka()/100.0;
    }
};
class Motociklist:public Vozac{
private:
    int mokjnost;
public:
    Motociklist(): Vozac(){}
    Motociklist(char *ime, int vozrast, int brTrki,bool daliVeteran,
                int mokjnost ): Vozac(ime,vozrast,brTrki,daliVeteran){
        this->mokjnost=mokjnost;
    }
    float zarabotuvacka(){
        return mokjnost*20;
    }
    float danok(){
        if(daliVeteran){
            return 25*zarabotuvacka()/100.0;
        }
        return 20*zarabotuvacka()/100.0;
    }
};
float soIstaZarabotuvachka(Vozac **v, int n, Vozac *vx){
    int br=0;
    for (int i=0;i<n;i++){
        if(*v[i]==*vx){
            br++;
        }
    }
    return br;
}
int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}