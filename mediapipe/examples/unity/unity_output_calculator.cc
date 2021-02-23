#include <stdlib.h>

#include <vector>

#include "export.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_format.pb.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/formats/landmark.pb.h"
#include "mediapipe/framework/formats/rect.pb.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/tool/status_util.h"

namespace unity {
  using namespace mediapipe;

namespace
{
  constexpr char kOutputLandmarksTag[] = "MULTI_LANDMARKS";
  constexpr char kOutputNormRectsTag[] = "NORM_RECTS";

}  // namespace

class UnityOutputCalculator : public CalculatorBase {
 public:

  static mediapipe::Status GetContract(CalculatorContract* cc) {
    cc->Inputs().Tag(kOutputLandmarksTag).Set<std::vector<::mediapipe::NormalizedLandmarkList>>();
    cc->Inputs().Tag(kOutputNormRectsTag).Set<std::vector<NormalizedRect>>();
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
