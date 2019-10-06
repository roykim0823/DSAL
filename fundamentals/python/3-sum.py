#!/usr/bin/pyhton3

# ver1: brute-force, O(n^3)
# C(N 3) = N(N-1)(N-2) / 3! = 1/6 N^3
def count_three_sum_v1(num_list, sum):
    count = 0
    for i in range(0, len(num_list)-2):
        for j in range(i+1, len(num_list)-1):
            for k in range(j+1, len(num_list)):
                if num_list[i] + num_list[j] + num_list[k] == sum:
                    # print(i, j, k, "->", num_list[i], num_list[j], num_list[k])
                    count += 1
    return count


# ver2: Using binary search after sorting
# O(N^2logN)

def binary_search(input_list, key):
    lo = 0
    hi = len(input_list)-1
    while lo <= hi:
        mid = lo + (hi - lo) // 2
        if key < input_list[mid]:
            hi = mid - 1
        elif key > input_list[mid]:
            lo = mid + 1
        else:
            return mid
    return -1

def count_three_sum_v2(num_list, sum):
    count = 0
    num_list.sort()
    for i in range(0, len(num_list)-2):
        for j in range(i+1, len(num_list)-1):
            k = binary_search(num_list, sum - (num_list[i]+num_list[j]))
            if k != -1 and k > j:  # only count if i < j < k to avoid double counting
                # print(i, j, k, "->", num_list[i], num_list[j], num_list[k])
                count += 1
    return count


# ver3: Using Hashing
# O(N^2)
def count_three_sum_v3(num_list, sum):
    count = 0    
    for i in range(0, len(num_list)-2):
        cur_sum = sum - num_list[i] 
        s = set()  # same as unordered_set in C++ STL
        for j in range(i+1, len(num_list)):
            if cur_sum - num_list[j] in s:                        
                # print(i, j, "->", num_list[i], num_list[j], cur_sum-num_list[j])
                count += 1
            s.add(num_list[j])
    return count


def main():
    input_list = [30, -40, -20, -10, 40, 0, 10, 5]
    for sum_value in range(0, 100, 10):
        print("sum_v1 = ", sum_value, "->",  count_three_sum_v1(input_list, sum_value))
        print("sum_v1 = ", sum_value, "->",  count_three_sum_v2(input_list, sum_value))
        print("sum_v1 = ", sum_value, "->",  count_three_sum_v3(input_list, sum_value)) 
        print()


if __name__ == '__main__':
  main()
