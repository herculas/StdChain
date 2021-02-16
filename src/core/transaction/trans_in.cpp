#include "core/transaction/trans_in.h"

TxIn::TxIn() {
    this->sequence = TxIn::SEQUENCE_FINAL;
}
