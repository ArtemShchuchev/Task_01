#include <iostream> // консоль - cout
#include <fstream>  // работа с файлами

void memoryFree(int**&, const unsigned int);

const std::string in_file = "in.txt", out_file = "out.txt";

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");   // задаём русский текст
    std::system("cls");

    const unsigned int MAS_NUM = 2; // кол-во массивов
    unsigned int m_size[MAS_NUM];   // размеры массивов
    int** massiv(nullptr);          // указатель на 2х массив указателей
    
    std::ifstream file(in_file);
    if (file.is_open())
    {
        massiv = new int* [MAS_NUM]();
        for (unsigned int m = 0; m < MAS_NUM; ++m)
        {
            if (file >> m_size[m])
            {
                massiv[m] = new int [m_size[m]];
                for (unsigned int i = 0; i < m_size[m]; ++i)
                {
                    if (!(file >> massiv[m][i]))
                    {
                        std::cout << "Ошибка! Файл повреждён!" << std::endl;
                        return 2;
                    }
                }
            }
        }

        file.close();
    }
    else
    {
        std::cout << "Не удалось открыть файл: " << in_file << std::endl;
        return 1;
    }

    std::ofstream file_wr(out_file);
    if (file_wr.is_open())
    {
        unsigned int m = MAS_NUM, j;
        do
        {
            --m;
            file_wr << m_size[m] << std::endl;

            j = (m == 0) ? 1 : m_size[m] - 1; // начальное условие для индекса массива

            unsigned int size = m_size[m];
            do
            {
                if (j >= m_size[m]) j = 0;
                file_wr << massiv[m][j] << " ";
                ++j;
            } while (--size);
            file_wr << std::endl;
        } while (m);

        file_wr.close();
    }
    else
    {
        std::cout << "Не удалось соранить файл: " << out_file << std::endl;
        return 3;
    }

    memoryFree(massiv, MAS_NUM);
    return 0;
}



void memoryFree(int**& memoryPtr, const unsigned int num)
{
    if (!memoryPtr) return; // нечего удалять
    //std::cout << "Освобождаю память...\n";
    for (unsigned int i = 0; i < num; ++i)
    {
        delete[] memoryPtr[i];
    }
    delete[] memoryPtr;
    memoryPtr = nullptr;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
