#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype> // for toupper() and for tolower()
using namespace std;

class Question {
public:
    string Question_statement;
    string seperator;
public:
    Question(string state = "null", string seperator = "--------------") {
        Question_statement = state;
        this->seperator = seperator;
    }
    
    string getStatement(){
    	return Question_statement ;
	}
	
	string getSeperator(){
		return seperator ;
	}

    virtual void displayQuestion() = 0;
};

class MCQS : public Question {
private:
    vector<string> Multiple_Choices;
    char correctAnswer;
public:
    MCQS(string statement, vector<string> choices, char correctAns, string seperator)
        : Question(statement, seperator), Multiple_Choices(choices), correctAnswer(correctAns) {}

    void displayQuestion() override {
        cout << Question_statement << endl;
        for (int i = 0; i < Multiple_Choices.size(); ++i) {
            cout << char('A' + i) << ") " << Multiple_Choices[i] << endl;
        }
        cout << seperator << endl;
    }
    
    vector<string>& getChoices() { return Multiple_Choices; }
    char getCorrectAns() const { return correctAnswer; }
};

class TrueFalse : public Question {
private:
    string correctAnswer;
public:
    TrueFalse(string statement, string Answer, string seperator) 
        : Question(statement, seperator), correctAnswer(Answer) {}

    void displayQuestion() override {
        cout << Question_statement << " (True/False)" << endl;
        cout << seperator << endl;
    }
    
    string getCorrectAnswer() const { return correctAnswer; }
};

class FilltheBlanks : public Question {
private:
    string correctAnswer;
public:
    FilltheBlanks(string statement, string correctAns, string seperator) 
        : Question(statement, seperator), correctAnswer(correctAns) {}

    void displayQuestion() override {
        cout << Question_statement << " ________" << endl;
        cout << seperator << endl;
    }
    
    string getCorrectAnswer() const { return correctAnswer; }
};

class QuizManager {
private:
    vector<MCQS> mcqQuestions;
    vector<FilltheBlanks> ftbQuestions;
    vector<TrueFalse> tfQuestions;
    
    void saveAllMCQS() {
        ofstream file_out("MCQS.txt", ios::trunc);  // Corrected mode
        for (int i = 0; i < mcqQuestions.size(); i++) {
            file_out << mcqQuestions[i].Question_statement << "\n";
            
            vector<string>& allChoices = mcqQuestions[i].getChoices();
            for (int j = 0; j < allChoices.size(); j++) {
                file_out << allChoices[j] << "\n";
            }
            
            file_out << mcqQuestions[i].getCorrectAns() << "\n";
            file_out << mcqQuestions[i].seperator << "\n";
        }
        file_out.close();
    }
    
    void saveAllTF() {
        ofstream file_out("TrueFalse.txt", ios::trunc);
        for (int i = 0; i < tfQuestions.size(); i++) {
            file_out << tfQuestions[i].Question_statement << "\n";
            file_out << tfQuestions[i].getCorrectAnswer() << "\n";
            file_out << tfQuestions[i].seperator << "\n";
        }
        file_out.close();
    }
    
    void saveAllFTB() {
        ofstream file_out("FTB.txt", ios::trunc);
        for (int i = 0; i < ftbQuestions.size(); i++) {
            file_out << ftbQuestions[i].Question_statement << "\n";
            file_out << ftbQuestions[i].getCorrectAnswer() << "\n";
            file_out << ftbQuestions[i].seperator << "\n";
        }
        file_out.close();
    }

public:
	bool DeleteQuestion(char type, int index) {
    	try {
        	switch(type) {
            	case 'A': // MCQS
                	if (index >= 0 && index < mcqQuestions.size()) {
                    	mcqQuestions.erase(mcqQuestions.begin() + index);
                    	saveData();
                    	return true;
                	}
                	break;
            	case 'B': // True/False
                	if (index >= 0 && index < tfQuestions.size()) {
                    	tfQuestions.erase(tfQuestions.begin() + index);
                    	saveData();
                    	return true;
                	}
                	break;
            	case 'C': // Fill in blanks
                	if (index >= 0 && index < ftbQuestions.size()) {
                    	ftbQuestions.erase(ftbQuestions.begin() + index);
                    	saveData();
                    	return true;
                	}
                	break;
            	default:
                	return false;
        	}
        	return false;  // If index was out of bounds
    	} catch (...) {
        	return false;  // Catch any unexpected errors
    	}
	}
	
	void DisplayAllMCQS() {
    	if (mcqQuestions.empty()) {
        	cout << "No MCQs available." << endl;
        	return;
    	}
   	 	for (int i = 0; i < mcqQuestions.size(); i++) {
        	cout << "[" << (i + 1) << "] ";  // Show 1-based index
        	mcqQuestions[i].displayQuestion();
    	}
	}

	void DisplayAllTrueFalse() {
    	if (tfQuestions.empty()) {
        	cout << "No True/False questions available." << endl;
        	return;
    	}
    	for (int i = 0; i < tfQuestions.size(); i++) {
        	cout << "[" << (i + 1) << "] ";
        	tfQuestions[i].displayQuestion();
    	}
	}	

	void DisplayAllFillInTheBlanks() {
    	if (ftbQuestions.empty()) {
        	cout << "No Fill-in-the-blank questions available." << endl;
        	return;
   	 	}
    	for (int i = 0; i < ftbQuestions.size(); i++) {
        	cout << "[" << (i + 1) << "] ";
        	ftbQuestions[i].displayQuestion();
    	}
	}
		
    void saveData() {
        saveAllMCQS();
        saveAllTF();
        saveAllFTB();
    }
    
    void loadData() {
        ifstream MCQS_in("MCQS.txt");
        ifstream Fill_The_Blanks_in("FTB.txt");
        ifstream True_False_in("TrueFalse.txt");

        string statement; 		// MCQ
        vector<string> choices; // MCQ
        char correctAns; 		// MCQ
        
        string Answer; 		// For True and False
        string Blanks; 		// For fill in the blanks
        string seperator;

        // For MCQS:
        while (getline(MCQS_in, statement)) {
            if (statement.empty()) {
                break;
            }

            for (int i = 0; i < 4; i++) {
                string choice;
                getline(MCQS_in, choice);
                choices.push_back(choice);
            }

            MCQS_in >> correctAns;
            MCQS_in.ignore(); // clear the input buffer.
            getline(MCQS_in, seperator);

            mcqQuestions.push_back(MCQS(statement, choices, correctAns, seperator));
            choices.clear(); // for safety, clears the vector before loading new options. As you know vector is dynamic so we only need initial 4 index(0,1,2,3)
        }

        // Fill in the blanks
        while (getline(Fill_The_Blanks_in, statement)) {
            if (statement.empty()) {
                break;
            }

            getline(Fill_The_Blanks_in, Blanks);
            getline(Fill_The_Blanks_in, seperator);

            ftbQuestions.push_back(FilltheBlanks(statement, Blanks, seperator)); // create an object and store it in the vector.
        }

        // TrueFalse:
        while (getline(True_False_in, statement)) {
            if (statement.empty()) {
                break;
            }

            getline(True_False_in, Answer);
            getline(True_False_in, seperator);

            tfQuestions.push_back(TrueFalse(statement, Answer, seperator)); // create object, store in the vector.
        }
        
        cout << "MCQS/True-False/Fill in the blanks\n" << endl;
    }
	
	// doing this so we can access these vectors and load single Questions in them later...in Educator and Student. 
	void addMCQ(const MCQS& question){
		mcqQuestions.push_back(question) ;
		saveData() ; // after each question addition..data is saved.
	}
	
	void addTF(const TrueFalse& question){
		tfQuestions.push_back(question) ;
		saveData() ; // after each question addition data is saved.
	}
	
	void addFTB(const FilltheBlanks& question){
		ftbQuestions.push_back(question) ;
		saveData() ; // after each question addition data is saved.
	}
	
};

class Credentials { 
private:
    string userName;
    string passWord;
    string hint;
public:
    Credentials(string name = "null", string pass = "null", string hint = "null") {
        userName = name;
        passWord = pass;
        this->hint = hint;
    }

    void setUserName(string name) { userName = name; }
    string getUserName() const { return userName; }
    void setPassword(string pass) { passWord = pass; }
    string getPassword() const { return passWord; }
    string getHint() const { return hint; }
    void setHint(string hint) { this->hint = hint; }
};

void signUp(string filePath) {
    ofstream out(filePath, ios::app);  // ios::app for append mode
    if (!out.is_open()) {
        cerr << "Error: Could not open file for writing: " << filePath << endl;
        return;
    }

    string username, password, hint;

    cout << "\n--- Sign Up ---\n";
    cout << "Enter new Username: ";
    cin.ignore() ;
    
    getline(cin , username) ; 
    cout << "Enter new Password: ";
    cin >> password;
    cout << "Enter a password hint: ";
    
    cin.ignore();  // Clear the newline character left by cin >>
    getline(cin, hint);

    // Write the data with proper newlines
    out << username << '\n' << password << '\n' << hint << '\n';
    out.close();
    
    if (out.fail()) {
        cerr << "Error: Failed to write data to file." << endl;
    } else {
        cout << "Account successfully created!\n";
    }
}

bool forgetPassword(const vector<Credentials>& creds, const string& username) {
    for (int i = 0; i < creds.size(); ++i) {
        if (creds[i].getUserName() == username) {
            cout << "Password Hint: " << creds[i].getHint() << endl;
            string guess;
            for (int j = 0; j < 3; j++) {
                cout << "Enter Password: ";
                cin >> guess;
                if (guess == creds[i].getPassword()) {
                    cout << "Access granted.\n";
                    return true;
                }
                else {
                    cout << "Incorrect. Try again.\n"; // after 3 times.
                }
            }
            cout << "Failed attempts. Redirecting to sign up...\n";
            return false;
        }
    }
    cout << "Username not found. Redirecting to sign up...\n";
    return false;
}

bool inputLogin(vector<Credentials>& creds, string filePath) {
    string username, password;
    cout << "\n--- Login ---\n";
    cout << "Enter Username: ";
    cin.ignore() ; // clear buffer
    getline(cin, username) ;
    cout << "Enter Password: ";
    cin >> password;

    for (int i = 0; i < creds.size(); ++i) {
        if (creds[i].getUserName() == username && creds[i].getPassword() == password) {
            cout << "\nLogin successful!\n";
            return true;
        }
        else if (creds[i].getUserName() == username && creds[i].getPassword() != password) {
            cout << "Incorrect password.\n";
            int choice;
            cout << "1. Try hint-based password recovery\n2. Sign up\nChoice: ";
            cin >> choice;
            if (choice == 1) {
                if (forgetPassword(creds, username)) // True means login successful
                    return true;
                else {
                    signUp(filePath); // false means login failed upon hints too,
                    return false;
                }
            }
            else {
                signUp(filePath);
                return false;
            }
        }
    }

    cout << "Username and password not found.\n"; // case 3 - when both the password and userName does not match.
    int choice;
    cout << "1. Try password recovery\n2. Sign up\nChoice: ";
    cin >> choice;
    if (choice == 1) {
        if (forgetPassword(creds, username)) // True recieved meaning success- loop ends
            return true ;
        else {
            signUp(filePath); // False means you need to signup - moved to the signup
            return false;
        }
    }
    else {
        signUp(filePath);
        return false;
    }
}

class User {
private:
    string UserName;
    string Password;
public:
    virtual void login() = 0;
    virtual void displayMenu() = 0;
};

class Student : public User {
private:
    vector<Credentials> credentials;
public:
    void login() override {
    credentials.clear();
    ifstream student_in("Student_Data.txt");
    string name, password, hint;

    while (getline(student_in, name)) {
        getline(student_in, password);
        getline(student_in, hint);
        if (!name.empty()) {
            credentials.push_back(Credentials(name, password, hint));
        }
    }
    student_in.close();
    
    // Capture and use the return value
    bool loginSuccess = inputLogin(credentials, "Student_Data.txt");
    if (loginSuccess) {
        displayMenu();  // Only show menu if login succeeded
    }
}

    void displayMenu() override {
        cout << "Student Dashboard (Coming soon)\n";
    }
};

class Educator : public User {
private:
    vector<Credentials> credentials;
    QuizManager quizmanager ; // currently figuring out how to load data.
public:
   void login() override { // Deals with educator credential data.
    credentials.clear();
    ifstream edu_in("Educator_Data.txt");
    string name, password, hint;

    while (getline(edu_in, name)) {
        getline(edu_in, password);
        getline(edu_in, hint);
        if (!name.empty()) {
            credentials.push_back(Credentials(name, password, hint));
        }
    }
    edu_in.close();
    
    // store and use the return value
    bool loginSuccess = inputLogin(credentials, "Educator_Data.txt");
    if (loginSuccess) { // when the login is successful only then load data and displayMenu .
    	quizmanager.loadData() ;
    	cout << "Educator Panel: " << endl; 
        displayMenu();  // Only show menu if login succeeded
    }
    
} // login end here.
	
	// Crud operations here: 1- Create/Add Questions, 2- read, 3- update, 4- delete
	void AddQuestion(){ // add operations
		//1- which type you are creating.
		while(true){
		
		int choice ;
		cout << "Choose Question type: " << endl;
		cout << "1- MCQ " << endl;
		cout << "2- True/False " << endl;
		cout << "3- Fill in the blanks " << endl;
		cout << "4- Exit. Visit again" << endl;
		cout << "Your choice: " ;
		cin >> choice ;
		
		string statement , seperator ; 
		if(choice == 1){
		
			vector <string> choices(4) ; // initialized vector with only 4 elements. Fixed the size. 
			char correctAns ;
			// 1- Take input:
			
			cout << "Statement: " ;
			cin.ignore() ;
			getline(cin, statement) ; 
			
			vector <string> Alphabets = { "A) ", "B) ", "C) ", "D) " };
			for(int i=0 ; i<4 ; i++){
				cout << Alphabets[i] ;
				getline(cin, choices[i]) ;
			}
			
			cout << "Correct Answer - (A,B,C,D) " ;
			cin >> correctAns ; // alphabet
			
    		// Check if it's lowercase
    		if (islower(correctAns)) {
        		correctAns = toupper(correctAns); // Convert to uppercase
    		}
    		
    		MCQS question(statement, choices, correctAns, seperator) ; // object formed.
    		quizmanager.addMCQ(question) ; // no need to load the whole vectors here.
    	}
    	
    	else if(choice == 2){
    		string Answer; // True and False option
			
			cout << "Statement: " ;
			cin.ignore() ; // before using the line - clear the whole buffer in the line..
			getline(cin,statement) ;
			
			int choice ;
			cout << "The answer for this is - (True/False)" << endl;
			cout << "1- For True" << endl;
			cout << "2- For False" << endl;
			cin >> choice ;
			
			if(choice == 1){
				Answer = "True" ;
			}
			else if(choice == 2){
				Answer = "False" ;
			}
			else{
				cout << "Kindly enter 1 or 2" << endl;	
			}
			
			TrueFalse question(statement, Answer, seperator);
			quizmanager.addTF(question) ;
		}
		
		else if(choice == 3){
			string Blanks ;
		
			cout << "Statement: " ;
			cin.ignore() ;
			getline(cin, statement) ;
			
			cout << "What comes in the Blank: " ;
			cin >> Blanks ;
			
    		FilltheBlanks question(statement, Blanks, seperator) ;
    		quizmanager.addFTB(question) ;
		}
		
		else if(choice == 4){
			cout << "Exit. Visit us again." << endl;
			break ;	
		}
		
			else{
		cout << "Invalid Input" << endl;		
			}
		}
	}
	
	void DeleteQuestion() {
    char choice;
    cout << "What kind of question you want to remove: " << endl;
    cout << "A. MCQ" << endl;
    cout << "B. True/False" << endl;
    cout << "C. Fill in the blanks" << endl;
    cout << "Your choice: " ;
    cin >> choice;

    if (islower(choice)) {
        choice = toupper(choice);
    }

    // Display questions first
    switch(choice) {
        case 'A':
            quizmanager.DisplayAllMCQS();
            break;
        case 'B':
            quizmanager.DisplayAllTrueFalse();
            break;
        case 'C':
            quizmanager.DisplayAllFillInTheBlanks();
            break;
        default:
            cout << "Invalid Choice." << endl;
            return;  // Exit if invalid choice
    }

    int QuestionNum;
    cout << "Enter Question Number: ";
    cin >> QuestionNum;

    // Adjust for 0-based index (show 1-based to user)
    if (QuestionNum < 1) {
        cout << "Invalid question number!" << endl;
        return;
    }

    bool success = quizmanager.DeleteQuestion(choice, QuestionNum - 1);
    if (!success) {
        cout << "Failed to delete question. Invalid number or type." << endl;
    } else {
        cout << "Question deleted successfully!" << endl;
    }
}
	
    void displayMenu() override {
        while(true){
    		int choice ;
				cout << "1- Add Questions" << endl;
				cout << "2- Delete Questions" << endl;
				cout << "3- Update Questions" << endl;
				cout << "4- Display Questions" << endl;
				cout << "5- For Exit." << endl;
				cout << "Your choice: " ;
			cin >> choice ;
			
			if (choice == 1){
				AddQuestion() ;
			}	
			else if(choice == 2){
				DeleteQuestion() ; 
			}
			else if(choice == 3){
				cout << "coming soon" << endl;
			}
			else if(choice == 4){
				cout << "coming soon" << endl;
			}
			else if(choice == 5){ 
				cout << "\nExit. Visit again" << endl;
				break;
			}
				else{
			cout << "Invalid Option" << endl;
 				}
			}
    	}
};

int main() {
    Student s;
    Educator e;
	
	while(true){

	    int roleChoice;
   		cout << "Choose Role: " << endl; 
		cout << "1. Student "   << endl; 
		cout << "2. Educator "  << endl;
		cout << "3. Exit. " << endl;
		
		cout << "Choice: " ;
    	cin >> roleChoice;

    	if (roleChoice == 1) {
        	s.login();
    	}
    	else if (roleChoice == 2) {
        	e.login();
    	}
    	else if(roleChoice == 3) {
        	cout << "Exit." << endl;
        	break ;
    	}
    	else{
    		cout << "Invalid choice" << endl;
		}
	}
	
    return 0;
}


