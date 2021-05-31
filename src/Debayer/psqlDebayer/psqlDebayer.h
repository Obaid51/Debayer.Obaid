#include <pthread.h>
#include <pqxx/pqxx>
#include "gRPC/buffer.h"
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <stack>
#include "atomic"
#include "stdlib.h"

class psqlDebayer
 {
public:
    psqlDebayer();
    ~psqlDebayer();
    pthread_t mThread;
    pthread_cond_t meta_sended;
    pthread_mutex_t meta_mtx;
    std::stack<imageMetaInfo> mMeta;
    static psqlDebayer* startThread();
    static void stopThread(psqlDebayer*);

    std::atomic_bool needStop;
 };
void *send_to_db(void*);
