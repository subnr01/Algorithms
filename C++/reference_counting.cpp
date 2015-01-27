// Fred.h

class FredPtr;

class Fred {
public:
  Fred() : count_(0) /*...*/ { }  // All ctors set count_ to 0 !
  ...
private:
  friend class FredPtr;     // A friend class
  unsigned count_;
  // count_ must be initialized to 0 by all constructors
  // count_ is the number of FredPtr objects that point at this
};

class FredPtr {
public:
  Fred* operator-> () { return p_; }
  Fred& operator* ()  { return *p_; }
  FredPtr(Fred* p)    : p_(p) { ++p_->count_; }  // p must not be NULL
 ~FredPtr()           { if (--p_->count_ == 0) delete p_; }
  FredPtr(FredPtr const& p) : p_(p.p_) { ++p_->count_; }
  FredPtr& operator= (FredPtr const& p)
        { // DO NOT CHANGE THE ORDER OF THESE STATEMENTS!
          // (This order properly handles self-assignment)
          // (This order also properly handles recursion, e.g., if a Fred contains FredPtrs)
          Fred* const old = p_;
          p_ = p.p_;
          ++p_->count_;
          if (--old->count_ == 0) delete old;
          return *this;
        }
private:
  Fred* p_;    // p_ is never NULL
};


class Fred {
public:
  static FredPtr create();              // Defined below class FredPtr {...};
  static FredPtr create(int i, int j);  // Defined below class FredPtr {...};
  ...
private:
  Fred();
  Fred(int i, int j);
  ...
};

class FredPtr { /* ... */ };

inline FredPtr Fred::create()             { return new Fred(); }
inline FredPtr Fred::create(int i, int j) { return new Fred(i,j); }
