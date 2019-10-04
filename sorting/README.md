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

TODO(khyunjin)
## Bucket Sort
