#include <stdlib.h>

#include <vector>

#include "export.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/parse_text_proto.h"

#define LOG_AND_RETURN(CODE) \
    do { \
        const auto result = CODE; \
        LOG(INFO) << __PRETTY_FUNCTION__ << ": " << result; \
        return result; \
    } while (0)

namespace mediapipe {
    StatusOr<CalculatorGraphConfig> LoadUnityObjectronCpuGraphConfig();
}

namespace unity {
    using namespace mediapipe;

class Graph {
public:
    Graph()
    {
        m_Config = mediapipe::LoadUnityObjectronCpuGraphConfig().ValueOrDie();
    }

    template<typename T>
    void SetInputSidePacket(const std::string& key, const T& value)
    {
        m_InputSidePackets[key] = mediapipe::MakePacket<T>(value);
    }

    mediapipe::Status Initialize()
    {
        LOG_AND_RETURN(m_Graph.Initialize(m_Config, m_InputSidePackets));
    }

    mediapipe::Status Start()
    {
        LOG_AND_RETURN(m_Graph.StartRun({}));
    }

private:
    mediapipe::CalculatorGraph m_Graph;
    mediapipe::CalculatorGraphConfig m_Config;
    std::map<std::string, mediapipe::Packet> m_InputSidePackets;
};

EXPORT(Graph*) UnityMediaPipe_Graph_Construct_() { return new Graph(); }

EXPORT(void) UnityMediaPipe_Graph_SetStringInputSidePacket(
    Graph* self, const char* key, int32_t keyLength,
    const char* value, int32_t valueLength)
{
    LOG(INFO) << "Setting " << key << " to a value of length " << valueLength;
    self->SetInputSidePacket(std::string(key, keyLength), std::string(value, valueLength));
}

EXPORT(absl::StatusCode) UnityMediaPipe_Graph_Initialize(Graph* self)
{
    return self->Initialize().code();
}

EXPORT(absl::StatusCode) UnityMediaPipe_Graph_Start(Graph* self)
{
    return self->Start().code();
}

}  // namespace mediapipe
