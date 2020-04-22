#include <iostream>
#include <string>
#include <fstream>

int solve(int N, int W, const int* weights, const int* purchases)
{
    int** A = new int*[N + 1];
    for (int i = 0; i <= N; i++)
        A[i] = new int[W + 1];

    for(int i = 0;i <= W; i++)
        A[0][i] = 0;

    for(int i = 1; i <= N; i++)
    {
        for(int j = 0; j <= W; j++)
        {
            A[i][j] = A[i - 1][j];
            if (j >= weights[i - 1] && ( A[i - 1][j - weights[i - 1]] + purchases[i - 1] > A[i][j]))
                A[i][j] = A[i - 1][j - weights[i - 1]] + purchases[i - 1];
        }
    }

    int result = A[N][W];

    for (int i = 0; i <= N; i++)
        delete[] A[i];
    delete[] A;

    return result;
}

int main()
{
    std::string t;
    std::string p;

    int N, //number of things
    W; //max weight

    int* weights;
    int* purchases;

    std::ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        fin >> N >> W;
        weights = new int[N];
        purchases = new int[N];

        int tmp;
        for (int i = 0; i < N; i++)
        {
            fin >> tmp;
            weights[i] = tmp;
        }

        for (int i = 0; i < N; i++)
        {
            fin >> tmp;
            purchases[i] = tmp;
        }
        fin.close();

        int result = solve(N, W, weights, purchases);

        std::fstream fout;
        fout.open("output.txt", std::ios::out);
        fout << result;
        fout.close();
    }

    return 0;
}
