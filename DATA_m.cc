//
// Generated file, do not edit! Created by opp_msgc 4.1 from DATA.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "DATA_m.h"

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




Register_Class(DATA);

DATA::DATA(const char *name, int kind) : cMessage(name,kind)
{
    this->DesName_var = 0;
    this->SrcName_var = 0;
    this->Payload_var = 0;
}

DATA::DATA(const DATA& other) : cMessage()
{
    setName(other.getName());
    operator=(other);
}

DATA::~DATA()
{
}

DATA& DATA::operator=(const DATA& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    this->DesName_var = other.DesName_var;
    this->SrcName_var = other.SrcName_var;
    this->Payload_var = other.Payload_var;
    return *this;
}

void DATA::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->DesName_var);
    doPacking(b,this->SrcName_var);
    doPacking(b,this->Payload_var);
}

void DATA::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->DesName_var);
    doUnpacking(b,this->SrcName_var);
    doUnpacking(b,this->Payload_var);
}

const char * DATA::getDesName() const
{
    return DesName_var.c_str();
}

void DATA::setDesName(const char * DesName_var)
{
    this->DesName_var = DesName_var;
}

const char * DATA::getSrcName() const
{
    return SrcName_var.c_str();
}

void DATA::setSrcName(const char * SrcName_var)
{
    this->SrcName_var = SrcName_var;
}

const char * DATA::getPayload() const
{
    return Payload_var.c_str();
}

void DATA::setPayload(const char * Payload_var)
{
    this->Payload_var = Payload_var;
}

class DATADescriptor : public cClassDescriptor
{
  public:
    DATADescriptor();
    virtual ~DATADescriptor();

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

Register_ClassDescriptor(DATADescriptor);

DATADescriptor::DATADescriptor() : cClassDescriptor("DATA", "cMessage")
{
}

DATADescriptor::~DATADescriptor()
{
}

bool DATADescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DATA *>(obj)!=NULL;
}

const char *DATADescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DATADescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int DATADescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *DATADescriptor::getFieldName(void *object, int field) const
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
        "Payload",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int DATADescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='D' && strcmp(fieldName, "DesName")==0) return base+0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SrcName")==0) return base+1;
    if (fieldName[0]=='P' && strcmp(fieldName, "Payload")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DATADescriptor::getFieldTypeString(void *object, int field) const
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
        "string",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *DATADescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DATADescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DATA *pp = (DATA *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DATADescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DATA *pp = (DATA *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getDesName());
        case 1: return oppstring2string(pp->getSrcName());
        case 2: return oppstring2string(pp->getPayload());
        default: return "";
    }
}

bool DATADescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DATA *pp = (DATA *)object; (void)pp;
    switch (field) {
        case 0: pp->setDesName((value)); return true;
        case 1: pp->setSrcName((value)); return true;
        case 2: pp->setPayload((value)); return true;
        default: return false;
    }
}

const char *DATADescriptor::getFieldStructName(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *DATADescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DATA *pp = (DATA *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


