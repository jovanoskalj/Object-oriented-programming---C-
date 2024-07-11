#include<iostream>
#include<cstring>
using namespace std;
int MAX=100;
enum typeC{standard,loyal,vip};
class UserExistsException {
private:
    const char* msg;
public:
    UserExistsException(const char* msg) {
        this->msg = msg;
    }
    void message() {
        cout << msg << endl;
    }
};
class Customer{
protected:
    char ime[50];
    char email[50];
    typeC tip;
    static int popust;
    static const int dopolnitelen_popust;
    int br_proizvodi;

public:
    Customer(){}
    Customer(char *ime, char *email, typeC tip, int br_proizvodi){
        ::strcpy(this->ime,ime);
        ::strcpy(this->email,email);
        this->tip=tip;
        this->br_proizvodi=br_proizvodi;
    }

    static void setDiscount1(int popust) {
        Customer::popust = popust;
    }
    friend ostream &operator<<(ostream &os,Customer &c){
        os<<c.ime<<endl;
        os<<c.email<<endl;
        os<<c.br_proizvodi<<endl;
        if(c.tip==standard){
            os<<"standard 0"<<endl;
        }
        if(c.tip==loyal){
            os<<"loyal "<<c.popust<<endl;
        }
        if(c.tip==vip){
            os<<"vip "<<c.dopolnitelen_popust+c.popust<<endl;
        }
        return os;
    }

    char *getEmail() {
        return email;
    }

    typeC getTip()  {
        return tip;
    }

    int getBrProizvodi()  {
        return br_proizvodi;
    }

    void setTip(typeC tip) {
        Customer::tip = tip;
    }
};
int Customer::popust=10;
const int Customer::dopolnitelen_popust=20;

class  FINKI_bookstore{
private:
    Customer *niza;
    int n;
public:
    FINKI_bookstore(){
        n=0;
        niza=new Customer[0];
    }
    FINKI_bookstore(FINKI_bookstore &fb){
        this->n=fb.n;
        this->niza= new Customer[fb.n+1];
        for (int i=0;i<n;i++){
            this->niza[i]=fb.niza[i];
        }
    }
    FINKI_bookstore&operator=(FINKI_bookstore &fb){
        if(this!=&fb) {
            delete []niza;
            this->n = fb.n;
            this->niza = new Customer[fb.n + 1];
            for (int i = 0; i < n; i++) {
                this->niza[i] = fb.niza[i];
            }
        }
        return *this;
    }
    void setCustomers(Customer *niza, int n){
        this->n = n;
        this->niza = new Customer[n + 1];
        for (int i = 0; i < n; i++) {
            this->niza[i] = niza[i];
        }
    }
    FINKI_bookstore &operator+=(Customer &c){
        Customer *temp = new Customer[n+1];
        for (int i=0;i<n;i++){
            if(strcmp(niza[i].getEmail(),c.getEmail())==0){
                throw UserExistsException("The user already exists in the list!");
            }
        }
        for (int i=0;i<n;i++){
            temp[i]=niza[i];
        }
        temp[n]=c;
        n++;
        delete []niza;
        niza=temp;
        return *this;
    }
    void update(){
        for (int i=0;i<n;i++){
            if(niza[i].getBrProizvodi()>10 && niza[i].getTip()==loyal){
                niza[i].setTip(vip);
            }
            if(niza[i].getBrProizvodi()>5 && niza[i].getTip()==standard){
                niza[i].setTip(loyal);
            }
        }
    }
    friend ostream& operator<<(ostream& os, FINKI_bookstore& fc) {
        for (int i = 0; i < fc.n; i++) {
            os << fc.niza[i];
        }
        return os;
    }
};
int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try{
            fc+=c;
        }
        catch (UserExistsException &e){
            e.message();
        }


        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
