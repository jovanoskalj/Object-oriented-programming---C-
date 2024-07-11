#include <iostream>
#include <cstring>

using namespace std;
class Transport{
protected:
    char destination[20];
    int price;
    int distance;
public:
    Transport(){}
    Transport(char *destination,int price,int distance){
        ::strcpy(this->destination,destination);
        this->price=price;
        this->distance=distance;
    }

    const char *getDestination() const {
        return destination;
    }

    int getPrice() const {
        return price;
    }

    void setPrice(int price) {
        Transport::price = price;
    }

    int getDistance() const {
        return distance;
    }
    virtual int cenaTransport() =0;
    void setDistance(int distance) {
        Transport::distance = distance;
    }
    virtual bool operator<(Transport &t){
        return this->distance<t.distance;
    }
};
class  AvtomobilTransport:public Transport{
private:
    bool daliShofer;
public:
    AvtomobilTransport():Transport(){}
    AvtomobilTransport(char *destination,int price,
                       int distance,bool daliShofer):Transport(destination,price,distance){
        this->daliShofer=daliShofer;
    }
    AvtomobilTransport(const AvtomobilTransport &at):Transport(at){
        this->daliShofer=at.daliShofer;
    }

    bool isDaliShofer() const {
        return daliShofer;
    }

    void setDaliShofer(bool daliShofer) {
        AvtomobilTransport::daliShofer = daliShofer;
    }
    int cenaTransport() {
        if (daliShofer) {
            return price + (price * 20 / 100.0);
        } else {
            return price;
        }
    }
    virtual bool operator<(AvtomobilTransport &t){
        return this->distance<t.distance;
    }

};
class KombeTransport:public  Transport{
private:
    int max_lugje;
public:
    KombeTransport():Transport(){}
    KombeTransport(char *destination,int price,
                   int distance,int max_lugje):Transport(destination,price,distance){
        this->max_lugje=max_lugje;
    }

    int getMaxLugje() const {
        return max_lugje;
    }

    void setMaxLugje(int maxLugje) {
        max_lugje = maxLugje;
    }
    int cenaTransport() {
        return price-(max_lugje*200);
    }
    virtual bool operator<(KombeTransport &t){
        return this->distance<t.distance;
    }
};
void pecatiPoloshiPonudi(Transport**ponudi, int n, Transport &nov){
    for (int i=0;i<n-1;i++){
        for(int j=i+1; j<n;j++){
            if(ponudi[i]->getDistance() > ponudi[j]->getDistance()){
                Transport * temp= ponudi[i];
                ponudi[i]=ponudi[j];
                ponudi[j]=temp;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(nov.cenaTransport()<ponudi[i]->cenaTransport()){
            cout<<ponudi[i]->getDestination()<<" "<<ponudi[i]->getDistance()<<" "<<
                ponudi[i]->cenaTransport()<<endl;
        }
    }


}


int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
