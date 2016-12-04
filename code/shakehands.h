#ifndef SHAKEHANDS_H
#define SHAKEHANDS_H

#include <QObject>
#include <QDebug>

class ShakeHands : public QObject
{
    Q_OBJECT
    public:
        explicit ShakeHands(QObject *parent = 0);
        int updateColor;
    signals:
        void cppReturnAnswer(QVariant data);
        void cppReturnAnswer0(QVariant data);
        void cppReturnAnswer1(QVariant data);
        void cppReturnAnswer2(QVariant data);
        void cppReturnAnswer3(QVariant data);
        void cppReturnAnswer4(QVariant data);
        void cppReturnAnswer5(QVariant data);
        void cppReturnAnswer6(QVariant data);
        void cppReturnAnswer7(QVariant data);
        void cppReturnAnswer8(QVariant data);
        void cppReturnAnswer9(QVariant data);
        void cppReturnAnswer10(QVariant data);
        void cppReturnAnswer11(QVariant data);
        void cppReturnAnswer12(QVariant data);
        void cppReturnAnswer13(QVariant data);
        void cppReturnAnswer14(QVariant data);
        void cppReturnAnswer15(QVariant data);
        void cppReturnAnswer16(QVariant data);
        void cppReturnAnswer17(QVariant data);
        void cppReturnAnswer18(QVariant data);
        void cppReturnAnswer19(QVariant data);
        void cppReturnAnswer20(QVariant data);
        void cppReturnAnswer21(QVariant data);
        void cppReturnAnswer22(QVariant data);
        void cppReturnAnswer23(QVariant data);
    public slots:
        void cppGetRequest(const QString &msg);

};

#endif // SHAKEHANDS_H
