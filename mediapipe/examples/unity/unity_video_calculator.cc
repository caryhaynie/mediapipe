#include <stdlib.h>

#include "export.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_format.pb.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/tool/status_util.h"

namespace unity {
  using namespace mediapipe;

namespace
{
    typedef void(*on_open_t)(void);
    typedef void(*on_process_t)(void);
    typedef void(*on_close_t)(void);
    typedef ImageFrame*(*get_image_frame_t)(uint64_t* timestampInMicrosecondsOut);
}  // namespace

// This Calculator takes no input streams and produces video packets.
// All streams and input side packets are specified using tags and all of them
// are optional.
//
// Output Streams:
//   VIDEO: Output video frames (ImageFrame).
//   VIDEO_PRESTREAM:
//       Optional video header information output at
//       Timestamp::PreStream() for the corresponding stream.
// Input Side Packets:
//   INPUT_FILE_PATH: The input file path.
//
// Example config:
// node {
//   calculator: "OpenCvVideoDecoderCalculator"
//   input_side_packet: "INPUT_FILE_PATH:input_file_path"
//   output_stream: "VIDEO:video_frames"
//   output_stream: "VIDEO_PRESTREAM:video_header"
// }
//
// OpenCV's VideoCapture doesn't decode audio tracks. If the audio tracks need
// to be saved, specify an output side packet with tag "SAVED_AUDIO_PATH".
// The calculator will call FFmpeg binary to save audio tracks as an aac file.
// If the audio tracks can't be extracted by FFmpeg, the output side packet
// will contain an empty std::string.
//
// Example config:
// node {
//   calculator: "OpenCvVideoDecoderCalculator"
//   input_side_packet: "INPUT_FILE_PATH:input_file_path"
//   output_side_packet: "SAVED_AUDIO_PATH:audio_path"
//   output_stream: "VIDEO:video_frames"
//   output_stream: "VIDEO_PRESTREAM:video_header"
// }
//
class UnityVideoCalculator : public CalculatorBase {
 public:

  static mediapipe::Status GetContract(CalculatorContract* cc) {
      LOG(INFO) << __PRETTY_FUNCTION__;

    // cc->InputSidePackets().Tag("INPUT_FILE_PATH").Set<std::string>();
    // cc->InputSidePackets().Tag("INPUT_FILE_PATH").Set<std::string>();
    cc->Outputs().Tag("VIDEO").Set<ImageFrame>();
    // if (cc->Outputs().HasTag("VIDEO_PRESTREAM")) {
    //   cc->Outputs().Tag("VIDEO_PRESTREAM").Set<VideoHeader>();
    // }
    // if (cc->OutputSidePackets().HasTag("SAVED_AUDIO_PATH")) {
    //   cc->OutputSidePackets().Tag("SAVED_AUDIO_PATH").Set<std::string>();
    // }
    return mediapipe::OkStatus();
  }

  mediapipe::Status Open(CalculatorContext* cc) override {
      LOG(INFO) << __PRETTY_FUNCTION__;

    // const std::string& input_file_path =
    //     cc->InputSidePackets().Tag("INPUT_FILE_PATH").Get<std::string>();
    // cap_ = absl::make_unique<cv::VideoCapture>(input_file_path);
    // if (!cap_->isOpened()) {
    //   return mediapipe::InvalidArgumentErrorBuilder(MEDIAPIPE_LOC)
    //          << "Fail to open video file at " << input_file_path;
    // }
    // width_ = static_cast<int>(cap_->get(cv::CAP_PROP_FRAME_WIDTH));
    // height_ = static_cast<int>(cap_->get(cv::CAP_PROP_FRAME_HEIGHT));
    // double fps = static_cast<double>(cap_->get(cv::CAP_PROP_FPS));
    // frame_count_ = static_cast<int>(cap_->get(cv::CAP_PROP_FRAME_COUNT));
    // // Unfortunately, cap_->get(cv::CAP_PROP_FORMAT) always returns CV_8UC1
    // // back. To get correct image format, we read the first frame from the video
    // // and get the number of channels.
    // cv::Mat frame;
    // cap_->read(frame);
    // if (frame.empty()) {
    //   return mediapipe::InvalidArgumentErrorBuilder(MEDIAPIPE_LOC)
    //          << "Fail to read any frames from the video file at "
    //          << input_file_path;
    // }
    // format_ = GetImageFormat(frame.channels());
    // if (format_ == ImageFormat::UNKNOWN) {
    //   return mediapipe::InvalidArgumentErrorBuilder(MEDIAPIPE_LOC)
    //          << "Unsupported video format of the video file at "
    //          << input_file_path;
    // }

    // if (fps <= 0 || frame_count_ <= 0 || width_ <= 0 || height_ <= 0) {
    //   return mediapipe::InvalidArgumentErrorBuilder(MEDIAPIPE_LOC)
    //          << "Fail to make video header due to the incorrect metadata from "
    //             "the video file at "
    //          << input_file_path;
    // }
    // auto header = absl::make_unique<VideoHeader>();
    // header->format = format_;
    // header->width = width_;
    // header->height = height_;
    // header->frame_rate = fps;
    // header->duration = frame_count_ / fps;

    // if (cc->Outputs().HasTag("VIDEO_PRESTREAM")) {
    //   cc->Outputs()
    //       .Tag("VIDEO_PRESTREAM")
    //       .Add(header.release(), Timestamp::PreStream());
    //   cc->Outputs().Tag("VIDEO_PRESTREAM").Close();
    // }
    // // Rewind to the very first frame.
    // cap_->set(cv::CAP_PROP_POS_AVI_RATIO, 0);

    return mediapipe::OkStatus();
  }

  mediapipe::Status Process(CalculatorContext* cc) override {
    LOG(INFO) << __PRETTY_FUNCTION__;

    if (GetImageFrame != nullptr)
    {
        uint64_t ts;
        auto imageFrame = GetImageFrame(&ts);
        Timestamp timestamp(ts);
        if (imageFrame != nullptr && prev_timestamp_ < timestamp)
        {
            LOG(INFO) << "Got image frame " << imageFrame->Width() << "x" << imageFrame->Height();
            cc->Outputs().Tag("VIDEO").Add(imageFrame, timestamp);
            prev_timestamp_ = timestamp;
        }
    }

    // auto image_frame = absl::make_unique<ImageFrame>(format_, width_, height_,
    //                                                  /*alignment_boundary=*/1);
    // // Use microsecond as the unit of time.
    // Timestamp timestamp(cap_->get(cv::CAP_PROP_POS_MSEC) * 1000);
    // if (format_ == ImageFormat::GRAY8) {
    //   cv::Mat frame = formats::MatView(image_frame.get());
    //   cap_->read(frame);
    //   if (frame.empty()) {
    //     return tool::StatusStop();
    //   }
    // } else {
    //   cv::Mat tmp_frame;
    //   cap_->read(tmp_frame);
    //   if (tmp_frame.empty()) {
    //     return tool::StatusStop();
    //   }
    //   if (format_ == ImageFormat::SRGB) {
    //     cv::cvtColor(tmp_frame, formats::MatView(image_frame.get()),
    //                  cv::COLOR_BGR2RGB);
    //   } else if (format_ == ImageFormat::SRGBA) {
    //     cv::cvtColor(tmp_frame, formats::MatView(image_frame.get()),
    //                  cv::COLOR_BGRA2RGBA);
    //   }
    // }
    // // If the timestamp of the current frame is not greater than the one of the
    // // previous frame, the new frame will be discarded.
    // if (prev_timestamp_ < timestamp) {
    //   cc->Outputs().Tag("VIDEO").Add(image_frame.release(), timestamp);
    //   prev_timestamp_ = timestamp;
    //   decoded_frames_++;
    // }

    return mediapipe::OkStatus();
  }

  mediapipe::Status Close(CalculatorContext* cc) override {
      LOG(INFO) << __PRETTY_FUNCTION__;

    // if (cap_ && cap_->isOpened()) {
    //   cap_->release();
    // }
    // if (decoded_frames_ != frame_count_) {
    //   LOG(WARNING) << "Not all the frames are decoded (total frames: "
    //                << frame_count_ << " vs decoded frames: " << decoded_frames_
    //                << ").";
    // }
    return mediapipe::OkStatus();
  }

  friend void VideoCalculator_SetCallbacks(on_open_t, on_process_t, on_close_t, get_image_frame_t);

 public:
  static on_open_t OnOpen;
  static on_process_t OnProcess;
  static on_close_t OnClose;
  static get_image_frame_t GetImageFrame;
  Timestamp prev_timestamp_ = Timestamp::Unset();
};

REGISTER_CALCULATOR(UnityVideoCalculator);

on_open_t UnityVideoCalculator::OnOpen = nullptr;
on_process_t UnityVideoCalculator::OnProcess = nullptr;
on_close_t UnityVideoCalculator::OnClose = nullptr;
get_image_frame_t UnityVideoCalculator::GetImageFrame = nullptr;

void VideoCalculator_SetCallbacks(on_open_t onOpen, on_process_t onProcess, on_close_t onClose, get_image_frame_t getImageFrame)
{
    UnityVideoCalculator::OnOpen = onOpen;
    UnityVideoCalculator::OnProcess = onProcess;
    UnityVideoCalculator::OnClose = onClose;
    UnityVideoCalculator::GetImageFrame = getImageFrame;
    LOG(INFO) << "UnityVideoCalculator: Callbacks set";
}

EXPORT(void) UnityMediaPipe_VideoCalculator_SetCallbacks(on_open_t onOpen, on_process_t onProcess, on_close_t onClose, get_image_frame_t getImageFrame)
{
    VideoCalculator_SetCallbacks(onOpen, onProcess, onClose, getImageFrame);
}

EXPORT(ImageFrame*) UnityMediaPipe_ImageFrame_ctor()
{
    return new ImageFrame();
}

EXPORT(void) UnityMediaPipe_ImageFrame_CopyPixelData(ImageFrame* imageFrame, ImageFormat::Format format, int width, int height, int widthStep, const uint8_t* pixelData, uint32_t alignmentBoundary)
{
    imageFrame->CopyPixelData(format, width, height, widthStep, pixelData, alignmentBoundary);
}

}  // namespace mediapipe
