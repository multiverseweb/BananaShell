#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <windows.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

int get_terminal_width() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width = 80; // default fallback

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    return width;
}

void print_line() {
    printf(RESET);
    int width = get_terminal_width();
    for (int i = 0; i < width; i++) {
        putchar('=');
    }
    putchar('\n');
}

void print_centered(const char *text) {
    printf(RESET);
    int width = get_terminal_width();
    int len = strlen(text);
    int padding = (width - len) / 2;

    for (int i = 0; i < padding; i++) putchar('=');
    printf("%s", text);
    for (int i = 0; i < width - padding - len; i++) putchar('=');
    putchar('\n');
}

int main(){
    printf(YELLOW "\n====================================================================================\n");
    printf("=====  ====================================================  ============  ==  =====\n");
    printf("=====  ====================================================  ============  ==  =====\n");
    printf("=====  ====================================================  ============  ==  =====\n");
    printf("=====  ======   ===  = ====   ===  = ====   =========   ===  ======   ===  ==  =====\n");
    printf("=====    ===  =  ==     ==  =  ==     ==  =  =======  =  ==    ===  =  ==  ==  =====\n");
    printf("=====  =  =====  ==  =  =====  ==  =  =====  ========  ====  =  ==     ==  ==  =====\n");
    printf("=====  =  ===    ==  =  ===    ==  =  ===    =========  ===  =  ==  =====  ==  =====\n");
    printf("=====  =  ==  =  ==  =  ==  =  ==  =  ==  =  =======  =  ==  =  ==  =  ==  ==  =====\n");
    printf("=====    ====    ==  =  ===    ==  =  ===    ========   ===  =  ===   ===  ==  =====\n");
    printf("====================================================================================\n");
    printf(YELLOW "====================================================================================\n\n");
    printf(RESET "Normal");
    printf(RED "\tError");
    printf(GREEN "\tSuccess");
    printf(YELLOW "\tWarning");
    printf(CYAN "\tInfo\n");
    sleep(2);


    char command[100];
    print_centered("Banana Shell");

    
    //=======================================displaying top introduction
    printf(CYAN "\n\nThe Banana Shell is a command-line interpreter that provides a user interface to interact with the operating system. It is a program that takes commands from the user and executes them. The shell also provides a variety of features to help users interact with the operating system, such as file and directory management, data manipulation, etc. .\nThe commands that can be executed are listed below:\n\n- ls\n- pwd\n- mkdir dir_name\n- touch file_name\n- echo 'text_to_write' > file_name\n- cat file_name\n- wc file_name\n- mv old_file_name new_file_name\n- cp source_file_name destination_file_name\n- rm file_name\n- rmdir dir_name\n- date\n- whoami\n- exit\n\n");
    printf(RESET);
    print_line();

    while (1){
        printf(YELLOW "\nB");
        printf(RESET "_ " RESET);
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character

        if (strcmp(command, "exit") == 0){
            printf(MAGENTA "\nTejas' Codes :)");
            sleep(2);
            printf(".");
            sleep(1);
            printf(".");
            sleep(1);
            printf(".");
            sleep(3);
            break;
        }
        else if (strncmp(command, "mkdir", 5) == 0){
            char dirname[50];
            sscanf(command, "mkdir %[^\n]", dirname);
            if (mkdir(dirname) == 0){
                printf(GREEN "Directory created successfully.\n" RESET);
            }
            else{
                printf(RED "Failed to create directory.\n" RESET);
            }
        }
        else if (strncmp(command, "touch", 5) == 0){
            char filename[50];
            sscanf(command, "touch %[^\n]", filename);
            FILE *file = fopen(filename, "w");
            if (file != NULL){
                fclose(file);
                printf(GREEN "File created successfully.\n" RESET);
            }
            else{
                printf(RED "Failed to create file.\n" RESET);
            }
        }
        else if (strncmp(command, "cat", 3) == 0){
            char filename[50];
            sscanf(command, "cat %[^\n]", filename);
            FILE *file = fopen(filename, "r");
            if (file != NULL){
                char ch;
                while ((ch = fgetc(file)) != EOF)
                {
                    printf("%c", ch);
                }
                fclose(file);
            }
            else{
                printf(RED "Failed to open file.\n" RESET);
            }
        }
        else if (strncmp(command, "echo", 4) == 0){
            char text[100];
            char filename[50];
            sscanf(command, "echo '%[^']' > %[^\n]", text, filename);
            FILE *file = fopen(filename, "a");
            if (file != NULL){
                fprintf(file, "%s\n", text);
                fclose(file);
                printf(GREEN "Text written to file.\n" RESET);
            }
            else{
                printf(RED "Failed to open file.\n" RESET);
            }
        }
        else if (strncmp(command, "ls", 2) == 0){
            system("ls");
        }
        else if (strncmp(command, "pwd", 3) == 0){
            system("pwd");
        }
        else if (strncmp(command, "mv", 2) == 0){
            FILE *oldfile, *newfile;
            char oldname[100];
            char newname[100];
            sscanf(command, "mv %[^ ] %[^ ]", oldname, newname);
            char ch;

            // Open the old file for reading
            oldfile = fopen(oldname, "r");
            if (oldfile == NULL){
                perror(RED "Error opening old file");
            }

            newfile = fopen(newname, "w");
            if (newfile == NULL){
                perror(RED "Error opening new file");
                fclose(oldfile);
            }

            while ((ch = fgetc(oldfile)) != EOF){
                fputc(ch, newfile);
            }

            fclose(oldfile);
            fclose(newfile);

            // Delete the old file
            if (remove(oldname) == 0){
                printf(GREEN "File renamed successfully.\n");
            }
            else{
                printf(RED "Error renaming file");
            }
        }
        else if (strncmp(command, "cp", 2) == 0){
            char source[100];
            char destination[100];
            sscanf(command, "cp %[^ ] %[^ ]", source, destination);
            FILE *source_file = fopen(source, "r");
            if (source_file == NULL){
                printf(RED "Error opening source file.\n");
            }
            FILE *destination_file = fopen(destination, "w");
            if (destination_file == NULL){
                printf(RED "Error opening destination file.\n");
                fclose(source_file);
            }
            char ch;
            while ((ch = fgetc(source_file)) != EOF){
                fputc(ch, destination_file);
            }
            fclose(source_file);
            fclose(destination_file);
            printf(GREEN "File copied successfully.\n");
        }
        else if (strncmp(command, "rmdir", 5) == 0){
            char dirname[100];
            sscanf(command, "rmdir %[^\n]", dirname);
            if (rmdir(dirname) == 0){
                printf(GREEN "Directory deleted successfully.\n");
            }
            else{
                printf(RED "Error deleting directory.\n");
            }
        }
        else if (strncmp(command, "rm", 2) == 0){
            char filename[100];
            sscanf(command, "rm %[^\n]", filename);
            if (remove(filename) == 0){
                printf(GREEN "File deleted successfully.\n");
            }
            else{
                printf(RED "Error deleting file.\n");
            }
        }
        else if (strncmp(command, "date", 4) == 0){
            system("date");
        }
        else if (strncmp(command, "whoami", 6) == 0){
            system("whoami");
        }
        else if (strncmp(command, "wc", 2) == 0){
            char filename[50];
            sscanf(command, "touch %[^\n]", filename);
            int wordCount = 0;
            char ch;
            FILE *file;
            // Open file
            file = fopen(filename, "r");

            // Check if file exists
            if (file == NULL) {
                printf(RED "File not found.\n");
            }
            else{

                // Read file character by character
                while ((ch = fgetc(file)) != EOF) {
                    // If current character is space, tab, or newline, increment word count
                    if (ch == ' ' || ch == '\t' || ch == '\n') {
                        wordCount++;
                    }
                }

                // Close file
                fclose(file);

                // Increment word count by 1 to account for the last word
                wordCount++;

                printf(GREEN "Word Count: %d\n", wordCount-1);
            }
        }
        else{
            printf(YELLOW "Command not supported.\n" RESET);
        }
    }
    return 0;
}
