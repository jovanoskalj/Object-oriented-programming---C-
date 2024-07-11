#include <iostream>
#include <cstring>

using namespace std;
class Image{
protected:
    char *name;
    char user_name[50];
    int w;
    int h;
public:
    Image(const char *name="untitled", char *user_name="unknown", int w=800, int h=800)
    {
        this->name = new char[strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->user_name, user_name);
        this->w = w;
        this->h = h;
        //  name = "unknown";

    }
    Image(const Image &im)
    {
        this->name = new char[strlen(im.name)+1];
        strcpy(this->name,im.name);
        strcpy(this->user_name, im.user_name);
        this->w = im.w;
        this->h = im.h;
    }
    Image& operator=(const Image &im){
        if(this!=&im){
            delete []name;
            this->name = new char[strlen(im.name)+1];
            strcpy(this->name,im.name);
            strcpy(this->user_name, im.user_name);
            this->w = im.w;
            this->h = im.h;
        }
        return *this;
    }
    virtual int fileSize(){
        return h*w*3;
    }
    friend ostream&operator<<(ostream&out, Image&im){
        out<<im.name<<" "<<im.user_name<<" "<<im.fileSize()<<endl;
        return out;
    }
    bool operator>(Image&i){
        return this->fileSize()>i.fileSize();
    }
    virtual ~Image(){
        delete[]name;
    }
};
//TransparentImage(name,user_name, w, h, tl);
class TransparentImage: public Image{
private:
    bool tl;
public:
    TransparentImage(): Image(){
        tl=true;
    }
    TransparentImage(char *name, char *user_name,int w,int h, bool tl):
            Image(name,user_name,w,h){
        this->tl=tl;
    }

    int fileSize(){
        if(tl) return w*h*4;
        else return w*h + (w*h)/8;
    }
    ~TransparentImage(){}
};
class Folder{
private:
    char ime[255];
    char sopstvenik[50];
    Image *images[100];
    int n;
public:
    Folder(){
        strcpy(ime,"untitled");
        strcpy(sopstvenik,"unknown");
        n=0;
        *images = nullptr;
    }
    Folder(char *ime, char *sopstvenik, int n, Image **images){
        this->n=n;
        for(int i=0; i<n; i++){
            this->images[i]=images[i];
        }
        strcpy(this->ime, ime);
        strcpy(this->sopstvenik,sopstvenik);
    }
    Folder (char *ime, char *sopstvenik){
        strcpy(this->ime,ime);
        strcpy(this->sopstvenik,sopstvenik);
    }
    int folderSize(){
        int sum=0;
        for(int i=0; i<n; i++){
            sum+=images[i]->fileSize();
        }
        return sum;
    }
    Image *getMaxFile(){
        int max=0;
        int index;
        for(int i=0; i<n; i++){
            if(images[i]->fileSize()>max){
                max = images[i]->fileSize();
                index=i;
            }
        }
        return images[index];
    }
    Folder&operator+=(Image&nova){
        images[n] = &nova;
        n++;
        return *this;
    }
    friend ostream& operator<<(ostream &out,Folder &f)
    {
        out<<f.ime<<" "<<f.sopstvenik<<endl;
        out<<"--"<<endl;
        for(int i=0;i<f.n;i++)
        {
            out<<*f.images[i];
        }
        out<<"--"<<endl;
        out<<"Folder size: "<<f.folderSize();
        return out;
    }
    Image *operator[](int index){
        if(index>=0&&index<=n)
        {
            return images[index];
        }
        else return NULL;
    }
    ~Folder(){}
};
Folder &max_folder_size(Folder *folders, int n){
    int max=0;
    int index;
    for(int i=0; i<n; i++){
        if(folders[i].folderSize()>max){
            max=folders[i].folderSize();
            index=i;
        }
    }
    return folders[index];
}
int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
}