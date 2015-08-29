//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_BUFFER_H
#define VERINET_BUFFER_H

#include <vector>
#include <string>
#include <cassert>

namespace veri {

class Buffer {
  public:
    Buffer();
    ~Buffer();

    void append(const char *data, std::size_t len);
    void append(const std::string &str);

    std::string retrive_all();

    std::size_t size() const { assert(write_pos_ >= read_pos_); return write_pos_ - read_pos_; }
    bool empty() const { return read_pos_ == write_pos_; }


  private:

    void ensure_size(std::size_t more);

    std::vector<char> buffer_;
    std::size_t read_pos_;
    std::size_t write_pos_;


};

}


#endif //VERINET_BUFFER_H
