
class InsertionSort(object):

    def sort(list):                                 # Cost  Executions
        for i in range(1, len(list)):               # c1    n
            temp = list[i]                          # c2    n - 1
            j = i - 1                               # c3    n - 1

            while j >= 0 and list[j] > temp:        # c4    sum_j=2^n tj
                list[j + 1] = list[j]               # c5    sum_j=2^n (tj - 1)
                j = j - 1                           # c6    sum_j=2^n (tj - 1)

            list[j + 1] = temp                      # c7    n - 1

        return list


class MergeSort(object):

    def sort(list):                                 # Cost      Executions
        if len(list) < 2:                           # c1        1
            return list                             # c2        1

        mid = len(list) // 2                        # c3        1
        left = MergeSort.sort(list[:mid])           # T(n/2)    1
        right = MergeSort.sort(list[mid:])          # T(n/2)    1
        return MergeSort.merge(left, right)         # n(c4)     1

    def merge(left, right):                         # Cost      Executions
        if not len(left) or not len(right):         # c5        1
            return left or right                    # c6        1

        merged = []                                 # c7        1

        while len(left) != 0 and len(right) != 0:   # c8        
            if left[0] < right[0]:                  #
                merged.append(left[0])              #
                left.remove(left[0])                #
            else:
                merged.append(right[0])             #
                right.remove(right[0])              #

        merged.extend(left or right)                #
        return merged                               #


class QuickSort(object):

    def sort(list):
        return None

        
if __name__ == "__main__":
    
    list1 = [1, 6, 3, 1, 8, 4, 5, 7, 10, 2, 9]
    sortedList1 = InsertionSort.sort(list1)
    print(sortedList1)

    sortedList2 = MergeSort.sort(list1)
    print(sortedList2)
    # TO-DO