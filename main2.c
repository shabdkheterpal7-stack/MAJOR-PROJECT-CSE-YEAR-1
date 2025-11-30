#include <stdio.h>
#include <string.h>
struct Student {
    char name[50];
    char sap_id[20];
    char phone[20];
    char email[50];
    int subjects;
    int marks[7];
    int total;
    float average;
};
struct Student students[100];
int count = 0;
void banner() {
    printf("\nSTUDENT MARKS SYSTEM\n");
    printf("Made by: Shabd Kheterpal, UPES SoCS, B.Tech CSE Year 1\n\n");
}
void showMenu() {
    printf("\n---- STUDENT MARKS SYSTEM MENU ----\n");
    printf("1. Enter New Student\n");
    printf("2. Search Student by SAP ID\n");
    printf("3. Save All Students to File\n");
    printf("4. Exit\n");
}
int getChoice() {
    int x;
    printf("Enter choice: ");
    scanf("%d", &x);
    return x;
}
void calculate(int index) {
    students[index].total = 0;
    for(int i = 0; i < students[index].subjects; i++) {
        students[index].total += students[index].marks[i];
    }
    students[index].average = (float)students[index].total / students[index].subjects;
}
void displayStudent(int index) {
    printf("\n----- STUDENT REPORT -----\n");
    printf("Name: %s\n", students[index].name);
    printf("SAP ID: %s\n", students[index].sap_id);
    printf("Phone: %s\n", students[index].phone);
    printf("Email: %s\n\n", students[index].email);
    for(int i = 0; i < students[index].subjects; i++) {
        printf("Subject %d: %d\n", i + 1, students[index].marks[i]);
    }
    printf("Total Marks: %d\n", students[index].total);
    printf("Average Marks: %.2f\n", students[index].average);
    if(students[index].average >= 90) printf("Grade: A+\n");
    else if(students[index].average >= 80) printf("Grade: A\n");
    else if(students[index].average >= 70) printf("Grade: B\n");
    else if(students[index].average >= 60) printf("Grade: C\n");
    else if(students[index].average >= 50) printf("Grade: D\n");
    else printf("Grade: F\n");
}
void inputStudent() {
    if(count >= 100) {
        printf("Maximum student limit reached.\n");
        return;
    }
    getchar();
    printf("Enter Student Name: ");
    fgets(students[count].name, sizeof(students[count].name), stdin);
    students[count].name[strcspn(students[count].name, "\n")] = '\0';
    printf("Enter SAP ID: ");
    fgets(students[count].sap_id, sizeof(students[count].sap_id), stdin);
    students[count].sap_id[strcspn(students[count].sap_id, "\n")] = '\0';
    printf("Enter Phone Number: ");
    fgets(students[count].phone, sizeof(students[count].phone), stdin);
    students[count].phone[strcspn(students[count].phone, "\n")] = '\0';
    printf("Enter Email: ");
    fgets(students[count].email, sizeof(students[count].email), stdin);
    students[count].email[strcspn(students[count].email, "\n")] = '\0';
    printf("Enter number of subjects (max 7): ");
    scanf("%d", &students[count].subjects);
    if(students[count].subjects < 1 || students[count].subjects > 7)
        students[count].subjects = 7;

    for(int i = 0; i < students[count].subjects; i++) {
        printf("Enter marks of subject %d: ", i + 1);
        scanf("%d", &students[count].marks[i]);
        if(students[count].marks[i] < 0 || students[count].marks[i] > 100)
            students[count].marks[i] = 0;
    }
    calculate(count);
    count++;
    printf("Student added successfully.\n");
}
void searchStudent() {
    char id[20];
    getchar();
    printf("Enter SAP ID to search: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    for(int i = 0; i < count; i++) {
        if(strcmp(id, students[i].sap_id) == 0) {
            displayStudent(i);
            return;
        }
    }
    printf("Student not found.\n");
}
void saveToFile() {
    FILE *fp = fopen("students.txt", "w");
    if(fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for(int i = 0; i < count; i++) {
        fprintf(fp, "Name: %s\n", students[i].name);
        fprintf(fp, "SAP ID: %s\n", students[i].sap_id);
        fprintf(fp, "Phone: %s\n", students[i].phone);
        fprintf(fp, "Email: %s\n", students[i].email);
        fprintf(fp, "Subjects: %d\n", students[i].subjects);
        for(int j = 0; j < students[i].subjects; j++) {
            fprintf(fp, "Subject %d: %d\n", j + 1, students[i].marks[j]);
        }
        fprintf(fp, "Total: %d\n", students[i].total);
        fprintf(fp, "Average: %.2f\n", students[i].average);
        fprintf(fp, "------------------------------\n");
    }
    fclose(fp);
    printf("All data saved to students.txt successfully.\n");
}
int main() {
    int choice;
    banner();
    while(1) {
        showMenu();
        choice = getChoice();
        if(choice == 1) {
            inputStudent();
        }
        else if(choice == 2) {
            searchStudent();
        }
        else if(choice == 3) {
            saveToFile();
        }
        else if(choice == 4) {
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
