// OVIMXcin.h

#ifndef __OVIMXcin_h
#define __OVIMXcin_h

#include <OpenVanilla/OpenVanilla.h>
#include "../../Source/OSX/VXCIN.h"
#include "OVKeySequence.h"

class XcinKeySequence : public OVKeySequenceSimple
{
public:
    XcinKeySequence(VXCIN* cintab);
    virtual int length() { return len; }
    virtual int add(char c);
    virtual NSString *compose(NSMutableString *s);
    virtual char *getSeq() { return seq; }
    
protected:
    VXCIN *cinTable;
};

class OVIMXcin;

class OVXcinContext : public OVIMContext
{
public:
    OVXcinContext(OVIMXcin *p, VXCIN *tab) : parent(p), keyseq(tab), cintab(tab) {}
    virtual int activate(OVService *) { return 1; }
    virtual int deactivate(OVService *) { return 1; }
    virtual int keyEvent(OVKeyCode *key, OVBuffer *buf,
        OVTextBar *textbar, OVService *srv);

protected:
    virtual void updateDisplay(OVBuffer *buf);
    virtual int compose(OVBuffer *buf);
    
    OVIMXcin *parent;
    XcinKeySequence keyseq;
    VXCIN *cintab;
};

class OVIMXcin : public OVInputMethod
{
public:
    OVIMXcin(char *lpath, char *cfile);
    virtual ~OVIMXcin();    
    virtual int identifier(char *s);
    virtual int name(char *locale, void *s, OVEncoding *enc);
    virtual int initialize(OVDictionary*, OVDictionary*, OVService*, char* path);
    virtual int terminate(OVDictionary*, OVDictionary*, OVService*);
    virtual OVIMContext *newContext();
    
protected:
    char loadpath[PATH_MAX];
    char cinfile[PATH_MAX];
    VXCIN *cintab;
};

#endif