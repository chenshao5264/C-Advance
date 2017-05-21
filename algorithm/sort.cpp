#include <iostream>

#include <vector>

#include <sys/time.h>
#include <unistd.h>

using namespace std;

void print(const vector<int>& array)
{
    for (int i = 0; i < array.size(); ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

// 合并有序数组
void MergeArray(vector<int>& array, int first, int mid, int last, vector<int>& newArray)
{
    newArray.clear();

    int i = first;
    int j = mid + 1;
    while ( i <= mid && j <= last)
    {
        if (array[i] < array[j])
        {
            newArray.push_back(array[i++]);
        }
        else
        {
            newArray.push_back(array[j++]);
        }
    }

    while (i <= mid)
    {
        newArray.push_back(array[i++]);
    }

    while (j <= last)
    {
        newArray.push_back(array[j++]);
    }

    for (int k = 0; k < newArray.size(); ++k)
    {
        array[first + k] = newArray[k];
    }
}

void MergeSort(vector<int>& array, int first, int last, vector<int>& newArray)
{
    if (first < last)
    {
        int mid = (first + last) / 2;
        MergeSort(array, first, mid, newArray);
        MergeSort(array, mid + 1, last, newArray);
        MergeArray(array, first, mid, last, newArray);
    }
}

// 归并排序
void MergeSort(vector<int>& array)
{
    vector<int> newArray;
    MergeSort(array, 0, array.size() - 1, newArray);
    array = newArray;
}

// 希尔插入排序
void ShellInsertIndex(vector<int>& array)
{
    int op = -1;
    int insertIndex = -1;
    int grap = array.size() / 2;

    while (grap > 0)
    {
        for (int k = grap; k < array.size(); ++k)
        {
            op = array[k];
            insertIndex = -1;
            for (int i = k - grap; i >= 0; i -= grap)
            {
                if (op < array[i])
                {
                    array[i + grap] = array[i];
                    insertIndex = i;
                }
                else
                {
                    break; //前面已排好序，所以可以直接放弃比较
                }
            }

            if (insertIndex != -1)
            {
                array[insertIndex] = op;
            }
        }
        grap /= 2;
    }
}

// 二分查找
// 时间复杂度 O(log(n))
int SearchBinaryInsertIndex(vector<int>& array, int right, int op)
{
    int left = 0;
    while (left <= right)
    {
        int middle = (left + right) / 2;

        if (op < array[middle])
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
    }
    return left;
}

// 二分查找排序
// 时间复杂度O(n*log(n)) + O(n^2 / 2) = O(n^2)
void BinaryInsertSort(vector<int>& array)
{
    int op = -1;
    int insertIndex = -1;
    for (int k = 1; k < array.size(); ++k)
    {
        op = array[k];
        insertIndex = SearchBinaryInsertIndex(array, k - 1, op);

        if (insertIndex != k)
        {
            for (int i = k; i > insertIndex; --i)
            {
                array[i] = array[i - 1];
            }
            array[insertIndex] = op;
        }
    }
}

// 直接插入排序
// 时间复杂度 O(n^2)
void DirectIsertSort(vector<int>& array)
{
    int op = -1;
    int insertIndex = -1;
    for (int k = 1; k < array.size(); ++k)
    {
        op = array[k];
        insertIndex = -1;
        for (int i = k - 1; i >= 0; --i)
        {
            if (op < array[i])
            {
                array[i + 1] = array[i];
                insertIndex = i;
            }
            else
            {
                break; //前面已排好序，所以可以直接放弃比较
            }
        }

        if (insertIndex != -1)
        {
            array[insertIndex] = op;
        }
    }

}

// 选择排序
// 时间复杂度 O(n^2)
void SelectSort(vector<int>& array)
{
    int min = -1;
    int candidateIndex = -1;

    for (int k = 0; k < array.size() - 1; ++k)
    {
        min = array[k];
        candidateIndex = -1;
        for (int i = k + 1; i < array.size(); ++i)
        {
            if (array[i] < min)
            {
                candidateIndex = i;
                min = array[i];
            }
        }
        if (candidateIndex != -1 && array[k] != min)
        {
            std::swap(array[k], array[candidateIndex]);
        }
    }
}

// 冒泡排序
// 时间复杂度 O(n^2)
void BubbleSort(vector<int>& array)
{
	int len = array.size();
    for (int k = 0; k < len - 1; ++k)
    {
        for (int i = 1; i < len - k; ++i)
        {
            if (array[i] < array[i - 1])
            {
                std::swap(array[i], array[i - 1]);
            }
        }
    }
}


void QuickSort(vector<int>& array, int first, int last)
{
    if (first >= last)
    {
        return;
    }
    int base = array[first];
    int i = first;
    int j = last;
    while (i < j)
    {
        while (array[j] >= base && i < j)
        {
            --j;
        }
        while (array[i] <= base && i < j)
        {
            ++i;
        }

        if (array[j] != array[i])
        {
            std::swap(array[j], array[i]);
        }
    }

    if (array[first] != array[i])
    {
        std::swap(array[first], array[i]);
    }


    QuickSort(array, first, i - 1);
    QuickSort(array, i + 1, last);
}

// 快速排序
// 时间复杂度O(Nlog(N))
void QuickSort(vector<int>& array)
{
    QuickSort(array, 0, array.size() - 1);
}

// 调整堆为大顶堆
void HeapAdjuest(vector<int>& array, int start, int len)
{
    int parent = array[start];
    int maxChild = 0;

    while (2 * start < len)
    {
        maxChild = 2 * start + 1;
        if (maxChild < len && array[maxChild] < array[maxChild + 1])
        {
            ++maxChild;
        }

        if (parent > array[maxChild])
        {
            break;
        }

        array[start] = array[maxChild];
        start = maxChild;
    }
    if (array[start] != parent)
    {
        array[start] = parent;
    }
}

// 堆排序
// 时间复杂度O(Nlog(N))
// 升序，构建大顶堆
// 降序，构建小顶堆
void HeapSort(vector<int>& array)
{
    int len = array.size();
    for (int i = len / 2 - 1; i >= 0; --i)
    {
        HeapAdjuest(array, i, len);
    }

    for (int i = len - 1; i > 0; --i)
    {
        std::swap(array[0], array[i]);
        HeapAdjuest(array, 0, i - 1);
    }

}

long getTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}


int main()
{
    std::cout << "Hello, World!" << std::endl;

//    vector<int> arr = {20 ,70, 60, 12, 40, 30, 8, 10};
//    HeapSort(arr);
//    print(arr);


    vector<int> arr;

    for (int i = 0; i < 200000; ++i)
    {
        arr.push_back(rand() % 10000);
    }

    vector<int> arr1(arr);
    vector<int> arr2(arr);
    vector<int> arr3(arr);
    vector<int> arr4(arr);
    vector<int> arr5(arr);
    vector<int> arr6(arr);
    vector<int> arr7(arr);

//    auto time1 = getTime();
//    BubbleSort(arr);                // 2800 ms
//    auto time2 = getTime();
//    cout << time2 - time1 << endl;
//
//    SelectSort(arr1);               // 650 ms
//    auto time3 = getTime();
//    cout << time3 - time2 << endl;
//
//    DirectIsertSort(arr2);          // 480 ms
//    auto time4 = getTime();
//    cout << time4 - time3 << endl;
//
//    BinaryInsertSort(arr3);         // 380 ms
//    auto time5 = getTime();
//    cout << time5 - time4 << endl;

    auto time5 = getTime();
    ShellInsertIndex(arr4);         // 6 ms
    auto time6 = getTime();
    cout << time6 - time5 << endl;

    MergeSort(arr5);                // 12 ms
    auto time7 = getTime();
    cout << time7 - time6 << endl;

    QuickSort(arr6);                 // 3 ms
    auto time8 = getTime();
    cout << time8 - time7 << endl;

    HeapSort(arr7);                 // 5ms
    auto time9 = getTime();
    cout << time9 - time8 << endl;

    return 0;
}
