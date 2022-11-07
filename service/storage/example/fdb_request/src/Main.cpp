#define FDB_API_VERSION 630
#include <foundationdb/fdb_c.h>
#include <spdlog/spdlog.h>
#include <thread>

constexpr fdb_error_t FDB_NO_ERROR = 0;

void assert_no_error(fdb_error_t err)
{
   if (err != FDB_NO_ERROR) {
      spdlog::error("FDB error: {}", fdb_get_error(err));
      exit(1);
   }
}

void network_thread()
{
   assert_no_error(fdb_run_network());
}

int main()
{
   assert_no_error(fdb_select_api_version(FDB_API_VERSION));
   assert_no_error(fdb_setup_network());

   std::thread network(network_thread);

   FDBDatabase *database;
   assert_no_error(fdb_create_database("clusterfile-local", &database));

   FDBTransaction *transaction;
   assert_no_error(fdb_database_create_transaction(database, &transaction));

   const char *key = "chunk_subscription.1875062";

   FDBFuture *future = fdb_transaction_get(transaction, reinterpret_cast<const uint8_t *>(key),
                                           static_cast<int>(strlen(key)), false);
   assert_no_error(fdb_future_block_until_ready(future));
   assert_no_error(fdb_future_get_error(future));

   fdb_bool_t is_present = false;

   const uint8_t *data{};
   int data_length{};

   assert_no_error(fdb_future_get_value(future, &is_present, &data, &data_length));

   if (data_length == 0) {
      spdlog::info("data is empty");
   } else {
      spdlog::info("received data: {}", reinterpret_cast<const char *>(data));
   }

   fdb_future_destroy(future);

   fdb_transaction_destroy(transaction);

   fdb_database_destroy(database);

   assert_no_error(fdb_stop_network());
   network.join();
}