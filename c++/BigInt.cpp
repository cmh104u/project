#include <iostream>
#include <cstdlib>
#include <cstring>
#include "BigInt.h"
using namespace std;
namespace BI
{
BigInt::~BigInt()
{
    delete [] in;
    in = NULL;
}
BigInt::BigInt()
{
    in = NULL;
    size = 0;
    oflag = 0;
}
BigInt::BigInt(string s)
{
    size = s.length();
    if(s[0]=='-')
    {
        oflag = 1;
        for(int i=1; i<size; i++)
            s[i-1]=s[i];
        size = size -1;
    }
    else oflag = 0;
    in = new int[size+11];
    for(int i=0; i<size; i++)
        in[i]=s[size-1-i]-'0';
}
BigInt::BigInt(long long int inint)
{
    if(inint<0)
    {
        oflag = 1;
        inint = abs(inint);
    }
    else    oflag = 0;
    int count(0);
    int tmp[100];
    while(inint!=0)
    {
        tmp[count++] = inint%10;
        inint = inint/10;
    }
    size = count;
    in = new int[size];
    for(int i=0; i<size; i++)
        in[i]=tmp[i];
}
BigInt::BigInt(const BigInt& c)
{
    size = c.size;
    oflag = c.oflag;
    in = new int[size];
    for(int i=0; i<size; i++)
        in[i]=c.in[i];
}
ostream& operator <<(ostream& outputStream,const  BigInt& amount)
{
    int zeroFlag(0);
    if(amount.oflag==1)
        outputStream << '-';
    for(int i=0; i<amount.size; i++)
    {
        if(amount.in[amount.size-1-i]!=0)zeroFlag=1;
        if(zeroFlag==1)
            outputStream << amount.in[amount.size-1-i];
    }
    if(zeroFlag==0)outputStream << "0";
    return outputStream;
}
BigInt& BigInt::operator =(const BigInt& amount)
{
    if(size!=amount.size)
    {
        delete [] in;
        in = new int[amount.size];
    }
    oflag = amount.oflag;
    size = amount.size;
    for(int i=0; i<size; i++)
        in[i] = amount.in[i];
    return *this;
}
BigInt operator +(BigInt amount1,BigInt amount2)
{
    BigInt ans;
    if(amount1.oflag==0&&amount2.oflag==1)
    {
        amount2.oflag = 0;
        ans = amount1-amount2;
    }
    else if(amount1.oflag==1&&amount2.oflag==0)
    {
        amount1.oflag = 0;
        ans = amount2-amount1;
    }
    else
    {
        if(amount1.oflag==1&&amount2.oflag==1)
            ans.oflag = 1;
        if(amount1.oflag==0&&amount2.oflag==0)
            ans.oflag = 0;
        int i;
        ans.size = (amount1.size>amount2.size)?amount1.size:amount2.size;
        ans.size = ans.size + 1;
        ans.in = new int[ans.size];
        for(i=0; i<ans.size; i++)
            ans.in[i]=0;
        for(i=0; i<ans.size-1; i++)
        {
            if(i<=amount1.size-1&&i<=amount2.size-1)
                ans.in[i]=ans.in[i]+amount1.in[i]+amount2.in[i];
            else if(i>amount1.size-1)
                ans.in[i]=ans.in[i]+amount2.in[i];
            else if(i>amount2.size-1)
                ans.in[i]=ans.in[i]+amount1.in[i];
            if(ans.in[i]>=10)
            {
                ans.in[i]=ans.in[i]-10;
                ans.in[i+1]=ans.in[i+1]+1;
            }
        }
        ans.size = ans.changeSize();
    }
    return ans;
}
BigInt operator -(BigInt amount1,BigInt amount2)
{
    BigInt ans;
    ans.oflag = 0;
    if(amount1.oflag==1&&amount2.oflag==1)
    {
        amount1.oflag = amount2.oflag = 0;
        ans = amount2-amount1;
    }
    else if(amount1.oflag==0&&amount2.oflag==1)
    {
        amount2.oflag = 0;
        ans = amount1+amount2;
    }
    else if(amount1.oflag==1&&amount2.oflag==0)
    {
        amount1.oflag = 0;
        ans = amount2+amount1;
        ans.oflag = 1;
    }
    else
    {
        int i;
        ans.size = (amount1.size>amount2.size)?amount1.size:amount2.size;
        if(amount1.size<amount2.size)ans.oflag=1;
        if(amount1.size==amount2.size)
        {
            for(i=ans.size-1; i>=0; i--)
            {
                if(amount1.in[i]==amount2.in[i])continue;
                ans.oflag=(amount1.in[i]>amount2.in[i])?0:1;
                break;
            }
        }
        ans.in = new int[ans.size];
        for(i=0; i<ans.size; i++)
            ans.in[i] = 0;
        for(i=0; i<ans.size; i++)
        {
            if(ans.oflag==1)
            {
                if(i<amount1.size&&i<amount2.size)
                    ans.in[i]=amount2.in[i]-amount1.in[i];
                else if(i>=amount1.size)
                    ans.in[i]=amount2.in[i];
                if(ans.in[i]<0)
                {
                    ans.in[i]=ans.in[i]+10;
                    amount2.in[i+1]=amount2.in[i+1]-1;
                }
            }
            else if(ans.oflag==0)
            {
                if(i<amount1.size&&i<amount2.size)
                    ans.in[i]=amount1.in[i]-amount2.in[i];
                else if(i>=amount2.size)
                    ans.in[i]=amount1.in[i];
                if(ans.in[i]<0)
                {
                    ans.in[i]=ans.in[i]+10;
                    amount1.in[i+1]=amount1.in[i+1]-1;
                }
            }
        }
        ans.size = ans.changeSize();
    }
    return ans;
}
BigInt operator *(BigInt amount1,BigInt amount2)
{
    BigInt ans,tmp;
    int i,j;
    if((amount1.oflag==1&&amount2.oflag==1)||(amount1.oflag==0&&amount2.oflag==0))
        ans.oflag = 0;
    else
        ans.oflag = 1;
    amount1.oflag=amount2.oflag=0;
    ans.size = 2*((amount1.size>amount2.size)?amount1.size:amount2.size);
    ans.in = new int[ans.size];
    for(i=0; i<ans.size; i++)
        ans.in[i] = 0;
    for(i=0; i<amount2.size; i++)
    {
        for(j=0; j<amount1.size; j++)
            ans.in[j+i]=ans.in[j+i]+amount2.in[i]*amount1.in[j];
    }
    for(i=0; i<ans.size; i++)
    {
        while(ans.in[i]>=10)
        {
            ans.in[i]=ans.in[i]-10;
            ans.in[i+1]++;
        }
    }
    ans.size = ans.changeSize();
    return ans;
}
BigInt BigInt::factorial()
{
    if(oflag==1)return 0;
    BigInt ans;
    ans.size = size;
    ans.oflag = oflag;
    ans.in = new int[ans.size];
    for(int i=0; i<ans.size; i++)
        ans.in[i]=in[i];
    BigInt tmp(ans);
    while(1)
    {
        tmp = tmp-1;
        ans = ans*tmp;
        if(tmp.size==1 && tmp.in[0]==1)
            break;
    }
    ans.size = ans.changeSize();
    return ans;
}
int BigInt::changeSize()
{
    int chaSize(0),zeroFlag(0);
    for(int i=0; i<size; i++)
    {
        if(in[size-1-i]!=0)zeroFlag=1;
        if(zeroFlag==1)
            chaSize++;
    }
    if(zeroFlag==0)chaSize=1;
    return chaSize;
}
BigInt operator /(BigInt amount1,BigInt amount2)
{
    if(amount1!=amount2)
    {
        BigInt flag,ans(0),tmp1(amount1);
        BigInt count;
        int i;
        count.in = new int[amount1.size];
        for(i=0; i<amount1.size; i++)
            amount1.in[i]=0;
        int n=amount1.size;
        tmp1.oflag=0;
        while(n>=0)
        {
            BigInt tmp2(amount2);
            tmp2.oflag=0;
            for(i=0; i<n; i++)
                tmp2=tmp2*10;
            flag = tmp1 - tmp2;
            if(flag.oflag==0)
            {
                count = 0;
                while(1)
                {
                    tmp1 = tmp1 - tmp2;
                    if(tmp1.oflag==0)
                        count=count+1;
                    else
                    {
                        tmp1 = tmp1 + tmp2;
                        break;
                    }
                }
                for(i=0; i<n; i++)
                    count = count*10;
                ans = ans + count;
            }
            n--;
        }
        if((amount1.oflag==1&&amount2.oflag==1)||(amount1.oflag==0&&amount2.oflag==0))
            ans.oflag = 0;
        else
            ans.oflag = 1;
        ans.size = ans.changeSize();
        return ans;
    }
    else
        return 1;
}
int BigInt::getOflag()
{
    return oflag;
}
void BigInt::changeOflag(int newOflag)
{
    oflag = oflag;
}
BigInt operator %(BigInt amount1,BigInt amount2)
{
    BigInt ans;
    ans = amount1-(amount2*(amount1 / amount2));
    ans.oflag = 0;
    return ans;
}
bool operator !=(BigInt amount1,BigInt amount2)
{
    int i;
    if(amount1.oflag!=amount2.oflag)return 1;
    else if(amount1.size!=amount2.size)return 1;
    else
    {
        for(i=0; i<amount1.size; i++)
        {
            if(amount1.in[i]==amount2.in[i])continue;
            else return 1;
        }
    }
    return 0;
}

}
