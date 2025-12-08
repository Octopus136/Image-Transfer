#include "DefaultProgressControl.h"

namespace ImgSizer {

void DefaultProgressControl::Report(double ratio) {
	if (m_ctx) {
        m_ctx->UpdateImageProgress(m_index, ratio);
    }
}

}