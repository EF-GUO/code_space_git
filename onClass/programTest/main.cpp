#include <iostream>

void isTri(int a,int b,int c){
    if ((a + b <= c) || (a + c <= b) || (b + c <= a))
    {
        printf("不能构成三角形");
    }
    else
    {
        if ((a==b) || (b==c) || (a==c))
        {
            if ((a==b) && (b==c))
            {
                printf("等边三角形");
            }
            else
            {
                printf("等腰三角形");
            }
        }
        printf("一般三角形");       
    }
}



int main()
{
    using namespace std;



}



