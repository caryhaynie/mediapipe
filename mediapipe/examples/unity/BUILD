# Copyright 2019 The MediaPipe Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

licenses(["notice"])

package(default_visibility = [
    "//visibility:public",
])

cc_library(
    name = "export_header",
    hdrs = ["export.h"]
)

cc_library(
    name = "unity_output_calculator",
    srcs = ["unity_output_calculator.cc"],
    deps = [
        ":export_header",
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:image_frame",
        "//mediapipe/framework/formats:image_frame_opencv",
        "//mediapipe/framework/port:parse_text_proto",
        "//mediapipe/framework/port:status",
        "//mediapipe/framework/tool:status_util"
    ],
)

cc_library(
    name = "unity_video_calculator",
    srcs = ["unity_video_calculator.cc"],
    deps = [
        ":export_header",
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:image_frame",
        "//mediapipe/framework/formats:image_frame_opencv",
        "//mediapipe/framework/port:parse_text_proto",
        "//mediapipe/framework/port:status",
        "//mediapipe/framework/tool:status_util"
    ],
)

cc_library(
    name = "unity_calculators",
    deps = [
        ":unity_output_calculator",
        ":unity_video_calculator"
    ]
)

cc_binary(
    name = "libmediapipe_unity.so",
    linkshared = 1,
    srcs = ["simple_run_graph_main.cc"],
    data = ["//mediapipe/examples/android/src/java/com/google/mediapipe/apps/objectdetection3d:binary_graph"],
    deps = [
        ":export_header",
        "//mediapipe/graphs/object_detection_3d:desktop_cpu_calculators",
        "//mediapipe/graphs/object_detection_3d:mobile_calculators",
        ":unity_calculators"
    ],
)

cc_library(
    name = "unity",
    alwayslink = 1,
    deps = [":libmediapipe_unity.so"]
)