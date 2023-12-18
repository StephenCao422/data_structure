#include<iostream>;

class heap{
    std::vector<int> elem;
    template<class T>
    void heap<T>::heapifyUp(size_t currentIdx){
        if (currentIdx == root()){
            return;
        }
        size_t parent = (currentIdx - 1)/2;
        if(elem[currentIdx]<elem[parent]){
            std::swap(elem[currentIdx], elem[parent]);
            heapifyUp(parent);
        }
    }

    template<class T>
    void heap<T>::heapifyDown(size_t currentIdx){
        size_t smallest = currentIdx;
        size_t left = currentIdx *2 +1;
        size_t right = currentIdx *2 +2;
        if(left<elem.size() && elem[left]<elem[smallest]){
            smallest = left;
        }
        if(right<elem.size() && elem[right]<elem[smallest]){
            smallest = right;
        }
        if(smallest != currentIdx){
            std::swap(elem[currentIdx],elem[smallest]);
            heapifyDown(smallest);
        }
    }
};

