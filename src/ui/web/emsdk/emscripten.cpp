#include "emscripten.hpp"
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include "time_event_system.hpp"
#include "operation.hpp"

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    EM_JS(void, JS_UpdateMatrix, (size_t x, size_t y,
         unsigned char target_enum), {
          const col = y;   // [0,10]
          const row = x;   // [0,18]
          const block = document.getElementById('matrix-block-' + row + '-' + col);

          if(block) {
              if(target_enum !== 0) {
                  block.style.backgroundColor = '#f0f0f0';
              } else {
                  block.style.backgroundColor = 'transparent';
              }
          }

      });

    EMSCRIPTEN_KEEPALIVE
    void output_in_JS(MatrixStateManager::ProcessData data) {

        auto& bit_map = data.bit_mask;
        auto& matrix = data.matrix;
        for(size_t i = 0; i < bmatrix_prop.x_size; ++i) {
            for(size_t j = 0; j < bmatrix_prop.y_size; ++j) {
                if(data.bit_mask.is_dirty(i,j)) {
                    auto target_type = static_cast<unsigned char>(matrix.get_block(i,j));
                    JS_UpdateMatrix(i,j,target_type);
                }
            }
        }
    }

    extern std::unique_ptr<OperationQueue> op_q;

    EMSCRIPTEN_KEEPALIVE
    void do_operation(int op_num) {
        op_q -> push(static_cast<Operation>(op_num));
    }

}






