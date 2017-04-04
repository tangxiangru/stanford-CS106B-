#include <stdio.h>
void hanoi(int n,char A,char B,char C);
void move(char x,char y);

int main()
{
  int n;
  printf("input number\n" );
  scanf("%d",&n );
  hanoi(n,'A','B','C');
  return 0;
}
void hanoi(int n,char A,char B,char C)
{
  if(n==1)
    move(A,C);
  else{
    hanoi(n-1,A,B,C);
    move(A,C);
    hanoi(n-1,B,A,C);
  }
}
void move(char x,char y)
{
  printf("%c-------->%c\n",x,y);
}
