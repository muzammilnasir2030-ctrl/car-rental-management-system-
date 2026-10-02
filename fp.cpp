#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;

struct CarNode {
    int id;
    string brand;
    string model;
    bool available;
    CarNode* left;
    CarNode* right;

    CarNode(int i, string b, string m, bool a = true) {
        id = i;
        brand = b;
        model = m;
        available = a;
        left = right = NULL;
    }
};

struct CustomerNode {
    int id;
    string name;
    string phone;
    CustomerNode* left;
    CustomerNode* right;

    CustomerNode(int i, string n, string p) {
        id = i;
        name = n;
        phone = p;
        left = right = NULL;
    }
};

struct QueueNode {
    int requestId;
    int carId;
    int customerId;
    double cost;
    string date;
    QueueNode* next;

    QueueNode(int r, int c, int cu, double co, string d) {
        requestId = r;
        carId = c;
        customerId = cu;
        cost = co;
        date = d;
        next = NULL;
    }
};

struct StackNode {
    string description;
    double amount;
    string date;
    StackNode* next;

    StackNode(string d, double a, string da) {
        description = d;
        amount = a;
        date = da;
        next = NULL;
    }
};

class CarBST {
    CarNode* root;

    CarNode* insert(CarNode* r, CarNode* n) {
        if (!r) return n;
        if (n->id < r->id)
            r->left = insert(r->left, n);
        else
            r->right = insert(r->right, n);
        return r;
    }

    void inorder(CarNode* r) {
        if (!r) return;
        inorder(r->left);
        cout << " | " << setw(6) << r->id << " | " 
             << setw(12) << r->brand << " | " 
             << setw(12) << r->model << " | " 
             << setw(10) << (r->available ? "Available" : "Rented") << " |\n";
        inorder(r->right);
    }

    void saveToFile(CarNode* r, ofstream& file) {
        if (!r) return;
        saveToFile(r->left, file);
        file << r->id << "," << r->brand << "," << r->model << "," << r->available << endl;
        saveToFile(r->right, file);
    }

public:
    CarBST() {
        root = NULL;
    }

    void addCar(int id, string b, string m, bool a = true) {
        root = insert(root, new CarNode(id, b, m, a));
    }

    CarNode* find(int id) {
        CarNode* t = root;
        while (t) {
            if (t->id == id) return t;
            if (id < t->id) t = t->left;
            else t = t->right;
        }
        return NULL;
    }

    CarNode* deleteNode(CarNode* r, int id) {
        if (!r) return NULL;
        if (id < r->id)
            r->left = deleteNode(r->left, id);
        else if (id > r->id)
            r->right = deleteNode(r->right, id);
        else {
            if (!r->left) {
                CarNode* temp = r->right;
                delete r;
                return temp;
            } else if (!r->right) {
                CarNode* temp = r->left;
                delete r;
                return temp;
            }
            CarNode* temp = r->right;
            while (temp->left) temp = temp->left;
            r->id = temp->id;
            r->brand = temp->brand;
            r->model = temp->model;
            r->available = temp->available;
            r->right = deleteNode(r->right, temp->id);
        }
        return r;
    }

    bool updateCar(int id, string b, string m, bool a) {
        CarNode* car = find(id);
        if (car) {
            car->brand = b;
            car->model = m;
            car->available = a;
            return true;
        }
        return false;
    }

    bool deleteCar(int id) {
        if (find(id)) {
            root = deleteNode(root, id);
            return true;
        }
        return false;
    }

    void display() {
        if (!root) {
            cout << "\n +----------------------------------------------------+\n";
            cout << " |          No cars available in system.             |\n";
            cout << " +----------------------------------------------------+\n";
            return;
        }
        cout << "\n +--------+--------------+--------------+------------+\n";
        cout << " | Car ID |    Brand     |    Model     |   Status   |\n";
        cout << " +--------+--------------+--------------+------------+\n";
        inorder(root);
        cout << " +--------+--------------+--------------+------------+\n";
    }

    void saveToFile() {
        ofstream file("cars.csv");
        if (file.is_open()) {
            file << "ID,Brand,Model,Available\n";
            saveToFile(root, file);
            file.close();
        }
    }

    void loadFromFile() {
        ifstream file("cars.csv");
        if (file.is_open()) {
            string line;
            bool firstLine = true;
            while (getline(file, line)) {
                if (firstLine) {
                    firstLine = false;
                    continue;
                }
                if (line.empty()) continue;
                stringstream ss(line);
                string id_str, brand, model, avail_str;
                
                getline(ss, id_str, ',');
                getline(ss, brand, ',');
                getline(ss, model, ',');
                getline(ss, avail_str, ',');
                
                int id = atoi(id_str.c_str());
                bool available = (avail_str == "1" || avail_str == "true" || avail_str == "True");
                
                addCar(id, brand, model, available);
            }
            file.close();
        }
    }
};

class CustomerBST {
    CustomerNode* root;

    CustomerNode* insert(CustomerNode* r, CustomerNode* n) {
        if (!r) return n;
        if (n->id < r->id)
            r->left = insert(r->left, n);
        else
            r->right = insert(r->right, n);
        return r;
    }

    void inorder(CustomerNode* r) {
        if (!r) return;
        inorder(r->left);
        cout << " | " << setw(7) << r->id << " | " 
             << setw(20) << r->name << " | " 
             << setw(15) << r->phone << " |\n";
        inorder(r->right);
    }

    void saveToFile(CustomerNode* r, ofstream& file) {
        if (!r) return;
        saveToFile(r->left, file);
        file << r->id << "," << r->name << "," << r->phone << endl;
        saveToFile(r->right, file);
    }

public:
    CustomerBST() {
        root = NULL;
    }

    void addCustomer(int id, string n, string p) {
        root = insert(root, new CustomerNode(id, n, p));
    }

    CustomerNode* find(int id) {
        CustomerNode* t = root;
        while (t) {
            if (t->id == id) return t;
            if (id < t->id) t = t->left;
            else t = t->right;
        }
        return NULL;
    }

    CustomerNode* deleteNode(CustomerNode* r, int id) {
        if (!r) return NULL;
        if (id < r->id)
            r->left = deleteNode(r->left, id);
        else if (id > r->id)
            r->right = deleteNode(r->right, id);
        else {
            if (!r->left) {
                CustomerNode* temp = r->right;
                delete r;
                return temp;
            } else if (!r->right) {
                CustomerNode* temp = r->left;
                delete r;
                return temp;
            }
            CustomerNode* temp = r->right;
            while (temp->left) temp = temp->left;
            r->id = temp->id;
            r->name = temp->name;
            r->phone = temp->phone;
            r->right = deleteNode(r->right, temp->id);
        }
        return r;
    }

    bool updateCustomer(int id, string n, string p) {
        CustomerNode* customer = find(id);
        if (customer) {
            customer->name = n;
            customer->phone = p;
            return true;
        }
        return false;
    }

    bool deleteCustomer(int id) {
        if (find(id)) {
            root = deleteNode(root, id);
            return true;
        }
        return false;
    }

    void display() {
        if (!root) {
            cout << "\n +----------------------------------------------------+\n";
            cout << " |       No customers registered in system.          |\n";
            cout << " +----------------------------------------------------+\n";
            return;
        }
        cout << "\n +---------+----------------------+-----------------+\n";
        cout << " | Cust ID |        Name          |      Phone      |\n";
        cout << " +---------+----------------------+-----------------+\n";
        inorder(root);
        cout << " +---------+----------------------+-----------------+\n";
    }

    void saveToFile() {
        ofstream file("customers.csv");
        if (file.is_open()) {
            file << "ID,Name,Phone\n";
            saveToFile(root, file);
            file.close();
        }
    }

    void loadFromFile() {
        ifstream file("customers.csv");
        if (file.is_open()) {
            string line;
            bool firstLine = true;
            while (getline(file, line)) {
                if (firstLine) {
                    firstLine = false;
                    continue;
                }
                if (line.empty()) continue;
                stringstream ss(line);
                string id_str, name, phone;
                
                getline(ss, id_str, ',');
                getline(ss, name, ',');
                getline(ss, phone, ',');
                
                int id = atoi(id_str.c_str());
                
                addCustomer(id, name, phone);
            }
            file.close();
        }
    }
};

class Queue {
    QueueNode* front;
    QueueNode* rear;

public:
    Queue() {
        front = rear = NULL;
    }

    void enqueue(int r, int c, int cu, double cost, string d) {
        QueueNode* n = new QueueNode(r, c, cu, cost, d);
        if (!rear)
            front = rear = n;
        else {
            rear->next = n;
            rear = n;
        }
    }

    QueueNode* peek() {
        return front;
    }

    void dequeue() {
        if (!front) return;
        QueueNode* t = front;
        front = front->next;
        if (!front) rear = NULL;
        delete t;
    }

    bool empty() {
        return front == NULL;
    }

    void display(string type) {
        if (!front) {
            cout << "\n +----------------------------------------------------+\n";
            cout << " |       No pending " << type << " requests.                 |\n";
            cout << " +----------------------------------------------------+\n";
            return;
        }
        cout << "\n +--------+--------+----------+----------+------------+\n";
        cout << " | Req ID | Car ID | Cust ID  |   Cost   |    Date    |\n";
        cout << " +--------+--------+----------+----------+------------+\n";
        QueueNode* t = front;
        while (t) {
            cout << " | " << setw(6) << t->requestId << " | " 
                 << setw(6) << t->carId << " | " 
                 << setw(8) << t->customerId << " | $" 
                 << setw(7) << fixed << setprecision(2) << t->cost << " | " 
                 << setw(10) << t->date << " |\n";
            t = t->next;
        }
        cout << " +--------+--------+----------+----------+------------+\n";
    }

    void saveToFile(string filename) {
        ofstream file(filename.c_str());
        if (file.is_open()) {
            file << "RequestID,CarID,CustomerID,Cost,Date\n";
            QueueNode* t = front;
            while (t) {
                file << t->requestId << "," << t->carId << "," << t->customerId 
                     << "," << fixed << setprecision(2) << t->cost << "," << t->date << endl;
                t = t->next;
            }
            file.close();
        }
    }

    void loadFromFile(string filename) {
        ifstream file(filename.c_str());
        if (file.is_open()) {
            string line;
            bool firstLine = true;
            while (getline(file, line)) {
                if (firstLine) {
                    firstLine = false;
                    continue;
                }
                if (line.empty()) continue;
                stringstream ss(line);
                string req_str, car_str, cust_str, cost_str, date;
                
                getline(ss, req_str, ',');
                getline(ss, car_str, ',');
                getline(ss, cust_str, ',');
                getline(ss, cost_str, ',');
                getline(ss, date, ',');
                
                int reqId = atoi(req_str.c_str());
                int carId = atoi(car_str.c_str());
                int custId = atoi(cust_str.c_str());
                double cost = atof(cost_str.c_str());
                
                enqueue(reqId, carId, custId, cost, date);
            }
            file.close();
        }
    }
};

class Stack {
    StackNode* top;

public:
    Stack() {
        top = NULL;
    }

    void push(string d, double a, string da) {
        StackNode* n = new StackNode(d, a, da);
        n->next = top;
        top = n;
    }

    void display(string title) {
        if (!top) {
            cout << "\n +----------------------------------------------------+\n";
            cout << " |          No " << title << " records available.           |\n";
            cout << " +----------------------------------------------------+\n";
            return;
        }
        cout << "\n +------------+--------------------------+------------+\n";
        cout << " |    Date    |      Description         |   Amount   |\n";
        cout << " +------------+--------------------------+------------+\n";
        StackNode* t = top;
        double total = 0;
        while (t) {
            cout << " | " << setw(10) << t->date << " | " 
                 << setw(24) << t->description << " | $" 
                 << setw(9) << fixed << setprecision(2) << t->amount << " |\n";
            total += t->amount;
            t = t->next;
        }
        cout << " +------------+--------------------------+------------+\n";
        cout << " |                        TOTAL AMOUNT   | $" 
             << setw(9) << fixed << setprecision(2) << total << " |\n";
        cout << " +-------------------------------------------+------------+\n";
    }

    void saveToFile(string filename) {
        ofstream file(filename.c_str());
        if (file.is_open()) {
            file << "Description,Amount,Date\n";
            StackNode* t = top;
            while (t) {
                file << t->description << "," << fixed << setprecision(2) << t->amount << "," << t->date << endl;
                t = t->next;
            }
            file.close();
        }
    }

    void loadFromFile(string filename) {
        ifstream file(filename.c_str());
        if (file.is_open()) {
            string line;
            bool firstLine = true;
            while (getline(file, line)) {
                if (firstLine) {
                    firstLine = false;
                    continue;
                }
                if (line.empty()) continue;
                stringstream ss(line);
                string desc, amount_str, date;
                
                getline(ss, desc, ',');
                getline(ss, amount_str, ',');
                getline(ss, date, ',');
                
                double amount = atof(amount_str.c_str());
                
                push(desc, amount, date);
            }
            file.close();
        }
    }
};

class CarWorkshopRentalSystem {
    CarBST cars;
    CustomerBST customers;
    Queue rentalQueue;
    Queue serviceQueue;
    Stack maintenance;
    Stack revenue;

    int carId;
    int custId;
    int reqId;

    void saveCounters() {
        ofstream file("counters.csv");
        if (file.is_open()) {
            file << "CarID,CustomerID,RequestID\n";
            file << carId << "," << custId << "," << reqId << endl;
            file.close();
        }
    }

    void loadCounters() {
        ifstream file("counters.csv");
        if (file.is_open()) {
            string line;
            bool firstLine = true;
            while (getline(file, line)) {
                if (firstLine) {
                    firstLine = false;
                    continue;
                }
                if (line.empty()) continue;
                stringstream ss(line);
                string car_str, cust_str, req_str;
                
                getline(ss, car_str, ',');
                getline(ss, cust_str, ',');
                getline(ss, req_str, ',');
                
                carId = atoi(car_str.c_str());
                custId = atoi(cust_str.c_str());
                reqId = atoi(req_str.c_str());
            }
            file.close();
        }
    }

public:
    CarWorkshopRentalSystem() {
        carId = 100;
        custId = 500;
        reqId = 1;
        
        // Load all data from files
        loadCounters();
        cars.loadFromFile();
        customers.loadFromFile();
        rentalQueue.loadFromFile("rentals.csv");
        serviceQueue.loadFromFile("services.csv");
        maintenance.loadFromFile("maintenance.csv");
        revenue.loadFromFile("revenue.csv");
    }

    ~CarWorkshopRentalSystem() {
        // Save all data to files when program exits
        saveAllData();
    }

    void saveAllData() {
        saveCounters();
        cars.saveToFile();
        customers.saveToFile();
        rentalQueue.saveToFile("rentals.csv");
        serviceQueue.saveToFile("services.csv");
        maintenance.saveToFile("maintenance.csv");
        revenue.saveToFile("revenue.csv");
    }

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void header(string t) {
        cout << "\n+=========================================================+\n";
        cout << "| " << setw(55) << t << " |\n";
        cout << "+=========================================================+\n";
    }

    void pause() {
        cout << "\n Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

    void successMessage(string msg) {
        cout << "\n >> SUCCESS: " << msg << "\n";
    }

    void errorMessage(string msg) {
        cout << "\n >> ERROR: " << msg << "\n";
    }

    void addCar() {
        string b, m;
        header("ADD NEW CAR TO FLEET");
        cout << "\n Enter car details below:\n";
        cout << " -----------------------------------------\n";
        cout << " Car Brand (e.g., Toyota, Honda)  : ";
        cin >> b;
        cout << " Car Model (e.g., Corolla, Civic) : ";
        cin >> m;
        
        cars.addCar(carId, b, m);
        cout << "\n >> SUCCESS: Car added successfully! (Car ID: " << carId << ")\n";
        carId++;
        saveAllData();
        pause();
    }

    void addCustomer() {
        string n, p;
        header("REGISTER NEW CUSTOMER");
        cin.ignore();
        cout << "\n Enter customer details below:\n";
        cout << " -----------------------------------------\n";
        cout << " Full Name                        : ";
        getline(cin, n);
        cout << " Phone Number                     : ";
        cin >> p;
        
        customers.addCustomer(custId, n, p);
        cout << "\n >> SUCCESS: Customer registered successfully! (Customer ID: " << custId << ")\n";
        custId++;
        saveAllData();
        pause();
    }

    void updateCar() {
        int id;
        string b, m;
        int avail_choice;
        header("UPDATE CAR INFORMATION");
        
        cout << "\n First, view all cars:\n";
        cars.display();
        
        cout << "\n Enter Car ID to update: ";
        cin >> id;
        
        CarNode* car = cars.find(id);
        if (!car) {
            errorMessage("Car ID not found!");
            pause();
            return;
        }
        
        cout << "\n Current Car Details:\n";
        cout << " Brand: " << car->brand << "\n";
        cout << " Model: " << car->model << "\n";
        cout << " Status: " << (car->available ? "Available" : "Rented") << "\n";
        
        cout << "\n Enter new details (press Enter to keep current value):\n";
        cout << " -----------------------------------------\n";
        cin.ignore();
        cout << " New Brand: ";
        getline(cin, b);
        if (b.empty()) b = car->brand;
        
        cout << " New Model: ";
        getline(cin, m);
        if (m.empty()) m = car->model;
        
        cout << " Availability Status (1=Available, 0=Rented) [" 
             << (car->available ? "1" : "0") << "]: ";
        string avail_input;
        getline(cin, avail_input);
        bool available;
        if (avail_input.empty()) {
            available = car->available;
        } else {
            available = (avail_input == "1");
        }
        
        if (cars.updateCar(id, b, m, available)) {
            successMessage("Car information updated successfully!");
            saveAllData();
        } else {
            errorMessage("Failed to update car information!");
        }
        pause();
    }

    void deleteCar() {
        int id;
        header("DELETE CAR FROM FLEET");
        
        cout << "\n First, view all cars:\n";
        cars.display();
        
        cout << "\n Enter Car ID to delete: ";
        cin >> id;
        
        CarNode* car = cars.find(id);
        if (!car) {
            errorMessage("Car ID not found!");
            pause();
            return;
        }
        
        cout << "\n Car to be deleted:\n";
        cout << " ID: " << car->id << "\n";
        cout << " Brand: " << car->brand << "\n";
        cout << " Model: " << car->model << "\n";
        
        cout << "\n Are you sure you want to delete this car? (y/n): ";
        char confirm;
        cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            if (cars.deleteCar(id)) {
                successMessage("Car deleted successfully!");
                saveAllData();
            } else {
                errorMessage("Failed to delete car!");
            }
        } else {
            cout << "\n Deletion cancelled.\n";
        }
        pause();
    }

    void updateCustomer() {
        int id;
        string n, p;
        header("UPDATE CUSTOMER INFORMATION");
        
        cout << "\n First, view all customers:\n";
        customers.display();
        
        cout << "\n Enter Customer ID to update: ";
        cin >> id;
        
        CustomerNode* customer = customers.find(id);
        if (!customer) {
            errorMessage("Customer ID not found!");
            pause();
            return;
        }
        
        cout << "\n Current Customer Details:\n";
        cout << " Name: " << customer->name << "\n";
        cout << " Phone: " << customer->phone << "\n";
        
        cout << "\n Enter new details (press Enter to keep current value):\n";
        cout << " -----------------------------------------\n";
        cin.ignore();
        cout << " New Full Name: ";
        getline(cin, n);
        if (n.empty()) n = customer->name;
        
        cout << " New Phone Number: ";
        getline(cin, p);
        if (p.empty()) p = customer->phone;
        
        if (customers.updateCustomer(id, n, p)) {
            successMessage("Customer information updated successfully!");
            saveAllData();
        } else {
            errorMessage("Failed to update customer information!");
        }
        pause();
    }

    void deleteCustomer() {
        int id;
        header("DELETE CUSTOMER");
        
        cout << "\n First, view all customers:\n";
        customers.display();
        
        cout << "\n Enter Customer ID to delete: ";
        cin >> id;
        
        CustomerNode* customer = customers.find(id);
        if (!customer) {
            errorMessage("Customer ID not found!");
            pause();
            return;
        }
        
        cout << "\n Customer to be deleted:\n";
        cout << " ID: " << customer->id << "\n";
        cout << " Name: " << customer->name << "\n";
        cout << " Phone: " << customer->phone << "\n";
        
        cout << "\n Are you sure you want to delete this customer? (y/n): ";
        char confirm;
        cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            if (customers.deleteCustomer(id)) {
                successMessage("Customer deleted successfully!");
                saveAllData();
            } else {
                errorMessage("Failed to delete customer!");
            }
        } else {
            cout << "\n Deletion cancelled.\n";
        }
        pause();
    }

    void rentalRequest() {
        int c, cu;
        double cost;
        string d;
        header("CREATE NEW RENTAL REQUEST");
        
        cout << "\n First, let's view available cars:\n";
        cars.display();
        
        cout << "\n Now, enter rental details:\n";
        cout << " -----------------------------------------\n";
        cout << " Customer ID                      : ";
        cin >> cu;
        cout << " Car ID (from list above)         : ";
        cin >> c;
        cout << " Rental Cost ($)                  : ";
        cin >> cost;
        cout << " Rental Date (DD-MM-YYYY)         : ";
        cin >> d;

        CarNode* car = cars.find(c);
        CustomerNode* customer = customers.find(cu);
        
        if (!customer) {
            errorMessage("Customer ID not found! Please register customer first.");
        } else if (!car) {
            errorMessage("Car ID not found! Please check the car list.");
        } else if (!car->available) {
            errorMessage("This car is currently rented out!");
        } else {
            rentalQueue.enqueue(reqId++, c, cu, cost, d);
            successMessage("Rental request created successfully!");
            saveAllData();
        }
        pause();
    }

    void processRental() {
        header("PROCESS RENTAL REQUEST");
        
        if (rentalQueue.empty()) {
            errorMessage("No rental requests in queue!");
            pause();
            return;
        }
        
        cout << "\n Next rental request to process:\n";
        rentalQueue.display("rental");
        
        QueueNode* r = rentalQueue.peek();
        CarNode* car = cars.find(r->carId);
        
        cout << "\n Processing rental...\n";
        if (car) car->available = false;

        stringstream ss;
        ss << "Rental Car ID " << r->carId;
        revenue.push(ss.str(), r->cost, r->date);
        rentalQueue.dequeue();
        
        successMessage("Rental processed! Car marked as rented.");
        saveAllData();
        pause();
    }

    void serviceRequest() {
        int c, cu;
        double cost;
        string d;
        header("CREATE SERVICE REQUEST");
        
        cout << "\n View all cars in system:\n";
        cars.display();
        
        cout << "\n Enter service details:\n";
        cout << " -----------------------------------------\n";
        cout << " Customer ID                      : ";
        cin >> cu;
        cout << " Car ID (from list above)         : ";
        cin >> c;
        cout << " Service Cost ($)                 : ";
        cin >> cost;
        cout << " Service Date (DD-MM-YYYY)        : ";
        cin >> d;

        if (cars.find(c) && customers.find(cu)) {
            serviceQueue.enqueue(reqId++, c, cu, cost, d);
            successMessage("Service request created successfully!");
            saveAllData();
        } else {
            errorMessage("Invalid Car ID or Customer ID!");
        }
        pause();
    }

    void processService() {
        header("PROCESS SERVICE REQUEST");
        
        if (serviceQueue.empty()) {
            errorMessage("No service requests in queue!");
            pause();
            return;
        }
        
        cout << "\n Next service request to process:\n";
        serviceQueue.display("service");
        
        QueueNode* s = serviceQueue.peek();
        maintenance.push("Car Service", s->cost, s->date);
        revenue.push("Service Revenue", s->cost, s->date);
        serviceQueue.dequeue();
        
        successMessage("Service completed successfully!");
        saveAllData();
        pause();
    }

    void showPendingRequests() {
        header("VIEW PENDING REQUESTS");
        cout << "\n RENTAL REQUESTS:";
        rentalQueue.display("rental");
        cout << "\n\n SERVICE REQUESTS:";
        serviceQueue.display("service");
        pause();
    }

    void menu() {
        int ch;
        do {
            clearScreen();
            cout << "\n+=========================================================+\n";
            cout << "|         CAR WORKSHOP & RENTAL MANAGEMENT SYSTEM         |\n";
            cout << "+=========================================================+\n";
            cout << "\n+-----------------------------------------------------------+\n";
            cout << "|                    MAIN MENU                              |\n";
            cout << "+-----------------------------------------------------------+\n";
            cout << "|  FLEET MANAGEMENT                                         |\n";
            cout << "|   1. Add New Car to Fleet                                 |\n";
            cout << "|   2. View All Cars                                        |\n";
            cout << "|   3. Update Car Information                               |\n";
            cout << "|   4. Delete Car from Fleet                                |\n";
            cout << "|                                                           |\n";
            cout << "|  CUSTOMER MANAGEMENT                                      |\n";
            cout << "|   5. Register New Customer                                |\n";
            cout << "|   6. View All Customers                                   |\n";
            cout << "|   7. Update Customer Information                          |\n";
            cout << "|   8. Delete Customer                                      |\n";
            cout << "|                                                           |\n";
            cout << "|  RENTAL OPERATIONS                                        |\n";
            cout << "|   9. Create Rental Request                                |\n";
            cout << "|  10. Process Rental (Mark Car as Rented)                  |\n";
            cout << "|                                                           |\n";
            cout << "|  SERVICE OPERATIONS                                       |\n";
            cout << "|  11. Create Service Request                               |\n";
            cout << "|  12. Process Service (Complete Maintenance)               |\n";
            cout << "|                                                           |\n";
            cout << "|  REPORTS & RECORDS                                        |\n";
            cout << "|  13. View Pending Requests (Rental & Service)             |\n";
            cout << "|  14. View Maintenance History                             |\n";
            cout << "|  15. View Revenue Report                                  |\n";
            cout << "|                                                           |\n";
            cout << "|   0. Exit System                                          |\n";
            cout << "+-----------------------------------------------------------+\n";
            cout << "\n Enter your choice (0-15): ";
            cin >> ch;

            switch (ch) {
                case 1: addCar(); break;
                case 2: header("FLEET - ALL CARS"); cars.display(); pause(); break;
                case 3: updateCar(); break;
                case 4: deleteCar(); break;
                case 5: addCustomer(); break;
                case 6: header("ALL REGISTERED CUSTOMERS"); customers.display(); pause(); break;
                case 7: updateCustomer(); break;
                case 8: deleteCustomer(); break;
                case 9: rentalRequest(); break;
                case 10: processRental(); break;
                case 11: serviceRequest(); break;
                case 12: processService(); break;
                case 13: showPendingRequests(); break;
                case 14: header("MAINTENANCE HISTORY"); maintenance.display("maintenance"); pause(); break;
                case 15: header("REVENUE REPORT"); revenue.display("revenue"); pause(); break;
                case 0: 
                    saveAllData();
                    cout << "\n+=========================================================+\n";
                    cout << "|     Thank you for using our system! Goodbye!            |\n";
                    cout << "|            All data saved successfully!                 |\n";
                    cout << "+=========================================================+\n";
                    break;
                default: 
                    errorMessage("Invalid choice! Please enter a number between 0-15.");
                    pause();
            }
        } while (ch != 0);
    }
};

int main() {
    CarWorkshopRentalSystem system;
    system.menu();
    return 0;
}
