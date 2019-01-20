/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] < second[curDim]){
        return true;
    }else if(first[curDim] == second[curDim]){
        return first < second;
    }
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double cur_distance = 0;
    double pot_distance = 0;
    for(int i = 0; i < Dim; i++){
        cur_distance += (currentBest[i] - target[i])*(currentBest[i] - target[i]);
        pot_distance += (potential[i] - target[i])*(potential[i] - target[i]);
    }
    if(pot_distance < cur_distance){
        return true;
    }else if(cur_distance == pot_distance){
        return potential < currentBest;
    }
    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    //std::cout<<std::endl<<"constructor has been called!"<<std::endl;
    if(newPoints.size() == 0){
        root = new KDTreeNode();
    }else{
        Points.assign(newPoints.begin(), newPoints.end());
        root = buildhelper(Points, 0, Points.size()-1, 0);
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
    /**
     * @todo Implement this function!
     */
    //std::cout<<std::endl<<"copy constructor has been called!"<<std::endl;
    this->Points = other.Points;
    _copy(this->root, other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
    /**
     * @todo Implement this function!
     */
    //std::cout<<std::endl<<"operator= has been called!"<<std::endl;
    _destory(this->root);
    _copy(this->root, rhs.root);
    return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
    /**
     * @todo Implement this function!
     */
    //std::cout<<std::endl<<"destructor has been called!"<<std::endl;
    _destory(this->root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    
    return findhelper( 0, 0, Points.size()-1, Points[(Points.size()-1)/2], query);
}

