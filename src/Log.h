//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_LOG_H
#define VERINET_LOG_H

namespace veri {

class Log {

};

}

#define LOG_INFO(fmt, ...) fprintf(stderr, "[INFO][%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) fprintf(stderr, "[FATAL][%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);abort();


#endif //VERINET_LOG_H
