#include<iostream>
#include<string.h>
using namespace std;

class OutOfBoundException {
private:
    char *msg;

public:
    OutOfBoundException(char *msg) {
        this->msg = new char[strlen(msg) + 1];
        strcpy(this->msg, msg);
    }

    void message() {
        cout << msg << endl;
    }

    ~OutOfBoundException() {
        delete[] msg;
    }
};

class Karticka {
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
    const static int max_p;

public:
    Karticka() {}

    Karticka(char* smetka, int pin) {
        strcpy(this->smetka, smetka);
        this->pin = pin;
        this->povekjePin = false;
    }

    const char* getSmetka() const {
        return smetka;
    }

    int getPin() const {
        return pin;
    }

    bool getDopolnitelenPin() {
        return povekjePin;
    }

    void setPin(int pin) {
        Karticka::pin = pin;
    }

    bool isPovekjePin() const {
        return povekjePin;
    }

    void setPovekjePin(bool povekjePin) {
        Karticka::povekjePin = povekjePin;
    }

    friend ostream& operator<<(ostream& os, Karticka& k) {
        os << k.smetka << ": " << k.tezinaProbivanje();
        return os;
    }

    virtual int tezinaProbivanje() {
        int temp = pin;
        int br = 0;
        while (temp) {
            temp /= 10;
            br++;
        }
        return br;
    }

    virtual ~Karticka() {}
};

class SpecijalnaKarticka : public Karticka {
private:
    int* dopolnitelni_kodovi;
    int n;


public:
    SpecijalnaKarticka() : Karticka() {
        n = 0;
        dopolnitelni_kodovi = new int[0];
    }

    SpecijalnaKarticka(char* smetka, int pin) : Karticka(smetka, pin) {
        n = 0;
        dopolnitelni_kodovi = new int[0];
        povekjePin=true;    }

    SpecijalnaKarticka(SpecijalnaKarticka& sk) : Karticka(sk) {
        this->n = sk.n;
        povekjePin=true;
        this->dopolnitelni_kodovi = new int[sk.n];
        for (int i = 0; i < n; i++) {
            this->dopolnitelni_kodovi[i] = sk.dopolnitelni_kodovi[i];
        }
    }

    SpecijalnaKarticka& operator=(SpecijalnaKarticka& sk) {
        if (this != &sk) {
            delete[] dopolnitelni_kodovi;
            Karticka::operator=(sk);
            this->n = sk.n;
            this->dopolnitelni_kodovi = new int[sk.n];
            for (int i = 0; i < n; i++) {
                this->dopolnitelni_kodovi[i] = sk.dopolnitelni_kodovi[i];
            }
        }
        return *this;
    }

    ~SpecijalnaKarticka() {
        delete[] dopolnitelni_kodovi;
    }

    int* getDopolnitelniKodovi() const {
        return dopolnitelni_kodovi;
    }

    void setDopolnitelniKodovi(int* dopolnitelniKodovi) {
        dopolnitelni_kodovi = dopolnitelniKodovi;
    }

    int getN() const {
        return n;
    }

    void setN(int n) {
        SpecijalnaKarticka::n = n;
    }

    static const int getMaxP() {
        return max_p;
    }

    int tezinaProbivanje() {
        int osnovno = Karticka::tezinaProbivanje();
        return osnovno + n;
    }

    SpecijalnaKarticka& operator+=(int nov) {
        if (n == max_p) {
            throw OutOfBoundException("Brojot na pin kodovi ne moze da go nadmine dozvolenoto");
        }
        int* temp = new int[n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = dopolnitelni_kodovi[i];
        }
        temp[n] = nov;
        n++;
        delete[] dopolnitelni_kodovi;
        dopolnitelni_kodovi = temp;
        return *this;
    }

    friend ostream& operator<<(ostream& os, SpecijalnaKarticka& k) {
        os << k.smetka << ": " << k.tezinaProbivanje();
        return os;
    }
};

const int Karticka::max_p = 4;

class Banka {
private:
    char naziv[30];
    Karticka* karticki[20];
    int broj;
    static int LIMIT;

public:
    Banka(char* naziv, Karticka** karticki, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            // ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()) {
                this->karticki[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            } else {
                this->karticki[i] = new Karticka(*karticki[i]);
            }
        }
        this->broj = broj;
    }

    ~Banka() {
        for (int i = 0; i < broj; i++) {
            delete karticki[i];
        }
    }

    static void setLIMIT(int limit) {
        LIMIT = limit;
    }

    void pecatiKarticki() {
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite:" << endl;
        for (int i = 0; i < broj; i++) {
            if (karticki[i]->tezinaProbivanje() <= LIMIT) {
                cout << *karticki[i] << endl;
            }
        }
    }

    void dodadiDopolnitelenPin(char* smetka, int novPin) {
        for (int i = 0; i < broj; i++) {
            if (strcmp(karticki[i]->getSmetka(), smetka) == 0) {
                SpecijalnaKarticka* sk = dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                if (sk) {
                    try {
                        *sk += novPin;
                    } catch (OutOfBoundException& o) {
                        o.message();
                    }
                }
            }
        }
    }
};

int Banka::LIMIT = 7;

int main() {

    Karticka** niza;
    int n, m, pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin >> n;
    niza = new Karticka*[n];
    for (int i = 0; i < n; i++) {
        cin >> smetka;
        cin >> pin;
        cin >> daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i] = new Karticka(smetka, pin);
        else
            niza[i] = new SpecijalnaKarticka(smetka, pin);
    }

    Banka komercijalna("Komercijalna", niza, n);
    for (int i = 0; i < n; i++) {
        delete niza[i];
    }
    delete[] niza;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> smetka >> pin;
        komercijalna.dodadiDopolnitelenPin(smetka, pin);
    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

    return 0;
}