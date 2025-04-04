#include <iostream>
#include <string>
using namespace std;

const int MAX_SEATS = 10; // Total number of seats in the movie theater // global variable.

// Function to display the seat status
void displaySeats(string seats[]) {
    cout << "\nSeat Status:\n";
    for (int i = 0; i < MAX_SEATS; i++) {
        cout << "Seat " << i + 1 << ": " << seats[i] << endl;
    }
}

// Function to book a ticket
void bookTicket(string seats[]) {
    int seatNumber;
    cout << "\nEnter the seat number to book (1 to " << MAX_SEATS << "): ";
    cin >> seatNumber;

    if (seatNumber < 1 || seatNumber > MAX_SEATS) {
        cout << "Invalid seat number.\n";
        return;
    }

    if (seats[seatNumber - 1] == "Booked") {
        cout << "Seat already booked!\n";
    } else {
        seats[seatNumber - 1] = "Booked";
        cout << "Seat " << seatNumber << " booked successfully!\n";
    }
}

// Function to cancel a ticket
void cancelTicket(string seats[]) {
    int seatNumber;
    cout << "\nEnter the seat number to cancel (1 to " << MAX_SEATS << "): ";
    cin >> seatNumber;

    if (seatNumber < 1 || seatNumber > MAX_SEATS) {
        cout << "Invalid seat number.\n";
        return;
    }

    if (seats[seatNumber - 1] == "Available") {
        cout << "Seat is already available, cannot cancel.\n";
    } else {
        seats[seatNumber - 1] = "Cancel" ;
        cout << "Seat " << seatNumber << " cancelled successfully!\n";
    }
}

// Function to handle payments
void makePayment() {
    int paymentChoice;
    cout << "\nSelect payment option:\n";
    cout << "1. Pay in full\n";
    cout << "2. Pay half\n";
    cout << "3. Pay on the spot\n";
    cout << "Enter your choice (1/2/3): ";
    cin >> paymentChoice;

    switch (paymentChoice) {
        case 1:
            cout << "You have paid in full.\n";
            break;
        case 2:
            cout << "You have paid half.\n";
            break;
        case 3:
            cout << "You have chosen to pay on the spot.\n";
            break;
        default:
            cout << "Invalid payment option.\n";
    }
}

// Function to search available seats
void searchAvailableSeats(string seats[]) {
    cout << "\nAvailable seats:\n";
    bool found = true ;
    
    for (int i = 0 ; i<MAX_SEATS ; i++){
    	if(seat[i] == "Available"){
    		cout <<  "Seat" << i+1  << "Available" << endl;
    		found = false ;
		}
	}
	
	if(found){
		cout << "Not Available" << endl;
	}
}

int main(){
	string seasts[MaxSeats] = {"Available" , "Available", "Available" , "Available", "Available", "Available", "Available", "Available", "Available"
	, "Available" }
	
	int choice ;
	do{
		cout << "\nMovie Ticket Reservation System\n";
        cout << "1. Display Seats\n";
        cout << "2. Book Ticket\n";
        cout << "3. Cancel Ticket\n";
        cout << "4. Make Payment\n";
        cout << "5. Search Available Seats\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {        
        	case 1: 
        	 displayseats(seats) ;
        	 break; 
            case 2: 
            bookTicket(seats);
             break;
            case 3:
                cancelTicket(seats);
                break;
            case 4:
                makePayment();
                break;
            case 5:
                searchAvailableSeats(seats);
                break;
            case 6:
                cout << "Exiting system.\n";
                break;
		}
    }
    while(choice != 6); {
	}
}