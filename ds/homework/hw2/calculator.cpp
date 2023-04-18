#include <iostream>
#include<cstdio>
#include<ctype.h>
#include<cstring>
#include<cmath>
#include"..\..\stack\stack2.h"
using namespace std;
#define N_OPTR 9 //���������

typedef enum
{
    ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE,
} Operator; //���������


//�ӡ������ˡ������˷����׳ˡ������š������š���ʼ������ֹ��
const char pri[N_OPTR][N_OPTR] =
{ //��������ȵȼ� [ջ��] [��ǰ]
   /*              |-------------------- �� ǰ �� �� �� --------------------| */
   /*              +      -      *      /      ^      !      (      )      \0 */
    /* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
    /* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
    /* ջ  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
    /* ��  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
    /* ��  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
    /* ��  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
    /* ��  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
    /* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
    /* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};

void readNumber(char*& p, Stack<double>& stk)
{ //����ʼ��p���Ӵ�����Ϊ��ֵ�������������ջ
    stk.push((double)(*p - '0')); //��ǰ��λ��Ӧ����ֵ��ջ
    while (isdigit(*(++p))) //ֻҪ�������н��ڵ����֣�����λ���������������
    {
        stk.push(stk.pop() * 10 + (*p - '0')); //����ԭ��������׷������λ������ֵ������ջ
    }
    if ('.' != *p)
    {
        return; //�˺��С���㣬����ζ�ŵ�ǰ�������������
    }
    float fraction = 1; //������ζ�Ż���С������
    while (isdigit(*(++p))) //��λ����
    {
        stk.push(stk.pop() + (*p - '0') * (fraction /= 10)); //С������
    }
}
Operator optrrank(char op)
{ //�������ת������
    switch (op)
    {
    case '+':
    {
        return ADD; //��
    }
    case '-':
    {
        return SUB; //��
    }
    case '*':
    {
        return MUL; //��
    }
    case '/':
    {
        return DIV; //��
    }
    case '^':
    {
        return POW; //�˷�
    }
    case '!':
    {
        return FAC; //�׳�
    }
    case '(':
    {
        return L_P; //������
    }
    case ')':
    {
        return R_P; //������
    }
    case '\0':
    {
        return EOE; //��ʼ������ֹ��
    }
    default:
    {
        exit(-1); //δ֪�����
    }
    }
}
char priority(char op1, char op2) //�Ƚ����������֮������ȼ�
{
    return pri[optrrank(op1)][optrrank(op2)];
}
void append(char*& rpn, double opnd)
{ //������������RPNĩβ
    char buf[64];
    if (0.0 < opnd - (int)opnd)
    {
        sprintf(buf, "%f \0", opnd); //�����ʽ����
    }
    else
    {
        sprintf(buf, "%d \0", (int)opnd); //������ʽ
    }
    rpn = (char*)realloc(rpn, sizeof(char) * (strlen(rpn) + strlen(buf) + 1)); //��չ�ռ�
    strcat(rpn, buf); //RPN�ӳ�
}
void append(char*& rpn, char optr)
{ //�����������RPNĩβ
    int n = strlen(rpn); //RPN��ǰ���ȣ���'\0'��β������n + 1��
    rpn = (char*)realloc(rpn, sizeof(char) * (n + 3)); //��չ�ռ�
    sprintf(rpn + n, "% c", optr);
    rpn[n + 2] = '\0'; //����ָ���������
}
__int64 facI(int n)
{
    __int64 f = 1;
    while (n > 1)
    {
        f *= n--;
    }
    return f;
} //�׳����㣨�����棩
double calcu(double a, char op, double b)
{ //ִ�ж�Ԫ����
    switch (op)
    {
    case '+':
    {
        return a + b;
    }
    case '-':
    {
        return a - b;
    }
    case '*':
    {
        return a * b;
    }
    case '/':
    {
        if (0 == b)
        {
            exit(-1);
        }
        else
        {
            return a / b; //ע�⣺����и�����Ϊ����ܲ���ȫ
        }
    }
    case '^':
    {
        return pow(a, b);
    }
    default:
    {
        exit(-1);
    }
    }
}

double calcu(char op, double b)
{ //ִ��һԪ����
    switch (op)
    {
    case '!':
    {
        return (double)facI((int)b); //Ŀǰ���н׳ˣ����մ˷�ʽ���
    }
    default:
    {
        exit(-1);
    }
    }
}

double evaluate(char* S, char* RPN) { //�ԣ����޳��׿ո�ģ����ʽS��ֵ����ת��Ϊ�沨��ʽRPN
    Stack<double> opnd; Stack<char> optr; //������ջ�������ջ
    optr.push('\0'); //β�ڱ�'\0'Ҳ��Ϊͷ�ڱ�������ջ
    while (!optr.empty()) { //�������ջ�ǿ�֮ǰ�����������ʽ�и��ַ�
        if (isdigit(*S)) { //����ǰ�ַ�Ϊ����������
            readNumber(S, opnd); append(RPN, opnd.top()); //��������������������RPNĩβ

        }
        else //����ǰ�ַ�Ϊ���������
            switch (priority(optr.top(), *S)) { //������ջ�������֮�����ȼ��ߵͷֱ���
            case '<': //ջ����������ȼ�����ʱ
                optr.push(*S); S++; //�����Ƴ٣���ǰ�������ջ
                break;
            case '=': //���ȼ���ȣ���ǰ�����Ϊ�����Ż���β���ڱ�'\0'��ʱ
                optr.pop(); S++; //�����Ų�������һ���ַ�
                break;
            case '>': { //ջ����������ȼ�����ʱ����ʵʩ��Ӧ�ļ��㣬�������������ջ
                char op = optr.pop(); append(RPN, op); //ջ���������ջ��������RPNĩβ
                if ('!' == op) //������һԪ�����
                    opnd.push(calcu(op, opnd.pop())); //��ȡһ������������������ջ
                else { //������������Ԫ�������
                    double opnd2 = opnd.pop(), opnd1 = opnd.pop(); //ȡ����ǰ������
                    opnd.push(calcu(opnd1, op, opnd2)); //ʵʩ��Ԫ���㣬�����ջ

                }
                break;
            }
            default: exit(-1); //���﷨���󣬲�������ֱ���˳�

            }//switch

    }//while
    return opnd.pop(); //�������������ļ�����
}
int main()
{
    char* rpn = (char*)malloc(sizeof(char) * 100);
    char a[100];
    scanf("%s",a);
    rpn[0] = '\0'; //�沨�����ʽ
    //double value = evaluate(const_cast <char*>("(1+2^3!-4)*(5!-(6-(7-(89-0!))))"), rpn); //��ֵ
    double value = evaluate(a, rpn);
    cout << value << endl;
    //cout << "the rpn is:" << rpn;
    free(rpn);
    rpn = NULL;

    system("pause");
    return 0;
}

