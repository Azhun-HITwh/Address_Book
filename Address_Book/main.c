//
//  main.c
//  Address_Book
//
//  Created by Azhun Zhu on 2022/1/17.
//

#include <stdio.h>
#include "address_book.h"

int main(int argc, const char * argv[]) {
    
    AddressBook address_book;
    
    typedef void (*Func)(AddressBook*);
    Func func_table[] = {
        DestoryBook,
        AddPersonInfo,
        DelPersonInfo,
        FindPersonInfo,
        ModifyPersonInfo,
        PrintPersonInfo,
        ClearPersonInfo,
        SortPersonInfo,
    };
    
    InitBook(&address_book);
        

    while (1) {
        system("clear");
        int choice = Menu();

        if (choice < 0 || choice > 7) {
            printf("输入错误！\n");
            continue;
        }

        func_table[choice](&address_book);

        if (choice == 0) {
            printf("\n 再见！\n");
            break;
        }
    }
    
return 0;
}
