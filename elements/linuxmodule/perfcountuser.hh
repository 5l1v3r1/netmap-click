#ifndef PERFCOUNTUSER_HH
#define PERFCOUNTUSER_HH
#include "element.hh"

class PerfCountUser : public Element { public:

  PerfCountUser();

  bool is_base() const		{ return _metric0 > -2; }
  
  int prepare(const String &, ErrorHandler *);
  int initialize(ErrorHandler *);

 private:

  int _metric0;
  int _metric1;
  
};

#define MSR_OS			(1<<17)
#define MSR_OCCURRENCE		(1<<18)
#define MSR_ENABLE		(1<<22)
#define MSR_FLAGS0		(MSR_OS|MSR_OCCURRENCE|MSR_ENABLE)
#define MSR_FLAGS1		(MSR_OS|MSR_OCCURRENCE)

#define MSR_EVNTSEL0		0x186
#define MSR_EVNTSEL1		0x187

#endif
