#include <iostream>
#include <cstring>
using namespace std;
class Book{
protected:
    char ISBN[20];
    char title[50];
    char author[30];
    float price;
public:
    Book(){}
    Book(char *ISBN, char *title, char *author, float price){
        ::strcpy(this->ISBN,ISBN);
        strcpy(this->title,title);
        strcpy(this->author,author);
        this->price=price;
    }
    virtual float bookPrice(){return 0;}
    virtual~ Book(){}
    virtual bool operator>(Book &b){
        return this->bookPrice()>b.bookPrice();
    }
    friend ostream &operator<<(ostream &os, Book &b){
        os<<b.ISBN<<": "<<b.title<<", "<<b.author<<" "<<b.bookPrice()<<endl;
    }
    void setISBN(char *ISBN){
        strcpy(this->ISBN,ISBN);
    };
};
class OnlineBook:public Book{
    char *url;
    int MB;
public:
    OnlineBook():Book(){
        url= new char[0];
    }
    OnlineBook(char *ISBN, char *title, char *author,
               float price, char *url, int MB)
            :Book(ISBN, title,author,price){
        this->url=new char[strlen(url)+1];
        ::strcpy(this->url,url);
        this->MB=MB;
    }
    float bookPrice(){
        if(MB>20){
            return price+(price *20/100);
        }
        return price;
    }
    bool operator>(OnlineBook &b){
        return this->bookPrice()>b.bookPrice();
    }
};
class PrintBook:  public Book{
    float weight;
    bool inStock;
public:
    PrintBook():Book(){}
    PrintBook(char *ISBN, char *title, char *author,
              float price, float weight,bool inStock):
            Book(ISBN, title,author,price){
        this->weight=weight;
        this->inStock=inStock;
    }
    float  bookPrice(){
        if(weight>0.7){
            return price+(price*15/100.0);
        }
        return price;
    }
    bool operator>(OnlineBook &b){
        return this->bookPrice()>b.bookPrice();
    }
};
void mostExpensiveBook (Book** books, int n){
    int br_online=0;
    int br_print=0;
    Book* max = books[0];
    for (int i=0;i<n;i++){
        OnlineBook *ob= dynamic_cast<OnlineBook*>(books[i]);
        if(ob){
            br_online++;
        }
        else{
            br_print++;
        }
        if(*books[i]>*max){
            max=books[i];
        }
    }
    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<br_online<<endl;
    cout<<"Total number of print books: "<<br_print<<endl;

    cout << "The most expensive book is:" << endl;
    if (OnlineBook* ob = dynamic_cast<OnlineBook*>(max)) {
        cout << *ob;
    } else if (PrintBook* pb = dynamic_cast<PrintBook*>(max)) {
        cout << *pb;
    }
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
