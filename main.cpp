#include "TXLib.h"
#include <fstream>

using namespace std;

struct shape
{
    string question;
    string v1;
    string v2;
    string v3;
    HDC p1;
    HDC p2;
    HDC p3;
    int right;
};

string getPart(int *p, string s)
{
    int pos1 = *p +1;
    *p = s.find(",",pos1);
    string part = s.substr(pos1,*p - pos1);
    return part;
}

bool clk(int x)
    {
        return (txMouseButtons() == 1 and
            txMouseX()>x and txMouseX()<x+307 and
            txMouseY()>273 and txMouseY()<562);
    }

int main()
{
    txCreateWindow(1300,730);

    int nQue = 1;
    int point = 0;
    char stroka[50];
    int i = 0;

    string str;
    ifstream file("вопросы.txt");

    shape sh;
    shape sh_list[10];

    while(file.good())
    {
        getline(file,str);
        int pos2 = -1;
        sh_list[i].question = getPart(&pos2,str);
        sh_list[i].v1 = getPart(&pos2,str);
        sh_list[i].v2 = getPart(&pos2,str);
        sh_list[i].v3 = getPart(&pos2,str);
        sh_list[i].p1 = txLoadImage(getPart(&pos2,str).c_str());
        sh_list[i].p2 = txLoadImage(getPart(&pos2,str).c_str());
        sh_list[i].p3 = txLoadImage(getPart(&pos2,str).c_str());
        sh_list[i].right = atoi(getPart(&pos2,str).c_str());
        i++;
    }
    while (nQue<11)
    {
        txSetFillColor(TX_BLACK);
        txClear();
        txBegin();

        sh = sh_list[nQue-1];

        //шаблон
        txSelectFont("Comic Sans",32);
        txSetColor(TX_WHITE);
        txSetFillColor(TX_TRANSPARENT);
        //номер вопроса
        sprintf(stroka,"Вопрос № %d",nQue);
        txDrawText(1100,30,1300,78,stroka);
        //первый вариант ответа
        txRectangle(103,273,410,562);
        txBitBlt(txDC(),103,273,307,289,sh.p1);
        //второй вариант ответа
        txRectangle(504,273,810,562);
        txBitBlt(txDC(),504,273,307,289,sh.p2);
        //третий вариант ответа
        txRectangle(893,273,1199,562);
        txBitBlt(txDC(),893,273,307,289,sh.p3);

        //вопрос
        txRectangle(269,67,1011,167);
        txDrawText(269,67,1011,167,sh.question.c_str());
        //комментарий к 1 вопросу
        txRectangle(103+39,562+24,410-39,562+24+33);
        txDrawText(103+39,562+24,410-39,562+24+33,sh.v1.c_str());
        //комментарий ко 2 вопросу
        txRectangle(504+39,562+24,810-39,562+24+33);
        txDrawText(504+39,562+24,810-39,562+24+33,sh.v2.c_str());
        //комментарий к 3 вопросу
        txRectangle(893+39,562+24,1199-39,562+24+33);
        txDrawText(893+39,562+24,1199-39,562+24+33,sh.v3.c_str());

        if (clk(103))
        {
            if(sh.right == 1)
            {
                point ++;
            }
            while(txMouseButtons() == 1)
            {
                txSleep(10);
            }
            nQue ++;
        }
        if (clk(504))
        {
            if(sh.right == 2)
            {
                point ++;
            }
            while(txMouseButtons() == 1)
            {
                txSleep(10);
            }
            nQue ++;
        }
        if (clk(893))
        {
            if(sh.right == 3)
            {
                point ++;
            }
            while(txMouseButtons() == 1)
            {
                txSleep(10);
            }
            nQue ++;
        }


        txEnd();
    }
    file.close();

    txSetFillColor(TX_BLACK);
    txClear();
    sprintf(stroka, "Ваш результат %d",point);
    txDrawText(0,0,1300,730,stroka);

    txDeleteDC(sh.p1);
    txDeleteDC(sh.p2);
    txDeleteDC(sh.p3);


    txTextCursor(false);
    return 0;
}
