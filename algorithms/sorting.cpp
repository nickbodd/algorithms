#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

void printArray(vector<int>& arr) {
    for (int i=0; i<arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int insertionSort(vector<int>& ar) {
    int ar_size = (int) ar.size();
    if (ar_size <= 1) {
        return 0;
    }
    
    int count = 0;
    for (int i=1; i<ar_size; ++i) {
        int lastElement = ar[i];
        for (int j=i-1; j >= 0; --j) {
            if (ar[j] > lastElement) {
                ar[j + 1] = ar[j];
                ar[j] = lastElement;
                count++;
            }
        }
    }
    return count;
}


int partition(vector<int>& arr, int startIndex, int endIndex, int & count) {
    
    int pivot = arr[endIndex];
    
    int traverse = startIndex;
    int low = startIndex;
    while (traverse < endIndex) {
        if (arr[traverse] < pivot) {
            int temp = arr[low];
            arr[low] = arr[traverse];
            arr[traverse] = temp;
            low++;
            count++;
            //          printArray(arr);
        }
        traverse++;
    }
    
    int temp = arr[low];
    arr[low] = pivot;
    arr[endIndex] = temp;
    count++;
    //    printArray(arr);
    
    return low;
}

int quickSort(vector<int>& arr, int startIndex, int endIndex) {
    
    if (startIndex >= endIndex) {
        return 0;
    }
    
    int count = 0;
    int partitionIndex = partition(arr, startIndex, endIndex, count);
    
    count += quickSort(arr, startIndex, partitionIndex - 1);
    count += quickSort(arr, partitionIndex + 1, endIndex);
    
    return count;
}

int sorting_main()
{
    int n;
    cin >> n;
    
    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }
    
    vector<int> arr2(arr);
    int qck = quickSort(arr, 0, (int) arr.size() - 1);
    int ins = insertionSort(arr2);
    cout << ins - qck;
    
    return 0;
}

int counting_sort() {
    int n;
    cin >> n;
    int numOfTimes[100] = { 0 };
    vector<pair<int, string>> data;
    for (int i=0; i<n; ++i) {
        int val;
        cin >> val;
        string text;
        cin >> text;
        
        numOfTimes[val]++;
        data.push_back(pair<int, string>(val, text));
    }
    
    int incrementalPosition[100] = { 0 };
    int totalSum = 0;
    for (int i=0; i<100; ++i) {
        incrementalPosition[i] = totalSum;
        totalSum += numOfTimes[i];
    }
    
    //positionsOfData tracks location of each data item from 0..n-1 will be placed
    // positionOfData[i] -> i-th data member will be placed at the resulting value
    vector<int> positionsOfData(n);
    for (int i=0; i<n; ++i) {
        int incrementalPositionIndex =  data[i].first;
        positionsOfData[i] = incrementalPosition[incrementalPositionIndex];
        incrementalPosition[incrementalPositionIndex]++;
    }
    
    // reverse the positionsOfData vector
    // Because, when we want to print, we dont care where each data element is placed,
    // instead we want sequentially which data member is needed to be placed next
    vector<int> reversePositionData(positionsOfData.size());
    for (int i=0; i < positionsOfData.size(); ++i) {
        reversePositionData[positionsOfData[i]] = i;
    }
    
    for (int i=0; i<reversePositionData.size(); ++i) {
        int dataIndex = reversePositionData[i];
        cout << ((dataIndex >= n/2) ? data[dataIndex].second : "-") << " ";
    }
    cout << endl;
    
    return 0;
}

struct ElementNode {
    int value;
    int index;
};

struct ElementDiffNode {
    int diff;
    int xIndex;
    int yIndex;
};

bool ElementNodeSort(const ElementNode& a, const ElementNode & b) {
    return a.value < b.value;
}

bool ElementDiffSort(const ElementDiffNode& a, const ElementDiffNode & b) {
    return a.diff < b.diff;
}

void smallest_absolute_difference() {
    int n;
    cin >> n;
    
    vector <ElementNode> arr;
    vector<int> data(n);
    for(int i = 0; i < n; ++i) {
        cin >> data[i];
        ElementNode e;
        e.value = data[i];
        e.index = i;
        arr.push_back(e);
    }
    
    vector<ElementDiffNode> absDiff;
    std::sort(arr.begin(), arr.end(), ElementNodeSort);
    for (int i=1; i < n; ++i) {
        int diff = abs(arr[i].value - arr[i-1].value);
        ElementDiffNode e;
        e.diff = diff;
        
        int x = arr[i-1].index;
        int y = arr[i].index;
        
        e.xIndex = (data[x] < data[y]) ? x : y;
        e.yIndex = (data[y] > data[x]) ? y : x;
        
        absDiff.push_back(e);
    }
    
    const auto minItr = min_element(absDiff.begin(), absDiff.end(), ElementDiffSort);
    
    int minValue = minItr->diff;
    for (int i = 0; i < absDiff.size(); ++i) {
        if (absDiff[i].diff == minValue) {
            cout << data[absDiff[i].xIndex] << " " << data[absDiff[i].yIndex] << " ";
        }
    }
}

int median_partition(vector<int> & data, int startIndex, int endIndex, int medianIndex) {
    
    int pivotValue = data[endIndex];
    int low = startIndex;
    for (int traverse=startIndex; traverse<=endIndex-1; ++traverse) {
        if (data[traverse] < pivotValue) {
            int temp = data[low];
            data[low] = data[traverse];
            data[traverse] = temp;
            low++;
        }
    }
    
    int temp = data[low];
    data[low] = pivotValue;
    data[endIndex] = temp;
    
    if (low == medianIndex) {
        return pivotValue;
    } else if (low > medianIndex) {
        return median_partition(data, startIndex, low-1, medianIndex);
    } else {
        return median_partition(data, low+1, endIndex, medianIndex);
    }
}

void find_median() {
    int n;
    cin >> n;
    
    vector<int> data(n);
    for(int i = 0; i < n; ++i) {
        cin >> data[i];
    }
    
    cout << median_partition(data, 0, n-1, n/2) << endl;
}

void rotated_array() {
    int N, K, Q;
    cin >> N >> K >> Q;
    
    vector<int> data(N);
    for(int i = 0; i < N; ++i) {
        cin >> data[i];
    }
    
    int query;
    for (int i=0; i < Q; ++i) {
        cin >> query;
        
        K = K % N;

        cout << data[ (N + query - K ) % N ] << endl;
    }
}

bool sorted(vector<int> & data) {
    for (int i=1; i<data.size(); ++i) {
        if (data[i] < data[i-1]) {
            return false;
        }
    }
    
    return true;
}

void almost_sorted() {
    int n;
    cin >> n;
    
    vector<int> data(n);
    for(int i = 0; i < n; ++i) {
        cin >> data[i];
    }
    
    if (sorted(data)) {
        cout << "yes" << endl;
        return;
    }
    
    // else
    int firstDip = 0;
    for (int i=1; i<data.size(); ++i) {
        if (data[i] < data[i-1]) {
            firstDip = i-1;
            break;
        }
    }
    
    int secondDip = data.size() - 1;
    for (int i=firstDip+1; i < data.size(); ++i) {
        if (data[firstDip] < data[i]) {
            secondDip = i - 1;
            break;
        }
    }
    
    int temp = data[firstDip];
    data[firstDip] = data[secondDip];
    data[secondDip] = temp;
    
    if (sorted(data)) {
        cout << "yes" << endl << "swap " << firstDip + 1 << " " << secondDip + 1 << endl;
        return;
    } else {
        //undo swap
        int temp = data[firstDip];
        data[firstDip] = data[secondDip];
        data[secondDip] = temp;
        
    }
    
    // if not reverse between first and second dips
    std::reverse(data.begin() + firstDip, data.begin() + secondDip + 1);
    
    if (sorted(data)) {
        cout << "yes" << endl << "reverse " << firstDip + 1 << " " << secondDip + 1<< endl;
    } else {
        cout << "no" << endl;
    }
    
}

int64_t permutations(int n, int r) {
    if (r > n) {
        return 0;
    }
    
    int64_t result = 1;
    int base = n - r;
    for (int j = base+1; j <= n; ++j) {
        result *= j;
    }
    return result;
}

void sherlock_and_pairs() {
    int testCases;
    cin >> testCases;
    
    for (int test=0; test < testCases; ++test) {
        int n;
        cin >> n;
        
        vector <int64_t> arr(n);
        for(int i = 0; i < (int)n; ++i) {
            cin >> arr[i];
        }
        
        //std::sort(arr.begin(), arr.end());
        
        map<int64_t, int> pairs;
        for (int i=0; i<arr.size(); ++i) {
            int key = arr[i];
            if (pairs.find(key) != pairs.end()) {
                pairs[key] += 1;
            } else {
                pairs[key] = 1;
            }
        }
        
        int64_t count = 0;
        for (auto it = pairs.begin(); it != pairs.end(); ++it) {
            if (it->second > 1) {
                count += permutations(it->second, 2);
            }
        }
        cout << count << endl;
    }
}

void array_unfairness() {
    int N, K;
    cin >> N >> K;
    
    vector <int64_t> arr(N);
    for(int i = 0; i < (int) N; ++i) {
        cin >> arr[i];
    }
    
    std::sort(arr.begin(), arr.end());
    
    int64_t minUnfairness = 99999999;
    for (int i=0; i <= (N-K); ++i) {
        int64_t max = arr[i+K-1];
        int64_t min = arr[i];
        
        int64_t unfairness = max - min;
        if (unfairness < minUnfairness) {
            minUnfairness = unfairness;
        }
    }
    
    
    cout << minUnfairness << endl;
}

int sorting_main2() {
    array_unfairness();
    return 0;
}
