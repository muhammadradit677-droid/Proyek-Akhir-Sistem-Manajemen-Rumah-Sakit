#include <iostream>
#include <string>
using namespace std;

// ====================================================================
// 1. CLASS PATIENT (BASE CLASS
// ====================================================================
class Patient {
private:
    int patientID;
    string name;
    int age;
    string disease;
    int priority;

public:
    // Constructor
    Patient() {
        patientID = 0;
        name = "";
        age = 0;
        disease = "";
        priority = 0;
    }
    
    Patient (int id, string n, int a, string d, int p) {
        patientID = id;
        name = n;
        age = a;
        disease = d;
        priority = p;
    }
    
    // Getter functions
    int getPatientID() { return patientID; }
    string getName() { return name; }
    int getAge() { return age; }
    string getDisease() { return disease; }
    int getPriority() { return priority; }
    
    // Setter
    void setPatientID(int id) { patientID = id; }
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setDisease(string d) { disease = d; }
    void setPriority(int p) { priority = p; }

    // Virtual function untuk Runtime Polymorphism (Tugas Orang 2)
    virtual void displayInfo() {
        cout << "======== Patient Information =======" << endl;
        cout << "Patient ID: " << patientID << endl;
        cout << "Name: " << name << endl; 
        cout << "Age: " << age << endl;
        cout << "Disease: " << disease << endl;
        cout << "Priority: " << priority << endl;
        cout << "===================================" << endl;
    }
};

// ====================================================================
// 2. INHERITANCE & POLYMORPH2)
// ====================================================================
// Kelas turunan dari Patient untuk menangani janji temu spesifik (Appointment)
class Appointment : public Patient {
private:
    string doctorName;
    string appointmentTime;

public:
    Appointment() : Patient() {
        doctorName = "";
        appointmentTime = "";
    }

    Appointment(int id, string n, int a, string d, int p, string doc, string time) 
        : Patient(id, n, a, d, p) {
        doctorName = doc;
        appointmentTime = time;
    }

    string getDoctorName() { return doctorName; }
    string getAppointmentTime() { return appointmentTime; }

    // Override fungsi virtual displayInfo() dari Base Class
    void displayInfo() override {
        cout << "======== Appointment Details =======" << endl;
        cout << "Appointment ID : " << getPatientID() << endl;
        cout << "Patient Name   : " << getName() << endl;
        cout << "Age            : " << getAge() << " years old" << endl;
        cout << "Symptom/Disease: " << getDisease() << endl;
        cout << "Assigned Doctor: Dr. " << doctorName << endl;
        cout << "Schedule Time  : " << appointmentTime << endl;
        cout << "Priority Level : " << getPriority() << endl;
        cout << "====================================" << endl;
    }
};

// ====================================================================
// 3. STRUCT NODE & DOUBLY LINKED LIST
// ====================================================================
// Node menyimpan objek Appointment agar membawa properti Orang 2
struct node {
    Appointment data; 
    node* next;
    node* prev;
};

class PatientLinkedList {
private:
    node* head;
    node* tail;

public:
    PatientLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // Fitur Orang 1: insertAtEnd
    void insertEnd(Appointment p) {
        node* newNode = new node();
        newNode->data = p;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "Patient appointment inserted successfully." << endl;
    }

    // Fitur Orang 2: Queue Dequeue (Serve Next Patient / Doctor System)
    // Ditaruh di dalam class agar bisa mengakses variabel 'head' & 'tail'
    void serveNextPatient() {
        if (head == nullptr) {
            cout << "No patients in queue to serve." << endl;
            return;
        }
        cout << "\n>>> Serving Next Patient (Doctor System) <<<" << endl;
        head->data.displayInfo(); // Memanggil displayInfo() hasil override polimorfisme

        node* temp = head;
        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        cout << "Patient has been successfully treated and removed from queue." << endl;
    }

    // Fitur Orang 1: displayForward
    void displayForward() {
        if (head == nullptr) {
            cout << "No patients data available." << endl;
            return;
        }
        node* temp = head;
        while (temp != nullptr) {
            temp->data.displayInfo();
            temp = temp->next;
        }
    }

    // Fitur Orang 1: displayBackward
    void displayBackward() {
        if (tail == nullptr) {
            cout << "No patients data available." << endl;
            return;
        }
        node* temp = tail;
        while (temp != nullptr) {
            temp->data.displayInfo();
            temp = temp->prev;
        }
    }

    // Fitur Orang 1: deleteByID
    void deletePatient(int id) {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        node* temp = head;
        while (temp != nullptr) {
            if (temp->data.getPatientID() == id) {
                if (temp == head) {
                    head = head->next;
                    if (head != nullptr)
                        head->prev = nullptr;
                }
                else if (temp == tail) {
                    tail = tail->prev; 
                    if (tail != nullptr)
                        tail->next = nullptr;
                }
                else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }
                
                delete temp;
                cout << "Patient deleted successfully." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Patient not found!" << endl;
    }   

    // Fitur Orang 1: Linear search by name
    void searchByName(string name) {
        if (head == nullptr) {
            cout << "No patients data available." << endl;
            return;
        }

        node* temp = head;
        bool found = false;
        while (temp != nullptr) {
            if (temp->data.getName() == name) {
                cout << "Patient found!" << endl;
                temp->data.displayInfo();
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "Patient not found!" << endl;
        }
    }

    // Fitur Orang 1: Search By ID
    void searchByID(int id) {
        if (head == nullptr) {
            cout << "No patients data available." << endl;
            return;
        }

        node* temp = head;
        while (temp != nullptr) {
            if (temp->data.getPatientID() == id) {
                cout << "Patient found!" << endl;
                temp->data.displayInfo();
                return;
            }
            temp = temp->next;
        }
        cout << "Patient not found!" << endl;
    }
    
    // Fitur Orang 1: Bubble sort Priority Descending
    void bubbbleSortPriority() {
        if (head == nullptr) {
            cout << "No patients data available." << endl;
            return;
        }

        bool swapped;
        do {
            swapped = false;
            node* current = head;

            while (current->next != nullptr) {
                if (current->data.getPriority() < current->next->data.getPriority()) 
                {
                    swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        cout << "Patients sorted by priority successfully." << endl;
    }

    // Fitur Orang 1: Merge Sort Helper
    node* split(node* headRef) {
        node* fast = headRef;
        node* slow = headRef;

        while (fast->next != nullptr && fast->next->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }

        node* temp = slow->next;
        slow->next = nullptr;
        return temp;
    }

    // Fitur Orang 1: Merge function
    node* merge(node* first, node* second) {
        if (!first) return second;
        if (!second) return first;
        if (first->data.getName() < second->data.getName()) {
            first->next = merge(first->next, second);
            first->next->prev = first;
            first->prev = nullptr;
            return first;
        }
        else {
            second->next = merge(first, second->next);
            second->next->prev = second;
            second->prev = nullptr;
            return second;
        }
    }

    // Fitur Orang 1: Merge Sort
    node* mergeSort(node* headRef) {
        if (headRef == nullptr || headRef->next == nullptr) 
            return headRef;
        
        node* second = split(headRef);
        headRef = mergeSort(headRef);
        second = mergeSort(second);

        return merge(headRef, second);
    }

    // Fitur Orang 1: Sort Name Ascending
    void sortByName() {
        head = mergeSort(head);
        node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        tail = temp;
        cout << "Patients sorted by name successfully." << endl;
    }
};

// ====================================================================
// 4. LOGIN SYSTEM INTERFACE (Tugas Orang 2)
// ====================================================================
bool loginSystem() {
    string username, password;
    cout << "\n==========================================" << endl;
    cout << "     LOGIN PORTAL SISTEM RUMAH SAKIT " << endl;
    cout << "==========================================" << endl;
    cout << "Username (Petunjuk: admin/doctor): ";
    cin >> username;
    cout << "Password (Petunjuk: 1234)        : ";
    cin >> password;

    if ((username == "admin" || username == "doctor") && password == "1234") {
        cout << "\nLogin Berhasil! Selamat Datang, " << username << ".\n" << endl;
        return true;
    } else {
        cout << "\n[ERROR] Kredensial Tidak Valid! Akses Ditolak.\n" << endl;
        return false;
    }
}

// ====================================================================
// 5. MAIN MENU INTEGRASI
// ====================================================================
int main() {
    PatientLinkedList hospital;
    int choice;
    int idCounter = 1001;

    // Gerbang Login Orang 2 sebelum masuk program utama
    while (!loginSystem()) {
        cout << "Silakan coba lagi..." << endl;
    }

    do {
        cout << "\n===== Hospital Patient Management System =====" << endl;
        cout << "1. Add Patient / Create Appointment" << endl;
        cout << "2. Display Patients (Forward)" << endl;
        cout << "3. Display Patients (Backward)" << endl;
        cout << "4. Delete Patient by ID" << endl;
        cout << "5. Search Patient by Name" << endl;
        cout << "6. Search Patient by ID" << endl;
        cout << "7. Sort Patients by Priority (Descending)" << endl;
        cout << "8. Sort Patients by Name (Ascending)" << endl;
        cout << "9. [Doctor System] Serve/Treat Next Patient (Queue)" << endl;
        cout << "10. Exit" << endl;
        cout << "Choose an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        cin.ignore();

        switch (choice) {
            case 1: {
                string name, disease, doctor, time;
                int age, priority;

                cout << "Enter patient name: ";
                getline(cin, name);

                cout << "Enter patient age: ";
                cin >> age;
                cin.ignore();

                cout << "Enter patient disease: ";
                getline(cin, disease);
                
                cout << "Enter designated Doctor Name: ";
                getline(cin, doctor);
                
                cout << "Enter appointment time (e.g., 10:00 AM): ";
                getline(cin, time);

                cout << "Enter patient priority (1-5): ";
                cin >> priority;

                // Memakai class anak 'Appointment' (Inheritance Orang 2)
                Appointment p(idCounter, name, age, disease, priority, doctor, time);
                hospital.insertEnd(p);

                idCounter++;
                break;
            }
            case 2:
                hospital.displayForward();
                break;
            case 3:
                hospital.displayBackward();
                break;
            case 4: {
                int id;
                cout << "Enter patient ID to delete: ";
                cin >> id;
                hospital.deletePatient(id);
                break;
            }
            case 5: {
                string name;
                cout << "Enter patient name to search: ";
                getline(cin, name);
                hospital.searchByName(name);
                break;
            }
            case 6: {
                int id;
                cout << "Enter patient ID to search: ";
                cin >> id;
                hospital.searchByID(id);
                break;
            }
            case 7:
                hospital.bubbbleSortPriority();
                break;
            case 8:
                hospital.sortByName();
                break;
            case 9:
                hospital.serveNextPatient(); // Fitur Queue Doctor System (Orang 2)
                break;
            case 10:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (choice != 10);

    return 0;
}