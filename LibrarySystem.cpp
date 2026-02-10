#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

enum enOperations { PrintAllBooks = 1, PrintAvailableBooks, PrintOldestBook };
enum enCategories { Fiction = 1, NonFiction, Science, Biography};
struct strBook
{
    string Title = "";
    string Author ="";
    enCategories Category;
    int PublishedYear = 0;
    bool isAvailable = false;
};
struct strBooks
{
    int HowManyBooks = 0;
    vector <strBook> vBookList;
};
void CategoryMenu()
{
    cout << "************************\n";

    cout << "** Category Menu **\n\n";
    cout << "[1].Fiction\n";
    cout << "[2].Non Fiction\n";
    cout << "[3].Science\n";
    cout << "[4].Biography\n";

    cout << "************************\n";
    
}
void OperationsMenu()
{
    cout << "\n** Operations Menu **\n\n";
    cout << "[1].Show All Books\n";
    cout << "[2].ShowAvailableBooks\n";
    cout << "[3].ShowOldestBook\n";

    cout << "*******************\n";

}
void CleanBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void ReadValidInt(std::string Message, int& Number)
{
    std::cout << Message;
    std::cin >> Number;

    while (std::cin.fail())
    {
        std::cin.clear();
        CleanBuffer();
        std::cout << "Invalid Number, plz enter a valid one:\n";
        std::cin >> Number;
    }

}
void InvalidNumber_ErrorMessage(int From, int To)
{
    std::cout << "Wrong Number, The number must be between ("
        << From << "-" << To << ")\n";

}
int ReadIntInRange(std::string Message, int From, int To)
{
    int Number = 0;
    bool isInValid = false;

    do {

        if (isInValid) {
            InvalidNumber_ErrorMessage(From, To);
        }

        ReadValidInt(Message, Number);

        isInValid = true;

    } while (Number < From || Number > To);

    return Number;
}
strBook ReadOneBook()
{
    strBook Book;
    char Answer = 'Y';

    cout << "Title: ";
    getline(cin>>ws, Book.Title);

    cout << "Author: ";
    getline(cin, Book.Author);

    CategoryMenu();
    Book.Category = (enCategories)ReadIntInRange("Choose a number: ", 1, 4);

    ReadValidInt("Published year: ", Book.PublishedYear);

    cout << "Is the book still available? Y/N ?\n";
    cin >> Answer;
    Book.isAvailable = (Answer == 'Y' || Answer == 'y');

    return Book;
}
strBooks ReadAllBooks()
{
    strBooks Books;
    strBook TempBook;

    ReadValidInt("How many books would you like to add: ", Books.HowManyBooks);

    for (int i = 0; i < Books.HowManyBooks;i++) 
    {
        cout << "\nEnter book" << i + 1 << " info\n";
        TempBook = ReadOneBook();

        Books.vBookList.push_back(TempBook);

    }

    cout << endl;

    return Books;
}
string CategoryAsText(enCategories Category)
{
    string ArrCategory[4] = { "Fiction","NonFiction","Science","Biography" };

    return ArrCategory[Category - 1];
}
string Availability(bool Answer)
{
    return (Answer) ? "Yes" : "No";
}
void ShowOneBook(const strBook& Book,int BookNumber)
{
    cout << "\nBook" << BookNumber << " info:\n\n";
    cout << "Title: " << Book.Title << endl;
    cout << "Author: " << Book.Author << endl;
    cout << "Category: " << CategoryAsText(Book.Category) << endl;
    cout << "Publishing Year: " << Book.PublishedYear << endl;
    cout << "Availability: " << Availability(Book.isAvailable) << endl;
}
void ShowAllBooks(const vector <strBook>& vBookList)
{
    cout << "\nBooks list:\n";
    for (int i = 0; i < vBookList.size();i++) 
    {
        ShowOneBook(vBookList[i], i + 1);

    }
    cout <<endl<< endl;
}
void AvailableBooks(const vector <strBook>& vBookList)
{
    bool isAvailable = false;

    cout << "\nAvailable Books list:\n";
    for (const strBook& Book : vBookList) {

        if (Book.isAvailable) {
            isAvailable = true;
            cout << Book.Title << "\n";
        }
            
    }

    if (!isAvailable)
        cout << "\nThere aren't any available books at this time :-(\n";

    cout << endl;
}
void OldestBook(const vector <strBook>& vBookList)
{
    string OldestBookName = vBookList[0].Title;
    int OldestB_PublishedYear = vBookList[0].PublishedYear;

    for (int i = 1;i < vBookList.size();i++) {

        if (vBookList[i].PublishedYear < OldestB_PublishedYear) {

            OldestBookName = vBookList[i].Title;
            OldestB_PublishedYear = vBookList[i].PublishedYear;
        }

    }

    cout << "\nThe oldest book:\n";
    cout << "Title: " << OldestBookName << endl;
    cout << "Published Year: " << OldestB_PublishedYear << endl;
    cout << endl;
}
void OperationsProcess(const vector <strBook>& vBookList,enOperations Choice)
{
    switch (Choice)
    {
    case enOperations::PrintAllBooks:
        ShowAllBooks(vBookList);
        break;
    case enOperations::PrintAvailableBooks:
        AvailableBooks(vBookList);
        break;
    case enOperations::PrintOldestBook:
        OldestBook(vBookList);
        break;

    default:"\nWrong Choice\n";

    }

}
void StartProgram()
{
    strBooks Books;
    char isContinue = 'Y';
    enOperations Choice;

    do {

        Books = ReadAllBooks();
        OperationsMenu();
        Choice = (enOperations)ReadIntInRange("Choose a number between(1-4): ", 1, 4);
        OperationsProcess(Books.vBookList, Choice);

        cout << "Do you want to continue? Y/N ? ";
        cin >> isContinue;

    } while (isContinue == 'Y' || isContinue == 'y');

    cout << "Have a nice day, Bey Bey\n";


}

int main()
{
    StartProgram();

    

    return 0;
}
