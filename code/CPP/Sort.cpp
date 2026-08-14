#include <iostream>
#include <vector>
using namespace std;


void bubble_sort(int a[], int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void selection_sort(int a[],int n)
{
   for(int i=0;i<n-1;i++)
   {
    int mini=i;
    for(int j=i+1;j<n;j++)
    {
        if(a[j]<a[mini])mini=j;
    }
    swap(a[i],a[mini]);
   }
}

void insertion_sort(int a[],int n)
{
for(int i=1;i<n;i++){
    int j=i-1;
    int key=a[i];
    while(j>=0 && a[j]>key)
    {
        a[j+1]=a[j];j--;
    }
    a[j+1]=key;
    }
}
void merge(int a[],int low, int mid, int high)
{
    vector<int> t;
    int i=low,j=mid+1;
    while(i<=mid && j<=high)
    {
        if(a[i]>a[j]){t.push_back(a[j]);j++;}
        else {t.push_back(a[i]);i++;
        
    }
    while(i<=mid)
    {
        t.push_back(a[i]);i++;
    }
    while(j<=high)t.push_back(a[j]);j++;
    for(int k=0;k<t.size();k++)
    {
        a[low+k]=t[k];
    }
}}

int partition(int a[],int low, int high)
{
    int pivot=a[high];
    int i= low-1;
    for(int j=low;j<high;j++)
    {
        if(a[j]<pivot){i++;swap(a[j],a[i]);}

    }
    swap(a[i+1],a[high]);

    return i+1;
}
void quick_sort(int a[],int low, int high)
{
    if(low>=high)return;

    int p=partition(a,low,high);
    quick_sort(a,low,p-1);
    quick_sort(a,p+1,high);
}

void merge_sort(int a[],int low, int high)
{
    if(low>=high)return;
    int mid=low+(high-low)/2;
    merge_sort(a,low,mid);
    merge_sort(a,mid+1,high);
    merge(a,low,mid,high);
}
int main()
{
    int n;

    cout << "enter the array size" << endl;
    cin >> n;

    int a[n];

    cout << "enter the array" << endl;

    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    cout << "Enter the sorting algo to choose from:\n"
         << "1. bubble(default)\n"
         << "2. Selection\n"
         << "3. Insertion\n"
         << "4. MergeSort\n"
         << "5. QuickSort\n";

    int choice = 1;
    cin>>choice;

    switch(choice)
    {
        case 1:
            cout << "executing bubble sort" << endl;
            bubble_sort(a, n);
            break;

        case 2:
            cout << "executing selection sort" << endl;
            selection_sort(a,n);
            break;

        case 3:
            cout << "executing Insertion sort" << endl;
            insertion_sort(a,n);
            break;

        case 4:
            cout << "executing merge sort" << endl;
            merge_sort(a,0,n-1);
            break;

        case 5:
            cout << "executing quick sort" << endl;
            quick_sort(a,0,n-1);
            break;
        default:
            cout << "wrong option, executing default algo\n" << endl;
            bubble_sort(a, n);break;
    }

    cout << "array after sorting" << endl;

    for(int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << endl;

    cout << "Thanks for using our service" << endl;

    return 0;
}


