#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

struct book {
    string title;
    string author;
    string genre;
    bool availability;
    string separator;
};

void ReadData(vector<book>& Books) {
    ifstream file_in("abcd.txt");
    if (!file_in) {
        cerr << "Could not open the file." << endl;
        return;
    }

    book LibraryBook;
    while (getline(file_in, LibraryBook.title)) {
        getline(file_in, LibraryBook.author);
        getline(file_in, LibraryBook.genre);
        file_in >> LibraryBook.availability;
        file_in.ignore(); // Ignore newline after availability
        getline(file_in, LibraryBook.separator);

        Books.push_back(LibraryBook);
    }

    file_in.close();
    cout << "Books loaded successfully." << endl;
}

void writeData(const vector<book>& Books) {
    ofstream file_out("abcd.txt");
    if (!file_out) {
        cerr << "Could not open the file for writing." << endl;
        return;
    }

    for (const auto& LibraryBook : Books) {
        file_out << LibraryBook.title << endl;
        file_out << LibraryBook.author << endl;
        file_out << LibraryBook.genre << endl;
        file_out << LibraryBook.availability << endl;
        file_out << LibraryBook.separator << endl;
    }

    file_out.close();
    cout << "Books saved successfully." << endl;
}

void addBook(vector<book>& Books) {
    book LibraryBook;
    cin.ignore();
    cout << "Enter Book title: ";
    getline(cin, LibraryBook.title);

    cout << "Enter Book author: ";
    getline(cin, LibraryBook.author);

    cout << "Enter Book genre: ";
    getline(cin, LibraryBook.genre);

    LibraryBook.availability = true;
    LibraryBook.separator = "---";

    Books.push_back(LibraryBook);
    writeData(Books); // Save changes to the file
    cout << "Book added successfully!" << endl;
}

void RemoveBook(vector<book>& Books) {
    string TitletoRemove;
    cin.ignore();
    cout << "Enter the title you want to remove: ";
    getline(cin, TitletoRemove);

    bool found = false;
    for (auto it = Books.begin(); it != Books.end(); ++it) {
        if (it->title == TitletoRemove) {
            Books.erase(it);
            writeData(Books); // Save changes to the file
            cout << "Book \"" << TitletoRemove << "\" removed successfully.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No book found with the title \"" << TitletoRemove << "\".\n";
    }
}

void searchTitle(vector<book>& Books) {
    cin.ignore();
    string titleToSearch;
    cout << "Enter title to search: ";
    getline(cin, titleToSearch);

    bool found = false;
    for (const auto& LibraryBook : Books) {
        if (LibraryBook.title == titleToSearch) {
            found = true;
            cout << "\nTitle: " << LibraryBook.title << endl;
            cout << "Author: " << LibraryBook.author << endl;
            cout << "Genre: " << LibraryBook.genre << endl;
            cout << "Availability: " << (LibraryBook.availability ? "Available" : "Not Available") << endl;
            cout << LibraryBook.separator << endl;
        }
    }
    if (!found) {
        cout << "No book found with the title \"" << titleToSearch << "\".\n";
    }
}

void searchAuthors(vector<book>& Books) {
    cin.ignore();
    string authorToSearch;
    cout << "Enter author to search: ";
    getline(cin, authorToSearch);

    bool found = false;
    for (const auto& LibraryBook : Books) {
        if (LibraryBook.author == authorToSearch) {
            found = true;
            cout << "\nTitle: " << LibraryBook.title << endl;
            cout << "Author: " << LibraryBook.author << endl;
            cout << "Genre: " << LibraryBook.genre << endl;
            cout << "Availability: " << (LibraryBook.availability ? "Available" : "Not Available") << endl;
            cout << LibraryBook.separator << endl;
        }
    }
    if (!found) {
        cout << "No books found by the author \"" << authorToSearch << "\".\n";
    }
}

void searchGenres(vector<book>& Books) {
    cin.ignore();
    string genreToSearch;
    cout << "Enter genre to search: ";
    getline(cin, genreToSearch);

    bool found = false;
    for (const auto& LibraryBook : Books) {
        if (LibraryBook.genre == genreToSearch) {
            found = true;
            cout << "\nTitle: " << LibraryBook.title << endl;
            cout << "Author: " << LibraryBook.author << endl;
            cout << "Genre: " << LibraryBook.genre << endl;
            cout << "Availability: " << (LibraryBook.availability ? "Available" : "Not Available") << endl;
            cout << LibraryBook.separator << endl;
        }
    }
    if (!found) {
        cout << "No books found in the genre \"" << genreToSearch << "\".\n";
    }
}

void search(vector<book>& Books) {
    int choice;
    do {
        cout << "\n1- Search by Title" << endl;
        cout << "2- Search by Author" << endl;
        cout << "3- Search by Genre" << endl;
        cout << "4- Exit Search" << endl;
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                searchTitle(Books);
                break;
            case 2:
                searchAuthors(Books);
                break;
            case 3:
                searchGenres(Books);
                break;
            case 4:
                cout << "Exiting search menu." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);
}

void Display(const vector<book>& Books) {
    if (Books.empty()) {
        cout << "No books available.\n";
        return;
    }

    cout << setw(30) << "Title" << setw(30) << "Author" << setw(30) << "Genre" << setw(15) << "Availability" << endl;
    cout << string(105, '-') << endl;
    for (const auto& books : Books) {
        cout << setw(30) << books.title
             << setw(30) << books.author
             << setw(30) << books.genre
             << setw(15) << (books.availability ? "Available" : "Not Available") << endl;
    }
}

int main() {
    vector<book> Books;

    // Load books from the file at the start
    ReadData(Books);

    int choice;
    do {
        cout << "\n1- Add Book" << endl;
        cout << "2- Remove Book" << endl;
        cout << "3- Display Books" << endl;
        cout << "4- Search Books" << endl;
        cout << "5- Save and Exit" << endl;

        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(Books);
                break;
            case 2:
                RemoveBook(Books);
                break;
            case 3:
                Display(Books);
                break;
            case 4:
                search(Books);
                break;
            case 5:
                writeData(Books); // Final save before exiting
                cout << "Exiting library management system." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
