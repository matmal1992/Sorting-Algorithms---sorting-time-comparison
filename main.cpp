#include <iostream>
#include <time.h>
#include <cstdlib>
#include <windows.h>

using namespace std;

void createArrays(int tabOne[], int tabTwo[], int tabThree[], int tabFour[], int tabFive[], int tabSize)
    {
        srand(time(NULL));

        for(int i = 0; i < tabSize; i++)
        {
            tabOne[i] = rand()%1000 + 1;
            tabTwo[i] = tabOne[i];
            tabThree[i] = tabOne[i];
            tabFour[i] = tabOne[i];
            tabFive[i] = tabOne[i];
        }
    }

bool tabIsSorted(int tab[], int tabSize)
{
    bool sorted = true;

    for(int i = 0; i < tabSize - 1; i++)
    {
        if(tab[i] > tab[i+1])
            sorted = false;
    }

    return sorted;
}

void quicksort(int tab[], int left, int right)
{
    int pivot = tab[(left + right) / 2];
    int p{}, q{}, buffor{};

    p = left;
    q = right;

    do
    {
        while(tab[p] < pivot) {p++;}

        while(tab[q] > pivot) {q--;}

        if(p <= q)
        {
            buffor = tab[p];
            tab[p] = tab[q];
            tab[q] = buffor;
            p++;
            q--;
        }
    } while(p <= q);

    if(q > left)
        quicksort(tab, left, q);
    if(p < right)
        quicksort(tab, p, right);
}

void merging(int tab[], int first, int middle, int last)
{
    int *tab_buf = new int[(last - first + 1)];
    int i = first, j = middle + 1, k = 0;

    while (i <= middle && j <= last)
    {
        if (tab[j] < tab[i])
        {
            tab_buf[k] = tab[j];
            j++;
        }
        else
        {
            tab_buf[k] = tab[i];
            i++;
        }
        k++;
    }

    if (i <= middle)
    {
        while (i <= middle)
        {
            tab_buf[k] = tab[i];
            i++;
            k++;
        }
    }
    else
    {
        while (j <= last)
        {
            tab_buf[k] = tab[j];
            j++;
            k++;
        }
    }

    for(i = 0; i <= last - first; i++)
    {
        tab[first + i] = tab_buf[i];
    }

        delete[] tab_buf;
}

void mergeSort(int tab[], int first, int last)
{
    int middle;

    if (first != last)
    {
        middle = (first + last)/2;
        mergeSort(tab, first, middle);
        mergeSort(tab, middle+1, last);
        merging(tab, first, middle, last);
    }
}

void bubbleSort(int tab[], int tabSize)
{
    clock_t start{}, stop{};
    double performTime{};
    int buffer{};
    start = clock();

    for(int j = 0; j < tabSize; j++)
    {
        for(int i = 0; i < tabSize; i++)
        {
            if(tab[i] >= tab[i+1])
            {
                buffer = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = buffer;
            }
        }
    }

    stop = clock();
    performTime = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "Is the array sorted? " << tabIsSorted(tab, tabSize) << endl << endl;
    cout << "Time of sorting: " << performTime << endl << endl;
}

void insertSort(int tab[], int tabSize)
{
    clock_t start{}, stop{};
    double performTime{};
    int insertedElement{};
    int j{};

    start = clock();

    for(int i = 1; i < tabSize; i++)
    {
        insertedElement = tab[i];
        j = i - 1;

        while(j >= 0 && tab[j] > insertedElement)
        {
            tab[j+1] = tab[j];
            j--;
        }
        tab[j+1] = insertedElement;
    }

    stop = clock();
    performTime = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "Is the array sorted? " << tabIsSorted(tab, tabSize) << endl;
    cout << "Time of sorting: " << performTime << endl << endl;
}

void selecSort(int tab[],int tabSize)
{
    clock_t start{}, stop{};
    double performTime{};
    int indexHolder{};

    start = clock();

    for(int i = 0; i < tabSize - 1; i++)
    {
        indexHolder = i;

        for(int j = i + 1; j < tabSize; j++)
        {
            if(tab[j] < tab[indexHolder])
                indexHolder = j;
        }

        swap(tab[i], tab[indexHolder]);
    }

    stop = clock();
    performTime = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "Is the array sorted? " << tabIsSorted(tab, tabSize) << endl;
    cout << "Time of sorting: " << performTime << endl << endl;
}

int main()
{
    clock_t start{}, stop{};
    double performTime{};
    int tabSize{};
    cout << boolalpha;

    cout << "I'm going to create 5 identical arrays." << endl;
    cout << "Provide number of elements in a single array: ";
    cin >> tabSize;
    cout << endl << endl;

    int *tabOne = new int [tabSize];
    int *tabTwo = new int [tabSize];
    int *tabThree = new int [tabSize];
    int *tabFour = new int [tabSize];
    int *tabFive = new int [tabSize];

    createArrays(tabOne, tabTwo, tabThree, tabFour, tabFive, tabSize);

    cout << "========= BUBBLE SORT =========" << endl;
    bubbleSort(tabOne, tabSize);

    cout << "========= INSERTION SORT =========" << endl;
    insertSort(tabTwo, tabSize);

    cout << "========= SELECTION SORT =========" << endl;
    selecSort(tabThree, tabSize);

    cout << "========= QUICK SORT =========" << endl;
    start = clock();
    quicksort(tabFour, 0, tabSize - 1);
    stop = clock();
    performTime = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "Is the array sorted? " << tabIsSorted(tabFour, tabSize) << endl;
    cout << "Time of sorting: " << performTime << endl << endl;


    cout << "========= MERGE SORT =========" << endl;
    start = clock();
    mergeSort(tabFive, 0, tabSize - 1);
    stop = clock();
    performTime = (double)(stop - start) / CLOCKS_PER_SEC;
    cout << "Is the array sorted? " << tabIsSorted(tabFive, tabSize) << endl;
    cout << "Time of sorting: " << performTime << endl << endl;

    delete[] tabOne;
    delete[] tabTwo;
    delete[] tabThree;
    delete[] tabFour;
    delete[] tabFive;

    return 0;
}
