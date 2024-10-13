#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATIENTS 100
#define MAX_APPOINTMENTS 50
typedef struct
{
    int id;
    char name[50];
    int age;
    char disease[50];
} Patient;
typedef struct
{
    int front, rear, size;
    Patient appointments[MAX_APPOINTMENTS];
} Queue;
void initQueue(Queue* q)
{
    q->front = q->rear = q->size = 0;
}
int isEmpty(Queue* q)
{
    return q->size == 0;
}
int isFull(Queue* q)
{
    return q->size == MAX_APPOINTMENTS;
}
void enqueue(Queue* q, Patient p)
{
    if (isFull(q))
    {
        printf("Queue is full. Cannot add more appointments.\n");
        return;
    }
    q->appointments[q->rear] = p;
    q->rear = (q->rear + 1) % MAX_APPOINTMENTS;
    q->size++;
}
Patient dequeue(Queue* q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty. No appointments to remove.\n");
        exit(1);
    }
    Patient p = q->appointments[q->front];
    q->front = (q->front + 1) % MAX_APPOINTMENTS;
    q->size--;
    return p;
}
void displayPatients(Patient patients[], int numPatients)
{
    printf("Patient Records:\n");
    for (int i = 0; i < numPatients; i++)
    {
        printf("ID: %d, Name: %s, Age: %d, Disease: %s\n",
               patients[i].id, patients[i].name, patients[i].age, patients[i].disease);
    }
}
void addPatient(Patient patients[], int* numPatients, Queue* q)
{
    if (*numPatients == MAX_PATIENTS)
    {
        printf("Maximum number of patients reached. Cannot add more patients.\n");
        return;
    }
    Patient p;
    printf("Enter patient ID: ");
    scanf("%d", &p.id);
    printf("Enter patient name: ");
    scanf("%s", p.name);
    printf("Enter patient age: ");
    scanf("%d", &p.age);
    printf("Enter patient disease: ");
    scanf("%s", p.disease);
    patients[(*numPatients)++] = p;
    enqueue(q, p);
    printf("Patient added successfully.\n");
}
void removePatient(Patient patients[], int* numPatients, Queue* q)
{
    if (*numPatients == 0)
    {
        printf("No patients to remove.\n");
        return;
    }
    int id;
    printf("Enter patient ID to remove: ");
    scanf("%d", &id);
    for (int i = 0; i < *numPatients; i++)
    {
        if (patients[i].id == id)
        {
            for (int j = i; j < *numPatients - 1; j++) {
                patients[j] = patients[j + 1];
            }
            (*numPatients)--;
            printf("Patient removed successfully.\n");
            return;
        }
    }
    printf("Patient not found.\n");
}
void updatePatient(Patient patients[], int numPatients)
{
    if (numPatients == 0)
    {
        printf("No patients to update.\n");
        return;
    }
    int id;
    printf("Enter patient ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < numPatients; i++)
    {
        if (patients[i].id == id)
        {
            printf("Enter new patient name: ");
            scanf("%s", patients[i].name);
            printf("Enter new patient age: ");
            scanf("%d", &patients[i].age);
            printf("Enter new patient disease: ");
            scanf("%s", patients[i].disease);
            printf("Patient updated successfully.\n");
            return;
        }
    }
    printf("Patient not found.\n");
}
int main()
{
    Patient patients[MAX_PATIENTS];
    int numPatients = 0;
    Queue q;
    initQueue(&q);
    while (1)
    {
        printf("Maiyol Hospital Management System\n");
        printf("1. Add Patient\n");
        printf("2. Remove Patient\n");
        printf("3. Update Patient\n");
        printf("4. Display Patients\n");
        printf("5. Exit\n");
        int ch;
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
                addPatient(patients, &numPatients, &q);
                break;
            case 2:
                removePatient(patients, &numPatients, &q);
                break;
            case 3:
                updatePatient(patients, numPatients);
                break;
            case 4:
                displayPatients(patients, numPatients);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
