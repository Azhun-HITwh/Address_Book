//
//  address_book.h
//  Address_Book
//
//  Created by Azhun Zhu on 2022/1/17.
//

#ifndef address_book_h
#define address_book_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

typedef struct PersonInfo {
    char name[100];
    char phone[100];
}PersonInfo;

typedef struct AddressBook {
    PersonInfo *all_address;
    int size;
    int capacity;
}AddressBook;

int Menu(void);

void InitBook(AddressBook* address_book);

void AddPersonInfo(AddressBook* address_book);

void DelPersonInfo(AddressBook* address_book);

void FindPersonInfo(AddressBook* address_book);

void ModifyPersonInfo(AddressBook* address_book);

void PrintPersonInfo(AddressBook* address_book);

void ClearPersonInfo(AddressBook* address_book);

void SortPersonInfo(AddressBook* address_book);

void DestoryBook(AddressBook* address_book);

#endif /* address_book_h */
