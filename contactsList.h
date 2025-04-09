//
// Created by Lisa Dion on 6/8/23.
//

#ifndef PROJECT4_CONTACTSLIST_H
#define PROJECT4_CONTACTSLIST_H
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using std::cout, std::endl, std::function, std::ifstream, std::left, std::setw, std::string, std::vector;

struct contact {
    string first;
    string last;

    // Constructors
    contact() : first("First"), last("Last") {}
    contact(string f, string l) : first(f), last(l) {}

    // Overloaded comparison operators, sorting by last name
    friend bool operator == (const contact& left, const contact& right) {
        return left.last == right.last;
    }

    friend bool operator <= (const contact& left, const contact& right) {
        return left.last <= right.last;
    }

    friend bool operator >= (const contact& left, const contact& right) {
        return left.last >= right.last;
    }

    friend bool operator < (const contact& left, const contact& right) {
        return left.last < right.last;
    }

    friend bool operator > (const contact& left, const contact& right) {
        return left.last > right.last;
    }

    friend bool operator != (const contact& left, const contact& right) {
        return left.last != right.last;
    }
};

class ContactsList {
private:
    vector<contact> contacts;

public:
    // Default constructor
    ContactsList() {
        contacts.clear();
    }

    // Read info from file
    // Assuming file has two columns for first and last name
    void readContactsFromFile(string filename) {
        ifstream inFile(filename);
        string header;
        getline(inFile, header);

        string first, last;
        while (inFile && inFile.peek() != EOF) {
            getline(inFile, first, ',');
            getline(inFile, last);
            contacts.emplace_back(first, last);
        }
        inFile.close();
    }

    // Print contacts to screen
    void printList() const {
        cout << left << setw(10) << "First" << "Last" << endl;
        for (const contact &c : contacts) {
            cout << setw(10) << c.first << c.last << endl;
        }
    }

    void sortAndPrint(function<vector<contact>(vector<contact>, unsigned long&, unsigned long&)> sortingFunction) {
        unsigned long a, b;
        vector<contact> sortedList = sortingFunction(contacts, a, b);

        cout << left << setw(10) << "First" << "Last" << endl;
        for (const contact &c : sortedList) {
            cout << setw(10) << c.first << c.last << endl;
        }
    }
};

#endif //PROJECT4_CONTACTSLIST_H
