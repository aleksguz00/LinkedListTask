#include <iostream>

template <class T>
class Element {
public:
    T data;
    Element* next;

    Element(const T& value) : data{ value }, next{ nullptr } {}
};

template <class T>
class LinkedList {
public:
    LinkedList() : head{ nullptr }, size{ 0 } {}
    ~LinkedList() {
        Element<T>* current = head;

        while (current) {
            Element<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    void InsertFront(const T& value) {
        Element<T>* newElement = new Element<T>{ value };
        newElement->next = head;
        head = newElement;

        ++size;
    }

    void InsertBack(const T& value) {
        Element<T>* newElement = new Element<T>{ value };

        if (head == nullptr) {
            head = newElement;
        }
        else {
            Element<T>* current = head;

            while(current->next) {
                current = current->next;
            }
            current->next = newElement;
        }

        ++size;
    }

    bool Find(const T& value) {
        Element<T>* current = head;

        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Тут не делаю провеку на пустоту списка, потому что в случае,
    // если список пустой, удаление прервётся в начале цилка, 
    // так как, в пустом списке у нас head == nullptr
    void Remove(const T& value) {
        Element<T>* current = head;
        Element<T>* previous = nullptr;

        while (current) {
            if (current->data == value) {
                // Проверяю, есть ли элементы перед удаляемым, если есть, перекидываю указатели
                if (previous) {
                    previous->next = current->next;
                }
                else {
                    head = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
            --size;
        }
    }

    size_t Size() {
        return size;
    }

    void PrintList() {
        Element<T>* current = head;

        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Мог бы реализвать через дружественную функцию,
    // чтобы можно было в любом порядке использовать операцию +=, но думаю, нет смысла
    // я думаю, что операция 5 += list выглядела бы странно
    // вставляет элемент в конец
    void operator+=(const T& value) {
        this->InsertBack(value);
    }

private:
    Element<T>* head;
    size_t size;
};

int main() {
    LinkedList<int> list;

    list.InsertFront(1);
    list.InsertFront(2);
    list.InsertFront(3);

    list.PrintList();
    std::cout << "Size: " << list.Size() << std::endl;

    int number;

    std::cout << "Enter number to find: ";
    std::cin >> number;

    if (list.Find(number)) {
        std::cout << "Number " << number << " was found at list\n";
    }
    else {
        std::cout << "Number " << number << "wasn't found at list\n";
    }

    list.Remove(2);
    list.PrintList();
    std::cout << "Size: " << list.Size() << std::endl;

    list.InsertFront(10);
    list.PrintList();
    std::cout << "Size: " << list.Size() << std::endl;

    list += 5;
    list.PrintList();
    std::cout << "Size: " << list.Size() << std::endl;

    list.InsertBack(777);
    list.PrintList();
    std::cout << "Size: " << list.Size() << std::endl;
}
