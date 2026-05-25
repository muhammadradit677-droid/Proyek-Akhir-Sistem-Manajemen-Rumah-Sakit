#include <iostream>
#include <string>
using namespace std;
//Buatkan class C++ bernama Patient menggunakan prinsip OOP.
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
    int getPatientID() {
        return patientID;
    }
    string getName() {
        return name;
    }
    int getAge() {
        return age;
    }
    string getDisease() {
        return disease;
    }
    int getPriority() {
        return priority;
    }
    
    //Setter
    void setPatientID(int id) {
        patientID = id;
    }
    void setName(string n) {
        name = n;
    }
    void setAge(int a) {
        age = a;
    }
    void setDisease(string d) {
        disease = d;
    }
    void setPriority(int p) {
        priority = p;
    }

    // Virtual function
    virtual void displayInfo() {
        cout << "======== Patient Information =======" << endl;
        cout << "Patient ID: " << patientID << endl;
        cout << "Name:" << name << endl; 
        cout << "Age: " << age << endl;
        cout << "Disease: " << disease << endl;
        cout << "===================================" << endl;
    }
};
//Buat implementasi Doubly Linked List manual di C++ tanpa menggunakan std::list atau std::vector.

//Ketentuan:
//- Node menyimpan object Patient
struct node {
    Patient data;
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

//- Fitur:
  //- insertAtEnd
    void insertEnd(Patient p) {
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

        cout << "Patient inserted successfully." << endl;

    }
   //- displayForward
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
    // displayBackward
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

  //- deleteByID
    void deletePatient(int id) {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        node* temp = head;
        while (temp != nullptr) {
            if (temp->data.getPatientID() == id) {
               // Jike node pertama
                if (temp == head) {
                    head = head->next;

                    if (head != nullptr)
                        head->prev = nullptr;
                }
                // Jika node terakhir
                else if (temp == tail) {
                    tail = tail->prev; 

                    if (tail != nullptr)
                        tail->next = nullptr;
                }
                // Jika node di tengah
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


// Linear search by name
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
// Search By ID
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
    
// Bubble sort Priority Descending
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

// Merge Sort Helper
    node* split(node* headRef) {

        node* fast = headRef;
        node* slow = headRef;

        while (fast->next != nullptr && fast->next->next != nullptr) 
        {
            fast = fast->next->next;
            slow = slow->next;

        }

        node* temp = slow->next;
        slow->next = nullptr;

        return temp;
    }
//Merge function
    node* merge(node* first, node* second) {

        if (!first) return second;
        if (!second) return first;
        if (first->data.getName() < second->data.getName()) 
        {
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
// Merge Sort
    node* mergeSort(node* headRef) {
        if (headRef == nullptr || headRef->next == nullptr) 
            return headRef;
        
        node* second = split(headRef);
        headRef = mergeSort(headRef);
        second = mergeSort(second);

        return merge(headRef, second);
    }
//Sort Name Ascending
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

int main() {
    PatientLinkedList hospital;

    int choice;
    int idCounter = 1001;

    do {

        cout << "===== Hospital Patient Management System =====" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Display Patients (Forward)" << endl;
        cout << "3. Display Patients (Backward)" << endl;
        cout << "4. Delete Patient by ID" << endl;
        cout << "5. Search Patient by Name" << endl;
        cout << "6. Search Patient by ID" << endl;
        cout << "7. Sort Patients by Priority (Descending)" << endl;
        cout << "8. Sort Patients by Name (Ascending)" << endl;
        cout << "9. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        cin.ignore();

        switch (choice) {
            case 1: {
                string name;
                int age;
                string disease;
                int priority;

                cout << "Enter patient name: ";
                getline(cin, name);

                cout << "Enter patient age: ";
                cin >> age;
                cin.ignore();

                cout << "Enter patient disease: ";
                getline(cin, disease);

                cout << "Enter patient priority (1-5): ";
                cin >> priority;

                Patient p(idCounter, name, age, disease, priority);
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
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
