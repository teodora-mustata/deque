#include <iostream>
#include "deque.h"

int main() 
{
    deque<int> dq;
    int choice;
    int element, index;

    while (true) {
        std::cout << "\n--- Deque Menu ---\n";
        std::cout << "1. Push back\n";
        std::cout << "2. Push front\n";
        std::cout << "3. Pop back\n";
        std::cout << "4. Pop front\n";
        std::cout << "5. Get size\n";
        std::cout << "6. Check if empty\n";
        std::cout << "7. Access element by index\n";
        std::cout << "8. Access front element\n";
        std::cout << "9. Access back element\n";
        std::cout << "10. Clear deque\n";
        std::cout << "11. Insert element at position\n";
        std::cout << "12. Delete element at position\n";
        std::cout << "13. Display\n";
        std::cout << "14. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter element to push back: ";
            std::cin >> element;
            dq.push_back(element);
            std::cout << "Element pushed back.\n";
            break;
        case 2:
            std::cout << "Enter element to push front: ";
            std::cin >> element;
            dq.push_front(element);
            std::cout << "Element pushed front.\n";
            break;
        case 3:
            try {
                dq.pop_back();
                std::cout << "Element popped back.\n";
            }
            catch (const std::out_of_range& e) {
                std::cout << e.what() << "\n";
            }
            break;
        case 4:
            try {
                dq.pop_front();
                std::cout << "Element popped front.\n";
            }
            catch (const std::out_of_range& e) {
                std::cout << e.what() << "\n";
            }
            break;
        case 5:
            std::cout << "Size of deque: " << dq.size() << "\n";
            break;
        case 6:
            std::cout << "Deque is " << (dq.empty() ? "empty.\n" : "not empty.\n");
            break;
        case 7:
            std::cout << "Enter index to access: ";
            std::cin >> index;
            try {
                std::cout << "Element at index " << index << ": " << dq[index] << "\n";
            }
            catch (const std::out_of_range& e) {
                std::cout << e.what() << "\n";
            }
            break;
        case 8:
            try {
                std::cout << "Front element: " << dq.front() << "\n";
            }
            catch (const std::out_of_range& e) {
                std::cout << e.what() << "\n";
            }
            break;
        case 9:
            try {
                std::cout << "Back element: " << dq.back() << "\n";
            }
            catch (const std::out_of_range& e) {
                std::cout << e.what() << "\n";
            }
            break;
        case 10:
            dq.clear();
            std::cout << "Deque cleared.\n";
            break;
        case 11:
            std::cout << "Enter element to insert: ";
            std::cin >> element;
            std::cout << "Enter position to insert: ";
            std::cin >> index;
            try {
                dq.insert(element, index);
                std::cout << "Element inserted.\n";
            }
            catch (const std::out_of_range& e) {
                std::cout << e.what() << "\n";
            }
            break;
        case 12:
            std::cout << "Enter position to delete: ";
            std::cin >> index;
            try {
                dq.delete_element(index);
                std::cout << "Element deleted.\n";
            }
            catch (const std::out_of_range& e) {
                std::cout << e.what() << "\n";
            }
            break;
        case 13:
            dq.display();
            dq.resetblockCnt();
            break;
        case 14:
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
