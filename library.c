
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char title[100];
    char author[100];
    int year;
} Book;

void addBook();
void listBooks();
void searchBook();
void deleteBook();
int menu();

int main() {
    int choice;
    do {
        choice = menu();
        switch(choice) {
            case 1: addBook(); break;
            case 2: listBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: printf("Çıkılıyor...\n"); break;
            default: printf("Geçersiz seçim!\n");
        }
    } while(choice != 5);
    return 0;
}

int menu() {
    int choice;
    printf("\n--- KÜTÜPHANE YÖNETİM SİSTEMİ ---\n");
    printf("1. Kitap Ekle\n");
    printf("2. Kitapları Listele\n");
    printf("3. Kitap Ara\n");
    printf("4. Kitap Sil\n");
    printf("5. Çıkış\n");
    printf("Seçiminiz: ");
    scanf("%d", &choice);
    return choice;
}

void addBook() {
    FILE *fp = fopen("books.txt", "a");
    if (fp == NULL) {
        printf("Dosya açılamadı!\n");
        return;
    }
    Book b;
    printf("Kitap ID: ");
    scanf("%d", &b.id);
    getchar(); // \n karakterini yut
    printf("Kitap Adı: ");
    fgets(b.title, 100, stdin); strtok(b.title, "\n");
    printf("Yazar: ");
    fgets(b.author, 100, stdin); strtok(b.author, "\n");
    printf("Yıl: ");
    scanf("%d", &b.year);

    fprintf(fp, "%d,%s,%s,%d\n", b.id, b.title, b.author, b.year);
    fclose(fp);
    printf("Kitap başarıyla eklendi.\n");
}

void listBooks() {
    FILE *fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("Dosya açılamadı veya hiç kitap eklenmemiş.\n");
        return;
    }
    Book b;
    printf("\n--- Kitap Listesi ---\n");
    while (fscanf(fp, "%d,%99[^,],%99[^,],%d\n", &b.id, b.title, b.author, &b.year) != EOF) {
        printf("ID: %d | Ad: %s | Yazar: %s | Yıl: %d\n", b.id, b.title, b.author, b.year);
    }
    fclose(fp);
}

void searchBook() {
    FILE *fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("Dosya açılamadı!\n");
        return;
    }
    char keyword[100];
    printf("Aranacak kitap adı: ");
    getchar();
    fgets(keyword, 100, stdin);
    strtok(keyword, "\n");

    Book b;
    int found = 0;
    while (fscanf(fp, "%d,%99[^,],%99[^,],%d\n", &b.id, b.title, b.author, &b.year) != EOF) {
        if (strstr(b.title, keyword)) {
            printf("Bulundu! ID: %d | Ad: %s | Yazar: %s | Yıl: %d\n", b.id, b.title, b.author, b.year);
            found = 1;
        }
    }
    if (!found) printf("Kitap bulunamadı.\n");
    fclose(fp);
}

void deleteBook() {
    FILE *fp = fopen("books.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Dosyalar açılamadı!\n");
        return;
    }

    int delId, found = 0;
    printf("Silinecek Kitap ID: ");
    scanf("%d", &delId);

    Book b;
    while (fscanf(fp, "%d,%99[^,],%99[^,],%d\n", &b.id, b.title, b.author, &b.year) != EOF) {
        if (b.id != delId) {
            fprintf(temp, "%d,%s,%s,%d\n", b.id, b.title, b.author, b.year);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found) {
        printf("Kitap silindi.\n");
    } else {
        printf("Kitap bulunamadı.\n");
    }
}
