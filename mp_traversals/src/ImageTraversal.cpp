#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt((h*h) + (s*s) + (l*l));
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
  }

  /**
  * Removes the current Point in the bfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    // if (!work_list.empty()){
    //   work_list.pop_front();
    // }
    // return;
    work_list.pop_front();
  }

  /**
  * Removes the current Point in the dfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    // if (!work_list.empty()){
    //   work_list.pop_back();
    // }
    // return;
    work_list.pop_back();
  }

  /**
   * Returns the current Point in the bfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point bfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    //return Point(0, 0);
    return work_list.front();
  }

  /**
   * Returns the current Point in the dfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point dfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    //return Point(0, 0);
    return work_list.back();
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param fns the set of functions describing a traversal's operation
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns) {  
    /** @todo [Part 1] */
    png_ = png;
    start_ = start;
    tor_ = tolerance;
    fns_ = fns;

    visited_ = std::vector<std::vector<bool>>(png_.width(), std::vector<bool>(png_.height(), false));
    visited_[start_.x][start_.y] = true;
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator(this,start_,png_, tor_);
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator();
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator()
  {
    /** @todo [Part 1] */
    data = nullptr;
    curr = Point(-1,-1);
  }

  ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point start, PNG png, double tolerance){
    this->data = traversal;
    this->start = start;
    this->curr = start;
  	this->tolerance = tolerance;

    //work_list_.push_back(start);
  }

  /**
  * Iterator increment operator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */
    //return *this;
    data->visited_[curr.x][curr.y] = true;

    std::vector<Point> directions = {
        Point(curr.x + 1, curr.y),
        Point(curr.x, curr.y + 1),
        Point(curr.x - 1, curr.y),
        Point(curr.x, curr.y - 1)};

    for (const Point &next : directions) {
        if (canGo(next)) {
            data->fns_.add(work_list_, next);
        }
    }
    //while (!work_list_.empty() && !isLegal(work_list_.front())) {
    while (!work_list_.empty() && !canGo(data->fns_.peek(work_list_))) {
        data->fns_.pop(work_list_);
    }
    if (!work_list_.empty()){  //updata
        //curr = work_list_front();
        curr = data->fns_.peek(work_list_);
    } else {
        *this = data->end();
    }
    return *this;
}


bool ImageTraversal::Iterator::canGo(const Point &curr) {
    if (curr.x < data->png_.width() && curr.y < data->png_.height()) {
        HSLAPixel &p1 = data->png_.getPixel(data->start_.x, data->start_.y);
        HSLAPixel &p2 = data->png_.getPixel(curr.x, curr.y);

        if (!data->visited_[curr.x][curr.y] && calculateDelta(p1, p2) < data->tor_) {
            return true;
        }
    }
    return false;
}

  /**
  * Iterator accessor operator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    //return Point(-1, -1);
    return curr;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    //return false;
    if (this->curr == other.curr){
      return false;
    }
    return true;
  }

  /**
   * Iterator size function.
   *
   * @return size_t the size of the iterator work queue.
   */
  size_t ImageTraversal::Iterator::size() const {
    return work_list_.size();
  }

  /**
   * Iterator empty function.
   *
   * @return bool whether the iterator work queue is empty.
   */
  bool ImageTraversal::Iterator::empty() const {
    return work_list_.empty();
  }

}