## Algorithms Complexity Analysis

### Insertion Sort

```python
class InsertionSort(object):

    def sort(list):                                 # Cost  Executions
        for i in range(1, len(list)):               # c1    n
            temp = list[i]                          # c2    n - 1
            j = i - 1                               # c3    n - 1

            while j >= 0 and list[j] > temp:        # c4    sum_j=1^n-1 tj
                list[j + 1] = list[j]               # c5    sum_j=1^n-1 (tj - 1)
                j = j - 1                           # c6    sum_j=1^n-1 (tj - 1)

            list[j + 1] = temp                      # c7    n - 1

        return list
```

So, we have:
```
T(n) = n(c1) + (n - 1)(c2 + c3 + c7) + (sum_j=1^n-1 tj)(c4) + (sum_j=1^n-1 (tj - 1))(c5 + c6)
T(n) = n(c1 + c2 + c3 + c7) + (sum_j=1^n-1 tj)(c4) + (sum_j=1^n-1 (tj - 1))(c5 + c6) - (c2 + c3 + c7)
```

In the **worst-case scenario**, when the input list is in reverse order, `j` will always reach -1 in the inner loop:
```
sum_j=1^n-1 tj = 1 + 2 + ... + n - 1 = n(n - 1) / 2 = (n^2 - n)/2
sum_j=1^n-1 tj - 1 = 1 + 2 + ... + n - 1 = n(n - 1) / 2 - 1 = (n^2 - n)/2 - 1

T(n) = n(c1 + c2 + c3 + c7) + ((n^2 - n) / 2)(c4) + ((n^2 - n) / 2 - 1)(c5 + c6)- (c2 + c3 + c7)
T(n) = n(c1 + c2 + c3 + c7) + (n^2(c4) - n(c4) + n^2(c5) - n(c5) + n^2(c6) - n(c6)) / 2 - (c2 + c3 + c7 + c5 + c6)
T(n) = n^2(c4 + c5 + c6)/2 + n(c1 + c2 + c3 + c7) - n(c4 + c5 + c6)/2 - (c2 + c3 + c5 + c6 + c7)
```