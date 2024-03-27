#include<bits/stdc++.h>
using namespace std;

 
class SegmentTree
{

private:
int size;
  
vector < int >tree;

 
public:
SegmentTree (vector < int >&arr)
  {
    
size = arr.size ();
    
tree.resize (2 * size);
    
build (arr);
  
} 
 
void build (vector < int >&arr)
  {
    
for (int i = 0; i < size; i++)
      {
	
tree[size + i] = arr[i];
    
} 
for (int i = size - 1; i > 0; i--)
      {
	
tree[i] = tree[2 * i] + tree[2 * i + 1];
  
} 
} 
 
void update (int index, int value)
  {
    
index += size;
    
tree[index] = value;
    
while (index > 1)
      {
	
index /= 2;
	
tree[index] = tree[2 * index] + tree[2 * index + 1];
      
}
  
}
  
 
int query (int left, int right)
  {
    
left += size;
    
right += size;
    
int sum = 0;
    
while (left <= right)
      {
	
if (left % 2 == 1)
	  {
	    
sum += tree[left];
	    
left++;
	  
}
	
if (right % 2 == 0)
	  {
	    
sum += tree[right];
	    
right--;
	  
}
	
left /= 2;
	
right /= 2;
      
}
    
return sum;
  
}

};


 
int
main ()
{
  
int n;
  
cout << "Enter the size of the array: ";
  
cin >> n;
  
 
vector < int >arr (n);
  
cout << "Enter the elements of the array: ";
  
for (int i = 0; i < n; i++)
    {
      
cin >> arr[i];
    
} 
 
SegmentTree st (arr);
  
 
int q;
  
cout << "Enter the number of queries: ";
  
cin >> q;
  
 
for (int i = 0; i < q; i++)
    {
      
int type;
      
cout << "Query " << i + 1 << ":\n";
      
cout << "Enter the type of query (1 - Update, 2 - Query): ";
      
cin >> type;
      
 
if (type == 1)
	{
	  
int index, value;
	  
cout << "Enter the index and value to update: ";
	  
cin >> index >> value;
	  
st.update (index, value);
	  
cout << "Updated successfully!\n";
	
}
      else if (type == 2)
	{
	  
int left, right;
	  
cout << "Enter the left and right indices for the query: ";
	  
cin >> left >> right;
	  
int result = st.query (left, right);
	  
cout << "Query result: " << result << endl;
	
}
      else
	{
	  
cout << "Invalid query type! Please try again.\n";
	  
i--;
	
}
      
cout << endl;
    
}
  
 
cout << "Final Array: ";
  
for (int i = 0; i < n; i++)
    {
      
cout << arr[i] << " ";
    
} 
cout << endl;
  
 
return 0;

}



