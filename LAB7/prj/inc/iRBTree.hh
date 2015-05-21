#ifndef IRBTREE__HH
#define IRBTREE__HH
#include "RBTree.hh"
template <typename T>
class iRBTree
{
public:
  virtual void add(T value)=0;
  virtual bool find(T value)=0;
  virtual void print()=0;
  //virtual void rotate_L(RBTree<T> *Z)=0;
  //virtual void rotate_R(RBTree<T> *Z)=0;
};

#endif
