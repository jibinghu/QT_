#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setMaximumSize(220,320);
    this->setMinimumSize(220,320);

    this->setWindowTitle("Calculator");

    QFont f("Umpush Bold",14);
    ui->mainlineEdit->setFont(f);

    // put picture on delete button

    QIcon con("/home/jibinghu23/Documents/QT_subject/Calculator/delete.png");
    ui->deleteButton->setIcon(con);
    // set equal symbol color
    ui->equalButton->setStyleSheet("background:grey");
}

Widget::~Widget()
{
    delete ui;
}


// display all operand and symbol

void Widget::on_oneButton_clicked()
{
    expression += "1";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_twoButton_clicked()
{
    expression += "2";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_threeButton_clicked()
{
    expression += "3";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_fourButton_clicked()
{
    expression += "4";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_fiveButton_clicked()
{
    expression += "5";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_sixButton_clicked()
{
    expression += "6";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_sevenButton_clicked()
{
    expression += "7";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_eightButton_clicked()
{
    expression += "8";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_nineButton_clicked()
{
    expression += "9";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_zeroButton_clicked()
{
    expression += "0";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_addButton_clicked()
{
    expression += "+";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_subButton_clicked()
{
    expression += "-";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_multiplyButton_clicked()
{
    expression += "*";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_dividedButton_clicked()
{
    expression += "/";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_leftButton_clicked()
{
    expression += "(";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_rightButton_clicked()
{
    expression += ")";
    ui->mainlineEdit->setText(expression);
}

void Widget::on_clearButton_clicked()
{
    expression.clear();
    ui->mainlineEdit->clear();
}

void Widget::on_deleteButton_clicked()
{
    expression.chop(1);
    ui->mainlineEdit->setText(expression);
}

// calculator logic
void Widget::on_equalButton_clicked()
{
    if (expression.isEmpty())
    {
        exit(0);
    }
    QStack<int> s_num,s_opt;

    char opt[128] = {0};
    int i=0,tmp=0,num1,num2;
    // convert QString to char*
    QByteArray ba;
    ba.append(expression); // convert QString to QByteArray
    strcpy(opt,ba.data()); // data could convert QByteArray to const char*

    while (opt[i] != '\0' || s_opt.empty() != true)
    {
        if (opt[i] >= '0' && opt[i] <= '9')
        {
            tmp = tmp * 10 + opt[i] - '0';
            i++;
            if (opt[i] < '0' || opt[i] > '9')
            {
                s_num.push(tmp);
                tmp = 0;
            }
        }
        else
        {
            if (s_opt.empty() == true || Priority(opt[i]) > Priority(s_opt.top()) ||
                    (s_opt.top() == '(' && opt[i] != ')'))
            {
                s_opt.push(opt[i]);
                i++;
                continue;
            }
            if (s_opt.top() == '(' && opt[i] != ')')
            {
                s_opt.pop();
                i++;
                continue;
            }
            if(Priority(opt[i]) <= Priority(s_opt.top()) || (opt[i] == ')' && s_opt.top() != '(') ||
                    (opt[i] == '\0' && s_opt.empty() != true))
            {
                char ch = s_opt.top();
                s_opt.pop();
                switch(ch)
                {
                    case '+':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push(num1 + num2);
                        break;
                    case '-':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push(num1 - num2);
                        break;
                    case '*':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push(num1 * num2);
                        break;
                    case '/':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push(num1 / num2);
                        break;
                }
            }
        }
    }
    ui->mainlineEdit->setText(QString::number(s_num.top()));
    expression.clear();
}

int Widget::Priority(char ch)
{
    switch(ch)
    {
        case '(':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
         default:
            return 0;
    }
}
