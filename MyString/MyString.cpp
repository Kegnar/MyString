//Разработать класс String, который в дальнейшем будетиспользоваться для работы со строками.Класс долженсодержать :
//Конструктор по умолчанию, позволяющий создатьстроку длиной 80 символов;
//Конструктор, позволяющий создавать строку произвольного размера;
//Конструктор, который создаёт строку и инициализирует её строкой, полученной от пользователя.
//Необходимо создать деструктор, а также использоватьмеханизмы делегирования конструкторов, если это возможно.
//Класс должен содержать методы для ввода строк с клавиатуры и вывода строк на экран.
//Также нужно реализоватьстатическую функцию - член, которая будет возвращатьколичество созданных объектов строк

//Добавьте все необходимые конструкторы и перегрузки для максимальной близости к оригинальному классу.

#include <iostream>
#include <Windows.h>

using namespace std;

class MyString
{
    static inline size_t cnt{0};       // способ инициализировать статическую переменную внути класса при помощи inline
    size_t length;
	char* line;
    
public:

	MyString() :MyString(nullptr) {}

    MyString(const char* lineP)
	{
        cnt++;
        if (lineP) {
            length = strlen(lineP);
            line = new char[length + 1] {};
            strcpy_s(line, length + 1, lineP);
        }
	}
    MyString(size_t lengthP, char* lineP) :length{ lengthP }, line{ lineP }{}

    // конструктор копирования
    MyString(const MyString& myStr):MyString(myStr.length, myStr.line){}

    // конструктор перемещения
    MyString(MyString&& myStr)noexcept
	{
        this->length = myStr.length;
        this->line = myStr.line;
        myStr.line = nullptr;
	}

    ~MyString()
    {
#ifdef _DEBUG
        cout << "Сработал деструктор и убил " << cnt << "-й объект\n";
#endif
        if(!line)
        {
	        delete[]line;
        }
        cnt--;
    }

    // ввод строки до символа ввода
    void getLine()      
    {
#define MAXLEN 32767  // максимальная длина строки
               
        char buffStr[MAXLEN]{};
        gets_s(buffStr, MAXLEN);
        this->length = strlen(buffStr);
        delete[] line;              // грохаем то, что было в строке до ввода
        line = new char[length + 1] {};
        strcpy_s(line, this->length+1, buffStr);
    }
    // печать
    void print()const
    {
		cout << this->line;
    }
    //длина строки
    size_t strLength()const
	{
        return this->length;
	}
    static size_t stringCounter()
    {
        return cnt;
    }

	friend istream& operator>>(istream&, MyString&);
    friend ostream& operator<< (ostream&, const MyString&);
    friend MyString operator+(const MyString&, const MyString&);
    MyString& operator=(const MyString& myStr)
    {
        if (this != &myStr) {
            this->length = myStr.length;
            this->line = new char[this->length + 1];
            strcpy_s(this->line, length, myStr.line);
        }
        return *this;
    }

    MyString& operator=(MyString&& myStr)noexcept
    {
        if (this != &myStr) {
            delete[]line;
            this->length = myStr.length;
            this->line = myStr.line;
        }
        return *this;
    }
    MyString& operator+=( const MyString& str)
    {
        strcat_s(this->line, MAXLEN * 2 + 1, str.line);
        this->length += str.length;
        return *this;
    }
    bool operator==(const MyString& str) const
    {
        return (!strcmp(this->line, str.line)); // strcmp возвращает 0 если строки равны
    }

};
MyString operator+(const MyString& str1, const MyString& str2)
{
    MyString tmp{ str1 };
    tmp.length = str1.length + str2.length;
    strcat_s(tmp.line, tmp.length + 1, str2.line);
    return tmp;
}
ostream& operator<< (ostream& os, const MyString& string)
{
    os << string.line;
    return os;
}
istream& operator>>(istream& is, MyString& string) // как и в стандартном string оператор >> вытягивает из потока набор символов до пробела
{
    char buffer[MAXLEN+1]{};
    is.get(buffer, MAXLEN,' ');

    string.length = strlen(buffer);
    string.line = buffer;
    return is;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    MyString test;

 //   cout << "Ввод данных в объект через метод:";
 //   test.getLine();
 //   cout << "Вывод данных из объекта через метод:";
	//test.print();
 //   cout << '\n';
 //   cout << "Ввод данных в объект через перегруз >>:";
 //   cin >> test;
 //   cout << "Печать при помощи перегрузки оператора <<: " << test << '\n';

    char str[] = "Куку";
    MyString test2{ str };
    test2.print();
    cout << '\n';
    MyString test3; // проверка работы деструктора на пустом объекте
    MyString test4{ "ПЫЩЪ!" };
    MyString test5 = test2 + test4;
    cout << test5 << '\n';
    cout << (test4 == test2) << '\n';
    const MyString test6{ test4 };
    cout << (test6 == test4) << '\n';
}

