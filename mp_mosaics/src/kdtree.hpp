/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>
#include <cmath>

using namespace std;

template <int Dim>
bool smallerDimVal( const Point<Dim>& first,
                    const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]){
      return true;
    }
    if (first[curDim] > second[curDim]){
      return false;
    }
      return (first < second);

    //return false;
}

template <int Dim>
bool shouldReplace( const Point<Dim>& target,
                    const Point<Dim>& currentBest,
                    const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
    double euclidean_cur = 0, euclidean_pot = 0;
    for(int i=0; i<Dim; i++){
      euclidean_cur += (target[i]-currentBest[i]) * (target[i]-currentBest[i]);
      euclidean_pot += (target[i]-potential[i]) * (target[i]-potential[i]);
    }
    if(euclidean_cur < euclidean_pot){
      return false;
    }
    if(euclidean_cur > euclidean_pot){
      return true;
    }
      return(potential < currentBest);
    //return false;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& newPoints,int start, int end, int depth){

  if(end < start + 1){
    return nullptr;
  }

    //int curDim = depth % Dim;
  auto median = newPoints.begin() + (end + start - 1) / 2;
  select(newPoints.begin()+start, newPoints.begin()+end, median, 
        ([depth](Point<Dim> a,Point<Dim> b) {return smallerDimVal(a, b, depth%Dim);}));//new cmp

  KDTreeNode* node = new KDTreeNode(*median);
    
    // node->left = KDTree<Dim>::buildTree(start, median, depth + 1);
    // node->right = KDTree<Dim>::buildTree(median + 1, end, depth + 1);
  node->left = KDTree<Dim>::buildTree(newPoints,start, (start+end-1)/2, depth+1);
  node->right = KDTree<Dim>::buildTree(newPoints,(start+end-1)/2+1, end, depth+1);
  size++;
  return node;
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints){
    /**
     * @todo Implement this function!
     */
  vector<Point<Dim>> pointsCopy = newPoints;
    // root = buildTree(pointsCopy.begin(), pointsCopy.end(), 0);
  if(newPoints.empty()){
    size = 0;
    root = NULL;
  }
  else{
    root = buildTree(pointsCopy, 0, pointsCopy.size(), 0);
  }
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other){
  /**
   * @todo Implement this function!
   */
  root = copyhelper(other.root);
}


template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copyhelper(const KDTreeNode* node){
  if(!node) 
    return nullptr;

  KDTreeNode* newNode = new KDTreeNode(node->point);
  newNode->left = copyhelper(node->left);
  newNode->right = copyhelper(node->right);
  return newNode;
}


template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs){
  /**
   * @todo Implement this function!
   */
  if (this == &rhs){
    return *this;
  }

  clean(root);
  root = copyhelper(rhs.root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree(){
  /**
   * @todo Implement this function!
   */
  clean(root);
}

template <int Dim>
void KDTree<Dim>::clean(KDTreeNode* node){
    if(!node)
        return;
    clean(node->left);
    clean(node->right);
    delete node;
}



template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const{
    /**
     * @todo Implement this function!
     */
    return nearesthelper(root, query, 0);
}


template <int Dim>
Point<Dim> KDTree<Dim>::nearesthelper(KDTreeNode* node, const Point<Dim>& query, int dimension) const{
    if (!node) {
        return Point<Dim>(); //defult value
    }
    KDTreeNode* nextNode = nullptr;
    KDTreeNode* otherNode = nullptr;

    if(smallerDimVal(query, node->point, dimension)){
      nextNode = node->left;
      otherNode = node->right;
    } else{
      nextNode = node->right;
      otherNode = node->left;
    }
    Point<Dim> currentBest;
    if (nextNode){
      currentBest = nearesthelper(nextNode, query, (dimension + 1) % Dim);
    } else{
      currentBest = node->point;
    }
    if (shouldReplace(query, currentBest, node->point)){
      currentBest = node->point;
    }

    double r = 0.0;
    for (int i = 0; i < Dim; i++){
      r += (query[i] - currentBest[i]) * (query[i] - currentBest[i]);
    }
    if ((query[dimension] - node->point[dimension]) * (query[dimension] - node->point[dimension]) <= r){
      if (otherNode) {
        Point<Dim> potential = nearesthelper(otherNode, query, (dimension + 1) % Dim);
        if (shouldReplace(query, currentBest, potential)){
          currentBest = potential;
        }
      }
    }

    return currentBest;
}



template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp)
{
    /**
     * @todo Implement this function!
     */
  if (start == end) return;

  RandIter pivot = end - 1;//last element as pivot
  RandIter i = start;

  for (RandIter j = start; j != pivot; ++j){
    if (cmp(*j, *pivot)){
      std::iter_swap(i, j);
      ++i;
    }
  }
  std::iter_swap(i, pivot);

  //check pivot
  if (k == i){
    return;
  } else if (k < i){
    select(start, i, k, cmp);
  } else{
    select(i + 1, end, k, cmp);
  }
}

