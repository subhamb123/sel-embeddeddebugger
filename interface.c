#include <stdio.h>
#include <stdlib.h>

int main (int argv, char* argc[]){

    int input = 0;
    int running = 1;

    while(running){
        clearScreen();
        printMainMenu();
        input = getInput();

        if(input==1)
            viewSnapshotLog();

        else if(input==2)
            takeSnapshotMessage();
            
        else if(input==3)
            createException();
        
        else if(input==0)
            running = 0;

        else{
            printf("\n Error, invalid option. (press any key to continue...)");
            getchar();
        }

    }

    return 0;
}

// Just displays a message you might see in a true implementation
void printMainMenu(){
    printf("Debugger\nMainMenu\n\n");
    printf("1: View Snapshots\n");
    printf("2: Take snapshot\n");
    printf("3: Create exception\n");
    printf("0: Exit\n");
    return;
}

// Gets the input from a user
int getInput(){

    int input = 0;
    printf("Option: ");
    scanf("%d", &input);
    return input;
}

// Just displays a message you might see in a true implementation
void viewSnapshotLog(){
    clearScreen();
    printf("snapshot\t\tdate\t\terror code\t\t\n\n");
    int errorcode = 0;
    int minute = 10;

    for(int i = 0; i < 25; i++){
        if(i<10){
            printf("snapshot-0%d\t\t10-05-2023 14:%d\t\t%d\n", i, minute, errorcode);
        }
        else
            printf("snapshot-%d\t\t10-05-2023 14:%d\t\t%d\n", i, minute, errorcode);

        minute += rand() % 2 + 1; 
        errorcode += rand() % 4 + 2; 

    }

    printf("\n(press any key to continue...)");
    getchar();
    getchar();


}

// Just displays a message you might see in a true implementation
void takeSnapshotMessage(){
    clearScreen();
    printf("Snapshot saved!\nSnapshot-26\t\t10-05-2023\t\t15:30");
    printf("\n(press any key to continue...)");
    getchar();
    getchar();

}

// Just displays a message you might see in a true implementation
void createException(){
    printf("Are you sure you want to cause an exception? This will cause an operation interruption! (y/n) y\n\n");
    printf("Creating exception...\n\n");
    printf("\n(press any key to continue...)");
    getchar();
    getchar();

}

// Just adds a ton of blank lines to "clear" the screen.
// If it's good enough for vscode it's good enough for me.
void clearScreen(){
    for(int i = 0; i < 500; i++){
        printf("\n");
    }
}