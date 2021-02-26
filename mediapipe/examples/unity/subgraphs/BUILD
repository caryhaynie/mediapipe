# Copyright 2020 The MediaPipe Authors.
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

load(
    "//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

licenses(["notice"])

package(default_visibility = ["//visibility:private"])

mediapipe_simple_subgraph(
    name = "box_landmark_gpu",
    graph = "box_landmark_gpu.pbtxt",
    register_as = "UnityBoxLandmarkSubgraphGpu",
    deps = [
        "//mediapipe/calculators/core:gate_calculator",
        "//mediapipe/calculators/core:split_vector_calculator",
        "//mediapipe/calculators/image:image_properties_calculator",
        "//mediapipe/calculators/tensor:image_to_tensor_calculator",
        "//mediapipe/calculators/tensor:inference_calculator",
        "//mediapipe/calculators/tensor:tensors_to_floats_calculator",
        "//mediapipe/calculators/tensor:tensors_to_landmarks_calculator",
        "//mediapipe/calculators/util:detections_to_rects_calculator",
        "//mediapipe/calculators/util:landmark_letterbox_removal_calculator",
        "//mediapipe/calculators/util:landmark_projection_calculator",
        "//mediapipe/calculators/util:landmarks_to_detection_calculator",
        "//mediapipe/calculators/util:rect_transformation_calculator",
        "//mediapipe/calculators/util:thresholding_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "object_detection_oid_v4_cpu",
    graph = "object_detection_oid_v4_cpu.pbtxt",
    register_as = "UnityObjectDetectionOidV4SubgraphCpu",
    deps = [
        "//mediapipe/calculators/image:image_transformation_calculator",
        "//mediapipe/calculators/tflite:ssd_anchors_calculator",
        "//mediapipe/calculators/tflite:tflite_converter_calculator",
        "//mediapipe/calculators/tflite:tflite_inference_calculator",
        "//mediapipe/calculators/tflite:tflite_tensors_to_detections_calculator",
        "//mediapipe/examples/unity:unity_detection_label_id_to_text_calculator",
        "//mediapipe/calculators/util:non_max_suppression_calculator",
        "//mediapipe/modules/objectron/calculators:filter_detection_calculator",
    ],
)

mediapipe_simple_subgraph(
    name = "object_detection_oid_v4_gpu",
    graph = "object_detection_oid_v4_cpu.pbtxt",
    register_as = "UnityObjectDetectionOidV4SubgraphGpu",
    deps = [
        "//mediapipe/calculators/image:image_transformation_calculator",
        "//mediapipe/calculators/tflite:ssd_anchors_calculator",
        "//mediapipe/calculators/tflite:tflite_converter_calculator",
        "//mediapipe/calculators/tflite:tflite_inference_calculator",
        "//mediapipe/calculators/tflite:tflite_tensors_to_detections_calculator",
        "//mediapipe/examples/unity:unity_detection_label_id_to_text_calculator",
        "//mediapipe/calculators/util:non_max_suppression_calculator",
        "//mediapipe/modules/objectron/calculators:filter_detection_calculator",
    ],
)


mediapipe_simple_subgraph(
    name = "objectron_cpu",
    graph = "objectron_cpu.pbtxt",
    register_as = "UnityObjectronCpuSubgraph",
    deps = [
        "//mediapipe/modules/objectron:box_landmark_cpu",
        ":object_detection_oid_v4_cpu",
        "//mediapipe/calculators/core:begin_loop_calculator",
        "//mediapipe/calculators/core:clip_vector_size_calculator",
        "//mediapipe/calculators/core:constant_side_packet_calculator",
        "//mediapipe/calculators/core:end_loop_calculator",
        "//mediapipe/calculators/core:gate_calculator",
        "//mediapipe/calculators/core:previous_loopback_calculator",
        "//mediapipe/calculators/image:image_properties_calculator",
        "//mediapipe/calculators/util:association_norm_rect_calculator",
        "//mediapipe/calculators/util:collection_has_min_size_calculator",
        "//mediapipe/calculators/util:detections_to_rects_calculator",
        "//mediapipe/modules/objectron/calculators:frame_annotation_to_rect_calculator",
        "//mediapipe/modules/objectron/calculators:landmarks_to_frame_annotation_calculator",
        "//mediapipe/modules/objectron/calculators:lift_2d_frame_annotation_to_3d_calculator",
    ],
)

cc_library(
    name = "unity_cpu_subgraphs",
    deps = [
        ":object_detection_oid_v4_cpu",
        ":objectron_cpu"
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "unity_gpu_subgraphs",
    deps = [
        ":box_landmark_gpu",
        ":object_detection_oid_v4_gpu"
    ],
    visibility = ["//visibility:public"]
)
