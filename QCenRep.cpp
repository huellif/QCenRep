#include "QCenRep.h"
#include <centralrepository.h>


//#include <QtCore/QDebug>

QString QCenRep::getCenrep(int iUID, int iKey)
{
    QString val;
    static const TUid repository = { iUID };
    const TUint32 key = iKey;

    ReadValStr(repository, key, &val);
    TInt i = ReadValInt(repository, key);

    if (i == -6)
    {
        if(val == QLatin1String(""))
        {
            return QString("");
        }

        else
        {
            return val;
        }
    }
    else {
        if (i != -1) {
            return val.number(i);

        }
        return QString("Missing key!");

    }
}

QString QCenRep::getCenrep(QString iUID, QString iKey)
{
    return getCenrep(iUID.toInt(0, 16), iKey.toInt(0, 16));
}

QString QCenRep::getCenrep(char *iUID, char *iKey)
{
    return getCenrep(QString::fromAscii(iUID).toInt(0, 16), QString::fromAscii(iKey).toInt(0, 16));
}

void QCenRep::setCenrep(QString iUID, QString iKey, QString qValue)
{
    setCenrep(iUID.toInt(),iKey.toInt(), qValue);
}

void QCenRep::setCenrep(const char *iUID, const char *iKey, const char *qValue)
{
    setCenrep(QString::fromAscii(iUID).toInt(0, 16), QString::fromAscii(iKey).toInt(0, 16), QString::fromAscii(qValue));
}

void QCenRep::setCenrep(int iUID, int iKey, QString qValue)
{
    qValue = qValue.trimmed();
    QString val;
    static const TUid repository = { iUID };
    const TUint32 key = iKey;

    ReadValStr(repository, key, &val);
    TInt i = ReadValInt(repository, key);


    if (i == -6) //String
    {
        ChangeValStr(repository, iKey, qValue);
    }

    else {
        if (i != -1) //key has to exist
        {
            ChangeValInt(repository, iKey, qValue.toInt());
        }
        //else qDebug() << "Missing key!";
    }
}

void QCenRep::setCenrep(int iUID, int iKey, const char *qValue)
{
    setCenrep(iUID, iKey, QString::fromAscii(qValue));
}

TInt QCenRep::ChangeValInt(const TUid KUidRepository, TUint32 key, const TInt newkeyvalue){
    TInt err;
    CRepository* iRepository = 0;
    QString intstr;
    TRAP(err, iRepository = CRepository::NewL(KUidRepository));
    intstr = QString::number(err);
    if(err) {
        delete iRepository;
        return err;
    }
    err = iRepository->Set(key, newkeyvalue);
    intstr = QString::number(err);
    if(err) {
        delete iRepository;
        return err;
    }
    delete iRepository;
    return err;
}

TInt QCenRep::ChangeValStr(const TUid KUidRepository, TUint32 key, const QString newkeyvalue){
    TInt err;
    TBuf<254> tbuf(newkeyvalue.utf16());
    CRepository* iRepository = 0;
    QString intstr;
    TRAP(err, iRepository = CRepository::NewL(KUidRepository));
    intstr = QString::number(err);
    if(err) {
        delete iRepository;
        return err;
    }
    err = iRepository->Set(key, tbuf);
    intstr = QString::number(err);
    if(err) {
        delete iRepository;
        return err;
    }
    delete iRepository;
    return err;
}

TInt QCenRep::ReadValInt(const TUid KUidRepository, TUint32 key){
    TInt err;
    TInt val;
    QString intstr;
    CRepository* iRepository = 0;
    TRAP(err, iRepository = CRepository::NewL(KUidRepository));
    intstr = QString::number(err);
    if(err) {
        delete iRepository;
        return err;
    }
    err = iRepository->Get(key, val);
    intstr = QString::number(err);
    if(err) {
        delete iRepository;
        return err;
    }
    delete iRepository;
    return val;
}

TInt QCenRep::ReadValStr(const TUid KUidRepository, TUint32 key, QString* retval){
    TInt err = 0;
    TBuf<254> val;
    QString intstr;
    CRepository* iRepository = 0;
    TRAP(err, iRepository = CRepository::NewL(KUidRepository));
    intstr = QString::number(err);
    if(err) {
        delete iRepository;
        return err;
    }
    err = iRepository->Get(key, val);
    intstr = QString::number(err);
    if(err) {
        delete iRepository;
        return err;
    }
    delete iRepository;
    retval->insert(0, (QChar*) val.Ptr(),val.Length());
    return err;
}

TInt QCenRep::CreateValInt(const TUid KUidRepository, TUint32 key, const TInt newkeyvalue){
    TInt err;
    CRepository* iRepository = 0;
    QString intstr;
    TRAP(err, iRepository = CRepository::NewL(KUidRepository));
    intstr = QString::number(err);
    if(err) {
        delete iRepository;
        return err;
    }
    err = iRepository->Create(key, newkeyvalue);
    intstr = QString::number(err);
    if(err) {
        delete iRepository;
        return err;
    }
    delete iRepository;
    return err;
}
