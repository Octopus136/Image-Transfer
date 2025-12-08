#pragma once

namespace ImgSizer {

class BasicProgressControl {
public:
    virtual ~BasicProgressControl() = default;
    virtual void Report(double ratio) = 0;
};

}