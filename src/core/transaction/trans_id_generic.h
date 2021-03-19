#ifndef STDCHAIN_CORE_TRANSACTION_ID_GENERIC_H
#define STDCHAIN_CORE_TRANSACTION_ID_GENERIC_H

#include "type/blob/blob_256.h"

class TxIDGeneric {

private:
    bool isWitnessTxID;
    Blob256 hash;

public:
    TxIDGeneric(bool isWitnessTxID, const Blob256 &hash);

    [[nodiscard]] bool isWitnessTransID() const;
    [[nodiscard]] const Blob256 &getHash() const;

    friend bool operator==(const TxIDGeneric &a, const TxIDGeneric &b);
    friend bool operator<(const TxIDGeneric &a, const TxIDGeneric &b);

};


#endif //STDCHAIN_CORE_TRANSACTION_ID_GENERIC_H
