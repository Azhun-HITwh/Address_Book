//
//  address_book.c
//  Address_Book
//
//  Created by Azhun Zhu on 2022/1/17.
//

#include "address_book.h"

#define PRIVATE static

PRIVATE int FindName(AddressBook *address_book, char search_name[100]){
    
    for (int i = 0; i < address_book->size; i++) {
        if (strcmp(address_book->all_address[i].name, search_name) == 0) {
            return i;
        }
    }
    
    return -1;
    
}

PRIVATE void ReallocBook(AddressBook *address_book){
    
    int newSize = (address_book->capacity == 0 ? 1 : 2 * address_book->capacity);
    
    PersonInfo *newAddress = realloc(address_book->all_address, newSize * sizeof(PersonInfo));
    if (!newAddress) {
        strerror(errno);
        exit(EXIT_FAILURE);
    }
    
    address_book->all_address = newAddress;
    address_book->capacity = newSize;
    
}

PRIVATE void LoadBook(AddressBook *address_book){
    
    FILE *fp = fopen("address_book.txt", "r");
    
    if (fp == NULL) {
        strerror(errno);
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        if (address_book->size == address_book->capacity) {
            ReallocBook(address_book);
        }
        
        PersonInfo tmp = {0};
        
        unsigned long n = fread(&tmp, sizeof(PersonInfo), 1, fp);
        
        if (n < 1) {
            break;
        }
        
        address_book->all_address[address_book->size++] = tmp;
        
    }
    printf("文件已载入！\n");
    fclose(fp);
    
}

PRIVATE void SaveBook(AddressBook *address_book){
    
    FILE *fp = fopen("address_book.txt", "w");
    
    if (fp == NULL) {
        strerror(errno);
        exit(EXIT_FAILURE);
    }
    
    unsigned long n = fwrite(address_book->all_address, sizeof(PersonInfo), address_book->size, fp);
    if (n != address_book->size) {
        strerror(errno);
        exit(EXIT_FAILURE);
    }
    printf("文件已保存！\n");
    fclose(fp);
}

int Menu(void){
    printf("\n\n\n\n\n\t\t\t\t\t\t AddressBook Management System\n");
    printf("\t\t\t\t\t\t     @author：Adrian Zhu \n");
    printf("\t\t\t\t\t\t    ======================\n");
    printf("\t\t\t\t\t\t    ***     0.退出     ***\n");
    printf("\t\t\t\t\t\t    ***  1.新增联系人  ***\n");
    printf("\t\t\t\t\t\t    ***  2.删除联系人  ***\n");
    printf("\t\t\t\t\t\t    ***  3.查找联系人  ***\n");
    printf("\t\t\t\t\t\t    ***  4.修改联系人  ***\n");
    printf("\t\t\t\t\t\t    ***  5.打印联系人  ***\n");
    printf("\t\t\t\t\t\t    ***  6.清除联系人  ***\n");
    printf("\t\t\t\t\t\t    ***  7.排序联系人  ***\n");
    printf("\t\t\t\t\t\t    ======================\n");

    printf("请输入你的选择：");
    int choice;
    scanf("%d", &choice);

    return choice;
}

void InitBook(AddressBook *address_book){
    
    address_book->size = 0;
    address_book->all_address = NULL;
    address_book->capacity = 0;
    
    LoadBook(address_book);
    
}

void AddPersonInfo(AddressBook *address_book){
    
    printf("新增联系人\n");
    
    if (address_book->size >= address_book->capacity) {
        ReallocBook(address_book);
    }
    
    PersonInfo *info = &address_book->all_address[address_book->size];
    
    printf("请输入联系人姓名：");
    scanf("%s", info->name);
    printf("请输入联系人电话：");
    scanf("%s", info->phone);

    address_book->size++;

//    system("pause");
    
}

void DelPersonInfo(AddressBook *address_book){
    
    char search_name[100] = {0};
    
    printf("删除联系人\n");
    printf("请输入联系人姓名：");
    scanf("%s", search_name);
    
    int name_exist = FindName(address_book, search_name);
    
    if (name_exist == -1) {
        printf("该联系人不存在！\n");
//        system("pause");
        return;
    }
    
    while (name_exist != -1) {
        address_book->all_address[name_exist] = address_book->all_address[address_book->size - 1];
        address_book->size--;
        name_exist = FindName(address_book, search_name);
    }
    printf("删除成功！\n");
    return;
        
//    system("pause");
    
}

void FindPersonInfo(AddressBook* address_book) {

    char search_name[100] = { 0 };

    //搜索人的方式也很多，我们这里用搜索名字的方法
    printf("搜索联系人\n");
    printf("请输入人名：");
    scanf("%s", search_name);

    for (int i = 0; i < address_book->size; i++) {
        PersonInfo* info = &address_book->all_address[i];
        if (strcmp(info->name, search_name) == 0) {
            printf("[%d] %s  %s\n", i, info->name, info->phone);
        }
    }
    
    return;
//    system("pause");
}

void ModifyPersonInfo(AddressBook* address_book) {
    
    char search_name[100] = { 0 };
    int isjump = 1;

    printf("修改联系人\n");
    printf("请输入联系人姓名：");
    scanf("%s", search_name);

    int name_exist = FindName(address_book, search_name);

    if (name_exist == -1) {
        printf("该联系人不存在！\n");
//        system("pause");
        return;
    }
    
    printf("请输入新的姓名，输入 0 跳过：");
    scanf("%d", &isjump);
    if (isjump) {
        scanf("%s", address_book->all_address[name_exist].name);
    }
    printf("请输入新的电话，输入 0 跳过：");
    scanf("%d", &isjump);
    if (isjump) {
        scanf("%s", address_book->all_address[name_exist].phone);
    }

    printf("更新成功！\n");
    return;
//    system("pause");
}

void PrintPersonInfo(AddressBook* address_book) {
    
    PersonInfo* info;

    if (address_book->size == 0) {
        printf("当前没有联系人！\n");
//        system("pause");
        return;
    }

    printf("所有联系人信息如下：\n");
    
    for (int i = 0; i < address_book->size; i++) {
        info = &address_book->all_address[i];
        printf("[%03d]%4s  %s\n", i, info->name, info->phone);
    }
    
    return;
//    system("pause");
}

void ClearPersonInfo(AddressBook* address_book) {
    
    int is_continue = 0;

    printf("清除所有联系人，你确定吗？输入 0 继续: ");
    scanf("%d", &is_continue);
    if(is_continue == 0) {
        address_book->size = 0;
        printf("清除完成！\n");
//        system("pause");
    }
    printf("已取消！\n");
    
    return;
//    system("pause");
}

void SortPersonInfo(AddressBook* address_book) {

    printf("排序通讯录\n");
    // 冒泡排序
    for (int i = 0; i < address_book->size - 1; i++) {
        for (int j = 0; j < address_book->size - 1 - i; j++) {
            PersonInfo* info = &address_book->all_address[j];
            PersonInfo* info_next = &address_book->all_address[j + 1];
            if (strcmp(info->name, info_next->name) > 0) {
                PersonInfo tmp;
                tmp = *info;
                *info = *info_next;
                *info_next = tmp;
            }
        }
    }
    printf("排序成功！\n");

    return;
//    system("pause");
}

void DestoryBook(AddressBook* address_book) {

    SaveBook(address_book);

    free(address_book->all_address);
    address_book->all_address = NULL;
    /*赋值运算的运算顺序是自右向左
      所以a=b=0相当于a=(b=0)
     */
    address_book->capacity = address_book->size = 0;
    
    return;
}
