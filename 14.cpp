#include <iostream>
#include <cstring>
using namespace std;
class SMS{
protected:
    float cena;
    char broj[50];
    const static int DDV;
public:
    SMS(){}
    SMS(char *broj, float cena){
        ::strcpy(this->broj,broj);
        this->cena=cena;
    }
    virtual float SMS_cena(){}
    friend ostream &operator<<(ostream &os, SMS &s){
        os<<"Tel: "<<s.broj<<" - cena: "<<s.SMS_cena()<<"den."<<endl;
        return os;
    }
    virtual ~SMS(){}
};

const int SMS::DDV=18;

class RegularSMS:public  SMS{
private:
    char msg[1000];
    bool daliRoaming;
    static int p_reg;
public:
    RegularSMS():SMS(){}
    RegularSMS(char *broj, float cena, char *msg,bool daliRoaming)
            :SMS(broj,cena){
        ::strcpy(this->msg,msg);
        this->daliRoaming=daliRoaming;
    }
    float SMS_cena(){
        int cel_del= ::strlen(msg)/160;
        if(strlen(msg)%160!=0){
            cel_del++;
        }
        if(daliRoaming){
            return cel_del*(cena + (cena*p_reg/100.0));
        }
        else{
            return cel_del*(cena + (cena*DDV/100.0));
        }

    }

    static void set_rProcent(int pReg) {
        p_reg = pReg;
    }
};
int RegularSMS::p_reg=300;

class SpecialSMS:public SMS{
private:
    bool daliHumanitarna;
    static int p_spec;
public:
    SpecialSMS():SMS(){}
    SpecialSMS(char *broj, float cena, bool daliHumanitarna):
            SMS(broj,cena){
        this->daliHumanitarna=daliHumanitarna;
    }

    static void set_sProcent(int pSpec) {
        p_spec = pSpec;
    }
    float SMS_cena(){
        if(daliHumanitarna){
            return cena;
        }
        else{
            return cena+(cena*p_spec/100.0);
        }
    }
    friend ostream &operator<<(ostream &os, SpecialSMS &s){
        os<<s.broj<<": "<<s.SMS_cena()<<endl;
        return os;
    }

};
int SpecialSMS::p_spec=150;

void vkupno_SMS(SMS** poraka, int n){
    float vk_s=0,vk_r=0;
    int br_s=0, br_r=0;
    for(int i=0;i<n;i++){
        SpecialSMS *s=dynamic_cast<SpecialSMS*>(poraka[i]);
        if(s){
            br_s++;
            vk_s+=poraka[i]->SMS_cena();
        }
        else{
            br_r++;
            vk_r+=poraka[i]->SMS_cena();
        }
    }
    cout<<"Vkupno ima "<<br_r<< " regularni SMS poraki i nivnata cena e: "<<vk_r<<endl;
    cout<<"Vkupno ima "<<br_s<<" specijalni SMS poraki i nivnata cena e: "<<vk_s<<endl;
}



int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
