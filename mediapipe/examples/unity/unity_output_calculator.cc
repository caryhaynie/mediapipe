#include <stdlib.h>

#include "export.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_format.pb.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/tool/status_util.h"

namespace unity {
  using namespace mediapipe;

namespace
{
}  // namespace

class UnityOutputCalculator : public CalculatorBase {
 public:

  static mediapipe::Status GetContract(CalculatorContract* cc) {
    return mediapipe::OkStatus();
  }

  mediapipe::Status Open(CalculatorContext* cc) override {
    return mediapipe::OkStatus();
  }

  mediapipe::Status Process(CalculatorContext* cc) override {
    LOG(INFO) << "Process called on UnityOutputCalculator";
    return mediapipe::OkStatus();
  }

  mediapipe::Status Close(CalculatorContext* cc) override {
    return mediapipe::OkStatus();
  }

  friend void OutputCalculator_SetCallbacks();

 public:
  Timestamp prev_timestamp_ = Timestamp::Unset();
};

REGISTER_CALCULATOR(UnityOutputCalculator);

void OutputCalculator_SetCallbacks()
{
}

}  // namespace mediapipe
