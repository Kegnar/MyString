//Разработать класс String, который в дальнейшем будетиспользоваться для работы со строками.Класс долженсодержать :
//Конструктор по умолчанию, позволяющий создатьстроку длиной 80 символов;
//Конструктор, позволяющий создавать строку произвольного размера;
//Конструктор, который создаёт строку и инициализирует её строкой, полученной от пользователя.
//Необходимо создать деструктор, а также использоватьмеханизмы делегирования конструкторов, если это возможно.
//Класс должен содержать методы для ввода строк с клавиатуры и вывода строк на экран.
//Также нужно реализоватьстатическую функцию - член, которая будет возвращатьколичество созданных объектов строк

#include <iostream>
#include <Windows.h>

using namespace std;

class MyString
{
    static inline unsigned cnt{0};       // способ инициализировать статическую переменную внути класса при помощи inline
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

    ~MyString()
    {
#ifdef _DEBUG
        cout << "Сработал деструктор и убил " << cnt << "-й объект\n";
#endif
        delete []line;
        cnt--;
    }
  
    
	static int stringCounter()
    {
        return cnt;
    }

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
    void print()
    {
		cout << this->line << endl;
    }
    char* getStr() const
	{
        return this->line;
	}
    void setStr(char* string_p)
	{
        this->line = string_p;
        this->length = strlen(string_p);
	}
    friend istream& operator>>(istream&, MyString&);

};
ostream& operator<< (ostream& os, const MyString& string)
{
    os << string.getStr();
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

    cout << "Ввод данных в объект через метод:";
    test.getLine();
    cout << "Вывод данных из объекта через метод:";
	test.print();
    cout << '\n';
    cout << "Ввод данных в объект через перегруз >>:";
    cin >> test;
    cout << "Печать при помощи перегрузки оператора <<: " << test << '\n';

    char str[] = "Куку";
    MyString test2{ str };
    test2.print();
    
}

