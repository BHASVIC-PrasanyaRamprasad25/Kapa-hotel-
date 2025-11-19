//
// Created by prasanya.ramprasad25 on 19/11/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>



// Global variables for guest information
int guestStayLengths[6];
int guestnumber[6];
int guestRoomChoices[6];
char guestBoardTypes[6][3];
char guestBookingIDs[6][80];
bool guestNewspapers[6];
int guestCount = 0;

char firstName[50];
char surName[50];
int adults;
int children;
int stayLength;
int roomChoice;
char boardType[3];
char bookingID[80];
bool newspaper;
bool namecheck;
bool roomsAvailable[6] = {true, true, true, true, true, true};
int roomPrices[6] = {100, 100, 85, 75, 75, 50};
int boardPrices[3] = {20, 15, 5};

/* --- nameCheck, daysInMonth, confirmOrQuit, getBoardPrice, etc. remain unchanged --- */
//TODO Add check out function once complete


int nameCheck(const char *s ) { //validation for name
    int k=0;
    if (strlen(s) >16 || strlen(s) <=0) {
        printf(" The name you entered is either too long or too short \n");
        k++;
    }

    for(int i=0;i<strlen(s);i++) {
        if ((s[i] <65 )||(s[i] <97 && s[i]>90)||( s[i]>122)  ) {
           k++;
        }
    }

    if (k>0){ printf(" The name can't have any unusual characters\n");}
    else if (k==0){return 1;}
}

int daysInMonth(int month) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return 28;
        default: return 0;
    }
}

int confirmOrQuit(const char* question) {
    char c;
    printf("%s (Y/N, Q to quit): ", question);
    scanf(" %c", &c);
    c = toupper(c);
    if (c == 'Q') {return -1;}
    if (c == 'N') {return 0;}
    if (c == 'Y') {return 1;}
    else { return 2;}
}

int getBoardPrice(const char* type) {
    if (strcmp(type, "FB") == 0) return boardPrices[0];
    if (strcmp(type, "HB") == 0) return boardPrices[1];
    if (strcmp(type, "BB") == 0) return boardPrices[2];
    return 0;
}



void checkin() {
    int day, month, year;

    printf("************* Welcome to Kap Hotel Check-in ***********\n");
    printf("You can quit at any question by pressing 'Q'.\n");

    while (true) {
        int p=0;
        do {
            printf("Enter main guest's first name: ");
            scanf("%s", firstName);
            p= nameCheck(firstName );
        }while(p != 1);

        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        int q=0;
       do {
           printf("Enter main guest's surname: ");
           scanf("%s", surName);
            q= nameCheck(surName);
       }while (q != 1);
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        printf("Enter main guest's DOB (DD/MM/YYYY): ");
        if (scanf("%d/%d/%d", &day, &month, &year) != 3) {
            printf("Invalid format.\n");
            while (getchar() != '\n');
            continue;
        }
        if (month < 1 || month > 12 || day < 1 || day > daysInMonth(month)) {
            printf("Invalid date.\n");
            continue;
        }
        if (year>2007) {
            printf("children can't sign up please bring an adult and enter their DOB.\n");
            continue;

        }
        if (year<1925) {
            printf("You can't be more than 100 years old, that is not possible.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;

    }


    while (true) {
        printf("Enter number of adults (16+): ");
        scanf("%d", &adults);
        printf("Enter number of children (15 or under): ");
        scanf("%d", &children);

        if (children > 0 && adults < 1) {
            printf("Children must be accompanied by at least one adult.\n");
            continue;
        }
        if (adults + children > 4) {
            printf("Maximum guests allowed is 4.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        printf("Enter number of days to stay (max 15): ");
        scanf("%d", &stayLength);
        if (stayLength < 1 || stayLength > 15) {
            printf("Invalid stay length.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        printf("Enter board type (HB/FB/BB): ");
        scanf("%s", boardType);
        if (strcmp(boardType, "HB") != 0 &&
            strcmp(boardType, "FB") != 0 &&
            strcmp(boardType, "BB") != 0) {
            printf("Invalid board type.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        printf("\nAvailable rooms:\n");
        for (int i = 0; i < 6; i++)
            printf("Room %d - GBP%d - %s\n", i + 1, roomPrices[i], roomsAvailable[i] ? "Available" : "Occupied");

        printf("Choose room number: ");
        scanf("%d", &roomChoice);

        if (roomChoice < 1 || roomChoice > 6 || !roomsAvailable[roomChoice - 1]) {
            printf("Room unavailable or invalid.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        printf("Do you want a newspaper? (Y/N): ");
        char c;
        scanf(" %c", &c);
        if (toupper(c) == 'Q') return;
        newspaper = (toupper(c) == 'Y');
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    roomsAvailable[roomChoice - 1] = false;
    //generate user's bookingID by concatenating random number and surname
    int r;
    srand(time(NULL));
    r = rand() % 100;
    strcpy(bookingID, surName);
    snprintf(bookingID, sizeof(bookingID), "%s%d", surName, r);

    printf("\nBooking Summary:\n");
    printf("Guest: %s %s\n", firstName, surName);
    printf("Adults: %d, Children: %d\n", adults, children);
    printf("Stay: %d days\n", stayLength);
    printf("Board type: %s (GDP%d per person per day)\n", boardType, getBoardPrice(boardType));
    printf("Room: %d (GDP%d)\n", roomChoice, roomPrices[roomChoice - 1]);
    printf("Newspaper: %d\n", newspaper );
    printf("Booking ID: %s\n", bookingID);
    printf("\n************* Check-in Complete ***********\n");
}

void storeInfo() { //write all of the check in data to the global vars
    guestStayLengths[guestCount] = stayLength;
    guestRoomChoices[guestCount] = roomChoice;
    strcpy(guestBoardTypes[guestCount], boardType);
    strcpy(guestBookingIDs[guestCount], bookingID);
    guestNewspapers[guestCount] = newspaper;
    guestnumber[guestCount] = children + adults;
    guestCount++;

    printf("\nGuest stay info has been stored under booking ID: %s\n", bookingID);
}

void findAndPrintByID() {
    char searchID[80];
    printf("\nEnter Booking ID to search: ");
    scanf("%s", searchID);

    for (int i = 0; i < guestCount; i++) {
        if (strcmp(guestBookingIDs[i], searchID) == 0) {

            printf("\n=== Guest Found ===\n");
            printf("Booking ID: %s\n", guestBookingIDs[i]);
            printf("Room: %d\n", guestRoomChoices[i]);
            printf("Stay Length: %d nights\n", guestStayLengths[i]);
            printf("number of guests: %d \n", guestnumber[i]);
            printf("Board Type: %s\n", guestBoardTypes[i]);
            printf("Newspaper: %d\n", guestNewspapers[i]);
            printf("====================\n");
            return;
        }
    }

    printf("\nNo guest found with Booking ID: %s\n", searchID);
}



//table system to determine availability
int endor7 = 0;
int naboo7 = 0;
int tatooine7 = 0;
int endor9 = 0;
int naboo9 = 0;
int tatooine9 = 0;

char bookTable(int numOfGuests); //function - user to enter choice of table
void processTableChoice(int numOfGuests); //procedure - determine if user's table can be booked

void dinnerSystem() {
    while (1) {
        printf("************* Dinner table booking ***********\n");

        int flag = 0;
        char bookingID[30];

        printf("\n Please enter your Booking ID: ");
        scanf("%s", bookingID);

        for (int i = 0; i < guestCount; i++) {
            if (strcmp(bookingID, guestBookingIDs[i]) == 0) {
                flag = 1;

                if (strcmp(guestBoardTypes[i], "FB") == 0 || strcmp(guestBoardTypes[i], "HB") == 0) {
                    processTableChoice(guestnumber[i]);
                }
                else {
                    printf("Sorry, you can only book a table if your board is FB or HB\n");
                }
            }
        }
        if (flag == 0) {
            printf("ERROR: Unable to book table as guest does not exist\n");
        }

        return;
    }
}

void processTableChoice(int numOfGuests) {
    char tableChoice;
    tableChoice = bookTable(numOfGuests);

    switch (tableChoice) {
        case 'A': endor7 = 1; printf("Your table has successfully been booked - Endor at 7PM\n"); break;
        case 'B': naboo7 = 1; printf("Your table has successfully been booked - Naboo at 7PM\n"); break;
        case 'C': tatooine7 = 1; printf("Your table has successfully been booked - Tatooine at 7PM\n"); break;
        case 'D': endor9 = 1; printf("Your table has successfully been booked - Endor at 9PM\n"); break;
        case 'E': naboo9 = 1; printf("Your table has successfully been booked - Naboo at 9PM\n"); break;
        case 'F': tatooine9 = 1; printf("Your table has successfully been booked - Tatooine at 9PM\n"); break;

        case 'X':
            printf("Sorry, this table is unavailable.\n");
            char option;
            printf("Would you like to choose a different table? (Y/N) : ");
            fflush(stdin);
            scanf(" %c", &option);
            if (toupper(option) == 'Y') { processTableChoice(numOfGuests); }
            break;

        case 0:
            printf("Sorry, there are no available tables today.\n");
    }
}

char bookTable(int numOfGuests) {
    if (numOfGuests <=4) {

        if (endor7 && naboo7 && tatooine7 && endor9 && naboo9 && tatooine9) return 0;

        char choice;
        do {
            printf("The available tables today are listed as below: \n");
            if (!endor7) printf("A) Endor at 7pm\n");
            if (!naboo7) printf("B) Naboo at 7pm\n");
            if (!tatooine7) printf("C) Tatooine at 7pm\n");
            if (!endor9) printf("D) Endor at 9pm\n");
            if (!naboo9) printf("E) Naboo at 9pm\n");
            if (!tatooine9) printf("F) Tatooine at 9pm\n");

            printf("Enter your choice of table (Enter letter): ");
            fflush(stdin);
            scanf("%c", &choice);
            char confirm;
            printf("Is this correct? (Y/N): ");
            fflush(stdin);
            scanf("%c", &confirm);
            if (toupper(confirm) == 'N') {
                choice = 'X'; //dummy value given so the do-while loop repeats
            }
            choice = toupper(choice);
            if (choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D' && choice != 'E' && choice != 'F' && choice != 'X') {
                printf("Please enter a VALID option from the given list.\n");
            }

        } while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='E'&&choice!='F');
        //dummy values given to choice if user tries to book an occupied table
        if (choice=='A' && endor7) return 'X';
        if (choice=='B' && naboo7) return 'X';
        if (choice=='C' && tatooine7) return 'X';
        if (choice=='D' && endor9) return 'X';
        if (choice=='E' && naboo9) return 'X';
        if (choice=='F' && tatooine9) return 'X';

        return choice;
    }
    else {
        printf("Sorry, there is not a free table for your party\n");
        return 'X';
    }
}


int main() {

    while (true) {
        char choice;

        printf("Do you want to Check In (C), Check Out (O), Dinner (D), Check info(I), or Quit (Q)? ");
        scanf(" %c", &choice);
        choice = toupper(choice);

        if (choice == 'C') {
            checkin();
            storeInfo();
        }
        else if (choice == 'O') {
            printf("Check Out function not added yet.\n");
        }
        else if (choice == 'D') {
            dinnerSystem();   // <-- This is where the dinner program is now called
        }
        else if (choice == 'I') {
            findAndPrintByID();
        }
        else if (choice == 'Q') {
            printf("Goodbye!\n");
            break;
        }
        else {
            printf("Invalid option.\n");
        }
    }

    return 0;
}

