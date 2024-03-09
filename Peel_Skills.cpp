#include <bits/stdc++.h>
using namespace std;

#define RESET "\033[0m"
#define CYAN "\033[36m"
#define BLUE "\033[34m"
#define RED  "\033[31m"
#define MAGENTA "\033[35m"

class PEEL{
private:
    int id, purchase_date, model_year, age, tint;
    double commission;
    string type, exterior_color, interior_color, last_name, postal_code;
    bool sunroof;
    fstream obj;
    map<string, int> car_by_name;
    map<int, int> car_by_id;
    vector<pair<int, int>> car_by_year;
    vector<string> car_types;
    const string questions[12] = {
    "Enter Car ID: ",
    "Enter Date of Purchase: ",
    "Enter Type of Vehicle (lowercase): ",
    "Enter Car Model Year: ",
    "Enter Exterior Color of Car: ",
    "Enter Interior Color of Car: ",
    "Does it have a sunroof? (yes or no): ",
    "What is the tint level? (Integer Only): ",
    "Enter the Owners Last Name: ",
    "Enter the Owners Age (lowercase): ",
    "Enter the Owners Postal Code: ",
    "Enter the Commission Cost: $"
    };
 
public:
    PEEL() {
        obj.open("details.flat", ios::in | ios::out);
    }

    void input(int x) {
        obj.seekg(0, ios_base::end);
        obj.seekp(0, ios_base::end);
        cout<<MAGENTA<<"Car "<<x<<RESET<<endl;

        for(int i = 0; i<12; i++){
            cout<<questions[i];
            if(i == 0){
                cin>>id;
                car_by_id.insert({id, x});
            }
            if(i == 1){
                cin>>purchase_date;
            }
            if(i == 2){
                cin>>type;
                if(type != "sedan"  && type != "suv"  && type != "van"){
                    cout<<RED<<"Invalid Car Type, Try Again"<<RESET<<endl;
                    i--;
                }   
            }
            if(i == 3){
                cin>>model_year;
                car_by_year.push_back(make_pair(model_year, x));
            }
            if(i == 4){
                cin>>exterior_color;
            }
            if(i == 5){
                cin>>interior_color;
            }
            if(i == 6){
                string sunroof_str;
                cin>>sunroof_str;
                sunroof = (sunroof_str == "yes");
            }
            if(i == 7){
                cin>>tint;
                if(tint < 0 || tint > 30){
                    cout<<RED<<"Invalid Tint Level, Try Again"<<RESET<<endl;
                    i--;
                }
            }
            if(i == 8){
                cin>>last_name;
                car_by_name.insert({last_name, x});
            }
            if(i == 9){
                cin>>age;
            }
            if(i == 10){
                cin>>postal_code;
            }
            if(i == 11){
                cin>>commission;
            }
        }
        obj<<id<<endl;
        obj<<purchase_date<<endl;
        obj<<type<<endl;
        obj<<model_year<<endl;
        obj<<exterior_color<<endl;
        obj<<interior_color<<endl;
        obj<<(sunroof ? "yes" : "no")<<endl;
        obj<<tint<<endl;
        obj<<last_name<<endl;
        obj<<age<<endl;
        obj<<postal_code<<endl;
        obj<<commission<<endl;
    }

    void output(int x) {
        cout<<MAGENTA<<"Car "<<x<<RESET<<endl;
        obj.clear();
        obj.seekg(0, ios::beg);
        string temp;
        
        for(int i = 0; i<x-1; i++){
            for(int j = 0; j<12; j++){
                getline(obj,temp);
            }
        }

        string line;
        getline(obj, line);
        id = stoi(line);
        cout<<"Car ID: "<<id<<endl;

        getline(obj, line);
        purchase_date = stoi(line);
        cout<<"Date of Purchase: "<<purchase_date<<endl;

        getline(obj,line);
        type = line;
        cout<<"Vehicle Type: "<<type<<endl;

        getline(obj, line);
        model_year = stoi(line);
        cout<<"Model Year: "<<model_year<<endl;

        obj>>exterior_color;
        cout<<"Exterior Color: "<<exterior_color<<endl;

        obj>>interior_color;
        cout<<"Interior Color: "<<interior_color<<endl;

        obj>>line;
        sunroof = (line == "yes");
        cout<<"Does it have a sunroof?: "<<(sunroof ? "Yes" : "No")<<endl;

        obj>>line;
        tint = stoi(line);
        cout<<"Tint Level: "<<tint<<"%"<<endl;

        obj>>line;
        last_name = line;
        cout<<"Owner's Last Name: "<<last_name<<endl;

        obj>>line;
        age = stoi(line);
        cout<<"Owner's Age: "<<age<<endl;

        obj>>postal_code;
        cout<<"Postal Code: "<<postal_code<<endl;

        obj>>line;
        commission = stod(line);
        cout<<"Commission: "<<commission<<endl;
}

    void remove_by_id() {
        int remove_id;
        cout<<"Enter the Car id you want to remove: ";
        cin>>remove_id;

        string line;

        obj.seekg((car_by_id[id] - 1) * sizeof(string) * 12, ios::beg);
        obj<<endl;
    }

    void search_by_name() {
        string name;
        cout<<"Enter the Name you want to search the car by: ";
        cin>>name;
        output(car_by_name[name]);
    }

    void display_by_year(){
        sort(car_by_year.begin(), car_by_year.end());
        for(auto &i : car_by_year){
            output(i.second);
        }
    }
};

int main() {
    PEEL peel;

    char choice;
    while (true) {
        cout<<CYAN<<"\nWelcome to the Peel Car Dealership!"<<RESET<<endl;
        cout<<"Your Choices are: "<<endl;
        cout<<"Add Vehicles to the File"<<BLUE<<" (I): "<<RESET<<endl;
        cout<<"Output A Specfic vehicle in the File"<<BLUE<<" (O): "<<RESET<<endl;
        cout<<"Remove a Vehicle by its ID"<<BLUE<<" (R): "<<RESET<<endl;
        cout<<"Search for a car by its owner's name"<<BLUE<<" (N): "<<RESET<<endl;
        cout<<"Display all cars sorted by Year of Manufacture"<<BLUE<<" (Y): "<<RESET<<endl;
        cout<<"Exit "<<BLUE<<"(X): "<<RESET<<endl;
        cout<<BLUE<<"Enter Your Choice (I, O, R, N, Y, X) in uppercase: "<<RESET;
        cin>>choice;

        switch (choice) {
            case 'I':
                int n;
                cout<<"Enter which car number you would like to add: ";
                cin>>n;
                peel.input(n);
                break;
            case 'O':
                int m;
                cout<<"Enter which car you would like to view: ";
                cin>>m;
                peel.output(m);
                break;
            case 'R':
                peel.remove_by_id();
                break;
            case 'N':
                peel.search_by_name();
                break;
            case 'Y':
                peel.display_by_year();
                break;
            case 'X':
                peel.obj.close();
                return 0;
            default:
                cout<<"Invalid Choice, Try Again"<<endl;
        }
    }
}
