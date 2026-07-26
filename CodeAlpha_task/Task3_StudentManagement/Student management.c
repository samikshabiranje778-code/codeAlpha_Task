//Task:Student Management System

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
}

void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct Student s;

    printf("Enter ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student Added Successfully.\n");
}

void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    if (fp == NULL) {
        printf("No Records Found.\n");
        return;
    }

    printf("\nID\tName\t\tMarks\n");
    printf("---------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%d\t%s\t\t%.2f\n", s.id, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;
    int id, found = 0;

    printf("Enter ID to Search: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("\nStudent Found\n");
            printf("ID: %d\n", s.id);
            printf("Name: %s\n", s.name);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Record Not Found.\n");

    fclose(fp);
}

void updateStudent() {
    FILE *fp = fopen("students.dat", "rb+");
    struct Student s;
    int id, found = 0;

    printf("Enter ID to Update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp,-sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            printf("Record Updated.\n");
            break;
        }
    }

    if (!found)
        printf("Record Not Found.\n");

    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    struct Student s;
    int id, found = 0;

    printf("Enter ID to Delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id != id)
            fwrite(&s, sizeof(s), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Record Deleted.\n");
    else
        printf("Record Not Found.\n");
}
