#include <iostream>
#include <vector>

using namespace std;

class Client {
private:
    string accountNumber;
    int pin;
    double balance;

public:
    Client(string accNum, int pin, double balance) : accountNumber(accNum), pin(pin), balance(balance) {}

    string getAccountNumber() const {
        return accountNumber;
    }

    int getPin() const {
        return pin;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }
};

class Bank {
private:
    vector<Client>clients;

public:
    Bank() {}

    void addClient(const Client& client) {
        clients.push_back(client);
    }

    Client* getClient(const string& accountNumber, int pin) {
        for (auto& client : clients) {
            if (client.getAccountNumber() == accountNumber && client.getPin() == pin) {
                return &client;
            }
        }
        return nullptr;
    }
};

class Bankomat {
private:
    Bank& bank;
    double cash;

public:
    Bankomat(Bank& bank, double cash) : bank(bank), cash(cash) {}
    void checkBalance(const string& accountNumber, int pin) {
        Client* client = bank.getClient(accountNumber, pin);
        if (client) {
            cout << "Twoj stan konta wynosi: " << client->getBalance() << "zl" << endl;
        }
        else {
            cout << "BLAD" << endl;
        }
    }
    void deposit(const string& accountNumber, int pin, double amount) {
        Client* client = bank.getClient(accountNumber, pin);
        if (client) {
            client->deposit(amount);
            cash += amount;
            cout << "Wplacono." << endl;
        }
        else {
            cout << "BLAD." << endl;
        }
    }
    void withdraw(const string& accountNumber, int pin, double amount) {
        Client* client = bank.getClient(accountNumber, pin);
        if (client) {
            if (client->withdraw(amount)) {
                cash -= amount;
                cout << "Wyplacono." << endl;
            }
            else {
                cout << "Brak srodkow." << endl;
            }
        }
        else {
            cout << "BLAD" << endl;
        }
    }
    void displayCash() {
        cout << "Pieniadze w bankomacie : " << cash << endl;
    }
};

int main()
{
    Client Robert("123456789", 5555, 1000.0);
    Client Marcin("987654321", 3333, 10000.0);
    Bank bank;
    bank.addClient(Robert);
    bank.addClient(Marcin);

    Bankomat bankomat(bank, 5000);
    string numberKonta;
    int pin;

    cout << "Zaloguj sie!" << endl;
    bool logged = false;
    do {
        cout << "Podaj numer karty : ";
        cin >> numberKonta;
        cout << "Podaj PIN : ";
        cin >> pin;

        Client* client = bank.getClient(numberKonta, pin);
        if (client) {
            cout << "Zalogowano!" << endl;
            logged = true;
        }
        else {
            cout << "Bledny numer karty lub PIN ! Sprobuj ponownie" << endl;
        }
    } while (!logged);

    int wybor;
    double amount;

    do {
        cout << "\nMENU:" << endl;
        cout << "1. Stan Konta" << endl;
        cout << "2. Wplac" << endl;
        cout << "3. Wyplac" << endl;
        cout << "4. Wyjdz" << endl;
        cout << "Wybierz numer : " << endl;
        cin >> wybor;
        switch (wybor) {
        case 1:
            bankomat.checkBalance(numberKonta, pin);
            break;
        case 2:
            cout << "Podaj kwote do wplacenia: ";
            cin >> amount;
            bankomat.deposit(numberKonta, pin, amount);
            break;
        case 3:
            cout << "Podaj kwote do wyplacenia: ";
            cin >> amount;
            bankomat.withdraw(numberKonta, pin, amount);
            break;
        case 4:
            cout << "Wychodzenie!" << endl;
            break;
        default:
            cout << "Nie ma takiej operacji!" << endl;
        }
    } while (wybor != 4);

    return 0;
}

