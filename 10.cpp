#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;
class NegativnaVrednost{
private:
    char *msg;
public:
    NegativnaVrednost(char *msg){
        this->msg=new char[strlen(msg)+1];
        strcpy(this->msg,msg);
    }
    void message(){
        cout<<msg<<endl;
    }
    ~NegativnaVrednost(){
        delete []msg;
    }
};
class Oglas{
private:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float evra;
public:
    Oglas(){}
    Oglas(char *naslov,char *kategorija, char *opis,float evra){
        strcpy(this->naslov,naslov);
        strcpy(this->kategorija,kategorija);
        strcpy(this->opis,opis);
        this->evra=evra;
    }
    bool operator >(Oglas &o){
        return this->evra>o.evra;
    }
    friend ostream &operator<<(ostream &os, Oglas &o){
        os<<o.naslov<<endl;
        os<<o.opis<<endl;
        os<<o.evra<<" evra"<<endl;
        return os;
    }

    float getEvra() const {
        return evra;
    }

    const char *getKategorija() {
        return kategorija;
    }
};
class Oglasnik{
private:
    char podatoci[20];
    Oglas *o;
    int n;
public:
    Oglasnik(){
        n=0;
        o=new Oglas[0];
    }
    Oglasnik(char *podatoci){
        strcpy(this->podatoci,podatoci);
        n=0;
        o=new Oglas[0];
    }
    Oglasnik(Oglasnik &og){
        strcpy(this->podatoci,og.podatoci);
        this->n=og.n;
        this->o=new Oglas[og.n];
        for(int i=0;i<n;i++){
            this->o[i]=og.o[i];
        }
    }

    Oglasnik &operator=(Oglasnik &og){
        if(this!=&og) {
            delete []o;
            strcpy(this->podatoci, og.podatoci);
            this->n = og.n;
            this->o = new Oglas[og.n];
            for (int i = 0; i < n; i++) {
                this->o[i] = og.o[i];
            }
        }
        return *this;
    }
    Oglasnik &operator+=(Oglas &nov){
        if(nov.getEvra()<0){
            throw NegativnaVrednost("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!");
        }
        Oglas *temp= new Oglas [n+1];
        for (int i=0;i<n;i++){
            temp[i]=o[i];
        }
        temp[n]=nov;
        delete []o;
        n++;
        o=temp;
        return *this;
    }
    ~Oglasnik(){
        delete []o;
    }
    friend ostream &operator<<(ostream &os, Oglasnik &og){
        os<<og.podatoci<<endl;
        for (int i=0;i<og.n;i++){
            os<<og.o[i]<<endl;
        }
        return os;
    }
    void oglasOdKategorija(char *k){
        for(int i=0;i<n;i++){
            if(strcmp(o[i].getKategorija(),k)==0){
                cout<<o[i]<<endl;
            }
        }
    }
    void najniskaCena(){
        int min=1000;
        int index=0;
        for (int i=0;i<n;i++){
            if(o[i].getEvra()<min){
                min=o[i].getEvra();
                index=i;
            }
        }
        cout<<o[index];
    }

};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }
            catch (NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);

            try{
                ogl+=o;
            }
            catch (NegativnaVrednost &n){
                n.message();
            }
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);

            try{
                ogl+=o;
            }
            catch (NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);

            try{
                ogl+=o;
            }
            catch (NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);

            try{
                ogl+=o;
            }
            catch (NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
