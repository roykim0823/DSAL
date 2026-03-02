## Pigeonhole Sort
Pigeonhole sorting is a sorting algorithm that is suitable for sorting lists of
elements where the number of elements and the number of possible key values are
approximately the same.
It requires O(n + Range) time where n is number of elements in input array and
‘Range’ is number of possible values in array.

### Working of Algorithm
1. Find minimum and maximum values in array.
   Let the minimum and maximum values be ‘min’ and ‘max’ respectively.
   Also find range as ‘max-min-1’.
2. Set up an array of initially empty “pigeonholes” the same size as of the range.
3. Visit each element of the array and then put each element in its pigeonhole.
   An element arr[i] is put in hole at index arr[i] – min.
4. Start the loop all over the pigeonhole array in order and put the elements
   from non- empty holes back into the original array.

### Comparison with Counting Sort
It is similar to counting sort, but differs in that it “moves items twice:
once to the bucket array and again to the final destination “.

### Coveat
Pigeonhole sort has limited use as requirements are rarely met. For arrays
where range is much larger than n, bucket sort is a generalization that is
more efficient in space and time.

## Bucket Sort
Bucket sort is mainly useful when input is uniformly distributed over a range. For example, consider the following problem.
Sort a large set of floating point numbers which are in range from 0.0 to 1.0 and are uniformly distributed across the range. How do we sort the numbers efficiently?

A simple way is to apply a comparison based sorting algorithm. The lower bound for Comparison based sorting algorithm (Merge Sort, Heap Sort, Quick-Sort .. etc) is Ω(n Log n), i.e., they cannot do better than nLogn.
Can we sort the array in linear time? Counting sort can not be applied here as we use keys as index in counting sort. Here keys are floating point numbers. 
The idea is to use bucket sort. 

Following is bucket algorithm.
```
bucketSort(arr[], n)
1) Create n empty buckets (Or lists).
2) Do following for every array element arr[i].
   a) Insert arr[i] into bucket[n*array[i]]
3) Sort individual buckets using insertion sort.
4) Concatenate all sorted buckets.
```

### Time Complexity
If we assume that insertion in a bucket takes O(1) time then steps 1 and 2 of the above algorithm clearly take O(n) time. The O(1) is easily possible if we use a linked list to represent a bucket (In the following code, C++ vector is used for simplicity). 

Step 4 also takes O(n) time as there will be n items in all buckets.
The main step to analyze is step 3. This step also takes O(n) time on average if all numbers are uniformly distributed (please refer CLRS book for more details)
- Worst Case : O(n^2)
- Average Case : O(n)