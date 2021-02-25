// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "absl/container/node_hash_map.h"
#include "mediapipe/calculators/util/detection_label_id_to_text_calculator.pb.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/detection.pb.h"
#include "mediapipe/framework/packet.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/util/resource_util.h"

namespace mediapipe {

  void init_map(absl::node_hash_map<int, std::string>& map)
  {
    map.insert({
      {0,"???"},
      {1,"Container"},
      {2,"Ambulance"},
      {3,"Ladder"},
      {4,"Toothbrush"},
      {5,"Sink"},
      {6,"Cassette deck"},
      {7,"Beer"},
      {8,"Parking meter"},
      {9,"Traffic light"},
      {10,"Washing machine"},
      {11,"Sunglasses"},
      {12,"Ball"},
      {13,"Backpack"},
      {14,"Bicycle"},
      {15,"Home appliance"},
      {16,"Boat"},
      {17,"Boot"},
      {18,"Headphones"},
      {19,"Bus"},
      {20,"Screwdriver"},
      {21,"Laptop"},
      {22,"Teapot"},
      {23,"Person"},
      {24,"Swimwear"},
      {25,"Balloon"},
      {26,"Wrench"},
      {27,"Vehicle registration plate"},
      {28,"Lantern"},
      {29,"Toaster"},
      {30,"Flashlight"},
      {31,"Billboard"},
      {32,"Limousine"},
      {33,"Necklace"},
      {34,"Scissors"},
      {35,"Stairs"},
      {36,"Computer keyboard"},
      {37,"Printer"},
      {38,"Traffic sign"},
      {39,"Chair"},
      {40,"Poster"},
      {41,"Fire hydrant"},
      {42,"Land vehicle"},
      {43,"Cabinetry"},
      {44,"Suitcase"},
      {45,"Snowmobile"},
      {46,"Clock"},
      {47,"Cattle"},
      {48,"Cello"},
      {49,"Desk"},
      {50,"Cat"},
      {51,"Computer mouse"},
      {52,"Calculator"},
      {53,"Computer monitor"},
      {54,"Box"},
      {55,"Stapler"},
      {56,"Studio couch"},
      {57,"Drum"},
      {58,"Dice"},
      {59,"Oven"},
      {60,"Couch"},
      {61,"Whiteboard"},
      {62,"Door"},
      {63,"Hat"},
      {64,"Eraser"},
      {65,"Tin can"},
      {66,"Mug"},
      {67,"Can opener"},
      {68,"Goggles"},
      {69,"Roller skates"},
      {70,"Coffee cup"},
      {71,"Cutting board"},
      {72,"Blender"},
      {73,"Stop sign"},
      {74,"Volleyball"},
      {75,"Vase"},
      {76,"Slow cooker"},
      {77,"Wardrobe"},
      {78,"Paper towel"},
      {79,"Sun hat"},
      {80,"Tree house"},
      {81,"Gas stove"},
      {82,"Salt and pepper shakers"},
      {83,"Mechanical fan"},
      {84,"Fax"},
      {85,"Nightstand"},
      {86,"Barrel"},
      {87,"Guitar"},
      {88,"Pillow"},
      {89,"Stationary bicycle"},
      {90,"Hammer"},
      {91,"Ceiling fan"},
      {92,"Sofa bed"},
      {93,"Sandal"},
      {94,"Bicycle helmet"},
      {95,"Bed"},
      {96,"Kettle"},
      {97,"Hair dryer"},
      {98,"Kitchenware"},
      {99,"Bookcase"},
      {100,"Refrigerator"},
      {101,"Alarm clock"},
      {102,"Filing cabinet"},
      {103,"Table"},
      {104,"Knife"},
      {105,"Bottle"},
      {106,"Dumbbell"},
      {107,"Bowl"},
      {108,"Billiard table"},
      {109,"Motorcycle"},
      {110,"Frying pan"},
      {111,"Bathroom cabinet"},
      {112,"Plate"},
      {113,"Mobile phone"},
      {114,"Table tennis racket"},
      {115,"Musical keyboard"},
      {116,"Scoreboard"},
      {117,"Briefcase"},
      {118,"Kitchen knife"},
      {119,"Piano"},
      {120,"Pumpkin"},
      {121,"Infant bed"},
      {122,"Mixer"},
      {123,"Cupboard"},
      {124,"Digital clock"},
      {125,"Rifle"},
      {126,"Skateboard"},
      {127,"High heels"},
      {128,"Snowboard"},
      {129,"Sword"},
      {130,"Training bench"},
      {131,"Coffee table"},
      {132,"Television"},
      {133,"Trombone"},
      {134,"Tank"},
      {135,"Telephone"},
      {136,"Trumpet"},
      {137,"Train"},
      {138,"Picnic basket"},
      {139,"Football helmet"},
      {140,"Truck"},
      {141,"Measuring cup"},
      {142,"Coffeemaker"},
      {143,"Violin"},
      {144,"Vehicle"},
      {145,"Wine"},
      {146,"Wheel"},
      {147,"Jug"},
      {148,"Toilet"},
      {149,"Clothing"},
      {150,"Footwear"},
      {151,"Tablet computer"},
      {152,"Dog"},
      {153,"Book"},
      {154,"Candle"},
      {155,"Hand dryer"},
      {156,"Soap dispenser"},
      {157,"Furniture"},
      {158,"Airplane"},
      {159,"Spoon"},
      {160,"Bench"},
      {161,"Window"},
      {162,"Closet"},
      {163,"Fork"},
      {164,"Lamp"},
      {165,"Camera"},
      {166,"Racket"},
      {167,"Human face"},
      {168,"Unicycle"},
      {169,"Flowerpot"},
      {170,"Drawer"},
      {171,"Stool"},
      {172,"Microwave oven"},
      {173,"Shelf"},
      {174,"Handgun"},
      {175,"Van"},
      {176,"Corded phone"},
      {177,"Tennis racket"},
      {178,"Wall clock"},
      {179,"Kitchen & dining room table"},
      {180,"Pressure cooker"},
      {181,"Kitchen appliance"},
      {182,"Tire"},
      {183,"Luggage and bags"},
      {184,"Microphone"},
      {185,"Glasses"},
      {186,"Pen"},
      {187,"Car"},
      {188,"Aircraft"},
      {189,"Dishwasher"},
      {190,"Binoculars"},
      {191,"Rays and skates"},
      {192,"Remote control"},
      {193,"Wheelchair"},
      {194,"Helmet"}});
  }

// Takes a label map (from label IDs to names), and replaces the label IDs
// in Detection protos with label names. Note that the calculator makes a copy
// of the input detections. Consider using it only when the size of input
// detections is small.
//
// Example usage:
// node {
//   calculator: "UnityDetectionLabelIdToTextCalculator"
//   input_stream: "input_detections"
//   output_stream: "output_detections"
//   node_options: {
//     [type.googleapis.com/mediapipe.UnityDetectionLabelIdToTextCalculatorOptions] {
//       label_map_path: "labelmap.txt"
//     }
//   }
// }
class UnityDetectionLabelIdToTextCalculator : public CalculatorBase {
 public:
  static mediapipe::Status GetContract(CalculatorContract* cc);

  mediapipe::Status Open(CalculatorContext* cc) override;
  mediapipe::Status Process(CalculatorContext* cc) override;

 private:
  absl::node_hash_map<int, std::string> label_map_;
};
REGISTER_CALCULATOR(UnityDetectionLabelIdToTextCalculator);

mediapipe::Status UnityDetectionLabelIdToTextCalculator::GetContract(
    CalculatorContract* cc) {
  LOG(INFO) << __PRETTY_FUNCTION__;
  cc->Inputs().Index(0).Set<std::vector<Detection>>();
  cc->Outputs().Index(0).Set<std::vector<Detection>>();

  return mediapipe::OkStatus();
}

mediapipe::Status UnityDetectionLabelIdToTextCalculator::Open(
    CalculatorContext* cc) {
  LOG(INFO) << __PRETTY_FUNCTION__;
  cc->SetOffset(TimestampDiff(0));

  init_map(label_map_);

  return mediapipe::OkStatus();
}

mediapipe::Status UnityDetectionLabelIdToTextCalculator::Process(
    CalculatorContext* cc) {
  LOG(INFO) << __PRETTY_FUNCTION__;
  std::vector<Detection> output_detections;
  for (const auto& input_detection :
       cc->Inputs().Index(0).Get<std::vector<Detection>>()) {
    output_detections.push_back(input_detection);
    Detection& output_detection = output_detections.back();
    bool has_text_label = false;
    for (const int32 label_id : output_detection.label_id()) {
      LOG(INFO) << "Detected object with label id " << label_id;
      if (label_map_.find(label_id) != label_map_.end()) {
        output_detection.add_label(label_map_[label_id]);
        has_text_label = true;
        LOG(INFO) << "Detected object called '" << label_map_[label_id] << "'.";
      }
    }
    // Remove label_id field if text labels exist.
    if (has_text_label) {
      output_detection.clear_label_id();
    }
  }
  cc->Outputs().Index(0).AddPacket(
      MakePacket<std::vector<Detection>>(output_detections)
          .At(cc->InputTimestamp()));
  return mediapipe::OkStatus();
}

}  // namespace mediapipe
