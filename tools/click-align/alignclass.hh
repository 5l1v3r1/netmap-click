#ifndef ALIGNCLASS_HH
#define ALIGNCLASS_HH
#include "alignment.hh"
#include "eclasst.hh"
#include "elementt.hh"

class Aligner { public:
    Aligner()		{ }
    virtual ~Aligner()	{ }
    virtual void have_flow(Vector<Alignment>::const_iterator in, int nin,
			   Vector<Alignment>::iterator out, int nout,
			   const String &flow_code);
    virtual void want_flow(Vector<Alignment>::iterator in, int nin,
			   Vector<Alignment>::const_iterator out, int nout,
			   const String &flow_code);
    virtual void adjust_flow(Vector<Alignment>::iterator in, int nin,
			     Vector<Alignment>::const_iterator out, int nout);
};

class NullAligner : public Aligner { public:
  NullAligner() { }
  void have_flow(Vector<Alignment>::const_iterator in, int nin,
		 Vector<Alignment>::iterator out, int nout,
		 const String &flow_code);
  void want_flow(Vector<Alignment>::iterator in, int nin,
		 Vector<Alignment>::const_iterator out, int nout,
		 const String &flow_code);
};

class CombinedAligner : public Aligner {
  Aligner *_have;
  Aligner *_want;
 public:
  CombinedAligner(Aligner *have, Aligner *want) : _have(have), _want(want) { }
  void have_flow(Vector<Alignment>::const_iterator in, int nin,
		 Vector<Alignment>::iterator out, int nout,
		 const String &flow_code);
  void want_flow(Vector<Alignment>::iterator in, int nin,
		 Vector<Alignment>::const_iterator out, int nout,
		 const String &flow_code);
};

class GeneratorAligner : public Aligner {
  Alignment _alignment;
 public:
  GeneratorAligner(const Alignment &a) : _alignment(a) { }
  void have_flow(Vector<Alignment>::const_iterator in, int nin,
		 Vector<Alignment>::iterator out, int nout,
		 const String &flow_code);
  void want_flow(Vector<Alignment>::iterator in, int nin,
		 Vector<Alignment>::const_iterator out, int nout,
		 const String &flow_code);
};

class ShifterAligner : public Aligner {
  int _shift;
 public:
  ShifterAligner(int shift) : _shift(shift) { }
  void have_flow(Vector<Alignment>::const_iterator in, int nin,
		 Vector<Alignment>::iterator out, int nout,
		 const String &flow_code);
  void want_flow(Vector<Alignment>::iterator in, int nin,
		 Vector<Alignment>::const_iterator out, int nout,
		 const String &flow_code);
};

class WantAligner : public Aligner {
  Alignment _alignment;
 public:
  WantAligner(Alignment a) : _alignment(a) { }
  void want_flow(Vector<Alignment>::iterator in, int nin,
		 Vector<Alignment>::const_iterator out, int nout,
		 const String &flow_code);
};

class ClassifierAligner : public Aligner {
 public:
  ClassifierAligner() { }
  void adjust_flow(Vector<Alignment>::iterator in, int nin,
		   Vector<Alignment>::const_iterator out, int nout);
};


class AlignClass : public ElementClassT {
  Aligner *_aligner;
 public:
  AlignClass(const String &);
  AlignClass(const String &, Aligner *);
  virtual Aligner *create_aligner(ElementT *, RouterT *, ErrorHandler *);
  void *cast(const char *);
};

class StripAlignClass : public AlignClass {
 public:
  StripAlignClass();
  Aligner *create_aligner(ElementT *, RouterT *, ErrorHandler *);
};

class CheckIPHeaderAlignClass : public AlignClass {
  int _argno;
 public:
  CheckIPHeaderAlignClass(const String &, int);
  Aligner *create_aligner(ElementT *, RouterT *, ErrorHandler *);
};

class AlignAlignClass : public AlignClass {
 public:
  AlignAlignClass();
  Aligner *create_aligner(ElementT *, RouterT *, ErrorHandler *);
};


Alignment common_alignment(Vector<Alignment>::const_iterator, int count);
Aligner *default_aligner();

#endif
