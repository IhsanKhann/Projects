#include <iostream>
#include <string>
using namespace std; 
void AddTasks (string tasks[] , bool tasksDone[] , int MaxTasks , int &tasksCount){
	if(tasksCount == MaxTasks){
		cout << "No more Tasks cant be added" << endl;
		return ; // leave function - directly.
	}
	
	int choice ;
	string taskToAdd ;
	
	    cout << "\nEnter your Choice: " << endl;
        cout << "Press 1 to add tasks " << endl;
        cout << "Press 0 to Exit.\n" << endl;  
	
	while(true){
		
		cout << "Your Choice: " ;
        cin >> choice; // wrtitten inside loop because we need cin repeatedly.
        
        cin.ignore() ;
        if(choice == 1){ 
        	if(tasksCount <= MaxTasks){
        		cout << "\nEnter Task: " << endl;
        		getline(cin , taskToAdd) ;
        	
        	    tasks[tasksCount] = taskToAdd ; 
        	    tasksCount++ ;
        	    tasksDone[tasksCount] = {false} ;
        	 
        	cout << "Task Added!\n" << endl; }
			else{
				cout << "Maximum limited reached" << endl;
				break; /// means break the function here. So else if and else is not excuted.
			}
		}
		else if(choice == 0){
		        cout << "Exit. Addition " << endl;
		        break; // if this is excuted. The function breaks here.
		        
			}
		else{
			cout << "Invalid Input.\n" << endl;
			break; // if this is excuted. The last statment must not be executed.
		}
	}
	  cout << "All Tasks Added. " << endl; 
}

#include <iostream>
#include <string>
using namespace std;

void DeleteTask(string Tasks[], int &taskCount, int MaxTasks, bool TaskCompletion[]) {
    if (taskCount == 0) {
        cout << "No tasks to remove" << endl;
        return;
    }

    cin.ignore();  // Ignore any leftover newline characters
    string TasktoRemove;
    cout << "Enter the task to remove: ";
    getline(cin, TasktoRemove);

    bool taskFound = false;
    for (int i = 0; i < taskCount; i++) {
        if (Tasks[i] == TasktoRemove) {
            // Shift all tasks after the found task one position left
            for (int j = i; j < taskCount - 1; j++) {
                Tasks[j] = Tasks[j + 1];
                TaskCompletion[j] = TaskCompletion[j + 1];  // Also shift completion status
            }
            taskCount--;  // Decrease the task count
            taskFound = true;
            cout << "Task '" << TasktoRemove << "' is removed." << endl;
            break;
        }
    }

    if (!taskFound) {
        cout << "Task not found." << endl;
    }
}

void MarkAsDone(string tasks[], int &taskCount, int MaxTasks, bool TaskCompletion[]) {
	
	for(int i = 0; i<taskCount ; i++){
    cout << i << " - " << tasks[i] << "(Undone)" << endl; 	
	}
	cout << endl;
	
    cin.ignore();  // Ignore the previous newline character
    string TaskDone;
    cout << "Enter the task done: ";
    getline(cin, TaskDone);
    
    bool taskFound = false;  // Flag to check if the task is found

    for (int i = 0; i < taskCount; i++) {
        if (TaskDone == tasks[i]) {
            TaskCompletion[i] = true;  // Mark the task as done
            cout << i << " - " << tasks[i] << " (Task Done)" << endl;
            taskFound = true;  // Task found, set the flag to true
        }
    }

    // If task is not found, print a message
    if (!taskFound) {
        cout << "Task not found." << endl;
    }
    
    // Check if all tasks are marked as done and print appropriate message
    bool allTasksDone = true;
    for (int i = 0; i < taskCount; i++) {
        if (!TaskCompletion[i]) {
            allTasksDone = false;
            break;
        }
    }

    if (allTasksDone) {
        cout << "All tasks are done!" << endl;
    } else {
        cout << "Not all tasks are done." << endl;
    }
}
int main(){
	int MaxTasks = 100 ;
	string Tasks[MaxTasks] ;
	int taskCount = 0 ;
    int choice ;                                                                                                                                                                                                                                                                 
    bool TaskCompletion[MaxTasks] = {false} ;
    
do{
   cout << "\nMenu: " << endl ;
   cout << "1- AddTasks "          << endl;
   cout << "2- DeleteTask"         << endl;
   cout << "3- Mask Task as Done " << endl;
   cout << "4- Exit\n "            << endl;
   cout << "Your Choice: "  ;
   cin  >> choice ;
   
   switch(choice) {
   case 1: 
     AddTasks ( Tasks , TaskCompletion , MaxTasks, taskCount) ;
     break ;
   case 2: 
     DeleteTask(Tasks , taskCount , MaxTasks,TaskCompletion  ) ;
     break ;
   case 3: 
     MarkAsDone (Tasks , taskCount ,MaxTasks ,TaskCompletion ) ;
     break;
    case 4:
      cout << "Exit. Visit again" << endl;
      break;
    default:
    cout << "Invalid Choice." << endl;
   }
}
  while (choice != 3);{
    }	
}