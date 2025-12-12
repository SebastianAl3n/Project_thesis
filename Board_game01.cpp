#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Customer{
    friend Reservation_manager;
    private:
    string first_name;
    string last_name;
    string street;
    int house_no;
    float postal_code;
    string city;
    int birth_year;
    double Ph_no;
    string U_id;

    public:
    Customer():first_name(""),last_name(""),street(""),house_no(0),postal_code(0),city(""),birth_year(0),Ph_no(0),U_id(""){}
    friend istream& operator>>(istream& is,Customer& customer);
    friend ostream& operator<<(ostream& os,Customer& customer);
};

istream& operator>>(istream& is, Customer& customer){
    cout<<"------Customer Data Entry-------"<<endl<<endl;
    cout<<"Enter the first name :";
    is>>customer.first_name;

    cout<<"Enter the last name :";
    is>>customer.last_name;

    cout<<"Enter the birth year :";
    is>>customer.birth_year;

    cout<<"Enter the Address :"<<endl;
    cout<<"House number :";
    is>>customer.house_no;
    cout<<"Street Name :";
    is>>customer.street;
    cout<<"City :";
    is>>customer.city;
    cout<<"Postal code :";
    is>>customer.postal_code;

    cout<<endl;
    cout<<"Enter the Phone Number :";
    is>>customer.Ph_no;

    cout<<"Enter your Member ID :";
    is>>customer.U_id;
    cout<<endl;
    cout<<"Your details have been successfully loggen in";
    return is;
}

class Available_gamelist{
    friend class Reservation_manager;
    private:
    string game_name;
    Available_gamelist* next_game;

    public:
    Available_gamelist(string &name):game_name(name),next_game(nullptr){}
};

class Reservation{
    friend class Reservation_manager;
    private:
    string reserved_game;
    string U_id;
    Reservation* next_reservation;

    public:
    Reservation():reserved_game(""),U_id(""),next_reservation(nullptr){}
    Reservation(string& g_name,string& id):reserved_game(g_name),U_id(id),next_reservation(nullptr){}
};

class Reservation_manager{
    private:
    Available_gamelist* game_head;
    Reservation* reservation_head;

    void initializeGameList();
    void save_reservation_to_file();
    void load_reservation_frm_file();

    bool isValidGame(const string& game_check);
    bool isGameReserved(const string& game_name);
    bool isCustomerReserved(const string& id);

    public:
    Reservation_manager();
    ~Reservation_manager();

    void run_menu();
    void make_reservatiom();
    void return_game();
    void display_all_reservations();
    void display_all_customers();
 
};
Reservation_manager::Reservation_manager():game_head(nullptr),reservation_head(nullptr){    //Constructor for Reservation manager.
    initializeGameList();
    load_reservation_frm_file();
}

Reservation_manager::~Reservation_manager(){
    Available_gamelist* current_game = game_head; //Look this up again

}

void Reservation_manager::initializeGameList(){
    string game_name[] ={"catan","ticket to ride","pandemic","carcassonne"};
    for(int i=0;i<4;i++){
        Available_gamelist* game = new Available_gamelist(game_name[i]);
        game->next_game=game_head;
        game_head=game;
    }
}

void Reservation_manager::load_reservation_frm_file(){ //Try adding throw catch exceptions here
    ifstream file("reservations.txt");
    if(file.is_open()){
        string game_name,customer_id;
        int count=0;
        
        while(file>>game_name>>customer_id){
            Reservation* new_reservation = new Reservation(game_name,customer_id);
            new_reservation->next_reservation=reservation_head;
            reservation_head=new_reservation;
            count++;
        }
        file.close();
        cout<<"Loaded "<<count<<" previous reservations"<<endl;
    }
    else{
        cout<<"No reservations were found"<<endl;
    }

}

void Reservation_manager::save_reservation_to_file(){ //also try to use throw catch
    ofstream file("reservations.txt");

    if(!file.is_open()){
        cerr<<"File could not be opened";
        return;
    }
    else{
        Reservation* current = reservation_head;
        int count=0;

        while(current!=nullptr){
            file<<current->reserved_game<<" "<<current->U_id;
            current=current->next_reservation;
            count++;
        }
    }
}

bool Reservation_manager::isValidGame(const string& game_check){
    Available_gamelist* current =game_head;
    while(current!=nullptr){
        if(current->game_name==game_check){
            return true;
        }
        current=current->next_game;
    }
    cout<<"The Entered game name "<<game_check<< " is not a valid one";
    return false;
}

bool Reservation_manager::isGameReserved(const string& game_check){
    Reservation* current =reservation_head;

    while(current!=nullptr){
        if(current->reserved_game==game_check){
            cout<<"The game "<<game_check<<" has already been reserved";
            return true;
        }
        current=current->next_reservation;
    }
    return false;
}

bool Reservation_manager::isCustomerReserved(const string& id){
    Reservation* current = reservation_head;

    while(current!=nullptr){
        if(current->U_id==id){
            cout<<"The customer has already made a reservatiom";
            return true;
        }
        current=current->next_reservation;
    }
    return false;

}

void Reservation_manager::run_menu(){
    int choice;
    cout<<"----------CAFE MANAGEMENT----------"<<endl;
    cout<<"1. Make a board game reservation"<<endl;
    cout<<"2. Cancel reservation and hand over board game<"<<endl;
    cout<<"3. Display all active reservations"<<endl;
    cout<<"4. Exit Program"<<endl;
    cout<<"Enter choice :";
    cin>>choice;                    //also add try catch exceptions here

    switch (choice)
    {
    case 1:{
        make_reservatiom();
        break;
    }
    case 2:{

    }
    case 3:{

    }
    case 4:{

    }
    
    default:
        break;
    }
}
