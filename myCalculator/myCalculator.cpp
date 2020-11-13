#include <iostream>  
using namespace std;

double expression();
double term();
double primary();
void welcome();
void calculate();
const char number = '8';
const char print = ';';
const char quit = 'e';
const string prompt = "input:";

class Token 
{
public:
    char kind;
    double value;
    Token(char kind = '\0', double value = 0):kind(kind), value(value)
    {}
};

class Token_stream 
{
public:
    //得到下一个token保存
    Token get()
    {
        //缓冲区有单词，从缓冲区中取单词   
        if (true == full)
        {
            full = false;
            return buffer;
        }
        //缓冲区没有单词，从输入流中取单词   
        char ch;
        cin >> ch;
        switch (ch)
        {
            //若遇到的是符号，就单保存一个符号
        case '+':case '-':case '*':
        case '/':case '%':case '(':
        case ')':case print:case quit:
            return Token(ch);
            //若遇到的是数字，先放回去再统一读取
        case '.':
        case '0':case '1':case '2':case '3':case '4':
        case '5':case '6':case '7':case '8':case '9':
        {
            cin.putback(ch);
            double val;
            cin >> val;
            return Token(number, val);
        }
        default:
        {
            cout << "err input!" << endl;
        }
        }
    }
    //将得到的token放回buffer中保存以供下一次使用
    void putback(Token t)
    {
        if (true == full)
        {
            cout << "err: m_buffer is full." << endl;
            return;
        }
        full = true;
        buffer = t;
    }
    Token_stream():full(false), buffer('\0', 0)
    {}
private:
    bool full;
    Token buffer;
};

//包含了一个只能存储一个变量的buffer   
Token_stream ts;

//处理+ - 加、减运算  
double expression()
{
    double left = term();
    Token t = ts.get();
    while (true) 
    {
        switch (t.kind) 
        {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

//处理* / % 乘、除、取余运算  
double term()
{
    double left = primary();
    Token t = ts.get();
    while (true) 
    {
        switch (t.kind) 
        {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            //若除数为0，进行处理
            if (0 == d) 
            {
                cout << "divide into zero" << endl;
            }
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = primary();
            int i1 = int(left);
            int i2 = int(d);
            if (i1 != left) 
            {
                cout << "left operand not int" << endl;
            }
            if (i2 != d) 
            {
                cout << "right operand not int" << endl;
            }
            if (i2 == 0) 
            {
                cout << "% divide into 0" << endl;
            }
            left = i1 % i2;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}
//处理（）- + 括号、正、负运算  

double primary()
{
    Token t = ts.get();
    switch (t.kind) 
    {
    case number:
        return t.value;
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (')' != t.kind)
        {
            cout << "expected ')'" << endl;
        }
        return d;
    }
    case '-':
        return -primary();
    case '+':
        return +primary();
    default:
        cout << "expected primary!" << endl;
    }
}

void calculate()
{
    while (cin) 
    {
        cout << prompt;
        Token t = ts.get();
        while (print == t.kind) t = ts.get();
        if (quit == t.kind) return;
        else ts.putback(t);
        cout << "ans" << '=' << expression() << endl;
    }
}

void welcome()
{
    cout << "Welcome to our simple calculator." << endl
        << "-----------------------------" << endl
        << "floating-point numbers" << endl
        << "operator: '+' '-' '*' '/' '%'" << endl
        << "negative: '-'" << endl
        << "positive: '+'" << endl
        << "end of expression: ';'" << endl
        << "quit: 'e'" << endl
        << "-----------------------------" << endl;
}

int main()
{
    welcome();
    calculate();
    cout << "program stopped" << endl;
    return 0;
}
