#include <iostream>
#include <cstring>
using namespace  std;
class Koncert{
private:
    char naziv[20];
    char lokacija[20];
    static float popust;
    float cena_bilet;
public:
    Koncert(){}
    Koncert(char *naziv, char *lokacija,float cena_bilet){
        ::strcpy(this->naziv,naziv);
        ::strcpy(this->lokacija,lokacija);
        this->cena_bilet=cena_bilet;
    }
    virtual float cena(){
        return cena_bilet - (cena_bilet*popust);
    }

    const char *getNaziv() {
        return naziv;
    }

    static float getSezonskiPopust() {
        return popust;
    }

    static void setSezonskiPopust(float popust) {
        Koncert::popust = popust;
    }

    virtual ~Koncert(){}
};float Koncert::popust=0.2;
class ElektronskiKoncert:public Koncert{
private:
    char *DJ;
    float casovi;
    bool daliDnevna;
public:
    ElektronskiKoncert():Koncert(){
        DJ=new char[0];
    }
    ElektronskiKoncert(char *naziv, char *lokacija,
                       float cena,char *DJ, float casovi, bool daliDnevna)
            : Koncert(naziv,lokacija,cena){
        this->DJ= new char[strlen(DJ)+1];
        ::strcpy(this->DJ,DJ);
        this->casovi=casovi;
        this->daliDnevna=daliDnevna;
    }
    ElektronskiKoncert(ElektronskiKoncert &e):Koncert(e){
        this->DJ= new char[strlen(e.DJ)+1];
        ::strcpy(this->DJ,e.DJ);
        this->casovi=e.casovi;
        this->daliDnevna=e.daliDnevna;
    }
    ElektronskiKoncert&operator=(ElektronskiKoncert &e){
        if(this!=&e) {
            delete[]DJ;
            Koncert::operator=(e);
            this->DJ = new char[strlen(e.DJ) + 1];
            ::strcpy(this->DJ, e.DJ);
            this->casovi = e.casovi;
            this->daliDnevna = e.daliDnevna;
        }
        return *this;
    }

    float cena()
    {
        float total = Koncert::cena();

        if(casovi >7)
        {
            total+=360;
        }
        else if(casovi > 5)
        {
            total+=150;
        }

        if(daliDnevna)
        {
            total-=50;
        }
        else
        {
            total+=100;
        }
        return total;
    }

    ~ElektronskiKoncert()
    {
        delete []DJ;
    }

};
void najskapKoncert(Koncert **k,int n)
{
    int brElek=0;
    float max=k[0]->cena();
    int index=0;

    for(int i=0;i<n;i++){
        ElektronskiKoncert *ek = dynamic_cast<ElektronskiKoncert*>(k[i]);
        if(ek!=0)
        {
            brElek++;
        }
        if(k[i]->cena() > max)
        {
            max = k[i]->cena();
            index = i;
        }
    }

    cout<<"Najskap koncert: "<<k[index]->getNaziv()<<" "<<k[index]->cena()<<endl;
    cout<<"Elektronski koncerti: "<<brElek<<" od vkupno "<<n<<endl;

}
bool prebarajKoncert(Koncert **k,int n,char *naziv,bool el)
{
    for(int i=0;i<n;i++)
    {
        if(el)
        {
            ElektronskiKoncert *ek = dynamic_cast<ElektronskiKoncert *>(k[i]);
            if(ek!=0)
            {
                if(strcmp(ek->getNaziv(),naziv)==0)
                {
                    cout<<ek->getNaziv()<<" "<<ek->cena()<<endl;
                    return true;
                }
            }
        }
        else
        {
            if(strcmp(k[i]->getNaziv(),naziv)==0)
            {
                cout<<k[i]->getNaziv()<<" "<<k[i]->cena()<<endl;
                return true;
            }

        }
    }
    return false;
}
int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
