class FrequencyMap {
private:
    struct Node {
        char key;
        int frequency;
        Node* next;
        
        Node(char k) : key(k), frequency(0), next(nullptr) {}
    };
    
    Node* head;
    
public:
    FrequencyMap() : head(nullptr) {}
    
    void insert(char key) {
        if (head == nullptr) {
            head = new Node(key);
            head->frequency = 1;
            return;
        }
        
        Node* current = head;
        while (current->next != nullptr && current->key != key) {
            current = current->next;
        }
        
        if (current->key == key) {
            current->frequency++;
        } else {
            Node* newNode = new Node(key);
            newNode->frequency = 1;
            current->next = newNode;
        }
    }

    int getSize() {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
    
    int getFrequency(char key) {
        Node* current = head;
        while (current != nullptr && current->key != key) {
            current = current->next;
        }
        
        if (current != nullptr) {
            return current->frequency;
        }
        
        return 0;
    }

    void getCharFrequencyArrays(char*& charArray, int*& freqArray) {
        int size = getSize();
        
        charArray = new char[size];
        freqArray = new int[size];
        
        Node* current = head;
        int index = 0;
        while (current != nullptr) {
            charArray[index] = current->key;
            freqArray[index] = current->frequency;
            current = current->next;
            index++;
        }
    }
};