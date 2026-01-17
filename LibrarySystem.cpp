#include <iostream>
#include <string>

using namespace std;

enum enMenuOperation { Print = 1, OldestBook = 2, AvailableBook = 3, Exit = 4 };
enum enBookCategory { Fiction = 1, NonFiction = 2, Science = 3, Biography = 4 };

struct strBookData
{
    string Title;
    string Author;
    enBookCategory Category;
    int YearPublished;
    bool Availability;
};

void BookCategoryMenu()
{
    cout << "************************\n";

    cout << "Book Category Menu\n";
    cout << "1- Fiction\n";
    cout << "2- Non Fiction\n";
    cout << "3- Science\n";
    cout << "4- Biography\n";

    cout << "************************\n";
    cout << "Choose a number between(1-4)\n";

}
void MainMenu()
{
    cout << "\n***Menu***\n";
    cout << "1- Print All Books\n";
    cout << "2- Show the oldest book\n";
    cout << "3- Show how many books are available\n";
    cout << "4- Exit\n";
    cout << "*******************\n";

    cout << "Choose a number:\n";
}

int ReadNumberInRange(int From, int To)
{
    int Number = 0;
    bool ShowWrongMessage = false;

    do {

        if (ShowWrongMessage) {
            cout << "Wrong Number, The number must be between ("
                << From << "-" << To << ")" << endl;
        }
            
        BookCategoryMenu();
        cin >> Number;

        ShowWrongMessage = true;

    } while (Number < From || Number > To);

    return Number;
}

enBookCategory ConvertNumberToEnum(int Num)
{
    return (enBookCategory)Num;
}

strBookData ReadBookData()
{
    strBookData Data;

    cout << "Plz enter the book title:\n";
    cin.ignore();
    getline(cin, Data.Title);

    cout << "Plz enter the book author:\n";
    getline(cin, Data.Author);

    int CategoryChoice = ReadNumberInRange(1, 4);

    Data.Category = ConvertNumberToEnum(CategoryChoice);

    cout << "Plz enter the year that the book has been published in:\n";
    cin >> Data.YearPublished;

    cout << "Is the book available:(Y/N)\n";
    char A = ' ';
    cin >> A;

    Data.Availability = (A == 'Y' || A == 'y');

    return Data;

}
void ReadAllBooks(strBookData Books[5])
{
    for (int i = 0; i < 5;i++) {

        cout << "Book Number" << i + 1 << "'s info:\n";
        Books[i] = ReadBookData();
    }


}

string CategoryAsString(enBookCategory Category)
{
    switch (Category)
    {
    case enBookCategory::Fiction:
        return "Fiction";

    case enBookCategory::NonFiction:
        return "Non Fiction";

    case enBookCategory::Biography:
        return "Biography";

    case enBookCategory::Science:
        return "Science";

    default:
        return "Unknow Category";
    }
}

string AvailabilityAsString(bool istrue)
{
    if (istrue)
        return "Yes";
    else
        return "No";
}

void PrintBook(strBookData Book)
{
    string Category = CategoryAsString(Book.Category);

    string Available = AvailabilityAsString(Book.Availability);

    cout << "Book Title: " << Book.Title << endl;
    cout << "Book Author: " << Book.Author << endl;
    cout << "Book Category: " << Category << endl;
    cout << "Publishing Year: " << Book.YearPublished << endl;
    cout << "Available: " << Available << endl;
}
void PrintAllBooks(strBookData Books[5])
{
    for (int i = 0; i < 5;i++) {

        cout << "\n************************\n";
        PrintBook(Books[i]);
    }

}

string ShowOldestBook(strBookData Books[5])
{
    string OldestBook = Books[0].Title;
    int OldestBookYearPublished = Books[0].YearPublished;

    for (int i = 1; i < 5;i++) {

        if (Books[i].YearPublished < OldestBookYearPublished) {

            OldestBookYearPublished = Books[i].YearPublished;
            OldestBook = Books[i].Title;
        }

    }

    return OldestBook;

}
int CountAvailableBooks(strBookData Books[5])
{
    int Counter = 0;

    for (int i = 0;i < 5;i++) {

        if (Books[i].Availability)
            Counter++;
    }

    return Counter;

}

string ShowBooksSameCategory(strBookData Books[5], enBookCategory Category)
{
    string Result = "";

    for (int i = 0;i < 5;i++) {

        if (Books[i].Category == Category)

            Result += Books[i].Title + "\n";
    }

    return Result;

}

enMenuOperation GetOpration(int Num)
{
    return (enMenuOperation)Num;
}

int main()
{
    strBookData Books[5];
    ReadAllBooks(Books);

    int Number = 0;

    do {

        MainMenu();

        Number = ReadNumberInRange(1, 4);

        enMenuOperation Operation = GetOpration(Number);

        switch (Operation) {

        case enMenuOperation::Print:
            PrintAllBooks(Books);
            break;

        case enMenuOperation::OldestBook:
            cout << "\n****************\n";
            cout << "The oldest book: "
                << ShowOldestBook(Books) << endl;
            break;

        case enMenuOperation::AvailableBook:
            cout << "\n****************\n";
            cout << "Available books: "
                << CountAvailableBooks(Books);
            break;

        case enMenuOperation::Exit:
            break;

        default: break;
        }

    } while (Number != 4);

    cout << "\n****************\n";
    cout << "Have a nice day, Bey Bey\n";

    BookCategoryMenu();


    int Number = ReadNumberInRange(1, 4);

    enBookCategory Category = ConvertNumberToEnum(Number);

    cout << ShowBooksSameCategory(Books, Category) << endl;

    return 0;
}
