#ifndef QCenRep_H
#define QCenRep_H

#include <QString>

/*
 thanks faenil for his cenrep example code from:
 https://github.com/faenil/i8910tuning/blob/master/i8910tuning.cpp

  How to use it:
    - all calls are static

    - to get a CenRep key's value use this format:

            getCenrep(int iUID, int iKey);
            getCenrep(QString iUID, QString iKey);
            getCenrep(char *iUID, char *iKey);

      it always will return a QString, you don't have to care about the original format (int or string). If the key doesn't exist you will get "Missing key!"

    - to set a new value:

            setCenrep(int iUID, int iKey, QString qValue);
            setCenrep(int iUID, int iKey, const char *qValue);
            setCenrep(QString iUID, QString iKey, QString qValue);
            setCenrep(const char *iUID, const char *iKey, const char *qValue);

       the type of the Value (string or int) gets detected, you don't have to worry about it.

Example code:

    get the current product improvment status:

        qDebug() << QCenRep::getCenrep(0x2003e081, 0x1);
        qDebug() << QCenRep::getCenrep(QString("0x2003e081"), QString("0x1"));
        qDebug() << QCenRep::getCenrep("0x2003e081", "0x1");

    disable product improvment:

        QCenRep::setCenrep(0x2003e081, 0x1, QString("0"));
        QCenRep::setCenrep(0x2003e081, 0x1, "0");
        QCenRep::setCenrep(QString("0x2003e081"), QString("0x1"), QString("0"));
        QCenRep::setCenrep("0x2003e081", "0x1", "0");
*/


class QCenRep
{

public:

    static QString getCenrep(int iUID, int iKey);
    static QString getCenrep(QString iUID, QString iKey);
    static QString getCenrep(char *iUID, char *iKey);

    static void setCenrep(int iUID, int iKey, QString qValue);
    static void setCenrep(int iUID, int iKey, const char *qValue);
    static void setCenrep(QString iUID, QString iKey, QString qValue);
    static void setCenrep(const char *iUID, const char *iKey, const char *qValue);

private:

    static TInt ChangeValInt(const TUid KUidRepository, TUint32 key, const TInt newkeyvalue);
    static TInt ReadValInt(const TUid KUidRepository, TUint32 key);
    static TInt ChangeValStr(const TUid KUidRepository, TUint32 key, const QString newkeyvalue);
    static TInt ReadValStr(const TUid KUidRepository, TUint32 key, QString* retval);
    static TInt CreateValInt(const TUid KUidRepository, TUint32 key, const TInt newkeyvalue);

};

#endif // QCenRep_H
