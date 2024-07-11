#include <iostream>
#include <cstring>

using namespace std;

class Delo {
private:
    char ime[51];
    int godina;
    char zemja[51];

public:
    Delo(const char* ime, int godina, const char* zemja) {
        strncpy(this->ime, ime, 50);
        this->ime[50] = '\0';
        this->godina = godina;
        strncpy(this->zemja, zemja, 50);
        this->zemja[50] = '\0';
    }

    bool operator==(const Delo& d) const {
        return strcmp(this->ime, d.ime) == 0;
    }

    const char* getIme() const {
        return ime;
    }

    int getGodina() const {
        return godina;
    }

    const char* getZemja() const {
        return zemja;
    }
};

class Pretstava {
protected:
    Delo delo;
    int br_karti;
    char data[16];

public:
    Pretstava(const Delo& delo, int br_karti, const char* data) : delo(delo) {
        this->br_karti = br_karti;
        strncpy(this->data, data, 15);
        this->data[15] = '\0';
    }

    virtual ~Pretstava() {}

    virtual float cena() {
        int M = 0, N = 0;
        int year=delo.getGodina();
        if(year>=1901)
        {
            M=50;
        }else if(year>1801&&year<=1900)
        {
            M=75;
        }else{
            M=100;
        }

        if (strcmp(delo.getZemja(), "Italija") == 0) {
            N = 100;
        }
        else if (strcmp(delo.getZemja(), "Rusija") == 0) {
            N = 150;
        }
        else {
            N = 80;
        }

        return N + M;
    }


    int getBrKarti() const {
        return br_karti;
    }

    const char* getData() const {
        return data;
    }

    const Delo &getDelo() const {
        return delo;
    }
};

class Opera : public Pretstava {
public:
    Opera(const Delo& delo, int br_karti, const char* data)
            : Pretstava(delo, br_karti, data) {}
};

class Balet : public Pretstava {
private:
    static int cena_balet;

public:
    Balet(const Delo& delo, int br_karti, const char* data)
            : Pretstava(delo, br_karti, data) {}

    float cena() {
        return Pretstava::cena() + cena_balet;
    }

    static void setCenaBalet(int cenaBalet) {
        cena_balet = cenaBalet;
    }
};

int Balet::cena_balet = 150;

float prihod(Pretstava** pretstavi, int n) {
    float suma = 0;
    for (int i = 0; i < n; i++) {
        suma += pretstavi[i]->cena() * pretstavi[i]->getBrKarti();
    }
    return suma;
}

int brojPretstaviNaDelo(Pretstava** pretstavi, int n, const Delo& d) {
    int brojPretstavi = 0;
    for (int i = 0; i < n; i++) {
        if (pretstavi[i]->getDelo() == d) {
            brojPretstavi++;
        }
    }
    return brojPretstavi;
}

Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}