#include <iostream>
#include <vector>
using namespace std;

void BubbleSort(vector<int>&);   //冒泡排序，稳定，O(n*n)--O(n),O(n*n)
void InsertionSort(vector<int>&);   //插入排序，稳定，O(n*n)--O(n),O(n*n)
void Shellsort(vector<int>&);   //希尔排序，不稳定，O(n*n)--O(n)
void SelectionSort(vector<int>&);   //选择排序，不稳定，O(n*n)
void HeapSort(vector<int>&); void Siftdown(vector<int>&,int,int);   //堆排序，不稳定，O(nlogn)--O(n),O(nlogn)
void MergeSort(vector<int>&,vector<int>&,int,int);   //归并排序，稳定，O(nlogn)
void QuickSort(vector<int>&,int,int); void Partitiion(vector<int>&,int,int);   //快速排序，不稳定，O(n*n)--O(nlogn),O(nlogn)

int main()
{
    vector<int> v;
    int m;
    char C;
    while(cin>>m)
    {
        v.push_back(m);
    }
    int N=v.size();
    vector<int> arr(N);
    cin.clear();
    cin>>C;
    switch(C)
    {
        case 'a': BubbleSort(v); cout<<"BubbleSort:"<<endl; break;
        case 'b': InsertionSort(v); cout<<"InsertionSort:"<<endl; break;
        case 'c': Shellsort(v); cout<<"ShellSort:"<<endl; break;
        case 'd': SelectionSort(v); cout<<"SelectionSort:"<<endl; break;
        case 'e': HeapSort(v); cout<<"HeapSort:"<<endl; break;
        case 'f': MergeSort(v,arr,0,N); cout<<"MergeSort:"<<endl; break;
        case 'g': QuickSort(v,0,N-1); cout<<"QuickSort:"<<endl; break;
        default: break;
    }
    for(int x:v)
    {
        cout<<x<<' ';
    }
    cout<<endl;
    return 0;
}

void BubbleSort(vector<int>& k)
{
    int n=k.size();
    for(int i=0;i<n;i++)
    {
        bool swapped=false;
        for(int j=n-2;j>=0;j--)
        {
            if(k[j]>k[j+1])
            {
                swap(k[j],k[j+1]);
                swapped=true;
            }
        }
        if(!swapped) break;
    }
}

void InsertionSort(vector<int>& k)
{
    int n=k.size();
    for(int i=1;i<n;i++)
    {
        int j=i-1;
        int temp=k[i];
        while(j>=0&&k[j]>temp)
        {
            k[j+1]=k[j];
            j--;
        }
        k[j+1]=temp;
    }
}

void Shellsort(vector<int>& k)
{
    int n=k.size();
    for(int gap=n/2;gap>0;gap/=2)
    {
        for(int i=gap;i<n;i++)
        {
            int temp=k[i];
            int j=i;
            while(j>=gap&&k[j-gap]>temp)
            {
                k[j]=k[j-gap];
                j-=gap;
            }
            k[j]=temp;
        }
    }
}

void SelectionSort(vector<int>& k)
{
    int n=k.size();
    for(int i=0;i<n;i++)
    {
        int min=i;
        for(int j=i+1;j<n;j++)
        {
            if(k[j]<k[min])
            min=j;
        }
        swap(k[i],k[min]);
    }
}

void Siftdown(vector<int>& k,int i,int n)
{
    int temp,j;
    temp=k[i];
    while((j=i*2+1)<n)
    {
        if(j<n-1&&k[j]<k[j+1]) j++;
        if(temp<k[j])
        {
            k[i]=k[j];
            k[j]=temp;
            i=j;
        }
        else break;
    }
}

void HeapSort(vector<int>& k)
{  
    int n=k.size();
    for(int i=(n-2)/2;i>=0;i--) Siftdown(k,i,n);
    for(int m=n-1;m>0;m--)
    {
        int temp=k[0];
        k[0]=k[m];
        k[m]=temp;
        Siftdown(k,0,m);
    }
}

void MergeSort(vector<int>& k,vector<int>& arr,int l,int r)
{
    if(r-l-1<=0) return;
    int m=(l+r)/2;
    MergeSort(k,arr,l,m);
    MergeSort(k,arr,m,r);
    int x=l,y=m,z=l;
    while(x<m&&y<r)
    {
        if(k[x]<k[y]) arr[z++]=k[x++];
        else arr[z++]=k[y++];
    }
    while(x<m) arr[z++]=k[x++];
    while(y<r) arr[z++]=k[y++];
    for(int j=l;j<r;j++) k[j]=arr[j];
}

int partition(vector<int>& k,int l,int r)
{
    int p=k[r];
    int i=l-1;
    for(int j=l;j<r;j++)
    {
        if(k[j]<=p)
        {
            i++;
            int temp=k[i];
            k[i]=k[j];
            k[j]=temp;
        }
    }
    int tempp=k[i+1];
    k[i+1]=k[r];
    k[r]=tempp;
    return i+1;
}

void QuickSort(vector<int>& k,int l,int r)
{
    if(l<r)
    {
        int pp=partition(k,l,r);
        QuickSort(k,l,pp-1);
        QuickSort(k,pp+1,r);
    }
}