#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <random>
#include <unistd.h>

using namespace std;

static int counter = 0;
pthread_mutex_t mutex;


void *thread_func(void *arg)
{
        pthread_mutex_lock(&mutex);

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
        pthread_mutex_unlock(&mutex);
        return NULL;
}

int main()
{
        int number, status;
        cout << "\nВведите колличество шаров: ";
        cin >> number;
        int i = 0;

        if (pthread_mutex_init(&mutex, NULL) != 0)
	{
                cout << "\nОшибка инициализации мьютекса\n";
                return 1;
        }

        pthread_t tid[number];
        while(i < number)
	{
                pthread_attr_t attr;
                pthread_attr_init(&attr);
                pthread_create(&tid[i],&attr,thread_func,&i);
                i++;
        }

        sleep(3);

        pthread_mutex_destroy(&mutex);

        cout << endl;
        return 0;
}

