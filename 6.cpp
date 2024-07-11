
#include<iostream>
#include<cstring>
using namespace std;

class ExistingGame
{
private:
    char *msg;
public:
    ExistingGame(char *msg)
    {
        this->msg = new char[strlen(msg)+1];
        strcpy(this->msg,msg);
    }
    void message()
    {
        cout<<msg<<endl;
    }
    ~ExistingGame()
    {
        delete []msg;
    }

};
class Game
{
protected:
    char game_name[100];
    float game_price;
    bool game_on_sale;
public:
    Game(){}
    Game(char *game_name,float game_price, bool game_on_sale)
    {
        strcpy(this->game_name,game_name);
        this->game_price = game_price;
        this->game_on_sale = game_on_sale;
    }
    bool operator==(const Game &g)
    {
        return strcmp(this->game_name,g.game_name)==0;
    }
    virtual void citaj()
    {   cin.get();
        cin.getline(game_name,100);
        cin>>game_price>>game_on_sale;
    }
    virtual void pecati()
    {
        cout<<"Game: "<<game_name<<", regular price: $"<<game_price;
        if(game_on_sale)
        {
            cout<<", bought on sale";
        }

    }
    friend ostream &operator<<(ostream &out,Game &g)
    {
        g.pecati();
        return out;
    }
    friend istream &operator>>(istream &in, Game &g)
    {
        g.citaj();
        return in;
    }
    virtual float price()
    {
        if(game_on_sale)
            return game_price - game_price*30/100;
        else
            return game_price;
    }
    virtual ~Game(){}
};

class SubscriptionGame : public Game{
private:
    float sub_game_monthly_fee;
    int sub_game_month;
    int sub_game_year;
public:
    SubscriptionGame(){}
    SubscriptionGame (char *game_name,float game_price, bool game_on_sale,
                      float sub_game_monthly_fee,int sub_game_month,int sub_game_year) : Game(game_name,game_price,game_on_sale)
    {
        this->sub_game_monthly_fee = sub_game_monthly_fee;
        this->sub_game_month = sub_game_month;
        this->sub_game_year = sub_game_year;
    }
    void pecati()
    {
        Game::pecati();
        cout<<", monthly fee: $"<<sub_game_monthly_fee<<", purchased: "<<sub_game_month<<"-"<<sub_game_year<<endl;
    }
    void citaj(){
        Game::citaj();
        cin>>sub_game_monthly_fee>>sub_game_month>>sub_game_year;
    }
    float price()
    {
        int brGod = 2018 - sub_game_year;
        int brMeseci = brGod*12 - sub_game_month + 5;//bidejki e fikno kazano deka e maj
        float osnovna = Game::price();
        return osnovna + brMeseci*sub_game_monthly_fee;
    }
    ~SubscriptionGame(){}
};

class User
{
private:
    char username[100];
    Game **games;
    int n;
public:
    User()
    {
        n=0;
        games = new Game*[0];
    }
    User(char *username)
    {
        strcpy(this->username, username);
        this->n=0;
        games = new Game*[0];
    }
    User(const User &u)
    {
        strcpy(this->username, username);
        this->n=u.n;
        games = new Game*[n];
        for(int i=0;i<n;i++)
        {
            this->games[i] = u.games[i];
        }
    }
    User& operator=(const User &u)
    {
        if(this!=&u)
        {
            delete []games;
            strcpy(this->username, username);
            this->n=u.n;
            games = new Game*[n];
            for(int i=0;i<n;i++)
            {
                this->games[i] = u.games[i];
            }
            return *this;
        }

        return *this;
    }

    User &operator+=( Game &nova)
    {
        for(int i=0;i<n;i++)
        {
            if(*games[i]==nova)
            {
                throw ExistingGame("The game is already in the collection");
            }
        }

        Game **temp = new Game*[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i] = games[i];
        }
        temp[n] = &nova;
        n++;
        delete []games;
        games = temp;
        return *this;
    }
    float total_spent()
    {
        float suma=0;
        for(int i=0;i<n;i++)
        {
            suma+=games[i]->price();
        }
        return suma;
    }
    friend ostream &operator<<(ostream &out,const User &u)
    {
        out<<endl;
        out<<"User: "<<u.username<<endl;
        for(int i=0;i<u.n;i++)
        {
            SubscriptionGame* sg = dynamic_cast<SubscriptionGame*>(u.games[i]);
            if(sg!=0)
            {
                out<<"- "<<*sg;
            }
            else
            {
                out<<"- "<<*u.games[i]<<endl;
            }
        }
        return out;
    }
    ~User()
    {
        for(int i=0;i<n;i++)
        {
            delete games[i];
        }
        delete []games;
    }
};
int main()
{
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1)
    {
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2)
    {
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3)
    {
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4)
    {
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5)
    {
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try
        {

            for (int i=0; i<num_user_games; ++i)
            {

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1)
                {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2)
                {
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }
        catch(ExistingGame &ex)
        {
            ex.message();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6)
    {
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i)
        {

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1)
            {
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2)
            {
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try
            {
                u+=(*g);
            }
            catch(ExistingGame &ex)
            {
                ex.message();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7)
    {
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i)
        {

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1)
            {
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2)
            {
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout<<u;
        cout<<endl;
        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }

}
