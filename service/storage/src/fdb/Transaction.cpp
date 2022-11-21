#include "Transaction.h"
#include <spdlog/spdlog.h>

namespace minecpp::service::storage::fdb {

Transaction::Transaction(FDBTransaction *transaction) :
    m_transaction{transaction}
{
}

Transaction::~Transaction()
{
   if (m_transaction != nullptr) {
      fdb_transaction_destroy(m_transaction);
   }
}

void Transaction::set(std::string_view key, Buffer buffer)
{
   fdb_transaction_set(m_transaction, reinterpret_cast<const uint8_t *>(key.data()),
                       static_cast<int>(key.size()), reinterpret_cast<const uint8_t *>(buffer.data),
                       static_cast<int>(buffer.size));
}

Future Transaction::commit()
{
   return Future(fdb_transaction_commit(m_transaction));
}

Future Transaction::get(std::string_view key)
{
   return Future{fdb_transaction_get(m_transaction, reinterpret_cast<const uint8_t *>(key.data()),
                                     static_cast<int>(key.size()), false)};
}

Transaction::Transaction(Transaction &&other) noexcept :
    m_transaction(std::exchange(other.m_transaction, nullptr))
{
}

Transaction &Transaction::operator=(Transaction &&other) noexcept
{
   m_transaction = std::exchange(other.m_transaction, nullptr);
   return *this;
}

}// namespace minecpp::service::storage::fdb
