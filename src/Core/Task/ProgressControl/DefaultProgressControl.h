#pragma once

#include "BasicProgressControl.h"
#include "ProgressContext.h"

namespace ImgSizer {

class DefaultProgressControl : public BasicProgressControl {
public:
    DefaultProgressControl(ProgressContext* ctx, int imageIndex)
        : m_ctx(ctx), m_index(imageIndex)
    {}

    void Report(double ratio) override;

private:
    ProgressContext* m_ctx = nullptr;
    int m_index = 0;
};

}