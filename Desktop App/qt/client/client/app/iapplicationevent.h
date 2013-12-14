#ifndef IAPPLICATIONEVENT_H
#define IAPPLICATIONEVENT_H

class IApplicationEvent
{
public:
    //flag décrivant les etats de changements dans le model
    enum CHANGE{
        CLIENT_CHANGE      = 0x1,
        INTERVENANT_CHANGE = 0x2,
        SESSION_CHANGE     = 0x4,
        ALL_CHANGE = ((unsigned int)-1)
    };
    //callback lors d'un changement
    virtual void appModelChange(int flags)=0;

    //flag décrivant les etats de changements dans la vue
    /*enum VIEW_CHANGE{
        BEFORE_CHANGE = 0x1,
        AFTER_CHANGE  = 0x2,
        SESSION_CHANGE     = 0x4,
        ALL_CHANGE = ((unsigned int)-1)
    };
    //callback lors d'un changement de vue dans l'application
    virtual void appViewChange(int flags)=0;*/
    //callback lors d'un changement de vue dans l'application
    virtual bool appViewClose()=0;
};

#endif // IAPPLICATIONEVENT_H
