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

load("//mediapipe/examples/unity:embed_graph.bzl", "mediapipe_embed_graph")

cc_library(
    name = "export_header",
    hdrs = ["export.h"]
)

cc_library(
    name = "unity_detection_label_id_to_text_calculator",
    srcs = ["unity_detection_label_id_to_text_calculator.cc"],
    deps = [
        ":export_header",
        "//mediapipe/calculators/util:detection_label_id_to_text_calculator_cc_proto",
        "//mediapipe/framework/formats:detection_cc_proto",
        "@com_google_absl//absl/container:node_hash_map",
        "//mediapipe/framework/port:status",
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework:packet",
        "//mediapipe/util:resource_util",
    ] + select({
        "//mediapipe:android": [
            "//mediapipe/util/android/file/base",
        ],
        "//mediapipe:ios": [
            "//mediapipe/util/android/file/base",
        ],
        "//mediapipe:macos": [
            "//mediapipe/framework/port:file_helpers",
        ],
        "//conditions:default": [
            "//mediapipe/framework/port:file_helpers",
        ],
    }),
    alwayslink = 1,
)

cc_library(
    name = "unity_output_calculator",
    srcs = ["unity_output_calculator.cc"],
    deps = [
        ":export_header",
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:landmark_registration",
        "//mediapipe/framework/formats:rect_registration",
        "//mediapipe/framework/port:status",
        "//mediapipe/framework/tool:status_util"
    ],
    alwayslink = 1
)

cc_library(
    name = "unity_video_calculator",
    srcs = ["unity_video_calculator.cc"],
    deps = [
        ":export_header",
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:image_frame",
        "//mediapipe/framework/port:status",
        "//mediapipe/framework/tool:status_util"
    ],
    alwayslink = 1
)

cc_library(
    name = "unity_calculators",
    deps = [
        ":unity_detection_label_id_to_text_calculator",
        ":unity_output_calculator",
        ":unity_video_calculator"
    ]
)

cc_library(
    name = "entry_point",
    srcs = ["simple_run_graph_main.cc"],
    deps = [
        ":export_header",
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/port:file_helpers",
        "//mediapipe/framework/port:map_util",
        "//mediapipe/framework/port:parse_text_proto",
    ]
)

mediapipe_embed_graph(
    name = "objectron_unity_cpu",
    graph = "//mediapipe/examples/unity:objectron_unity_cpu.pbtxt",
    register_as = "UnityObjectronCpuGraph",
    deps = [
        ":unity_calculators",
        "//mediapipe/calculators/core:constant_side_packet_calculator",
    ]
)

cc_library(
    name = "graph_interop",
    srcs = ["graph_interop.cc"],
    deps = [
        ":export_header",
        ":objectron_unity_cpu",
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/port:parse_text_proto",
        "//mediapipe/framework/port:status",
        "//mediapipe/framework/tool:status_util"
    ],
    alwayslink = 1
)

cc_binary(
    name = "libmediapipe_unity.so",
    linkshared = 1,
    #data = ["//mediapipe/examples/android/src/java/com/google/mediapipe/apps/objectdetection3d:binary_graph"],
    deps = [
        ":entry_point",
        ":export_header",
        ":unity_calculators",
        ":graph_interop",
        "//mediapipe/calculators/core:constant_side_packet_calculator",
        "//mediapipe/calculators/tflite:tflite_model_calculator",
        "//mediapipe/examples/unity/subgraphs:unity_subgraphs",
        #"//mediapipe/modules/objectron:objectron_cpu",
        #"//mediapipe/graphs/object_detection_3d:desktop_cpu_calculators",
        #"//mediapipe/graphs/object_detection_3d:mobile_calculators",
    ],
)

cc_library(
    name = "unity",
    alwayslink = 1,
    deps = [":libmediapipe_unity.so"]
)
