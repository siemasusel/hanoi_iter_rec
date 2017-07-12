#include <iostream>
#include <cstdio>
#include <ctime>
#include <math.h>
#include <stack>

using namespace std;

void show(char s, char d)
{
	//cout << "Move disk from " << s << " to " << d << endl;
}
void hanoi_rec(int n, char sour, char dest, char buff)
{
	if (n == 1)
		show(sour, dest);
	else
	{
		hanoi_rec(n - 1, sour, buff, dest);
		show(sour, dest);
		hanoi_rec(n - 1, buff, dest, sour);
	}
}
void hanoi_rec2(int n, char sour, char dest, char buff)
{
	while (n != 1)
	{
		hanoi_rec2(n - 1, sour, buff, dest);
		show(sour, dest);
		n--;
		swap(sour, buff);
	}
	show(sour, dest);
}
void hanoi_rec3(int n, char sour, char dest, char buff)
{
	if (n != 1)
	{
		n--; swap(dest, buff);
		hanoi_rec3(n, sour, dest, buff);
		swap(dest, buff);
		show(sour, dest);
		swap(sour, buff);
		hanoi_rec3(n, sour, dest, buff);
		n++; swap(sour, buff);
	}
	else
		show(sour, dest);
}

void hanoi_iter1(int n, char sour, char dest, char buff)
{
	int i = 1;
	do
	{
		while (n != 1)
		{
			n--; swap(dest, buff);
			i *= 2;			//i=i*2
		}
		show(sour, dest);
		while ((i != 1) && (i % 2))
		{
			i = i / 2;
			n++; swap(sour, buff);
		}
		if (i == 1)
			goto END;
		i++;
		swap(dest, buff);
		show(sour, dest);
		swap(sour, buff);
	} while (i != 1);
END:
	;
}
stack < int > tohA;
stack < int > tohB;
stack < int > tohC;
//Ckeck from which stack you are allowed to move disk
//You can place disk on stack only if upper disk of new stack is bigger 
void check(stack < int >& x, stack < int >& y, char xx, char yy)
{
	if (x.empty())
	{
		int tmp = y.top();
		y.pop();
		x.push(tmp);
		show(yy, xx);
	}

	else if (y.empty())
	{
		int tmp = x.top();
		x.pop();
		y.push(tmp);
		show(xx, yy);
	}
	else if (x.top() < y.top())
	{
		int tmp = x.top();
		x.pop();
		y.push(tmp);
		show(xx, yy);
	}
	else if (x.top() > y.top())
	{
		int tmp = y.top();
		y.pop();
		x.push(tmp);
		show(yy, xx);
	}
}
void hanoi_iter2(int n, char sour, char dest, char buff)
{
	int moves = pow(2, n) - 1;		//number of moves = 2^n - 1
	for (int i=n; i>0; i--)
		tohA.push(i);
	
	if (n % 2)		//odds
	{
		for (int i = 1; i <= moves; i++)
		{
			if (i % 3 == 1)			//possible move beetween A and C
			{
				check(tohA, tohC, sour, dest);
			}
			else if (i % 3 == 2)	//possible move beetween A and B
			{
				check(tohA, tohB, sour, buff);
			}
			else if (i % 3 == 0)	//possible move beetween B and C
			{
				check(tohB, tohC, buff, dest);
			}
		}
	}
	else			//even
	{
		for (int i = 1; i <= moves; i++)
		{
			if (i % 3 == 1)			//possible move beetween A and B
			{
				check(tohA, tohB, sour, buff);
			}
			else if (i % 3 == 2)	//possible move beetween A and C
			{
				check(tohA, tohC, sour, dest);
			}
			else if (i % 3 == 0)	//possible move beetween B and C
			{
				check(tohB, tohC, buff, dest);
			}
		}
	}
}
int main()
{
	int N;
	clock_t start_R1, start_R2, start_R3, start_I1, start_I2;
	clock_t end_R1, end_R2, end_R3, end_I1, end_I2;

	cout << "Enter the number of disks: "; cin >> N;
	cout << endl << "RECURSION1" << endl;
	start_R1 = clock();
	hanoi_rec(N, 'A', 'C', 'B');
	end_R1 = clock();
	cout << endl << "RECURSION2" << endl;
	start_R2 = clock();
	hanoi_rec2(N, 'A', 'C', 'B');
	end_R2 = clock();
	cout << endl << "RECURSION3" << endl;
	start_R3 = clock();
	hanoi_rec3(N, 'A', 'C', 'B');
	end_R3 = clock();
	cout << endl << "ITERATION1" << endl;
	start_I1 = clock();
	hanoi_iter1(N, 'A', 'C', 'B');
	end_I1 = clock();
	cout << endl << "ITERATION2" << endl;
	start_I2 = clock();
	hanoi_iter2(N, 'A', 'C', 'B');
	end_I2 = clock();

	//---TIMES---
	cout << endl << "RECURSION1 TIME: " << static_cast < double >(end_R1- start_R1) / CLOCKS_PER_SEC <<endl;
	cout << endl << "RECURSION2 TIME: " << static_cast < double >(end_R2 - start_R2) / CLOCKS_PER_SEC << endl;
	cout << endl << "RECURSION3 TIME: " << static_cast < double >(end_R3 - start_R3) / CLOCKS_PER_SEC << endl;
	cout << endl << "ITERATION1 TIME: " << static_cast < double >(end_I1 - start_I1) / CLOCKS_PER_SEC << endl;
	cout << endl << "ITERATION2 TIME: " << static_cast < double >(end_I2 - start_I2) / CLOCKS_PER_SEC << endl;

	system("pause");
	return 0;
}