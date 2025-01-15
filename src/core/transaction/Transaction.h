#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include "LockManager.h"
#include "Table.h"

namespace db {
    class Transaction {
    public:
        enum OperationType { INSERT, UPDATE, DELETE };

        struct Operation {
            OperationType type;
            int recordID;
            Record data; // for DELETE and UPDATE
        };

        Transaction(LockManager& lockManager);
        ~Transaction();

        void begin();
        void commit();
        void rollback();

        bool insertRecord(Table& table, const Record& record);
        bool updateRecord(Table& table, int recordID, const Record& record);
        bool deleteRecord(Table& table, int recordID);

    private:
        static int nextTransactionID;
        int transactionID;
        LockManager& lockManager;
        std::vector<Operation> rollbackJournal;
        bool isActive;
    };
}

#endif // TRANSACTION_H