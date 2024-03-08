#include <bits/stdc++.h>
using namespace std;

class PEEL {
private:
    int id, purchase_date, model_year, age;
    double commission;
    string type, exterior_color, interior_color, last_name, postal_code;
    bool sunroof;
    fstream obj;
    ifstream obj2;
    map<string, int> car_by_name;
    map<int, int> car_by_id;
    vector<pair<int, int>> car_by_year;
    vector<string> car_types;
 
public:
    PEEL() {
        obj.open("details.flat", ios::in | ios::app);
        obj2.open("details.flat");
    }

    void input(int x) {
        obj.seekg(0, ios_base::end);
        obj.seekp(0, ios_base::end);
        cout<<"Car "<<x<<endl;
        cout<<"Enter Car ID: ";
        cin>>id;
        obj<<id<<endl;
        car_by_id.insert({x, id});
        cout<<"Enter data of purchase: ";
        cin>>purchase_date;
        obj<<purchase_date<<endl;
        cout<<"Enter Type of Vehicle: ";
        cin>>type;
        obj<<type<<endl;
        cout<<"Enter Car Model Year: ";
        cin>>model_year;
        obj<<model_year<<endl;
        car_by_year.push_back(make_pair(x, model_year));
        cout<<"Enter Exterior Color of Car: ";
        cin>>exterior_color;
        obj<<exterior_color<<endl;
        cout<<"Enter Interior Color of Car: ";
        cin>>interior_color;
        obj<<interior_color<<endl;
        cout<<"Does it have a sunroof? (yes or no): ";
        string sunroof_str;
        cin>>sunroof_str;
        sunroof = (sunroof_str == "yes");
        obj<<(sunroof ? "yes" : "no")<<endl;
        cout<<"Enter the Owners Last Name: ";
        cin>>last_name;
        obj<<last_name<<endl;
        car_by_name.insert({last_name, x});
        cout<<"Enter the Owners Age: ";
        cin>>age;
        obj<<age<<endl;
        cout<<"Enter the Owners Postal Code: ";
        cin>>postal_code;
        obj<<postal_code<<endl;
        cout<<"Enter the Commission Cost: ";
        cin>>commission;
        obj<<commission<<endl;
    }

    void output(int x) {
        cout<<"Car "<<x<<endl;
        obj.clear();
        obj.seekg(0, ios::beg);
        string temp;
        for(int i = 0; i<x-1; i++){
            for(int j = 0; j<11; j++){
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
        int id;
        cout<<"Enter the Car id you want to remove: ";
        cin>>id;
        obj.clear();
        obj.seekg(0, ios::beg);
        ofstream obj1("temp.txt");
        string line;
        while (getline(obj, line)) {
            int carId;
            obj1<<line<<endl;
            obj>>carId;
            if (carId == id) {
                for (int i = 0; i < 10; ++i) {
                    getline(obj, line);
                }
            }
        }
        obj.close();
        obj1.close();
        remove("details.flat");
        rename("temp.txt", "details.flat");
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
            output(i.first);
        }
    }
};

int main() {
    PEEL peel;

    char choice;
    while (true) {
        cout<<"Welcome to the Peel Car Dealership!"<<endl;
        cout<<"Your Choices are: "<<endl;
        cout<<"Add Vehicles to the File(I): "<<endl;
        cout<<"Output Every Vehicle in the File(O): "<<endl;
        cout<<"Remove a Vehicle by its ID(R): "<<endl;
        cout<<"Search for a car by its owner's name(N): "<<endl;
        cout<<"Display all cars sorted by Year of Manufacture(Y): "<<endl;
        cout<<"Exit (X): "<<endl;
        cout<<"Enter Your Choice (I, O, R, N, Y, X) in uppercase: ";
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
                return 0;
            default:
                cout<<"Invalid Choice, Try Again"<<endl;
        }
    }
}