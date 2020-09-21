// Include Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Color Constants
#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE   "\x1B[34m"
#define MAGENTA   "\x1B[35m"
#define CYAN   "\x1B[36m"
#define WHITE   "\x1B[37m"
#define RESET "\x1B[0m"

// Data Structure
typedef struct Entries {
    char
    /*1*/ name[20], // Firstname Lastname
    /*2*/ connection[15], // Broadband, WiFi, 2G, 3G, 4G
    /*3*/ usage[20], // Social, News, Entertainment, Work, Academic
    /*4*/ area[10]; // Bashundhara, Mirpur, Uttara, Dhanmondi, Gulshan, Banani, Motijheel, Cantonment, Others
    /*5*/ int age; // 34
    /*6*/ float hours; // 5.5
} Entries;

// File IO Functions
int readNumOfEntriesFromFile();
Entries* readFromFile();
void appendToFile(Entries Entry);
void writeToFile(Entries EntriesArr[], int entriesNo);

// Menu Functions
void mainMenu(); // Show The Menu
void adminMenuAuth(); // Admin Menu Authenication
void pageTitle(char title[]); // Show Title of the App, Page and call fflush()
void adminMenu(); // Show Admin Panel - Tashfi

// Feature Functions
void askSurvey(); // Ask Questions & Save Them
void modifyAnEntry(); // Edit an Entry and ReWrite Whole File
void deleteAnEntry(); // Delete an Entry and ReWrite Whole File
void listAll(); // Show All Entries
void searchByName(); // Show Entry Matching Name
void searchByArea(); // Show Entry/Entries Matching Area
void searchByAge(); // Show Entry/Entries Matching Age Interval
void compareUsageByArea(); // Compare All Areas Usage by Average of Users From  Each Area
void barChartAgeVsHours(); // Show Age vs Hours Barchart
void pyramidConnection(); // Pyramid of Internet Connection Usage from Low to High

// Test Function
void Test();
void Test(){

    // Single Entry
    Entries Entry;
    printf("%s\n",Entry.name);
    printf("%s\n", Entry.connection);
    printf("%s\n", Entry.usage);
    printf("%s\n", Entry.area);
    printf("%d\n", Entry.age);
    printf("%.1f\n", Entry.hours);
}

// Main
int main(){
    mainMenu();
    modifyAnEntry();
    return 0;
}
// Read From File & Return Number of Entries
// Params: void
// Return:int entriesNum
int readNumOfEntriesFromFile(){
    FILE *entriesFile;
    entriesFile = fopen("database/entries.txt", "r");

    int lines = 0;
    for(char c=getc(entriesFile); c!=EOF; c=getc(entriesFile)){
            if(c=='\n'){
                lines++;
            }
    }
    fclose(entriesFile);

    int entriesNum = lines/6;

    return entriesNum;
}
// Read From File
// Params: void
// Return: struct EntriesArr[]
Entries* readFromFile(){
    readNumOfEntriesFromFile();
    static Entries EntriesArr[3];

    FILE *entriesFile;
    entriesFile = fopen("database/entries.txt", "r");

    if(entriesFile == NULL){
        printf("Ooops! No Entries Found :/\n");
    }

    for(int i=0; i<readNumOfEntriesFromFile(); i++){
        fscanf (entriesFile, "%[^\n]s",EntriesArr[i].name);
        fscanf (entriesFile, "%s",EntriesArr[i].usage);
        fscanf (entriesFile, "%s",EntriesArr[i].connection);
        fscanf (entriesFile, "%s",EntriesArr[i].area);
        fscanf (entriesFile, "%d ",&EntriesArr[i].age);
        fscanf (entriesFile, "%f ",&EntriesArr[i].hours);
    }

    fclose(entriesFile);

    return EntriesArr;
}
// Append To File
// Params: struct Entries Entry
// Return: void
void appendToFile(Entries Entry){



    FILE *entriesFile;
    entriesFile = fopen("database/entries.txt", "a");

    fprintf(entriesFile, "%s\n",Entry.name);
    fprintf(entriesFile, "%s\n",Entry.usage);
    fprintf(entriesFile, "%s\n",Entry.connection);
    fprintf(entriesFile, "%s\n",Entry.area);
    fprintf(entriesFile, "%d\n", Entry.age);
    fprintf(entriesFile, "%.1f\n", Entry.hours);

    fclose(entriesFile);
}
// Write To File
// Params: struct Entries[]
// Return: void
void writeToFile(Entries *EntriesArr, int entriesNo){
    FILE *entriesFile;
    entriesFile = fopen("database/entries.txt", "w");

    for(int i=0; i<entriesNo; i++){
        fprintf(entriesFile, "%s\n",EntriesArr[i].name);
        fprintf(entriesFile, "%s\n",EntriesArr[i].usage);
        fprintf(entriesFile, "%s\n",EntriesArr[i].connection);
        fprintf(entriesFile, "%s\n",EntriesArr[i].area);
        fprintf(entriesFile, "%d\n", EntriesArr[i].age);
        fprintf(entriesFile, "%.1f\n", EntriesArr[i].hours);
    }

    fclose(entriesFile);
}



// Title of The App, Page, fflush(stdin)
void pageTitle(char title[]){
    system("cls");
    puts(CYAN "------------------------------------------------------");
    puts(" Survey Entry and Analyser - Internet Usage       ");
    puts("------------------------------------------------------");
    printf(" %s\n", title);
    puts("------------------------------------------------------");
    puts(RESET);

    fflush(stdin);
}



// Menu To Choose Survey/Admin
void mainMenu(){
    pageTitle("Main Menu");

    int chc;
    puts("\n1. Enter the survey. \n");
    puts("\n2. Enter Admin Panel. \n");
    puts("\n0. Exit App. ");

    puts("\n\nEnter your choice:");
    scanf("%d", &chc);

    switch (chc) {
        case 1: askSurvey();
        break;
        case 2: adminMenuAuth();
        break;
        default: pageTitle("Dhonnobaad. Abar Ashben. :3"); exit(0);
    }
}
// Admin Authenication
void adminMenuAuth(){
    pageTitle("Login to Admin Panel");

    char user[15], pass[15];
    int matched = 0;

    while(!matched){
        puts("Enter Admin Username: [Hint: admin] ");
        gets(user);
        fflush(stdin);
        puts("Enter Admin Password: [Hint: pass] ");
        gets(pass);
        fflush(stdin);

        if(strcmp(user, "admin") == 0 && strcmp(pass, "pass") == 0){
            adminMenu();
            break;
        } else {
            printf(RED "\n\nIncorrect Username/Password :(\n\n\n" RESET);
        }
    }
}
// The Admin Panel
void adminMenu(){
    pageTitle("Admin Panel");
    int chc;

    puts("1. List All Entries. ");
    puts("\n2. Modify An Entry. ");
    puts("\n3. Delete An Entry. \n");

    puts("\n4. Search Entry By Name. ");
    puts("\n5. Search Entries By Area. ");
    puts("\n6. Search Entries By Age Interval. ");
    puts("\n7. Compare Usage Among Areas. ");
    puts("\n8 Visualize BarChart of Age vs Hours. ");
    puts("\n9. Visualize Pyramid of Internet Connection Types. ");

    puts("\n\n10. Back To Main Menu. ");
    puts("\n0. Exit Application. ");

    puts("\n\nEnter your choice:");
    scanf("%d", &chc);

    switch (chc) {
        case 1: listAll();
        break;
        case 2: modifyAnEntry();
        break;
        case 3: deleteAnEntry();
        break;
        case 4: searchByName();
        break;
        case 5: searchByArea();
        break;
        case 6: searchByAge();
        break;
        case 7: compareUsageByArea();
        break;
        case 8: barChartAgeVsHours();
        break;
        case 9: pyramidConnection();
        break;
        case 10: mainMenu();
        break;
        default: pageTitle("Dhonnobaad. Abar Ashben. :3"); exit(0);
    }
}


// Ask Questions and then Save
void askSurvey(){
    pageTitle("Survey Data Entry");

    Entries Entry;

    // 1
    puts("Your Name? (One Word)");
    gets(Entry.name);
    fflush(stdin);

    // 2
    puts("\nConnection You Use? (One Word)");
    puts("a. Broadband \tb. WiFi \tc. 3G \td. 4G \te. others");
    gets(Entry.connection);
    fflush(stdin);
    if(strcmp(Entry.connection, "a") == 0){
        strcpy(Entry.connection, "Broadband");
    } else if(strcmp(Entry.connection, "b") == 0){
        strcpy(Entry.connection, "WiFi");
    } if(strcmp(Entry.connection, "c") == 0){
        strcpy(Entry.connection, "3G");
    } if(strcmp(Entry.connection, "d") == 0){
        strcpy(Entry.connection, "4G");
    } if(strcmp(Entry.connection, "e") == 0){
        strcpy(Entry.connection, "Others");
    }

    // 3
    puts("\nWhat do you Internet mostly for? (One Word)");
    puts("a. Social \tb. News \tc. Entertainment \td. Work \te. Academic \tf. Others");
    gets(Entry.usage);
    fflush(stdin);
    if(strcmp(Entry.usage, "a") == 0){
        strcpy(Entry.usage, "Social");
    } else if(strcmp(Entry.usage, "b") == 0){
        strcpy(Entry.usage, "News");
    } if(strcmp(Entry.usage, "c") == 0){
        strcpy(Entry.usage, "Entertainment");
    } if(strcmp(Entry.usage, "d") == 0){
        strcpy(Entry.usage, "Work");
    } if(strcmp(Entry.usage, "e") == 0){
        strcpy(Entry.usage, "Academic");
    } if(strcmp(Entry.usage, "f") == 0){
        strcpy(Entry.usage, "Others");
    }

    // 4
    puts("\nYour Area?");
    puts("a. Bashundhara b. Mirpur c. Uttara e. Banani f. Others");
    gets(Entry.area);
    fflush(stdin);
    if(strcmp(Entry.area, "a") == 0){
        strcpy(Entry.area, "Bashundhara");
    } else if(strcmp(Entry.area, "b") == 0){
        strcpy(Entry.area, "Mirpur");
    } if(strcmp(Entry.area, "c") == 0){
        strcpy(Entry.area, "Uttara");
    } if(strcmp(Entry.area, "d") == 0){
        strcpy(Entry.area, "Dhanmondi");
    } if(strcmp(Entry.area, "e") == 0){
        strcpy(Entry.area, "Banani");
    } if(strcmp(Entry.area, "f") == 0){
        strcpy(Entry.area, "Others");
    }

    // 5
    puts("\nYour Age?");
    scanf("%d", &Entry.age);
    fflush(stdin);

    // 6
    puts("\nHow many hours do you spend on the Internet everyday?");
    scanf("%f",&Entry.hours);

    appendToFile(Entry);

    puts(CYAN "\n\n\nPress any key to go back to Main Menu");
    getch();
    mainMenu();
}



// Show All Entries
void listAll(){
    pageTitle("All Entries");
    Entries *EntriesArr = readFromFile();
    int entriesNum = readNumOfEntriesFromFile();

    for(int i=0; i<entriesNum; i++){
        printf("\n\nEntry No.:%d ", i+1);
        puts("\n---------------------------------");
        printf("Name: %s",EntriesArr[i].name);
        puts("");
        printf("Usage: %s",EntriesArr[i].usage);
        puts("");
        printf("Connection: %s",EntriesArr[i].connection);
        puts("");
        printf("Area: %s",EntriesArr[i].area);
        puts("");
        printf("Age: %d ", EntriesArr[i].age);
        puts("");
        printf("Hours: %.1f ", EntriesArr[i].hours);
    }

    puts(CYAN "\n\n\nPress any key to go back to Admin Panel" RESET);
    getch();
    adminMenu();
}
// Read Whole File -> Search Matching Entry -> Edit -> Write Whole File
void modifyAnEntry(){
    pageTitle("Modify An Entry");

    Entries *EntriesArr = readFromFile();

    // Write code here to filter out an entry and modify it
    char name[20];
    int EntriesNum = readNumOfEntriesFromFile();
    puts("Enter 'Name' of the Entry to Modify");
    gets(name);
    char oldName[20];

    for(int i=0; i<EntriesNum; i++){
        strcpy(oldName, EntriesArr[i].name);

        if(strcmp(strupr(oldName), strupr(name)) == 0){
            if(strcmp(strupr(EntriesArr[i].name), strupr(name)) == 0){
                printf("\nMatch Found!\n\nPlease Enter New Info For This Entry.\n\n");
                strcpy(name, "found");

                // 1
                puts("Your Name? (One Word)");
                gets(EntriesArr[i].name);
                fflush(stdin);

                // 2
                puts("\nConnection You Use? (One Word)");
                puts("a. Broadband \tb. WiFi \tc. 3G \td. 4G \te. others");
                gets(EntriesArr[i].connection);
                fflush(stdin);
                if(strcmp(EntriesArr[i].connection, "a") == 0){
                    strcpy(EntriesArr[i].connection, "Broadband");
                } else if(strcmp(EntriesArr[i].connection, "b") == 0){
                    strcpy(EntriesArr[i].connection, "WiFi");
                } if(strcmp(EntriesArr[i].connection, "c") == 0){
                    strcpy(EntriesArr[i].connection, "3G");
                } if(strcmp(EntriesArr[i].connection, "d") == 0){
                    strcpy(EntriesArr[i].connection, "4G");
                } if(strcmp(EntriesArr[i].connection, "e") == 0){
                    strcpy(EntriesArr[i].connection, "Others");
                }

                // 3
                puts("\nWhat do you Internet mostly for? (One Word)");
                puts("a. Social \tb. News \tc. Entertainment \td. Work \te. Academic \tf. Others");
                gets(EntriesArr[i].usage);
                fflush(stdin);
                if(strcmp(EntriesArr[i].usage, "a") == 0){
                    strcpy(EntriesArr[i].usage, "Social");
                } else if(strcmp(EntriesArr[i].usage, "b") == 0){
                    strcpy(EntriesArr[i].usage, "News");
                } if(strcmp(EntriesArr[i].usage, "c") == 0){
                    strcpy(EntriesArr[i].usage, "Entertainment");
                } if(strcmp(EntriesArr[i].usage, "d") == 0){
                    strcpy(EntriesArr[i].usage, "Work");
                } if(strcmp(EntriesArr[i].usage, "e") == 0){
                    strcpy(EntriesArr[i].usage, "Academic");
                } if(strcmp(EntriesArr[i].usage, "f") == 0){
                    strcpy(EntriesArr[i].usage, "Others");
                }

                // 4
                puts("\nYour Area?");
                puts("a. Bashundhara b. Mirpur c. Uttara e. Banani f. Others");
                gets(EntriesArr[i].area);
                fflush(stdin);
                if(strcmp(EntriesArr[i].area, "a") == 0){
                    strcpy(EntriesArr[i].area, "Bashundhara");
                } else if(strcmp(EntriesArr[i].area, "b") == 0){
                    strcpy(EntriesArr[i].area, "Mirpur");
                } if(strcmp(
                            EntriesArr[i].area, "c") == 0){
                    strcpy(EntriesArr[i].area, "Uttara");
                } if(strcmp(EntriesArr[i].area, "d") == 0){
                    strcpy(EntriesArr[i].area, "Dhanmondi");
                } if(strcmp(EntriesArr[i].area, "e") == 0){
                    strcpy(
                           EntriesArr[i].area, "Banani");
                } if(strcmp(EntriesArr[i].area, "f") == 0){
                    strcpy(EntriesArr[i].area, "Others");
                }

                // 5
                puts("\nYour Age?");
                scanf("%d", &EntriesArr[i].age);
                fflush(stdin);

                // 6
                puts("\nHow many hours do you spend on the Internet everyday?");
                scanf("%f",&EntriesArr[i].hours);

                writeToFile(EntriesArr, EntriesNum);
            }
        }
    }

    if(!strcmp(name, "found") == 0){
        printf("\nEntry Not Found :\(");
    }


    puts(CYAN "\n\n\nPress any key to go back to Admin Panel" RESET);
    getch();
    adminMenu();
}
// Read Whole File -> Search Matching Entry -> Delete -> Write Whole File
void deleteAnEntry(){
    pageTitle("Delete An Entry");

    Entries *EntriesArr = readFromFile();

    // Write code here to filter out an entry and modify it
    char name[20];
    int EntriesNum = readNumOfEntriesFromFile();
    puts("Enter 'Name' of the Entry to Delete.");
    gets(name);
    char oldName[20];

    for(int i=0; i<EntriesNum; i++){
        strcpy(oldName, EntriesArr[i].name);

        if(strcmp(strupr(oldName), strupr(name)) == 0){
            printf("\nMatch Found!\n\nSelected Entry Successfully Deleted! \n\n");
            strcpy(name, "found");

            for(int j=i; j<EntriesNum; j++){
                strcpy(EntriesArr[j].name, EntriesArr[j+1].name);
                strcpy(EntriesArr[j].usage, EntriesArr[j+1].usage);
                strcpy(EntriesArr[j].connection, EntriesArr[j+1].connection);
                strcpy(EntriesArr[j].area, EntriesArr[j+1].area);
                EntriesArr[j].age = EntriesArr[j+1].age;
                EntriesArr[j].hours = EntriesArr[j+1].hours;
            }

            writeToFile(EntriesArr, EntriesNum-1);
        }
    }

    if(!strcmp(name, "found") == 0){
        printf("\nEntry Not Found :\(");
    }

    puts(CYAN "\n\n\nPress any key to go back to Admin Panel" RESET);
    getch();
    adminMenu();
}


// Show Entry Matching Name
void searchByName(){
    pageTitle("Search By Name");

    // Write code Here
    Entries *EntriesArr = readFromFile();

    char name[20];
    int EntriesNum = readNumOfEntriesFromFile();
    puts("Enter 'Name' of the Entry to Search.");
    gets(name);
    char oldName[20];

    for(int i=0; i<EntriesNum; i++){
        strcpy(oldName, EntriesArr[i].name);

        if(strcmp(strupr(oldName), strupr(name)) == 0){
            printf("\nMatch Found!\n\n");
            strcpy(name, "FOUND");

            puts("\n---------------------------------");
            printf("Name: %s",EntriesArr[i].name);
            puts("");
            printf("Usage: %s",EntriesArr[i].usage);
            puts("");
            printf("Connection: %s",EntriesArr[i].connection);
            puts("");
            printf("Area: %s",EntriesArr[i].area);
            puts("");
            printf("Age: %d ", EntriesArr[i].age);
            puts("");
            printf("Hours: %.1f ", EntriesArr[i].hours);
            puts("\n---------------------------------");
        }
    }

    if(!strcmp(name, "FOUND") == 0){
        printf("\nEntry Not Found :\(");
    }

    puts(CYAN "\n\n\nPress any key to go back to Admin Panel" RESET);
    getch();
    adminMenu();
}
// Show Entry/Entries Matching Area
void searchByArea(){
    pageTitle("Search By Area");

    // Write code Here
    Entries *EntriesArr = readFromFile();

    char area[20];
    int EntriesNum = readNumOfEntriesFromFile();
    puts("Enter 'Area' of the Entries to Search.");
    gets(area);
    char oldArea[20];
    int count = 0;

    for(int i=0; i<EntriesNum; i++){
        strcpy(oldArea, EntriesArr[i].area);

        if(strcmp(strupr(oldArea), strupr(area)) == 0){
            puts("\n---------------------------------");
            printf("Name: %s",EntriesArr[i].name);
            puts("");
            printf("Usage: %s",EntriesArr[i].usage);
            puts("");
            printf("Connection: %s",EntriesArr[i].connection);
            puts("");
            printf("Area: %s",EntriesArr[i].area);
            puts("");
            printf("Age: %d ", EntriesArr[i].age);
            puts("");
            printf("Hours: %.1f ", EntriesArr[i].hours);
            puts("\n---------------------------------");
        } else count++;
    }

    if(count == EntriesNum){
        printf("\nNo Entries From This Area :\(");
    }

    puts(CYAN "\n\n\nPress any key to go back to Admin Panel" RESET);
    getch();
    adminMenu();
}
// Show Entry/Entries Matching Age Interval
void searchByAge(){
    pageTitle("Search By Age Interval");

    // Write code Here
    Entries *EntriesArr = readFromFile();

    int min, max;
    int EntriesNum = readNumOfEntriesFromFile();
    puts("Enter Minimum Age");
    scanf("%d", &min);
    puts("Enter Maximum Age");
    scanf("%d", &max);
    int count = 0;

    for(int i=0; i<EntriesNum; i++){
        if(min < EntriesArr[i].age && EntriesArr[i].age < max){
            puts("\n---------------------------------");
            printf("Name: %s",EntriesArr[i].name);
            puts("");
            printf("Usage: %s",EntriesArr[i].usage);
            puts("");
            printf("Connection: %s",EntriesArr[i].connection);
            puts("");
            printf("Area: %s",EntriesArr[i].area);
            puts("");
            printf("Age: %d ", EntriesArr[i].age);
            puts("");
            printf("Hours: %.1f ", EntriesArr[i].hours);
            puts("\n---------------------------------");
        } else count++;
    }

    if(count == EntriesNum){
        printf("\nNo Entries From This Age Interval:\(");
    }

    puts(CYAN "\n\n\nPress any key to go back to Admin Panel" RESET);
    getch();
    adminMenu();
}
// Compare All Areas Usage by Average of Users From  Each Area
void compareUsageByArea(){
    pageTitle("Comparison of Usage By Area on Average");

    // Write code Here

    float Bashundhara = 0, Mirpur = 0, Uttara = 0, Dhanmondi = 0,  Banani = 0, Others = 0;

    int BashundharaC = 0, MirpurC = 0, UttaraC = 0, DhanmondiC = 0, BananiC = 0, OthersC = 0;


    Entries *EntriesArr = readFromFile();

    for(int i=0; i<readNumOfEntriesFromFile(); i++){
        if(strcmp(EntriesArr[i].area, "Bashundhara") == 0){
           BashundharaC++;
           Bashundhara += EntriesArr[i].hours;
        }
        if(strcmp(EntriesArr[i].area, "Mirpur") == 0){
           MirpurC++;
           Mirpur += EntriesArr[i].hours;
        }
        if(strcmp(EntriesArr[i].area, "Uttara") == 0){
           UttaraC++;
           Uttara += EntriesArr[i].hours;
        }if(strcmp(EntriesArr[i].area, "Dhanmondi") == 0){
           DhanmondiC++;
           Dhanmondi += EntriesArr[i].hours;
        }if(strcmp(EntriesArr[i].area, "Banani") == 0){
           BananiC++;
           Banani += EntriesArr[i].hours;
        }if(strcmp(EntriesArr[i].area, "Others") == 0){
           OthersC++;
           Others += EntriesArr[i].hours;
        }
    }

    if(BashundharaC > 0) Bashundhara = Bashundhara/BashundharaC;
    if(MirpurC > 0) Mirpur = Mirpur/MirpurC;
    if(UttaraC > 0) Uttara = Uttara/UttaraC;
    if(DhanmondiC > 0) Dhanmondi = Dhanmondi/DhanmondiC;
    if(BananiC > 0) Banani = Banani/BananiC;
    if(OthersC > 0) Others = Others/OthersC;

    puts("Bashundhara     Mirpur          Uttara          Dhanmondi       Banani          Others");
    printf("%.1f Hours \t%.1f Hours \t%.1f Hours \t%.1f Hours \t%.1f Hours \t%.1f Hours \t", Bashundhara, Mirpur, Uttara, Dhanmondi, Banani, Others);

    puts(CYAN "\n\n\nPress any key to go back to Admin Panel" RESET);
    getch();
    adminMenu();
}
// Show Age vs Hours Barchart
void barChartAgeVsHours(){
    pageTitle("Bar Chart Age vs Hours");

    // Write code Here
    Entries *EntriesArr = readFromFile();
    int EntriesNum = readNumOfEntriesFromFile();
    float ageHoursArr[5] = {0, 0, 0, 0, 0};
    int ageCountArr[5] = {0, 0, 0, 0, 0};

    for(int i=0; i<EntriesNum; i++){
        if(EntriesArr[i].age >= 0 && EntriesArr[i].age <=10) { ageHoursArr[0]+=EntriesArr[i].hours; ageCountArr[0]++; }
        if(EntriesArr[i].age >= 11 && EntriesArr[i].age <=15) { ageHoursArr[1]+=EntriesArr[i].hours; ageCountArr[1]++; }
        if(EntriesArr[i].age >= 16 && EntriesArr[i].age <=20) { ageHoursArr[2]+=EntriesArr[i].hours; ageCountArr[2]++; }
        if(EntriesArr[i].age >= 21 && EntriesArr[i].age <=30) { ageHoursArr[3]+=EntriesArr[i].hours; ageCountArr[3]++; }
        if(EntriesArr[i].age >= 30 && EntriesArr[i].age <=100) { ageHoursArr[4]+=EntriesArr[i].hours; ageCountArr[4]++; }
    }

    for(int i=0; i<5; i++){
        ageHoursArr[i] = (float)ageHoursArr[i]/ageCountArr[i]/24*100;
    }



    printf("  AGE \n");
    printf(RESET "-------------------------------------------------------------------------------------------------------------\n");
    for(int i=0; i<5; i++){
        printf(RESET "");
        switch(i){
                 case 0: printf("1 to 10  ");
                 break;
                 case 1: printf("11 to 15 ");
                 break;
                 case 2: printf("16 to 20 ");
                 break;
                 case 3: printf("20 to 30 ");
                 break;
                 case 4: printf("30+      ");
                 break;
        }

        if(i == 0) printf(RED);
        if(i == 1) printf(YELLOW);
        if(i == 2) printf(MAGENTA);
        if(i == 3) printf(BLUE);
        if(i == 4) printf(GREEN);


        for(int j=0; j<ageHoursArr[i]; j++){
            printf("*");
        }
        puts("");
        for(int j=0; j<100+9; j++){
            printf(RESET"-");
        }
        printf("\n");
    }
    printf("HOURS -> |00||01||02||03||04||05||06||07||08||09||10||11||12||13||14||15||16||17||18||18||20||21||22||23||24|\n");
    printf("PER DAY\n");

    puts(CYAN "\n\n\nPress any key to go back to Admin Panel" RESET);
    getch();
    adminMenu();
}
// Pyramid of Internet Connection Usage from Low to High
void pyramidConnection(){
    pageTitle("Pyramid of Connection");

    // Write code
    char conArr[5][20] = {"Broadband", "WiFI", "3G", "4G", "Others"};
    int conCountsArr[5] = {0, 0, 0, 0, 0};

    Entries *EntriesArr = readFromFile();

    for(int i=0; i<readNumOfEntriesFromFile(); i++){
        if(strcmp(EntriesArr[i].connection, "Broadband") == 0){
           conCountsArr[0]++;
        }
        if(strcmp(EntriesArr[i].connection, "WiFi") == 0){
           conCountsArr[1]++;
        }
        if(strcmp(EntriesArr[i].connection, "3G") == 0){
           conCountsArr[2]++;
        }
        if(strcmp(EntriesArr[i].connection, "4G") == 0){
           conCountsArr[3]++;
        }
        if(strcmp(EntriesArr[i].connection, "Others") == 0){
           conCountsArr[4]++;
        }
    }

    int i, j, a;
    char aa[20];
     for (i = 0; i < 5; ++i){
            for (j = i + 1; j < 5; ++j){
                if (conCountsArr[i] < conCountsArr[j]){
                    a = conCountsArr[i];
                    strcpy(aa, conArr[i]);

                    conCountsArr[i] = conCountsArr[j];
                    strcpy(conArr[i], conArr[j]);

                    conCountsArr[j] = a;
                    strcpy(conArr[j], aa);
                }
            }
        }

    int space, rows = 15, k=0;
    for(i=1; i<=rows; i++){
        k=0;
        for(space=1; space<=rows-i; space++){
            printf("  ");
        }
        while(k != 2*i-1){
            if(i>0) printf(RED);
            if(i>3) printf(YELLOW);
            if(i>6) printf(MAGENTA);
            if(i>9) printf(BLUE);
            if(i>12) printf(GREEN);
            printf("* ");
            printf(RESET);
            k++;
        }
        k=0;
        for(space=1; space<=rows-i; space++){
            printf("  ");
        }
        printf("   ");
        if(i==2) printf(RED "%s", conArr[0]);
        if(i==5) printf(YELLOW "%s", conArr[1]);
        if(i==8) printf(MAGENTA "%s", conArr[2]);
        if(i==11) printf(BLUE "%s", conArr[3]);
        if(i==14) printf(GREEN "%s", conArr[4]);
        printf("\n");
    }

    puts(CYAN "\n\n\nPress any key to go back to Admin Panel" RESET);
    getch();
    adminMenu();
}
