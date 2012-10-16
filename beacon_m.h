//
// Generated file, do not edit! Created by opp_msgc 4.1 from beacon.msg.
//

#ifndef _BEACON_M_H_
#define _BEACON_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0401
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif



/**
 * Class generated from <tt>beacon.msg</tt> by opp_msgc.
 * <pre>
 * message beacon{
 *     string SourceName;
 * }
 * </pre>
 */
class beacon : public ::cMessage
{
  protected:
    opp_string SourceName_var;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const beacon&);

  public:
    beacon(const char *name=NULL, int kind=0);
    beacon(const beacon& other);
    virtual ~beacon();
    beacon& operator=(const beacon& other);
    virtual beacon *dup() const {return new beacon(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual const char * getSourceName() const;
    virtual void setSourceName(const char * SourceName_var);
};

inline void doPacking(cCommBuffer *b, beacon& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, beacon& obj) {obj.parsimUnpack(b);}


#endif // _BEACON_M_H_