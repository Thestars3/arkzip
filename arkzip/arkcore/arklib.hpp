#ifndef ARKLIB_HPP
#define ARKLIB_HPP

#include "ArkLibrary.hpp"
#include <QFile>
#include <QString>
#include <QPointer>

class Unhv3;
class IArkEvent;

class ArkLib :
        public CArkLib
{
public:
    ArkLib();
    void SetPassword(const QString &password);
    void Destroy();
    BOOL32 Open(QFile *file);
    BOOL32 ExtractAllTo(const QString &path);
    BOOL32 ExtractOneAs(int index, const QString &filePathName);
    virtual int GetFileItemCount() const;
    virtual void Close();
    virtual ARKERR GetLastError() const;
    virtual BOOL32 IsOpened() const;
    virtual BOOL32 SetEvent(IArkEvent *pProgress);
    virtual BOOL32 TestArchive();
    virtual const SArkFileItem* GetFileItem(int index) const;

private:
    QPointer<Unhv3> unhv3_;
    IArkEvent *iArkEvent_;

};

#endif // ARKLIB_HPP
