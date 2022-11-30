#pragma once
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
