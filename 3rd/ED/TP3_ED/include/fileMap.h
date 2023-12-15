#include <string>
#include "minHeap.h"

class FileMap {
private:
    struct Node {
        std::string key;
        MinHeapNode* value;
        Node* next;
        
        Node(const std::string& k, MinHeapNode* v) : key(k), value(v), next(nullptr) {}
    };
    
    Node* head;
    
public:
    FileMap() : head(nullptr) {}
    
    void insert(const std::string& key, MinHeapNode* value) {
        if (head == nullptr) {
            head = new Node(key, value);
            return;
        }
        
        Node* current = head;
        while (current->next != nullptr && current->key != key) {
            current = current->next;
        }
        
        if (current->key == key) {
            current->value = value;
        } else {
            Node* newNode = new Node(key, value);
            current->next = newNode;
        }
    }
    
    MinHeapNode* getValue(const std::string& key) {
        Node* current = head;
        while (current != nullptr && current->key != key) {
            current = current->next;
        }
        
        if (current != nullptr) {
            return current->value;
        }
        
        return nullptr;
    }
};