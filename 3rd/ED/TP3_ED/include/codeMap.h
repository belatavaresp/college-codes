#include <string>
using std::string;

class CodeMap {
private:
    struct Node {
        char key;
        std::string code;
        Node* next;
        
        Node(char k) : key(k), next(nullptr) {}
    };
    
    Node* head;
    int size;
    
public:
    CodeMap() : head(nullptr), size(0) {}
    
    void insert(char key, const std::string& code) {
        if (head == nullptr) {
            head = new Node(key);
            head->code = code;
            size = 1;
            return;
        }
        
        Node* current = head;
        while (current->next != nullptr && current->key != key) {
            current = current->next;
        }
        
        if (current->key == key) {
            current->code = code;
        } else {
            Node* newNode = new Node(key);
            newNode->code = code;
            current->next = newNode;
            size++;
        }
    }
    
    string getCode(char key) {
        Node* current = head;
        while (current != nullptr && current->key != key) {
            current = current->next;
        }
        
        if (current != nullptr) {
            return current->code;
        }
        
        return "";
    }

    string& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        
        return current->code;
    }

    string getAllCodes() {
        std::string allCodes;
        Node* current = head;
        
        while (current != nullptr) {
            allCodes += current->code;
            current = current->next;
        }
        
        return allCodes;
    }
};