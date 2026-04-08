#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// User class
class User {
public:
    string username, password;

    void signup() {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        ofstream file("users.txt", ios::app);
        file << username << " " << password << endl;
        file.close();

        cout << "Signup Successful!\n";
    }

    bool login() {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        ifstream file("users.txt");
        string u, p;

        while (file >> u >> p) {
            if (u == username && p == password) {
                cout << "Login Successful!\n";
                return true;
            }
        }

        cout << "Invalid Credentials!\n";
        return false;
    }
};

// MENU CLASS
class Menu {
public:
    vector<string> items = {"Pizza", "Burger", "Pasta", "Sandwich", "Momos", "Chilly Potato", "Garlic Bread", "Cold Drink"};
    vector<int> prices = {200, 100, 150, 80, 50, 100, 120, 90};

    void displayMenu() {
        cout << "\n------ MENU ------\n";
        for (int i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i] << " - Rs." << prices[i] << endl;
        }
    }
};

// ORDER CLASS
class Order {
public:
    vector<string> cart;
    vector<int> cost;
    vector<int> quantity;
    int total = 0;

    void addItem(Menu &menu) {
        int choice, qty;
        cout << "Enter item number to add: ";
        cin >> choice;

        if (choice >= 1 && choice <= menu.items.size()) {
            cout << "Enter quantity: ";
            cin >> qty;

            cart.push_back(menu.items[choice - 1]);
            cost.push_back(menu.prices[choice - 1]);
            quantity.push_back(qty);

            total += menu.prices[choice - 1] * qty;

            cout << "Item added to cart!\n";
        } else {
            cout << "Invalid choice!\n";
        }
    }

    void showCart() {
        cout << "\n------ CART ------\n";
        for (int i = 0; i < cart.size(); i++) {
            cout << i + 1 << ". " << cart[i] 
                 << " | Qty: " << quantity[i]
                 << " | Price: Rs." << cost[i]
                 << " | Total: Rs." << cost[i] * quantity[i] << endl;
        }
        cout << "Total Bill: Rs." << total << endl;
    }

    void removeItem() {
        if (cart.empty()) {
            cout << "Cart is empty!\n";
            return;
        }

        showCart();
        int index;
        cout << "Enter item number to remove: ";
        cin >> index;

        if (index >= 1 && index <= cart.size()) {
            int i = index - 1;

            total -= cost[i] * quantity[i];

            cart.erase(cart.begin() + i);
            cost.erase(cost.begin() + i);
            quantity.erase(quantity.begin() + i);

            cout << "Item removed successfully!\n";
        } else {
            cout << "Invalid choice!\n";
        }
    }

    void placeOrder(string username) {
        ofstream file("orders.txt", ios::app);

        file << "User: " << username << endl;
        for (int i = 0; i < cart.size(); i++) {
            file << cart[i] 
                 << " | Qty: " << quantity[i]
                 << " | Rs." << cost[i] * quantity[i] << endl;
        }
        file << "Total: Rs." << total << endl;
        file << "----------------------\n";

        file.close();

        cout << "\nOrder Placed Successfully!\n";
    }
};

int main() {
    User user;
    Menu menu;
    Order order;

    int choice;

    cout << "1. Signup\n2. Login\nChoice: ";
    cin >> choice;

    if (choice == 1) {
        user.signup();
    }

    if (choice == 2) {
        if (!user.login()) return 0;
    }

    int option;
    do {
        cout << "\n1. View Menu\n2. Add Item\n3. View Cart\n4. Remove Item\n5. Place Order\n6. Exit\nChoice: ";
        cin >> option;

        switch (option) {
        case 1:
            menu.displayMenu();
            break;
        case 2:
            menu.displayMenu();
            order.addItem(menu);
            break;
        case 3:
            order.showCart();
            break;
        case 4:
            order.removeItem();
            break;
        case 5:
            order.placeOrder(user.username);
            break;
        case 6:
            cout << "Thank you!\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (option != 6);

    return 0;
}
