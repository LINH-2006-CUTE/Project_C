#include <stdio.h>
#include <string.h>

// ***** QUAN LY SINH VIEN
struct Student{
    int id;
    char name[50];
    int age;
    char phoneNumber[50]; 
    char emailAddress[50];
};

struct Student sv[100];
int sinhVien = 0;

// hien thi menu chuc nang chinh SINH VIEN
void showMenuAll(){
    printf("*** Students Management System Using C ***\n");
    printf("\n\tCHOOSE YOUR ROLE\n");
    printf("[1] Admin\n");
    printf("[0] Exit your program\n");
    printf("==================================\n");
    printf("Enter your choice: \n");
}

// hien thi lua chon (trong Admin)
void showMenuAdmin(){
    printf("\nMENU ADMIN\n");
    printf("[1] Student\n");
    printf("[2] Teacher\n");
    printf("[3] Class\n");
    printf("[4] Exit\n");
    printf("\n YOUR CHOOSE:");
}

// hien thi menu chuc nang quan ly sinh vien
void showMenuStudent(){
    printf("***** QUAN LY SINH VIEN *****\n");
    printf("==========================\n");
    printf("[1] Hien thi danh sach sinh vien\n");
    printf("[2] Them sinh vien\n");
    printf("[3] Sua thong tin sinh vien\n");
    printf("[4] Xoa sinh vien\n");
    printf("[5] Sap xep danh sach sinh vien\n");
    printf("[6] Tim kiem sinh vien \n");
    printf("[7] Thoat\n");
    printf("==========================\n");
    printf("Nhap lua chon cua ban: ");
}

// hien thi danh sach sinh vien
void showSv(){
    FILE *ptr = fopen("Student.bin", "rb");
    if (ptr == NULL){
        printf("------------------------------------------ \n");
        printf("Khong the mo file de doc du lieu!\n");
        return;
    }
    sinhVien = fread(sv, sizeof(struct Student), 100, ptr);
    fclose(ptr);
    if (sinhVien == 0){
    	printf("\n"); 
        printf("Danh sach sinh vien trong\n");
        return;
    }

    printf("\nDANH SACH SINH VIEN\n");
    printf("==========================\n");
    printf("ID\tTen\tTuoi\tSo Dien Thoai\tEmail\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < sinhVien; i++) {
        printf("%02d\t%s\t%d\t%s\t%s\n", sv[i].id, sv[i].name, sv[i].age, sv[i].phoneNumber, sv[i].emailAddress);
    }
}

// kiem tra du lieu sinh vien
int checkStudentData(struct Student newSv){
    if (strlen(newSv.name) == 0 || strlen(newSv.emailAddress) == 0 || newSv.phoneNumber == 0){
        printf("Ban can dien thong tin sinh vien\n");
        return 0;
    }
    for (int i = 0; i < sinhVien; i++){
        if (sv[i].id == newSv.id){
            printf("\nID sinh vien da ton tai\n");
            return 0;
        }
        if (strcmp(sv[i].emailAddress, newSv.emailAddress) == 0){
            printf("\nEmail sinh vien da ton tai\n");
            return 0;
        }
        if (strcmp(sv[i].phoneNumber, newSv.phoneNumber) == 0){
            printf("\nSo dien thoai sinh vien da ton tai\n");
            return 0;
        }
    }
    return 1;
}

// them sinh vien
void addSv(){
    if (sinhVien >= 100){
        printf("\nDanh sach da day\n");
        return;
    }
    struct Student newSv;
    do {
        printf("Nhap ID sinh vien: ");
        scanf("%d", &newSv.id);
        printf("Nhap ten sinh vien: ");
        scanf(" %s", newSv.name);
        printf("Nhap tuoi sinh vien: ");
        scanf("%d", &newSv.age);
        printf("Nhap so dien thoai sinh vien: ");
        scanf("%s", newSv.phoneNumber); //& k dc doc dung cach 
        printf("Nhap email sinh vien: ");
        scanf("%s", newSv.emailAddress);
    } while (!checkStudentData(newSv));
    sv[sinhVien++] = newSv;
    FILE *ptr = fopen("Student.bin", "wb");
    if (ptr == NULL){
    	printf("\n"); 
        printf("\nKhong the mo file de ghi\n");
        return;
    }
    fwrite(sv, sizeof(struct Student), sinhVien, ptr);
    fclose(ptr);
    printf("\nDanh sach sinh vien da duoc them!\n");
}

// sua thong tin sinh vien
void editSv(){
    int id;
    printf("Nhap ID sinh vien muon sua: ");
    scanf("%d", &id);
    for (int i = 0; i < sinhVien; i++){
        if (sv[i].id == id){
            printf("Nhap thong tin moi:\n");
            printf("Nhap ten moi: ");
            scanf(" %s", sv[i].name);
            printf("Nhap tuoi moi: ");
            scanf("%d", &sv[i].age);
            printf("Nhap so dien thoai moi: ");
            scanf("%s", sv[i].phoneNumber);
            printf("Nhap email moi: ");
            scanf("%s", sv[i].emailAddress);
            printf("Sua thong tin sinh vien thanh cong\n");
            break;
        }
    }
}

// xoa sinh vien
void deleteSv(){
    int id;
    char confirm;
    printf("Nhap ID sinh vien muon xoa: ");
    scanf("%d", &id);

    for (int i = 0; i < sinhVien; i++){
        if (sv[i].id == id) {
            printf("\nThong tin sinh vien:\n");
            printf("ID: %d\n", sv[i].id);
            printf("Ten: %s\n", sv[i].name);
            printf("Tuoi: %d\n", sv[i].age);
            printf("So Dien Thoai: %s\n", sv[i].phoneNumber);
            printf("Email: %s\n", sv[i].emailAddress);

            printf("\nBan co muon xoa sinh vien nay?(Y/N): ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y'){
                for (int j = i; j < sinhVien - 1; j++){
                    sv[j] = sv[j + 1];
                }
                sinhVien--;
                
                FILE *ptr = fopen("Student.bin", "wb");  // xoa xong luu lai dsach 
                if (ptr == NULL) {
                    printf("Khong the mo file de ghi\n");
                    return;
                }
                fwrite(sv, sizeof(struct Student), sinhVien, ptr);
                fclose(ptr);
                printf("\nXoa sinh vien thanh cong\n");
            } else {
                printf("\nHUY\n");
            }
            return;
        }
    }
    printf("ID sinh vien khong ton tai\n");
}

// sap xep sinh vien theo ID
void sortSvID(){
    for (int i = 0; i < sinhVien - 1; i++){
        for (int j = i + 1; j < sinhVien; j++){
            if (sv[i].id > sv[j].id) {
                struct Student temp = sv[i];
                sv[i] = sv[j];
                sv[j] = temp;
            }
        }
    }
    FILE *ptr = fopen("Student.bin", "wb");
    if (ptr == NULL){
        printf("\nKhong the mo file de ghi\n");
        return;
    }
    fwrite(sv, sizeof(struct Student), sinhVien, ptr);
    fclose(ptr); 
    printf("\nDanh sach sinh vien da duoc sap xep theo ID\n");
}

// sap xep sinh vien theo ten
void sortSvName(){
    for (int i = 0; i < sinhVien - 1; i++){
        for (int j = i + 1; j < sinhVien; j++){
            if (strcmp(sv[i].name, sv[j].name) > 0){
                struct Student temp = sv[i];
                sv[i] = sv[j];
                sv[j] = temp;
            }
        }
    }
    
    FILE *ptr = fopen("Student.bin", "wb");
    if (ptr == NULL){
        printf("\nKhong the mo file de ghi\n");
        return;
    }
    fwrite(sv, sizeof(struct Student), sinhVien, ptr);
    fclose(ptr); 
    printf("\nDanh sach sinh vien da duoc sap xep theo ten\n");
}

// tim kiem sinh vien theo ten/id/ sdt/email
void searchSv(){
    char searchName[50];
    char searchID[50];
    char searchPhoneNumber[50];
    char searchEmail[50];
    int check = 0;
    int searchChoice;

    printf("Tim kiem theo:\n");
    printf("1. Ten\n");
    printf("2. ID\n");
    printf("3. So dien thoai\n");
    printf("4. Email\n");
    printf("Nhap lua chon: ");
    scanf("%d", &searchChoice);
    printf("\nKet qua tim kiem:\n");
    printf("ID\tTen\tTuoi\tSo Dien Thoai\tEmail\n");
    printf("---------------------------------------------------------\n");

    switch (searchChoice) {
        case 1:
            printf("Nhap ten sinh vien muon tim: ");
            scanf(" %s", searchName);
            for (int i = 0; i < sinhVien; i++){
                if (strstr(sv[i].name, searchName) != NULL){
                    printf("%d\t%s\t%d\t%s\t%s\n", sv[i].id, sv[i].name, sv[i].age, sv[i].phoneNumber, sv[i].emailAddress);
                    check = 1;
                }
            }
            if (check != 1){
                printf("\nKhong tim thay sinh vien nao!\n");
            }
            break;
            
        case 2:
            printf("Nhap ID sinh vien muon tim: ");
            scanf("%s", searchID);
            for (int i = 0; i < sinhVien; i++){
                char idStr[10];
                sprintf(idStr, "%d", sv[i].id);
                if (strcmp(idStr, searchID) == 0){
                    printf("%d\t%s\t%d\t%s\t%s\n", sv[i].id, sv[i].name, sv[i].age, sv[i].phoneNumber, sv[i].emailAddress);
                    check = 1;
                }
            }
            break;
            
        case 3:
            printf("Nhap so dien thoai sinh vien muon tim: ");
            scanf("%s", searchPhoneNumber);
            for (int i = 0; i < sinhVien; i++){
                if (strcmp(sv[i].phoneNumber, searchPhoneNumber) == 0){
                    printf("%d\t%s\t%d\t%s\t%s\n", sv[i].id, sv[i].name, sv[i].age, sv[i].phoneNumber, sv[i].emailAddress);
                    check = 1;
                }
            }
            break;
            
        case 4:
            printf("Nhap email sinh vien muon tim: ");
            scanf("%s", searchEmail);
            for (int i = 0; i < sinhVien; i++){
                if (strcmp(sv[i].emailAddress, searchEmail) == 0){
                    printf("%d\t%s\t%d\t%s\t%s\n", sv[i].id, sv[i].name, sv[i].age, sv[i].phoneNumber, sv[i].emailAddress);
                    check = 1;
                }
            }
            break;
            
        default:
            printf("Lua chon khong hop le!\n");
            break;
    }

    if (check == 0){
        printf("\nKhong tim thay ket qua tim kiem\n");
    }
}


// ********QUAN LY GIAO VIEN
struct Teacher {
    int id;
    char name[50];
    int age;
    char phoneNumber[50];
    char emailAddress[50];
};

struct Teacher teacher[100];
int teacherCount = 0;

void showMenuTeacher(){
    printf("***** QUAN LY GIAO VIEN *****\n");
    printf("==========================\n");
    printf("[1] Hien thi danh sach giao vien\n");
    printf("[2] Them giao vien\n");
    printf("[3] Sua thong tin giao vien\n");
    printf("[4] Xoa giao vien\n");
    printf("[5] Tim kiem giao vien\n");
    printf("[6] Thoat\n");
    printf("==========================\n");
    printf("Nhap lua chon cua ban: ");
}

// Hien thi danh sach giao vien
void showTeacher(){
    FILE *ptr = fopen("Teacher.bin", "rb");
    if (ptr == NULL){
        printf("Khong the mo file de doc du lieu!\n");
        return;
    }
    teacherCount = fread(teacher, sizeof(struct Teacher), 100, ptr);
    fclose(ptr);

    if (teacherCount == 0){
        printf("Danh sach giao vien trong\n");
        return;
    }

    printf("\nDANH SACH GIAO VIEN\n");
    printf("==========================\n");
    printf("ID\tTen\tTuoi\tSo Dien Thoai\tEmail\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < teacherCount; i++){
        printf("%d\t%s\t%d\t%s\t%s\n", teacher[i].id, teacher[i].name, teacher[i].age, teacher[i].phoneNumber, teacher[i].emailAddress);
    }
}

// Them giao vien
void addTeacher(){
    if (teacherCount >= 100){
        printf("Danh sach giao vien da day\n");
        return;
    }

    struct Teacher newTeacher;
    printf("Nhap ID giao vien: ");
    scanf("%d", &newTeacher.id);
    printf("Nhap ten giao vien: ");
    scanf(" %s", newTeacher.name);
    printf("Nhap tuoi giao vien: ");
    scanf("%d", &newTeacher.age);
    printf("Nhap so dien thoai giao vien: ");
    scanf("%s", newTeacher.phoneNumber);
    printf("Nhap email giao vien: ");
    scanf("%s", newTeacher.emailAddress);

    teacher[teacherCount++] = newTeacher;
    
    FILE *ptr = fopen("Teacher.bin", "wb");
    if (ptr == NULL){
        printf("Khong the mo file de ghi\n");
        return;
    }
    fwrite(teacher, sizeof(struct Teacher), teacherCount, ptr);
    fclose(ptr);

    printf("Giao vien da duoc them!\n");
}

// Sua thong tin giao vien
void editTeacher(){
    int id;
    int check = 0;
    printf("Nhap ID giao vien muon sua: ");
    scanf("%d", &id);

    for (int i = 0; i < teacherCount; i++){
        if (teacher[i].id == id) {
            printf("Nhap thong tin moi:\n");
            printf("Nhap ten moi: ");
            scanf(" %s", teacher[i].name);
            printf("Nhap tuoi moi: ");
            scanf("%d", &teacher[i].age);
            printf("Nhap so dien thoai moi: ");
            scanf("%s", teacher[i].phoneNumber);
            printf("Nhap email moi: ");
            scanf("%s", teacher[i].emailAddress);
            printf("Sua thong tin giao vien thanh cong\n");
            check = 1;
            break;
        }
    }

    if (check == 0){
        printf("ID giao vien khong ton tai\n");
    }
}

// Xoa giao vien
void deleteTeacher(){
    int id;
    char confirm;
    int check = 0;
    printf("Nhap ID giao vien muon xoa: ");
    scanf("%d", &id);

    for (int i = 0; i < teacherCount; i++){
        if (teacher[i].id == id){
            printf("\nThong tin giao vien:\n");
            printf("ID: %d\n", teacher[i].id);
            printf("Ten: %s\n", teacher[i].name);
            printf("Tuoi: %d\n", teacher[i].age);
            printf("So Dien Thoai: %s\n", teacher[i].phoneNumber);
            printf("Email: %s\n", teacher[i].emailAddress);

            printf("\nBan co muon xoa giao vien nay?(Y/N): ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y'){
                for (int j = i; j < teacherCount - 1; j++){
                    teacher[j] = teacher[j + 1];
                }
                teacherCount--;
                
                FILE *ptr = fopen("Teacher.bin", "wb");
                if (ptr == NULL){
                    printf("Khong the mo file de ghi\n");
                    return;
                }
                fwrite(teacher, sizeof(struct Teacher), teacherCount, ptr);
                fclose(ptr);

                printf("Xoa giao vien thanh cong\n");
            } else {
                printf("Huy xoa giao vien\n");
            }
            check = 1;
            break;
        }
    }

    if (check == 0) {
        printf("ID giao vien khong ton tai\n");
    }
}

// Tim giao vien
void searchTeacher(){
    char searchName[50];
    char searchID[50];
    char searchPhoneNumber[50];
    char searchEmail[50];
    int check = 0;
    int searchChoice;

    printf("Ban muon tim giao vien theo:\n");
    printf("1. Ten\n");
    printf("2. ID\n");
    printf("3. So dien thoai\n");
    printf("4. Email\n");
    printf("Nhap lua chon: ");
    scanf("%d", &searchChoice);

    printf("\nKet qua tim kiem:\n");
    printf("ID\tTen\tTuoi\tSo Dien Thoai\tEmail\n");
    printf("---------------------------------------------------------\n");

    switch (searchChoice){
        case 1: {
            printf("Nhap ten giao vien muon tim: ");
            scanf(" %s", searchName);
            for (int i = 0; i < teacherCount; i++){
                if (strstr(teacher[i].name, searchName) != NULL){
                    printf("%d\t%s\t%d\t%s\t%s\n", teacher[i].id, teacher[i].name, teacher[i].age, teacher[i].phoneNumber, teacher[i].emailAddress);
                    check = 1;
                }
            }
            break;
        }
        case 2: {
            printf("Nhap ID giao vien muon tim: ");
            scanf("%s", searchID);
            for (int i = 0; i < teacherCount; i++){
                char idStr[10];
                sprintf(idStr, "%d", teacher[i].id);
                if (strcmp(idStr, searchID) == 0){
                    printf("%d\t%s\t%d\t%s\t%s\n", teacher[i].id, teacher[i].name, teacher[i].age, teacher[i].phoneNumber, teacher[i].emailAddress);
                    check = 1;
                }
            }
            break;
        }
        case 3: {
            printf("Nhap so dien thoai giao vien muon tim: ");
            scanf("%s", searchPhoneNumber);
            for (int i = 0; i < teacherCount; i++){
                if (strcmp(teacher[i].phoneNumber, searchPhoneNumber) == 0){
                    printf("%d\t%s\t%d\t%s\t%s\n", teacher[i].id, teacher[i].name, teacher[i].age, teacher[i].phoneNumber, teacher[i].emailAddress);
                    check = 1;
                }
            }
            break;
        }
        case 4: {
            printf("Nhap email giao vien muon tim: ");
            scanf("%s", searchEmail);
            for (int i = 0; i < teacherCount; i++){
                if (strstr(teacher[i].emailAddress, searchEmail) != NULL){
                    printf("%d\t%s\t%d\t%s\t%s\n", teacher[i].id, teacher[i].name, teacher[i].age, teacher[i].phoneNumber, teacher[i].emailAddress);
                    check = 1;
                }
            }
            break;
        }
        default:{
            printf("Lua chon khong hop le!\n");
            return;
        }
    }

    if (check == 0){
        printf("\nKhong tim thay giao vien!!\n");
    }
}
 
 
 ///***** QUAN LY LOP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showMenuClass(){
    printf("***** QUAN LY LOP HOC*****\n");
    printf("==========================\n");
    printf("[1] Hien thi danh sach lop\n");
    printf("[2] Them lop\n");
    printf("[3] Sua thong tin lop hoc\n");
    printf("[4] Xoa lop hoc\n");
    printf("[5] Tim kiem lop hoc\n");
    printf("[6] Thoat\n");
    printf("==========================\n");
    printf("Lua chon cua ban:\n ");
}

struct Class {
    int classId;
    char className[50];
    int numberOfStudents;
    char teacherName[50];
};

struct Class classes[100];
int classCount = 0;

//Hien thi danh sach LOP
void showClasses(){
	FILE *ptr = fopen("Classroom.bin", "rb");
    if (ptr == NULL) {
        printf("------------------------------------------ \n");
        printf("Khong the mo file de doc du lieu!\n");
        return;
    }
    classCount = fread(classes, sizeof(struct Class), 100, ptr); 
    fclose(ptr);
    if (classCount == 0){
        printf("\nKhong tim thay lop hoc nao\n");
        return;
    }
    
    printf("\nDANH SACH LOP HOC\n");
    printf("==========================\n");
    printf("ID LOP\tTen lop\tSo luong sinh vien\tGiao vien\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < classCount; i++) {
        printf("%d\t%s\t%d\t%s\n", classes[i].classId, classes[i].className, classes[i].numberOfStudents, classes[i].teacherName);
    }
}

// Them lop
void addClass(){
    if (classCount >= 100){
        printf("\nDanh sach lop da day\n");
        return;
    }
    struct Class newClass;
    printf("Nhap ID lop hoc:\n");
    scanf("%d", &newClass.classId);
    printf("Nhap ten lop hoc: ");
    scanf(" %s", newClass.className);
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &newClass.numberOfStudents);
    printf("Nhap ten giao vien cua lop: ");
    scanf(" %s", newClass.teacherName);

    classes[classCount++] = newClass;
    FILE *ptr = fopen("Classroom.bin", "wb");
    if (ptr == NULL){
        printf("\nKhong the mo file de ghi\n");
        return;
    }
    fwrite(classes, sizeof(struct Class), classCount, ptr);  
    fclose(ptr);
    printf("\nThong tin lop da duoc them!!!\n");
}

// Sua lop
void editClass(){
    int classId; 
	int check = 0;
    printf("Nhap ID lop muon sua: ");
    scanf("%d", &classId);
    for (int i = 0; i < classCount; i++){
        if (classes[i].classId == classId){
            check = 1;
            printf("Nhap ten lop moi: ");
            scanf(" %s", classes[i].className);
            printf("Nhap so luong sinh vien moi: ");
            scanf("%d", &classes[i].numberOfStudents);
            printf("Nhap ten giao vien moi: ");
            scanf(" %s", classes[i].teacherName);
            printf("Da sua thong tin lop!\n");
            break;
        }
    }
    if (check !=1){
        printf("Moi ban nhap lai:\n");
    }
}

// Xoa Lop
void deleteClass(){
    int classId;
	int check = 0;
    char confirm;
    printf("Nhap ID lop muon xoa: ");
    scanf("%d", &classId);

    for (int i = 0; i < classCount; i++){
        if (classes[i].classId == classId){
            check = 1;
            printf("\nThong tin lop hoc:\n");
            printf("ID lop: %d\n", classes[i].classId);
            printf("Ten lop: %s\n", classes[i].className);
            printf("So luong sinh vien: %d\n", classes[i].numberOfStudents);
            printf("Giao vien: %s\n", classes[i].teacherName);

            printf("\nBan co muon xoa lop nay?(Y/N): ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y') {
                for (int j = i; j < classCount - 1; j++){
                    classes[j] = classes[j + 1];
                }
                classCount--;
                
                FILE *ptr = fopen("Classroom.bin", "wb");
			    if (ptr == NULL) {
			        printf("Khong the mo file de ghi\n");
			        return;
			    }
			    fwrite(classes, sizeof(struct Class), classCount, ptr);  // S?a t? 'sv' thành 'classes'
			    fclose(ptr);
                
                printf("\nXoa lop hoc thanh cong\n");
            } else {
                printf("\nHUY\n");
            }
            return;
        }
    }
    if (check != 1){
        printf("Moi ban nhap lai:\n");
    }
}

// Tim lop
void searchClass(){
    int searchChoice;
    char searchName[50];
    int check = 0;

    printf("Ban muon tim kiem lop theo:\n");
    printf("1. Ten lop\n");
    printf("2. ID lop\n");
    printf("Lua cho  cua ban: ");
    scanf("%d", &searchChoice);

    printf("\nKet qua:\n");
    printf("ID Lop\tTen lop\tSo luong sinh vien\tGiao vien\n");
    printf("---------------------------------------------------------\n");

    switch (searchChoice) {
        case 1:
            printf("Nhap ten lop muon tim:\n ");
            scanf(" %s", searchName);
            for (int i = 0; i < classCount; i++){
                if (strstr(classes[i].className, searchName) != NULL){
                    printf("%d\t%s\t%d\t%s\n", classes[i].classId, classes[i].className, classes[i].numberOfStudents, classes[i].teacherName);
                    check = 1;
                }
            }
            break;
        case 2:
            printf("Nhap ID lop muon tim:\n");
            scanf("%d", &searchChoice);
            for (int i = 0; i < classCount; i++){
                if (classes[i].classId == searchChoice){
                    printf("%d\t%s\t%d\t%s\n", classes[i].classId, classes[i].className, classes[i].numberOfStudents, classes[i].teacherName);
                    check = 1;
                }
            }
            break;
        default:
            printf("Lua chon khong hop le!\n");
            return;
    }
    if (check != 1){
        printf("\nKhong tim thay lop!\n");
    }
}

 
int main(){
    int choice;
    do {
        showMenuAll();
        scanf("%d", &choice);
        switch (choice){
            case 1: {
            	printf("\n");
                int adminChoice;
                do {
                    showMenuAdmin();
                    scanf("%d", &adminChoice);
                    switch (adminChoice){
                        case 1:{
                        	printf("Quan ly sinh vien \n");
                            int studentChoice;
                            do {
                                showMenuStudent();
                                scanf("%d", &studentChoice);
                                switch (studentChoice){
                                    case 1: showSv(); 
									break;
                                    case 2: addSv(); 
									break;
                                    case 3: editSv(); 
									break;
                                    case 4: deleteSv(); 
									break;
                                    case 5: {
                                        printf("1. Sap xep theo ID\n");
                                        printf("2. Sap xep theo ten\n");
                                        printf("Nhap lua chon: ");
                                        int sortChoice;
                                        scanf("%d", &sortChoice);
                                        if (sortChoice == 1) sortSvID();
                                        else if (sortChoice == 2) sortSvName();
                                        else printf("Lua chon khong hop le!\n");
                                        break;
                                    }
                                    case 6: searchSv(); 
									break;
                                    case 7: printf("Thoat chuong trinh\n"); 
									break;
                                    default: printf("Lua chon khong hop le!\n");
                                }
                            } while (studentChoice != 7);
                            break;
						}
                            
                        case 2:{
                        	printf("\n Quan ly giao vien\n");
								int teacherChoice;
									do {
								showMenuTeacher();
								scanf("%d", &teacherChoice);
									switch (teacherChoice){
								    	case 1: 
											showTeacher();
										break;
								    	case 2: 
											addTeacher(); 
										break;
								    	case 3: 
											editTeacher(); 
										break;
								    	case 4: 
											deleteTeacher(); 
										break;
								    	case 5: 
											searchTeacher(); 
										break;
								    	case 6: 
											printf("Thoat chuong trinh\n"); 
										break;
								    	default: 
											printf("Lua chon khong hop le!\n"); 
										break;
									}
									
									}while (teacherChoice != 6);
                            break;
						}
							
                        case 3:{
                        	printf("Quan ly lop \n");
								int classChoice;
									do {
									showMenuClass();
									scanf("%d", &classChoice);
									switch (classChoice){
								    	case 1: {
											showClasses();
											break;
										}	
								    	case 2: {
								    		addClass(); 
											break;
										}	
								    	case 3: {
								    		editClass(); 
											break;
										}
								    	case 4: {
								    		deleteClass(); 
											break;
										}
								    	case 5: {
								    		searchClass(); 
											break;
										}	
								    	case 6: {
								    		printf("Thoat chuong trinh\n"); 
											break;
										}
								    	default:{
								    		printf("Lua chon khong hop le!\n"); 
                            				break;
										} 
											
                        			}
                        		
								}while( classChoice != 6 );
							break;
						}
                            
                        case 4:{
                        	 printf("\nThoat chuong trinh\n");
							break;
						}
                        default:{
                        	printf("Moi ban chon lai:\n");
							break;
						}
                    }
                    
                } while (adminChoice != 4);
                break;
			}
			
			case 0:{
            	printf("\n==========THANK YOU==========\n");
                printf("=========SEE YOU SOON==========");
                break;
			}
                
            default:{
            	printf("Lua chon khong hop le!\n");
				break;
			}
       }
	
	} while (choice != 0);


    return 0;
}

