//
// Author: Yao Han <verihy@gmail.com>
// 

#include <Buffer.h>
#include <cstring>


veri::Buffer::Buffer(): buffer_(1024), read_pos_(0), write_pos_(0) {

}


veri::Buffer::~Buffer() {

}


void veri::Buffer::ensure_size(std::size_t more) {
    if (write_pos_ + more > buffer_.size()) {
        if (read_pos_ + buffer_.size() - write_pos_ >= more) {
            std::copy(buffer_.begin() + read_pos_, buffer_.begin() + write_pos_, buffer_.begin());
            auto tmp = size();
            read_pos_ = 0;
            write_pos_ = tmp;
        } else {
            buffer_.resize(write_pos_ + more);
        }
    }
}

void veri::Buffer::append(const char *data, std::size_t len) {
    ensure_size(len);
    std::copy(data, data + len, buffer_.begin() + write_pos_);
    write_pos_ += len;
}


void veri::Buffer::append(const std::string &str) {
    append(str.data(), str.size());
}


std::string veri::Buffer::retrive_all() {
    auto ret = std::string(&*(buffer_.begin() + read_pos_), size());
    read_pos_ = write_pos_ = 0;
    return ret;
}
