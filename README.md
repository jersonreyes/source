

# C++ PROJECT 

*Para sa mga walang magamit na computer ngayong quarantine at sa mga madaming iniisip at hindi maisingit dahil sa sitwasyon. I'm with you guys <3 
Pero hindi ko muna binuo. Kailangan talaga matuto tayo eh. Kasi wala ring silbi pagaaral kung hindi mo pinagaaralan. Nandito na lahat guys. May comments naman sa loob ng code. Analyze niyo na lang at gawa kayo ng sarili niyong version or kopya ng mga parte depende sa pangangailangan. Kunin niyo lang yung pinaka idea. Sure akong malalaman agad ni maam pag kinopya niyo lahat. Nonetheless God bless guys keep safe!* 

<img src="bulsu.rd.png" width="100%">

Final output nung sakin. Download niyo na lang kung gusto niyo i-analyze.   
**EXE Application. Pwede i-run:** https://git.io/JJnjx   
**PDF Documentation:** https://git.io/JJnjN   
**Final code ko:** https://git.io/JJnj1   


Iba yung code nung sakin kasi may sinubukan akong ibang approach. Wag niyo kopyahan guys.   
Alam ni ma'am yung style ko please wag niyo na subukan para hindi tayo mapahamak HAHAHAHA.

# MAIN CODE
**UPDATE:** Marami akong binagong line sa code. Kung nakopya niyo na nung una, kopyahin niyo ulit. Important yung mga pinalitan kong line. Salamat!
### HEADER & DECLARATION

    #include <iostream>
    #include <iomanip>
    #include <stdlib.h>
    
    using namespace std;
    
    struct StudRec {
      string ID, remarks;
      float score_quiz, score_assi, score_act, score_proj, score_mid, score_final, score_total, final_grade;
      char name[25], sex;
      int index, deleted = -1;
    } student[25];
    
    // PALITAN NIYO YUNG num_students KUNG ILAN GUSTO NIYONG MALALAGYAN NG INFO (ILANG ULIT MANGHIHINGI)
    void findLowest(), findHighest(), findRec(), sortName(), sortGrade(), calculate(), showAll(), create(int ref_id), modify(), del(), displayMenu(), firstRun();
    int idExists(string referred_id), verifyRun(), num_students = 2, student_counter = 0;
    
    int main() {
      displayMenu(); return 0;
    }

### PROCESS TASK SELECTION

    void processChoice() {
      string choice;
      cout << "\n\nEnter task: ";
      cin >> choice;
    
      if (choice == "1")
        create(-1);
      else if (choice == "2")
        del();
      else if (choice == "3")
        modify();
      else if (choice == "4") {
        showAll();
        processChoice();
      } else if (choice == "5")
        calculate();
      else if (choice == "6")
        findHighest();
      else if (choice == "7")
        findLowest();
      else if (choice == "8")
        findRec();
      else if (choice == "9")
        sortGrade();
      else if (choice == "10")
        sortName();
      else if (choice == "x" || choice == "X") {
        cin.ignore();
        system("cls");
        cout << "Thank you for using the program\n\n\n";
        exit;
      } else if (choice == "m" || choice == "M") {
        displayMenu();
      } else {
        cout << "You've entered an invalid option. Please try again.";
        processChoice();
      }
    }

### MENU

    void displayMenu() {
      cout << "[1] Add student records\n"
              "[2] Delete student records\n"
              "[3] Update student records\n"
              "[4] View all student records\n"
              "[5] Calculate the final grade of a selected student\n"
              "[6] Show student who gets the max total score\n"
              "[7] Show student who gets the min total score\n"
              "[8] Find student by ID\n"
              "[9] Sort records by total scores\n"
              "[10] Sort records by student's name\n\n"
              "[M] Display the Menu\n"
              "[X] Exit the Program\n";
      processChoice();
    }

### CREATE

    void create(int ref_id) {
      int index, j, student_num = 0, runs=0, limit=0;
      char prename[25], sex;
      string id;
    
      //EXIT IF MAX STUDENT NUMBER IS REACHED
        if (student_counter>=num_students) {
            cout << "Maximum amount of students reached";
            processChoice();
        }
    
      for (int i=0; i < num_students; i++) {
    
        //ADJUST INDEX TO LAST DELETED INDEX TO OVERWRITE | BEST METHOD | LESS COMPLICATED
        for(int f=0; f < num_students; f++)
        if(student[f].deleted == 1)
            i = f;
    
        if (student_counter>=num_students) //EXIT IF MAX (FOR NEW RECORD CREATION)
            processChoice();
    
        // FOR NEW RECORDS/DEFAULT + INCREMENT STUDENT COUNTER
        student_counter++;
        student[i].index = student_counter;
        student[i].deleted = 0;
    
        cout << "\nEnter Student"
             << " Name"
             << "\t|   ";
        cin.ignore();
        cin.getline(student[i].name, 25);
    
      IDVERIFY:
        cout << "Enter ID number"
             << "\t\t|   ";
        cin >> id;
    
        int find = idExists(id);
    
        // IF ID IS NON-EXISTENT, CONTINUE
        if (find < 0) {
          // STORE ID
          student[i].ID = id;
          cout << "Enter Sex"<< "\t\t|   ";cin.ignore();cin >> student[i].sex;
          cout << "Score in Quiz"<< "\t\t|   ";cin.ignore();cin >> student[i].score_quiz;
          cout << "Score in Assignment"<< "\t|   ";cin >> student[i].score_assi;
          cout << "Score in Midterm Exam"<< "\t|   ";cin >> student[i].score_mid;
          cout << "Score in Final Exam"<< "\t|   ";cin >> student[i].score_final;
          cout << "Score in Activity"<< "\t|   ";cin >> student[i].score_act;
          cout << "Score in Project"<< "\t|   ";cin >> student[i].score_proj;
    
          // PRE-COMPUTE DATA BEFORE LEAVING
          int total = student[i].score_quiz + student[i].score_assi +
                      student[i].score_mid + student[i].score_final +
                      student[i].score_act + student[i].score_proj;
          student[i].score_total = total;
    
          // FOR FINAL GRADE
          float final =
              ((student[i].score_quiz / 150) * 100 * .20) +
              (((student[i].score_mid / 2 + student[i].score_final / 2) / 100) * 100 * .30) +
              ((student[i].score_act / 150) * 100 * .25) +
              ((student[i].score_proj / 100) * 100 * .15) +
              ((student[i].score_assi / 20) * 100 * .10);
    
          student[i].final_grade = final;
    
          if (final >= 75)
            student[i].remarks = "Passed";
          else
            student[i].remarks = "Failed";
        } else {
          // ASK TO ENTER ID AGAIN
          cout << "\nID already taken. Please enter another ID.\n";
          goto IDVERIFY;
        }
      }
      processChoice();
    }

### DELETE

    void del() {
      firstRun();
      string student_id;
      int status = 0;
      char confirm;
    
      showAll();
    
    DEL:
      cout << "\n\nEnter ID of student record to delete: ";
      cin >> student_id;
    
      for (int i = 0; i < num_students; i++) {
        // RECORD FOUND
        if (student[i].ID == student_id) {
          // CONFIRMATION
          cout
              << "Confirm Delete. Enter Y to continue or enter any key to cancel: ";
          cin >> confirm;
    
          if (confirm == 'y' || confirm == 'Y') {
            // SET IGNORE FOR NEXT SEARCH
            // YOU CAN ASSIGN STRUCT MEMBERS TO NULL TO FREE MEMORY.
            // EXAMPLE student[i].name = "NULL";
            // KASO HAHABA YUNG CODE. DEPENDE SA INYO :)
            student[i].deleted = 1;
            student[i].index = -1;
            student[i].ID = "NULL";
            status = 1;
            student_counter--;
          } else
            processChoice();
        }
      }
      if (status == 0) {
        cout << "\nOOPS! ID doesn't seem to match any records!";
        goto DEL;
      }
      // RESET FIND COUNT
      processChoice();
    }

### MODIFY

    void modify() {
      firstRun();
      string id;
      int ref_id;
    
    MOD:
      cout << "\n\nEnter ID of student to be modified: ";
      cin >> id;
    
      int i = idExists(id);
    
      // DON'T LET IT PASS IF NOT FOUND, LOOP
      if (i < 0) {
        cout << "OOPS! ID doesn't seem to match any records!\n";
        goto MOD;
      } else {
        cout << "\nEnter Student"
             << " Name"
             << "\t|   ";
        cin.ignore();
        cin.getline(student[i].name, 25);
    
      IDVERIFY:
        cout << "Enter ID number"
             << "\t\t|   ";
        cin >> id;
        int find = idExists(id);
    
        // IF ID IS NON-EXISTENT, CONTINUE
        if (find < 0) {
          // STORE ID
          student[i].ID = id;
          cout << "Enter Sex"<< "\t\t|   ";cin.ignore();cin >> student[i].sex;
          cout << "Score in Quiz"<< "\t\t|   ";cin.ignore();cin >> student[i].score_quiz;
          cout << "Score in Assignment"<< "\t|   ";cin >> student[i].score_assi;
          cout << "Score in Midterm Exam"<< "\t|   ";cin >> student[i].score_mid;
          cout << "Score in Final Exam"<< "\t|   ";cin >> student[i].score_final;
          cout << "Score in Activity"<< "\t|   ";cin >> student[i].score_act;
          cout << "Score in Project"<< "\t|   ";cin >> student[i].score_proj;
    
          // PRE-COMPUTE DATA BEFORE LEAVING
          int total = student[i].score_quiz + student[i].score_assi +
                      student[i].score_mid + student[i].score_final +
                      student[i].score_act + student[i].score_proj;
          student[i].score_total = total;
    
          // FOR FINAL GRADE
          float final =
              ((student[i].score_quiz / 150) * 100 * .20) +
              (((student[i].score_mid / 2 + student[i].score_final / 2) / 100) *
               100 * .30) +
              ((student[i].score_act / 150) * 100 * .25) +
              ((student[i].score_proj / 100) * 100 * .15) +
              ((student[i].score_assi / 20) * 100 * .10);
    
          student[i].final_grade = final;
    
          if (final >= 75)
            student[i].remarks = "Passed";
          else
            student[i].remarks = "Failed";
        } else {
          // ASK TO ENTER ID AGAIN
          cout << "\nID already taken. Please enter another ID.\n";
          goto IDVERIFY;
        }
      }
      processChoice();
    }

### ID CHECK

*Return student index from ID. Can also be used to check if ID already exists*

    int idExists(string referred_id) {
      int i = -1;
      for (int z = 0; z < num_students; z++) {
        if (student[z].ID == referred_id) {
          i = z;
          if(i==0)i==1;
        }
      }
      return i; //RETURN VALUE
    }

### SHOW ALL

    void showAll() {
      firstRun();
      cout << "\nID NUMBER\tName\t\t\tSex\t\tTotal Score";
      for (int index = 0; index < num_students; index++) {
          // IGNORE DELETED STUDENTS (BLANK RESULTS)
          if (student[index].deleted != 1 && student[index].deleted != -1) {
            cout << endl << student[index].ID << "\t\t" << student[index].name;
            cout << "\t\t" << student[index].sex << "\t\t"
                 << student[index].score_total;
          }
      }
    }

### FINAL GRADE

    void calculate() {
      firstRun();
      string ref_id;
    // SEARCH
    FINALGRADE:
      cout << "\n\nEnter ID of student to be computed: ";
      cin >> ref_id;
      int find = idExists(ref_id);
    
      if (find >= 0) {
        for (int j = 0; j < num_students; j++) {
          if (student[j].ID == ref_id) {
            cout << "\nShowing Final Grade\n\n";
            cout << "\nID NUMBER\tName\t\t\tFinal Grade\t\tRemarks";
            cout << endl
                 << student[j].ID << "\t\t" << student[j].name << "\t\t" << fixed
                 << setprecision(2) << student[j].final_grade << "\t\t\t"
                 << student[j].remarks;
            processChoice();
          }
        }
      } else {
        cout << "\nOOPS! ID doesn't seem to match any records!\n";
        goto FINALGRADE;
      }
    }

### SORT BY NAME

    void sortName() {
      firstRun();
      for (int i = 0; i < num_students; i++) {
        for (int j = i; j < num_students; j++) {
          if (string(student[i].name) > string(student[j].name) && student[j].deleted == 0 && student[j].index != -1) {
            swap(student[i].ID, student[j].ID);
            swap(student[i].index, student[j].index);
            swap(student[i].score_total, student[j].score_total);
            swap(student[i].remarks, student[j].remarks);
            swap(student[i].score_final, student[j].score_final);
            swap(student[i].name, student[j].name);
            swap(student[i].sex, student[j].sex);
            swap(student[i].final_grade, student[j].final_grade);
            swap(student[i].deleted, student[j].deleted);
          }
        }
      }
      // OUTPUT SORTED DATA
      cout << "\nList Sorted by Name\n\n";
      cout << "\nID NUMBER\tNAME\t\t\tSex\t\tFINAL GRADE";
      for (int f = 0; f < num_students; f++) {
        if (student[f].deleted == 0) {
          cout << endl
               << student[f].ID << "\t\t" << student[f].name << "\t\t"
               << student[f].sex << "\t\t" << fixed << setprecision(2)
               << student[f].final_grade;
        }
      }
      processChoice();
    }

### SORT BY GRADE

    void sortGrade() {
      firstRun();
      for (int i = 0; i < num_students; i++) {
        for (int j = i; j < num_students; j++) {
          if (student[i].final_grade <= student[j].final_grade && student[i].deleted == 0 && student[j].index != -1) {
            swap(student[i].ID, student[j].ID);
            swap(student[i].index, student[j].index);
            swap(student[i].score_total, student[j].score_total);
            swap(student[i].remarks, student[j].remarks);
            swap(student[i].score_final, student[j].score_final);
            swap(student[i].name, student[j].name);
            swap(student[i].sex, student[j].sex);
            swap(student[i].final_grade, student[j].final_grade);
            swap(student[i].deleted, student[j].deleted);
          }
        }
      }
      // OUTPUT SORTED DATA
      cout << "\nList Sorted by Grade\n\n";
      cout << "\nID NUMBER\tNAME\t\t\tSex\t\tFINAL GRADE";
      for (int f = 0; f < num_students; f++) {
        if (student[f].deleted == 0) {
          cout << endl
               << student[f].ID << "\t\t" << student[f].name << "\t\t"
               << student[f].sex << "\t\t" << fixed << setprecision(2)
               << student[f].final_grade;
        }
      }
      processChoice();
    }

### FIND BY ID

    void findRec() {
      firstRun();
      string id;
    
    MOD:
      cout << "\n\nEnter ID of student to find: ";
      cin >> id;
    
      int i = idExists(id);
    
      // DON'T LET IT PASS IF NOT FOUND, LOOP
      if (i < 0) {
        cout << "OOPS! ID doesn't seem to match any records!\n";
        goto MOD;
      } else {
        for (int index = 0; index < num_students; index++) {
            if (student[index].ID == id) {
              cout << "\nStudent Found\n\n";
              cout << "\nID NUMBER\tName\t\t\tSex\t\tTotal Score";
              cout << endl
                   << student[index].ID << "\t\t" << student[index].name << "\t\t"
                   << student[index].sex << "\t\t" << student[index].score_total;
            }
        }
      }
      processChoice();
    }

### HIGHEST GRADE HOLDER

    void findHighest() {
      firstRun();
      int index = 0, current_value = 0;
    
      for(int i=0; i < num_students; i++)
        if(student[i].ID != "NULL") {
            current_value = student[i].score_total;
            break;
        }
    
      for (int j = 0; j < num_students; j++) {
        if (current_value <= student[j].score_total && student[j].ID != "NULL") {
          current_value = student[j].score_total;
          index = j;
        }
      }
      cout << "\nShowing Highest Grade Holder\n\n";
      cout << "\nID NUMBER\tName\t\t\tSex\t\tTotal Score";
      cout << endl
           << student[index].ID << "\t\t" << student[index].name << "\t\t"
           << student[index].sex << "\t\t" << student[index].score_total;
      processChoice();
    }

### FIND LOWEST

    void findLowest() {
      firstRun();
      int index = 0, current_value=0;
    
      for(int i=0; i < num_students; i++)
        if(student[i].ID != "NULL") {
            current_value = student[i].score_total;
            break;
        }
    
      for (int j = 0; j < num_students; j++) {
        if (student[j].score_total <= current_value && student[j].ID != "NULL") {
          current_value = student[j].score_total;
          index = j;
        }
      }
      cout << "\nShowing Lowest Grade Holder\n\n";
      cout << "\nID NUMBER\tName\t\t\tSex\t\tTotal Score";
      cout << endl
           << student[index].ID << "\t\t" << student[index].name << "\t\t"
           << student[index].sex << "\t\t" << student[index].score_total;
      processChoice();
    }

### EXTRA GUARD

Prevent any task from starting by requiring records to be added first.

    void firstRun() {
      if (student_counter == 0) {
        cout << "You have not added any students yet. Please add records.";
        processChoice();
      }
    }
