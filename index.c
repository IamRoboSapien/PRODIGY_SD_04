#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[20];
    char email[50];
};

struct Contact contacts[MAX];
int count = 0;

// Function to load contacts from file
void loadContacts() {
    FILE *fp = fopen("contacts.txt", "r");
    if (fp == NULL) return;

    while (fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",
                  contacts[count].name,
                  contacts[count].phone,
                  contacts[count].email) == 3) {
        count++;
    }
    fclose(fp);
}

// Function to save contacts to file
void saveContacts() {
    FILE *fp = fopen("contacts.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    fclose(fp);
}

// Add contact
void addContact() {
    if (count >= MAX) {
        printf("Contact list full!\n");
        return;
    }
    printf("Enter Name: ");
    scanf(" %[^\n]", contacts[count].name);
    printf("Enter Phone: ");
    scanf(" %[^\n]", contacts[count].phone);
    printf("Enter Email: ");
    scanf(" %[^\n]", contacts[count].email);
    count++;
    saveContacts();
    printf("Contact added successfully!\n");
}

void viewContacts() {
    if (count == 0) {
        printf("No contacts found.\n");
        return;
    }
    printf("\n--- Contact List ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s | %s | %s\n", i + 1,
               contacts[i].name,
               contacts[i].phone,
               contacts[i].email);
    }
}

void editContact() {
    int index;
    viewContacts();
    printf("Enter contact number to edit: ");
    scanf("%d", &index);
    if (index < 1 || index > count) {
        printf("Invalid contact number.\n");
        return;
    }
    index--; 
    printf("Editing %s...\n", contacts[index].name);
    printf("Enter new Name: ");
    scanf(" %[^\n]", contacts[index].name);
    printf("Enter new Phone: ");
    scanf(" %[^\n]", contacts[index].phone);
    printf("Enter new Email: ");
    scanf(" %[^\n]", contacts[index].email);
    saveContacts();
    printf("Contact updated successfully!\n");
}

void deleteContact() {
    int index;
    viewContacts();
    printf("Enter contact number to delete: ");
    scanf("%d", &index);
    if (index < 1 || index > count) {
        printf("Invalid contact number.\n");
        return;
    }
    index--;
    for (int i = index; i < count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    count--;
    saveContacts();
    printf("Contact deleted successfully!\n");
}

int main() {
    int choice;
    loadContacts();

    do {
        printf("\n--- Contact Management System ---\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: editContact(); break;
            case 4: deleteContact(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
