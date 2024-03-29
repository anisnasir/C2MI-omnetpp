//
// Generated file, do not edit! Created by opp_msgc 4.1 from RREQ.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "RREQ_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(RREQ);

RREQ::RREQ(const char *name, int kind) : cMessage(name,kind)
{
    this->DesName_var = 0;
    this->SrcName_var = 0;
    this->cost_var = 0;
    this->timestamp_var = 0;
}

RREQ::RREQ(const RREQ& other) : cMessage()
{
    setName(other.getName());
    operator=(other);
}

RREQ::~RREQ()
{
}

RREQ& RREQ::operator=(const RREQ& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    this->DesName_var = other.DesName_var;
    this->SrcName_var = other.SrcName_var;
    this->cost_var = other.cost_var;
    this->timestamp_var = other.timestamp_var;
    return *this;
}

void RREQ::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->DesName_var);
    doPacking(b,this->SrcName_var);
    doPacking(b,this->cost_var);
    doPacking(b,this->timestamp_var);
}

void RREQ::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->DesName_var);
    doUnpacking(b,this->SrcName_var);
    doUnpacking(b,this->cost_var);
    doUnpacking(b,this->timestamp_var);
}

const char * RREQ::getDesName() const
{
    return DesName_var.c_str();
}

void RREQ::setDesName(const char * DesName_var)
{
    this->DesName_var = DesName_var;
}

const char * RREQ::getSrcName() const
{
    return SrcName_var.c_str();
}

void RREQ::setSrcName(const char * SrcName_var)
{
    this->SrcName_var = SrcName_var;
}

int RREQ::getCost() const
{
    return cost_var;
}

void RREQ::setCost(int cost_var)
{
    this->cost_var = cost_var;
}

int RREQ::getTimestamp() const
{
    return timestamp_var;
}

void RREQ::setTimestamp(int timestamp_var)
{
    this->timestamp_var = timestamp_var;
}

class RREQDescriptor : public cClassDescriptor
{
  public:
    RREQDescriptor();
    virtual ~RREQDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(RREQDescriptor);

RREQDescriptor::RREQDescriptor() : cClassDescriptor("RREQ", "cMessage")
{
}

RREQDescriptor::~RREQDescriptor()
{
}

bool RREQDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<RREQ *>(obj)!=NULL;
}

const char *RREQDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int RREQDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int RREQDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *RREQDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "DesName",
        "SrcName",
        "cost",
        "timestamp",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int RREQDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='D' && strcmp(fieldName, "DesName")==0) return base+0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SrcName")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "cost")==0) return base+2;
    if (fieldName[0]=='t' && strcmp(fieldName, "timestamp")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *RREQDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "int",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *RREQDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int RREQDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    RREQ *pp = (RREQ *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string RREQDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    RREQ *pp = (RREQ *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getDesName());
        case 1: return oppstring2string(pp->getSrcName());
        case 2: return long2string(pp->getCost());
        case 3: return long2string(pp->getTimestamp());
        default: return "";
    }
}

bool RREQDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    RREQ *pp = (RREQ *)object; (void)pp;
    switch (field) {
        case 0: pp->setDesName((value)); return true;
        case 1: pp->setSrcName((value)); return true;
        case 2: pp->setCost(string2long(value)); return true;
        case 3: pp->setTimestamp(string2long(value)); return true;
        default: return false;
    }
}

const char *RREQDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *RREQDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    RREQ *pp = (RREQ *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


