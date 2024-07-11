#include <cstring>
#include <iostream>
using namespace std;
enum Size {mala,golema,familijarna};
class Pizza{
protected:
    char ime[20];
    char sostojki[100];
    float cena;
public:
    Pizza(){}
    Pizza(char *ime,char *sostojki,float cena){
        ::strcpy(this->ime,ime);
        ::strcpy(this->sostojki,sostojki);
        this->cena=cena;
    }
    virtual float price(){return 0;}
    bool operator<(Pizza &f){
        return this->price()<f.price();
    }
    virtual ~Pizza(){}
};
class FlatPizza:public Pizza{
    Size golemina;
public:
    FlatPizza():Pizza(){}
    FlatPizza(char *ime,char *sostojki, float cena)
            :Pizza(ime,sostojki,cena){
        golemina=mala;
    }

    FlatPizza(char *ime,char *sostojki, float cena, Size golemina)
            :Pizza(ime,sostojki,cena){
        this->golemina=golemina;
    }
    float price(){
        if(this->golemina==mala){
            return cena+(cena*10/100);
        }
        if(this->golemina==golema){
            return cena+(cena*20/100);
        }
        else{
            return cena+(cena*30/100);
        }
    }
    friend ostream &operator<<(ostream &os,FlatPizza &fp){
        os<<fp.ime<<": "<<fp.sostojki<<", ";
        if(fp.golemina==mala){
            os<<"small - "<<fp.price()<<endl;
        }
        if(fp.golemina==familijarna){
            os<<"family - "<<fp.price()<<endl;
        }

        return  os;
    }
//  bool operator<(FlatPizza &f){
//        return this->price()<f.price();
//    }
};
class FoldedPizza:public Pizza{
    bool daliBelo;
public:
    FoldedPizza():Pizza(){}
    FoldedPizza(char *ime,char *sostojki, float cena):
            Pizza(ime,sostojki,cena){
        daliBelo=true;
    }

    void setWhiteFlour(bool daliBelo) {
        FoldedPizza::daliBelo = daliBelo;
    }
    float price(){
        if(daliBelo){
            return cena+(cena*10/100);
        }
        return cena+(cena*30/100);
    }
    friend ostream &operator<<(ostream &os,FoldedPizza &fp){
        os<<fp.ime<<": "<<fp.sostojki<<", ";
        if(fp.daliBelo){
            os<<"wf - "<<fp.price()<<endl;
        }
        else{
            os<<"nwf - "<<fp.price()<<endl;
        }
        return  os;
    }
//    bool operator<(FoldedPizza &f){
//        return this->price()<f.price();
//    }
};
void expensivePizza(Pizza **pi,int num_p){
    Pizza *max=pi[0];
    for (int i=0;i<num_p;i++){
        if(*max<*pi[i]){
            max=pi[i];
        }
    }
    if (FlatPizza* fp = dynamic_cast<FlatPizza*>(max))
    {
        cout << *fp;
    }
    else if (FoldedPizza* fop = dynamic_cast<FoldedPizza*>(max))
    {
        cout << *fop;
    }
}
int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
