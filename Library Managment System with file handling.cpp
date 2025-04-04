#include <iostream> 
#include <iomanip> // For setw
#include <string>
#include <fstream>
using namespace std;
void loadBooks(string titles[], string authors[], string genres[], bool availability[], int& bookCount, int Max_books, int Quantity[]) {
    ifstream file("abc.txt");
    bookCount = 0;

    while (file && bookCount < Max_books) { // 2 conditions: file & bookCount < Max_books.
        getline(file, titles[bookCount]);
        
        if (titles[bookCount].empty()){
		break; // if titles[bookCount] - title is not read - loop ends. 
		}
		else{
        getline(file, authors[bookCount]);
        getline(file, genres[bookCount]);

        int Availability; // mark 2
        file >> Availability;
        availability[bookCount] = (Availability == 1);

        file >> Quantity[bookCount];
        file.ignore(); // Ignore leftover newline

        string separator;
        getline(file, separator); // Read the separator (---)

        bookCount++; 
		}
    }
    file.close();
}


void saveBooks(string titles[], string authors[], string genres[], bool availability[], int& bookCount, int Quantity[]) {
    ofstream file("xyz.txt");
    for (int i = 0; i < bookCount; i++) {
        file << titles[i] << endl;
        file << authors[i] << endl;
        file << genres[i] << endl;
        file << (availability[i] ? 1 : 0) << endl; // Save availability as 1 or 0 // mark 3
        file << Quantity[i] << endl;
        file << "---" << endl; // Separator between books
    }
    file.close();
}

void addbook(string titles[], string authors[], string genres[], bool availability[], int& bookCount, int Max_books, int Quantity[]) {
    if (bookCount >= Max_books) {
        cout << "Library is full. Remove some books to add new ones.\n";
    } else {
        cin.ignore(); // Clear leftover newline // mark 4
        cout << "\nEnter book details:\n";
        cout << "Title: ";
        getline(cin, titles[bookCount]);
        cout << "Author: ";
        getline(cin, authors[bookCount]);
        cout << "Genre: ";
        getline(cin, genres[bookCount]);
        availability[bookCount] = true; // Mark as available
        
        int choice;
        cout << "Enter 1 to add a single book or 0 for quantity: ";
        cin >> choice;

        bool isDuplicate = false; // Flag to check if the book is a duplicate
        
        // Check for duplicates and update quantity accordingly
        if (choice == 1) {
            Quantity[bookCount] = 1; // Set quantity to 1 for a new single book count[4] = 1 ; 
            
            // Check if the book is a duplicate
            for (int i = 0; i < bookCount; i++) {
                if (titles[i] == titles[bookCount]) { // titles[3] == titles[i] 
                    Quantity[i]++; // Increment the quantity of the existing book by 1
                    isDuplicate = true;
                    cout << "Duplicate found. Quantity updated.\n";
                    break; // Exit the loop after updating the quantity
                }
            }
            
            if (!isDuplicate) { // if duplicate not found.
                cout << "New book added with quantity 1.\n";
                bookCount++; // Increment bookCount only for new books
            }

        } else if (choice == 0) {
            cout << "Enter quantity: ";
            cin >> Quantity[bookCount]; // cin >> myarray[1]
            
            // Check if the book is a duplicate
            for (int i = 0; i < bookCount; i++) { // count[i]++ ; count = count + 1; count = count[bookCount] ;
                if (titles[i] == titles[bookCount]) {
                    Quantity[i] = Quantity[bookCount]; // Update quantity of existing book
                    isDuplicate = true;
                    cout << "Duplicate found. Quantity updated.\n";
                    break; // Exit the loop after updating the quantity
                }
            }

            if (!isDuplicate) { // if duplicate not found.
                cout << "New book added with quantity " << Quantity[bookCount] << ".\n";
                bookCount++; // Increment bookCount only for new books
            }
        }

        saveBooks(titles, authors, genres, availability, bookCount, Quantity); 
    }
}


void removebook(string titles[], string authors[], string genres[], bool availability[], int& bookCount, int Quantity[] ) {
    if (bookCount == 0) {
        cout << "No books in the library to remove.\n";
    } else {
        cin.ignore();
        string titleToRemove;
        cout << "\nEnter the title of the book to remove: ";
        getline(cin, titleToRemove);
        
        for (int i = 0; i < bookCount; i++) {
            if (titles[i] == titleToRemove) { 
                if(Quantity[i] != 0){
                	Quantity[i]-- ;
                }
                else{ // Quantity becomes zero.
                for (int j = i; j < bookCount - 1; j++) {
                    titles[j] = titles[j + 1];
                    authors[j] = authors[j + 1];
                    genres[j] = genres[j + 1];
                    availability[j] = availability[j + 1];
                }
                bookCount--;
            }
                saveBooks(titles, authors , genres , availability , bookCount, Quantity ) ;
                
                cout << "\nBook '" << titleToRemove << "' removed successfully!\n";
                return;
            }
        }
        cout << "\nBook not found in the library.\n";
    }
}

void Borrow_Return(string titles[], string authors[] , string genres[] , bool availability[], int bookCount, int Quantity[]) {
    cin.ignore();
    string title;
    cout << "\nEnter the title of the book: ";
    getline(cin, title);

    for (int i = 0; i < bookCount; i++) {
        if (titles[i] == title) {
            if (availability[i]) {
            	 availability[i] = false;
                Quantity[i]-- ;
                cout << "\nBook '" << titles[i] << "' has been borrowed.\n";
            } else {
                availability[i] = true;
                Quantity[i]++ ; 
                cout << "\nBook '" << titles[i] << "' has been returned.\n";
            }
            saveBooks(titles, authors , genres , availability , bookCount , Quantity ) ;
            return;
        }
    }
    cout << "\nBook not found in the library.\n";
}

void searchBookByTitle(string titles[], string authors[], string genres[], bool availability[], int bookCount) {
    cin.ignore();
    string bookSearch;
    cout << "\nEnter the title of the book to search: ";
    getline(cin, bookSearch);

    for (int i = 0; i < bookCount; i++) {
        if (titles[i] == bookSearch) {
            cout << "\nBook Found:\n";
            cout << "Title: " << titles[i] << "\n";
            cout << "Author: " << authors[i] << "\n";
            cout << "Genre: " << genres[i] << "\n";
            cout << "Availability: " << (availability[i] ? "Available" : "Not Available") << "\n"; // mark 5.
            return;
        }
    }
    cout << "\nBook not found.\n";
}

void searchBookByAuthor(string titles[], string authors[], string genres[], bool availability[], int bookCount) {
    cin.ignore();
    string authorSearch;
    cout << "\nEnter the author of the book to search: ";
    getline(cin, authorSearch);

    for (int i = 0; i < bookCount; i++) {
        if (authors[i] == authorSearch) {
            cout << "\nBook Found:\n";
            cout << "Title: " << titles[i] << "\n";
            cout << "Genre: " << genres[i] << "\n";
            cout << "Availability: " << (availability[i] ? "Available" : "Not Available") << "\n";
        }
    }
}

void searchBookByGenre (string titles[], string authors[], string genres[], bool availability[], int bookCount) {
    cin.ignore();
    string GenreSearch;
    cout << "\nEnter the author of the book to search: ";
    getline(cin, GenreSearch);

    for (int i = 0; i < bookCount; i++) {
        if (genres[i] == GenreSearch) {
            cout << "\nBook Found:\n";
            cout << "Title: " << titles[i] << "\n";
            cout << "Genre: " << genres[i] << "\n";
            cout << "Availability: " << (availability[i] ? "Available" : "Not Available") << "\n";
        }
    }
}

void search(string titles[], string authors[], string genres[], bool availability[], int bookCount) {
    int choice;
    do {
        cout << "\nSearch Menu:\n";
        cout << "1 - Search by Title\n";
        cout << "2 - Search by Author\n";
        cout << "3 - Search by Genre\n";
        cout << "4 - Exit Search Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            searchBookByTitle(titles, authors, genres, availability, bookCount);
        } else if (choice == 2) {
            searchBookByAuthor(titles, authors, genres, availability, bookCount);
        } else if (choice == 3) {
          	searchBookByGenre(titles, authors, genres, availability, bookCount);
        } else if (choice != 4) {
            cout << "Invalid Choice. Try again.\n";
        }
    } while (choice != 4);{
  }
}
// mark 6:
void sortBooks(string titles[], string authors[], string genres[], int bookCount, string criterion) {
	
	if (criterion != "title" && criterion != "author" && criterion != "genre") {
        cout << "Invalid criterion! Sorting will not be performed.\n";
        return;
    }
    
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - i - 1; j++) {
            bool condition = false;
            if (criterion == "title" && titles[j] > titles[j + 1]) {
                condition = true;
            } else if (criterion == "author" && authors[j] > authors[j + 1]) {
                condition = true;
            } else if (criterion == "genre" && genres[j] > genres[j + 1]) {
                condition = true;
            }

            if (condition) {
                swap(titles[j], titles[j + 1]);
                swap(authors[j], authors[j + 1]);
                swap(genres[j], genres[j + 1]);
            }
        }
    }
}
// mark 7:
void displayBooks(string titles[], string authors[], string genres[], bool availability[], int bookCount, int Quantity[]) {
    if (bookCount == 0) {
        cout << "\nNo books available in the library.\n";
        return;
    }

    cout << "\n----------------------------------- Displaying all books in the library -------------------------------------------------\n";
    cout << left << setw(30) << "Title" << setw(30) << "Author" << setw(30) << "Genre" << setw(10) << "Quantity" << "Availability\n";
    cout << "--------------------------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < bookCount; i++) {
        cout << left << setw(30) << titles[i] 
             << setw(30) << authors[i] 
             << setw(30) << genres[i] 
             << setw(10) << Quantity[i]
             << (availability[i] ? "Available" : "Not Available") << "\n";
    }

    cout << "---------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Total Books: " << bookCount << endl << endl;
}


void displaySortedBooks(string titles[], string authors[], string genres[], bool availability[], int bookCount, int Quantity[]) {
    cin.ignore();
    string criterion;
    cout << "Enter the criterion for sorting (title/author/genre): ";
    getline(cin, criterion);

    sortBooks(titles, authors, genres, bookCount, criterion);

    cout << "\nSorted Books:\n";
    displayBooks(titles, authors, genres, availability, bookCount, Quantity) ;
}

void display(string titles[], string authors[], string genres[], bool availability[], int bookCount, int Quantity[]) {
    int choice;
    do {
        cout << "\nDisplay Menu:\n";
        cout << "1 - Display Books\n";
        cout << "2 - Display Sorted Books\n";
        cout << "3 - Exit Display Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            displayBooks(titles, authors, genres, availability, bookCount, Quantity);
        } else if (choice == 2) {
            displaySortedBooks(titles, authors, genres, availability, bookCount, Quantity);
        } else if (choice != 3) {
            cout << "Invalid Choice. Try again.\n";
        }
    } while (choice != 3);
}

int main() {
    const int Max_books = 100;
    string titles[Max_books]   ;
	string authors[Max_books]  ;
	string genres[Max_books]   ;
    bool availability[Max_books] = {true} ;
    int bookCount = 0 ;
    int Quantity[Max_books] ;
    
    loadBooks(titles , authors , genres , availability, bookCount , Max_books, Quantity) ;
    cout << "Books Loaded Successfully!" << endl;

    int choice;
    do {
        cout << "\nLibrary System\n";
        cout << "1 - Add Book\n";
        cout << "2 - Remove Book\n";
        cout << "3 - Search Book\n";
        cout << "4 - Display Books\n";
        cout << "5 - Borrow/Return Book\n";
        cout << "6 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            addbook(titles, authors, genres, availability, bookCount, Max_books, Quantity);
        } else if (choice == 2) {
            removebook(titles, authors, genres, availability, bookCount, Quantity);
        } else if (choice == 3) {
            search(titles, authors, genres, availability, bookCount);
        } else if (choice == 4) {
            display(titles, authors, genres, availability, bookCount, Quantity);
        } else if (choice == 5) {
            Borrow_Return(titles, authors , genres, availability, bookCount, Quantity);
		}
		else{
			cout << "Exit. Thank you visit us Again." << endl;
		}
    }
    while(choice != 6);{
	}
	
	return 0 ;
}
    


