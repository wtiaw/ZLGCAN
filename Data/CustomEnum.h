#pragma once
#include <qmetaobject.h>
#include <QObject>

namespace CustomEnum
{
    Q_NAMESPACE

    enum EFormType
    {
        None = 0,
        ACR_E11,
        ACR_H53,
    };

    Q_ENUM_NS(EFormType)
};

template <typename EnumClass>
QString GetEnumKeyStr(const int value)
{
    return QMetaEnum::fromType<EnumClass>().valueToKey(value);
}
