//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_NOCOPYABLE_H
#define VERINET_NOCOPYABLE_H

namespace veri {

class nocopyable {
  public:
    nocopyable() = default;
    nocopyable(const nocopyable &) = delete;
    nocopyable(nocopyable &&) = delete;

    nocopyable& operator= (const nocopyable &) = delete;
    nocopyable& operator= (nocopyable &&) = delete;

};

}


#endif //VERINET_NOCOPYABLE_H
