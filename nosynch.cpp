#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <random>
#include <unistd.h>

using namespace std;

static int counter = 0;

void *thread_func(void *arg)
{
        counter += 1;
        random_device rd;
        mt19937 mersenne(rd());

        srand(mersenne());
        int x = -50 + rand() % 100;
        int y = -50 + rand() % 100;
        cout << "\nНачало [" << counter << "]";
        cout << "\n[" << counter << "]\tx = " << x << "\t  y = " << y;

        while(x > -100 && x < 100 && y > -100 && y < 100)
	{
                x += - 50 + rand() % 100;
                y += - 50 + rand() % 100;
                cout << "\n[" << counter << "]\tx = " << x << "\t  y = " << y;
        }
}


int main()
{
        int number, status;
        cout << "\nВведите колличество шаров: ";
        cin >> number;
        int i = 0;
        pthread_t tid[number];
        while(i < number)
	{
                pthread_attr_t attr;
                pthread_attr_init(&attr);
                pthread_create(&tid[i],&attr,thread_func,&i);
                i++;
        }

        sleep(3);
        cout << endl;
        return 0;
}

