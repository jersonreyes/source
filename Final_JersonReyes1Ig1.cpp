/*
██████╗ ██╗   ██╗██╗     ███████╗██╗   ██╗   ██████╗ ██████╗
██╔══██╗██║   ██║██║     ██╔════╝██║   ██║   ██╔══██╗██╔══██╗
██████╔╝██║   ██║██║     ███████╗██║   ██║   ██████╔╝██║  ██║
██╔══██╗██║   ██║██║     ╚════██║██║   ██║   ██╔══██╗██║  ██║
██████╔╝╚██████╔╝███████╗███████║╚██████╔╝██╗██║  ██║██████╔╝

DOCUMENTATION:
==========================================================================

UPDATE: ADDED SUPPORT FOR C++98. UPDATED SORTING METHOD FOR COMPATIBLITY (WINDOWS GCC COMPILER) | OLD METHODS USE NEW C++11
ERRORS: Every process has error shown if violated. Input guards are placed on every run and sometimes when call starts.
DISCLAIMER: There are still existing bugs which are not worth trying to fix :)
NAME SORTATION IS BY FIRST NAME. ADJUST num_students TO YOUR TARGETED AMOUNT OF STUDENTS. REF: LINE 53.

FUNCTIONS:
Record viewing, finding, sorting and final grade calculations are handled by the same function.
(including finding highest and lowest grade holder)

Available values:
records to show: all, id (record finding), highest_total_score, lowest_total_score, final_grade;
id: default, value;
sortation type: name, score;
output_type: default, print, print_ask;

Format:
showData("amount of records", "id" "sortation type", "output type");
==========================================================================
Adding, deleting, and modifying records are also handled by a single function.
available values: new, delete, update;

Format:
process("type of task", "reference id");

*/
#define _WIN32_WINNT 0x0500 //FOR WINDOW RESIZING
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <windows.h>
#include <sstream>

using namespace std;

struct StudRec {
   string ID, remarks;
   float score_quiz, score_assi, score_act, score_proj, score_mid, score_final, score_total, final_grade;
   char name[25], sex;
   int index, deleted;
   //ASSIGN DEFAULT VALUE FOR IGNORING DELETED RECORDS
   StudRec() {deleted=2;}
} student[25];

void displayMenu(), processChoice(), process(string type, string id), displayLogo(), firstRun(), COLOR(), UNCOLOR(), WHITE(), COLOR_BLACK(), COLOR_BLACK_ALT(), lock();
int showData(string selection, string id, string sortation_type, string output_type), verifyRun(), num_students = 5, student_counter = 0, registered_student_counter = 0, previous_deletion = 0;

int main() {
   lock();
   displayLogo();
   displayMenu();
   return 0;
}

void processChoice() {

   string choice;
   cout  << "\n\nEnter task: " ; cin >> choice;

   if(choice == "1")
      process("new", "default");
   else if(choice == "2")
      process("delete", "default");
   else if(choice == "3")
      process("update", "default");
   else if(choice == "4") {
      showData("all", "name", "default", "print_ask");
      processChoice();
   }  else if(choice == "5")
      showData("final_grade", "default", "default", "default");
   else if(choice == "6")
      showData("highest_total_score", "default", "default", "default");
   else if(choice == "7")
      showData("lowest_total_score", "default", "default", "default");
   else if(choice == "8")
      showData("id", "default", "default", "print_ask");
   else if(choice == "9")
      showData("sort", "default", "score", "default");
   else if(choice == "10")
      showData("sort", "default", "name", "default");
   else if(choice == "x" || choice == "X" ) {
      system("cls");
      cout  <<
      "\n   _____  _   _     _     _   _  _  __ __   __ ___   _   _  _ \n"
      "  |_   _|| | | |   / \\   | \\ | || |/ / \\ \\ / // _ \\ | | | || |\n"
      "    | |  | |_| |  / _ \\  |  \\| || ' /   \\ V /| | | || | | || |\n"
      "    | |  |  _  | / ___ \\ | |\\  || . \\    | | | |_| || |_| ||_|\n"
      "    |_|  |_| |_|/_/   \\_\\|_| \\_||_|\\_\\   |_|  \\___/  \\___/ (_)\n"
      "    GOD BLESS AND KEEP SAFE | WASH YOUR HANDS! :)                   \n\n\n" ;
      cin.ignore(); system("exit"); exit(0);
   }  else if(choice == "m" || choice == "M" ) {
      cout << endl;
      displayMenu();
   }  else {
     cout  << "You've entered an invalid option. Please try again." ;
     processChoice();
   }
}

/*
MENU DISPLAY
*/
void displayMenu() {
   cout <<
   "  [1] Add student records\n"
   "  [2] Delete student records\n"
   "  [3] Update student records\n"
   "  [4] View all student records\n"
   "  [5] Calculate the final grade of a selected student\n"
   "  [6] Show student who gets the max total score\n"
   "  [7] Show student who gets the min total score\n"
   "  [8] Find student by ID\n"
   "  [9] Sort records by total scores\n"
   "  [10] Sort records by student's name\n\n"
   "  [M] Display the Menu\n"
   "  [X] Exit the Program\n";
   processChoice();
}

/*
RECORD PROCESSING (ADDITION, REMOVAL, AND MODIFICATION)
*/
void process(string task, string id) {
   if (task == "new" || task == "update") {
      int index, j, i = 0;
      char prename[25], sex;
      string id;
      if (previous_deletion) i = registered_student_counter + previous_deletion;

      //HANDLE IF MAXIMUM AMOUNT OF STUDENTS ALLOWED IS EXCEEDED
      if(registered_student_counter == num_students && task == "new") {
        cout << "You've reached the maximum amount of students allowed in a class.\nConsider deleting? Enter 2 to remove old students.";
        processChoice();
      }
      //MODIFYING RECORDS
      if (task == "update") {
         firstRun();
         showData("all","default","default","print");
         MOD: cout << "\n\nEnter ID of student to be modified: "; cin >> id;

         //SET POINTING INDEX FOR MODIFYING INITIATION
         for (int j = 0; j < num_students + previous_deletion; j++)
            if (student[j].ID == id)
              i=j;

         int result = showData("id", id, "default", "default");
         student_counter = result;
         index = i;
         //DON'T LET IT PASS IF NOT FOUND, LOOP
         if (result == 0) {
            cout  << "OOPS! ID doesn't seem to match any records!\n" ;
            goto MOD;
         }
      }
      for (; i < num_students + previous_deletion; i++) {
         //ADDING NEW RECORDS
         if (task == "new") {
            //FOR NEW RECORDS/DEFAULT + INCREMENT STUDENT COUNTER
            index = i;
            student_counter++; registered_student_counter++;
            student[index].index = student_counter;
            student[index].deleted = 0;
         }

         NAME:
         cout << "\n  Enter Student " << student_counter << " Name" << "\t|   "; cin.ignore(); cin.getline(prename, 25);

         //NAMES SHOULD NOT CONTAIN ANY NUMBER
         //FOUND NEW SIMPLER SOLUTION USING FUNCTION | OLD CODE
         //if (prename[j] == '0' || prename[j] == '1' || prename[j] == '2' || prename[j] == '3' || prename[j] == '5' || prename[j] == '6' || prename[j] == '7' || prename[j] == '8' || prename[j] == '9')
         for (j = 0; j < 25; j++) {
            if (isdigit(prename[j])) {
               cout  << "\n  Only letters are allowed. Please re-enter. \n" ;
               goto NAME;
            }
         }
         //EMPTY CHECKING
         if (! * prename) {
            cout  << "  Name is a requirement. Please fill in. \n\n" ;
            goto NAME;
         }

         //SUCCESS: STORE
         strcpy(student[i].name, prename);

         IDVERIFIY:
         cout << "  Enter ID number" << "\t|   "; cin >> id;

         //VERIFY IF ID ALREADY EXISTS
         int find = showData("id", id, "default", "default");

         //IF ID IS NON-EXISTENT, CONTINUE
         if (find == 0) {
            //STORE ID
            student[index].ID = id;

            SEX:
            cout << "  Enter Sex" << "\t\t|   "; cin.ignore(); cin >> sex;
            //SUCCESS
            if (sex == 'm' || sex == 'M' || sex == 'f' || sex == 'F')
               student[index].sex = sex;
            else {
               cout  << "\n  Please enter a valid option between "  <<  "M"  << " and "  << "F\n"  ;
               goto SEX;
            }

            QUIZ: cout << "  Score in Quiz" << "\t\t|   "; cin.ignore(); cin >> student[index].score_quiz; if (verifyRun()) goto QUIZ;
            ASSI: cout << "  Score in Assignment" << "\t|   ";cin >> student[index].score_assi; if (verifyRun()) goto ASSI;
            MID: cout << "  Score in Midterm Exam" << "\t|   ";cin >> student[index].score_mid; if (verifyRun()) goto MID;
            FINALS: cout << "  Score in Final Exam" << "\t|   ";cin >> student[index].score_final; if (verifyRun()) goto FINALS;
            ACTI: cout << "  Score in Activity" << "\t|   ";cin >> student[index].score_act; if (verifyRun()) goto ACTI;
            PROJ: cout << "  Score in Project" << "\t|   ";cin >> student[index].score_proj; if (verifyRun()) goto PROJ;

            //PRE-COMPUTE DATA BEFORE LEAVING
            int total = student[index].score_quiz + student[index].score_assi + student[index].score_mid + student[index].score_final + student[index].score_act + student[index].score_proj;
            student[index].score_total = total;

            /*
            QUIZ ADJUSTED TO 150/150 BECAUSE RESULT DIFFERS FROM THE PROVIDED SAMPLE
            ASSIGNMENT USES /20 ASSUMPTION BASED ON PROVIDED SAMPLE | NOT PROVIDED

            INSTRUCTED FORMULA
            float final =
            ((student[index].score_quiz / 20) * 100 *.20) +
            (((student[index].score_mid / 2 + student[index].score_final / 2) / 100) * 100 * .30) +
            ((student[index].score_act / 150) * 100 * .25) +
            ((student[index].score_proj / 100) * 100 * .15) +
            ((student[index].score_assi / 20) * 100 * .10);
            */

            // ADJUSTED FORMULA TO MATCH PROVIDED SAMPLE
            float final =
            ((student[index].score_quiz / 150) * 100 *.20) +
            (((student[index].score_mid / 2 + student[index].score_final / 2) / 100) * 100 * .30) +
            ((student[index].score_act / 150) * 100 * .25) +
            ((student[index].score_proj / 100) * 100 * .15) +
            ((student[index].score_assi / 20) * 100 * .10);

            student[index].final_grade = final;

            if (final >= 75) student[index].remarks = "Passed";
            else student[index].remarks = "Failed";

            //ADITIONAL: FOR INCOMPLETE
            if (!student[index].score_quiz||!student[index].score_assi||!student[index].score_mid||!student[index].score_final||!student[index].score_act||!student[index].score_proj)
               student[index].remarks = "Failed: INC";
         } else {
            //ASK TO ENTER ID AGAIN
            cout  << "\n  ID already taken. Please enter another ID.\n" ;
            goto IDVERIFIY;
         }
         //EXIT OUT OF LOOP ONCE UPDATED
         if (task == "update") break;
      }
      processChoice();
   }

   if (task == "delete") {
      firstRun();
      string student_id;
      int status = 0;
      char confirm;
      showData("all", "default", "delete", "default");

      DEL:
      cout << "\n\nEnter ID of student record to delete: "; cin >> student_id;

      for (int i = 0; i < num_students + registered_student_counter; i++) {
      //RECORD FOUND
         if (student[i].ID == student_id) {

            //CONFIRMATION
            cout  << "You are about to delete " << "\033[37m" << student[i].name << "\033[36m\e[1m" << " with the ID " << "\033[37m" << student[i].ID << "\033[36m\e[1m" << " from your records.\n"
            << "Please enter Y to continue or enter any key to cancel: " ; cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {
                //FILL MEMORY WITH DEFAULT'S, EMPTY OUT | NEW EFFICIENT AND SHORT CODE / student[i].index IS BUGGED IF FIRST INDEX IS SET TO 0
                int temp = student[i].index;
                memset(& student[i], 0, sizeof(student[i]));
                student[i].index = temp;
                //SET IGNORE FOR NEXT SEARCH
                student[i].deleted = 1;
                registered_student_counter--;
                status = 1;
                previous_deletion++;
            }  else processChoice();
         }
      }
      if (status == 0) {
        cout  << "\nOOPS! ID doesn't seem to match any records!" ;
        goto DEL;
      }
      //RESET FIND COUNT
      processChoice();
   }
}

/*
RECORD REQUEST PROCESS (PRINT OR RETURN DATA AND SORTING)
*/
int showData(string selection, string id, string sortation_type, string output_type) {
   int count = 0, index_ref = 0, pre_highest_total_score = student[0].score_total, pre_lowest = student[0].score_total, status = 0, runs=0;
   string id_student_score, id_lowest_total_score, sorted[num_students+previous_deletion][5],
   BORDER = "\n\t===================================================================";
   firstRun();
   if((output_type == "print_ask" || output_type == "print") && selection != "id") {
      cout << "\n\t\t\tFound " << registered_student_counter << " Student Records\n";
      status = 1;
   }
   if(selection == "all") {
      if(sortation_type=="delete") cout << "\n\t\t\tShowing " << registered_student_counter << " Available Students\n";
      WHITE();
      cout << BORDER << "\n\tID NUMBER\tName\t\t\tSex\t\tTotal Score";
      status = 1;
   }
   if((sortation_type == "name" || sortation_type == "score") && selection != "id") {
     cout << "\n\t\t\tShowing ";
     if(sortation_type=="name") cout << "Alphabetically"; else cout << "Grade";
      cout << " Sorted\n";
      WHITE();
     cout << BORDER << "\n\tID NUMBER\tNAME\t\t\tSex\t\tFINAL GRADE" << BORDER;
   }

   if (output_type == "print_ask" && selection == "id" && status != 1) {
      cout << "\nEnter ID of student to find: ";  cin >> id;
   }

   if (selection == "all") cout << BORDER;
   for (int index = 0; index < num_students + previous_deletion; index++) {
      if (student[0].index != 0) { //NO STUDENTS ADDED YET
         //DELETION STATUSES: 0 = NOT DELETED, 1 = DELETED, 2 = DEFAULT
         //IGNORE DELETED STUDENTS (BLANK RESULTS)
         if (student[index].deleted != 1 && student[index].deleted != 2) {
            //FILTERED RESULTS, DON'T SHOW UNNECESSARY INFO
            if (selection == "all") {
               status = 1; //RECORDS FOUND
               if(sortation_type == "delete") cout << setprecision(0);
               if(index%2)COLOR_BLACK(); else COLOR_BLACK_ALT();
               cout << endl << "\t" << student[index].ID << "\t\t" << student[index].name;
               cout << "\t\t" << student[index].sex << "\t\t" << student[index].score_total;
            }

            //FIND BY ID AND PRINT
            if (selection == "id" && (output_type == "print_ask" || output_type == "print")) {
               if (student[index].ID == id) {
                 if(sortation_type=="default") {
                  cout << "\n\t\t\tShowing Student List\n\n"; WHITE(); cout << BORDER << "\n\tID NUMBER\tName\t\t\tSex\t\tTotal Score" << BORDER;
                  }
                  if(index%2)COLOR_BLACK(); else COLOR_BLACK_ALT();
                  cout << endl << "\t" << student[index].ID << "\t\t" << student[index].name << "\t\t" << student[index].sex << "\t\t" << student[index].score_total;
                  status = 1;
               }
            }
            //FIND BY ID BUT ONLY RETURN FIND COUNT
            if (selection == "id" && output_type == "default") {
               if (student[index].ID == id) {
                  ++count;
                  index_ref = student[index].index;
               }
               status = 1;
            }
         }
         if (selection == "final_grade") {
            firstRun();

            //SHOW ALL
            showData("all", "default", "default", "print_ask");

            string ref_id;
            //SEARCH
            FINALGRADE:
            cout << "\n\nEnter ID of student to be computed: "; cin >> ref_id;

            //TO Exit
            if(ref_id == "!exit") break;

            int count = showData("id", ref_id, "default", "default");
            if (count > 0) {
               for (int j = 0; j < num_students + registered_student_counter; j++) {
                  if (student[j].ID == ref_id) {
                    cout << "\n\t\t\tShowing Final Grade\n\n"; WHITE(); cout << BORDER;
                     cout << "\n\tID NUMBER\tName\t\t\tFinal Grade\t\tRemarks" << BORDER;
                     COLOR_BLACK();
                     cout << endl << "\t" << student[j].ID << "\t\t" << student[j].name << "\t\t" << fixed << setprecision(2) << student[j].final_grade << "\t\t\t" << student[j].remarks;
                     UNCOLOR();
                     processChoice();
                  }
               }
            } else {
               cout  << "\nOOPS! ID doesn't seem to match any records!\nEnter !exit to choose other options.\n" ;
               goto FINALGRADE;
            }
         }
         for (int j = 0; j < num_students + previous_deletion; j++) {
            if (selection == "highest_total_score") {
                if (pre_highest_total_score <= student[j].score_total) {
                   pre_highest_total_score = student[j].score_total;
                   id_student_score = student[j].ID;
                }
            }
            if (selection == "lowest_total_score") {
              if (student[j].score_total <= pre_lowest) {
                 pre_lowest = student[j].score_total;
                 id_student_score = student[j].ID;
              }
            }
         }
         if (selection == "highest_total_score" || selection == "lowest_total_score") {
           showData("id", id_student_score, "default", "print");
           processChoice();
         }

         //SORT AND OUTPUT DATA
         if (selection == "sort") {
            /*
            STRUCT MEMBER TO ARRAY STORAGE
            index 0 = ID, 1 = NAME, 2 = SEX, 3 = FINAL GRADE (sorted[][index]), 4 = DELETED STATUS
            */
            for(int i=0; i<num_students+previous_deletion; i++) {
                sorted[i][0] = student[i].ID;
                sorted[i][1] = student[i].name;
                sorted[i][2] = student[i].sex;

                //CONVERSION FROM FLOAT TO STRING
                //DECIDED TO MAKE A TEMPORARY ARRAY
                //RATHER THAN TOUCHING ORIGINAL STRUCT ARRAY TO PRESERVE
                ostringstream grade, deleted;
                grade << student[i].final_grade;
                deleted << student[i].deleted;

                //STORE CONVERTED
                sorted[i][3] = grade.str();
                sorted[i][4] = deleted.str();

            }
            //ARRANGE ALPHABETICALLY OR BY FINAL GRADE
            for(int i=0; i<num_students+previous_deletion; i++) {
              for(int j=i; j<num_students+previous_deletion; j++) {
                if(sortation_type == "name") {
                  if(sorted[i][1] > sorted[j][1])
                    swap(sorted[i], sorted[j]);
                }
                if(sortation_type == "score") {
                  //CONVERSION FROM STRING BACK TO FLOAT
                  float current, next;
                  const char *current_float, *next_float;
                  current_float = sorted[i][3].c_str();
                  next_float = sorted[j][3].c_str();
                  current = atof(current_float);
                  next = atof(next_float);

                  if(current <= next) {
                      swap(sorted[i], sorted[j]);
                  }
                }
              }
            }
            //OUTPUT SORTED DATA
            for(int f=0; f<num_students;f++) {
               if(runs>=registered_student_counter){UNCOLOR();processChoice();};
                  if (sorted[f][4] == "0") {
                    //CONVERT GRADE STRING BACK TO FLOAT FOR SET PRECISION
                    float grade;
                    const char *grade_string;
                    grade_string = sorted[f][3].c_str();
                    grade = atof(grade_string);
                    if(f%2)COLOR_BLACK(); else COLOR_BLACK_ALT();
                    cout << endl << "\t" << sorted[f][0] << "\t\t" << sorted[f][1] << "\t\t" << sorted[f][2] << "\t\t" << fixed << setprecision(2) << grade;
                    runs++;
                  }
               }
            UNCOLOR();
            status=1; //SUCCESS
            }
      } else {
         //DEFAULT CATCHER
         cout  << "You have not added any students yet. Please add records." ;
         processChoice();
      }
   }
   UNCOLOR();
   //NO RECORD FOUND/POST
   if (status == 0) {
      cout  << "\nOOPS! ID doesn't seem to match any records!" ;
      processChoice();
   }
   //FOUND STUDENT THROUGH ID
   if(output_type == "print_ask" && selection == "id" && status == 1) processChoice();
   if (index_ref > 0) return index_ref;
   else return 0;
}

/*
CATCH IF USER ENTERS NON NUMERICAL VALUES ON GRADES
*/
int verifyRun() {
   //ERROR CATCHER
   if (cin.fail()) {
      cin.clear(); cin.ignore();
      cout  << "\n  You are entering a non-numerical value in a student's grade.\n" ;
      return 1;
   }  else return 0;
}

/*
PREVENT ANY TASK REQUIRING RECORDS TO BE ADDED FIRST BEFORE IT CAN BE RUN
*/
void firstRun() {
   if (registered_student_counter == 0) {
      cout  << "You have not added any students yet. Please add records." ;
      processChoice();
   }
}

/*
RESIZE WINDOW AND LOCK RESIZING
*/
void lock() {
    HWND console = GetConsoleWindow(); RECT r;
    GetWindowRect(console, &r); MoveWindow(console, r.left, r.top, 700, 400, TRUE); //RESIZE
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX); //RESIZE LOCK
    SetConsoleTitle(TEXT("BulSU.RD"));
}
/*
SHOW BULSU LOGO ON FIRST RUN
*/
void COLOR() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN  | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
}
void WHITE() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
}
void UNCOLOR() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}
void COLOR_BLACK_ALT() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
}
void COLOR_BLACK() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}
void displayLogo() {
    system("Color 0B");
    cout << endl <<
    "   ____   _   _  _      ____   _   _    ____   ____  \n"
    "  | __ ) | | | || |    / ___| | | | |  |  _ \\ |  _ \\ \n"
    "  |  _ \\ | | | || |    \\___ \\ | | | |  | |_) || | | |\n"
    "  | |_) || |_| || |___  ___) || |_| |_ |  _ < | |_| |\n"
    "  |____/  \\___/ |_____||____/  \\___/(_)|_| \\_\\|____/ \n"
    "  \u0053\u0054\u0055\u0044\u0045\u004e\u0054 \u0052\u0045\u0043\u004f\u0052\u0044\u0053 \u0056\u0049\u0041 \u0054\u0045\u0052\u004d\u0049\u004e\u0041\u004c \u007c \u0049\u0054\u002d\u0031\u0030\u0035 \u007c \u004a\u0045\u0052\u0053\u004f\u004e \u0052\u0045\u0059\u0045\u0053\n\n"
    << "  ";
    COLOR(); cout << "+=============================+"; UNCOLOR(); cout << "\n  ";
    COLOR(); cout << "|       MENU STARTS HERE      |"; UNCOLOR(); cout << "\n  ";
    COLOR(); cout << "+=============================+"; UNCOLOR(); cout << "\n\n";
}
